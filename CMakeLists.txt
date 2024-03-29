cmake_minimum_required(VERSION 3.5.0)

set (CMAKE_CXX_STANDARD 20)

set(PROJECT_MAJOR_VERSION 1 CACHE INTERNAL "Major version")
set(PROJECT_MINOR_VERSION 0 CACHE INTERNAL "Minor version")
set(PROJECT_PATCH_VERSION 28 CACHE INTERNAL "Patch version")
set(PROJECT_VERSION ${PROJECT_MAJOR_VERSION}.${PROJECT_MINOR_VERSION}.${PROJECT_PATCH_VERSION})

file(GLOB TARGET_SRC "./src/*.cpp" )
file(GLOB TEST_SRC "./test/*.cpp")

option(WITH_BOOST_TEST "Whether to build Boost test" OFF)
option(WITH_GOOGLE_TEST "Whether to build gtest" OFF)

project(helloworld VERSION ${PROJECT_VERSION})

add_custom_target(generate_build_number
    COMMAND ${CMAKE_COMMAND}
            -D
    "BUILD_NUMBER_FILE=${CMAKE_SOURCE_DIR}/build_number.txt"
    -P "${CMAKE_SOURCE_DIR}/generate-build-number.cmake"
    BYPRODUCTS "${CMAKE_SOURCE_DIR}/build_number.txt"
    )

add_custom_command(
    OUTPUT "${PROJECT_BINARY_DIR}/build_info.hpp"
    COMMAND ${CMAKE_COMMAND}
    -D"BUILD_NUMBER_FILE=${CMAKE_SOURCE_DIR}/build_number.txt"
    -D"CPP_FILE=${PROJECT_BINARY_DIR}/build_number.hpp"
    -P "${CMAKE_SOURCE_DIR}/generate-build-info-cpp.cmake"
    DEPENDS "${CMAKE_SOURCE_DIR}/build_number.txt"
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
    set (BOOST_COMPONENTS
    thread 
    filesystem
    unit_test_framework)

    set (Boost_USE_STATIC_LIBS ON)

    set (Boost_USE_MULTITHREADED ON)

    include_directories(${Boost_INCLUDE_DIRS})

    find_package(Boost COMPONENTS ${BOOST_COMPONENTS} REQUIRED)
    
    add_definitions(-DBOOST_TEST_STATIC_LINK)

    add_executable(boost_test_version 
        "./test/boost_test_version.cpp"
        )
    
    target_link_libraries(boost_test_version
        ${CMAKE_THREAD_LIBS_INIT} 
        ${Boost_LIBRARIES}
        mylib)

        add_test(boost_test_version boost_test_version)

        add_executable(boost_test_build
        "./test/boost_test_build.cpp"
        "${PROJECT_BINARY_DIR}/build_info.hpp")

        target_link_libraries(boost_test_build
        ${CMAKE_THREAD_LIBS_INIT} 
        ${Boost_LIBRARIES})

        target_include_directories(boost_test_build
        PUBLIC "${PROJECT_BINARY_DIR}")

        add_test(boost_test_build boost_test_build)

        enable_testing()
        
   
endif()

if (WITH_GOOGLE_TEST)
    find_package(PkgConfig)
    
    pkg_check_modules(GTEST REQUIRED gtest>=1.5.0)
    
    include_directories(
        ${GTEST_INCLUDE_DIRS}
    )

    add_executable(google_test_version "./test/google_test_version.cpp" "./test/main.cpp")
    add_executable(google_test_build "./test/google_test_build.cpp" "./test/main.cpp" "${PROJECT_BINARY_DIR}/build_info.hpp")
    
    target_link_libraries(google_test_version
    PRIVATE ${GTEST_LIBRARIES}
    PRIVATE mylib)

    target_link_libraries(google_test_build
    PRIVATE ${GTEST_LIBRARIES})

    target_include_directories(google_test_build
    PUBLIC ${PROJECT_BINARY_DIR})

    add_test(google_test_version google_test_version)
    add_test(google_test_build google_test_build)

    enable_testing()
#
#
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


