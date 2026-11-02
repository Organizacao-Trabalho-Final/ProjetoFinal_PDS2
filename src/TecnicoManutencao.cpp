#include <string>
#include <vector>
#include <algorithm>
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
        if (std::find(manutencoes.begin(), manutencoes.end(), m) != manutencoes.end()) {
            return;
        }
        manutencoes.push_back(m);
    }

    void TecnicoManutencao::setManutencoes(const std::vector<Manutencao*> &m){
        if (&m == &manutencoes) {
            return;
        }
        for (Manutencao *atual : manutencoes) {
            if (std::find(m.begin(), m.end(), atual) == m.end()) {
                delete atual;
            }
        }
        manutencoes.clear();
        for (Manutencao *nova : m) {
            adicionarManutencao(nova);
        }
    }

    int TecnicoManutencao::consultarManutencoesPendentes() const{
        int qtd = 0;
        for (const Manutencao *m : manutencoes) {
            if (m != nullptr & m->getEstado() == EstadoManutencao::PENDENTE) {
                qtd++;
            }
        }
        return qtd;
    }

    void TecnicoManutencao::registrarReparo(Manutencao* m, const std::string &r){
        if (m == nullptr) {
            return;
        }
        if (std::find(manutencoes.begin(), manutencoes.end(), m) == manutencoes.end()) {
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
        if (std::find(manutencoes.begin(), manutencoes.end(), m) == manutencoes.end()) {
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