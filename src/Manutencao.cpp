#include <iostream>
#include <string>
#include "Manutencao.hpp"

    Manutencao::Manutencao(Obra *o, TecnicoManutencao *tm, std::string d, Data i):
    obra(o), tecnico(tm), dano(d), inicio(i), estado(EstadoManutencao::PENDENTE) {}

    Obra* Manutencao::getObra() const {

    }

    TecnicoManutencao* Manutencao::getTecnico() const {

    }

    std::string Manutencao::getDano() const {

    }

    std::string Manutencao::getReparo() const {

    }

    Data Manutencao::getInicio() const {

    }

    EstadoManutencao Manutencao::getEstado() const {

    }

    void Manutencao::registrarReparo(std::string r) {

    }

    void Manutencao::iniciar() {

    }

    void Manutencao::concluir() {

    }