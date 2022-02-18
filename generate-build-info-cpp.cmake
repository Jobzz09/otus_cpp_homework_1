file(READ "${BUILD_NUMBER_FILE}" build_number)
string(STRIP "${build_number}" build_number)


file(WRITE "${CPP_FILE}"
	"#ifndef BUIILD_NUMBER_H\n"
    "#define BUILD_NUMBER_H\n"
    "#include <stdint.h>\n"
    "#define PROJECT_BUILD_NUMBER ${build_number}\n"
    "#endif //BUILD_NUMBER_H\n"
    )