#ifndef MANUTENCAO_H
#define MANUTENCAO_H

#include <iostream>
#include <string>
#include "Data.hpp"

class Obra;
class TecnicoManutencao;

enum class EstadoManutencao {
    PENDENTE,
    EM_ANDAMENTO,
    CONCLUIDA
};

class Manutencao {
    private:
        Obra *obra;
        TecnicoManutencao *tecnico;
        std::string dano;
        std::string reparo;
        Data inicio;
        EstadoManutencao estado;

    public:
        Manutencao(Obra *o, TecnicoManutencao *tm, std::string d, Data i);

        Obra* getObra() const;
        TecnicoManutencao* getTecnico() const;
        std::string getDano() const;
        std::string getReparo() const;
        Data getInicio() const;
        EstadoManutencao getEstado() const;

        void registrarReparo(std::string r);
        void iniciar();
        void concluir();

        ~Manutencao() = default;
};
#endif