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

TEST_CASE("Teste função diaMes() - Data") {

    Data data(10, 06, 1942);

    CHECK(data.diaMes(2, 2025) == 28);
    CHECK(data.diaMes(2, 2016) == 29);
    CHECK(data.diaMes(3, 2000) == 31);
    CHECK(data.diaMes(4, 2000) == 30);

}

TEST_CASE("Teste função Dias() - Data") {

    Data data(10, 06, 1942);

    CHECK(data.Dias(31, 12, 2016) == 366);
    CHECK(data.Dias(31, 12, 2038) == 365);
    CHECK(data.Dias(31, 05, 2016) == 152);
    CHECK(data.Dias(24, 01, 2000) == 24 );
    CHECK(data.Dias(05, 04, 2023) == 95 );
    CHECK_THROWS(data.Dias(05,  04, 20240));
    CHECK_THROWS(data.Dias(-05, 04,  2024));
    CHECK_THROWS(data.Dias(05,  -1,  2024));
    CHECK_THROWS(data.Dias(05,  04, -2024));
    CHECK_THROWS(data.Dias(05,  13,  2024));
    CHECK_THROWS(data.Dias(29,  02,  2038));

}



