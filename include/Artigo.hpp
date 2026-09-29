#ifndef ARTIGO_H
#define ARTIGO_H

#include <string>
#include "Obra.hpp"

class Artigo : public Obra {
    private:
        std::string area;
        int ano;

    public:
        Artigo(std::string t, std::string a, int id, std::string ar, int an);
        void setAno(int a);
        void setArea(std::string a);

        int getAno() const;
        std::string getArea() const;

        void printObra() const override;
};
#endif