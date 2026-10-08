#include <string>
#include "Artigo.hpp"

    Artigo::Artigo(std::string t, std::string a, int id, std::string ar, int an):
    Obra(t, a, id), area(ar), ano(an) {}

    void Artigo::setAno(int a) {

    }

    void Artigo::setArea(std::string a) {

    }

    int Artigo::getAno() const {

    }

    std::string Artigo::getArea() const {

    }

    void Artigo::printObra() const {

    }