#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include <string>
#include "Artigo.hpp"
#include <stdexcept>
#include <iostream>
#include <sstream>

TEST_CASE("Artigo - construtor"){

    SUBCASE("Caso de lancamento de excecao do construtor"){

        std::string t1 = "Confissoes";
        std::string ar = "fisica";
        std::string au1 = "S.A";
        int id1 = 11;
        int an = 2026;

        CHECK_THROWS_AS(Artigo(t1, au1, id1, ar, 0), std::invalid_argument);
        CHECK_THROWS_AS(Artigo(t1, au1, id1, ar, 10000), std::invalid_argument);
    }

    SUBCASE("Caso valido do construtor"){

        std::string t1 = "Confissoes";
        std::string ar = "fisica";
        std::string au1 = "S.A";
        int id1 = 11;
        int an = 2026;

        CHECK_NOTHROW(Artigo(t1, au1, id1, ar, an));

        Artigo* a = new Artigo(t1, au1, id1, ar, an);

        CHECK_NOTHROW(Artigo(t1, au1, id1, ar, 1));
        CHECK_NOTHROW(Artigo(t1, au1, id1, ar, 9999));

        CHECK(a->getTitulo() == t1);
        CHECK(a->getAutor() == au1);
        CHECK(a->getArea() == ar);
        CHECK(a->getAno() == an);
        CHECK(a->getID() == id1);

        delete a;
    }
}

TEST_CASE("Artigo - setAno"){
    
    SUBCASE("Caso valido de setAno"){

        std::string t1 = "Confissoes";
        std::string ar = "fisica";
        std::string au1 = "S.A";
        int id1 = 11;
        int an = 2026;

        Artigo* a = new Artigo(t1, au1, id1, ar, an);

        a->setAno(199);
        CHECK(a->getAno() == 199);

        delete a;
    }

    SUBCASE("setAno lanca excecao"){

        std::string t1 = "Confissoes";
        std::string ar = "fisica";
        std::string au1 = "S.A";
        int id1 = 11;
        int an = 2026;

        Artigo* a = new Artigo(t1, au1, id1, ar, an);
        CHECK_NOTHROW(a->setAno(9999));
        CHECK_NOTHROW(a->setAno(1));
        CHECK_THROWS_AS(a->setAno(10000), std::invalid_argument);
        CHECK_THROWS_AS(a->setAno(0), std::invalid_argument);

        delete a;
    }
}

TEST_CASE("Artigo - setArea"){

    std::string t1 = "Confissoes";
    std::string ar = "fisica";
    std::string au1 = "S.A";
    int id1 = 11;
    int an = 2026;
    Artigo* a = new Artigo(t1, au1, id1, ar, an);

    a->setArea("ingles");

    CHECK(a->getArea() == "ingles");

    delete a;
}

TEST_CASE("Artigo - getAno"){

    std::string t1 = "Confissoes";
    std::string ar = "fisica";
    std::string au1 = "S.A";
    int id1 = 11;
    int an = 2026;
    Artigo* a = new Artigo(t1, au1, id1, ar, an);

    CHECK(a->getAno() == 2026);

    delete a;
}

TEST_CASE("Artigo - getArea"){

    std::string t1 = "Confissoes";
    std::string ar = "fisica";
    std::string au1 = "S.A";
    int id1 = 11;
    int an = 2026;
    Artigo* a = new Artigo(t1, au1, id1, ar, an);

    CHECK(a->getArea() == "fisica");

    delete a;
}

TEST_CASE("Artigo - printObra"){

    std::string t1 = "Confissoes";
    std::string ar = "fisica";
    std::string au1 = "S.A";
    int id1 = 11;
    int an = 2026;
    Artigo* a = new Artigo(t1, au1, id1, ar, an);

    std::stringstream cap;
    std::streambuf* original = std::cout.rdbuf(cap.rdbuf());
    a->printObra();

    std::cout.rdbuf(original);
    std::stringstream buffer;
    buffer << cap.rdbuf();
    std::string txt = buffer.str();

    CHECK(txt == "Titulo: Confissoes\nAutor: S.A\nArea: fisica\nAno: 2026\nID: 11\nDisponivel: Sim\n");

    delete a;
}