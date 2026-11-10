#include <string>
#include "Bibliotecario.hpp"
#include "Data.hpp"
#include "Emprestimo.hpp"
#include "Manutencao.hpp"
#include "TecnicoManutencao.hpp"
#include "Obra.hpp"
#include "Estudante.hpp"
#include "Professor.hpp"

    Bibliotecario::Bibliotecario(const std::string &n, const std::string &c):
    Pessoa(n, c) {}
        
    Emprestimo* Bibliotecario::aprovarEmprestimo(Pessoa *p, Obra *o, Data d) {
        if (p == nullptr || o == nullptr) {
            return nullptr;
        }
        if (dynamic_cast<Estudante*>(p) == nullptr && dynamic_cast<Professor*>(p) == nullptr) {
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
        if (e == nullptr || !e->isAtivo() || !e->isRenovacaoSolicitada()) {
            return false;
        }
        if (e->getAtraso(hj) > 0) {
            e->cancelarSolicitacaoRenovacao();
            return false;
        }
        return e->renovarEmprestimo();
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
        if (!o->isDanificado() || !o->isDisponivel() || o->isEmManutencao() || dano.find_first_not_of(" \t\n\r") == std::string::npos) {
            return nullptr;
        }
        Manutencao* m = new Manutencao(o, tm, dano, i);
        tm->adicionarManutencao(m);
        o->setDisponivel(false);
        return m;
    }