#include <string>
#include <vector>
#include "Catalogo.hpp"

    Catalogo::Catalogo(): obrasCadastradas() {}

    bool Catalogo::verificarDuplicata(int id) const {
        for (Obra *o : obrasCadastradas) {
            if (o != nullptr && o->getID() == id) {
                return true;
            }
        }
        return false;
    }

    bool Catalogo::cadastrarObra(Obra *o) {
        if (o == nullptr || verificarDuplicata(o->getID())) {
            return false;
        }
        obrasCadastradas.push_back(o);
        return true;
    }

    bool Catalogo::removerObra(int id) {
        for (auto it = obrasCadastradas.begin(); it != obrasCadastradas.end(); ++it) {
            if (*it != nullptr && (*it)->getID() == id) {
                delete *it;
                obrasCadastradas.erase(it);
                return true;
            }
        }
        return false;
    }

    Obra* Catalogo::buscarPorTitulo(const std::string& t) const {
        for (Obra *o : obrasCadastradas) {
            if (o != nullptr && o->getTitulo() == t) {
                return o;
            }
        }
        return nullptr;
    }

    Obra* Catalogo::buscarPorId(int id) const {
        for (Obra *o : obrasCadastradas) {
            if (o != nullptr && o->getID() == id) {
                return o;
            }
        }
        return nullptr;
    }

    std::vector<Obra*> Catalogo::buscarPorAutor(const std::string& a) const {
        std::vector<Obra*> obrasAutor;
        for (Obra *o : obrasCadastradas) {
            if (o != nullptr && o->getAutor() == a) {
                obrasAutor.push_back(o);
            }
        }
        return obrasAutor;
    }

    const std::vector<Obra*>& Catalogo::listarObras() const {
        return obrasCadastradas;
    }

    Catalogo::~Catalogo() { // Liberação de memória
    for (Obra *obra : obrasCadastradas) {
        delete obra;
    }
}
