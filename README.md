# CI-server

## Summary
The goal of this project is to implements a small continuous integration CI server. We use Github as our development platform and C++ as the language. The CI server only contains some core features of continuous integration like compilation, testing and notification.

## Compiling

This is one way to compile the project on a linux/debian based machine while in the project dir.

First running cmake to construct a Makefile
```
ci_test$ cmake -B./build -H.
```
Secondly run the make file to create exicutables
```
ci_test$ make -C ./build
```
There are now exicutables in the build folder one of them should be unittest, example of a exicutable being ran.
```
ci_test$ ./build/unittest
```
