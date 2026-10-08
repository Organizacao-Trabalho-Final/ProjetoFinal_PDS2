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

    bool cadastrarObra(Obra *o);
    bool removerObra(int id);
    bool alterarTituloObra(int id, const std::string& t);
    bool alterarAutorObra(int id, const std::string& a);

    Obra* buscarPorTitulo(const std::string& t) const;
    std::vector<Obra*> buscarPorAutor(const std::string& a) const;
    std::vector<Obra*> listarObras() const;

    ~Catalogo() = default;
};
#endif