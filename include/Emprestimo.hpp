#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

#include <iostream>
#include "Obra.hpp"
#include "Pessoa.hpp"

class Emprestimo {
    private:
        Obra *obra;
        Pessoa *usuario;
        int retirada, devolucao;
        bool ativo;

    public:
        Emprestimo(Obra &o, Pessoa &p, int data);

        Obra& getObra() const;
        Pessoa& getUsuario() const;
        int getRetirada() const;
        int getDevolucao() const;
        bool isAtivo() const;

        int getAtraso(int data);
        void renovarEmprestimo(int data);
        bool validarEmprestimo();

        ~Emprestimo() = default;
};
#endif