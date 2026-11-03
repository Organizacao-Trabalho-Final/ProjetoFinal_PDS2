#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "Data.hpp"

TEST_CASE("Teste Construtor - Data") {
    CHECK_THROWS(Data( 10,  13,   2006));
    CHECK_THROWS(Data( 32,  10,   2006));
    CHECK_THROWS(Data(-10,  10,  -2006));
    CHECK_THROWS(Data(  0,  10,  -2006));
    CHECK_THROWS(Data( 10,  10,      0));
    CHECK_THROWS(Data( 10,  10, -20060));
    CHECK_THROWS(Data( 10,  -6,   2006));
    CHECK_THROWS(Data( 29,   2,   2001));
    CHECK_THROWS(Data( 31,   4,   2006));
    CHECK_THROWS(Data( 29,   2,   2023));
    CHECK_THROWS(Data( 31,   6,   2026));
    CHECK_THROWS(Data( 31,  11,   2026));

    CHECK_NOTHROW(Data(  1,   1,     1));
    CHECK_NOTHROW(Data( 31,   1,  2000));
    CHECK_NOTHROW(Data( 29,   2,  2024));
    CHECK_NOTHROW(Data( 31,  12,  2026));
}

TEST_CASE("Teste getters - Data") {
    Data data(15, 8, 2026);

    CHECK(data.getDia() == 15);
    CHECK(data.getMes() == 8);
    CHECK(data.getAno() == 2026);
    CHECK(data.getData() == "15/8/2026");
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

    Data data3(31, 12, 2026);
    data3 = data3.somarDias(1);

    CHECK(data3.getDia() == 1);
    CHECK(data3.getMes() == 1);
    CHECK(data3.getAno() == 2027);

    Data data4(1, 1, 2026);
    data4 = data4.somarDias(365);

    CHECK(data4.getDia() == 1);
    CHECK(data4.getMes() == 1);
    CHECK(data4.getAno() == 2027);

    Data data5(1, 1, 2024);
    data5 = data5.somarDias(366);

    CHECK(data5.getDia() == 1);
    CHECK(data5.getMes() == 1);
    CHECK(data5.getAno() == 2025);

    CHECK_THROWS(data2.somarDias(-10));
    CHECK_THROWS(data2.somarDias(0));
}

TEST_CASE("Teste anos bissexto - Data") {
    Data data1(28, 2, 2024);
    data1 = data1.somarDias(1);

    CHECK(data1.getDia() == 29);
    CHECK(data1.getMes() == 2);
    CHECK(data1.getAno() == 2024);

    data1 = data1.somarDias(1);

    CHECK(data1.getDia() == 1);
    CHECK(data1.getMes() == 3);
    CHECK(data1.getAno() == 2024);

    CHECK_NOTHROW(Data(29, 2, 2000));
    CHECK_THROWS(Data(29, 2, 1900));
    CHECK_NOTHROW(Data(29, 2, 2024));
    CHECK_THROWS(Data(29, 2, 2023));
}

TEST_CASE("Teste fevereiro em ano não bissexto - Data") {
    Data data(28, 2, 2023);
    data = data.somarDias(1);

    CHECK(data.getDia() == 1);
    CHECK(data.getMes() == 3);
    CHECK(data.getAno() == 2023);
}

TEST_CASE("Teste função diferencaDatas() - Data") {
    Data data1(30, 6, 1942);

    CHECK(data1.diferencaDatas(Data(30, 6, 1942)) == 0);
    CHECK(data1.diferencaDatas(Data(30, 7, 1942)) == 30);
    CHECK(data1.diferencaDatas(Data(10, 8, 1942)) == 41);

    CHECK(Data(31, 12, 2026).diferencaDatas(Data(1, 1, 2027)) == 1);
    CHECK(Data(30, 12, 2026).diferencaDatas(Data(2, 1, 2027)) == 3);
    CHECK(Data(28, 2, 2024).diferencaDatas(Data(1, 3, 2024)) == 2);
    CHECK(Data(28, 2, 2023).diferencaDatas(Data(1, 3, 2023)) == 1);
    CHECK(Data(1, 1, 2026).diferencaDatas(Data(1, 1, 2027)) == 365);
    CHECK(Data(1, 1, 2024).diferencaDatas(Data(1, 1, 2025)) == 366);
    CHECK(Data(10, 1, 2026).diferencaDatas(Data(5, 1, 2026)) == -5);
}

TEST_CASE("Teste função isValida() - Data") {
    Data data(10, 6, 1942);
    CHECK(data.isValida());
}