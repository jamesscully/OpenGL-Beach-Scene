# OpenGL Beach Scene
## Overview
Written in C++ with freeGlut to meet requirements for computer graphics. 

Implemented features:

* Model loading - requires single, triangulated mesh in .obj format in ```Models/``` folder
* Material loading - requires .mtl file in ```Models/``` folder
* UV / Texture loading - loads UV vertices from .obj, texture from ```Models/UV/``` 

## Requirements
- CMake 3.15 
- GCC 10.1 (tested + built on)

or, if you're using Visual Studio to compile
- Windows SDK 10.0.16299.0 and Toolset v141 (VS2017) 



## Installation
### Windows
If you're using Visual Studio, open the .sln and it *should* be configured to run out of the box. Similarly, I believe CLion should also auto-configure when opening the CMakeLists.txt. 

Alternatively, translate the Linux commands below; they should be somewhat close to compliant on Windows

### Linux

To build the executable manually, first enter the main directory
```bash
$ cd G53GRA.Framework/G53GRA.Framework
```

Generate build files for CMake
```bash
$ cmake CMakeLists.txt
```

Generate the executable from the Makefile
```bash
$ make
```

The executable should then be generated under the current directory, so

```bash
./G53GRA.Framework
```

Or if you're in a hurry, 

```bash
cd G53GRA.Framework/G53GRA.Framework && cmake CMakeLists.txt && make && ./G53GRA.Framework
```


