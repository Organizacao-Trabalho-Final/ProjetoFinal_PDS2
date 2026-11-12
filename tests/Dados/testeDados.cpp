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
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>
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

    static bool carregarInterno(Dados& d) {
        return d.carregarDadosInterno();
    }
};

struct TesteDados2{
    static void carregarEmprestimos(Dados& d, std::ifstream& in, Pessoa* p){
        d.carregarEmprestimos(in, p);
    }
};

struct TesteCatalogo {
    static int getProximoId(const Catalogo& c) {
        return c.getProximoId();
    }
};

class PessoaDesconhecidaDados : public Pessoa {
    public:
        PessoaDesconhecidaDados(const std::string &n, const std::string &c) : Pessoa(n, c) {}

        int getPrazo() const override {
            return 30;
        }
};

class DiretorioTemporario {
    private:
        std::string diretorioAnterior;
        std::string caminho;

    public:
        DiretorioTemporario() {
            char atual[4096];
            if (getcwd(atual, sizeof(atual)) == nullptr) {
                throw std::runtime_error("Não foi possível obter o diretório atual.");
            }
            diretorioAnterior = atual;

            char modelo[] = "/tmp/pds2-dados-XXXXXX";
            char *novo = mkdtemp(modelo);
            if (novo == nullptr) {
                throw std::runtime_error("Não foi possível criar diretório temporário.");
            }
            caminho = novo;

            if (chdir(caminho.c_str()) != 0) {
                rmdir(caminho.c_str());
                throw std::runtime_error("Não foi possível acessar diretório temporário.");
            }
        }

        ~DiretorioTemporario() {
            std::remove("usuario.txt");
            std::remove("obras.txt");
            std::remove("emprestimos.txt");
            rmdir("usuario.txt");
            rmdir("obras.txt");
            chdir(diretorioAnterior.c_str());
            rmdir(caminho.c_str());
        }
};

static void escreverArquivosDados(const std::string &obras, const std::string &usuarios) {
    std::ofstream outObras("obras.txt");
    outObras << obras;
    outObras.close();

    std::ofstream outUsuarios("usuario.txt");
    outUsuarios << usuarios;
    outUsuarios.close();
}

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
    std:: string cpf1 = "11122233396";

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

        std::string testa = "11;3;3;2008;17;4;2008;1;0;";
        CHECK(txt == testa);
        delete e1;

        SUBCASE("Empréstimo com renovação solicitada") {
            Professor p3(n1, cpf1, ar);
            Catalogo* ca1 = new Catalogo();
            Usuarios* us1 = new Usuarios();
            Dados da1(us1, ca1);

            std::vector<Emprestimo*> e;
            Emprestimo* e1 = new Emprestimo(A, p3, d1);
            REQUIRE(e1->solicitarRenovacao());
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

            CHECK(buffer.str() == "11;3;3;2008;17;4;2008;1;1;");
            le_arqv.close();
            std::remove(caminho.c_str());
            delete e1;
        }
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
    std:: string cpf1 = "11122233396";

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
            cria << "1;11;3;3;2008;17;4;2008;1;";
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
            cria << "3;11;3;3;2008;17;4;2008;1;0;12;3;3;2008;17;4;2008;1;0;13;3;3;2008;17;4;2008;1;0;";
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
            cria << "3;11;3;3;2008;17;4;2008;1;0;12;3;3;2008;17;4;2008;1;0;13;3;3;2008;17;4;2008;1;0;";
        }
        std::ifstream in(caminho);
        REQUIRE(in.is_open());
        TesteDados2::carregarEmprestimos(da1, in, &p3);

        CHECK(in.fail());
        in.clear();
    }

    SUBCASE("Caso valido com renovacao solicitada") {

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        Professor p3(n1, cpf1, ar);
        Livro* B = new Livro(t1, au1, id1, g1, ed1);
        
        REQUIRE(ca1->cadastrarObra(B));
        std::string caminho = "Caminho.txt";
        {
            std::ofstream cria(caminho);
            cria << "1;11;3;3;2008;17;4;2008;1;1;";
        }

        std::ifstream in(caminho);
        REQUIRE(in.is_open());
        TesteDados2::carregarEmprestimos(da1, in, &p3);
        REQUIRE_FALSE(in.fail());
        REQUIRE(p3.getEmprestimos().size() == 1);

        CHECK(p3.getEmprestimos()[0]->isAtivo());
        CHECK(p3.getEmprestimos()[0]->isRenovacaoSolicitada());

        in.close();
        std::remove(caminho.c_str());
    }
}

