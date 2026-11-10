#include <string>
#include <stdexcept>
#include "Estudante.hpp"
#include "Obra.hpp"
#include "Livro.hpp"
#include "Tratamento.hpp"

    Estudante::Estudante(const std::string &n, const std::string &cpf, const std::string &c, const std::string &m):
    Pessoa(n, cpf), curso(c), matricula(m) {
        Tratamento tratamento;
        tratamento.isStringValido(curso, 1, 50, true, "Curso");
        tratamento.validarMatricula(matricula);
    }

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