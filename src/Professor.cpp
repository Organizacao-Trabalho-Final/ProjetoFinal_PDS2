#include <string>
#include <stdexcept>
#include "Obra.hpp"
#include "Professor.hpp"

    Professor::Professor(const std::string &n, const std::string &c, const std::string &a):
    Pessoa(n, c), area(a) {
        if (area.empty()) {
            throw std::invalid_argument("Área de atuação do professor não pode ser vazia.");
        }
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