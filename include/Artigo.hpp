#ifndef ARTIGO_HPP
#define ARTIGO_HPP

/**
 * @file Artigo.hpp
 * @brief Contrato da classe Artigo
 */
#include <string>
#include "Obra.hpp"

/**
 * @class Artigo
 * @brief Representa um artigo cadastrado no sistema.
 *
 * Herda os atributos e comportamentos gerais de Obra e acrescenta
 * área e ano de publicação.
 */
class Artigo : public Obra {
    private:
        std::string area;
        int ano;

    public:
        /**
         * @brief Constrói um objeto Artigo.
         * @param t Título do artigo.
         * @param a Autor do artigo.
         * @param id Identificação do artigo.
         * @param ar Área do conteúdo do artigo.
         * @param an Ano de publicação do artigo.
         */
        Artigo(const std::string &t, const std::string &a, int id, const std::string &ar, int an);

        /**
         * @brief Altera o ano de publicação do artigo.
         * @param a Novo ano.
         */
        void setAno(int a);

        /**
         * @brief Altera a área do artigo.
         * @param a Nova área.
         */
        void setArea(const std::string &a);

        /**
         * @brief Retorna o ano de publicação do artigo.
         * @return Ano de publicação.
         */
        int getAno() const;

        /**
         * @brief Retorna a área do artigo.
         * @return Área do artigo.
         */
        std::string getArea() const;

        /**
         * @brief Exibe as informações do artigo.
         */
        void printObra() const override;
};
#endif