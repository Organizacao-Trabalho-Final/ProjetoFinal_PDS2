#include <string>
#include <stdexcept>
#include "Obra.hpp"
#include "Manutencao.hpp"

    Manutencao::Manutencao(Obra *o, TecnicoManutencao *tm, const std::string &d, const Data &i):
    obra(o), tecnico(tm), dano(d), inicio(i), estado(EstadoManutencao::PENDENTE) {
        if (tm == nullptr) {
            throw std::invalid_argument("Uma manutenção precisa estar associada a um técnico.");
        }
        if (obra != nullptr) {
            obra->setEmManutencao(true);
        }
    }

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
        if (obra != nullptr) {
            obra->setEmManutencao(e != EstadoManutencao::CONCLUIDA);
        }
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
        if (obra == nullptr || estado != EstadoManutencao::EM_ANDAMENTO || reparo.find_first_not_of(" \t\n\r") == std::string::npos) {
            return;
        }
        estado = EstadoManutencao::CONCLUIDA;
        obra->setDanificado(false);
        obra->setDisponivel(true);
        obra->setEmManutencao(false);
    }