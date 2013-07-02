# List of all tests
set(TESTS
    #"model1_mutant_conv"
    #"yeast_fixed_points"
    #"ligand_activator"
    #"model_stochastic"
    #"model_timed"
    #"epo_complex"
    #"fonctor"
    #"dynamic_network"
    "converge_yeast"
    "converge_fadd"
    "decision_fadd"
    "decision_gata1"
    )

# Add all defined tests
foreach(e ${TESTS})
    if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${e}")
        message(FATAL_ERROR "Cannot add test ${e}, no directory with that name lies in ${CMAKE_CURRENT_SOURCE_DIR}")
    else()
        set(e_exe_name "CELLBOOL_${e}")
        file(GLOB_RECURSE e_sources "${CMAKE_CURRENT_SOURCE_DIR}/${e}/*.cpp")
        add_executable(${e_exe_name} ${e_sources})
        target_link_libraries(${e_exe_name} ${CELLBOOL_LIB})
    endif()
endforeach()
