#include <iostream>
#include "Emprestimo.hpp"
#include "Pessoa.hpp"
#include "Obra.hpp"

    Emprestimo::Emprestimo(Obra &o, Pessoa &p, Data d):
    obra(&o), usuario(&p), retirada(d), devolucao(d.somarDias(p.getPrazo())), ativo(true) {}

    void Emprestimo::setAtivo(bool b) {
        ativo = b;
    }

    bool Emprestimo::isAtivo() const {
        return ativo;
    }

    Obra& Emprestimo::getObra() {
        return *obra;
    }

    const Pessoa& Emprestimo::getUsuario() const {
        return *usuario;
    }

    Data Emprestimo::getRetirada() const {
        return retirada;
    }

    Data Emprestimo::getDevolucao() const {
        return devolucao;
    }

    int Emprestimo::getAtraso(Data d) const {
        int atraso = devolucao.diferencaDatas(d);
        return atraso;
    }

    void Emprestimo::encerrarEmprestimo() {
        setAtivo(false);
        obra->setDisponivel(true);
    }

    void Emprestimo::printEmprestimo() const {
        std::string _nome = obra->getTitulo();
        std::string _dev  = devolucao.getData();
        std::string _ret  = retirada.getData();
        int         _id   = obra->getID();
        bool        _at   = ativo;
        std::cout << "Obra: " << _nome << std::endl;
        std::cout << "ID: " << _id << std::endl;
        std::cout << "Retirada: " << _ret << std::endl;
        std::cout << "Data para devolução: " << _dev << std::endl;
        std::cout << "Ativo: " << _at << std::endl;
    }

    void Emprestimo::renovarEmprestimo() {
        
    }