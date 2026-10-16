#include <string>
#include <vector>
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

    }

    void Pessoa::registrarEmprestimo(Emprestimo *e) {
        
    }