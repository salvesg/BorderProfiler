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

### Build and run the project

The project consist on a simple class called `ImageBorders` that inherits from the `cv::Mat` class. **Warnning**: This is designed so it is easier to call `cv::Mat` functions, but `Mat` class does not have a virtual destructor so do not use with polymorphism. 

To build the library simple procced as:
```bash
mkdir build && cd build
cmake .. -DOpenCV_DIR=../external/opencv/build
make
```
This will create the library `lib/libImageBorders.a` and the `bin/CreateBorders`. 

To see the class in action, you can find some examples images in the `pictures` directory. From the root directory, run:
```bash
bin/CreateBorders ./pictures/bike.jpg
```
and you will be pronted the borders of your image. Close the pop up window or press any key on the terminal to end the program. To save the borders of your image, just run the command again indicating the path where the borders should be saved:
```bash
mkdir borders
bin/CreateBorders ./pictures/bike.jpg ./borders
```
