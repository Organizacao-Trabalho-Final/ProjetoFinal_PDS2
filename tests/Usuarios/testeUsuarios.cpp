#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../third_party/doctest.h"
#include "../../include/Usuarios.hpp"
#include "../../include/Professor.hpp"
#include "../../include/Estudante.hpp"
#include "../../include/Livro.hpp"
#include "../../include/Emprestimo.hpp"
#include "../../include/TecnicoManutencao.hpp"
#include "../../include/Manutencao.hpp"
#include "../../include/Bibliotecario.hpp"
#include <limits>

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
    CHECK(u2.buscarUsuarioCPF("01234567970") == nullptr);

    CHECK_FALSE(u2.adicionarUsuario(nullptr, 3));
    CHECK(u2.buscarUsuarioId(3) == nullptr);

    CHECK_FALSE(u2.adicionarUsuario(p1, 4));
    CHECK(u2.buscarUsuarioId(4) == nullptr);

    Pessoa *cpfDuplicado = new Professor("Outro Professor", "01234567890", "DCC");
    CHECK_FALSE(u2.adicionarUsuario(cpfDuplicado, 2));
    CHECK(u2.buscarUsuarioId(2) == nullptr);
    delete cpfDuplicado;

    Pessoa *idDuplicado = new Professor("Outro Professor", "11122233396", "DCC");
    CHECK_FALSE(u2.adicionarUsuario(idDuplicado, 1));
    CHECK(u2.buscarUsuarioCPF("11122233396") == nullptr);
    delete idDuplicado;

    CHECK(u2.removerUsuarioNome("Rezeck"));
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

    Pessoa *p4 = new Estudante("João", "01234567970", "Engenharia de Controle e Automação", "2026012345");
    u4.adicionarUsuario(p4, 2);
    CHECK(u4.getOcupacao("01234567970") == "Estudante");
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
        CHECK(u5.adicionarUsuario(new ClasseTeste("Teste um", "11122233396"), 1));
        CHECK(u5.adicionarUsuario(new ClasseTeste("Teste dois", "01234567970"), 2));
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

    CHECK_FALSE(usuarios.removerUsuarioNome("Rezeck"));
    CHECK(usuarios.buscarUsuarioNome("Rezeck") == prof);
}

TEST_CASE("Impedir remoção de técnico com histórico de manutenções") {
    Livro obra("Calculo", "Stewart", 1, "Didatico", 1);
    Usuarios usuarios;
    TecnicoManutencao *tecnico = new TecnicoManutencao("Max", "12345678909");
    
    usuarios.adicionarUsuario(tecnico, 1);
    Manutencao *m = new Manutencao(&obra, tecnico, "Capa rasgada", Data(10, 11, 2026));
    tecnico->adicionarManutencao(m);

    CHECK_FALSE(usuarios.removerUsuarioNome("Max"));
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

    Pessoa *p2 = new Estudante("Santiago", "11122233396", "Engenharia", "2026012345");
    int id2 = usuarios.adicionarUsuario(p2);

    CHECK(id2 == 2);
    CHECK(usuarios.buscarUsuarioId(2) == p2);
}

TEST_CASE("Teste atualização do próximo ID - Usuarios") {
    Usuarios usuarios;
    Pessoa *p1 = new Professor("Rezeck", "01234567890", "DCC");

    CHECK(usuarios.adicionarUsuario(p1, 10));

    Pessoa *p2 = new Estudante("Daniel", "11122233396", "Engenharia", "2026012345");
    int id = usuarios.adicionarUsuario(p2);

    CHECK(id == 11);
    CHECK(usuarios.buscarUsuarioId(11) == p2);
}

TEST_CASE("Usuarios - rejeita IDs nao positivos") {
    Usuarios usuarios;
    Pessoa* idZero = new Professor("Zero", "12345678909", "DCC");
    CHECK_FALSE(usuarios.adicionarUsuario(idZero, 0));
    delete idZero;

    Pessoa* idNegativo = new Professor("Negativo", "11122233396", "DCC");
    CHECK_FALSE(usuarios.adicionarUsuario(idNegativo, -1));
    delete idNegativo;
    CHECK(usuarios.getUsuarios().empty());
}

