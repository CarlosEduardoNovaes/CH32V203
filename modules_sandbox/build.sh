#!/bin/bash
g++ -std=c++23 -c -fmodules-ts -x c++  math.cppm
g++ -std=c++23 -c -fmodules-ts -x c++  bitfield.cppm
g++ -std=c++23 -c -fmodules-ts -x c++  reg.cppm
g++ -std=c++23  -fmodules-ts   main.cpp math.o reg.o -o app