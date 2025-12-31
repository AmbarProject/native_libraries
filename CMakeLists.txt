# CMakeLists.txt - VERSÃO CORRIGIDA

cmake_minimum_required(VERSION 3.20)
project(ambar-package-manager
    VERSION 0.1.0
    DESCRIPTION "Ambar Package Manager"
    LANGUAGES CXX
)

# Opções do projeto
option(AMB_BUILD_TESTS "Build tests" OFF)  # Mudei para OFF inicialmente
option(AMB_ENABLE_SANITIZERS "Enable address and undefined sanitizers" OFF)
option(AMB_DOWNLOAD_CLI11 "Download CLI11 automatically" ON)

# C++ padrão
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Configurações específicas por plataforma
if(WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS -DNOMINMAX)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# Download CLI11 se necessário
if(AMB_DOWNLOAD_CLI11)
    include(cmake/DownloadCLI11.cmake)
    download_cli11()
endif()

# Subdiretórios PRINCIPAIS primeiro
add_subdirectory(src)

# Configurações de warnings - AGORA DEPOIS dos targets
include(cmake/CompilerWarnings.cmake)

# Testes - VAMOS CRIAR DEPOIS
if(AMB_BUILD_TESTS)
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests AND IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests)
        enable_testing()
        add_subdirectory(tests)
    else()
        message(WARNING "Tests directory not found, skipping tests")
    endif()
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
message(STATUS "=========================================")
message(STATUS "Ambar Package Manager v${PROJECT_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "C++ version: ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Tests: ${AMB_BUILD_TESTS}")
message(STATUS "=========================================")