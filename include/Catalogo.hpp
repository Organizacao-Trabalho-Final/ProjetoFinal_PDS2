#ifndef CATALOGO_H
#define CATALOGO_H

#include <string>
#include <vector>
#include "Obra.hpp"

class Catalogo {
private:
    std::vector<Obra*> obrasCadastradas;
    bool verificarDuplicata(int id) const;

public:
    Catalogo();
    ~Catalogo();

    bool cadastrarObra(Obra* obra);
    Obra* buscarPorTitulo(const std::string& titulo) const;
    Obra* buscarPorAutor(const std::string& autor) const;
    bool alterarTituloObra(int id, const std::string& novoTitulo);
    bool alterarAutorObra(int id, const std::string& novoAutor);
    bool removerObra(int id);
    std::vector<Obra*> listarObras() const;
};

#endif