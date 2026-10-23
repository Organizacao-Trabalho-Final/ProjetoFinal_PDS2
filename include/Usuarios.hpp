#ifndef USUARIOS_HPP
#define USUARIOS_HPP

/**
 * @file Usuarios.hpp
 * @brief Declaração da classe Usuarios
 * @date 2026-10-23
 */

#include <utility>
#include <vector>
#include <string>

/**
 * @class Artigo
 * @brief Cria a estrutura da classe Usuarios
 */


class Usuarios {

    private :
        /**
         * @brief Vetor de pares de ponteiros para Pessoa e seus respectivos IDs
         */
        std::vector<std::pair<Pessoa*, int>> usuarios;

    public :
        /**
         * @brief Construtor da classe Usuarios
         */
        Usuarios();
        /**
         * @brief Adiciona um usuário ao vetor de usuários
         * @param usuario Ponteiro para o objeto Pessoa a ser adicionado
         * @param _id ID do usuário a ser adicionado
         */
        void adicionarUsuario(Pessoa *usuario, int _id);
        /**
         * @brief Remove um nome e seu ID do vetor de usuários
         * @param nome Nome do usuário a ser removido
         */
        void removerUsuario(const std::string & nome);
        /**
         * @brief Busca um usuário pelo nome
         * @param nome Nome do usuário a ser buscado
         * @return Ponteiro para o objeto Pessoa encontrado ou nullptr se não encontrado
         */
        Pessoa * buscarUsuarioNome(const std::string & nome) const;
        /**
         * @brief Busca um usuário pelo ID
         * @param id ID do usuário a ser buscado
         * @return Ponteiro para o objeto Pessoa encontrado ou nullptr se não encontrado
         */
        Pessoa * buscarUsuarioId(int id) const;
        /**
         * @brief Busca um usuário pelo CPF
         * @param _cpf CPF do usuário a ser buscado
         * @return Ponteiro para o objeto Pessoa encontrado ou nullptr se não encontrado
         */
        Pessoa * buscarUsuarioCPF(std::string _cpf) const;
        /**
         * @brief Busca um usuário pelo índice no vetor de usuários
         * @param index Índice do usuário a ser buscado
         * @return Referência para o par de ponteiro para Pessoa e ID encontrado ou um par com nullptr e -1 se não encontrado
         */
        std::pair<Pessoa*, int>& buscarUsuarioIndex(int index) ;
        /**
         * @brief Retorna o vetor de usuários
         * @return Referência constante para o vetor de pares de ponteiros para Pessoa e seus respectivos IDs
         */
        const std::vector<std::pair<Pessoa*, int>>& getUsuarios() const;
        /**
         * @brief Retorna a ocupação de um usuário pelo CPF
         * @param _cpf CPF do usuário
         * @return Ocupação do usuário como string
         */
        std::string getOcupacao(std::string _cpf) const;
        /**
         * @brief Retorna a ocupação de um usuário pelo índice no vetor de usuários
         * @param index Índice do usuário
         * @return Ocupação do usuário como string
         */
        std::string getOcupacao(int index) const;
        /**
         * @brief Destrutor da classe Usuarios
         */
        ~Usuarios() = default;

};

#endif