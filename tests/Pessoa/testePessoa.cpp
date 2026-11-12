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
#include <sstream>

struct capturaCout {
    std::ostringstream saida;
    std::streambuf* original;

    capturaCout() : original(std::cout.rdbuf(saida.rdbuf())) {}
    ~capturaCout() { std::cout.rdbuf(original); }

    std::string str() const { return saida.str(); }
};

std::string n1 = "Wederley";
std:: string cpf1 = "11122233396";
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
    Emprestimo* e2 = new Emprestimo(A, p3, d1);
    Emprestimo* e3 = new Emprestimo(A, p3, d1);
    std::vector<Emprestimo*> e = {e1, e2, e3};
    p3.setEmprestimos(e);

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
    Professor p2(n1, cpf1, ar);
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

TEST_CASE("Pessoa - getEmprestimo"){
    
    std::string ar = "fisica";
    std::string t1 = "Confissoes";
    std::string au1 = "S.A";
    int id1 = 11;
    std::string g1 = "Romance";
    int ed1 = 21;
    Livro A(t1, au1, id1, g1, ed1);
    Data d1(3, 3, 2008);
    Professor p3(n1, cpf1, ar);

    SUBCASE("Pessoa com vetor de emprestimos vazio"){
        std::vector<Emprestimo*> e;
        p3.setEmprestimos(e);
        CHECK(p3.getEmprestimos() == e);
    }

    SUBCASE("testa se os objetos sao os mesmos (referencia) ou nao"){
        std::vector<Emprestimo*> e;
        Emprestimo* e1 = new Emprestimo(A, p3, d1);
        Emprestimo* e2 = new Emprestimo(A, p3, d1);
        e.push_back(e1);
        e.push_back(e2);
        //os dois emprestimos estao ativos
        p3.setEmprestimos(e);
        e1->setAtivo(false);
        CHECK(p3.getEmprestimos()[0]->isAtivo() == false);
    }
}

TEST_CASE("Pessoa - podeEmprestar"){

    std::string ar = "fisica";
    std::string t1 = "Confissoes";
    std::string au1 = "S.A";
    int id1 = 11;
    std::string g1 = "Romance";
    int ed1 = 21;
    Livro A(t1, au1, id1, g1, ed1);
    Data d1(3, 3, 2008);
    Professor p3(n1, cpf1, ar);

    SUBCASE("Caso valido - diferente de nullptr e obra disponivel"){
        CHECK(p3.podeEmprestar(&A) == true);
    }

    SUBCASE("Teste com obra nula"){
        Obra* o1 = nullptr;
        CHECK(p3.podeEmprestar(o1) == false);
    }

    SUBCASE("Teste com obra indisponivel"){
        A.setDisponivel(false);
        CHECK(p3.podeEmprestar(&A) == false);
    }
}

TEST_CASE("Pessoa - consultarAtivos"){

    std::string ar = "fisica";
    std::string t1 = "Confissoes";
    std::string au1 = "S.A";
    int id1 = 11;
    std::string g1 = "Romance";
    int ed1 = 21;
    Livro A(t1, au1, id1, g1, ed1);
    Data d1(3, 3, 2008);
    Professor p3(n1, cpf1, ar);

    SUBCASE("Emprestimos com 2 nullptr e 2 emprestimos ativos"){
        Emprestimo* e1 = nullptr;
        Emprestimo* e2 = nullptr;
        Emprestimo* e3 = new Emprestimo(A, p3, d1);
        Emprestimo* e4 = new Emprestimo(A, p3, d1);

        std::vector<Emprestimo*> e;
        e.push_back(e1);
        e.push_back(e2);
        e.push_back(e3);
        e.push_back(e4);
        p3.setEmprestimos(e);
        std::vector<Emprestimo*> j;
        j.push_back(e3);
        j.push_back(e4);

        CHECK(p3.consultarAtivos() == j);
        CHECK(p3.consultarAtivos().size() == 2);
    }

    SUBCASE("Emprestimo com 2 emprestimos ativos e 2 emprestimos desativos"){

        std::vector<Emprestimo*> e;
        Emprestimo* e1 = new Emprestimo(A, p3, d1);
        Emprestimo* e2 = new Emprestimo(A, p3, d1);
        Emprestimo* e3 = new Emprestimo(A, p3, d1);
        Emprestimo* e4 = new Emprestimo(A, p3, d1);
        e.push_back(e1);
        e.push_back(e2);
        e.push_back(e3);
        e.push_back(e4);
        p3.setEmprestimos(e);

        e3->setAtivo(false);
        e2->setAtivo(false);

        std::vector<Emprestimo*> j;
        j.push_back(e1);
        j.push_back(e4);

        CHECK(p3.consultarAtivos() == j);
        CHECK(p3.consultarAtivos().size() == 2);
    }

    SUBCASE("Caso valido - somente emprestimos ativos"){

        std::vector<Emprestimo*> e;
        Emprestimo* e3 = new Emprestimo(A, p3, d1);
        Emprestimo* e4 = new Emprestimo(A, p3, d1);
        e.push_back(e3);
        e.push_back(e4);
        p3.setEmprestimos(e);

        std::vector<Emprestimo*> j;
        j.push_back(e3);
        j.push_back(e4);

        CHECK(p3.consultarAtivos() == j);
    }

    SUBCASE("Pessoa sem emprestimos"){
        CHECK(p3.consultarAtivos().empty());
    }
}

