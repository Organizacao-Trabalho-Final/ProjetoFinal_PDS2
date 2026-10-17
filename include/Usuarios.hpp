#ifndef USUARIOS_HPP
#define USUARIOS_HPP

#include "Pessoa.hpp"
#include <utility>
#include <vector>
#include <string>

class Usuarios {

    private :

        std::vector<std::pair<Pessoa*, int>> usuarios;

    public :

        Usuarios();

        void adicionarUsuario(Pessoa *usuario);
        void removerUsuario(const std::string & nome);
        Pessoa * buscarUsuarioNome(const std::string & nome) const;
        Pessoa * buscarUsuarioId(int id) const;
        
        std::vector<std::pair<Pessoa*, int>> getUsuarios() const;
        
        ~Usuarios();

};

#endif