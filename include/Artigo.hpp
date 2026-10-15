#ifndef ARTIGO_H
#define ARTIGO_H

/**
 * @file Artigo.hpp
 * @brief Declaração da classe Artigo
 * @date 2026-10-15
 */
#include <string>
#include "Obra.hpp"

/**
 * @class Artigo
 * @brief Cria a estrutura da classe Artigo
 */
class Artigo : public Obra {
    private:
        std::string area;
        int ano;

    public:
        /**
         * @brief Construtor da classe Artigo
         * @param t String contendo o título do artigo
         * @param a String contendo o nome do autor do artigo
         * @param id Identificação do Artigo
         * @param ar Área do conteúdo do artigo
         * @param an Ano de publicação do artigo
         */
        Artigo(std::string t, std::string a, int id, std::string ar, int an);

        /**
         * @brief Usado para mudar o valor em "ano"
         * @param a O ano que ficará armazenado em "ano"
         */
        void setAno(int a);

        /**
         * @brief Usado para mudar o valor armazendao em "area"
         * @param a String com a área do artigo
         */
        void setArea(std::string a);

        /**
         * @brief Usado para ler o que está em "ano"
         * @return Retorna "ano"
         */
        int getAno() const;

        /**
         * @brief Usado para ler a string armazenada em "ano"
         * @return Retorna "area"
         */
        std::string getArea() const;

        /**
         * @brief Método virtual usado para imprimir os dados de uma obra
         */
        void printObra() const override;
};
#endif