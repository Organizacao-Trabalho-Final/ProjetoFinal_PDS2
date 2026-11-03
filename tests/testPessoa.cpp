#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include "Obra.hpp"
#include "Pessoa.hpp"
#include "Emprestimo.hpp"
#include "Livro.hpp"

std::string n1 = "Wederley";
std:: string cpf1 = "11122233344";
Pessoa p1(n1, cpf1);
TEST_CASE("Teste Pessoa - getNome"){
    CHECK(p1.getNome() == n1);
}

TEST_CASE("Teste Pessoa - getCPF"){
    CHECK(p1.getCPF() == cpf1);
}

TEST_CASE("Teste Pessoa - getPrazo"){
    CHECK(p1.getPrazo() == 0);
}

TEST_CASE("Teste Pessoa - getMaxEmprestimos"){
    CHECK(p1.getMaxEmprestimos() == 0);
}

TEST_CASE("Teste Pessoa - getNumEmprestimos"){
    Pessoa p2(n1, cpf1);
    SUBCASE("Caso com zero emprestimos"){
        CHECK(p2.getNumEmprestimos() == 0);
    }
    Pessoa p3(n1, cpf1);
    std::string t1 = "Confissoes";
    std::string au1 = "S.A";
    int id1 = 11;
    std::string g1 = "Romance";
    int ed1 = 21;
    Livro A(t1, au1, id1, g1, ed1);
    Data d1(3, 3, 2008);
    Emprestimo e1(A, p3, d1);
    Emprestimo e2(A, p3, d1);
    std::vector<Emprestimo*> e = {&e1, &e2};
    p3.setEmprestimos(e);
    SUBCASE("Caso com quantidade positiva de emprestimos"){
        CHECK(p3.getNumEmprestimos() == 2);
    }
}