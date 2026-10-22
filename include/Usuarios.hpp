#ifndef USUARIOS_HPP
#define USUARIOS_HPP

#include <utility>
#include <vector>
#include <string>

class Pessoa;

class Usuarios {

    private :

        std::vector<std::pair<Pessoa*, int>> usuarios;

    public :

        Usuarios();

        void adicionarUsuario(Pessoa *usuario, int _id);
        void removerUsuario(const std::string & nome);
        Pessoa * buscarUsuarioNome(const std::string & nome) const;
        Pessoa * buscarUsuarioId(int id) const;
        Pessoa * buscarUsuarioCPF(std::string _cpf) const;
        std::pair<Pessoa*, int>& buscarUsuarioIndex(int index) ;
        
        const std::vector<std::pair<Pessoa*, int>>& getUsuarios() const;
        
        std::string getOcupacao(std::string _cpf) const;
        std::string getOcupacao(int index) const;

        ~Usuarios() = default;

};

#endif