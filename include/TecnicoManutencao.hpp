#ifndef TECNICOMANUTENCAO_H
#define TECNICOMANUTENCAO_H

#include <iostream>
#include <string>
#include <vector>
#include "Pessoa.hpp"

class Manutencao;
class Obra;
class Catalogo;

class TecnicoManutencao : public Pessoa {
    private:
        std::vector<Manutencao*> manutencoes;

    public:
        TecnicoManutencao(std::string n, std::string c);

        // Gerenciamento das manutenções atribuídas ao técnico
        void adicionarManutencao(Manutencao *m);

        // Consultas
        int consultarManutencoesPendentes() const;
        Obra* identificarObra(Manutencao *m) const;

        // Operações sobre a manutenção
        void registrarReparo(Manutencao *m, std::string tipoReparo);
        void concluirManutencao(Manutencao *m);

        // Autoriza a obra a voltar a ficar disponível no catálogo
        void autorizarDisponibilidade(Manutencao *m, Catalogo *c);
};
#endif