if(PROJECT_IS_TOP_LEVEL)
    message(STATUS "cstl: Building development/test environment")
    
    file(GLOB_RECURSE CSTL-TEST-SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

    add_executable(cstl-test ${CSTL-TEST-SOURCES})
    target_link_libraries(cstl-test PRIVATE cstl)
    
    target_compile_options(cstl-test PRIVATE -Wall -Wextra -Wpedantic)
endif()