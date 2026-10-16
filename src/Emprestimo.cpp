#include "Emprestimo.hpp"
#include "Pessoa.hpp"

    Emprestimo::Emprestimo(Obra &o, Pessoa &p, Data d):
    obra(&o), usuario(&p), retirada(d), devolucao(d.somarDias(p.getPrazo())), ativo(true) {}

    void Emprestimo::setAtivo(bool b) {
        ativo = b;
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

    void Emprestimo::renovarEmprestimo() {
        
    }