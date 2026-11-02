#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include "Obra.hpp"
#include "Pessoa.hpp"
#include "Emprestimo.hpp"

    Pessoa::Pessoa(const std::string &n, const std::string &c):
    nome(n), CPF(c), emprestimos(0) {}

    std::string Pessoa::getNome() const {
        return nome;
    }

    std::string Pessoa::getCPF() const {
        return CPF;
    }

    int Pessoa::getPrazo() const {
        return 0;
    }

    int Pessoa::getMaxEmprestimos() const {
        return 0;
    }

    int Pessoa::getNumEmprestimos() const {
        return static_cast<int>(emprestimos.size());
    }

    int Pessoa::getEmprestimosAtivos() const {
        int count = 0;
        for (Emprestimo* e : emprestimos) {
            if (e != nullptr && e->isAtivo()) 
                count++;
        }
        return count;
    }

    void Pessoa::setEmprestimos(std::vector<Emprestimo*> &e) {
        if (&e == &emprestimos) {
            return;
        }
        for (Emprestimo *atual : emprestimos) {
            delete atual;
        }
        emprestimos.clear();
        for (Emprestimo *novo : e) {
            if (novo != nullptr) {
                emprestimos.push_back(novo);
            }
        }
    }

    const std::vector<Emprestimo*>& Pessoa::getEmprestimos() const {
        return emprestimos;
    }

    bool Pessoa::podeEmprestar(const Obra *o) const {
        return (o != nullptr && o->isDisponivel());
    }

    std::vector<Emprestimo*> Pessoa::consultarAtivos() const {
        std::vector<Emprestimo*> ativos;
        for (Emprestimo * e : emprestimos) {
            if (e != nullptr && e->isAtivo()) {
                ativos.push_back(e);
            }
        }
        return ativos;
    }

    std::vector<Emprestimo*> Pessoa::historicoEmprestimos() const {
        for (Emprestimo *e : emprestimos) {
            if (e == nullptr) {
                continue;
            }
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
        for (Emprestimo *atual : emprestimos) {
            if (atual == e) {
                return;
            }
        }
        emprestimos.push_back(e);
    }

    Pessoa::~Pessoa() { // Liberação de memória
        for (Emprestimo *e : emprestimos) {
            delete e;
        }
    }