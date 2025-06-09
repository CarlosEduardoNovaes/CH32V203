#!/bin/bash

wget -c https://github.com/xpack-dev-tools/riscv-none-elf-gcc-xpack/releases/download/v14.2.0-3/xpack-riscv-none-elf-gcc-14.2.0-3-linux-x64.tar.gz
tar -xvf xpack-riscv-none-elf-gcc-14.2.0-3-linux-x64.tar.gz 
mv xpack-riscv-none-elf-gcc-14.2.0-3 ./toolchain
