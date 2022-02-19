#include "mylib.h"

#include <iostream>
#include "build_number.hpp"

int main([[maybe_unused]]int argc, [[maybe_unused]] char** argv) {
    std::cout << "Build: "  << get_build() << std::endl;
    std::cout << "Hello, World!" << std::endl;
    
    return 0;
}

