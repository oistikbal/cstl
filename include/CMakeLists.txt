add_library(cstl INTERFACE)

file(GLOB_RECURSE CSTL_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/cstl/*.h")

target_sources(cstl 
    PRIVATE ${CSTL_HEADERS}
)

source_group(
    TREE "${CMAKE_CURRENT_SOURCE_DIR}"
    PREFIX "Header Files"
    FILES ${CSTL_HEADERS}
)

set_target_properties(cstl PROPERTIES CXX_STANDARD 20)
set_target_properties(cstl PROPERTIES CXX_STANDARD_REQUIRED True)