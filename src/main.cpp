#include "mylib.h"

#include <iostream>

template <typename T>
void ignore(T&&);

int main([[maybe_unused]]int argc, [[maybe_unused]] char** argv) {
    std::cout << "Version: " << get_version() << std::endl;
    std::cout << "Build: " << get_build() << std::endl;
    std::cout << "Hello, World from otus c++ pro homework 1!!!!" << std::endl;
    std::cout << "Student: Maxim Korytko" << std::endl;
    return 0;
}

template<typename T>
void ignore(T&&) {}