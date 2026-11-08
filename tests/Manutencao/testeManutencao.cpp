#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../third_party/doctest.h"
#include "../../include/Manutencao.hpp"
#include "Livro.hpp"
#include "TecnicoManutencao.hpp"

bool operator==(const Data& a, const Data& b) {
    return a.getDia() == b.getDia() &&
           a.getMes() == b.getMes() &&
           a.getAno() == b.getAno();
}

TEST_CASE("Teste construtor e getters - Manutencao") {
    Livro l1("Dom Quixote", "Miguel de Cervantes", 1, "romanc", 3);
    TecnicoManutencao tm1("Nicolas", "01234567890");
    Data d1(10, 11, 2026);
    Manutencao m(&l1, &tm1, "Folha rasgada", d1);

    CHECK(m.getObra() == &l1);
    CHECK(m.getTecnico() == &tm1);
    CHECK(m.getDano() == "Folha rasgada");
    CHECK(m.getInicio() == d1);
    CHECK(m.getEstado() == EstadoManutencao::PENDENTE);

    SUBCASE("Teste setEstado e registrarReparo - Manutencao") {
        m.setEstado(EstadoManutencao::EM_ANDAMENTO);
        CHECK(m.getEstado() == EstadoManutencao::EM_ANDAMENTO);

        m.registrarReparo("Folha colada");
        CHECK(m.getReparo() == "Folha colada");
    }
}

TEST_CASE("Teste iniciar e concluir - Manutencao") {
    Livro l2("O Pequeno Príncipe", "Antoine de Saint-Exupéry", 2, "infantil", 1);
    TecnicoManutencao tm2("Max", "09876543210");
    Data d2(12, 11, 2026);
    Manutencao m2(&l2, &tm2, "Folha rasurada", d2);

    m2.iniciar();
    CHECK(m2.getEstado() == EstadoManutencao::EM_ANDAMENTO);
    CHECK(l2.isDisponivel() == false);
    m2.concluir();
    CHECK(m2.getEstado() == EstadoManutencao::CONCLUIDA);
    CHECK(l2.isDisponivel() == true);
    CHECK(l2.isDanificado() == false);

    SUBCASE("Ponteiro de obra nulo") {
        TecnicoManutencao tm3("Daniel", "12345678901");
        Data d3(13, 11, 2026);
        Manutencao m3(nullptr, &tm3, "Dano desconhecido", d3);

        m3.iniciar();
        CHECK(m3.getEstado() == EstadoManutencao::PENDENTE);
        m3.concluir();
        CHECK(m3.getEstado() == EstadoManutencao::PENDENTE);
    }

    SUBCASE("Iniciar e concluir com ordem inversa"){
        Livro l4("1984", "George Orwell", 3, "distopia", 1);
        TecnicoManutencao tm4("Santiago", "23456789012");
        Data d4(14, 11, 2026);
        Manutencao m4(&l4, &tm4, "Capa rasgada", d4);

        m4.concluir();
        CHECK(m4.getEstado() == EstadoManutencao::PENDENTE);
        CHECK(l4.isDisponivel() == true);
        CHECK(l4.isDanificado() == false);

        m4.iniciar();
        CHECK(m4.getEstado() == EstadoManutencao::EM_ANDAMENTO);
        CHECK(l4.isDisponivel() == false);

        m4.concluir();
        CHECK(m4.getEstado() == EstadoManutencao::CONCLUIDA);
        CHECK(l4.isDisponivel() == true);
        CHECK(l4.isDanificado() == false);

        m4.iniciar();
        CHECK(m4.getEstado() == EstadoManutencao::CONCLUIDA);
        CHECK(l4.isDisponivel() == true);
        CHECK(l4.isDanificado() == false);
    }
}

TEST_CASE("Teste destrutor - Manutencao") {
    Livro l5("O Senhor dos Anéis", "J.R.R. Tolkien", 4, "fantasia", 1);
    TecnicoManutencao tm5("Rezeck", "34567890123");
    Data d5(15, 11, 2026);
    {
        Manutencao m5(&l5, &tm5, "Capa rasgada", d5);
        CHECK(m5.getObra() == &l5);
        CHECK(m5.getTecnico() == &tm5);
    }
    CHECK(l5.getTitulo() == "O Senhor dos Anéis");
    CHECK(tm5.getNome() == "Rezeck");
}