# cmake/CompilerWarnings.cmake - VERSÃO CORRIGIDA

function(set_project_warnings target_name)
    if(NOT TARGET ${target_name})
        message(WARNING "Target '${target_name}' does not exist, skipping warnings")
        return()
    endif()
    
    option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)

    set(MSVC_WARNINGS
        /W4
        /w14242 # conversion
        /w14254 # bitfield to bool
        /w14263 # member init
        /w14265 # class init
        /w14287 # unsigned compare
        /we4289 # var init
        /w14296 # expression
        /w14311 # truncation
        /w14545 # expression before comma
        /w14546 # before function
        /w14547 # before operator
        /w14549 # before operator
        /w14555 # expression has no effect
        /w14619 # pragma warning
        /w14640 # enable warning
        /w14826 # Conversion
        /w14905 # wide string
        /w14906 # string to char
        /w14928 # illegal copy
    )

    set(CLANG_WARNINGS
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wcast-align
        -Wunused
        -Woverloaded-virtual
        -Wconversion
        -Wsign-conversion
        -Wnull-dereference
        -Wdouble-promotion
        -Wformat=2
    )

    set(GCC_WARNINGS
        ${CLANG_WARNINGS}
        -Wmisleading-indentation
        -Wduplicated-cond
        -Wduplicated-branches
        -Wlogical-op
        -Wuseless-cast
    )

    if(WARNINGS_AS_ERRORS)
        set(CLANG_WARNINGS ${CLANG_WARNINGS} -Werror)
        set(GCC_WARNINGS ${GCC_WARNINGS} -Werror)
        set(MSVC_WARNINGS ${MSVC_WARNINGS} /WX)
    endif()

    if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        set(PROJECT_WARNINGS ${MSVC_WARNINGS})
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(PROJECT_WARNINGS ${CLANG_WARNINGS})
    else()
        set(PROJECT_WARNINGS ${GCC_WARNINGS})
    endif()

    target_compile_options(${target_name} PRIVATE ${PROJECT_WARNINGS})
    
    message(STATUS "Warning level set for target: ${target_name}")
endfunction()