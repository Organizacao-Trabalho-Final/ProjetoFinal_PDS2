#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <string>
#include <vector>
#include "doctest.h"
#include "Emprestimo.hpp"
#include "Professor.hpp"
#include "Obra.hpp"
#include "Livro.hpp"

Professor prof("Juriscreudo", "11122233344", "matematica");
std::string nome = "girafales";
std::string cpf = "1234567890";
std::string a = "biologia";
std::string ab;
Professor profa(nome, cpf, a);
Professor profs(nome, cpf, ab);
TEST_CASE("Teste Professor - getArea"){
    CHECK(prof.getArea() == "matematica");
    CHECK(profa.getArea() == a);
    CHECK(profs.getArea() == ab);
}

TEST_CASE("Teste Professor - getPrazo"){
    CHECK(profa.getPrazo() == 60);
}

TEST_CASE("Teste Professor - getMaxEmprestimos"){
    CHECK(profa.getMaxEmprestimos() == 5);
}

TEST_CASE("Teste Professor - podeEmprestar"){

    std::string t1 = "Dom Casmurro";
    std::string a1 = "Joaquim";
    int id1 = 1;
    std::string g = "jakjaknabujak";
    int ed = 2;
    Livro* A = new Livro(t1, a1, id1, g, ed);
    Livro* B = nullptr;
    Livro* C = new Livro(t1, a1, id1, g, ed);
    Livro* D = new Livro(t1, a1, id1, g, ed);
    Livro* E = new Livro(t1, a1, id1, g, ed);
    Livro* F = new Livro(t1, a1, id1, g, ed);
    Data d(3, 3, 2008);
    Emprestimo e1(*A, profs, d);
    Emprestimo e2(*F, profs, d);
    Emprestimo e3(*C, profs, d);
    Emprestimo e4(*D, profs, d);
    Emprestimo e5(*E, profs, d);

    Professor profj("fulano", "22233344455", "fisica");
    Livro* S = new Livro(t1, a1, id1, g, ed);
    SUBCASE("Caso Valido"){
        std::vector<Emprestimo*> e = {&e1, &e2, &e3, &e4};
        profj.setEmprestimos(e);
        CHECK(profj.podeEmprestar(S) == true);
    }

    SUBCASE("Ponteiro nulo"){
        CHECK(profj.podeEmprestar(B) == false);
    }

    SUBCASE("Obra que nao esta disponivel"){
        S->setDisponivel(false);
        CHECK(profj.podeEmprestar(S) == false);
    }

    SUBCASE("Muitos emprestimos ativos"){
        S->setDisponivel(true);
        std::vector<Emprestimo*> e = {&e1, &e2, &e3, &e4, &e5};
        profj.setEmprestimos(e);
        CHECK(profj.podeEmprestar(S) == false);
    }
    delete A;
    delete F;
    delete C;
    delete D;
    delete E;
    delete S;
}


// return (o != nullptr && o->isDisponivel() && getEmprestimosAtivos() < getMaxEmprestimos());