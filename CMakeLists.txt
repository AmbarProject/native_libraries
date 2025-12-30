cmake_minimum_required(VERSION 3.20)
project(ambar-package-manager 
    VERSION 0.1.0 
    DESCRIPTION "Ambar Package Manager"
    LANGUAGES CXX
)

# Opções do projeto
option(AMB_BUILD_TESTS "Build tests" ON)
option(AMB_BUILD_EXAMPLES "Build examples" OFF)
option(AMB_ENABLE_SANITIZERS "Enable address and undefined sanitizers" OFF)

# C++ padrão
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Configurações específicas por plataforma
if(WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS -DNOMINMAX)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# Políticas do CMake
cmake_policy(SET CMP0077 NEW)

# Diretórios de output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Subdiretórios
add_subdirectory(src)

# Testes
if(AMB_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Configurações de sanitizers (debug)
if(AMB_ENABLE_SANITIZERS AND CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    add_compile_options(
        -fsanitize=address,undefined
        -fno-sanitize-recover=all
        -fno-omit-frame-pointer
    )
    add_link_options(
        -fsanitize=address,undefined
    )
endif()

# Informações do projeto
message(STATUS "========================================")
message(STATUS "Ambar Package Manager v${PROJECT_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Build tests: ${AMB_BUILD_TESTS}")
message(STATUS "========================================")