TEST_CASE("Dados - salvarDados"){

    std::string ar = "fisica";
    std::string t1 = "Confissoes";
    std::string au1 = "S.A";
    int id1 = 11;
    std::string g1 = "Romance";
    int ed1 = 21;
    Livro A(t1, au1, id1, g1, ed1);
    Data d1(3, 3, 2008);
    std::string n1 = "Wederley";
    std:: string cpf1 = "11122233396";
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

        std::string v = "ProximoId;" + std::to_string(TesteCatalogo::getProximoId(*ca1)) + "\n" + "Livro;Confissoes;S.A;11;1;0;Romance;21\n";
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

        std::string v = "ProximoId;" + std::to_string(TesteCatalogo::getProximoId(*ca1)) + "\n" + "Artigo;Confissoes;S.A;11;1;0;fisica;2008\n";
        CHECK(txt == v);
    }

    SUBCASE("Caso com obras nullptr"){

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        Professor p3(n1, cpf1, ar);

        Obra* orb = nullptr;

        ca1->cadastrarObra(orb);
        da1.salvarDados();

        std::ifstream in("obras.txt");
        std::stringstream buffer;
        buffer << in.rdbuf();
        const std::string ver = buffer.str();

        CHECK(ver == "ProximoId;" + std::to_string(TesteCatalogo::getProximoId(*ca1)) + "\n");
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
        std::cerr.rdbuf(original);

        std::ifstream in("obras.txt");
        std::stringstream buffer;
        buffer << in.rdbuf();
        const std::string ver = buffer.str();

        CHECK(ver == "ProximoId;12\n");
        CHECK(cap.str() == "Tipo de obra desconhecido. Não foi possível salvar os dados.\n");
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

        std::string v = "Professor;11;Wederley;11122233396;fisica;0;\n";

        CHECK(txt == v);
    }

    SUBCASE("Caso com estudante"){

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);
        std::string cu1 = "Matematica";
        std::string ma1 = "2026021111";
        Estudante* es1 = new Estudante(n1, cpf1, cu1, ma1);

        us1->adicionarUsuario(es1, id1);

        da1.salvarDados();

        std::string o = "usuario.txt";
        std::ifstream in(o);
        std::stringstream buffer;
        buffer << in.rdbuf();
        std::string txt = buffer.str();

        std::string v = "Estudante;11;Wederley;11122233396;Matematica;2026021111;0;\n";

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

        std::string v = "TecnicoManutencao;11;Wederley;11122233396;0;0;\n";

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

        std::string v = "Bibliotecario;11;Wederley;11122233396;0;\n";

        CHECK(txt == v);
    }
}

