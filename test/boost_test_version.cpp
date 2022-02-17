#define BOOST_TEST_MODULE boost_test_version

#include "mylib.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(boost_test_version)

BOOST_AUTO_TEST_CASE(test_valid_version) {
    BOOST_CHECK(static_cast<uint32_t>(get_version()) > 0);
}

BOOST_AUTO_TEST_SUITE_END()