TEST_CASE("historicoEmprestimos"){

    std::string ar = "fisica";
    std::string t1 = "Confissoes";
    std::string au1 = "S.A";
    int id1 = 11;
    std::string g1 = "Romance";
    int ed1 = 21;
    Livro A(t1, au1, id1, g1, ed1);
    Data d1(3, 3, 2008);
    Professor p3(n1, cpf1, ar);

    std::string moldura = "||======================================================||\n";

    SUBCASE("Caso valido com 1 emprestimo"){

        std::string pem;
        std::string obtido;

        Emprestimo* e1 = new Emprestimo(A, p3, d1);
        std::vector<Emprestimo*> e;
        e.push_back(e1);
        p3.setEmprestimos(e);

        {
            capturaCout cp;
            e1->printEmprestimo();
            pem = cp.str();
        }

        {
            capturaCout cp;
            p3.historicoEmprestimos();
            obtido = cp.str();
        }

        CHECK(obtido == moldura + pem + moldura);
    }

    SUBCASE("Caso em que nao tem emprestimos"){
        std::string pem;
        std::string obtido;
        std::string sub;

        std::vector<Emprestimo*> e;
        p3.setEmprestimos(e);

        {
            capturaCout cp;
            p3.historicoEmprestimos();
            obtido = cp.str();
        }

        CHECK(obtido == sub);
    }

    SUBCASE("Caso em que o vetor emprestimos tem elementos nullptr"){
        std::string pem;
        std::string obtido;
        std::string sub;

        Emprestimo* e2 = nullptr;
        std::vector<Emprestimo*> e;
        e.push_back(e2);
        p3.setEmprestimos(e);

        {
            capturaCout cp;
            p3.historicoEmprestimos();
            obtido = cp.str();
        }

        CHECK(obtido == sub);
    }

    SUBCASE("Caso com dois emprestimos"){
        std::string pem;
        std::string obtido;
        std::string pem2;

        Emprestimo* e1 = new Emprestimo(A, p3, d1);
        Emprestimo* e2 = new Emprestimo(A, p3, d1);
        std::vector<Emprestimo*> e;
        e.push_back(e1);
        e.push_back(e2);
        p3.setEmprestimos(e);

        {
            capturaCout cp;
            e1->printEmprestimo();
            pem = cp.str();
        }

        {
            capturaCout cp;
            e2->printEmprestimo();
            pem2 = cp.str();
        }

        {
            capturaCout cp;
            p3.historicoEmprestimos();
            obtido = cp.str();
        }

        CHECK(obtido == moldura + pem + moldura + moldura + pem2 + moldura);
    }
}

TEST_CASE("Pessoa - registrarEmprestimo"){
    
    std::string ar = "fisica";
    std::string t1 = "Confissoes";
    std::string au1 = "S.A";
    int id1 = 11;
    std::string g1 = "Romance";
    int ed1 = 21;
    Livro A(t1, au1, id1, g1, ed1);
    Data d1(3, 3, 2008);
    Professor p3(n1, cpf1, ar);

    SUBCASE("testa o lancamento de excecao"){
        CHECK_THROWS_AS(p3.registrarEmprestimo(nullptr), std::invalid_argument);
    }

    SUBCASE("caso onde a pessoa ja possui aquele emprestimo"){
        Emprestimo* e1 = new Emprestimo(A, p3, d1);
        std::vector<Emprestimo*> e;
        e.push_back(e1);
        p3.setEmprestimos(e);

        p3.registrarEmprestimo(e1);
        CHECK(p3.getEmprestimos() == e);
    }

    SUBCASE("Caso onde eh inserido um emprestimo novo"){
        Emprestimo* e1 = new Emprestimo(A, p3, d1);
        std::vector<Emprestimo*> e;
        e.push_back(e1);
        p3.registrarEmprestimo(e1);
        CHECK(p3.getEmprestimos() == e);
    }
}

TEST_CASE("Pessoa - validação do construtor") {

    CHECK_THROWS_AS(Pessoa("", "11122233396"), std::invalid_argument);
    CHECK_THROWS_AS(Pessoa("Maria", ""), std::invalid_argument);
    CHECK_NOTHROW(Pessoa("Maria", "11122233396"));
    CHECK_THROWS_AS(Pessoa("Maria", "12345678900"), std::invalid_argument);
    CHECK_THROWS_AS(Pessoa("   ", "12345678909"), std::invalid_argument);
    CHECK_NOTHROW(Pessoa("Maria", "12345678909"));
        
}

TEST_CASE("Pessoa - caminhos restantes") {
    Pessoa p("Pessoa base", "52998224725");
    Livro obra("Teste", "Autor", 50, "Didático", 1);

    CHECK(p.Pessoa::podeEmprestar(&obra));
    CHECK_FALSE(p.Pessoa::podeEmprestar(nullptr));
    obra.setDisponivel(false);
    CHECK_FALSE(p.Pessoa::podeEmprestar(&obra));

    std::vector<Emprestimo*> &emprestimos = const_cast<std::vector<Emprestimo*>&>(p.getEmprestimos());
    p.setEmprestimos(emprestimos);
    emprestimos.push_back(nullptr);

    {
        capturaCout cp;
        CHECK(p.historicoEmprestimos().size() == 1);
        CHECK(cp.str().empty());
    }

    emprestimos.clear();
    Pessoa *temporaria = new Pessoa("Temporaria", "11122233396");
    delete temporaria;
}