TEST_CASE("Dados - carregarDados"){

    std::string ar = "fisica";
    std::string t1 = "Confissoes";
    std::string au1 = "S.A";
    int id1 = 11;
    std::string g1 = "Romance";
    int ed1 = 21;
    Livro A(t1, au1, id1, g1, ed1);
    Data d1(3, 3, 2008);
    std::string n1 = "Wederley";
    std:: string cpf1 = "11122233396";

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

        auto obras = da1.getCatalogo()->listarObras();
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

        auto obras = da1.getCatalogo()->listarObras();
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

        auto obras = da1.getCatalogo()->listarObras();
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
            u << "Estudante;11;Wederley;11122233396;Matematica;2026021111;0;\n";
        }
        da1.carregarDados();

        Pessoa* p = da1.getUsuarios()->buscarUsuarioId(11);
        REQUIRE(p != nullptr);
        Estudante* e = dynamic_cast<Estudante*> (p);
        REQUIRE(e != nullptr);
        
        CHECK(e->getMatricula() == "2026021111");
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
            u << "Professor;11;Wederley;11122233396;fisica;0;\n";
        }
        da1.carregarDados();

        Pessoa* p = da1.getUsuarios()->buscarUsuarioId(11);
        REQUIRE(p != nullptr);
        Professor* e = dynamic_cast<Professor*> (p);
        REQUIRE(e != nullptr);
        
        CHECK(e->getCPF() == "11122233396");
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
            u << "Bibliotecario;11;Wederley;11122233396;0;\n";
        }
        da1.carregarDados();

        Pessoa* p = da1.getUsuarios()->buscarUsuarioId(11);
        REQUIRE(p != nullptr);
        Bibliotecario* e = dynamic_cast<Bibliotecario*> (p);
        REQUIRE(e != nullptr);
        
        CHECK(e->getCPF() == "11122233396");
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
            u << "TecnicoManutencao;11;Wederley;11122233396;0;0;\n";
        }
        da1.carregarDados();

        Pessoa* p = da1.getUsuarios()->buscarUsuarioId(11);
        REQUIRE(p != nullptr);
        TecnicoManutencao* e = dynamic_cast<TecnicoManutencao*> (p);
        REQUIRE(e != nullptr);
        
        CHECK(e->getCPF() == "11122233396");
    }

    SUBCASE("Caso com tecnico com uma manutencao"){

        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);

        {
            std::ofstream out("obras.txt");
            out << "Livro;Confissoes;S.A;11;1;0;Romance;21\n";
        }
        {
            std::ofstream u("usuario.txt");
            u << "TecnicoManutencao;11;Wederley;11122233396;0;1;\n11;11122233396;rasgo;costura;3;3;2008;1;";
        }
        da1.carregarDados();

        Pessoa* p = da1.getUsuarios()->buscarUsuarioId(11);
        REQUIRE(p != nullptr);
        TecnicoManutencao* e = dynamic_cast<TecnicoManutencao*> (p);
        REQUIRE(e != nullptr);

        REQUIRE(e->getManutencoes().size() == 1);
        REQUIRE(e->getManutencoes().size() == 1);

        Obra* obraCarregada = da1.getCatalogo()->buscarPorId(11);
        REQUIRE(obraCarregada != nullptr);
        CHECK(e->getManutencoes()[0]->getObra() == obraCarregada);
    }

    SUBCASE("Caso com CPF da manutencao diferente do tecnico") {
        
        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);

        {
            std::ofstream out("obras.txt");
            out << "Livro;Confissoes;S.A;11;1;0;Romance;21\n";
        }
        {
            std::ofstream u("usuario.txt");
            u << "TecnicoManutencao;11;Wederley;11122233396;0;1;\n"
            << "11;99999999999;rasgo;costura;3;3;2008;1;";
        }
        std::stringstream cap;
        std::streambuf* original = std::cerr.rdbuf(cap.rdbuf());

        da1.carregarDados();
        std::cerr.rdbuf(original);

        CHECK(cap.str().find("CPF da manutenção não corresponde ao técnico responsável.") != std::string::npos);
        CHECK(da1.getUsuarios()->buscarUsuarioId(11) == nullptr);
        CHECK(da1.getCatalogo()->buscarPorId(11) == nullptr);

        std::remove("obras.txt");
        std::remove("usuario.txt");
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
            u << "TecnicoManutencao;11;Wederley;11122233396;0;1;\n11;11122233396;rasgo;costura;3;3;2008;1;";
        }

        da1.getCatalogo()->cadastrarObra(nullptr);

        std::stringstream cap;
        std::streambuf* original = std::cerr.rdbuf(cap.rdbuf());
        da1.carregarDados();

        std::cerr.rdbuf(original);
        std::stringstream le;
        le << cap.rdbuf();
        std::string txt = le.str();

        CHECK(txt.find("Obra não encontrada ao carregar manutenção: 11\n") != std::string::npos);
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
            u << "TecnicoManutencao;11;Wederley;11122233396;0;1;\n11;11122233396;rasgo;costura;3;3;2008;99;";
        }

        std::stringstream cap;
        std::streambuf* original = std::cerr.rdbuf(cap.rdbuf());
        da1.carregarDados();

        std::cerr.rdbuf(original);
        std::stringstream le;
        le << cap.rdbuf();
        std::string txt = le.str();

        CHECK(txt.find("Erro ao ler uma manutenção do técnico.\n") != std::string::npos);

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
            u << "TecnicoManutencao;11;Wederley;11122233396;0;-6;\n11;11122233396;rasgo;costura;3;3;2008;1;";
        }

        std::stringstream cap;
        std::streambuf* original = std::cerr.rdbuf(cap.rdbuf());
        da1.carregarDados();

        std::cerr.rdbuf(original);
        std::stringstream le;
        le << cap.rdbuf();
        std::string txt = le.str();

        CHECK(txt.find("Quantidade de manutenções inválida.\n") != std::string::npos);

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
            u << "TecnicoManutencao;abc;Wederley;11122233396;0;1;\n11;11122233396;rasgo;costura;3;3;2008;1;";
        }

        std::stringstream cap;
        std::streambuf* original = std::cerr.rdbuf(cap.rdbuf());
        da1.carregarDados();

        std::cerr.rdbuf(original);
        std::stringstream le;
        le << cap.rdbuf();
        std::string txt = le.str();

        CHECK(txt.find("Erro ao ler os dados de um técnico de manutenção.\n") != std::string::npos);

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
            u << "Bibliotecario;abc;Wederley;11122233396;0;1;\n11;11122233396;rasgo;costura;3;3;2008;1;";
        }

        std::stringstream cap;
        std::streambuf* original = std::cerr.rdbuf(cap.rdbuf());
        da1.carregarDados();

        std::cerr.rdbuf(original);
        std::stringstream le;
        le << cap.rdbuf();
        std::string txt = le.str();

        CHECK(txt.find("Erro ao ler os dados de um bibliotecário.\n") != std::string::npos);

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
            u << "Professor;abc;Wederley;11122233396;0;1;\n11;11122233396;rasgo;costura;3;3;2008;1;";
        }

        std::stringstream cap;
        std::streambuf* original = std::cerr.rdbuf(cap.rdbuf());
        da1.carregarDados();

        std::cerr.rdbuf(original);
        std::stringstream le;
        le << cap.rdbuf();
        std::string txt = le.str();

        CHECK(txt.find("Erro ao ler os dados de um professor.\n") != std::string::npos);

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
            u << "Estudante;abc;Wederley;11122233396;0;1;\n11;11122233396;rasgo;costura;3;3;2008;1;";
        }

        std::stringstream cap;
        std::streambuf* original = std::cerr.rdbuf(cap.rdbuf());
        da1.carregarDados();

        std::cerr.rdbuf(original);
        std::stringstream le;
        le << cap.rdbuf();
        std::string txt = le.str();

        CHECK(txt.find("Erro ao ler os dados de um estudante.\n") != std::string::npos);

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

        CHECK(txt.find("Erro ao ler os dados de um livro.\n") != std::string::npos);

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

        CHECK(txt.find("Erro ao ler os dados de um artigo.\n") != std::string::npos);

        delete B;
    }

    SUBCASE("Preserva dados antigos quando o carregamento falha") {
        Catalogo* ca1 = new Catalogo();
        Usuarios* us1 = new Usuarios();
        Dados da1(us1, ca1);

        Livro* original = new Livro(
            "Calculo",
            "Stewart",
            50,
            "Didatico",
            1
        );
        REQUIRE(ca1->cadastrarObra(original));

        {
            std::ofstream out("obras.txt");
            out << "Livro;Confissoes;S.A;abc;1;0;Romance;21\n";
        }
        {
            std::ofstream out("usuario.txt");
        }

        da1.carregarDados();
        CHECK(da1.getCatalogo() == ca1);
        CHECK(da1.getUsuarios() == us1);
        CHECK(da1.getCatalogo()->buscarPorId(50) == original);

        std::remove("obras.txt");
        std::remove("usuario.txt");
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

    TecnicoManutencao *tecnico = new TecnicoManutencao("Carlos", "52998224725");
    usuarios->adicionarUsuario(tecnico, 1);

    Manutencao *m = new Manutencao(obra, tecnico, "Capa rasgada", Data(10, 11, 2026));

    tecnico->adicionarManutencao(m);
    m->iniciar();
    m->concluir();

    CHECK_FALSE(dados.removerObra(11));
    CHECK(catalogo->buscarPorId(11) == obra);
}

