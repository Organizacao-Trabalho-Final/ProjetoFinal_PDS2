#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../third_party/doctest.h"
#include "../../include/TecnicoManutencao.hpp"
#include "Manutencao.hpp"
#include "Livro.hpp"
#include "Data.hpp"

TEST_CASE("Teste Construtor - TecnicoManutencao") {
    TecnicoManutencao t1("José", "01234567890");
    CHECK(t1.getNome() == "José");
    CHECK(t1.getCPF() == "01234567890");
    CHECK(t1.getManutencoes().empty());
}

TEST_CASE("Teste adicionarManutencao - TecnicoManutencao") {
    TecnicoManutencao t2("José", "01234567890");
    Livro l1("Cálculo", "Stewart", 1, "Didático", 1);
    Livro l2("Um Curso de Cálculo", "Guidorizzi", 2, "Didático", 1);
    Manutencao *m1 = new Manutencao(&l1, &t2, "Capa rasgada", Data(10, 11, 2026));
    Manutencao *m2 = new Manutencao(&l2, &t2, "Páginas soltas", Data(12, 11, 2026));

    t2.adicionarManutencao(m1);
    t2.adicionarManutencao(m2);

    CHECK(t2.getManutencoes().size() == 2);
    CHECK(t2.getManutencoes()[0] == m1);
    CHECK(t2.getManutencoes()[1] == m2);

    t2.adicionarManutencao(nullptr);
    CHECK(t2.getManutencoes().size() == 2);

    t2.adicionarManutencao(m1);
    CHECK(t2.getManutencoes().size() == 2);
}

TEST_CASE("Teste setManutencao - TecnicoManutencao") {
    TecnicoManutencao t3("José", "01234567890");
    Livro l1("Cálculo", "Stewart", 1, "Didático", 1);
    Livro l2("Um Curso de Cálculo", "Guidorizzi", 2, "Didático", 1);
    Manutencao *m1 = new Manutencao(&l1, &t3, "Capa rasgada", Data(10, 11, 2026));
    Manutencao *m2 = new Manutencao(&l2, &t3, "Páginas soltas", Data(12, 11, 2026));
    std::vector<Manutencao*> manutencoes = {m1, m2};
    t3.setManutencoes(manutencoes);

    CHECK(t3.getManutencoes().size() == 2);
    CHECK(t3.getManutencoes()[0] == m1);
    CHECK(t3.getManutencoes()[1] == m2);

    std::vector<Manutencao*> manutencoesVazias;
    t3.setManutencoes(manutencoesVazias);
    CHECK(t3.getManutencoes().empty());
}

TEST_CASE("Teste consultarManutencoesPendentes - TecnicoManutencao") {
    TecnicoManutencao t4("José", "01234567890");
    Livro l1("Cálculo", "Stewart", 1, "Didático", 1);
    Livro l2("Um Curso de Cálculo", "Guidorizzi", 2, "Didático", 1);
    Manutencao *m1 = new Manutencao(&l1, &t4, "Capa rasgada", Data(10, 11, 2026));
    Manutencao *m2 = new Manutencao(&l2, &t4, "Páginas soltas", Data(12, 11, 2026));
    t4.adicionarManutencao(m1);
    t4.adicionarManutencao(m2);

    CHECK(t4.consultarManutencoesPendentes() == 2);
    m1->iniciar();
    CHECK(t4.consultarManutencoesPendentes() == 1);
    m2->iniciar();
    CHECK(t4.consultarManutencoesPendentes() == 0);
}

TEST_CASE("Teste registrarReparo - TecnicoManutencao") {
    TecnicoManutencao t5("José", "01234567890");
    Livro l1("Cálculo", "Stewart", 1, "Didático", 1);
    Manutencao *m1 = new Manutencao(&l1, &t5, "Capa rasgada", Data(10, 11, 2026));
    t5.adicionarManutencao(m1);

    m1->iniciar();
    t5.registrarReparo(m1, "Capa consertada");
    CHECK(m1->getReparo() == "Capa consertada");

    m1->concluir();
    t5.registrarReparo(m1, "Tentativa de reparo após conclusão");
    CHECK(m1->getReparo() == "Capa consertada");
}

TEST_CASE("Teste concluirManutencao - TecnicoManutencao") {
    TecnicoManutencao t6("José", "01234567890");
    Livro l1("Cálculo", "Stewart", 1, "Didático", 1);
    Manutencao *m1 = new Manutencao(&l1, &t6, "Capa rasgada", Data(10, 11, 2026));
    t6.adicionarManutencao(m1);
    l1.setDanificado(true);
    l1.setDisponivel(false);

    CHECK(m1->getEstado() == EstadoManutencao::PENDENTE);
    m1->iniciar();
    CHECK(m1->getEstado() == EstadoManutencao::EM_ANDAMENTO);
    t6.concluirManutencao(m1);
    CHECK(m1->getEstado() == EstadoManutencao::EM_ANDAMENTO);
    CHECK(l1.isDanificado() == true);

    t6.registrarReparo(m1, "Capa restaurada");
    t6.concluirManutencao(m1);
    CHECK(m1->getEstado() == EstadoManutencao::CONCLUIDA);
    CHECK(l1.isDanificado() == false);
    CHECK(l1.isDisponivel() == true);
}

TEST_CASE("Destrutor de TecnicoManutencao") {
    Livro l1("Cálculo", "Stewart", 1, "Didático", 1);
    {
        TecnicoManutencao t7("José", "01234567890");
        t7.adicionarManutencao(new Manutencao(&l1, &t7, "Capa rasgada", Data(10, 11, 2026)));
    }

    CHECK(true);
}