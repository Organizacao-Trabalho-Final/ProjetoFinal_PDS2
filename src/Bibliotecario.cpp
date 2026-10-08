#include <string>
#include "Bibliotecario.hpp"
#include "Data.hpp"

    Bibliotecario::Bibliotecario(std::string n, std::string c):
    Pessoa(n, c) {}
        
    Emprestimo* Bibliotecario::aprovarEmprestimo(Pessoa *p, Obra *o, Data d) {

    }

    bool Bibliotecario::aprovarRenovacao(Emprestimo *e) {

    }

    void Bibliotecario::registrarDevolucao(Emprestimo *e) {

    }

    void Bibliotecario::avaliarObra(Obra *o) {

    }

    Manutencao* Bibliotecario::encaminharManutencao(Obra *o, TecnicoManutencao *tm, std::string dano, Data i) {
        
    }