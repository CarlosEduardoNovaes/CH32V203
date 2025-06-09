# cmake/toolchain.cmake

# Caminho absoluto para a pasta do script
get_filename_component(_CMAKE_SCRIPT_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(TOOLCHAIN_DIR "${_CMAKE_SCRIPT_DIR}/../toolchain")

# Definições básicas do sistema
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR riscv)

# Caminhos dos compiladores
set(CMAKE_C_COMPILER "${TOOLCHAIN_DIR}/bin/riscv-none-elf-gcc")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_DIR}/bin/riscv-none-elf-g++")
set(CMAKE_ASM_COMPILER "${CMAKE_C_COMPILER}")
