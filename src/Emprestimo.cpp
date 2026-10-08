#include "Emprestimo.hpp"
#include "Pessoa.hpp"

    Emprestimo::Emprestimo(Obra &o, Pessoa &p, Data d):
    obra(&o), usuario(&p), retirada(d), devolucao(d.somarDias(p.getPrazo())), ativo(true) {}

    void Emprestimo::setAtivo(bool b) {

    }

    Obra& Emprestimo::getObra() {

    }

    const Pessoa& Emprestimo::getUsuario() const {

    }

    Data Emprestimo::getRetirada() const {

    }

    Data Emprestimo::getDevolucao() const {

    }

    int Emprestimo::getAtraso(Data d) const {

    }

    void Emprestimo::encerrarEmprestimo() {

    }

    void Emprestimo::renovarEmprestimo() {

    }