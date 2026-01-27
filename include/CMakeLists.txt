add_library(cstl INTERFACE)

target_include_directories(cstl INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

#
#source_group(
#    TREE "${CMAKE_CURRENT_SOURCE_DIR}"
#   PREFIX "Header Files"
#    FILES ${CSTL_HEADERS}
#)


set_target_properties(cstl PROPERTIES CXX_STANDARD 20)
set_target_properties(cstl PROPERTIES CXX_STANDARD_REQUIRED True)