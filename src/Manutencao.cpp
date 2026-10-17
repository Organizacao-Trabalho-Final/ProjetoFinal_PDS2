#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include "Obra.hpp"
#include "Manutencao.hpp"

    Manutencao::Manutencao(Obra *o, TecnicoManutencao *tm, std::string d, Data i):
    obra(o), tecnico(tm), dano(d), inicio(i), estado(EstadoManutencao::PENDENTE) {}

    Obra* Manutencao::getObra() const {
        return obra;
    }

    TecnicoManutencao* Manutencao::getTecnico() const {
        return tecnico;
    }

    std::string Manutencao::getDano() const {
        return dano;
    }

    std::string Manutencao::getReparo() const {
        return reparo;
    }

    Data Manutencao::getInicio() const {
        return inicio;
    }

    EstadoManutencao Manutencao::getEstado() const {
        return estado;
    }

    void Manutencao::registrarReparo(std::string r) {
        reparo = r;
    }

    void Manutencao::iniciar() {
        /*auto agora = std::chrono::system_clock::now();
        std::time_t tempo = std::chrono::system_clock::to_time_t(agora);
        std::tm * atual = std::localtime(&tempo);

        int dia = atual->mday;
        int mes = atual->mon + 1;
        int ano = atual->year + 1900;*/

        obra->setDisponivel(false);
        estado = EstadoManutencao::EM_ANDAMENTO;
    }

    void Manutencao::concluir() {
        estado = EstadoManutencao::CONCLUIDA;
        obra->setDisponivel(true);
    }