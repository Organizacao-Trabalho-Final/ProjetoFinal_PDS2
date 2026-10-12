#include <string>
#include "Livro.hpp"

    Livro::Livro(std::string t, std::string a, int id, std::string g, int e):
    Obra(t, a, id), genero(g), edicao(e) {}

    void Livro::setEdicao(int e) {

    }

    void Livro::setGenero(std::string g) {

    }

    int Livro::getEdicao() const {

    }

    std::string Livro::getGenero() const {

    }

    void Livro::printObra() const {

    }