#ifndef BIBLIOTECARIO_H
#define BIBLIOTECARIO_H

#include "Pessoa.hpp"

class Data;
class Obra;
class Emprestimo;
class Manutencao;
class TecnicoManutencao;

class Bibliotecario : public Pessoa {
    public:
        Bibliotecario(std::string n, std::string c);
        
        Emprestimo* aprovarEmprestimo(Pessoa *p, Obra *o, Data d);
        bool aprovarRenovacao(Emprestimo *e, Data hj);
        void registrarDevolucao(Emprestimo *e);
        bool avaliarObra(const Obra *o) const;
        Manutencao* encaminharManutencao(Obra *o, TecnicoManutencao *tm, std::string dano, Data i);
};
#endif