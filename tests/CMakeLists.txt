if(NOT AMB_BUILD_TESTS)
    return()
endif()

# Find Catch2 or Google Test
# Por enquanto, vamos pular testes complexos
message(STATUS "Tests disabled for MVP - skipping test setup")