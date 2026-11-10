#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <string>
#include <vector>
#include <stdexcept>
#include "doctest.h"
#include "Emprestimo.hpp"
#include "Professor.hpp"
#include "Obra.hpp"
#include "Livro.hpp"

Professor prof("Juriscreudo", "98765432100", "matematica");
std::string nome = "girafales";
std::string cpf1 = "12345678909";
std::string cpf2 = "52998224725";
std::string a = "biologia";
std::string ab = "historia";
Professor profa(nome, cpf1, a);
Professor profs(nome, cpf2, ab);
TEST_CASE("Teste Professor - getArea"){
    CHECK(prof.getArea() == "matematica");
    CHECK(profa.getArea() == a);
    CHECK(profs.getArea() == ab);
}

TEST_CASE("Teste Professor - getPrazo"){
    CHECK(profa.getPrazo() == 45);
}

TEST_CASE("Teste Professor - getMaxEmprestimos"){
    CHECK(profa.getMaxEmprestimos() == 5);
}

TEST_CASE("Teste Professor - podeEmprestar"){

    std::string t1 = "Dom Casmurro";
    std::string a1 = "Joaquim";
    std::string g = "jakjaknabujak";
    int ed = 2;

    Livro A(t1, a1, 1, g, ed);
    Livro B(t1, a1, 2, g, ed);
    Livro C(t1, a1, 3, g, ed);
    Livro D(t1, a1, 4, g, ed);
    Livro E(t1, a1, 5, g, ed);
    Livro F(t1, a1, 6, g, ed);
    Livro* G = nullptr;

    Data d(3, 3, 2008);
    Professor profj("fulano", "22233344405", "fisica");

    SUBCASE("Caso Valido"){
        profj.registrarEmprestimo(new Emprestimo(A, profj, d));
        profj.registrarEmprestimo(new Emprestimo(B, profj, d));
        profj.registrarEmprestimo(new Emprestimo(C, profj, d));
        profj.registrarEmprestimo(new Emprestimo(D, profj, d));

        CHECK(profj.podeEmprestar(&F) == true);
    }

    SUBCASE("Ponteiro nulo"){
        CHECK(profj.podeEmprestar(G) == false);
    }

    SUBCASE("Obra que nao esta disponivel"){
        F.setDisponivel(false);
        CHECK(profj.podeEmprestar(&F) == false);
    }

    SUBCASE("Muitos emprestimos ativos"){
        profj.registrarEmprestimo(new Emprestimo(A, profj, d));
        profj.registrarEmprestimo(new Emprestimo(B, profj, d));
        profj.registrarEmprestimo(new Emprestimo(C, profj, d));
        profj.registrarEmprestimo(new Emprestimo(D, profj, d));
        profj.registrarEmprestimo(new Emprestimo(E, profj, d));
        CHECK(profj.podeEmprestar(&F) == false);
    }
}

TEST_CASE("Professor - validação do construtor") {

    CHECK_THROWS_AS(Professor("Maria", "52998224725", ""), std::invalid_argument);
    CHECK_THROWS_AS(Professor("Maria", "12345678901", "Matemática"), std::invalid_argument);
    CHECK_NOTHROW(Professor("Maria", "98765432100", "Matemática"));

}