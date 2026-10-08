#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../third_party/doctest.h"
#include "../../include/Data.hpp"

TEST_CASE("Teste Construtor - Data") {

    CHECK_THROWS(Data( 10,  13,   2006));
    CHECK_THROWS(Data( 32,  10,   2006));
    CHECK_THROWS(Data(-10,  10,  -2006));
    CHECK_THROWS(Data( 10, -06,   2006));
    CHECK_THROWS(Data( 29,  02,   2001));
    CHECK_THROWS(Data( 31,  04,   2006));

}