TEST_CASE("Usuarios - interrompe geracao antes do limite de int") {
    Usuarios usuarios;
    const int limite = std::numeric_limits<int>::max();
    Pessoa* penultimo = new Professor("Penultimo", "01234567970", "DCC");
    REQUIRE(usuarios.adicionarUsuario(penultimo, limite - 1));

    Pessoa* excedente = new Professor("Excedente", "01234567970", "DCC");
    CHECK(usuarios.adicionarUsuario(excedente) == 0);
    delete excedente;
    CHECK(usuarios.buscarUsuarioId(limite - 1) == penultimo);
}

TEST_CASE("Usuarios - remover usuário pelo CPF") {
    Usuarios usuarios;
    Pessoa *p = new Professor("Paulo Rezeck", "52998224725", "Computação");

    REQUIRE(usuarios.adicionarUsuario(p) == 1);
    CHECK(usuarios.removerUsuarioCPF("52998224725"));
    CHECK(usuarios.getUsuarios().empty());
    CHECK(usuarios.buscarUsuarioCPF("52998224725") == nullptr);
}

TEST_CASE("Usuarios - ocupações restantes") {
    Usuarios usuarios;
    Pessoa *bibliotecario = new Bibliotecario("Ana", "52998224725");
    Pessoa *tecnico = new TecnicoManutencao("Carlos", "11122233396");
    Pessoa *desconhecido = new ClasseTeste("Pessoa teste", "01234567970");

    REQUIRE(usuarios.adicionarUsuario(bibliotecario, 1));
    REQUIRE(usuarios.adicionarUsuario(tecnico, 2));
    REQUIRE(usuarios.adicionarUsuario(desconhecido, 3));

    CHECK(usuarios.getOcupacao("52998224725") == "Bibliotecario");
    CHECK(usuarios.getOcupacao(0) == "Bibliotecario");
    CHECK(usuarios.getOcupacao("11122233396") == "TecnicoManutencao");
    CHECK(usuarios.getOcupacao(1) == "TecnicoManutencao");
    CHECK(usuarios.getOcupacao("01234567970") == "ERRO");
    CHECK(usuarios.getOcupacao(2) == "ERRO");
}

TEST_CASE("Usuarios - ignora registros nulos e buscas sem resultado") {
    Usuarios usuarios;
    std::vector<std::pair<Pessoa*, int> > &registros =
        const_cast<std::vector<std::pair<Pessoa*, int> >&>(usuarios.getUsuarios());
    registros.push_back(std::make_pair(static_cast<Pessoa*>(nullptr), 0));

    Pessoa *p = new Professor("Paulo", "52998224725", "Computação");
    REQUIRE(usuarios.adicionarUsuario(p, 1));

    CHECK(usuarios.getOcupacao(0) == "ERRO");
    CHECK_FALSE(usuarios.removerUsuarioNome("Inexistente"));
    CHECK_FALSE(usuarios.removerUsuarioCPF("11122233396"));
    CHECK(usuarios.removerUsuarioNome("Paulo"));
}

TEST_CASE("Usuarios - impede remover técnico com manutenção pelo CPF") {
    Usuarios usuarios;
    Livro obra("Cálculo", "Stewart", 40, "Didático", 1);
    TecnicoManutencao *tecnico = new TecnicoManutencao("Max", "52998224725");
    REQUIRE(usuarios.adicionarUsuario(tecnico, 1));

    tecnico->adicionarManutencao(new Manutencao(&obra, tecnico, "Capa rasgada", Data(10, 11, 2026)));
    CHECK_FALSE(usuarios.removerUsuarioCPF("52998224725"));
    CHECK(usuarios.buscarUsuarioCPF("52998224725") == tecnico);
}