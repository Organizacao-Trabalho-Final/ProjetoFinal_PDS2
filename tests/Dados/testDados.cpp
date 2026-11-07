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

struct TesteDados2{
    static void carregarEmprestimos(Dados& d, std::ifstream& in, Pessoa* p){
        d.carregarEmprestimos(in, p);
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

TEST_CASE("Dados - carregarEmprestimos"){

    std::string ar = "fisica";
    std::string t1 = "Confissoes";
    std::string au1 = "S.A";
    int id1 = 11;
    int id2 = 12;
    int id3 = 13;
    std::string g1 = "Romance";
    int ed1 = 21;
    Livro A(t1, au1, id1, g1, ed1);
    Data d1(3, 3, 2008);
    std::string n1 = "Wederley";
    std:: string cpf1 = "11122233344";

    SUBCASE("caso com usuarios nulo"){
        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = nullptr;
        Dados da1(us1, ca1);
        Professor p3(n1, cpf1, ar);

        std::string caminho = "Caminho.txt";
        {
            std::ofstream cria(caminho);
        }
        std::ifstream in(caminho);
        REQUIRE(in.is_open());
        TesteDados2::carregarEmprestimos(da1, in, &p3);

        CHECK(in.fail());
        in.clear();
    }

    SUBCASE("Caso com catalogo nulo"){
        Catalogo* ca1 = nullptr;
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        Professor p3(n1, cpf1, ar);

        std::string caminho = "Caminho.txt";
        {
            std::ofstream cria(caminho);
        }
        std::ifstream in(caminho);
        REQUIRE(in.is_open());
        TesteDados2::carregarEmprestimos(da1, in, &p3);

        CHECK(in.fail());
        in.clear();
    }

    SUBCASE("Caso com pessoa nula"){
        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        Professor* p3 = nullptr;

        std::string caminho = "Caminho.txt";
        {
            std::ofstream cria(caminho);
        }
        std::ifstream in(caminho);
        REQUIRE(in.is_open());
        TesteDados2::carregarEmprestimos(da1, in, p3);

        CHECK(in.fail());
        in.clear();
    }

    SUBCASE("Caso com numeroEmprestimos negativo"){
        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        Professor p3(n1, cpf1, ar);

        std::string caminho = "Caminho.txt";
        {
            std::ofstream cria(caminho);
            cria << "-5";
        }
        std::ifstream in(caminho);
        REQUIRE(in.is_open());
        TesteDados2::carregarEmprestimos(da1, in, &p3);

        CHECK(in.fail());
        in.clear();
    }

    SUBCASE("Caso com falha na leitura de in"){
        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        Professor p3(n1, cpf1, ar);

        std::string caminho = "Caminho.txt";
        {
            std::ofstream cria(caminho);    
        }
        std::ifstream in(caminho);
        REQUIRE(in.is_open());
        TesteDados2::carregarEmprestimos(da1, in, &p3);

        CHECK(in.fail());
        in.clear();
    }

    SUBCASE("Falha na leitura"){
        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        Professor p3(n1, cpf1, ar);
        std::vector<Emprestimo*> e;

        std::string caminho = "Caminho.txt";
        {
            std::ofstream cria(caminho);
            cria << "11;1;2;3;2026;";
        }
        std::ifstream in(caminho);
        REQUIRE(in.is_open());
        TesteDados2::carregarEmprestimos(da1, in, &p3);

        CHECK(in.fail());
        in.clear();
        CHECK(p3.getEmprestimos() == e);
    }

    SUBCASE("Caso valido"){

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        Professor p3(n1, cpf1, ar);
        std::vector<Emprestimo*> e;

        Livro* B = new Livro(t1, au1, id1, g1, ed1);
        Livro* C = new Livro(t1, au1, id2, g1, ed1);
        Livro* D = new Livro(t1, au1, id3, g1, ed1);

        ca1->cadastrarObra(B);
        ca1->cadastrarObra(C);
        ca1->cadastrarObra(D);

        std::string caminho = "Caminho.txt";
        {
            std::ofstream cria(caminho);
            cria << "3;11;3;3;2008;17;4;2008;1;12;3;3;2008;17;4;2008;1;13;3;3;2008;17;4;2008;1;";
        }
        std::ifstream in(caminho);
        REQUIRE(in.is_open());
        TesteDados2::carregarEmprestimos(da1, in, &p3);

        CHECK(p3.getEmprestimos()[0]->getObra().getID() == 11);
        CHECK(p3.getEmprestimos()[1]->getObra().getID() == 12);
        CHECK(p3.getEmprestimos()[2]->getObra().getID() == 13);
        in.clear();
    }

    SUBCASE("Caso com obra nula"){

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        Professor p3(n1, cpf1, ar);
        std::vector<Emprestimo*> e;

        Livro* B = nullptr;
        ca1->cadastrarObra(B);

        std::string caminho = "Caminho.txt";
        {
            std::ofstream cria(caminho);
            cria << "3;11;3;3;2008;17;4;2008;1;12;3;3;2008;17;4;2008;1;13;3;3;2008;17;4;2008;1;";
        }
        std::ifstream in(caminho);
        REQUIRE(in.is_open());
        TesteDados2::carregarEmprestimos(da1, in, &p3);

        CHECK(in.fail());
        in.clear();
    }
}

TEST_CASE("Dados - salvarDados"){

    std::string ar = "fisica";
    std::string t1 = "Confissoes";
    std::string au1 = "S.A";
    int id1 = 11;
    int id2 = 12;
    int id3 = 13;
    std::string g1 = "Romance";
    int ed1 = 21;
    Livro A(t1, au1, id1, g1, ed1);
    Data d1(3, 3, 2008);
    std::string n1 = "Wederley";
    std:: string cpf1 = "11122233344";
    int anop = 2008;

    SUBCASE("Caso com Usuarios nulo"){
        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = nullptr;
        Dados da1(us1, ca1);

        std::stringstream cap;
        std::streambuf* original = std::cerr.rdbuf(cap.rdbuf());

        da1.salvarDados();

        std::cerr.rdbuf(original);

        CHECK(cap.str() == "Não foi possível salvar os dados: usuários ou catálogo não inicializados.\n");
    }

    SUBCASE("Caso com Catalogo nulo"){

        Catalogo* ca1 = nullptr;
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);

        std::stringstream cap;
        std::streambuf* original = std::cerr.rdbuf(cap.rdbuf());

        da1.salvarDados();

        std::cerr.rdbuf(original);

        CHECK(cap.str() == "Não foi possível salvar os dados: usuários ou catálogo não inicializados.\n");
    }

    SUBCASE("Catalogo com livro"){

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        Professor p3(n1, cpf1, ar);

        Livro* B = new Livro(t1, au1, id1, g1, ed1);
        ca1->cadastrarObra(B);

        da1.salvarDados();

        std::string o = "obras.txt";
        std::ifstream in(o);
        std::stringstream buffer;
        buffer << in.rdbuf();
        std::string txt = buffer.str();

        std::string v = "Livro;Confissoes;S.A;11;1;0;Romance;21\n";

        CHECK(txt == v);
    }

    SUBCASE("Catalogo com artigo"){

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        Professor p3(n1, cpf1, ar);

        Artigo* B = new Artigo(t1, au1, id1, ar, anop);

        ca1->cadastrarObra(B);

        da1.salvarDados();

        std::string o = "obras.txt";
        std::ifstream in(o);
        std::stringstream buffer;
        buffer << in.rdbuf();
        std::string txt = buffer.str();

        std::string v = "Artigo;Confissoes;S.A;11;1;0;fisica;2008\n";

        CHECK(txt == v);
    }

    SUBCASE("Caso com obras nullptr"){

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        Professor p3(n1, cpf1, ar);

        Obra* orb = nullptr;

        ca1->cadastrarObra(orb);

        std::stringstream cap;
        std::streambuf* original = std::cerr.rdbuf(cap.rdbuf());

        da1.salvarDados();
        std::string ver = cap.str();

        std::cerr.rdbuf(original);

        CHECK(ver == "");
    }

    SUBCASE("Caso com obra desconhecida"){

        class obraDesconhecida : public Obra {
            public:
                obraDesconhecida(std::string t, std::string a, int idd)
                : Obra(t, a, idd) {}

                void printObra() const{
                    return;
                }
        };
        
        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        Professor p3(n1, cpf1, ar);

        Obra* orb = new obraDesconhecida(t1, au1, id1);

        ca1->cadastrarObra(orb);

        std::stringstream cap;
        std::streambuf* original = std::cerr.rdbuf(cap.rdbuf());

        da1.salvarDados();
        std::string ver = cap.str();

        std::cerr.rdbuf(original);

        CHECK(ver == "Tipo de obra desconhecido. Não foi possível salvar os dados.\n");
    }

    SUBCASE("Caso com Professor"){

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        Professor* p3 = new Professor(n1, cpf1, ar);

        us1->adicionarUsuario(p3, id1);

        da1.salvarDados();

        std::string o = "usuario.txt";
        std::ifstream in(o);
        std::stringstream buffer;
        buffer << in.rdbuf();
        std::string txt = buffer.str();

        std::string v = "Professor;11;Wederley;11122233344;fisica;0;\n";

        CHECK(txt == v);
    }

    SUBCASE("Caso com estudante"){

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        std::string cu1 = "Matematica";
        std::string ma1 = "1";
        Estudante* es1 = new Estudante(n1, cpf1, cu1, ma1);

        us1->adicionarUsuario(es1, id1);

        da1.salvarDados();

        std::string o = "usuario.txt";
        std::ifstream in(o);
        std::stringstream buffer;
        buffer << in.rdbuf();
        std::string txt = buffer.str();

        std::string v = "Estudante;11;Wederley;11122233344;Matematica;1;0;\n";

        CHECK(txt == v);
    }

    SUBCASE("Caso com TecnicoManutencao"){

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        TecnicoManutencao* te = new TecnicoManutencao(n1, cpf1);

        us1->adicionarUsuario(es1, id1);

        da1.salvarDados();

        std::string o = "usuario.txt";
        std::ifstream in(o);
        std::stringstream buffer;
        buffer << in.rdbuf();
        std::string txt = buffer.str();

        std::string v = "Estudante;11;Wederley;11122233344;Matematica;1;0;\n";

        CHECK(txt == v);
    }
}