#include <iostream>
#include <exception>
#include "Dados.hpp"
#include "Usuarios.hpp"
#include "Catalogo.hpp"
#include "Interface.hpp"

int main() {
    try {
        Dados dados(new Usuarios(), new Catalogo());
        dados.carregarDados();

        Interface interface(&dados);
        interface.executar();

        dados.salvarDados();
    } catch (const std::exception &e) {
        std::cerr << "Erro durante a execução: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}