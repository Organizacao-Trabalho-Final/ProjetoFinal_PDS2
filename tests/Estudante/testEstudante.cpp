#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include <string>
#include <stdexcept>
#include "Estudante.hpp"
#include "Obra.hpp"
#include "Livro.hpp"
#include "Pessoa.hpp"
#include "Data.hpp"
#include "Emprestimo.hpp"
#include "Artigo.hpp"

TEST_CASE("Estudante - getCurso"){

    std::string n1 = "Daniel";
    std::string cpf = "11122233344";
    std::string c = "Matematica";
    std::string m = "111";

    Estudante e(n1, cpf, c, m);

    CHECK(e.getCurso() == c);
}

TEST_CASE("Estudante - getMatricula"){

    std::string n1 = "Daniel";
    std::string cpf = "11122233344";
    std::string c = "Matematica";
    std::string m = "111";

    Estudante e(n1, cpf, c, m);

    CHECK(e.getMatricula() == m);
}

TEST_CASE("Estudante - getPrazo"){

    std::string n1 = "Daniel";
    std::string cpf = "11122233344";
    std::string c = "Matematica";
    std::string m = "111";

    Estudante e(n1, cpf, c, m);

    CHECK(e.getPrazo() == 30);
}

TEST_CASE("Estudante - getMaxEmprestimos"){

    std::string n1 = "Daniel";
    std::string cpf = "11122233344";
    std::string c = "Matematica";
    std::string m = "111";

    Estudante e(n1, cpf, c, m);

    CHECK(e.getMaxEmprestimos() == 3);
}

TEST_CASE("Estudante - podeEmprestar"){

    std::string n1 = "Daniel";
    std::string cpf = "11122233344";
    std::string c = "Matematica";
    std::string m = "111";

    std::string t1 = "Confissoes";
    std::string ar = "fisica";
    std::string au1 = "S.A";
    std::string g1 = "Teo";
    int ed1 = 21;
    int id1 = 11;
    int an = 2026;
    Data d1(3, 3, 2008);

    Estudante e(n1, cpf, c, m);

    SUBCASE("Obra nula"){
        CHECK(e.podeEmprestar(nullptr) == false);
    }

    SUBCASE("Livro nullptr"){
        Artigo f(t1, au1, id1, ar, an);
        CHECK(e.podeEmprestar(&f) == false);
    }

    SUBCASE("Livro valido"){
        Livro* B = new Livro(t1, au1, id1, g1, ed1);
        CHECK(e.podeEmprestar(B) == true);
        delete B;
    }

    SUBCASE("Livro Indisponivel"){
        Livro* B = new Livro(t1, au1, id1, g1, ed1);
        B->setDisponivel(false);

        CHECK(e.podeEmprestar(B) == false);

        delete B;
    }

    SUBCASE("Muitos emprestimos ativos"){

        Livro B(t1, au1, id1, g1, ed1);
        Livro C(t1, au1, id1, g1, ed1);
        Livro D(t1, au1, id1, g1, ed1);
        Livro E(t1, au1, id1, g1, ed1);
        Emprestimo* e1 = new Emprestimo(B, e, d1);
        Emprestimo* e2 = new Emprestimo(C, e, d1);
        Emprestimo* e3 = new Emprestimo(D, e, d1);
        e.registrarEmprestimo(e1);
        e.registrarEmprestimo(e2);
        e.registrarEmprestimo(e3);

        CHECK(e.podeEmprestar(&E) == false);
    }

    SUBCASE("Com emprestimos ativos(2) mas abaixo do maximo"){

        Livro B(t1, au1, id1, g1, ed1);
        Livro C(t1, au1, id1, g1, ed1);
        Livro E(t1, au1, id1, g1, ed1);
        Emprestimo* e1 = new Emprestimo(B, e, d1);
        Emprestimo* e2 = new Emprestimo(C, e, d1);
        e.registrarEmprestimo(e1);
        e.registrarEmprestimo(e2);

        CHECK(e.podeEmprestar(&E) == true);
    }
}

TEST_CASE("Estudante - validação do construtor") {

    CHECK_THROWS_AS(Estudante("Daniel", "11122233344", "", "111"), std::invalid_argument);
    CHECK_THROWS_AS(Estudante("Daniel", "11122233344", "Matemática", ""), std::invalid_argument);
    CHECK_NOTHROW(Estudante("Daniel", "11122233344", "Matemática", "111"));

}