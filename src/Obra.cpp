#include <stdexcept>
#include "Obra.hpp"

    Obra::Obra(const std::string &t, const std::string &a, int id):
    titulo(t), autor(a), id(id), disponivel(true), danificado(false), emManutencao(false) {
        if (titulo.empty()) {
            throw std::invalid_argument("Título da obra não pode ser vazio.");
        }
        if (autor.empty()) {
            throw std::invalid_argument("Autor da obra não pode ser vazio.");
        }
        if (id <= 0) {
            throw std::invalid_argument("ID da obra deve ser maior que zero.");
        }
    }

    void Obra::setDanificado(bool d) {
        danificado = d;
    }

    void Obra::setDisponivel(bool d) {
        disponivel = d;
    }

    void Obra::setEmManutencao(bool m) {
        emManutencao = m;
    }

    void Obra::setTitulo(const std::string &t) {
        if (t.empty()) {
            throw std::invalid_argument("Título da obra não pode ser vazio.");
        }
        titulo = t;
    }

    void Obra::setAutor(const std::string &a) {
        if (a.empty()) {
            throw std::invalid_argument("Autor da obra não pode ser vazio.");
        }
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

    bool Obra::isEmManutencao() const {
        return emManutencao;
    }