#include <iostream>
#include <string>
#include "Bibliotecario.hpp"
#include "Data.hpp"
#include "Emprestimo.hpp"
#include "Manutencao.hpp"
#include "TecnicoManutencao.hpp"
#include "Obra.hpp"

using namespace std;

    Bibliotecario::Bibliotecario(std::string n, std::string c):
    Pessoa(n, c) {}
        
    Emprestimo* Bibliotecario::aprovarEmprestimo(Pessoa *p, Obra *o, Data d) {
        if(p == nullptr || o == nullptr)
            return nullptr;
        if(o->disponivel && p->getMaxEmorestimos() > p->getNumEmprestimos()){
            Emprestimo* e = new Emprestimo(*o, *p, d);
            e->setAtivo(true);
            //o->setDisponivel(false);

            return e;
        }
        return nullptr;
    }

    bool Bibliotecario::aprovarRenovacao(Emprestimo *e) {
        if(e->getAtraso() > 0 || e->getObra().getDisponivel() == 0 || e->isAtivo() == true)
            return false;
        return true;
    }

    void Bibliotecario::registrarDevolucao(Emprestimo *e) {
        if(e == nullptr)
            return;
        if(e->isAtivo){
            e->encerrarEmprestimo();
        }
    }

    void Bibliotecario::avaliarObra(Obra *o) {
        if(o->isDanificado()){
            cout << "Livro Danificado" << endl;
        }
    }

    Manutencao* Bibliotecario::encaminharManutencao(Obra *o, TecnicoManutencao *tm, string dano, Data i) {
        if(o == nullptr || tm == nullptr)
            return nullptr;
        if(o->isDanificado()){
            Manutencao* m = new Manutencao(o, tm, dano, i);
            tm->adicionarManutencao(m);
            return m;
        }
        return nullptr;
    }