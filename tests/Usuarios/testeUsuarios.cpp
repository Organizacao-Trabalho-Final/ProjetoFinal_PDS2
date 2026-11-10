#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../third_party/doctest.h"
#include "../../include/Usuarios.hpp"
#include "../../include/Professor.hpp"
#include "../../include/Estudante.hpp"
#include "../../include/Livro.hpp"
#include "../../include/Emprestimo.hpp"
#include "../../include/TecnicoManutencao.hpp"
#include "../../include/Manutencao.hpp"

TEST_CASE("Teste Construtor - Usuarios") {
    Usuarios u1;
    CHECK(u1.buscarUsuarioNome("Rezeck") == nullptr);
    CHECK(u1.buscarUsuarioId(1) == nullptr);
    CHECK(u1.buscarUsuarioCPF("01234567890") == nullptr);
}

TEST_CASE("Teste adicionarUsuario() e removerUsuario() - Usuarios") {
    Usuarios u2;
    Pessoa *p1 = new Professor("Rezeck", "01234567890", "DCC");
    CHECK(u2.adicionarUsuario(p1, 1));

    CHECK(u2.buscarUsuarioNome("Rezeck") == p1);
    CHECK(u2.buscarUsuarioId(1) == p1);
    CHECK(u2.buscarUsuarioCPF("01234567890") == p1);
    CHECK(u2.buscarUsuarioNome("Paulo") == nullptr);
    CHECK(u2.buscarUsuarioId(2) == nullptr);
    CHECK(u2.buscarUsuarioCPF("01234567891") == nullptr);

    CHECK_FALSE(u2.adicionarUsuario(nullptr, 3));
    CHECK(u2.buscarUsuarioId(3) == nullptr);

    CHECK_FALSE(u2.adicionarUsuario(p1, 4));
    CHECK(u2.buscarUsuarioId(4) == nullptr);

    Pessoa *cpfDuplicado = new Professor("Outro Professor", "01234567890", "DCC");
    CHECK_FALSE(u2.adicionarUsuario(cpfDuplicado, 2));
    CHECK(u2.buscarUsuarioId(2) == nullptr);
    delete cpfDuplicado;

    Pessoa *idDuplicado = new Professor("Outro Professor", "11122233344", "DCC");
    CHECK_FALSE(u2.adicionarUsuario(idDuplicado, 1));
    CHECK(u2.buscarUsuarioCPF("11122233344") == nullptr);
    delete idDuplicado;

    CHECK(u2.removerUsuario("Rezeck"));
    CHECK(u2.buscarUsuarioNome("Rezeck") == nullptr);
}

TEST_CASE("Teste buscarUsuarioIndex() - Usuarios") {
    Usuarios u3;
    Pessoa *p2 = new Professor("Rezeck", "01234567890", "DCC");
    u3.adicionarUsuario(p2, 1);
    std::pair<Pessoa*, int> usuario = u3.buscarUsuarioIndex(0);

    CHECK(usuario.first == p2);
    CHECK(usuario.second == 1);
    CHECK(u3.buscarUsuarioIndex(0) == std::make_pair(p2, 1));
    CHECK(u3.buscarUsuarioIndex(-1) == std::make_pair(static_cast<Pessoa*>(nullptr), -1));
    CHECK(u3.buscarUsuarioIndex(1) == std::make_pair(static_cast<Pessoa*>(nullptr), -1));
}

TEST_CASE("Teste getOcupacao() - Usuarios") {
    Usuarios u4;
    Pessoa *p3 = new Professor("Rezeck", "01234567890", "DCC");
    u4.adicionarUsuario(p3, 1);

    CHECK(u4.getOcupacao("01234567890") == "Professor");
    CHECK(u4.getOcupacao(0) == "Professor");

    Pessoa *p4 = new Estudante("João", "01234567891", "Engenharia de Controle e Automação", "2026012345");
    u4.adicionarUsuario(p4, 2);
    CHECK(u4.getOcupacao("01234567891") == "Estudante");
    CHECK(u4.getOcupacao(1) == "Estudante");

    CHECK(u4.getOcupacao("01234567892") == "ERRO");
    CHECK(u4.getOcupacao(2) == "ERRO -> Index Inválido"); 
}

static int destruidas = 0;
class ClasseTeste : public Pessoa {
    public:
        ClasseTeste(const std::string &nome, const std::string &cpf)
            : Pessoa(nome, cpf) {}

        ~ClasseTeste() {
            destruidas++;
        }
};

TEST_CASE("Teste destrutor - Usuarios") {
    destruidas = 0;
    {
        Usuarios u5;
        CHECK(u5.adicionarUsuario(new ClasseTeste("Teste 1", "00000000001"), 1));
        CHECK(u5.adicionarUsuario(new ClasseTeste("Teste 2", "00000000002"), 2));
        CHECK(destruidas == 0);
    }
    CHECK(destruidas == 2);
}

TEST_CASE("Impedir remoção de usuário com histórico de empréstimos") {
    Livro obra("Calculo", "Stewart", 1, "Didatico", 1);
    Usuarios usuarios;
    Professor *prof = new Professor("Rezeck", "01234567890", "DCC");

    usuarios.adicionarUsuario(prof, 1);
    Emprestimo *e = new Emprestimo(obra, *prof, Data(10, 11, 2026));
    e->setAtivo(false);
    prof->registrarEmprestimo(e);

    CHECK_FALSE(usuarios.removerUsuario("Rezeck"));
    CHECK(usuarios.buscarUsuarioNome("Rezeck") == prof);
}

TEST_CASE("Impedir remoção de técnico com histórico de manutenções") {
    Livro obra("Calculo", "Stewart", 1, "Didatico", 1);
    Usuarios usuarios;
    TecnicoManutencao *tecnico = new TecnicoManutencao("Max", "12345678901");
    
    usuarios.adicionarUsuario(tecnico, 1);
    Manutencao *m = new Manutencao(&obra, tecnico, "Capa rasgada", Data(10, 11, 2026));
    tecnico->adicionarManutencao(m);

    CHECK_FALSE(usuarios.removerUsuario("Max"));
    CHECK(usuarios.buscarUsuarioNome("Max") == tecnico);
}

TEST_CASE("Teste geração automática de IDs - Usuarios") {
    Usuarios usuarios;
    Pessoa *p1 = new Professor("Rezeck", "01234567890", "DCC");
    int id1 = usuarios.adicionarUsuario(p1);

    CHECK(id1 == 1);
    CHECK(usuarios.buscarUsuarioId(1) == p1);

    Pessoa *duplicado = new Professor("Outro professor", "01234567890", "DCC");
    CHECK(usuarios.adicionarUsuario(duplicado) == 0);
    delete duplicado;

    Pessoa *p2 = new Estudante("Santiago", "11122233344", "Engenharia", "2026012345");
    int id2 = usuarios.adicionarUsuario(p2);

    CHECK(id2 == 2);
    CHECK(usuarios.buscarUsuarioId(2) == p2);
}

TEST_CASE("Teste atualização do próximo ID - Usuarios") {
    Usuarios usuarios;
    Pessoa *p1 = new Professor("Rezeck", "01234567890", "DCC");

    CHECK(usuarios.adicionarUsuario(p1, 10));

    Pessoa *p2 = new Estudante("Daniel", "11122233344", "Engenharia", "2026012345");
    int id = usuarios.adicionarUsuario(p2);

    CHECK(id == 11);
    CHECK(usuarios.buscarUsuarioId(11) == p2);
}