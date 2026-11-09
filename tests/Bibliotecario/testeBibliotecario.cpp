#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../third_party/doctest.h"
#include "../../include/Bibliotecario.hpp"
#include "Livro.hpp"
#include "Data.hpp"
#include "Estudante.hpp"
#include "Emprestimo.hpp"
#include "TecnicoManutencao.hpp"
#include "Manutencao.hpp"

TEST_CASE("Teste do construtor - Bibliotecario") {
    Bibliotecario b1("João", "12345678900");
    CHECK(b1.getNome() == "João");
    CHECK(b1.getCPF() == "12345678900");
}

TEST_CASE("Teste do método aprovarEmprestimo - Bibliotecario") {
    Bibliotecario b2("João", "12345678900");
    Estudante e2("Maria", "98765432100", "Letras", "2026021111");
    Livro l2("Hamlet", "William Shakespeare", 1, "Drama", 3);
    Data d2(10, 11, 2026);

    Emprestimo* n2 = b2.aprovarEmprestimo(&e2, &l2, d2);
    CHECK(n2 != nullptr);
    CHECK(l2.isDisponivel() == false);
    CHECK(e2.getNumEmprestimos() == 1);

    SUBCASE("Empréstimo de obra danificada ou indisponível") {
        l2.setDanificado(true);
        Emprestimo* n2 = b2.aprovarEmprestimo(&e2, &l2, d2);
        CHECK(n2 == nullptr);
        l2.setDanificado(false);
        l2.setDisponivel(false);
        Emprestimo* n3 = b2.aprovarEmprestimo(&e2, &l2, d2);
        CHECK(n3 == nullptr);
    }

    SUBCASE("Empréstimo de obra ou pessoa nula") {
        Emprestimo* n4 = b2.aprovarEmprestimo(&e2, nullptr, d2);
        CHECK(n4 == nullptr);
        Emprestimo* n5 = b2.aprovarEmprestimo(nullptr, &l2, d2);
        CHECK(n5 == nullptr);
    }

    SUBCASE("Empréstimo de obra já emprestada") {
        Emprestimo* n7 = b2.aprovarEmprestimo(&e2, &l2, d2);
        CHECK(n7 == nullptr);
    }
}

TEST_CASE("Teste de aprovarRenovacao - Bibliotecario") {
    Bibliotecario b3("João", "12345678900");
    Estudante e3("Maria", "98765432100", "Letras", "2026021111");
    Livro l3("Hamlet", "William Shakespeare", 1, "Drama", 3);
    Data d3(10, 11, 2026);
    Emprestimo* n3 = b3.aprovarEmprestimo(&e3, &l3, d3);

    SUBCASE("Renovação de empréstimo válido") {
        Data d4(15, 11, 2026);
        Data devolucaoAnterior = n3->getDevolucao();
        REQUIRE(n3->solicitarRenovacao() == true);

        CHECK(b3.aprovarRenovacao(n3, d4) == true);
        CHECK(devolucaoAnterior.diferencaDatas(n3->getDevolucao()) == 30);
        CHECK(n3->isRenovacaoSolicitada() == false);
        CHECK(b3.aprovarRenovacao(n3, d4) == false);
    }

    SUBCASE("Renovação de empréstimo com atraso") {
        Data d5(20, 12, 2026);
        REQUIRE(n3->solicitarRenovacao() == true);

        CHECK(b3.aprovarRenovacao(n3, d5) == false);
        CHECK(n3->isRenovacaoSolicitada() == false);
    }

    SUBCASE("Renovação de empréstimo nulo ou inativo") {
        CHECK(b3.aprovarRenovacao(nullptr, d3) == false);
        REQUIRE(n3->solicitarRenovacao() == true);
        n3->encerrarEmprestimo();

        CHECK(n3->isRenovacaoSolicitada() == false);
        CHECK(b3.aprovarRenovacao(n3, d3) == false);
    }
}

