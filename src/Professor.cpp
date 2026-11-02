#include <string>
#include "Obra.hpp"
#include "Professor.hpp"

    Professor::Professor(std::string n, std::string c, std::string a):
    Pessoa(n, c), area(a) {}

    std::string Professor::getArea() const {
        return area;
    }
        
    int Professor::getPrazo() const {
        return 60;
    }
        
    int Professor::getMaxEmprestimos() const {
        return 5;
    }

    bool Professor::podeEmprestar(const Obra *o) const {
        return (o != nullptr && o->isDisponivel() && getEmprestimosAtivos() < getMaxEmprestimos());
    }