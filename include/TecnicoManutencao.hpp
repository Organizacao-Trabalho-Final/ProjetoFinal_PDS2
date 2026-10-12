#ifndef TECNICOMANUTENCAO_H
#define TECNICOMANUTENCAO_H

#include <iostream>
#include <string>
#include <vector>
#include "Pessoa.hpp"

class Manutencao;
class Obra;

class TecnicoManutencao : public Pessoa {
    private:
        std::vector<Manutencao*> manutencoes;

    public:
        TecnicoManutencao(std::string n, std::string c);

        void adicionarManutencao(Manutencao *m);
        int consultarManutencoesPendentes() const;
        void registrarReparo(Manutencao *m, std::string r);
        void concluirManutencao(Manutencao *m);
};
#endif