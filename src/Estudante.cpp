#include <string>
#include "Estudante.hpp"

    Estudante::Estudante(std::string n, std::string cpf, std::string c, std::string m):
    Pessoa(n, cpf), curso(c), matricula(m) {}

    std::string Estudante::getCurso() const {
        return curso;
    }

    std::string Estudante::getMatricula() const {
        return matricula;
    }

    int Estudante::getPrazo() const {
        return 30;
    }

    int Estudante::getMaxEmprestimos() const {
        return 3;
    }

    bool Estudante::podeEmprestar(const Obra *o) const {
        return Obra->isDisponivel();
    }