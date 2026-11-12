#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>
#include "Livro.hpp"

TEST_CASE("Livro - construtor"){
    
    std::string t1 = "Confissoes";
    std::string ar = "fisica";
    std::string au1 = "S.A";
    std::string g1 = "teo";
    int ed1 = 21;
    int id1 = 11;

    SUBCASE("Caso de lancamento de excecao do construtor"){

        CHECK_THROWS_AS(Livro w(t1, au1, id1, g1, 0), std::invalid_argument);
        CHECK_THROWS_AS(Livro w(t1, au1, id1, g1, -1), std::invalid_argument);
        CHECK_THROWS_AS(Livro w(t1, au1, id1, "", ed1), std::invalid_argument);
    }

    SUBCASE("caso valido do construtor"){

        CHECK_NOTHROW(Livro w(t1, au1, id1, g1, 1));
    }
}

TEST_CASE("Livro - setEdicao"){

    std::string t1 = "Confissoes";
    std::string ar = "fisica";
    std::string au1 = "S.A";
    std::string g1 = "teo";
    int ed1 = 21;
    int id1 = 11;

    SUBCASE("Caso em que setEdicao lanca excecao"){
        Livro i(t1, au1, id1, g1, ed1);

        CHECK_THROWS_AS(i.setEdicao(0), std::invalid_argument);
        CHECK_THROWS_AS(i.setEdicao(-1), std::invalid_argument);
    }

    SUBCASE("Caso em que setEdicao nao lanca excecao"){
        Livro i(t1, au1, id1, g1, ed1);
        CHECK_NOTHROW(i.setEdicao(1));
        CHECK(i.getEdicao() == 1);
    }
}

TEST_CASE("Livro - setGenero"){

    std::string t1 = "Confissoes";
    std::string ar = "fisica";
    std::string au1 = "S.A";
    std::string g1 = "teo";
    int ed1 = 21;
    int id1 = 11;
    Livro i(t1, au1, id1, g1, ed1);

    i.setGenero("Ficcao");
    CHECK(i.getGenero() == "Ficcao");
    CHECK_THROWS_AS(i.setGenero(""), std::invalid_argument);
    CHECK(i.getGenero() == "Ficcao");
    CHECK_THROWS_AS(i.setGenero("   "), std::invalid_argument);

}

TEST_CASE("Livro - getGenero"){

    std::string t1 = "Confissoes";
    std::string ar = "fisica";
    std::string au1 = "S.A";
    std::string g1 = "teo";
    int ed1 = 21;
    int id1 = 11;
    Livro i(t1, au1, id1, g1, ed1);

    CHECK(i.getGenero() == g1);
}

TEST_CASE("Livro - getEdicao"){

    std::string t1 = "Confissoes";
    std::string ar = "fisica";
    std::string au1 = "S.A";
    std::string g1 = "teo";
    int ed1 = 21;
    int id1 = 11;
    Livro i(t1, au1, id1, g1, ed1);

    CHECK(i.getEdicao() == ed1);
}

TEST_CASE("Livro - printObra"){

    std::string t1 = "Confissoes";
    std::string ar = "fisica";
    std::string au1 = "S.A";
    std::string g1 = "teo";
    int ed1 = 21;
    int id1 = 11;
    Livro* a = new Livro(t1, au1, id1, g1, ed1);
    Livro* b = new Livro(t1, au1, id1, g1, ed1);
    b->setDisponivel(false);

    std::stringstream cap;
    std::streambuf* original = std::cout.rdbuf(cap.rdbuf());
    a->printObra();
    b->printObra();

    std::cout.rdbuf(original);
    std::stringstream buffer;
    buffer << cap.rdbuf();
    std::string txt = buffer.str();

    CHECK(txt == "Titulo: Confissoes\nAutor: S.A\nGenero: teo\nEdição: 21\nID: 11\nDisponibilidade: Disponível\nTitulo: Confissoes\nAutor: S.A\nGenero: teo\nEdição: 21\nID: 11\nDisponibilidade: Indisponível\n");

    delete b;
    delete a;
}