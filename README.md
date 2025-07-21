# Introduction

This small projects applies a Sobel filter to an image benefiting from some of the tools available from OpenCV.

It consist on a simple class called `ImageBorders` (see `lib/ImageBorders.cc` for the implementation) that inherits from the `cv::Mat` class. **Warning**: This is designed so it is easier to call `cv::Mat` functions, but `Mat` class does not have a virtual destructor so do not use with polymorphism. The final product is an executable that takes and image and displays its borders, or saves them as a new image.

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
git clone --recursive https://github.com/salvesg/BorderProfiler.git
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
make # Optional -j$(nproc)
```

### Build and run the project

To build the library simply procced from the project root directory as:
```bash
mkdir build && cd build
```
If you have [OpenMP](https://www.openmp.org/) installed in your system (comes by default with many gcc installation), parallelization of the border obtention can be done. If not you will be pronted with a warning during configuration. You can install it simply with `sudo apt install libomp-dev`.

To compile the project do (for system-wide installation ignore the `-DOpenCV_DIR` argument or make it point to where it is installed, usually in `/usr/local`).
```bash
cmake .. -DOpenCV_DIR=<full_path_to_project>/external/opencv/build
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
To benefit from parallel procesing, you will have to set the number of threads to be used yourself (default: 1). For example, to span 4 parallel workers, simply export the following environment variable `export OMP_NUM_THREADS=4`. Notice that performance might saturate for high degrees of parallelization (>4 threads) due to many reason.

## Installing the project on Windows

**Note:** This instruction might not help you set up the project on windows correctly. Opening an issue is recomended in that case.

To install and make the project work on windows you will need some prerequisites.
 - Make sure you have *Visual Studio* installed with the *Desktop development with C++* workload. Make sure the MSVC compiler and Cmake tools for Windows are included.
 - While you can download and build OpenCV yourself, you can simply download the precompiled binaries and extract them, for example, to `C:\opencv`.
 - Download this project manually or using git: `git clone https://github.com/salvesg/BorderProfiler.git` (you don't need the OpenCV submodule)
 
Open a `x64 Native Tools Command Prompt for VS`, which you can easily acchive by pressing the windows key and typing it. Navigate to the project main folder and do:
```cmd
mkdir build
cd build
```
Then, configure the project with:
```cmd
cmake .. -DOpenCV_DIR="C:/opencv/build"
```
Hopefully, configuration will be succesfull, but it will tell you that it is better if you add `C:\opencv\build\x64\vc16\bin` to your `PATH` variable. You can do this with the windows environment manager. (at this point you might as well create the variable `OpenCV_DIR` for the next time you configure it).

Finally, at the same `build` folder, do:
```cmd
cmake --build . --config Release
```
You will find the resulting executable under `bin\Release` as *BorderProfiler.exe*. Test that it works with:
```cmd
bin\Release\BorderProfiler.exe pictures\bike.jpg
```
You should see the borders of the bike. Press any key or close the window to end the program. Add an extra folder path to the command line to save the border image to that folder

If you were not prompted otherwise, parallelization through OpenMP is enable. On the command line, you can control the number of threads to use for procesing the image with:
```cmd
set OMP_NUM_THREADS=<num of threads desired>
```

