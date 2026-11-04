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
#include "Professor.hpp"

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
    std::string ar = "fisica";
    Professor p3(n1, cpf1, ar);
    std::string t1 = "Confissoes";
    std::string au1 = "S.A";
    int id1 = 11;
    std::string g1 = "Romance";
    int ed1 = 21;
    Livro A(t1, au1, id1, g1, ed1);
    Data d1(3, 3, 2008);
    Emprestimo* e1 = new Emprestimo(A, p3, d1);
    std::cout << "apos e1: " << p3.getNumEmprestimos() << "\n";
    Emprestimo* e2 = new Emprestimo(A, p3, d1);
    std::cout << "apos e2: " << p3.getNumEmprestimos() << "\n";
    Emprestimo* e3 = new Emprestimo(A, p3, d1);
    std::cout << "apos e2: " << p3.getNumEmprestimos() << "\n";
    Emprestimo* e4 = new Emprestimo(A, p3, d1);
    std::cout << "apos e2: " << p3.getNumEmprestimos() << "\n";
    std::vector<Emprestimo*> e = {e1, e2, e3};
    p3.setEmprestimos(e);
    std::cout << "apos set: " << p3.getNumEmprestimos() << "\n";
    SUBCASE("Caso com quantidade positiva de emprestimos"){
        CHECK(p3.getNumEmprestimos() == 3);
    }
}

TEST_CASE("Pessoa - getEmprestimosAtivos"){
    
    std::string ar = "fisica";
    std::string t1 = "Confissoes";
    std::string au1 = "S.A";
    int id1 = 11;
    std::string g1 = "Romance";
    int ed1 = 21;
    Livro A(t1, au1, id1, g1, ed1);
    Data d1(3, 3, 2008);

    Professor p1(n1, cpf1, ar);
    SUBCASE("vetor com ponteiro nulo"){
        std::vector<Emprestimo*> e;
        Emprestimo* e1 = nullptr;
        e.push_back(e1);
        p1.setEmprestimos(e);
        CHECK(p1.getEmprestimosAtivos() == 0);
    }

    SUBCASE("vetor de emprestimos nulo"){
        std::vector<Emprestimo*> e;
        p1.setEmprestimos(e);
        CHECK(p1.getEmprestimosAtivos() == 0);
    }

    SUBCASE("vetor com 3 emprestimos ativos"){
        std::vector<Emprestimo*> e;
        Emprestimo* e1 = new Emprestimo(A, p1, d1);
        Emprestimo* e2 = new Emprestimo(A, p1, d1);
        Emprestimo* e3 = new Emprestimo(A, p1, d1);
        e.push_back(e1);
        e.push_back(e2);
        e.push_back(e3);
        p1.setEmprestimos(e);
        CHECK(p1.getEmprestimosAtivos() == 3);
    }

    SUBCASE("Vetor com 2 emprestimos ativos e 1 desativo"){
        std::vector<Emprestimo*> e;
        Emprestimo* e1 = new Emprestimo(A, p1, d1);
        Emprestimo* e2 = new Emprestimo(A, p1, d1);
        Emprestimo* e3 = new Emprestimo(A, p1, d1);
        e.push_back(e1);
        e.push_back(e2);
        e.push_back(e3);
        e1->setAtivo(false);
        p1.setEmprestimos(e);
        CHECK(p1.getEmprestimosAtivos() == 2);
    }

    SUBCASE("Vetor com 2 emprestimos ativos, 1 desativo e um nullptr"){
        std::vector<Emprestimo*> e;
        Emprestimo* e1 = new Emprestimo(A, p1, d1);
        Emprestimo* e2 = new Emprestimo(A, p1, d1);
        Emprestimo* e3 = new Emprestimo(A, p1, d1);
        Emprestimo* e4 = nullptr;
        e.push_back(e1);
        e.push_back(e2);
        e.push_back(e3);
        e.push_back(e4);
        e1->setAtivo(false);
        p1.setEmprestimos(e);
        CHECK(p1.getEmprestimosAtivos() == 2);
    }
}

