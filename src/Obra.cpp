#include "../include/Obra.hpp"

Obra::Obra(std::string t, std::string a, int id) {

    this->titulo = t;
    this->autor  = a;
    this->id     = id;

    // Veificar  ????????
    this->danificado = false;
    this->disponivel = true;
    // ??????????

}

void Obra::setDanificado(bool d) {

    this->danificado = d;

}

void Obra::setDisponivel(bool d) {

    this->disponivel = d;

}

void Obra::setTitulo(std::string t) {

    this->titulo = t;

}

void Obra::setAutor(std::string a) {

    this->autor = a;

} 

std::string Obra::getAutor() const {

    return this->autor;

}

std::string Obra::getTitulo() const {

    return this->titulo;

}

int Obra::getID() const {

    return this->id;

}

bool Obra::isDanificado() const {

    return this->danificado;

}

bool Obra::isDisponivel() const {

    return this->disponivel;

}