TEST_CASE("Dados - recupera proximo ID corretamente") {
    Catalogo* ca1 = new Catalogo();
    Usuarios* us1 = new Usuarios();
    Dados da1(us1, ca1);

    {
        std::ofstream out("obras.txt");

        out << "ProximoId;5\n";
        out << "Livro;Confissoes;S.A;10;1;0;Romance;21\n";
    }
    {
        std::ofstream out("usuario.txt");
    }
    da1.carregarDados();
    CHECK(TesteCatalogo::getProximoId(*da1.getCatalogo()) == 11);

    std::remove("obras.txt");
    std::remove("usuario.txt");
}

TEST_CASE("Dados - obra com emprestimo ativo fica indisponivel") {
    Catalogo* ca1 = new Catalogo();
    Usuarios* us1 = new Usuarios();
    Dados da1(us1, ca1);

    {
        std::ofstream out("obras.txt");

        out << "Livro;Confissoes;S.A;11;1;0;Romance;21\n";
    }
    {
        std::ofstream out("usuario.txt");

        out << "Professor;12;Wederley;11122233396;fisica;1;"
            << "11;3;3;2008;17;4;2008;1;0;\n";
    }
    da1.carregarDados();
    Obra* obra = da1.getCatalogo()->buscarPorId(11);
    REQUIRE(obra != nullptr);
    CHECK_FALSE(obra->isDisponivel());

    std::remove("obras.txt");
    std::remove("usuario.txt");
}

TEST_CASE("Dados - salvar manutenções e ignorar ponteiros nulos") {
    Catalogo *catalogo = new Catalogo();
    Usuarios *usuarios = new Usuarios();
    Dados dados(usuarios, catalogo);

    Livro *obra = new Livro("Cálculo", "Stewart", 71, "Didático", 1);
    REQUIRE(catalogo->cadastrarObra(obra));

    TecnicoManutencao *tecnico = new TecnicoManutencao("Carlos", "52998224725");
    REQUIRE(usuarios->adicionarUsuario(tecnico, 1));
    tecnico->adicionarManutencao(new Manutencao(obra, tecnico, "Capa rasgada", Data(10, 11, 2026)));

    std::vector<Obra*> &obras = const_cast<std::vector<Obra*>&>(catalogo->listarObras());
    obras.push_back(nullptr);
    std::vector<std::pair<Pessoa*, int> > &registros =
        const_cast<std::vector<std::pair<Pessoa*, int> >&>(usuarios->getUsuarios());
    registros.push_back(std::make_pair(static_cast<Pessoa*>(nullptr), 0));

    dados.salvarDados();

    std::ifstream in("usuario.txt");
    std::stringstream buffer;
    buffer << in.rdbuf();
    CHECK(buffer.str().find("TecnicoManutencao;1;Carlos;52998224725;0;1;71;52998224725;Capa rasgada;;10;11;2026;0;") != std::string::npos);
    in.close();
    
    std::remove("obras.txt");
    std::remove("usuario.txt");;
}

