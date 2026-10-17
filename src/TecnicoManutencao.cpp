#include <iostream>
#include <string>
#include <vector>
#include "Manutencao.hpp"
#include "TecnicoManutencao.hpp"

    TecnicoManutencao::TecnicoManutencao(std::string n, std::string c):
    Pessoa(n, c), manutencoes() {}

    std::vector<Manutencao*>& TecnicoManutencao::getManutencoes() const {

    }

    int TecnicoManutencao::getMaxManutencoes() const {
        
    }

    void TecnicoManutencao::adicionarManutencao(Manutencao *m) {

    }
        
    int TecnicoManutencao::consultarManutencoesPendentes() const {

    }
        
    void TecnicoManutencao::registrarReparo(Manutencao *m, std::string r) {

    }
        
    void TecnicoManutencao::concluirManutencao(Manutencao *m) {

    }