TEST_CASE("Teste de registrarDevolucao - Bibliotecario") {
    Bibliotecario b4("João", "12345678900");
    Estudante e4("Maria", "98765432100", "Letras", "2026021111");
    Livro l4("Hamlet", "William Shakespeare", 1, "Drama", 3);
    Data d4(12, 11, 2026);

    Emprestimo* n4 = b4.aprovarEmprestimo(&e4, &l4, d4);

    SUBCASE("Devolução de empréstimo válido") {
        b4.registrarDevolucao(n4);
        CHECK(n4->isAtivo() == false);
        CHECK(l4.isDisponivel() == true);
    }

    SUBCASE("Devolução de empréstimo nulo ou inativo") {
        b4.registrarDevolucao(nullptr);
        CHECK(n4->isAtivo() == true);

        n4->encerrarEmprestimo();
        b4.registrarDevolucao(n4);
        CHECK(n4->isAtivo() == false);
    }

    SUBCASE("Devolução de obra danificada") {
        l4.setDanificado(true);
        b4.registrarDevolucao(n4);

        CHECK(n4->isAtivo() == false);
        CHECK(l4.isDisponivel() == false);
    }
}

TEST_CASE("Teste de avaliarObra - Bibliotecario") {
    Bibliotecario b5("João", "12345678900");
    Livro l5("Hamlet", "William Shakespeare", 1, "Drama", 3);

    SUBCASE("Avaliação de obra danificada") {
        l5.setDanificado(true);
        CHECK(b5.avaliarObra(&l5) == true);
    }

    SUBCASE("Avaliação de obra não danificada") {
        l5.setDanificado(false);
        CHECK(b5.avaliarObra(&l5) == false);
    }

    SUBCASE("Avaliação de obra nula") {
        CHECK(b5.avaliarObra(nullptr) == false);
    }
}

TEST_CASE("Teste de encaminharManutencao - Bibliotecario") {
    Bibliotecario b6("João", "12345678900");
    TecnicoManutencao t1("Carlos", "11122233344");
    Livro l6("Hamlet", "William Shakespeare", 1, "Drama", 3);
    Data d6(15, 11, 2026);

    SUBCASE("Encaminhamento de obra danificada") {
        l6.setDanificado(true);
        Manutencao* m1 = b6.encaminharManutencao(&l6, &t1, "Capa rasgada", d6);
        CHECK(m1 != nullptr);
        CHECK(l6.isDisponivel() == false);
        CHECK(t1.getManutencoes().size() == 1);
    }

    SUBCASE("Encaminhamento de obra não danificada") {
        l6.setDanificado(false);
        Manutencao* m2 = b6.encaminharManutencao(&l6, &t1, "Capa rasgada", d6);
        CHECK(m2 == nullptr);
    }

    SUBCASE("Encaminhamento de obra ou técnico nulo") {
        l6.setDanificado(true);
        Manutencao* m3 = b6.encaminharManutencao(nullptr, &t1, "Capa rasgada", d6);
        CHECK(m3 == nullptr);

        Manutencao* m4 = b6.encaminharManutencao(&l6, nullptr, "Capa rasgada", d6);
        CHECK(m4 == nullptr);
    }
}

TEST_CASE("Bibliotecario respeita limite de emprestimos") {
    Bibliotecario b("Joao", "12345678900");
    Estudante e("Maria", "98765432100", "Letras", "2026021111");

    Livro l1("Livro 1", "Autor", 1, "Romance", 1);
    Livro l2("Livro 2", "Autor", 2, "Romance", 1);
    Livro l3("Livro 3", "Autor", 3, "Romance", 1);
    Livro l4("Livro 4", "Autor", 4, "Romance", 1);

    Data d(10, 11, 2026);
    CHECK(b.aprovarEmprestimo(&e, &l1, d) != nullptr);
    CHECK(b.aprovarEmprestimo(&e, &l2, d) != nullptr);
    CHECK(b.aprovarEmprestimo(&e, &l3, d) != nullptr);

    CHECK(e.getEmprestimosAtivos() == 3);
    CHECK(b.aprovarEmprestimo(&e, &l4, d) == nullptr);
}

TEST_CASE("Bibliotecario restringe categorias de usuarios") {
    Bibliotecario b("Joao", "12345678900");
    Bibliotecario outroBibliotecario("Ana", "11122233344");
    TecnicoManutencao tecnico("Carlos", "22233344455");

    Livro livro("Hamlet", "Shakespeare", 1, "Drama", 1);
    Data d(10, 11, 2026);

    CHECK(b.aprovarEmprestimo(&outroBibliotecario, &livro, d) == nullptr);
    CHECK(b.aprovarEmprestimo(&tecnico, &livro, d) == nullptr);
    CHECK(livro.isDisponivel());
}