#include <string>
#include "Estudante.hpp"

    Estudante::Estudante(std::string n, std::string cpf, std::string c, std::string m):
    Pessoa(n, cpf), curso(c), matricula(m) {}

   
