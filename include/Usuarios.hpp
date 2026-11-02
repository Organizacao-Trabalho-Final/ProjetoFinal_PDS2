#ifndef USUARIOS_HPP
#define USUARIOS_HPP

/**
 * @file Usuarios.hpp
 * @brief Contrato da classe Usuario.
 */

#include <utility>
#include <vector>
#include <string>

class Pessoa;

/**
 * @class Usuarios
 * @brief Gerencia o cadastro e a consulta dos usuários do sistema.
 */
class Usuarios {

    private:
        std::vector<std::pair<Pessoa*, int>> usuarios;

    public:
        /**
         * @brief Constrói um objeto Usuarios.
         */
        Usuarios();

        /**
         * @brief Adiciona um usuário ao cadastro.
         * @param usuario Ponteiro para o objeto Pessoa a ser adicionado.
         * @param id ID do usuário a ser adicionado.
         */
        void adicionarUsuario(Pessoa *p, int id);

        /**
         * @brief Remove o primeiro usuário encontrado com o nome informado.
         * @param nome Nome do usuário a ser removido.
         */
        void removerUsuario(const std::string &nome);

        /**
         * @brief Busca um usuário pelo nome.
         * @param nome Nome do usuário a ser buscado.
         * @return Ponteiro para o objeto Pessoa encontrado ou nullptr se não encontrado.
         */
        Pessoa *buscarUsuarioNome(const std::string &nome) const;

        /**
         * @brief Busca um usuário pelo ID.
         * @param id ID do usuário a ser buscado.
         * @return Ponteiro para o objeto Pessoa encontrado ou nullptr se não encontrado.
         */
        Pessoa *buscarUsuarioId(const int id) const;

        /**
         * @brief Busca um usuário pelo CPF.
         * @param cpf CPF do usuário a ser buscado.
         * @return Ponteiro para o objeto Pessoa encontrado ou nullptr se não encontrado.
         */
        Pessoa * buscarUsuarioCPF(const std::string &cpf) const;

        /**
         * @brief Busca um usuário pelo índice no vetor de usuários.
         * @param index Índice do usuário a ser buscado.
         * @return Par contendo o ponteiro para Pessoa e seu ID, ou {nullptr, -1} se não encontrado.
         */
        std::pair<Pessoa*, int> buscarUsuarioIndex(int index) const;

        /**
         * @brief Retorna o vetor de usuários.
         * @return Referência constante para o vetor de pares de ponteiros para Pessoa e seus respectivos IDs.
         */
        const std::vector<std::pair<Pessoa*, int>>& getUsuarios() const;

        /**
         * @brief Retorna a ocupação de um usuário pelo CPF.
         * @param cpf CPF do usuário.
         * @return Ocupação do usuário como string.
         */
        std::string getOcupacao(const std::string &cpf) const;

        /**
         * @brief Retorna a ocupação de um usuário pelo índice no vetor de usuários
         * @param index Índice do usuário
         * @return Ocupação do usuário como string
         */
        std::string getOcupacao(int index) const;

        // Impedem cópias superficiais dos ponteiros pertencentes à classe.
        Usuarios(const Usuarios&) = delete;
        Usuarios& operator=(const Usuarios&) = delete;

        /**
         * @brief Destrutor da classe Usuarios.
         * Libera a memória dos objetos Pessoa cadastrados.
         */
        ~Usuarios();
};
#endif