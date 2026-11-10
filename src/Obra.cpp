#include <stdexcept>
#include "Obra.hpp"
#include "Tratamento.hpp"

    Obra::Obra(const std::string &t, const std::string &a, int id):
    titulo(t), autor(a), id(id), disponivel(true), danificado(false), emManutencao(false) {
        Tratamento tratamento;
        tratamento.isStringValido(titulo, 1, 50, true, "Título");
        tratamento.isStringValido(autor, 1, 50, true, "Autor");
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
        Tratamento tratamento;
        tratamento.isStringValido(t, 1, 50, true, "Título");
        titulo = t;
    }

    void Obra::setAutor(const std::string &a) {
        Tratamento tratamento;
        tratamento.isStringValido(a, 1, 50, true, "Autor");
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