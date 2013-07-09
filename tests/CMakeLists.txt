# List of all tests
set(TESTS
    "matrix_model"
    "timed_matrix_model"
    )

# Add all defined tests
foreach(e ${TESTS})
    if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${e}")
        message(FATAL_ERROR "Cannot add test ${e}, no directory with that name lies in ${CMAKE_CURRENT_SOURCE_DIR}")
    else()
        set(e_exe_name ${e})
        file(GLOB_RECURSE e_sources "${CMAKE_CURRENT_SOURCE_DIR}/${e}/*.cpp")
        add_executable(${e_exe_name} ${e_sources})
        target_link_libraries(${e_exe_name} ${BOOL_NETWORK_LIB})
    endif()
endforeach()
