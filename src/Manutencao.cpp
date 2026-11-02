#include <string>
#include "Obra.hpp"
#include "Manutencao.hpp"

    Manutencao::Manutencao(Obra *o, TecnicoManutencao *tm, const std::string &d, const Data &i):
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

    void Manutencao::setEstado(EstadoManutencao e) {
        estado = e;
    }

    void Manutencao::registrarReparo(const std::string &r) {
        reparo = r;
    }

    void Manutencao::iniciar() {
        if (obra == nullptr || estado != EstadoManutencao::PENDENTE) {
            return;
        }
        obra->setDisponivel(false);
        estado = EstadoManutencao::EM_ANDAMENTO;
    }

    void Manutencao::concluir() {
        if (obra == nullptr || estado != EstadoManutencao::EM_ANDAMENTO) {
            return;
        }
        estado = EstadoManutencao::CONCLUIDA;
        obra->setDanificado(false);
        obra->setDisponivel(true);
    }