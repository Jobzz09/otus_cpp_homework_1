file(GLOB MYLIB_TARGET_SRC "./src/*.cpp")

add_library(mylib ${MYLIB_TARGET_SRC})

target_include_directories(mylib
PUBLIC include)