#include <string>
#include "Estudante.hpp"

    Estudante::Estudante(std::string n, std::string cpf, std::string c, std::string m):
    Pessoa(n, cpf), curso(c), matricula(m) {}

    std::string Estudante::getCurso() const {

    }

    std::string Estudante::getMatricula() const {

    }

    int Estudante::getPrazo() const {

    }

    int Estudante::getMaxEmprestimos() const {

    }

    bool Estudante::podeEmprestar(const Obra *o) const {

    }