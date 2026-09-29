#ifndef ESTUDANTE_H
#define ESTUDANTE_H

#include <string>
#include "Pessoa.hpp"

class Estudante : public Pessoa {
    private:
        std::string curso;
        std::string matricula;

    public:
        Estudante(std::string n, std::string cpf, std::string c, std::string m);

        std::string getCurso() const;
        std::string getMatricula() const;
        int getPrazo() const override;
        int getMaxEmprestimos() const override;

        bool podeEmprestar(const Obra *o) const override;
};
#endif