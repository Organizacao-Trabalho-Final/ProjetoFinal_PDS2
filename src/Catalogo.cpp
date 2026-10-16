#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include "Catalogo.hpp"

    Catalogo::Catalogo(): obrasCadastradas() {}

    bool Catalogo::verificarDuplicata(int id) const {
        int temp_id;
        int tamanho = obrasCadastradas.size();
        for(int i = 0; i < tamanho; i++) {
            temp_id = obrasCadastradas[i]->getID();
            if(temp_id == id)
                return true;
        }
        return false;
    }

    bool Catalogo::cadastrarObra(Obra *o) {
        int temp_id = o->getID();
        bool existe = verificarDuplicata(temp_id);
        if(existe) {
            throw std::invalid_argument("Essa obra já está no catálogo");
            return false;
        }
        obrasCadastradas.push_back(o);
        return true;
    }

    bool Catalogo::removerObra(int id) {
        int temp_id;
        int tamanho = obrasCadastradas.size();
        for(int i = 0; i < tamanho; i++) {
            temp_id = obrasCadastradas[i]->getID();
            if(temp_id == id) {
                obrasCadastradas.erase(obrasCadastradas.begin() + i);
                return true;
            }
        }
        return false;
    }

    bool Catalogo::alterarTituloObra(int id, const std::string& t) {
        int temp_id;
        int tamanho = obrasCadastradas.size();
        for(int i = 0; i < tamanho; i++) {
            temp_id = obrasCadastradas[i]->getID();
            if(id == temp_id) {
                obrasCadastradas[i]->setTitulo(t);
                return true;
            }            
        }
        return false;
    }

    bool Catalogo::alterarAutorObra(int id, const std::string& a) {
        
    }

    Obra* Catalogo::buscarPorTitulo(const std::string& t) const {

    }

    std::vector<Obra*> Catalogo::buscarPorAutor(const std::string& a) const {

    }

    std::vector<Obra*> Catalogo::listarObras() const {

    }