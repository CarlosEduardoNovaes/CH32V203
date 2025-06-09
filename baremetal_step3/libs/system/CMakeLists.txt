# Cria a biblioteca estática chamada "system"
add_library(system STATIC)

# Define as versões e padrões do C++
set_target_properties(system PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Adiciona os arquivos-fonte (C e C++)
target_sources(system PRIVATE
    system.cxx
)

# Define o diretório onde estão os headers públicos da lib
target_include_directories(system PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
)

# # (Opcional) Adiciona flags específicas para essa lib
# target_compile_options(system PRIVATE
#     -Wall -Wextra
# )

# (Opcional) Linka com outras bibliotecas se necessário
# target_link_libraries(system PUBLIC OutraLib)
