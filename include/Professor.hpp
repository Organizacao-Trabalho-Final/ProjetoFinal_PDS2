#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <string>
#include "Pessoa.hpp"

class Professor : public Pessoa {
    private:
        std::string area;

    public:
        Estudante(std::string n, std::string c, std::string a);

        std::string getArea() const;
        int getPrazo() const override;
        int getMaxEmprestimos() const override;

        bool podeEmprestar(const Obra *o) const override;
};
#endif