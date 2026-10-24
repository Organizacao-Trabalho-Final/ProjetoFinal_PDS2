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
        if(o == nullptr) {
            //throw std::invalid_argument("Ponteiro para obra Nulo");
            return false;
        }
        int temp_id = o->getID();
        bool existe = verificarDuplicata(temp_id);
        if(existe) {
            //throw std::invalid_argument("Essa obra já está no catálogo");
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
                //delete obrasCadastradas[i];
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
        int temp_id;
        int tamanho = obrasCadastradas.size();
        for(int i = 0; i < tamanho; i++) {
            temp_id = obrasCadastradas[i]->getID();
            if(id == temp_id) {
                obrasCadastradas[i]->setAutor(a);
                return true;
            }            
        }
        return false;
    }

    Obra* Catalogo::buscarPorTitulo(const std::string& t) const {
        std::string temp_t;
        int tamanho = obrasCadastradas.size();
        for(int i = 0; i < tamanho; i++) {
            temp_t = obrasCadastradas[i]->getTitulo();
            if(temp_t == t) {
                return obrasCadastradas[i];
            }
        }
        //throw std::invalid_argument("Obra não encontrada!");
        return nullptr;
    }

    Obra* Catalogo::buscarPorId(int _id) const {

        int temp_id;
        int tamanho = obrasCadastradas.size();
        for(int i = 0; i < tamanho; i++) {
            temp_id = obrasCadastradas[i]->getID();
            if(temp_id == _id) {
                return obrasCadastradas[i];
            }
        }
        //throw std::invalid_argument("Obra não encontrada!");
        return nullptr;

    }


    std::vector<Obra*> Catalogo::buscarPorAutor(const std::string& a) const {
        std::string temp_a;
        std::vector<Obra*> obrasAutor(0);
        int tamanho = obrasCadastradas.size();
        for(int i = 0; i < tamanho; i++) {
            temp_a = obrasCadastradas[i]->getAutor();
            if(temp_a == a) {
                obrasAutor.push_back(obrasCadastradas[i]);
            }
        }
        return obrasAutor;
        //throw std::invalid_argument("Autor não encontrada!");
    }

    std::vector<Obra*> Catalogo::listarObras() const {
        int tamanho = obrasCadastradas.size();
        for(int i = 0; i < tamanho; i++) {
            std::cout << "||================================================||" << std::endl;
            obrasCadastradas[i]->printObra();
            std::cout << "||================================================||" << std::endl;
        }
        return obrasCadastradas;
    }
