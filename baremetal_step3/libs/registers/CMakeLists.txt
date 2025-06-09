# Cria uma biblioteca estática chamada "registers"
add_library(registers STATIC)

# Habilita o suporte a módulos C++
set_target_properties(registers PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Adiciona os arquivos de módulo (interface e implementação)
target_sources(registers
    PRIVATE
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
            bitview.cppm
)

# # Opcional: inclui diretórios para dependências internas (caso o módulo use headers privados)
# target_include_directories(registers PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/src
# )

# Se o módulo exportar dependências externas, você pode linká-las aqui
target_link_libraries(registers PUBLIC bare)
