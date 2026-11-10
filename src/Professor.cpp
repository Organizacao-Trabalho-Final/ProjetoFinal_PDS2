#include <string>
#include <stdexcept>
#include "Obra.hpp"
#include "Professor.hpp"
#include "Tratamento.hpp"

    Professor::Professor(const std::string &n, const std::string &c, const std::string &a):
    Pessoa(n, c), area(a) {
        Tratamento tratamento;
        tratamento.isStringValido(area, 1, 50, true, "Área de atuação");
    }

    std::string Professor::getArea() const {
        return area;
    }
        
    int Professor::getPrazo() const {
        return 45;
    }
        
    int Professor::getMaxEmprestimos() const {
        return 5;
    }

    bool Professor::podeEmprestar(const Obra *o) const {
        return (o != nullptr && o->isDisponivel() && getEmprestimosAtivos() < getMaxEmprestimos());
    }