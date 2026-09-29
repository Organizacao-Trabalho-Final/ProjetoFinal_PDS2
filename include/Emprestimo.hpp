#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

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
        void setAtivo(bool b);

        Obra& getObra();
        const Pessoa& getUsuario() const;
        Data getRetirada() const;
        Data getDevolucao() const;

        int getAtraso(Data d) const;
        void encerrarEmprestimo();
        void renovarEmprestimo();

        ~Emprestimo() = default;
};
#endif