# RealToSimControlBoard

```bash
yarp server
```

## Example with Left Dextra
```bash
openrave --module OpenraveYarpPluginLoader "env openrave/dextra/leftDextra.robot.xml open --device controlBoard_nws_yarp --subdevice YarpOpenraveControlBoard --robotIndex 0 --allManipulators" --viewer qtcoin --collision ode
```

```bash
yarpdev --device RealToSimControlBoard --context RealToSimControlBoard --from leftDextra.ini
```

## Example with Left Dextra in a teoSim
```bash
teoSim dextra
```

```bash
yarpdev --device RealToSimControlBoard --context RealToSimControlBoard --from leftDextra.ini --name /teoSim/leftHand --remotePrefix /teoSim/leftDextra
```

## Example with Lacquey Fetch
```bash
openrave --module OpenraveYarpPluginLoader "env openrave/lacqueyFetch/lacqueyFetch.robot.xml open --device controlBoard_nws_yarp --subdevice YarpOpenraveControlBoard --robotIndex 0 --allManipulators" --viewer qtcoin --collision ode
```

```bash
yarpdev --device RealToSimControlBoard --context RealToSimControlBoard --from lacqueyFetch.ini
```

## Example with Lacquey Fetch (left) in a teoSim
```bash
teoSim
```

```bash
yarpdev --device RealToSimControlBoard --context RealToSimControlBoard --from lacqueyFetch.ini --name /teoSim/leftHand --remotePrefix /teoSim/leftLacqueyFetch
```
