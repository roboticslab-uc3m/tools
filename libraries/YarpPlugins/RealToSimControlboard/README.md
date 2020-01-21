# RealToSimControlboard

```bash
yarp server
```

## Example with Left Dextra
```bash
openrave --module OpenraveYarpPluginLoader "env openrave/dextra/leftDextra.robot.xml open --device controlboardwrapper2 --subdevice YarpOpenraveControlboard --robotIndex 0 --allManipulators" --viewer qtcoin --collision ode
```

```bash
yarpdev --device RealToSimControlboard --context RealToSimControlboard --from leftDextra.ini
```

## Example with Left Dextra in a teoSim
```bash
teoSim
```

```bash
yarpdev --device RealToSimControlboard --context RealToSimControlboard --from leftDextra.ini --prefix teoSim
```

## Example with Lacquey Fetch
```bash
openrave --module OpenraveYarpPluginLoader "env openrave/lacqueyFetch/lacqueyFetch.robot.xml open --device controlboardwrapper2 --subdevice YarpOpenraveControlboard --robotIndex 0 --allManipulators" --viewer qtcoin --collision ode
```

```bash
yarpdev --device RealToSimControlboard --context RealToSimControlboard --from lacqueyFetch.ini --prefix /lacqueyFetch
```

## Example with Lacquey Fetch in a teoSim
```bash
teoSim
```

```bash
yarpdev --device RealToSimControlboard --context RealToSimControlboard --from lacqueyFetch.ini
```
