#include <string>
#include "Obra.hpp"
#include "Professor.hpp"

    Professor::Professor(std::string n, std::string c, std::string a):
    Pessoa(n, c), area(a) {}

    std::string Professor::getArea() const {
        return area;
    }
        
    int Professor::getPrazo() const {
        //????????????????????/!?!?!?!?!?!?!?!?!
        //Que prazo??!?!?!?!?!?!?!?!?!
    }
        
    int Professor::getMaxEmprestimos() const {
        return Pessoa::getMaxEmprestimos();
    }

    bool Professor::podeEmprestar(const Obra *o) const {
        return o->isDisponivel();
    }