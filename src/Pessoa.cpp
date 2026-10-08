#include <string>
#include <vector>
#include "Pessoa.hpp"

    Pessoa::Pessoa(std::string n, std::string c):
    nome(n), CPF(c), emprestimos() {}

    std::string Pessoa::getNome() const {

    }

    std::string Pessoa::getCPF() const {

    }

    int Pessoa::getPrazo() const {

    }

    int Pessoa::getMaxEmprestimos() const {

    }

    bool Pessoa::podeEmprestar(const Obra *o) const {

    }

    std::vector<Emprestimo*> Pessoa::consultarAtivos() {

    }

    std::vector<Emprestimo*> Pessoa::historicoEmprestimos() {

    }

    void Pessoa::registrarEmprestimo(Emprestimo *e) {
        
    }