TEST_CASE("Pessoa - setEmprestimos"){

    std::string ar = "fisica";
    std::string t1 = "Confissoes";
    std::string au1 = "S.A";
    int id1 = 11;
    std::string g1 = "Romance";
    int ed1 = 21;
    Livro A(t1, au1, id1, g1, ed1);
    Data d1(3, 3, 2008);

    Professor p1(n1, cpf1, ar);

    SUBCASE("Inserindo emprestimos em uma pessoa sem emprestimos"){
        std::vector<Emprestimo*> e;
        Emprestimo* e1 = new Emprestimo(A, p1, d1);
        Emprestimo* e2 = new Emprestimo(A, p1, d1);
        Emprestimo* e3 = new Emprestimo(A, p1, d1);
        e.push_back(e1);
        e.push_back(e2);
        e.push_back(e3);
        p1.setEmprestimos(e);
        CHECK(p1.getEmprestimos() == e);
    }

    SUBCASE("Inserindo emprestimos em uma pessoa que ja possui emprestimos"){
        std::vector<Emprestimo*> e;
        Emprestimo* e1 = new Emprestimo(A, p1, d1);
        Emprestimo* e2 = new Emprestimo(A, p1, d1);
        Emprestimo* e3 = new Emprestimo(A, p1, d1);
        e.push_back(e1);
        e.push_back(e2);
        e.push_back(e3);
        p1.setEmprestimos(e);

        Emprestimo* e4 = new Emprestimo(A, p1, d1);
        Emprestimo* e5 = new Emprestimo(A, p1, d1);
        Emprestimo* e6 = new Emprestimo(A, p1, d1);
        Emprestimo* e7 = nullptr;
        std::vector<Emprestimo*> j;
        j.push_back(e4);
        j.push_back(e5);
        j.push_back(e6);
        j.push_back(e7);
        p1.setEmprestimos(j);
        j.erase(j.begin() + 3);

        CHECK(p1.getEmprestimos() == j);
    }

    SUBCASE("Inserindo emprestimos em uma pessoa sem emprestimos com vetor de nullptr"){
        Emprestimo* e4 = nullptr;
        Emprestimo* e5 = nullptr;
        Emprestimo* e6 = nullptr;
        Emprestimo* e7 = nullptr;
        std::vector<Emprestimo*> j;
        j.push_back(e4);
        j.push_back(e5);
        j.push_back(e6);
        j.push_back(e7);
        p1.setEmprestimos(j);

        j.erase(j.begin() + 3);
        j.erase(j.begin() + 2);
        j.erase(j.begin() + 1);
        j.erase(j.begin());

        CHECK(p1.getEmprestimos() == j);
    }

    SUBCASE("Inserindo um vetor nulo"){
        std::vector<Emprestimo*> j;
        p1.setEmprestimos(j);
        CHECK(p1.getEmprestimos() == j);
    }

    SUBCASE("Inserindo um vetor com elementos que o vetor ja possui"){
        std::vector<Emprestimo*> e;

        Emprestimo* e1 = new Emprestimo(A, p1, d1);
        Emprestimo* e2 = new Emprestimo(A, p1, d1);
        Emprestimo* e3 = new Emprestimo(A, p1, d1);
        e.push_back(e1);
        e.push_back(e2);
        e.push_back(e3);
        p1.setEmprestimos(e);

        Emprestimo* e4 = new Emprestimo(A, p1, d1);
        Emprestimo* e5 = new Emprestimo(A, p1, d1);
        Emprestimo* e6 = new Emprestimo(A, p1, d1);

        std::vector<Emprestimo*> j;
        j.push_back(e1);
        j.push_back(e4);
        j.push_back(e5);
        j.push_back(e6);
        p1.setEmprestimos(j);

        CHECK(p1.getEmprestimos() == j);
    }

    SUBCASE("Inerindo o mesmo vetor que a pessoa ja tinha"){
        std::vector<Emprestimo*> e;
        Emprestimo* e1 = new Emprestimo(A, p1, d1);
        Emprestimo* e2 = new Emprestimo(A, p1, d1);
        Emprestimo* e3 = new Emprestimo(A, p1, d1);
        e.push_back(e1);
        e.push_back(e2);
        e.push_back(e3);
        p1.setEmprestimos(e);

        std::vector<Emprestimo*> j;
        j.push_back(e1);
        j.push_back(e2);
        j.push_back(e3);
        p1.setEmprestimos(j);
        CHECK(p1.getEmprestimos() == j);
    }
}