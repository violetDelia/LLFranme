find_package(LLFrame REQUIRED PATHS ${INSTALL_DIR})
# # ---------- install_test ----------# #
add_executable(install_test "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
target_include_directories(install_test
    PRIVATE
    $<BUILD_INTERFACE:${INSTALL_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${NONE}>
)
message(${INSTALL_LIB_DIR})
target_link_libraries(install_test PRIVATE LLFrame)

