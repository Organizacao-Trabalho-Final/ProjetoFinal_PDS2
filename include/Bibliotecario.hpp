#ifndef BIBLIOTECARIO_H
#define BIBLIOTECARIO_H

#include "Pessoa.hpp"
class Data;

class Bibliotecario : public Pessoa {
    public:
        Bibliotecario(std::string n, std::string c);
        
        Emprestimo* aprovarEmprestimo(Pessoa *p, Obra *o, Data d);
        bool aprovarRenovacao(Emprestimo *e);
        void registrarDevolucao(Emprestimo *e);
        void avaliarObra(Obra *o);
};
#endif