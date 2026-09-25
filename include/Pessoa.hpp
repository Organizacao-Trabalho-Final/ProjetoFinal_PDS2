#ifndef PESSOA_H
#define PESSOA_H

#include <iostream>
#include <string>

class Obra;
class Emprestimo;

class Pessoa {
    private:
        std::string nome;
        std::string CPF;

    public:
        Pessoa(std::string n, std::string c);

        std::string getNome() const;
        std::string getCPF() const;
        virtual int getPrazo() const;
        virtual int getMaxEmprestimos() const;

        virtual bool podeEmprestar(const Obra *o) const;
        Emprestimo** consultarAtivos();
        Emprestimo** historicoEmprestimos();
        void pedirRenovacao(Emprestimo *e);

        virtual ~Pessoa() = default;
};
#endif