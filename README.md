# CI-server

## Summary
This is an implementation of a small continuous integration CI-server that automatically tests code. The server is connected to a GitHub repository 
through a webhook, and whenever a pull request is made, the server runs the tests and notifies the user of the results on the pull request page.

## License
This project is licensed under the MIT License - see the LICENSE.md file for details.

## Prerequisites
The project requires CMake (version 3.2 or higher), C++ (14 or higher) and ngrok.

## Naming conventions
We will use [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html) for the code, and 
[this Git Style Guide](https://github.com/agis/git-style-guide) for commit messages.

## Compiling

This is one way to compile the project on a linux/debian based machine while in the project dir.

First running cmake to construct a Makefile
```
ci_test$ cmake -B./build -H.
```
Secondly run the make file to create executables
```
ci_test$ make -C ./build
```
There are now executables in the build folder one of them should be unittest, example of a executable being ran.
```
ci_test$ ./build/unittest
```

## Contributions

### Emma Good
* Created the JSON parser class that extracts data from the HTTP payload.

### Ted Klein Bergman
* Created main server 

### Yuanjue Li


### Fredrik Pilhqvist
* Created integrationTest function that compiles and tests a commit.
* Documented compiling.
* Testing server
