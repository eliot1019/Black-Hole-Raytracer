# Black-Hole-Raytracer
Raytracer for a Schwarzschild black hole
[Writeup](https://eliot1019.github.io/Black-Hole-Raytracer/)

![lava_disk.jpg](https://github.com/eliot1019/Black-Hole-Raytracer/blob/master/samples/lava_disk.jpg)

### Dependencies
- [OpenCV](https://opencv.org/releases/)

### Running on Mac
- Install [OpenCV](https://medium.com/@nuwanprabhath/installing-opencv-in-macos-high-sierra-for-python-3-89c79f0a246a) for Mac
- Install CMake and Xcode Toolchain
- Create a `build` folder in the root directory of the `Black-Hole-Raytracer` cloned repo
- Run `cmake .` to generate the make file for the project
- In src/Program.cpp, replace the input images for `DiskImg` and `SkyImg` with absolute paths on your machine (due to OpenCV on Mac bug)
- Run `make` and run the blackholeraytracer executable
 


### Running on Windows
- Install [Visual Studio 2017 with Visual Studio C++ Support](https://docs.microsoft.com/en-us/cpp/build/vscpp-step-0-installation?view=vs-2017)
- Install [CMake](https://cmake.org/download/)
- Create a `build` folder in the root directory of the `Black-Hole-Raytracer` cloned repo
- Use CMake to compile, generate, and open this project
    - Point the source code to the project repo path
    - Set the binary build location to the `build` folder
    - Click `Configure` and choose the `Visual Studio 15 2017 Win64` option
    - Click `Generate` and then `Open Project`
- Follow instructions [here](https://www.deciphertechnic.com/install-opencv-with-visual-studio/) to install and link OpenCV