TEST_CASE("Dados - rejeita manutenção inconsistente ao salvar") {
    Catalogo *catalogo = new Catalogo();
    Usuarios *usuarios = new Usuarios();
    Dados dados(usuarios, catalogo);

    Livro *obra = new Livro("Cálculo", "Stewart", 72, "Didático", 1);
    REQUIRE(catalogo->cadastrarObra(obra));
    TecnicoManutencao *tecnico = new TecnicoManutencao("Carlos", "52998224725");
    REQUIRE(usuarios->adicionarUsuario(tecnico, 1));
    tecnico->adicionarManutencao(new Manutencao(obra, tecnico, "Capa", Data(10, 11, 2026)));

    std::vector<Manutencao*> &manutencoes =
        const_cast<std::vector<Manutencao*>&>(tecnico->getManutencoes());
    manutencoes.push_back(nullptr);

    std::stringstream cap;
    std::streambuf *original = std::cerr.rdbuf(cap.rdbuf());
    dados.salvarDados();
    std::cerr.rdbuf(original);

    CHECK(cap.str() == "Manutenção inconsistente. Não foi possível salvar os dados.\n");
    manutencoes.pop_back();
    
    std::remove("obras.txt");
    std::remove("usuario.txt");;
}

TEST_CASE("Dados - salvar tipo de usuário desconhecido") {
    Catalogo *catalogo = new Catalogo();
    Usuarios *usuarios = new Usuarios();
    Dados dados(usuarios, catalogo);
    REQUIRE(usuarios->adicionarUsuario(new PessoaDesconhecidaDados("Teste", "52998224725"), 1));

    std::stringstream cap;
    std::streambuf *original = std::cerr.rdbuf(cap.rdbuf());
    dados.salvarDados();
    std::cerr.rdbuf(original);

    CHECK(cap.str() == "Tipo de usuário desconhecido. Não foi possível salvar os dados.\n");
    
    std::remove("obras.txt");
    std::remove("usuario.txt");;
}

TEST_CASE("Dados - caminhos básicos de abertura e cabeçalho") {
    
    std::remove("obras.txt");
    std::remove("usuario.txt");;
    {
        Dados dados(new Usuarios(), new Catalogo());
        CHECK(dados.carregarDados());
    }

    escreverArquivosDados("ProximoId;0\n", "");
    {
        Dados dados(new Usuarios(), new Catalogo());
        CHECK_FALSE(dados.carregarDados());
    }

    escreverArquivosDados("ProximoId;1\n", "");
    std::remove("usuario.txt");
    {
        Dados dados(new Usuarios(), new Catalogo());
        CHECK_FALSE(dados.carregarDados());
    }

    std::remove("obras.txt");
    escreverArquivosDados("", "");
    std::remove("obras.txt");
    {
        Dados dados(new Usuarios(), new Catalogo());
        CHECK_FALSE(dados.carregarDados());
    }
    
    std::remove("obras.txt");
    std::remove("usuario.txt");;
}

TEST_CASE("Dados - rejeita tipos e identificadores inválidos de obras") {
    const std::string usuarioVazio = "";
    const std::vector<std::string> arquivos = {
        "Artigo;Artigo inválido;Autor;0;1;0;Física;2024\n",
        "Artigo;Primeiro;Autor;1;1;0;Física;2024\nArtigo;Duplicado;Autor;1;1;0;Física;2024\n",
        "Livro;Livro inválido;Autor;0;1;0;Didático;1\n",
        "Livro;Primeiro;Autor;1;1;0;Didático;1\nLivro;Duplicado;Autor;1;1;0;Didático;1\n",
        "ObraDesconhecida;Título;Autor;1;1;0;Tipo;1\n",
        "Livro;Último;Autor;2147483647;1;0;Didático;1\n"
    };

    for (const std::string &obras : arquivos) {
        escreverArquivosDados(obras, usuarioVazio);
        Dados dados(new Usuarios(), new Catalogo());
        CHECK_FALSE(dados.carregarDados());
        
    std::remove("obras.txt");
    std::remove("usuario.txt");;
    }
}

TEST_CASE("Dados - corrige próximo ID após carregar obras") {
    escreverArquivosDados("ProximoId;1\nLivro;Livro;Autor;10;1;0;Didático;1\n", "");
    Dados dados(new Usuarios(), new Catalogo());
    REQUIRE(dados.carregarDados());
    CHECK(TesteCatalogo::getProximoId(*dados.getCatalogo()) == 11);
    
    std::remove("obras.txt");
    std::remove("usuario.txt");;
}

TEST_CASE("Dados - rejeita tipos e registros inválidos de usuários") {
    const std::vector<std::string> usuariosInvalidos = {
        "OutroTipo;1;Ana;52998224725;\n",
        "Professor;1;Ana;52998224725",
        "TecnicoManutencao;1;Carlos;52998224725;"
    };

    for (const std::string &usuarios : usuariosInvalidos) {
        escreverArquivosDados("ProximoId;1\n", usuarios);
        Dados dados(new Usuarios(), new Catalogo());
        CHECK_FALSE(dados.carregarDados());
        
    std::remove("obras.txt");
    std::remove("usuario.txt");;
    }
}

