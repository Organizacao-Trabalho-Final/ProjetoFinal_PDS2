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

TEST_CASE("Teste função diaMes() - Data") {

    Data data(10, 06, 1942);

    CHECK(data.diaMes(2, 2025) == 28);
    CHECK(data.diaMes(2, 2016) == 29);
    CHECK(data.diaMes(3, 2000) == 31);
    CHECK(data.diaMes(4, 2000) == 30);

}

TEST_CASE("Teste função isValida() - Data") {

    Data data(30, 06, 1942);

    CHECK(data.isValida(30, 06, 1942) == true);
    CHECK(data.isValida(30, 06, -1942) == false);
    CHECK(data.isValida(30, 06, 19420) == false);
    CHECK(data.isValida(00, 06, 1942) == false);
    CHECK(data.isValida(30, 13, 1942) == false);
    CHECK(data.isValida(-10, 06, 1942) == false);
    CHECK(data.isValida(-15, -03, 1942) == false);
    CHECK(data.isValida(-30, 06, 19420) == false);
    CHECK(data.isValida(29, 02, 2038) == false);
    CHECK(data.isValida(28, 02, 2038) == true);

}

TEST_CASE("Teste função somarDias() - Data") {

    Data data1(10, 6, 1942);
    data1 = data1.somarDias(10);

    CHECK(data1.getDia() == 20);
    CHECK(data1.getMes() == 6);
    CHECK(data1.getAno() == 1942);

    data1 = data1.somarDias(10);

    CHECK(data1.getDia() == 30);
    CHECK(data1.getMes() == 6);
    CHECK(data1.getAno() == 1942);

    data1 = data1.somarDias(10);

    CHECK(data1.getDia() == 10);
    CHECK(data1.getMes() == 7);
    CHECK(data1.getAno() == 1942);

    Data data2(10, 12, 1942);
    data2 = data2.somarDias(10);

    CHECK(data2.getDia() == 20);
    CHECK(data2.getMes() == 12);
    CHECK(data2.getAno() == 1942);

    data2 = data2.somarDias(10);

    CHECK(data2.getDia() == 30);
    CHECK(data2.getMes() == 12);
    CHECK(data2.getAno() == 1942);

    data2 = data2.somarDias(10);

    CHECK(data2.getDia() == 9);
    CHECK(data2.getMes() == 1);
    CHECK(data2.getAno() == 1943);

    CHECK_THROWS(data2.somarDias(-10));
    CHECK_THROWS(data2.somarDias(0));

}

TEST_CASE("Teste função difenrencaDatas() - Data") {

    Data data1(30, 06, 1942);

    CHECK(data1.diferencaDatas(Data(30, 6, 1942)) == 0);
    CHECK(data1.diferencaDatas(Data(30, 7, 1942)) == 30);
    CHECK(data1.diferencaDatas(Data(10, 8, 1942)) == 41);


}







