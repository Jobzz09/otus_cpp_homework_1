cmake_minimum_required(VERSION 3.5.0)

set (CMAKE_CXX_STANDARD 20)
set(PROJECT_MAJOR_VERSION 1 CACHE INTERNAL "Major version")
set(PROJECT_MINOR_VERSION 0 CACHE INTERNAL "Minor version")
set(PROJECT_PATCH_VERSION 28 CACHE INTERNAL "Patch version")
set(PROJECT_VERSION ${PROJECT_MAJOR_VERSION}.${PROJECT_MINOR_VERSION}.${PROJECT_PATCH_VERSION})

file(GLOB TARGET_SRC "./src/*.cpp" )
file(GLOB TEST_SRC "./test/*.cpp")

option(WITH_BOOST_TEST "Whether to build Boost test" ON)

project(helloworld VERSION ${PROJECT_VERSION})

add_custom_target(generate_build_number
    COMMAND ${CMAKE_COMMAND}
            -D
    "BUILD_NUMBER_FILE=${PROJECT_BINARY_DIR}/build_number.txt"
    -P "${CMAKE_SOURCE_DIR}/generate-build-number.cmake"
    BYPRODUCTS "${PROJECT_BINARY_DIR}/build_number.txt"
    )

add_custom_command(
    OUTPUT "${PROJECT_BINARY_DIR}/build_info.hpp"
    COMMAND ${CMAKE_COMMAND}
    -D"BUILD_NUMBER_FILE=${PROJECT_BINARY_DIR}/build_number.txt"
    -D"CPP_FILE=${PROJECT_BINARY_DIR}/build_number.hpp"
    -P "${CMAKE_SOURCE_DIR}/generate-build-info-cpp.cmake"
    DEPENDS "${PROJECT_BINARY_DIR}/build_number.txt"
)

add_executable(${PROJECT_NAME} ${TARGET_SRC} "${PROJECT_BINARY_DIR}/build_info.hpp")

add_dependencies(${PROJECT_NAME} generate_build_number)


add_subdirectory(lib/mylib)

configure_file(version.h.in include/version.h)

target_include_directories(${PROJECT_NAME}
PUBLIC /lib/mylib/include
PUBLIC ${PROJECT_BINARY_DIR}
PUBLIC ${PROJECT_BINARY_DIR}/include)

target_include_directories(mylib
PUBLIC ${PROJECT_BINARY_DIR}/include)

target_link_directories(${PROJECT_NAME}
PRIVATE ./lib/mylib/src
PRIVATE ${PROJECT_BINARY_DIR}
)

target_link_libraries(${PROJECT_NAME}
PRIVATE mylib)

if (WITH_BOOST_TEST)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
        
    add_executable(boost_test_version ${TEST_SRC})

    set_target_properties(boost_test_version PROPERTIES
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})

    target_link_libraries(boost_test_version
        ${BOOST_LIBRARIES}
        mylib)
   
endif()

if (MSVC)
    target_compile_options(${PROJECT_NAME}
        PRIVATE /W4)
    target_compile_options(mylib
        PRIVATE /W4)
    if(WITH_BOOST_TEST)
        target_compile_options(boost_test_version
            PRIVATE /W4)
    endif()
else ()
    target_compile_options(${PROJECT_NAME}
        PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(mylib
        PRIVATE -Wall -Wextra -pedantic -Werror)
    if(WITH_BOOST_TEST)
        target_compile_options(boost_test_version
            PRIVATE -Wall -Wextra -pedantic -Werror)
    endif()
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT jobzz.off@gmail.com)
include(CPack)

if(WITH_BOOST_TEST)
    enable_testing()
    add_test(boost_test_version boost_test_version)
endif()

