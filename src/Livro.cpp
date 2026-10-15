#include <iostream>
#include <string>
#include "Livro.hpp"

    Livro::Livro(std::string t, std::string a, int id, std::string g, int e):
    Obra(t, a, id), genero(g), edicao(e) {}

    void Livro::setEdicao(int e) {
        if (e > 0) {
            edicao = e;
        }
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
        std::cout << "Titulo: " << getTitulo();
        std::cout << "Autor: " << getAutor() << std::endl;
        std::cout << "Genero: " << getGenero() << std::endl;
        std::cout << "Edição: " << getEdicao() << std::endl;
        std::cout << "ID: " << getID() << std::endl;
        std::cout << "Disponivel: " << (isDisponivel() ? "Sim" : "Não") << std::endl;
    }