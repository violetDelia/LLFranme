find_package(LLFrame 1.0.0 REQUIRED PATHS ${INSTALL_DIR})

# # ---------- install_test ----------# #
add_executable(install_test "${CMAKE_CURRENT_SOURCE_DIR}/install_test.cpp")
target_include_directories(install_test
    PRIVATE
    $<BUILD_INTERFACE:${INSTALL_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${NONE}>
)
target_link_libraries(install_test PRIVATE llframe)