TEST_CASE("Dados - rejeita usuários duplicados de cada categoria") {
    const std::vector<std::string> usuariosInvalidos = {
        "Estudante;1;Ana;52998224725;Engenharia;2026021111;0;\nEstudante;1;Bia;11122233396;Engenharia;2026022222;0;\n",
        "Professor;1;Ana;52998224725;Computação;0;\nProfessor;1;Bia;11122233396;Computação;0;\n",
        "Bibliotecario;1;Ana;52998224725;0;\nBibliotecario;1;Bia;11122233396;0;\n",
        "TecnicoManutencao;1;Ana;52998224725;0;0;\nTecnicoManutencao;1;Bia;11122233396;0;0;\n"
    };

    for (const std::string &usuarios : usuariosInvalidos) {
        escreverArquivosDados("ProximoId;1\n", usuarios);
        Dados dados(new Usuarios(), new Catalogo());
        CHECK_FALSE(dados.carregarDados());
        
    std::remove("obras.txt");
    std::remove("usuario.txt");;
    }
}

TEST_CASE("Dados - rejeita manutenção inválida após uma manutenção válida") {
    const std::string obras = "ProximoId;12\nLivro;Livro;Autor;11;1;0;Didático;1\n";
    const std::string cpf = "52998224725";
    const std::string manutencaoValida = "11;" + cpf + ";Capa rasgada;;10;11;2026;0;";
    const std::string manutencaoEstadoInvalido = "11;" + cpf + ";Dano;;10;11;2026;9;";
    const std::string manutencaoCpfInvalido = "11;11122233396;Dano;;10;11;2026;0;";
    const std::string manutencaoObraInvalida = "999;" + cpf + ";Dano;;10;11;2026;0;";

    const std::vector<std::string> usuariosInvalidos = {
        "TecnicoManutencao;1;Carlos;" + cpf + ";0;2;" + manutencaoValida + manutencaoEstadoInvalido + "\n",
        "TecnicoManutencao;1;Carlos;" + cpf + ";0;2;" + manutencaoValida + manutencaoCpfInvalido + "\n",
        "TecnicoManutencao;1;Carlos;" + cpf + ";0;2;" + manutencaoValida + manutencaoObraInvalida + "\n"
    };

    for (const std::string &usuarios : usuariosInvalidos) {
        escreverArquivosDados(obras, usuarios);
        Dados dados(new Usuarios(), new Catalogo());
        CHECK_FALSE(dados.carregarDados());
        
    std::remove("obras.txt");
    std::remove("usuario.txt");;
    }
}

TEST_CASE("Dados - valida consistência dos empréstimos carregados") {
    const std::string obraDisponivel = "ProximoId;2\nLivro;Livro;Autor;1;1;0;Didático;1\n";
    const std::string obraDanificada = "ProximoId;2\nLivro;Livro;Autor;1;0;1;Didático;1\n";
    const std::string cpf1 = "52998224725";
    const std::string cpf2 = "11122233396";
    const std::string emprestimoAtivo = "1;10;11;2026;10;12;2026;1;0;";
    const std::string emprestimoInativo = "1;10;11;2026;10;12;2026;0;0;";

    escreverArquivosDados(obraDisponivel, "Professor;1;Ana;" + cpf1 + ";Computação;1;" + emprestimoInativo + "\n");
    {
        Dados dados(new Usuarios(), new Catalogo());
        CHECK(dados.carregarDados());
    }
    
    std::remove("obras.txt");
    std::remove("usuario.txt");;

    escreverArquivosDados(obraDanificada, "Professor;1;Ana;" + cpf1 + ";Computação;1;" + emprestimoAtivo + "\n");
    {
        Dados dados(new Usuarios(), new Catalogo());
        CHECK_FALSE(dados.carregarDados());
    }
    
    std::remove("obras.txt");
    std::remove("usuario.txt");;

    escreverArquivosDados(obraDisponivel,
        "Professor;1;Ana;" + cpf1 + ";Computação;1;" + emprestimoAtivo + "\n"
        "Estudante;2;Bia;" + cpf2 + ";Engenharia;2026021111;1;" + emprestimoAtivo + "\n");
    {
        Dados dados(new Usuarios(), new Catalogo());
        CHECK_FALSE(dados.carregarDados());
    }
    
    std::remove("obras.txt");
    std::remove("usuario.txt");;
}

TEST_CASE("Dados - valida conflitos entre empréstimos e manutenções") {
    const std::string obras = "ProximoId;2\nLivro;Livro;Autor;1;1;0;Didático;1\n";
    const std::string cpf1 = "52998224725";
    const std::string cpf2 = "11122233396";
    const std::string emprestimo = "1;10;11;2026;10;12;2026;1;0;";
    const std::string manutencao = "1;" + cpf2 + ";Capa rasgada;;10;11;2026;0;";

    escreverArquivosDados(obras,
        "Professor;1;Ana;" + cpf1 + ";Computação;1;" + emprestimo + "\n"
        "TecnicoManutencao;2;Carlos;" + cpf2 + ";0;1;" + manutencao + "\n");
    {
        Dados dados(new Usuarios(), new Catalogo());
        CHECK_FALSE(dados.carregarDados());
    }
    
    std::remove("obras.txt");
    std::remove("usuario.txt");;

    const std::string manutencaoCpf1 = "1;" + cpf1 + ";Capa rasgada;;10;11;2026;0;";
    const std::string manutencaoCpf2 = "1;" + cpf2 + ";Capa rasgada;;10;11;2026;0;";
    escreverArquivosDados(obras,
        "TecnicoManutencao;1;Carlos;" + cpf1 + ";0;1;" + manutencaoCpf1 + "\n"
        "TecnicoManutencao;2;Paulo;" + cpf2 + ";0;1;" + manutencaoCpf2 + "\n");
    {
        Dados dados(new Usuarios(), new Catalogo());
        CHECK_FALSE(dados.carregarDados());
    }
    
    std::remove("obras.txt");
    std::remove("usuario.txt");;
}

