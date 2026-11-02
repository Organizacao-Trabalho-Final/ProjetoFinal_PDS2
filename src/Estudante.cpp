#include <string>
#include "Estudante.hpp"
#include "Obra.hpp"
#include "Livro.hpp"

    Estudante::Estudante(const std::string &n, const std::string &cpf, const std::string &c, const std::string &m):
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
        if (o == nullptr) {
        return false;
        }

        if (dynamic_cast<const Livro*>(o) == nullptr) {
            return false;
        }
        return (o->isDisponivel() && getEmprestimosAtivos() < getMaxEmprestimos());
}