#ifndef OBRA_H
#define OBRA_H

#include <iostream>
#include <string>

class Obra {
    private:
        std::string titulo, autor;
        int id;
        bool disponivel, danificado;

    public:
        Obra(std::string t, std::string a, int id);
        void setDisponivel(bool d);
        void setDanificado(bool d);

        std::string getTitulo() const;
        std::string getAutor() const;
        int getID() const;
        bool isDisponivel() const;
        bool isDanificado() const;

        virtual void printObra() const = 0;
        
        virtual ~Obra() = default;
};
#endif