TEST_CASE("Dados - remove obra com dados nulos ou ponteiros não inicializados") {
    {
        Dados dados(nullptr, new Catalogo());
        CHECK_FALSE(dados.removerObra(1));
    }
    {
        Dados dados(new Usuarios(), nullptr);
        CHECK_FALSE(dados.removerObra(1));
    }
    {
        Catalogo *catalogo = new Catalogo();
        Usuarios *usuarios = new Usuarios();
        Dados dados(usuarios, catalogo);
        REQUIRE(catalogo->cadastrarObra(new Livro("Livro", "Autor", 1, "Didático", 1)));

        std::vector<std::pair<Pessoa*, int> > &registros =
            const_cast<std::vector<std::pair<Pessoa*, int> >&>(usuarios->getUsuarios());
        registros.push_back(std::make_pair(static_cast<Pessoa*>(nullptr), 0));
        CHECK(dados.removerObra(1));
    }
    
    std::remove("obras.txt");
    std::remove("usuario.txt");;
}

TEST_CASE("Dados - rejeita ponteiros nulos e associações inconsistentes em memória") {
    SUBCASE("Usuário nulo") {
        Usuarios *usuarios = new Usuarios();
        std::vector<std::pair<Pessoa*, int> > &registros =
            const_cast<std::vector<std::pair<Pessoa*, int> >&>(usuarios->getUsuarios());
        registros.push_back(std::make_pair(static_cast<Pessoa*>(nullptr), 0));
        Dados dados(usuarios, new Catalogo());

        escreverArquivosDados("", "");
        CHECK_FALSE(TesteDados::carregarInterno(dados));
        
    std::remove("obras.txt");
    std::remove("usuario.txt");;
    }

    SUBCASE("Empréstimo nulo") {
        Usuarios *usuarios = new Usuarios();
        Professor *prof = new Professor("Ana", "52998224725", "Computação");
        REQUIRE(usuarios->adicionarUsuario(prof, 1));
        std::vector<Emprestimo*> &emprestimos =
            const_cast<std::vector<Emprestimo*>&>(prof->getEmprestimos());
        emprestimos.push_back(nullptr);
        Dados dados(usuarios, new Catalogo());

        escreverArquivosDados("", "");
        CHECK_FALSE(TesteDados::carregarInterno(dados));
        
    std::remove("obras.txt");
    std::remove("usuario.txt");;
    }

    SUBCASE("Manutenção associada a outro técnico") {
        TecnicoManutencao outro("Paulo", "11122233396");
        Catalogo *catalogo = new Catalogo();
        Usuarios *usuarios = new Usuarios();
        Livro *obra = new Livro("Livro", "Autor", 1, "Didático", 1);
        REQUIRE(catalogo->cadastrarObra(obra));
        TecnicoManutencao *tecnico = new TecnicoManutencao("Carlos", "52998224725");
        REQUIRE(usuarios->adicionarUsuario(tecnico, 1));

        std::vector<Manutencao*> &manutencoes =
            const_cast<std::vector<Manutencao*>&>(tecnico->getManutencoes());
        manutencoes.push_back(new Manutencao(obra, &outro, "Capa", Data(10, 11, 2026)));
        Dados dados(usuarios, catalogo);

        escreverArquivosDados("", "");
        CHECK_FALSE(TesteDados::carregarInterno(dados));
        
    std::remove("obras.txt");
    std::remove("usuario.txt");;
    }
}

TEST_CASE("Dados - rejeita renovação inválida e limpa empréstimos parciais") {
    Catalogo *catalogo = new Catalogo();
    Usuarios *usuarios = new Usuarios();
    Dados dados(usuarios, catalogo);
    REQUIRE(catalogo->cadastrarObra(new Livro("Livro", "Autor", 1, "Didático", 1)));
    Professor pessoa("Ana", "52998224725", "Computação");

    SUBCASE("Renovação solicitada em empréstimo inativo") {
        escreverArquivosDados("", "");
        std::ofstream out("emprestimos.txt");
        out << "1;1;10;11;2026;10;12;2026;0;1;";
        out.close();

        std::ifstream in("emprestimos.txt");
        REQUIRE(in.is_open());
        TesteDados2::carregarEmprestimos(dados, in, &pessoa);
        CHECK(in.fail());
        CHECK(pessoa.getEmprestimos().empty());
        in.close();
        std::remove("emprestimos.txt");
        
    std::remove("obras.txt");
    std::remove("usuario.txt");;
    }

    SUBCASE("Falha depois de carregar um empréstimo válido") {
        escreverArquivosDados("", "");
        std::ofstream out("emprestimos.txt");
        out << "2;1;10;11;2026;10;12;2026;1;0;999;10;11;2026;10;12;2026;1;0;";
        out.close();

        std::ifstream in("emprestimos.txt");
        REQUIRE(in.is_open());
        TesteDados2::carregarEmprestimos(dados, in, &pessoa);
        CHECK(in.fail());
        CHECK(pessoa.getEmprestimos().empty());
        in.close();
        std::remove("emprestimos.txt");
        
    std::remove("obras.txt");
    std::remove("usuario.txt");;
    }
}

