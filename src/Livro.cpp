#include <stdexcept>
#include <iostream>
#include <string>
#include "Livro.hpp"
#include "Tratamento.hpp"

    Livro::Livro(const std::string &t, const std::string &a, int id, const std::string &g, int e):
    Obra(t, a, id), genero(g), edicao(e) {
        Tratamento tratamento;
        tratamento.isStringValido(genero, 1, 50, true, "Gênero");
        if (e <= 0) {
            throw std::invalid_argument("Edicao deve ser maior que zero.");
        }
    }

    void Livro::setEdicao(int e) {
        if (e <= 0) {
            throw std::invalid_argument("Edição deve ser maior que zero");
        }
        edicao = e;
    }
    
    void Livro::setGenero(const std::string &g) {
        Tratamento tratamento;
        tratamento.isStringValido(g, 1, 50, true, "Gênero");
        genero = g;
    }

    int Livro::getEdicao() const {
        return edicao;
    }

    std::string Livro::getGenero() const {
        return genero;
    }

    void Livro::printObra() const {
        std::cout << "Titulo: " << getTitulo() << std::endl;
        std::cout << "Autor: " << getAutor() << std::endl;
        std::cout << "Genero: " << getGenero() << std::endl;
        std::cout << "Edição: " << getEdicao() << std::endl;
        std::cout << "ID: " << getID() << std::endl;
        std::cout << "Disponivel: " << (isDisponivel() ? "Sim" : "Não") << std::endl;
    }