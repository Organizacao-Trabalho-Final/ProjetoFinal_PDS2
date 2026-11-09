#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../third_party/doctest.h"
#include "../../include/Obra.hpp"
#include <stdexcept>

class TesteObra : public Obra {
    public:
        TesteObra(std::string t, std::string a, int id) : Obra(t, a, id) {}
        void printObra() const override {}
};

TEST_CASE("Teste Construtor - Obra") {
    TesteObra o1("Cálculo Vol1", "Stewart", 3);
    CHECK(o1.getTitulo() == "Cálculo Vol1");
    CHECK(o1.getAutor() == "Stewart");
    CHECK(o1.getID() == 3);

    CHECK_THROWS_AS(TesteObra("Cálculo Vol1", "", 3), std::invalid_argument);
    CHECK_THROWS_AS(TesteObra("Cálculo Vol1", "Stewart", 0), std::invalid_argument);
    CHECK_THROWS_AS(TesteObra("Cálculo Vol1", "Stewart", -1), std::invalid_argument); 
}

TEST_CASE("Teste Setters e Getters - Obra") {
    TesteObra o3("Cálculo Vol1", "Stewart", 3);
    o3.setTitulo("Dom Casmurro");
    o3.setAutor("Machado de Assis");
    o3.setDisponivel(false);
    o3.setDanificado(true);
    CHECK(o3.getTitulo() == "Dom Casmurro");
    CHECK(o3.getAutor() == "Machado de Assis");
    CHECK(o3.isDisponivel() == false);
    CHECK(o3.isDanificado() == true);
    CHECK_THROWS_AS(o3.setTitulo(""), std::invalid_argument);
    CHECK_THROWS_AS(o3.setAutor(""), std::invalid_argument);
    CHECK(o3.getTitulo() == "Dom Casmurro");
    CHECK(o3.getAutor() == "Machado de Assis");
}

TEST_CASE("Teste isDisponivel - Obra"){
    TesteObra o4("Dom Quixote", "Miguel de Cervantes", 4);
    CHECK(o4.isDisponivel() == true);
    o4.setDisponivel(false);
    CHECK(o4.isDisponivel() == false);
}

TEST_CASE("Teste isDanificado - Obra"){
    TesteObra o5("O Pequeno Príncipe", "Antoine de Saint-Exupéry", 5);
    CHECK(o5.isDanificado() == false);
    o5.setDanificado(true);
    CHECK(o5.isDanificado() == true);
}