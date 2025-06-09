cmake_minimum_required(VERSION 3.25)

# 🎯 Define o projeto após garantir que o toolchain foi baixado
project(Firmware C CXX ASM)


# 📌 C++20 com suporte a módulos
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 📁 Diretórios do projeto
set(SRC_DIR     "${CMAKE_SOURCE_DIR}/src")
set(STARTUP_DIR "${CMAKE_SOURCE_DIR}/startup")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(LIBS_DIR    "${CMAKE_SOURCE_DIR}/libs")
set(BIN_DIR     "${CMAKE_SOURCE_DIR}/bin")

# Cria pasta de saída binária
file(MAKE_DIRECTORY ${BIN_DIR})

# Incluir headers
include_directories(${INCLUDE_DIR})

# 🔎 Coleta fontes da aplicação
file(GLOB_RECURSE APP_SOURCES
    "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.c" "${SRC_DIR}/*.cxx"
    "${SRC_DIR}/*.cppm" "${SRC_DIR}/*.cxxm"
)

# 🔎 Coleta fontes de startup
file(GLOB STARTUP_SOURCES
    "${STARTUP_DIR}/*.c" "${STARTUP_DIR}/*.s" "${STARTUP_DIR}/*.S"
)

# 🔁 Adiciona bibliotecas de libs/
file(GLOB CHILD_LIB_DIRS RELATIVE ${LIBS_DIR} ${LIBS_DIR}/*)
foreach(lib ${CHILD_LIB_DIRS})
    if(IS_DIRECTORY "${LIBS_DIR}/${lib}")
        add_subdirectory(${LIBS_DIR}/${lib})
    endif()
endforeach()

# 🛠️ Cria executável final
add_executable(firmware.elf
    ${APP_SOURCES}
    ${STARTUP_SOURCES}
)

# 📎 Include para headers da aplicação
target_include_directories(firmware.elf PRIVATE ${INCLUDE_DIR})

# 🔗 Link com bibliotecas (alvo: mesmo nome do diretório)
foreach(lib ${CHILD_LIB_DIRS})
    target_link_libraries(firmware.elf PRIVATE ${lib})
endforeach()

# ⚙️ Flags típicas para compilação bare-metal
target_compile_options(firmware.elf PRIVATE
    -Wall -Wextra -Werror
    -ffreestanding -nostdlib
)

# 🧩 Opções de link
target_link_options(firmware.elf PRIVATE
    -T${STARTUP_DIR}/linker.ld
    -nostdlib -Wl,--gc-sections -Wl,-Map=${BIN_DIR}/firmware.map
)

# 🔄 Gera firmware.bin e firmware.hex após build
add_custom_command(TARGET firmware.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary firmware.elf ${BIN_DIR}/firmware.bin
    COMMAND ${CMAKE_OBJCOPY} -O ihex   firmware.elf ${BIN_DIR}/firmware.hex
    COMMENT "Gerando firmware.bin e firmware.hex"
)
