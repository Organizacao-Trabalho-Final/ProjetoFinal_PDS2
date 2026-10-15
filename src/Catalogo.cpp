#include <string>
#include <vector>
#include "Catalogo.hpp"

    Catalogo::Catalogo(): obrasCadastradas() {}

    bool Catalogo::verificarDuplicata(int id) const {

        int temp_id;
        int tamanho = obrasCadastradas.size();

        for(int i = 0; i < tamanho; i++) {
            temp_id = obrasCadastradas[i].getID();

            if(temp_id == id)
                return true;
        }

        return false;

    }

    bool Catalogo::cadastrarObra(Obra *o) {

    }

    bool Catalogo::removerObra(int id) {

    }

    bool Catalogo::alterarTituloObra(int id, const std::string& t) {

    }

    bool Catalogo::alterarAutorObra(int id, const std::string& a) {

    }

    Obra* Catalogo::buscarPorTitulo(const std::string& t) const {

    }

    std::vector<Obra*> Catalogo::buscarPorAutor(const std::string& a) const {

    }

    std::vector<Obra*> Catalogo::listarObras() const {

    }