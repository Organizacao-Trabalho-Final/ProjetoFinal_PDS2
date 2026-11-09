#ifndef LIVRO_HPP
#define LIVRO_HPP

/**
 * @file Livro.hpp
 * @brief Contrato da classe Livro.
 */
#include <string>
#include "Obra.hpp"

/**
 * @class Livro
 * @brief Representa um livro cadastrado no sistema.
 *
 * Herda os atributos e comportamentos gerais de Obra e acrescenta
 * gênero e edição.
 */
class Livro : public Obra {
    private:
        std::string genero;
        int edicao;

    public:
        /**
         * @brief Constrói um objeto Livro.
         * @param t Título do livro.
         * @param a Autor do livro.
         * @param id Identificador da obra.
         * @param g Gênero do livro.
         * @param e Edição do livro.
         * @throws std::invalid_argument se o gênero estiver vazio ou a edição não for positiva.
         */
        Livro(const std::string &t, const std::string &a, int id, const std::string &g, int e);

        /**
         * @brief Altera a edição do livro.
         * @param e Nova edição, que deve ser maior que zero.
         * @throws std::invalid_argument se o a edição for menor que 0.
         */
        void setEdicao(int e);

        /**
         * @brief Altera o gênero do livro.
         * @param g Novo gênero do livro.
         * @throws std::invalid_argument se o gênero estiver vazio.
         */
        void setGenero(const std::string &g);

        /**
         * @brief Retorna a edição do livro.
         * @return Edição do livro.
         */
        int getEdicao() const;

        /**
         * @brief Retorna o gênero do livro.
         * @return Gênero do livro.
         */
        std::string getGenero() const;

        /**
         * @brief Exibe as informações do livro.
         */
        void printObra() const override;
};
#endif