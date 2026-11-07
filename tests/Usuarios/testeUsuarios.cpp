#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../third_party/doctest.h"
#include "../../include/Usuarios.hpp"
#include "../../include/Professor.hpp"
#include "../../include/Estudante.hpp"

TEST_CASE("Teste Construtor - Usuarios") {
    Usuarios u1;
    CHECK(u1.buscarUsuarioNome("Rezeck") == nullptr);
    CHECK(u1.buscarUsuarioId(1) == nullptr);
    CHECK(u1.buscarUsuarioCPF("01234567890") == nullptr);
}

TEST_CASE("Teste adicionarUsuario() e removerUsuario() - Usuarios") {
    Usuarios u2;
    Pessoa *p1 = new Professor("Rezeck", "01234567890", "DCC");
    u2.adicionarUsuario(p1, 1);

    CHECK(u2.buscarUsuarioNome("Rezeck") == p1);
    CHECK(u2.buscarUsuarioId(1) == p1);
    CHECK(u2.buscarUsuarioCPF("01234567890") == p1);
    CHECK(u2.buscarUsuarioNome("Paulo") == nullptr);
    CHECK(u2.buscarUsuarioId(2) == nullptr);
    CHECK(u2.buscarUsuarioCPF("01234567891") == nullptr);

    u2.adicionarUsuario(nullptr, 3);
    CHECK(u2.buscarUsuarioId(3) == nullptr);

    u2.adicionarUsuario(p1, 4);
    CHECK(u2.buscarUsuarioId(4) == nullptr);

    u2.removerUsuario("Rezeck");
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
        ClasseTeste() : Pessoa("Teste", "00000000000") {}
        ~ClasseTeste() { destruidas++; }
};

TEST_CASE("Teste destrutor - Usuarios") {
    destruidas = 0;
    {
        Usuarios u5;
        u5.adicionarUsuario(new ClasseTeste(), 1);
        u5.adicionarUsuario(new ClasseTeste(), 2);
        CHECK(destruidas == 0);
    }
    CHECK(destruidas == 2);
}