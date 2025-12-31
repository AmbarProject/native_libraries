function(download_cli11)
    if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/third_party/CLI11.hpp")
        message(STATUS "Downloading CLI11...")
        
        set(CLI11_URL "https://github.com/CLIUtils/CLI11/releases/download/v2.3.2/CLI11.hpp")
        set(CLI11_PATH "${CMAKE_CURRENT_SOURCE_DIR}/third_party/CLI11.hpp")
        
        file(DOWNLOAD
            ${CLI11_URL}
            ${CLI11_PATH}
            TLS_VERIFY ON
            STATUS DOWNLOAD_STATUS
        )
        
        list(GET DOWNLOAD_STATUS 0 STATUS_CODE)
        if(NOT STATUS_CODE EQUAL 0)
            message(WARNING "Failed to download CLI11. Please download manually.")
        else()
            message(STATUS "CLI11 downloaded successfully")
        endif()
    endif()
endfunction()