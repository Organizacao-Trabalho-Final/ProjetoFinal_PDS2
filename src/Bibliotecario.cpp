#include <string>
#include "Bibliotecario.hpp"
#include "Data.hpp"
#include "Emprestimo.hpp"
#include "Manutencao.hpp"
#include "TecnicoManutencao.hpp"
#include "Obra.hpp"

    Bibliotecario::Bibliotecario(std::string n, std::string c):
    Pessoa(n, c) {}
        
    Emprestimo* Bibliotecario::aprovarEmprestimo(Pessoa *p, Obra *o, Data d) {
        if (p == nullptr || o == nullptr) {
            return nullptr;
        }
        if (!o->isDanificado() && p->podeEmprestar(o)) {
            Emprestimo* e = new Emprestimo(*o, *p, d);
            p->registrarEmprestimo(e);
            o->setDisponivel(false);
            return e;
        }
        return nullptr;
    }

    bool Bibliotecario::aprovarRenovacao(Emprestimo *e, Data hj) {
        if (e == nullptr || !e->isAtivo() || e->getAtraso(hj) > 0) {
            return false;
        } else {
            e->renovarEmprestimo();
            return true;
        }
    }

    void Bibliotecario::registrarDevolucao(Emprestimo *e) {
        if (e == nullptr || !e->isAtivo()) {
            return;
        }
        e->encerrarEmprestimo();
        Obra &o = e->getObra();
        o.setDisponivel(!o.isDanificado());
    }

    bool Bibliotecario::avaliarObra(const Obra *o) const {
        return (o != nullptr && o->isDanificado());
    }

    Manutencao* Bibliotecario::encaminharManutencao(Obra *o, TecnicoManutencao *tm, std::string dano, Data i) {
        if (o == nullptr || tm == nullptr) {
            return nullptr;
        }
        if (o->isDanificado()) {
            Manutencao* m = new Manutencao(o, tm, dano, i);
            tm->adicionarManutencao(m);
            o->setDisponivel(false);
            return m;
        }
        return nullptr;
    }