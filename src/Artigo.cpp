#include <string>
#include "Artigo.hpp"
#include <stdexcept>
#include <iostream>

    Artigo::Artigo(const std::string &t, const std::string &a, int id, const std::string &ar, int an):
    Obra(t, a, id), area(ar), ano(an) {
        if (area.empty()) {
            throw std::invalid_argument("Área do artigo não pode ser vazia.");
        }
        if (ano < 1 || ano > 9999) {
            throw std::invalid_argument("Ano invalido -> ANO > 0 | ANO com ate 4 digitos");
        }
    }

    void Artigo::setAno(int a) {
        if(a < 1 || a > 9999) {
            throw std::invalid_argument("Ano inválido -> ANO > 0 | ANO com 4 digitos");
        }
        ano = a;
    }

    void Artigo::setArea(const std::string &a) {
        if (a.empty()) {
            throw std::invalid_argument("Área do artigo não pode ser vazia.");
        }
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