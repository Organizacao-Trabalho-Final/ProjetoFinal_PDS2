#ifndef BIBLIOTECARIO_H
#define BIBLIOTECARIO_H

#include <iostream>
#include "Pessoa.hpp"

class Bibliotecario : public Pessoa {
    public:
        Bibliotecario(std::string n, std::string c);
        
        bool aprovarEmprestimo(Emprestimo *e, Data d);
        bool aprovarRenovacao(Emprestimo *e, Data d);
        void registrarDevolucao(Emprestimo *e);
        void avaliarObra(Obra *o);
};
#endif