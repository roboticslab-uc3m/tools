# RealToSimControlboard

```bash
yarp server
```

## Example with Dextra
Example invocation with a `leftDextra`:
```bash
yarpdev --device RealToSimControlboard --context RealToSimControlboard --from leftDextra.ini
```

Example invocation with a `leftDextra` in a `teoSim`:
```bash
yarpdev --device RealToSimControlboard --context RealToSimControlboard --from leftDextra.ini --prefix teoSim
```

## Example with Lacquey Fetch
```bash
openrave --module OpenraveYarpPluginLoader "env openrave/lacqueyFetch/lacqueyFetch.robot.xml open --device controlboardwrapper2 --subdevice YarpOpenraveControlboard --robotIndex 0 --allManipulators" --viewer qtcoin --collision ode
```
