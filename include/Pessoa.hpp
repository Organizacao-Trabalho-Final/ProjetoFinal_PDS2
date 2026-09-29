#ifndef PESSOA_H
#define PESSOA_H

#include <string>
#include <vector>
class Obra;
class Emprestimo;

class Pessoa {
    private:
        std::string nome;
        std::string CPF;
        std::vector<Emprestimo*> emprestimos;

    public:
        Pessoa(std::string n, std::string c);

        std::string getNome() const;
        std::string getCPF() const;
        virtual int getPrazo() const;
        virtual int getMaxEmprestimos() const;

        virtual bool podeEmprestar(const Obra *o) const;
        std::vector<Emprestimo*> consultarAtivos();
        std::vector<Emprestimo*> historicoEmprestimos();
        void registrarEmprestimo(Emprestimo *e);
    
        virtual ~Pessoa() = default;
};
#endif