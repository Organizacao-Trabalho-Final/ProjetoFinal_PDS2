#include <iostream>
#include "Emprestimo.hpp"
#include "Pessoa.hpp"
#include "Obra.hpp"

    Emprestimo::Emprestimo(Obra &o, Pessoa &p, const Data d):
    obra(&o), usuario(&p), retirada(d), devolucao(d.somarDias(p.getPrazo())), ativo(true), renovacaoSolicitada(false) {}

    void Emprestimo::setAtivo(bool b) {
        ativo = b;
        if (!ativo) {
            renovacaoSolicitada = false;
        }
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

    void Emprestimo::setDevolucao(Data d) {
        devolucao = d;
    }

    int Emprestimo::getAtraso(Data d) const {
        int atraso = devolucao.diferencaDatas(d);
        if (atraso < 0) {
            return 0;
        }
        return atraso;
    }

    bool Emprestimo::solicitarRenovacao() {
        if (!ativo || renovacaoSolicitada) {
            return false;
        }
        renovacaoSolicitada = true;
        return true;
    }

    bool Emprestimo::isRenovacaoSolicitada() const {
        return renovacaoSolicitada;
    }

    void Emprestimo::cancelarSolicitacaoRenovacao() {
        renovacaoSolicitada = false;
    }

    void Emprestimo::encerrarEmprestimo() {
        setAtivo(false);
    }

    void Emprestimo::printEmprestimo() const {
        std::cout << "Obra: " << obra->getTitulo() << std::endl;
        std::cout << "Usuario: " << usuario->getNome() << std::endl;
        std::cout << "Data de retirada: " << retirada.getData() << std::endl;
        std::cout << "Data de devolucao: " << devolucao.getData() << std::endl;
        std::cout << "Estado: " << (ativo ? "Ativo" : "Encerrado") << std::endl;
    }

    bool Emprestimo::renovarEmprestimo() {
        if (!ativo || !renovacaoSolicitada) {
            return false;
        }
        devolucao = devolucao.somarDias(usuario->getPrazo());
        renovacaoSolicitada = false;
        return true;
    }