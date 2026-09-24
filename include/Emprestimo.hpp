#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

#include <iostream>
#include "Data.hpp"

class Obra;
class Pessoa;

class Emprestimo {
    private:
        Obra *obra;
        Pessoa *usuario;
        Data retirada, devolucao;
        bool ativo;

    public:
        Emprestimo(Obra &o, Pessoa &p, Data d);

        const Obra& getObra() const;
        const Pessoa& getUsuario() const;
        Data getRetirada() const;
        Data getDevolucao() const;
        bool isAtivo() const;

        int getAtraso(Data d) const;
        bool validarEmprestimo() const;
        void renovarEmprestimo(Data d);

        ~Emprestimo() = default;
};
#endif