TEST_CASE("Dados - cobre falha de leitura") {
    escreverArquivosDados("ProximoId;1\n", "Professor;1;Ana;52998224725;Computação;");
    Dados dados(new Usuarios(), new Catalogo());
    CHECK_FALSE(dados.carregarDados());
    
    std::remove("obras.txt");
    std::remove("usuario.txt");;
}

TEST_CASE("Dados - preserva o próximo ID e ignora manutenção concluída") {
    SUBCASE("Atualiza próximo ID a partir da maior obra") {
        escreverArquivosDados("ProximoId;1\nLivro;Livro;Autor;10;1;0;Didático;1\n", "");
        Dados dados(new Usuarios(), new Catalogo());
        REQUIRE(dados.carregarDados());
        CHECK(TesteCatalogo::getProximoId(*dados.getCatalogo()) == 11);
        
    std::remove("obras.txt");
    std::remove("usuario.txt");;
    }

    SUBCASE("Manutenção concluída não bloqueia a obra") {
        const std::string obras = "ProximoId;2\nLivro;Livro;Autor;1;1;0;Didático;1\n";
        const std::string usuarios =
            "TecnicoManutencao;1;Carlos;52998224725;0;1;1;52998224725;Capa rasgada;Capa restaurada;10;11;2026;2;\n";
        escreverArquivosDados(obras, usuarios);
        Dados dados(new Usuarios(), new Catalogo());
        REQUIRE(dados.carregarDados());
        CHECK(dados.getCatalogo()->buscarPorId(1)->isDisponivel());
        CHECK_FALSE(dados.getCatalogo()->buscarPorId(1)->isDanificado());
        
    std::remove("obras.txt");
    std::remove("usuario.txt");;
    }
}

TEST_CASE("Dados - trata falhas ao abrir arquivos durante o salvamento") {
    SUBCASE("Falha ao abrir usuario.txt") {
        DiretorioTemporario dir;
        REQUIRE(mkdir("usuario.txt", 0700) == 0);

        Dados dados(new Usuarios(), new Catalogo());
        std::ostringstream cap;
        std::streambuf *original = std::cerr.rdbuf(cap.rdbuf());
        dados.salvarDados();
        std::cerr.rdbuf(original);

        CHECK(cap.str() == "Erro ao abrir o arquivo para salvar os dados -> Usuarios.\n");
    }

    SUBCASE("Falha ao abrir obras.txt") {
        DiretorioTemporario dir;
        {
            std::ofstream usuario("usuario.txt");
            REQUIRE(usuario.is_open());
        }
        REQUIRE(mkdir("obras.txt", 0700) == 0);

        Dados dados(new Usuarios(), new Catalogo());
        std::ostringstream cap;
        std::streambuf *original = std::cerr.rdbuf(cap.rdbuf());
        dados.salvarDados();
        std::cerr.rdbuf(original);

        CHECK(cap.str() == "Erro ao abrir o arquivo para salvar os dados -> Obras.\n");
    }
}

TEST_CASE("Dados - detecta falha durante a gravação") {
    DiretorioTemporario dir;
    REQUIRE(symlink("/dev/full", "obras.txt") == 0);

    Catalogo *catalogo = new Catalogo();
    REQUIRE(catalogo->cadastrarObra(new Livro("Livro teste", "Autor", 1, "Didático", 1)));
    Dados dados(new Usuarios(), catalogo);

    std::ostringstream cap;
    std::streambuf *original = std::cerr.rdbuf(cap.rdbuf());
    dados.salvarDados();
    std::cerr.rdbuf(original);

    CHECK(cap.str() == "Erro durante a gravação dos arquivos de dados.\n");
}

TEST_CASE("Dados - rejeita empréstimo ativo de usuário não autorizado") {
    Catalogo *catalogo = new Catalogo();
    Usuarios *usuarios = new Usuarios();

    Livro *obra = new Livro("Livro", "Autor", 1, "Didático", 1);
    REQUIRE(catalogo->cadastrarObra(obra));

    PessoaDesconhecidaDados *pessoa = new PessoaDesconhecidaDados("Teste", "52998224725");
    REQUIRE(usuarios->adicionarUsuario(pessoa, 1));

    Emprestimo *e = new Emprestimo(*obra, *pessoa, Data(10, 11, 2026));
    pessoa->registrarEmprestimo(e);

    Dados dados(usuarios, catalogo);
    escreverArquivosDados("", "");

    CHECK_FALSE(TesteDados::carregarInterno(dados));

    std::remove("obras.txt");
    std::remove("usuario.txt");
}