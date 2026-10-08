#include <iostream>
#include <string>
#include <vector>
#include "TecnicoManutencao.hpp"

    TecnicoManutencao::TecnicoManutencao(std::string n, std::string c):
    Pessoa(n, c), manutencoes() {}

    void TecnicoManutencao::adicionarManutencao(Manutencao *m) {

    }
        
    int TecnicoManutencao::consultarManutencoesPendentes() const {

    }
        
    void TecnicoManutencao::registrarReparo(Manutencao *m, std::string r) {

    }
        
    void TecnicoManutencao::concluirManutencao(Manutencao *m) {

    }