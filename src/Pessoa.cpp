#include <string>
#include <vector>
#include <iostream>
#include "Obra.hpp"
#include "Pessoa.hpp"
#include "Emprestimo.hpp"

    Pessoa::Pessoa(std::string n, std::string c):
    nome(n), CPF(c), emprestimos() {}

    std::string Pessoa::getNome() const {
        return nome;
    }

    std::string Pessoa::getCPF() const {
        return CPF;
    }

    int Pessoa::getPrazo() const {
        //return o que? eu não sei!! Que prazo!? 
        // Do empréstimo?
        // Mas pessoa tem um vetor de emptréstimos, como vou retornar apenas um 'int'??!?!
    }

    int Pessoa::getMaxEmprestimos() const {
        return emprestimos.size();
    }

    const std::vector<Emprestimo*>& Pessoa::getEmprestimos() const {
        return emprestimos;
    }

    bool Pessoa::podeEmprestar(const Obra *o) const {
        return o->isDisponivel();
    }

    std::vector<Emprestimo*> Pessoa::consultarAtivos() {
        bool ativo;
        std::vector<Emprestimo*> ativos(0);
        for(Emprestimo * e : emprestimos) {
            ativo = e->isAtivo();
            if(ativo) {
                ativos.push_back(e);
            }
        }
        return ativos;
    }

    std::vector<Emprestimo*> Pessoa::historicoEmprestimos() {
        for(Emprestimo * e : emprestimos) {
            std::cout << "||======================================================||" << std::endl;
            e->printEmprestimo();
            std::cout << "||======================================================||" << std::endl;
        }
        return emprestimos;
    }

    void Pessoa::registrarEmprestimo(Emprestimo *e) {
        if(e == nullptr) {
            throw std::invalid_argument("Ponteiro para Emprestimo nulo -> e = 'nullptr'");
        }
        emprestimos.push_back(e);
    }