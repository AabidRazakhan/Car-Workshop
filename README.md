# Car Workshop
***
Last Update : Sunday, 15. April 2021 11:22PM 

A Simple console application built using C++ (C++11 to be precise) that has following features.
- Assign Username for the admin user
- Password protecting the admin user so as to prevent unauthorized access to data
- Binary mode read and write
- Cross-Platform build and run support. (Works with Windows and Linux)

#### Overview
This project is a part of **CSE202 ETE Project** . I have used c++11 and c++17. It was fun making this project, i discovered a lot of new featues and learned a lot about c++11.

This is also my first cross plaform console application (Linux/Windows) I have tested and build the binary in ubuntu but it should also compile and run on windows. Below i will provide how to compile it yourself. 

#### Binaries
You can download the binary executable for the program from [here](https://github.com/coder3101/Car-Workshop/blob/master/cmake-build-debug/Car_Workshop)

To run the executable you need to run the following command from the directory where you have downloaded the binary. 

	./Car_Workshop

If you face any issues try to make this file executable by :

	chmod +x Car_Workshop

**I will soon update the windows binary here**

#### Compiling from Source 
You can download the complete source and compile it yourself. But before that you need to get any of the two build tools.

1. cmake : More info on downloading it [here](https://cmake.org/install/ )
2. Bazel : More info on downlaoding it [here](https://docs.bazel.build/versions/master/install-windows.html)

##### Using CMake

**YOU NEED TO USE THE MASTER BRANCH OF THIS REPOSITORY TO BUILD WITH CMAKE**

After you have configured the cmake run following with cmake bin in **PATH** :

```shell
<cmake_path> --build "<source_path>/cmake-build-debug" --target all -- -j 2
```

*cmake_path* : Path where cmake binary lies
*source_path* : Path where source code's main.cc lies

You will get the executable inside of *cmake-debug-build* directory
	
​	 
##### Using bazel

If you want to use bazel to build the executable from source first make sure bazel is in the **ENVIRONMENT** Variable.
Then download the code from **master-bazel** branch of this repository

**WARNING : YOU MUST DOWNLOAD CODE FROM THIS BRANCH AS THIS CONTAINS BAZEL SCRIPTS NECESSARY TO BUILD THE BINARY**

**BAZEL HAS SOME PROBLEMS BUILDING IF YOUR SOURCE'S ABSOLUTE PATH CONTAINS SPACES, MAKE SURE TO PLACE THE SOURCE CODE IN A PLACE WITH NO SPACES (LIKE C://)**

Run the following code inside of root of source directory or where a WORKSPACE file is located

```shell
bazel build //:build-app
```

Wait for few seconds, bazel will automatically build the binary and store the result in this location

```shell
/bazel-bin/build-app or /bazel-bin/build-app.exe
```

You can then run the binary

#### Known Issues

As no software is bugfree, it also have some issues in the code, most of those issues are highlighted with *//todo* or *//fixme* .

Only Known Issue I have found is duplication of vectors of orders when written or read from disk, and mismatch to mark order done that is result of duplication. I actaully have a lot to do, so i may or may not fix them.






