## tools: Installation from Source Code

First install the dependencies:
- [Install CMake](https://github.com/roboticslab-uc3m/installation-guides/blob/develop/install-cmake.md)
- [Install YARP](https://github.com/roboticslab-uc3m/installation-guides/blob/develop/install-yarp.md)
- [Install KDL](https://github.com/roboticslab-uc3m/installation-guides/blob/develop/install-kdl.md)
- Only for `testBasicCartesianControl`, we use `FakeControlboard` from [openrave-yarp-plugins](https://github.com/roboticslab-uc3m/openrave-yarp-plugins):
```bash
cd  # go home
mkdir -p repos; cd repos  # create $HOME/repos if it does not exist; then, enter it
git clone https://github.com/roboticslab-uc3m/openrave-yarp-plugins
cd openrave-yarp-plugins
git checkout d58cfecf097ded53f014ac982e949b233b4e3c40
mkdir build && cd build
cmake .. -DENABLE_OpenraveYarpControlboard=OFF -DENABLE_OpenraveYarpPaintSquares=OFF -DENABLE_YarpOpenraveControlboard=OFF -DENABLE_YarpOpenraveControlboardCollision=OFF -DENABLE_teoSim=OFF
make -j$(nproc)  # compile
sudo make install
cd ../..
```

### Install tools on Ubuntu (working on all tested versions)

Our software integrates the previous dependencies. Note that you will be prompted for your password upon using `sudo` a couple of times:

```bash
cd  # go home
mkdir -p repos; cd repos  # create $HOME/repos if it does not exist; then, enter it
git clone --recursive https://github.com/roboticslab-uc3m/tools.git  # Download tools software from the repository; Use --recursive to get embedded repositories (technically, git submodules)
cd tools; mkdir build; cd build; cmake ..  # Configure the tools software
make -j$(nproc) # Compile
sudo make install  # Install :-)
cp ../scripts/gnome/tools.desktop $HOME/Desktop
```

For CMake `find_package(ROBOTICSLAB_TOOLS REQUIRED)`, you may also be interested in adding the following to your `~/.bashrc` or `~/.profile`:
```bash
export ROBOTICSLAB_TOOLS_DIR=$HOME/repos/tools/build  # Points to where TEOConfig.cmake is generated upon running CMake
```

For additional options use ccmake instead of cmake.

### Even more!

Done! You are now probably interested in one of the following links:
- [Simulation and Basic Control: Now what can I do?]( teo-post-install.md )
