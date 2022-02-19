#define BOOST_TEST_MODULE boost_test_build
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <build_number.hpp>

BOOST_AUTO_TEST_SUITE(boost_test_build)

BOOST_AUTO_TEST_CASE(test_build_number) {
    BOOST_CHECK(static_cast<uint32_t>(get_build()) > 0);
}

BOOST_AUTO_TEST_SUITE_END()