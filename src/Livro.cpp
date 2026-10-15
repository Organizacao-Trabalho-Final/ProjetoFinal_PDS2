#include <iostream>
#include <string>
#include "Livro.hpp"

    Livro::Livro(std::string t, std::string a, int id, std::string g, int e):
    Obra(t, a, id), genero(g), edicao(e) {}

    void Livro::setEdicao(int e) {
        edicao = e;
    }

    void Livro::setGenero(std::string g) {
        genero = g;
    }

    int Livro::getEdicao() const {
        return edicao;
    }

    std::string Livro::getGenero() const {
        return genero;
    }

    void Livro::printObra() const {
        std::cout << "Titulo: " << getTitulo() << "\nAutor: " << getAutor() << "\nID: " << getID() << "\nGenero: " << getGenero() << "\nEdição: " << getEdicao();
    }