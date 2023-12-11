# #---------- reletive path define ----------##
set(CORE_MODULE_RELATIVE_DIR "core")
set(MEMORY_MODULE_RELATIVE_DIR "memory")

# #---------- define absolute path ----------##
cmake_path(APPEND CORE_MODULE_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${CORE_MODULE_RELATIVE_DIR})
cmake_path(APPEND MEMORY_MODULE_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${MEMORY_MODULE_RELATIVE_DIR})

# #---------- seach sorce files ----------##
aux_source_directory(${CORE_MODULE_DIR} CORE_MODULE_FILES)
aux_source_directory(${MEMORY_MODULE_DIR} MEMORY_MODULE_FILES)

# #---------- set files global ----------##
set(LLFRAME_MODULE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/llframe.ixx" PARENT_SCOPE)
set(CORE_MODULE_FILES ${CORE_MODULE_FILES} PARENT_SCOPE)
set(MEMORY_MODULE_FILES ${MEMORY_MODULE_FILES} PARENT_SCOPE)
