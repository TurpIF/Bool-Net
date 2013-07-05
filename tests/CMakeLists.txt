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
    "matrix_model"
    "timed_matrix_model"
    )

find_package(PythonInterp 2 QUIET)
if(${PYTHONINTERP_FOUND})
else()
    message(WARNING "Python not found. Impossible to add the run targets")
endif()

# Add all defined tests
foreach(e ${TESTS})
    if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${e}")
        message(FATAL_ERROR "Cannot add test ${e}, no directory with that name lies in ${CMAKE_CURRENT_SOURCE_DIR}")
    else()
        set(e_exe_name "CELLBOOL_${e}")
        file(GLOB_RECURSE e_sources "${CMAKE_CURRENT_SOURCE_DIR}/${e}/*.cpp")
        add_executable(${e_exe_name} ${e_sources})
        target_link_libraries(${e_exe_name} ${CELLBOOL_LIB})

        set(run_file_dir "${CMAKE_CURRENT_SOURCE_DIR}/${e}")
        set(run_file "run.sh")
        set(run_file_in  "${run_file}.in")
        if(${PYTHONINTERP_FOUND} AND EXISTS "${run_file_dir}/${run_file_in}")
            set(run_name "test.${e}.run")
            set(run_path "${CMAKE_CURRENT_BINARY_DIR}/${e}.run")

            message(STATUS "Adding the run target ${run_name}")

            set(SRC_DIR "${run_file_dir}")
            set(BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}")
            set(EXE "${e_exe_name}")

            configure_file(${run_file_dir}/${run_file_in} ${run_path}/${run_file})

            add_custom_target(${run_name}
                COMMAND sh ${run_path}/${run_file}
                WORKING_DIRECTORY ${run_path}
                COMMENT "Executing the script of the test ${e}" VERBATIM
                DEPENDS ${e_exe_name}
            )
        endif()
    endif()
endforeach()
