#ifndef LIVRO_H
#define LIVRO_H

#include <string>
#include "Obra.hpp"

class Livro : public Obra {
    private:
        std::string genero;
        int edicao;

    public:
        Livro(std::string t, std::string a, int id, std::string g, int e);
        void setEdicao(int e);
        void setGenero(std::string g);

        std::string getGenero() const;
        int getEdicao() const;

        void printObra() const override;
};
#endif