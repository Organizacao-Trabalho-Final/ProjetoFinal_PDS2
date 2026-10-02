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
        std::string danoIdentificado;
        std::string reparosRealizados;
        Data dataInicio;
        Data prazoPrevisto;
        EstadoManutencao estado;

    public:
        Manutencao(Obra *o, TecnicoManutencao *tm, std::string dano, Data inicio, Data prazo);

        
        Obra* getObra() const;
        TecnicoManutencao* getTecnico() const;

        
        void registrarDano(std::string dano);
        void registrarReparo(std::string reparo);
        std::string getDanoIdentificado() const;
        std::string getReparosRealizados() const;

        
        void setDataInicio(Data d);
        Data getDataInicio() const;
        void setPrazoPrevisto(Data p);
        Data getPrazoPrevisto() const;

        
        void setEstado(EstadoManutencao e);
        EstadoManutencao getEstado() const;
        std::string getEstadoString() const;
        bool isPendente() const;
        bool isEmAndamento() const;
        bool isConcluida() const;

    
        void modificarDisponibilidadeObra(bool disponivel);
};
#endif