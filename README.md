# Build Instructions

## Windows
1. Clone this repository <br>
`$ git clone https://github.com/gpl27/milipede.git`

2. Download and install [MSYS2](https://www.msys2.org/)

3. Download and install [CMake](https://cmake.org/download/)

4. Use CMake to generate Makefiles and compile the code
- Open CMake
- Specify the path of the "src" folder in the option "Where is the source code:" 
![4.1](https://user-images.githubusercontent.com/83479142/186039910-ff2ee543-b439-4c81-ac9e-440c699fbec0.png)
- Create a folder named "build" and specify the path in the option "Where to build the binaries:"
![4.2](https://user-images.githubusercontent.com/83479142/186040498-2a8f2b73-2114-457b-adc7-38cb9e34029c.png)
- Select the option "Generate"
- Specify "MinGW Makefiles" for generator and select the default option
![4.3](https://user-images.githubusercontent.com/83479142/186040024-cd8868f4-fdc2-4547-95a1-b00d4fcaaa7a.png)
- Click Finish

5. Set up the environment using Visual Studio Code
- Install the [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) extension
- Search and click the button on the VS Code status bar where is written "No Kit Selected"
- Select the GCC Kit
6. Build the project in Visual Studio Code
- Click on the "Build" button on the VS Code status bar

## Linux
`$ cd milipede`

`$ mkdir build`

`$ cd build`

`$ cmake ../src`

`$ cmake --build .`
