#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../third_party/doctest.h"
#include "../../include/Tratamento.hpp"
#include <stdexcept>

TEST_CASE("Getters dos limites") {
    Tratamento t1;
    CHECK(t1.getMinNum() == 0);
    CHECK(t1.getMaxNum() == 1000);
    CHECK(t1.getMinString() == 0);
    CHECK(t1.getMaxString() == 50);
}

TEST_CASE("Setters dos limites") {
    Tratamento t2;
    t2.setMinNum(5);
    t2.setMaxNum(50);
    t2.setMinString(20);
    t2.setMaxString(800);
    CHECK(t2.getMinNum() == 5);
    CHECK(t2.getMaxNum() == 50);
    CHECK(t2.getMinString() == 20);
    CHECK(t2.getMaxString() == 800);
}

TEST_CASE("Teste função isVazio() - Tratamento") {
    Tratamento t3;
    CHECK(t3.isVazio("Rezeck", "Nome") == false);
    CHECK(t3.isVazio("12345678910", "") == false);
    CHECK_THROWS(t3.isVazio("", "CPF"));
}

TEST_CASE("Teste função isPositivo() - Tratamento") {
    Tratamento t4;
    CHECK(t4.isPositivo(10, "NUM") == true);
    CHECK(t4.isPositivo(0, "NUM") == true);
    CHECK(t4.isPositivo(1, "") == true);
    CHECK_THROWS(t4.isPositivo(-10, "NUM"));
}

TEST_CASE("Teste função isNumeroValido() - Tratamento") {
    Tratamento t5;
    CHECK(t5.isNumeroValido(0, "NUM") == true);
    CHECK(t5.isNumeroValido(1000, "NUM") == true);
    CHECK(t5.isNumeroValido(500, "NUM") == true);
    CHECK_THROWS(t5.isNumeroValido(-1, "NUM"));
    CHECK_THROWS(t5.isNumeroValido(1001, "NUM"));
}

TEST_CASE("Teste função isNumeroValido() - Tratamento") {
    Tratamento t6;
    CHECK(t6.isNumeroValido(0, 0, 10, "NUM") == true);
    CHECK(t6.isNumeroValido(10, 0, 10, "NUM") == true);
    CHECK(t6.isNumeroValido(5, 0, 10, "NUM") == true);
    CHECK_THROWS(t6.isNumeroValido(-1, 0, 10, "NUM"));
    CHECK_THROWS(t6.isNumeroValido(11, 0, 10, "NUM"));
}

TEST_CASE("Teste função isStringValido() - Tratamento") {
    Tratamento t7;
    t7.setMinString(2);
    t7.setMaxString(10);
    CHECK(t7.isStringValido("ab", "NOME") == true);
    CHECK(t7.isStringValido("abcdefghij", "") == true);
    CHECK(t7.isStringValido("abcde", "NOME") == true);
    CHECK_THROWS(t7.isStringValido("a", "NOME"));
    CHECK_THROWS(t7.isStringValido("Limite Excedido", "NOME"));
    CHECK_THROWS(t7.isStringValido("UFMG2026", "NOME"));
}

TEST_CASE("Teste função isStringValido() - Tratamento") {
    Tratamento t8;
    CHECK(t8.isStringValido("ab", 2, 10, false, "NOME") == true);
    CHECK(t8.isStringValido("abcdefghij", 2, 10, false, "") == true);
    CHECK(t8.isStringValido("abcde", 2, 10, false, "NOME") == true);
    CHECK(t8.isStringValido("12345678910", 0, 11, true, "CPF") == true);
    CHECK_THROWS(t8.isStringValido("a", 2, 10, false, "NOME"));
    CHECK_THROWS(t8.isStringValido("Limite Excedido", 2, 10, false, "NOME"));
    CHECK_THROWS(t8.isStringValido("UFMG2026", 2, 10, false, "NOME"));
}

TEST_CASE("Teste função getCaracterInvalidos() - Tratamento") {
    Tratamento t9;
    t9.setCaracterInvalidos("!@#$%^&*()_+-=~`");
    CHECK(t9.getCaracterInvalidos() == "!@#$%^&*()_+-=~`");
    }

TEST_CASE("Teste função isCaracterValido() - Tratamento") {
    Tratamento t10;
    t10.setCaracterInvalidos("!@#$%^&*()_+-=~`");
    CHECK(t10.isCaracterValido("HelloWorld", "STR") == true);
    CHECK(t10.isCaracterValido("Hello World", "") == true);
    CHECK_THROWS(t10.isCaracterValido("Hello World!", "STR"));
    CHECK_THROWS(t10.isCaracterValido("", "STR"));

    CHECK(t10.isCaracterValido("HelloWorld", "!@#$%^&*()_+-=~`", "STR") == true);
    CHECK(t10.isCaracterValido("Hello World", "!@#$%^&*()_+-=~`", "") == true);
    CHECK_THROWS(t10.isCaracterValido("Hello World!", "!@#$%^&*()_+-=~`", "STR"));
    CHECK_THROWS(t10.isCaracterValido("", "!@#$%^&*()_+-=~`", "STR"));
}

