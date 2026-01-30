add_library(cstl INTERFACE)

target_include_directories(cstl INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

file(GLOB_RECURSE CSTL_LIB_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")

target_sources(cstl INTERFACE 
    $<BUILD_INTERFACE:${CSTL_LIB_HEADERS}>
)

set_target_properties(cstl PROPERTIES CXX_STANDARD 20)
set_target_properties(cstl PROPERTIES CXX_STANDARD_REQUIRED True)