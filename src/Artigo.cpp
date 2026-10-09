#include <string>
#include "Artigo.hpp"
#include <exception>
#include <iostream>

    Artigo::Artigo(std::string _titulo, std::string _autor, int _id, std::string _area, int _ano):
    Obra(_titulo, _autor, _id), area(_area), ano(_ano) {}

    void Artigo::setAno(int a) {
        if(a < 0 || a > 9999) {
            throw std::invalid_argument("Ano inválido -> ANO > 0 | ANO com 4 digitos");
        }
        this->ano = a;
    }

    void Artigo::setArea(std::string a) {
        this->area = a;
    }

    int Artigo::getAno() const {
        return this->ano;
    }

    std::string Artigo::getArea() const {
        this->area;
    }

    void Artigo::printObra() const {

        std::cout << "Autor: " << getAutor() << std::endl;
        std::cout << "Area: " << this->getArea() << std::endl;
        std::cout << "Ano: " << this->getAno() << std::endl;
        std::cout << "ID: " << getID() << std::endl;
        std::cout << "Disponivel: " << (isDisponivel() ? "Sim" : "Não") << std::endl;

    }