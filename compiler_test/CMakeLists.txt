# # ---------- options ----------# #
if(DEFINED COMPILER_TEST_OPTION)
    unset(COMPILER_TEST_OPTION CACHE)
endif()

option(COMPILER_TEST_OPTION "Test if the compilation is working" ON)

if(COMPILER_TEST_OPTION)
    # # ---------- mcompiler_test ----------# #
    # compiler_cuda_test
    add_library(compiler_cuda_test "${CMAKE_CURRENT_SOURCE_DIR}/compiler_cuda_test.cu")
    target_include_directories(compiler_cuda_test
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${INCLUDE_DIR}>
    )
    target_link_libraries(compiler_cuda_test)

    # compiler_module_test
    add_library(compiler_module_test "${CMAKE_CURRENT_SOURCE_DIR}/compiler_module_test.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/compiler_module_test.ixx")
    target_include_directories(compiler_module_test
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${INCLUDE_DIR}>
    )
    target_link_libraries(compiler_module_test PUBLIC compiler_cuda_test)

    # compiler_test
    add_executable(compiler_test "${CMAKE_CURRENT_SOURCE_DIR}/compiler_test.cpp")
    target_include_directories(compiler_test
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
        $<INSTALL_INTERFACE:${INCLUDE_DIR}>
    )
    target_link_libraries(compiler_test PUBLIC compiler_module_test)

    # #---------- install ----------##
    install(TARGETS compiler_test
        DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
