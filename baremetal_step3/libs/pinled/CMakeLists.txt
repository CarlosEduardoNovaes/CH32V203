# Cria uma biblioteca estática chamada "pinled"
add_library(pinled STATIC)

# Habilita o suporte a módulos C++
set_target_properties(pinled PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Adiciona os arquivos de módulo (interface e implementação)
target_sources(pinled
    PRIVATE
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
            pinled.cppm
)

# # Opcional: inclui diretórios para dependências internas (caso o módulo use headers privados)
# target_include_directories(pinled PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/src
# )

# # Se o módulo exportar dependências externas, você pode linká-las aqui
# target_link_libraries(pinled PUBLIC pinled)
target_link_libraries(pinled PROVATE system)
