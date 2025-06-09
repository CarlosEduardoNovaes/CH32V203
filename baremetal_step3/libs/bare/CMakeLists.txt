# Cria uma biblioteca estática chamada "bare"
add_library(bare STATIC)

# Habilita o suporte a módulos C++
set_target_properties(bare PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Adiciona os arquivos de módulo (interface e implementação)
target_sources(bare
    PRIVATE
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
            bare-traits.cppm bare.cppm
)

# # Opcional: inclui diretórios para dependências internas (caso o módulo use headers privados)
# target_include_directories(bare PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/src
# )

target_sources(bare PUBLIC bare.cppm)