TEST_CASE("Teste função temNumeroString() e temNumeroStringEX() - Tratamento") {
    Tratamento t11;
    CHECK(t11.temNumeroString("HelloWorld") == false);
    CHECK(t11.temNumeroString("Hello World 123") == true);

    CHECK(t11.temNumeroStringEX("HelloWorld", "STR") == false);
    CHECK_THROWS(t11.temNumeroStringEX("Hello World 123", "STR"));
    CHECK_THROWS(t11.temNumeroStringEX("Hello World 123", ""));
}

TEST_CASE("Teste função somenteNumeros() e somenteNumerosEX() - Tratamento") {
    Tratamento t12;
    CHECK(t12.somenteNumeros("HelloWorld") == false);
    CHECK(t12.somenteNumeros("123") == true);

    CHECK(t12.somenteNumerosEX("123", "STR") == true);
    CHECK(t12.somenteNumerosEX("123", "") == true);
    CHECK_THROWS(t12.somenteNumerosEX("Hello World 123", "STR"));
    CHECK_THROWS(t12.somenteNumerosEX("Hello World 123", ""));
}

TEST_CASE("Teste função validarCPF() - Tratamento") {
    Tratamento t13;
    CHECK(t13.validarCPF("12345678910") == true);
    CHECK_THROWS(t13.validarCPF("1234567891"));
    CHECK_THROWS(t13.validarCPF("123456789101"));
    CHECK(t13.validarCPF("52998224725") == true);
    CHECK_THROWS(t13.validarCPF("52998224724"));
    CHECK_THROWS(t13.validarCPF("11111111111"));
    CHECK_THROWS(t13.validarCPF(""));
}

TEST_CASE("Teste função validarMatricula() - Tratamento"){
    Tratamento t14;
    CHECK(t14.validarMatricula("2025028972") == true);
    CHECK_THROWS(t14.validarMatricula("202528972"));
    CHECK_THROWS(t14.validarMatricula("20250289721"));
    CHECK_THROWS(t14.validarMatricula("2025e28972"));
    CHECK_THROWS(t14.validarMatricula(""));
}

TEST_CASE("Teste função validarQtdEX() e validarQtd() - Tratamento") {
    Tratamento t15;
    t15.setMaxString(10);
    t15.setMinString(2);
    CHECK(t15.validarQtd("ab") == true);
    CHECK(t15.validarQtd("abcdefghij") == true);
    CHECK(t15.validarQtd("abcde") == true);
    CHECK(t15.validarQtd("1", 1, 10) == true);
    CHECK(t15.validarQtd("1234567890", 1, 10) == true);   
    CHECK(t15.validarQtd("12345", 1, 10) == true);   
    CHECK(t15.validarQtd("1234567890123") == false);
    CHECK(t15.validarQtd("a") == false);
    CHECK(t15.validarQtd("1234567890", 1, 5) == false);
    CHECK(t15.validarQtd("ab", 3, 10) == false);

    CHECK(t15.validarQtdEX("abcdefghij") == true);
    CHECK(t15.validarQtdEX("ab") == true);
    CHECK(t15.validarQtdEX("abcde", "STR") == true);
    CHECK(t15.validarQtdEX("12345", 5, 10) == true);
    CHECK(t15.validarQtdEX("12", 2, 10, "STR") == true);
    CHECK(t15.validarQtdEX("12345", 5, 10, "STR") == true);
    CHECK_THROWS(t15.validarQtdEX("1", 2, 10));
    CHECK_THROWS(t15.validarQtdEX("123456789101", 2, 10, "STR"));
    CHECK_THROWS(t15.validarQtdEX("a"));
    CHECK_THROWS(t15.validarQtdEX("abcdefghijk", "STR"));
}

TEST_CASE("Setters rejeitam limites inconsistentes") {
    Tratamento t;
    CHECK_THROWS_AS(t.setMinString(-1), std::invalid_argument);
    CHECK(t.getMinString() == 0);
    CHECK_THROWS_AS(t.setMaxString(-1), std::invalid_argument);
    CHECK(t.getMaxString() == 50);

    t.setMinString(10);
    CHECK_THROWS_AS(t.setMaxString(9), std::invalid_argument);
    CHECK(t.getMaxString() == 50);
    CHECK_THROWS_AS(t.setMinString(51), std::invalid_argument);
    CHECK(t.getMinString() == 10);

    t.setMinNum(10);
    CHECK_THROWS_AS(t.setMaxNum(9), std::invalid_argument);
    CHECK(t.getMaxNum() == 1000);
    CHECK_THROWS_AS(t.setMinNum(1001), std::invalid_argument);
    CHECK(t.getMinNum() == 10);
}

TEST_CASE("Validar intervalos explícitos") {
    Tratamento t;
    CHECK_THROWS_AS(t.isNumeroValido(5, 10, 0), std::invalid_argument);
    CHECK_THROWS_AS(t.isStringValido("abc", 4, 2), std::invalid_argument);
    CHECK_THROWS_AS(t.validarQtdEX("abc", 4, 2), std::invalid_argument);
    CHECK(t.validarQtd("abc", 4, 2) == false);
}

TEST_CASE("Validar quantidade respeita limites inclusivos") {
    Tratamento t;
    CHECK(t.validarQtd("") == true);
    CHECK(t.validarQtdEX("") == true);

    CHECK(t.validarQtd("abc", 0, 3) == true);
    CHECK(t.validarQtdEX("abc", 0, 3) == true);

    CHECK(t.validarQtd("abc", 4, 3) == false);
    CHECK_THROWS_AS(t.validarQtdEX("abc", 4, 3), std::invalid_argument);
}