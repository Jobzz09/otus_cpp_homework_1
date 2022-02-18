#include "mylib.h"

#include <iostream>
#include "build_number.hpp"

int main([[maybe_unused]]int argc, [[maybe_unused]] char** argv) {
    std::cout << "Build: "  << PROJECT_BUILD_NUMBER << std::endl;
    std::cout << "Hello, World!" << std::endl;
    
    return 0;
}

