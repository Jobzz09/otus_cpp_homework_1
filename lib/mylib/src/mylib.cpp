#include "mylib.h"
#include "version.h"

uint32_t get_version() {
    return PROJECT_VERSION_PATCH;
}

uint32_t get_build() {
    //return PROJECT_BUILD_NUMBER;
    return 0;
}

