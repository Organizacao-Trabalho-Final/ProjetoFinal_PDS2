#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include "Dados.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <istream>
#include <utility>
#include <sstream>
#include <cstdio>
#include <stdexcept>
#include "Estudante.hpp"
#include "Emprestimo.hpp"
#include "Professor.hpp"
#include "Pessoa.hpp"
#include "Artigo.hpp"
#include "Livro.hpp"
#include "Data.hpp"
#include "Usuarios.hpp"
#include "Catalogo.hpp"
#include "Manutencao.hpp"
#include "TecnicoManutencao.hpp"
#include "Bibliotecario.hpp"

struct TesteDados {
    static void salvarEmprestimos(Dados& d, std::ofstream& out, const std::vector<Emprestimo*>& v) {
        d.salvarEmprestimos(out, v);
    }
};

TEST_CASE("Dados - getUsuario"){

    SUBCASE("versao nao const"){
        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        CHECK(da1.getUsuarios() == us1);
    }
    
    SUBCASE("versao const"){
        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        const Dados da1(us1, ca1);
        CHECK(da1.getUsuarios() == us1);
    }
}

TEST_CASE("Dados - getCatalogo"){
    SUBCASE("Versao nao const"){
        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        CHECK(da1.getCatalogo() == ca1);
    }

    SUBCASE("versao const"){
        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        const Dados da1(us1, ca1);
        CHECK(da1.getCatalogo() == ca1);
    }
}

TEST_CASE("Dados - salvarEmprestimos"){

    std::string ar = "fisica";
    std::string t1 = "Confissoes";
    std::string au1 = "S.A";
    int id1 = 11;
    std::string g1 = "Romance";
    int ed1 = 21;
    Livro A(t1, au1, id1, g1, ed1);
    Data d1(3, 3, 2008);
    std::string n1 = "Wederley";
    std:: string cpf1 = "11122233344";

    SUBCASE("Vetor de emprestimos vazio"){
        
        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        std::vector<Emprestimo*> e;

        std::string caminho = "salvaEm.txt";
        {
            std::ofstream escr_arqv(caminho);
            REQUIRE(escr_arqv.is_open());
            TesteDados::salvarEmprestimos(da1, escr_arqv, e);
        }
        
        std::ifstream le_arqv(caminho);
        REQUIRE(le_arqv.is_open());
        std::stringstream buffer;
        buffer << le_arqv.rdbuf();
        std::string txt = buffer.str();

        le_arqv.close();
        std::remove(caminho.c_str());

        CHECK(txt == "");
    }

    SUBCASE("Vetor de emprestimos com um elemento"){
        Professor p3(n1, cpf1, ar);
        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        std::vector<Emprestimo*> e;
        Emprestimo* e1 = new Emprestimo(A, p3, d1);
        e.push_back(e1);
        

        std::string caminho = "salvaEm.txt";
        {
            std::ofstream escr_arqv(caminho);
            REQUIRE(escr_arqv.is_open());
            TesteDados::salvarEmprestimos(da1, escr_arqv, e);
        }

        std::ifstream le_arqv(caminho);
        REQUIRE(le_arqv.is_open());
        std::stringstream buffer;
        buffer << le_arqv.rdbuf();
        std::string txt = buffer.str();

        le_arqv.close();
        std::remove(caminho.c_str());

        std::string testa = "11;3;3;2008;17;4;2008;1;";

        CHECK(txt == testa);
    }

    SUBCASE("vetor de emprestimos com elemento nullptr"){
        Emprestimo* e1 = nullptr;
        std::vector<Emprestimo*> e;
        e.push_back(e1);
        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);

        std::string caminho = "salvaEm.txt";
        std::ofstream escr_arqv(caminho); ////////////////////////
        


        CHECK_THROWS_AS(TesteDados::salvarEmprestimos(da1, escr_arqv, e), std::invalid_argument);

        escr_arqv.close();
        std::remove(caminho.c_str());
    }
}