# Introduction

This small projects applies a Sobel filter to an image benefiting from some of the tools available from OpenCV.

# Installation

This projects uses some OpenCV libraries, hence the OpenCV repository comes as a submodule of the project. Idelly, if you have a system-wide installation, the needed libraries will be automatically fetched. If this is not the case, I recommend build the minimum requisites together with this project.

## Installing the Project + OpenCV in Linux

First, make sure your machine fulfills all the prerequisites to build OpenCV, which are listed in the OpenCV documentation "[Installation in Linux](https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html)". I further recomend the following packages to have graphical interfaces (`highgui`) supported:
```bash
sudo apt update
sudo apt install libgtk2.0-dev pkg-config libcanberra-gtk-module
```

Next clone the project making sure the submodules are also pulled:
```bash
git clone --recursive git@github.com:salvesg/BorderProfiler.git
```
Navigate to the `external` folder, where the OpenCV project should have been cloned to. If it is not there or the folder exist or its empty, you might have forgoted the `--recursive` flag. You can re-initialize the submodules with
```bash
git submodule update --init --recursive
```

### Building OpenCV

Once inside `external/opencv`, create the build directory and jump to it:
```bash
mkdir build && cd build
```
Configure cmake with:
```bash
cmake .. \
	-DCMAKE_BUILD_TYPE=Release \
	-DBUILD_LIST=core,imgcodecs,highgui \
	-DWITH_GTK=ON
```
Configuration should be pretty fast. You can check the text printed to `stdout` to verify that only the desired packages have been set as build targets, and that GTK support has been enabled. Finish building (you can indicate how many CPU cores to use but it is fairly fast).
```bash
make # OPtional -j$(nproc)
```

### Build the project

**Note**: This section is work under progress. 

For the moment, only a test script is available with the project. To compile it, in the root directory of the project run:
```bash
mkdir build && cd build
```
Once inside, do:
```bash
cmake .. -DOpenCV_DIR=../external/opencv/build
```
This will help cmake find the necesary configuration file from our own OpenCV installation. Follow with
```bash
make
```
And you will find an executable in the `bin` directory called `PoliteCat`. Execute it to see a very polite cat. Press the `s` key to create a copy of such a polite cat (nice). Press any other key (except the switch-off button) to stop seeing the polite cat (sad).
