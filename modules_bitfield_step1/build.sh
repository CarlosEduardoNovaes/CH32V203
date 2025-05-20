#!/bin/bash
g++ -std=c++23 -O3 -c -fmodules-ts -x c++  math.cppm
g++ -std=c++23 -O3 -c -fmodules-ts -x c++  bitfield.cppm
g++ -std=c++23 -O3 -c -fmodules-ts -x c++  reg.cppm
#g++ -std=c++23 -O3 -fmodules-ts   main.cpp math.o reg.o -o app
#objdump -d -S --no-show-raw-insn app > app.asm
