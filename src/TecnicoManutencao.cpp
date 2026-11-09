#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "TecnicoManutencao.hpp"
#include "Manutencao.hpp"

    TecnicoManutencao::TecnicoManutencao(std::string n, std::string c):
    Pessoa(n, c) {}

    const std::vector<Manutencao*>& TecnicoManutencao::getManutencoes() const{
        return manutencoes;
    }

    void TecnicoManutencao::adicionarManutencao(Manutencao* m){
        if (m == nullptr) {
            return;
        }
        if (m->getTecnico() != this) {
            throw std::invalid_argument("A manutenção não está associada a este técnico.");
        }
        if (std::find(manutencoes.begin(), manutencoes.end(), m) != manutencoes.end()) {
            return;
        }
        manutencoes.push_back(m);
    }

    void TecnicoManutencao::setManutencoes(const std::vector<Manutencao*> &m){
        if (&m == &manutencoes) {
            return;
        }

        std::vector<Manutencao*> novas;
        std::vector<Manutencao*> antigas;
        for (Manutencao *nova : m) {
            if (nova == nullptr) {
                continue;
            }
            if (nova->getTecnico() != this) {
                throw std::invalid_argument("Manutenção associada a outro técnico.");
            }
            if (std::find(novas.begin(), novas.end(), nova) == novas.end()) {
                novas.push_back(nova);
            }
        }

        for (Manutencao *atual : manutencoes) {
            if (atual != nullptr && std::find(antigas.begin(), antigas.end(), atual) == antigas.end()) {
                antigas.push_back(atual);
            }
        }

        for (Manutencao *atual : antigas) {
            if (std::find(novas.begin(), novas.end(), atual) == novas.end()) {
                delete atual;
            }
        }
        manutencoes.swap(novas);
    }

    int TecnicoManutencao::consultarManutencoesPendentes() const{
        int qtd = 0;
        for (const Manutencao *m : manutencoes) {
            if (m != nullptr && m->getEstado() == EstadoManutencao::PENDENTE) {
                qtd++;
            }
        }
        return qtd;
    }

    void TecnicoManutencao::registrarReparo(Manutencao* m, const std::string &r){
        if (m == nullptr) {
            return;
        }
        if (m->getTecnico() != this || std::find(manutencoes.begin(), manutencoes.end(), m) == manutencoes.end()) {
            return;
        }
        if (m->getEstado() != EstadoManutencao::EM_ANDAMENTO) {
            return;
        }
        m->registrarReparo(r);
    }

    void TecnicoManutencao::concluirManutencao(Manutencao* m){
        if (m == nullptr) {
            return;
        }
        if (m->getTecnico() != this || std::find(manutencoes.begin(), manutencoes.end(), m) == manutencoes.end()) {
            return;
        }
        if (m->getEstado() != EstadoManutencao::EM_ANDAMENTO) {
            return;
        }
        m->concluir();
    }

    TecnicoManutencao::~TecnicoManutencao() { // Liberação de memória
        for (Manutencao *m : manutencoes) {
            delete m;
        }
    }