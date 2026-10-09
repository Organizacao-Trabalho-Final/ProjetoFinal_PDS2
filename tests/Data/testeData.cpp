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

TEST_CASE("Teste função isBissexto - Data") {

        Data data(10, 06, 1942);

        CHECK(data.isBissexto(2016) ==  true);
        CHECK(data.isBissexto(2020) ==  true);
        CHECK(data.isBissexto(2024) ==  true);
        CHECK(data.isBissexto(2023) == false);
        CHECK(data.isBissexto(2025) == false);
        CHECK(data.isBissexto(2026) == false);
        CHECK(data.isBissexto(2028) ==  true);
        CHECK(data.isBissexto(2035) == false);
        CHECK(data.isBissexto(2037) == false);
        CHECK(data.isBissexto(2038) == false);
        CHECK_THROWS(data.isBissexto(-2000));
        CHECK_THROWS(data.isBissexto(20242));

}

