if(PROJECT_IS_TOP_LEVEL)
    message(STATUS "cstl: Building development/test environment")
    
    file(GLOB_RECURSE CSTL-TEST-SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
    file(GLOB_RECURSE CSTL-TEST-HEADERS "${PROJECT_SOURCE_DIR}/include/cstl/*.h")

    add_executable(cstl-test ${CSTL-TEST-SOURCES})
    target_link_libraries(cstl-test PUBLIC cstl)

    target_sources(cstl-test PRIVATE ${CSTL-TEST-HEADERS})

endif()