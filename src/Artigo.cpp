#include <string>
#include "Artigo.hpp"
#include <stdexcept>
#include <iostream>

    Artigo::Artigo(std::string t, std::string a, int id, std::string _area, int _ano):
    Obra(t, a, id), area(_area), ano(_ano) {}

    void Artigo::setAno(int a) {
        if(a < 0 || a > 9999) {
            throw std::invalid_argument("Ano inválido -> ANO > 0 | ANO com 4 digitos");
        }
        ano = a;
    }

    void Artigo::setArea(std::string a) {
        area = a;
    }

    int Artigo::getAno() const {
        return ano;
    }

    std::string Artigo::getArea() const {
        return area;
    }

    void Artigo::printObra() const {
        std::cout << "Titulo: " << getTitulo() << std::endl;
        std::cout << "Autor: " << getAutor() << std::endl;
        std::cout << "Area: " << getArea() << std::endl;
        std::cout << "Ano: " << getAno() << std::endl;
        std::cout << "ID: " << getID() << std::endl;
        std::cout << "Disponivel: " << (isDisponivel() ? "Sim" : "Não") << std::endl;
    }