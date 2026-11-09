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
        std::ofstream escr_arqv(caminho);

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
        TecnicoManutencao* te1 = new TecnicoManutencao(n1, cpf1);

        us1->adicionarUsuario(te1, id1);

        da1.salvarDados();

        std::string o = "usuario.txt";
        std::ifstream in(o);
        std::stringstream buffer;
        buffer << in.rdbuf();
        std::string txt = buffer.str();

        std::string v = "TecnicoManutencao;11;Wederley;11122233344;0;0;\n";

        CHECK(txt == v);
    }

    SUBCASE("Caso com Bibliotecario"){

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        Bibliotecario* bi1 = new Bibliotecario(n1, cpf1);

        us1->adicionarUsuario(bi1, id1);

        da1.salvarDados();

        std::string o = "usuario.txt";
        std::ifstream in(o);
        std::stringstream buffer;
        buffer << in.rdbuf();
        std::string txt = buffer.str();

        std::string v = "Bibliotecario;11;Wederley;11122233344;0;\n";

        CHECK(txt == v);
    }
}

TEST_CASE("Dados - carregarDados"){

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

    SUBCASE("Caso para artigo valido"){
        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);

        {
            std::ofstream out("obras.txt");
            out << "Artigo;Confissoes;S.A;11;1;0;fisica;2008\n";
        }
        {
            std::ofstream u("usuario.txt");
        }
        da1.carregarDados();

        auto obras = ca1->listarObras();
        REQUIRE(obras.size() == 1);
        Artigo* a = dynamic_cast<Artigo*>(obras[0]);
        REQUIRE(a != nullptr);

        CHECK(a->getTitulo() == "Confissoes");
        CHECK(a->getAutor() == "S.A");
        CHECK(a->getID() == 11);
    }

    SUBCASE("Caso para Livro valido"){

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);

        {
            std::ofstream out("obras.txt");
            out << "Livro;Confissoes;S.A;11;1;0;Romance;21\n";
        }
        {
            std::ofstream u("usuario.txt");
        }
        da1.carregarDados();

        auto obras = ca1->listarObras();
        REQUIRE(obras.size() == 1);
        Livro* a = dynamic_cast<Livro*>(obras[0]);
        REQUIRE(a != nullptr);

        CHECK(a->getTitulo() == "Confissoes");
        CHECK(a->getAutor() == "S.A");
        CHECK(a->getID() == 11);
    }

    SUBCASE("Caso para 2 livros validos"){

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);

        {
            std::ofstream out("obras.txt");
            out << "Livro;Confissoes;S.A;11;1;0;Romance;21\n" << "Livro;Confissoes;S.A;12;1;0;Romance;21\n";
        }
        {
            std::ofstream u("usuario.txt");
        }
        da1.carregarDados();

        auto obras = ca1->listarObras();
        REQUIRE(obras.size() == 2);
        Livro* a = dynamic_cast<Livro*>(obras[0]);
        Livro* b = dynamic_cast<Livro*>(obras[1]);
        REQUIRE(a != nullptr);
        REQUIRE(b != nullptr);

        CHECK(a->getTitulo() == "Confissoes");
        CHECK(a->getAutor() == "S.A");
        CHECK(a->getID() == 11);

        CHECK(b->getTitulo() == "Confissoes");
        CHECK(b->getAutor() == "S.A");
        CHECK(b->getID() == 12);
    }

    SUBCASE("Caso para um estudante valido"){

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);

        {
            std::ofstream out("obras.txt");
        }
        {
            std::ofstream u("usuario.txt");
            u << "Estudante;11;Wederley;11122233344;Matematica;1;0;\n";
        }
        da1.carregarDados();

        Pessoa* p = us1->buscarUsuarioId(11);
        REQUIRE(p != nullptr);
        Estudante* e = dynamic_cast<Estudante*> (p);
        REQUIRE(e != nullptr);
        
        CHECK(e->getMatricula() == "1");
    }

    SUBCASE("Caso para um professor valido"){

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);

        {
            std::ofstream out("obras.txt");
        }
        {
            std::ofstream u("usuario.txt");
            u << "Professor;11;Wederley;11122233344;fisica;0;\n";
        }
        da1.carregarDados();

        Pessoa* p = us1->buscarUsuarioId(11);
        REQUIRE(p != nullptr);
        Professor* e = dynamic_cast<Professor*> (p);
        REQUIRE(e != nullptr);
        
        CHECK(e->getCPF() == "11122233344");
    }

    SUBCASE("Caso para Bibliotecario valido"){

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);

        {
            std::ofstream out("obras.txt");
        }
        {
            std::ofstream u("usuario.txt");
            u << "Bibliotecario;11;Wederley;11122233344;0;\n";
        }
        da1.carregarDados();

        Pessoa* p = us1->buscarUsuarioId(11);
        REQUIRE(p != nullptr);
        Bibliotecario* e = dynamic_cast<Bibliotecario*> (p);
        REQUIRE(e != nullptr);
        
        CHECK(e->getCPF() == "11122233344");
    }

    SUBCASE("Caso para TecnicoManutencao valido"){
        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);

        {
            std::ofstream out("obras.txt");
        }
        {
            std::ofstream u("usuario.txt");
            u << "TecnicoManutencao;11;Wederley;11122233344;0;0;\n";
        }
        da1.carregarDados();

        Pessoa* p = us1->buscarUsuarioId(11);
        REQUIRE(p != nullptr);
        TecnicoManutencao* e = dynamic_cast<TecnicoManutencao*> (p);
        REQUIRE(e != nullptr);
        
        CHECK(e->getCPF() == "11122233344");
    }

    SUBCASE("Caso com tecnico com uma manutencao"){

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        Livro* B = new Livro(t1, au1, id1, g1, ed1);

        {
            std::ofstream out("obras.txt");
            out << "Livro;Confissoes;S.A;11;1;0;Romance;21\n";
        }
        {
            std::ofstream u("usuario.txt");
            u << "TecnicoManutencao;11;Wederley;11122233344;0;1;\n11;11122233344;rasgo;costura;3;3;2008;1;";
        }
        da1.carregarDados();

        Pessoa* p = us1->buscarUsuarioId(11);
        REQUIRE(p != nullptr);
        TecnicoManutencao* e = dynamic_cast<TecnicoManutencao*> (p);
        REQUIRE(e != nullptr);

        Manutencao* mn = new Manutencao(B, e, "rasgo", d1);

        REQUIRE(e->getManutencoes().size() == 1);
        CHECK(e->getManutencoes()[0]->getObra()->getID() == B->getID());

        delete B;
    }

    SUBCASE("Caso com tecnico com uma manutencao de uma obra nullptr"){

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);

        {
            std::ofstream out("obras.txt");
        }
        {
            std::ofstream u("usuario.txt");
            u << "TecnicoManutencao;11;Wederley;11122233344;0;1;\n11;11122233344;rasgo;costura;3;3;2008;1;";
        }

        da1.getCatalogo()->cadastrarObra(nullptr);

        std::stringstream cap;
        std::streambuf* original = std::cerr.rdbuf(cap.rdbuf());
        da1.carregarDados();

        std::cerr.rdbuf(original);
        std::stringstream le;
        le << cap.rdbuf();
        std::string txt = le.str();

        CHECK(txt == "Obra não encontrada ao carregar manutenção: 11\n");
    }

    SUBCASE("Caso com estado de manutencao invalida"){

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        Livro* B = new Livro(t1, au1, id1, g1, ed1);

        {
            std::ofstream out("obras.txt");
            out << "Livro;Confissoes;S.A;11;1;0;Romance;21\n";
        }
        {
            std::ofstream u("usuario.txt");
            u << "TecnicoManutencao;11;Wederley;11122233344;0;1;\n11;11122233344;rasgo;costura;3;3;2008;99;";
        }

        std::stringstream cap;
        std::streambuf* original = std::cerr.rdbuf(cap.rdbuf());
        da1.carregarDados();

        std::cerr.rdbuf(original);
        std::stringstream le;
        le << cap.rdbuf();
        std::string txt = le.str();

        CHECK(txt == "Erro ao ler uma manutenção do técnico.\n");

        delete B;
    }

    SUBCASE("Caso para quantidade de manutencoes invalida"){

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        Livro* B = new Livro(t1, au1, id1, g1, ed1);

        {
            std::ofstream out("obras.txt");
            out << "Livro;Confissoes;S.A;11;1;0;Romance;21\n";
        }
        {
            std::ofstream u("usuario.txt");
            u << "TecnicoManutencao;11;Wederley;11122233344;0;-6;\n11;11122233344;rasgo;costura;3;3;2008;1;";
        }

        std::stringstream cap;
        std::streambuf* original = std::cerr.rdbuf(cap.rdbuf());
        da1.carregarDados();

        std::cerr.rdbuf(original);
        std::stringstream le;
        le << cap.rdbuf();
        std::string txt = le.str();

        CHECK(txt == "Quantidade de manutenções inválida.\n");

        delete B;
    }

    SUBCASE("Caso com dados do tecnico invalidos"){

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        Livro* B = new Livro(t1, au1, id1, g1, ed1);

        {
            std::ofstream out("obras.txt");
            out << "Livro;Confissoes;S.A;11;1;0;Romance;21\n";
        }
        {
            std::ofstream u("usuario.txt");
            u << "TecnicoManutencao;abc;Wederley;11122233344;0;1;\n11;11122233344;rasgo;costura;3;3;2008;1;";
        }

        std::stringstream cap;
        std::streambuf* original = std::cerr.rdbuf(cap.rdbuf());
        da1.carregarDados();

        std::cerr.rdbuf(original);
        std::stringstream le;
        le << cap.rdbuf();
        std::string txt = le.str();

        CHECK(txt == "Erro ao ler os dados de um técnico de manutenção.\n");

        delete B;
    }

    SUBCASE("Caso com Bibliotecario invalido"){

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        Livro* B = new Livro(t1, au1, id1, g1, ed1);

        {
            std::ofstream out("obras.txt");
            out << "Livro;Confissoes;S.A;11;1;0;Romance;21\n";
        }
        {
            std::ofstream u("usuario.txt");
            u << "Bibliotecario;abc;Wederley;11122233344;0;1;\n11;11122233344;rasgo;costura;3;3;2008;1;";
        }

        std::stringstream cap;
        std::streambuf* original = std::cerr.rdbuf(cap.rdbuf());
        da1.carregarDados();

        std::cerr.rdbuf(original);
        std::stringstream le;
        le << cap.rdbuf();
        std::string txt = le.str();

        CHECK(txt == "Erro ao ler os dados de um bibliotecário.\n");

        delete B;
    }

    SUBCASE("Caso com Professor invalido"){

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        Livro* B = new Livro(t1, au1, id1, g1, ed1);

        {
            std::ofstream out("obras.txt");
            out << "Livro;Confissoes;S.A;11;1;0;Romance;21\n";
        }
        {
            std::ofstream u("usuario.txt");
            u << "Professor;abc;Wederley;11122233344;0;1;\n11;11122233344;rasgo;costura;3;3;2008;1;";
        }

        std::stringstream cap;
        std::streambuf* original = std::cerr.rdbuf(cap.rdbuf());
        da1.carregarDados();

        std::cerr.rdbuf(original);
        std::stringstream le;
        le << cap.rdbuf();
        std::string txt = le.str();

        CHECK(txt == "Erro ao ler os dados de um professor.\n");

        delete B;
    }

    SUBCASE("Caso com Estudante invalido"){

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        Livro* B = new Livro(t1, au1, id1, g1, ed1);

        {
            std::ofstream out("obras.txt");
            out << "Livro;Confissoes;S.A;11;1;0;Romance;21\n";
        }
        {
            std::ofstream u("usuario.txt");
            u << "Estudante;abc;Wederley;11122233344;0;1;\n11;11122233344;rasgo;costura;3;3;2008;1;";
        }

        std::stringstream cap;
        std::streambuf* original = std::cerr.rdbuf(cap.rdbuf());
        da1.carregarDados();

        std::cerr.rdbuf(original);
        std::stringstream le;
        le << cap.rdbuf();
        std::string txt = le.str();

        CHECK(txt == "Erro ao ler os dados de um estudante.\n");

        delete B;
    }

    SUBCASE("Caso com Livro invalido"){

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        Livro* B = new Livro(t1, au1, id1, g1, ed1);

        {
            std::ofstream out("obras.txt");
            out << "Livro;Confissoes;S.A;abc;1;0;Romance;21\n";
        }
        {
            std::ofstream u("usuario.txt");
        }

        std::stringstream cap;
        std::streambuf* original = std::cerr.rdbuf(cap.rdbuf());
        da1.carregarDados();

        std::cerr.rdbuf(original);
        std::stringstream le;
        le << cap.rdbuf();
        std::string txt = le.str();

        CHECK(txt == "Erro ao ler os dados de um livro.\n");

        delete B;
    }

    SUBCASE("Caso com Artigo invalido"){

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        Livro* B = new Livro(t1, au1, id1, g1, ed1);

        {
            std::ofstream out("obras.txt");
            out << "Artigo;Confissoes;S.A;abc;1;0;Romance;21\n";
        }
        {
            std::ofstream u("usuario.txt");
        }

        std::stringstream cap;
        std::streambuf* original = std::cerr.rdbuf(cap.rdbuf());
        da1.carregarDados();

        std::cerr.rdbuf(original);
        std::stringstream le;
        le << cap.rdbuf();
        std::string txt = le.str();

        CHECK(txt == "Erro ao ler os dados de um artigo.\n");

        delete B;
    }
}

