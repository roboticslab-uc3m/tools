## tools: Installation from Source Code

First install the dependencies:
- [Install CMake](https://github.com/roboticslab-uc3m/installation-guides/blob/master/install-cmake.md)
- [Install YARP](https://github.com/roboticslab-uc3m/installation-guides/blob/master/install-yarp.md)

### Install tools on Ubuntu (working on all tested versions)

Our software integrates the previous dependencies. Note that you will be prompted for your password upon using `sudo` a couple of times:

```bash
cd  # go home
mkdir -p repos; cd repos  # create $HOME/repos if it does not exist; then, enter it
git clone --recursive https://github.com/roboticslab-uc3m/tools.git  # Download tools software from the repository; Use --recursive to get embedded repositories (technically, git submodules)
cd tools; mkdir build; cd build; cmake ..  # Configure the tools software
make -j$(nproc) # Compile
sudo make install # Install :-)
cp ../scripts/gnome/tools.desktop $HOME/Desktop
sudo pip install -r requirements.txt #Install python requirements
```

For CMake `find_package(ROBOTICSLAB_TOOLS REQUIRED)`, you may also be interested in adding the following to your `~/.bashrc` or `~/.profile`:
```bash
export ROBOTICSLAB_TOOLS_DIR=$HOME/repos/tools/build  # Points to where TEOConfig.cmake is generated upon running CMake
```

For additional options use `ccmake` instead of `cmake`.

