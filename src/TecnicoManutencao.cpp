#include <iostream>
#include <string>
#include <vector>
#include "Pessoa.hpp"
#include "TecnicoManutencao.hpp"
#include "Manutencao.hpp"
#include "Obra.hpp"

using namespace std;

TecnicoManutencao::TecnicoManutencao(string n, string c): Pessoa::Pessoa(n, c){}

void TecnicoManutencao::adicionarManutencao(Manutencao* m){
    manutencoes.push_back(m);
}

int TecnicoManutencao::consultarManutencoesPendentes() const{
    size_t n = manutencoes.size();
    for(size_t i=0; i<n; i++){
        if(manutencoes[i]->getEstado() == EstadoManutencao::PENDENTE){
            return manutencoes[i]->getObra()->getID();
        }
    }
    return -1;
}

void TecnicoManutencao::registrarReparo(Manutencao* m, string r){
    m->registrarReparo(r);
}

void TecnicoManutencao::concluirManutencao(Manutencao* m){
    m->concluir();
}