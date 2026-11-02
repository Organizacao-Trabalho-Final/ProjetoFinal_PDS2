#include "Obra.hpp"

    Obra::Obra(const std::string &t, const std::string &a, int id):
    titulo(t), autor(a), id(id), disponivel(true), danificado(false) {}

    void Obra::setDanificado(bool d) {
        danificado = d;
    }

    void Obra::setDisponivel(bool d) {
        disponivel = d;
    }

    void Obra::setTitulo(const std::string &t) {
        titulo = t;
    }

    void Obra::setAutor(const std::string &a) {
        autor = a;
    } 

    std::string Obra::getAutor() const {
        return autor;
    }

    std::string Obra::getTitulo() const {
        return titulo;
    }

    int Obra::getID() const {
        return id;
    }

    bool Obra::isDanificado() const {
        return danificado;
    }

    bool Obra::isDisponivel() const {
        return disponivel;
    }