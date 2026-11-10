#include <string>
#include <stdexcept>
#include <iostream>
#include "Artigo.hpp"
#include "Tratamento.hpp"

    Artigo::Artigo(const std::string &t, const std::string &a, int id, const std::string &ar, int an):
    Obra(t, a, id), area(ar), ano(an) {
        Tratamento tratamento;
        tratamento.isStringValido(area, 1, 50, true, "Área");
        if (ano < 1 || ano > 9999) {
            throw std::invalid_argument("Ano de publicação inválido.");
        }
    }

    void Artigo::setAno(int a) {
        if(a < 1 || a > 9999) {
            throw std::invalid_argument("Ano de publicação inválido.");
        }
        ano = a;
    }

    void Artigo::setArea(const std::string &a) {
        Tratamento tratamento;
        tratamento.isStringValido(a, 1, 50, true, "Área");
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