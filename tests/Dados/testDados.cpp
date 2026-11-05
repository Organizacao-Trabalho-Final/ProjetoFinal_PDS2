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
        
    }
}