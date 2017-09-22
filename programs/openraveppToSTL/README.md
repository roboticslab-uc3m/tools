# openraveppToStl script

This script is designed to do the conversion between the .pp files obtained with the openrave convex decomposition model used/created [here](https://github.com/roboticslab-uc3m/openrave-yarp-plugins/blob/develop/examples/openrave-YarpRobot-collision-sim.py), 
to a more standard file format (stl), in order to be used with other frameworks like ArmarX, and so on.

## How to use it

Just change this [line](https://github.com/roboticslab-uc3m/tools/blob/b565045f11cd0b2f0ec0fc403823d679b8a79fd3/programs/openraveppToSTL/openraveppToSTL.py#L21) to be the filename of the pp file you want to convert.

then run the python script in this folder
```
python openravepp-to-stl.py 
```
