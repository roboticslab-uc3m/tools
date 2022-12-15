from argparse import ArgumentParser
import time
import yarp

import matplotlib.pyplot as plt

parser = ArgumentParser(description='Visualize step response and manually tune a PID.')
parser.add_argument('--prefix', required=True, type=str, help='robot port prefix')
parser.add_argument('--carrier', default='unix_stream', type=str, help='carrier used for reading robot state')
parser.add_argument('--joint', required=True, type=int, help='joint id')
parser.add_argument('--type', default='pos', type=str, help='PID type (pos, vel)')
parser.add_argument('--kp', type=float, help='proportional gain')
parser.add_argument('--ki', type=float, help='integral gain')
parser.add_argument('--kd', type=float, help='derivative gain')
parser.add_argument('--initial', type=float, help='joint value to be achieved on start [deg]')
parser.add_argument('--step', type=float, default=1.0, help='step size [deg]')
parser.add_argument('--duration', type=float, default=5.0, help='command duration [s]')
parser.add_argument('--sampling', type=float, default=1e-3, help='sampling period [s]')
parser.add_argument('--period', type=float, help='command period [s] (enables staircase reference)')
parser.add_argument('--store', action='store_true', help='preserve new PID coefficients')
args = parser.parse_args()

if args.duration <= 0.0:
    raise ValueError('Duration must be positive')

if args.sampling <= 0.0:
    raise ValueError('Sampling period must be positive')

if args.period is not None and args.period <= 0.0:
    raise ValueError('Command period must be positive')

yarp.Network.init()

if not yarp.Network.checkNetwork():
    raise RuntimeError('YARP server not running')

options = yarp.Property()
options.put('device', 'remote_controlboard')
options.put('remote', args.prefix)
options.put('local', '/pidTuning' + args.prefix)
options.put('carrier', args.carrier)

dd = yarp.PolyDriver(options)

if not dd.isValid():
    raise RuntimeError('Unable to open device')

time.sleep(0.5) # wait for first data to arrive

limits = dd.viewIControlLimits()
mode = dd.viewIControlMode()
enc = dd.viewIEncoders()
pid = dd.viewIPidControl()
pos = dd.viewIPositionControl()
posd = dd.viewIPositionDirect()

if not 0 <= args.joint < enc.getAxes():
    raise ValueError('Joint id %d out of range' % args.joint)

min = yarp.DVector(1)
max = yarp.DVector(1)

if not limits.getLimits(args.joint, min, max):
    raise RuntimeError('Unable to get joint limits')

print('Joint limits: %f [deg], %f [deg]' % (min[0], max[0]))

pidType = yarp.encode(args.type)
v_pid = yarp.PidVector(1)

if not pid.getPid(pidType, args.joint, v_pid):
    raise RuntimeError('Unable to get PID')

print('Current PID: kp=%f, ki=%f, kd=%f' % (v_pid[0].kp, v_pid[0].ki, v_pid[0].kd))

if args.initial is not None:
    print('Moving joint q%d to %f [deg]' % (args.joint, args.initial))

    if not mode.setControlMode(args.joint, yarp.VOCAB_CM_POSITION):
        raise RuntimeError('Unable to set POS mode')

    if not pos.positionMove(args.joint, args.initial):
        raise RuntimeError('Unable to move joint')

    while True:
        time.sleep(0.1)
        if pos.checkMotionDone(): break

    time.sleep(1.0) # give it some time to settle

initial = enc.getEncoder(args.joint)
print('Initial position: %f [deg]' % initial)

if not mode.setControlMode(args.joint, yarp.VOCAB_CM_POSITION_DIRECT):
    raise RuntimeError('Unable to set POSD mode')

using_new_pid = False

if args.kp is not None or args.ki is not None or args.kd is not None:
    new_pid = yarp.Pid(v_pid[0].kp, v_pid[0].kd, v_pid[0].ki,
                       v_pid[0].max_int, v_pid[0].scale, v_pid[0].max_output)

    if args.kp is not None: new_pid.kp = args.kp
    if args.ki is not None: new_pid.ki = args.ki
    if args.kd is not None: new_pid.kd = args.kd

    if not pid.setPid(pidType, args.joint, new_pid):
        raise RuntimeError('Unable to set new PID')

    print('New PID: kp=%f, ki=%f, kd=%f' % (new_pid.kp, new_pid.ki, new_pid.kd))
    using_new_pid = True

print('Starting... step=%f [deg], duration=%f [s], sampling=%f [ms]' % (args.step, args.duration, args.sampling * 1000))

t = []
y_enc = []
y_ref = []
start = time.time()

def doStep(target, samples):
    if not posd.setPosition(args.joint, target):
        raise RuntimeError('Unable to move joint')

    for i in range(samples):
        now = time.time()
        t.append(now - start)
        y_enc.append(abs(enc.getEncoder(args.joint) - initial))
        y_ref.append(abs(target - initial))

        # https://stackoverflow.com/a/25251804/10404307
        time.sleep(args.sampling - ((now - start) % args.sampling))

if args.period is not None:
    target = initial
    samples = int(args.period / args.sampling)
    n_steps = int(args.duration / args.period)

    print('Staircase reference: period=%f [s], n_steps=%d, distance=%f [deg], speed=%f [deg/s]' % (
        args.period, n_steps, abs(n_steps * args.step), abs(args.step) / args.period
    ))

    for i in range(n_steps):
        target += args.step
        doStep(target, samples)
else:
    target = initial + args.step
    samples = int(args.duration / args.sampling)
    doStep(target, samples)

print('Done')
plt.plot(t, y_enc, 'b')
plt.plot(t, y_ref, 'r')
plt.xlabel('time (s)')
plt.ylabel('position (deg)')
plt.title('Step response')

plt.show()

if using_new_pid:
    if args.store:
        print('Preserving new PID coefficients')
    else:
        if not pid.setPid(pidType, args.joint, v_pid[0]):
            raise RuntimeError('Unable to restore old PID')

        print('Restored old PID')
