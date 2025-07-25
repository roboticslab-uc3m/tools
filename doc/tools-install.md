## tools: Installation from Source Code

First install the dependencies:
- [Install CMake 3.19+](https://github.com/roboticslab-uc3m/installation-guides/blob/master/docs/install-cmake.md/)
- [Install YCM 0.11+](https://github.com/roboticslab-uc3m/installation-guides/blob/master/docs/install-ycm.md/)
- [Install YARP 3.11+](https://github.com/roboticslab-uc3m/installation-guides/blob/master/docs/install-yarp.md/)

For unit testing, you'll need the googletest source package. Refer to [Install googletest](https://github.com/roboticslab-uc3m/installation-guides/blob/master/docs/install-googletest.md/).

### Install tools on Ubuntu (working on all tested versions)

Our software integrates the previous dependencies. Note that you will be prompted for your password upon using `sudo` a couple of times:

```bash
cd  # go home
mkdir -p repos; cd repos  # create $HOME/repos if it does not exist; then, enter it
git clone --recursive https://github.com/roboticslab-uc3m/tools.git  # Download tools software from the repository; Use --recursive to get embedded repositories (technically, git submodules)
cd tools; mkdir build; cd build; cmake ..  # Configure the tools software
make -j$(nproc) # Compile
sudo make install # Install :-)
```

For additional options, use `ccmake` instead of `cmake`.
