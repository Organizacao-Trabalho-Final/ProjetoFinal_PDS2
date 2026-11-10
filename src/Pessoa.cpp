#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "Obra.hpp"
#include "Pessoa.hpp"
#include "Emprestimo.hpp"
#include "Tratamento.hpp"

    Pessoa::Pessoa(const std::string &n, const std::string &c):
    nome(n), CPF(c) {
        Tratamento tratamento;
        tratamento.isStringValido(nome, 1, 50, false, "Nome");
        tratamento.validarCPF(CPF);
    }

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
        
        std::vector<Emprestimo*> novos;
        novos.reserve(e.size());

        for (Emprestimo* novo : e) {
            if (novo != nullptr && std::find(novos.begin(), novos.end(), novo) == novos.end()) {
                novos.push_back(novo);
            }
        }
        for (Emprestimo* atual : emprestimos) {
            if (atual != nullptr && std::find(novos.begin(), novos.end(), atual) == novos.end()) {
                delete atual;
            }
        }
        emprestimos.swap(novos);
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
        for (size_t i=0; i<emprestimos.size(); i++) {
            if (emprestimos[i] == nullptr) {
                continue;
            }
            std::cout << "||======================================================||" << std::endl;
            emprestimos[i]->printEmprestimo();
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