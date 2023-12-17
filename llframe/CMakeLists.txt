# #---------- option cache ----------# #

# #---------- build options ----------# #

if(TEST_ALL)
    option(LLFRAME_TEST "test llframe" ON)
endif()

# #---------- project settings ----------# #
project(LLFrame VERSION ${LLFrame_VERSION} LANGUAGES CXX C CUDA)

# #---------- reletive path define ----------##
set(LLFRAME_CMAKE_RELATIVE_DIR "cmake")
set(LLFRAME_TEST_RELATIVE_DIR "test")
set(LLFRAME_INCLUDE_RELATIVE_DIR "include")
set(LLFRAME_SOURCE_RELATIVE_DIR "src")
set(LLFRAME_MODULE_RELATIVE_DIR "module")
set(LLFRAME_INSTALL_INCLUDE_RELATIVE_DIR "llframe")
set(LLFRAME_INSTALL_MODULE_RELATIVE_DIR "__MODULE__")

# #---------- define absolute path ----------##
cmake_path(APPEND LLFRAME_CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${LLFRAME_CMAKE_RELATIVE_DIR})
cmake_path(APPEND LLFRAME_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${LLFRAME_TEST_RELATIVE_DIR})
cmake_path(APPEND LLFRAME_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${LLFRAME_INCLUDE_RELATIVE_DIR})
cmake_path(APPEND LLFRAME_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${LLFRAME_SOURCE_RELATIVE_DIR})
cmake_path(APPEND LLFRAME_MODULE_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${LLFRAME_MODULE_RELATIVE_DIR})
cmake_path(APPEND LLFRAME_INSTALL_INCLUDE_DIR ${INSTALL_INCLUDE_DIR} ${LLFRAME_INSTALL_INCLUDE_RELATIVE_DIR})
cmake_path(APPEND LLFRAME_INSTALL_MODULE_DIR ${LLFRAME_INSTALL_INCLUDE_DIR} ${LLFRAME_INSTALL_MODULE_RELATIVE_DIR})
set(LLFRAME_INSTALL_LIB_DIR ${INSTALL_LIB_DIR})
set(LLFRAME_INSTALL_CMAKE_DIR ${INSTALL_CMAKE_DIR})
set(LLFRAME_INSTALL_RUNTIME_DIR ${INSTALL_RUNTIME_DIR})
set(LLFRAME_INCLUDE_DIR ${LLFRAME_INCLUDE_DIR} PARENT_SCOPE)
# #---------- generate configure header file ----------##
configure_file("config.h.in" "${LLFRAME_INCLUDE_DIR}/config.h")

# add subdirectory
if(USE_MODULE)
    add_subdirectory(${LLFRAME_MODULE_DIR})
endif(USE_MODULE)

add_subdirectory(${LLFRAME_SOURCE_DIR})

# #---------- seach sorce files ----------##
aux_source_directory(${LLFRAME_SOURCE_DIR} LLFRAME_SOURCE_FILES)

if(USE_MODULE)
    list(APPEND LLFRAME_SOURCE_FILES ${LLFRAME_MODULE_FILES})
endif(USE_MODULE)

# #---------- compiler llframe ----------##
add_library(LLFrame ${LLFRAME_SOURCE_FILES})

set_target_properties(LLFrame PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
target_include_directories(LLFrame
    PRIVATE
    $<BUILD_INTERFACE:${LLFRAME_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${LLFRAME_INSTALL_DIR}>
)

target_link_libraries(LLFrame
    PUBLIC LLFrame_core LLFrame_memory LLFrame_tensor
)


# #---------- setting version ----------##
set_property(TARGET LLFrame PROPERTY VERSION ${LLFRAME_VERSION})

# #---------- test ----------##
if(LLFRAME_TEST)
    enable_testing()
    configure_file("test_config.h.in" "${LLFRAME_TEST_DIR}/test_config.h")
    add_subdirectory(${LLFRAME_TEST_DIR})
endif(LLFRAME_TEST)

# #---------- install ----------##
include(CMakePackageConfigHelpers)
install(DIRECTORY "${LLFRAME_INCLUDE_DIR}/" DESTINATION "${LLFRAME_INSTALL_INCLUDE_DIR}")
install(DIRECTORY "${LLFRAME_MODULE_DIR}/" DESTINATION "${LLFRAME_INSTALL_MODULE_DIR}" FILES_MATCHING PATTERN "*.ixx")
install(TARGETS LLFrame LLFrame_core LLFrame_memory LLFrame_tensor
    EXPORT LLFrameTargets
    RUNTIME DESTINATION ${LLFRAME_INSTALL_RUNTIME_DIR}
    LIBRARY DESTINATION ${LLFRAME_INSTALL_LIB_DIR}
    ARCHIVE DESTINATION ${LLFRAME_INSTALL_LIB_DIR})

install(EXPORT LLFrameTargets
    FILE LLFrameTargets.cmake
    DESTINATION ${LLFRAME_INSTALL_CMAKE_DIR}
)

configure_package_config_file("${LLFRAME_CMAKE_DIR}/LLFrameConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/LLFrameConfig.cmake"
    INSTALL_DESTINATION ${LLFRAME_INSTALL_CMAKE_DIR}
)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/LLFrameConfigVersion.cmake"
    VERSION ${LLFRAME_VERSION}
    COMPATIBILITY SameMajorVersion)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/LLFrameConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/LLFrameConfigVersion.cmake"
    DESTINATION ${LLFRAME_INSTALL_CMAKE_DIR})