#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <iostream>
#include <string>
#include "Dados.hpp"
#include "Tratamento.hpp"

class Interface {
    private:
        Dados *dados;
        Tratamento tratamento;

        void menuObras();
        void menuUsuarios();
        void menuEmprestimos();
        void menuManuntecoes();

        int lerOpcao(int min, int max);

    public:
        Interface(Dados *d);

        void executar();
};
#endif