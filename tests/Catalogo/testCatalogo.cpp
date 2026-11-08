#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include <string>
#include <vector>
#include "Catalogo.hpp"
#include "Livro.hpp"

struct TesteCatalogo{
    static bool g(Catalogo &c, int id){
        return c.verificarDuplicata(id);
    }
};

TEST_CASE("Catalogo - verificarDuplicata"){

    std::string t1 = "Confissoes";
    std::string ar = "fisica";
    std::string au1 = "S.A";
    std::string g1 = "teo";
    int ed1 = 21;
    int id1 = 11;

        Livro* a = new Livro(t1, au1, id1, g1, ed1);
        Livro* b = new Livro(t1, au1, 12, g1, ed1);
        Livro* q = new Livro(t1, au1, id1, g1, ed1);
        Catalogo c;
        Catalogo s;
        Catalogo x;
        x.cadastrarObra(a);
        x.cadastrarObra(b);
        c.cadastrarObra(q);
        CHECK(TesteCatalogo::g(c, 11) == true);
        CHECK(TesteCatalogo::g(c, 2) == false);
        CHECK(TesteCatalogo::g(s, 5) == false);
        CHECK(TesteCatalogo::g(x, 12) == true);
        CHECK(TesteCatalogo::g(x, 6) == false);
}

TEST_CASE("Catalogo - cadastrarObra"){

    std::string t1 = "Confissoes";
    std::string ar = "fisica";
    std::string au1 = "S.A";
    std::string g1 = "teo";
    int ed1 = 21;
    int id1 = 11;
    Catalogo h;

    Livro* a = nullptr;
    Livro* b = new Livro(t1, au1, id1, g1, ed1);
    h.cadastrarObra(b);
    Livro* c = new Livro(t1, au1, 12, g1, ed1);

    CHECK(h.cadastrarObra(a) == false);
    CHECK(h.cadastrarObra(b) == false);
    CHECK(h.cadastrarObra(c) == true);
}

TEST_CASE("Catalogo - removerObra)"){

    std::string t1 = "Confissoes";
    std::string ar = "fisica";
    std::string au1 = "S.A";
    std::string g1 = "teo";
    int ed1 = 21;
    int id1 = 11;
    Catalogo h;

    Livro* a = new Livro(t1, au1, id1, g1, ed1);
    Livro* b = new Livro(t1, au1, 12, g1, ed1);
    h.cadastrarObra(a);
    h.cadastrarObra(b);
    CHECK(h.removerObra(11) == true);
    CHECK(h.removerObra(11) == false);
}

TEST_CASE("Catalogo - buscarPorTitulo"){

    std::string t1 = "Confissoes";
    std::string ar = "fisica";
    std::string au1 = "S.A";
    std::string g1 = "teo";
    int ed1 = 21;
    int id1 = 11;
    Catalogo h;

    Livro* a = new Livro(t1, au1, id1, g1, ed1);
    Livro* c = new Livro("s", au1, 13, g1, ed1);

    h.cadastrarObra(a);
    h.cadastrarObra(c);
    CHECK(h.buscarPorTitulo(t1) == a);
    CHECK(h.buscarPorTitulo("m") == nullptr);
    CHECK(h.buscarPorTitulo("s") == c);
}

TEST_CASE("Catalogo - buscarPorId"){

    std::string t1 = "Confissoes";
    std::string ar = "fisica";
    std::string au1 = "S.A";
    std::string g1 = "teo";
    int ed1 = 21;
    int id1 = 11;
    Catalogo h;

    Livro* a = new Livro(t1, au1, id1, g1, ed1);
    Livro* c = new Livro("s", au1, 13, g1, ed1);

    h.cadastrarObra(a);
    h.cadastrarObra(c);
    CHECK(h.buscarPorId(id1) == a);
    CHECK(h.buscarPorId(23) == nullptr);
    CHECK(h.buscarPorId(13) == c);
}

TEST_CASE("Catalogo - BuscarPorAutor"){

    std::string t1 = "Confissoes";
    std::string ar = "fisica";
    std::string au1 = "S.A";
    std::string g1 = "teo";
    int ed1 = 21;
    int id1 = 11;
    Catalogo h;

    Livro* a = new Livro(t1, au1, id1, g1, ed1);
    Livro* c = new Livro("s", au1, 13, g1, ed1);
    Livro* b = new Livro(t1, "vf", 14, g1, ed1);
    std::vector<Obra*> e;
    e.push_back(a);
    e.push_back(c);
    std::vector<Obra*> ws;

    h.cadastrarObra(a);
    h.cadastrarObra(c);
    h.cadastrarObra(b);

    CHECK(h.buscarPorAutor(au1) == e);
    CHECK(h.buscarPorAutor("ss") == ws);
}

TEST_CASE("Catalogo - listarObras"){

    std::string t1 = "Confissoes";
    std::string ar = "fisica";
    std::string au1 = "S.A";
    std::string g1 = "teo";
    int ed1 = 21;
    int id1 = 11;
    Catalogo h;
    Catalogo mn;
    Catalogo y;
    Catalogo lk;

    Livro* a = new Livro(t1, au1, id1, g1, ed1);
    Livro* c = new Livro("s", au1, 13, g1, ed1);
    Livro* z = new Livro(t1, "vf", 14, g1, ed1);
    Livro* x = new Livro(t1, "vf", 15, g1, ed1);
    Livro* s = new Livro(t1, "vf", 16, g1, ed1);
    Livro* as = new Livro(t1, "vf", 14, g1, ed1);
    std::vector<Obra*> e;
    e.push_back(a);
    e.push_back(c);
    std::vector<Obra*> ws;

    h.cadastrarObra(a);
    h.cadastrarObra(c);

    mn.cadastrarObra(z);
    mn.cadastrarObra(x);
    mn.cadastrarObra(s);
    std::vector<Obra*> cd;
    cd.push_back(z);
    cd.push_back(x);
    cd.push_back(s);

    std::vector<Obra*> l;
    l.push_back(as);

    lk.cadastrarObra(as);

    CHECK(h.listarObras() == e);
    CHECK(mn.listarObras() == cd);
    CHECK(y.listarObras() == ws);
    CHECK(lk.listarObras() == l);
}