TEST_CASE("Remover obra sem vínculos") {
    Catalogo *catalogo = new Catalogo();
    Usuarios *usuarios = new Usuarios();
    Dados dados(usuarios, catalogo);

    Livro *obra = new Livro("Calculo", "Stewart", 11, "Didatico", 1);
    REQUIRE(catalogo->cadastrarObra(obra));

    CHECK(dados.removerObra(11));
    CHECK(catalogo->buscarPorId(11) == nullptr);
    CHECK_FALSE(dados.removerObra(11));
}

TEST_CASE("Impedir remoção de obra com empréstimo") {
    Catalogo *catalogo = new Catalogo();
    Usuarios *usuarios = new Usuarios();
    Dados dados(usuarios, catalogo);

    Livro *obra = new Livro("Calculo", "Stewart", 11, "Didatico", 1);
    REQUIRE(catalogo->cadastrarObra(obra));

    Professor *professor = new Professor("Rezeck", "01234567890", "DCC");
    usuarios->adicionarUsuario(professor, 1);

    Emprestimo *e = new Emprestimo(*obra, *professor, Data(10, 11, 2026));
    e->setAtivo(false);
    professor->registrarEmprestimo(e);

    CHECK_FALSE(dados.removerObra(11));
    CHECK(catalogo->buscarPorId(11) == obra);
}

TEST_CASE("Impedir remoção de obra com manutenção") {
    Catalogo *catalogo = new Catalogo();
    Usuarios *usuarios = new Usuarios();
    Dados dados(usuarios, catalogo);

    Livro *obra = new Livro("Calculo", "Stewart", 11, "Didatico", 1);
    REQUIRE(catalogo->cadastrarObra(obra));

    TecnicoManutencao *tecnico = new TecnicoManutencao("Carlos", "12345678901");
    usuarios->adicionarUsuario(tecnico, 1);

    Manutencao *m = new Manutencao(obra, tecnico, "Capa rasgada", Data(10, 11, 2026));

    m->setEstado(EstadoManutencao::CONCLUIDA);
    tecnico->adicionarManutencao(m);

    CHECK_FALSE(dados.removerObra(11));
    CHECK(catalogo->buscarPorId(11) == obra);
}