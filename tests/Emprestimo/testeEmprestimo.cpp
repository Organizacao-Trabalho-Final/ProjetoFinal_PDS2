#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../third_party/doctest.h"
#include "../../include/Emprestimo.hpp"
#include "Livro.hpp"
#include "Pessoa.hpp"
#include "Estudante.hpp"

struct TesteEmprestimo {
    static bool renovar(Emprestimo &e) {
        return e.renovarEmprestimo();
    }
};

TEST_CASE("Teste Construtor e Getters - Emprestimo") {
    Livro l1("Dom Casmurro", "Machado de Assis", 1, "Romance", 5);
    Estudante p1("Fulano", "01234567890", "Engenharia", "2026012345");
    Emprestimo e1(l1, p1, Data(12, 11, 2026));

    CHECK(e1.getObra().getTitulo() == "Dom Casmurro");
    CHECK(e1.getUsuario().getNome() == "Fulano");
    CHECK(e1.getRetirada().getData() == "12/11/2026");
    CHECK(e1.getDevolucao().getData() == "12/12/2026");
    CHECK(e1.isAtivo() == true);

    Livro l2("Dom Casmurro", "Machado de Assis", 1, "Romance", 5);
    Pessoa p2("Fulano", "01234567890");
    CHECK_THROWS_AS(Emprestimo(l2, p2, Data(12, 11, 2026)), std::invalid_argument);
}

TEST_CASE("Teste isAtivo e setAtivo - Emprestimo") {
    Livro l3("Dom Casmurro", "Machado de Assis", 1, "Romance", 5);
    Estudante p3("Fulano", "01234567890", "Engenharia", "2026012345");
    Emprestimo e3(l3, p3, Data(12, 11, 2026));

    CHECK(e3.isAtivo() == true);
    e3.encerrarEmprestimo();
    CHECK(e3.isAtivo() == false);
}

TEST_CASE("Teste setDevolucao e getAtraso - Emprestimo") {
    Livro l4("Dom Casmurro", "Machado de Assis", 1, "Romance", 5);
    Estudante p4("Fulano", "01234567890", "Engenharia", "2026012345");
    Emprestimo e4(l4, p4, Data(12, 11, 2026));

    CHECK(e4.getDevolucao().getData() == "12/12/2026");
    e4.setDevolucao(Data(15, 12, 2026));
    CHECK(e4.getDevolucao().getData() == "15/12/2026");
    e4.setDevolucao(Data(14, 12, 2026));
    CHECK(e4.getDevolucao().getData() == "14/12/2026");

    CHECK(e4.getAtraso(Data(15, 12, 2026)) == 1);
    CHECK(e4.getAtraso(Data(14, 12, 2026)) == 0);
    CHECK(e4.getAtraso(Data(13, 12, 2026)) == 0);
    CHECK(e4.getAtraso(Data(01, 01, 2027)) == 18);
    CHECK_THROWS_AS(e4.getAtraso(Data(32, 12, 2026)), std::invalid_argument);
}

TEST_CASE("Teste encerrarEmprestimo - Emprestimo") {
    Livro l5("Dom Casmurro", "Machado de Assis", 1, "Romance", 5);
    Estudante p5("Fulano", "01234567890", "Engenharia", "2026012345");
    Emprestimo e5(l5, p5, Data(12, 11, 2026));

    CHECK(e5.isAtivo() == true);
    e5.encerrarEmprestimo();
    CHECK(e5.isAtivo() == false);
}

TEST_CASE("Teste printEmprestimo - Emprestimo") {
    Livro l7("Dom Casmurro", "Machado de Assis", 1, "Romance", 5);
    Estudante p7("Fulano", "01234567890", "Engenharia", "2026012345");
    Emprestimo e7(l7, p7, Data(12, 11, 2026));

    std::ostringstream oss;
    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    e7.printEmprestimo();

    std::cout.rdbuf(oldCoutStreamBuf);

    std::string expectedOutput = 
        "Obra: Dom Casmurro\n"
        "Usuario: Fulano\n"
        "Data de retirada: 12/11/2026\n"
        "Data de devolucao: 12/12/2026\n"
        "Estado: Ativo\n";

    CHECK(oss.str() == expectedOutput);
}

TEST_CASE("Teste Destrutor - Emprestimo") {
    Livro l8("Dom Casmurro", "Machado de Assis", 1, "Romance", 5);
    Estudante p8("Fulano", "01234567890", "Engenharia", "2026012345");
    {
    Emprestimo e8(l8, p8, Data(12, 11, 2026));
    CHECK(e8.getObra().getTitulo() == "Dom Casmurro");
    CHECK(e8.getUsuario().getNome() == "Fulano");
    }
    CHECK(true);
}

TEST_CASE("Teste solicitarRenovacao - Emprestimo") {
    Livro l6("Dom Casmurro", "Machado de Assis", 1, "Romance", 5);
    Estudante p6("Fulano", "01234567890", "Engenharia", "2026012345");
    Emprestimo e6(l6, p6, Data(12, 11, 2026));

    CHECK(e6.isRenovacaoSolicitada() == false);
    CHECK(e6.solicitarRenovacao() == true);
    CHECK(e6.isRenovacaoSolicitada() == true);
    CHECK(e6.solicitarRenovacao() == false);
}

TEST_CASE("Teste solicitar renovacao com emprestimo inativo") {
    Livro l7("Dom Casmurro", "Machado de Assis", 1, "Romance", 5);
    Estudante p7("Fulano", "01234567890", "Engenharia", "2026012345");
    Emprestimo e7(l7, p7, Data(12, 11, 2026));
    CHECK(e7.solicitarRenovacao() == true);

    e7.encerrarEmprestimo();
    CHECK(e7.isRenovacaoSolicitada() == false);
    CHECK(e7.solicitarRenovacao() == false);
}

TEST_CASE("Emprestimo - renovação em estados inválidos") {
    Livro livro("Dom Casmurro", "Machado de Assis", 90, "Romance", 1);
    Estudante estudante("Fulano", "01234567890", "Engenharia", "2026012345");
    Emprestimo e(livro, estudante, Data(12, 11, 2026));

    CHECK_FALSE(TesteEmprestimo::renovar(e));
    REQUIRE(e.solicitarRenovacao());
    e.encerrarEmprestimo();
    CHECK_FALSE(TesteEmprestimo::renovar(e));
}