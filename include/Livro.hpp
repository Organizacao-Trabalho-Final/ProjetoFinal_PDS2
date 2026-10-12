#ifndef LIVRO_H
#define LIVRO_H


/**
 * @file Livro.hpp
 * @brief declaração da classe Livro
 * @date 2026-10-11
 */
#include <string>
#include "Obra.hpp"

/**
 * @class Livro
 * @brief cria a estrutura da classe Livro como herança de Obra
 */
class Livro : public Obra {
    private:
        std::string genero;
        int edicao;

    public:
        /**
         * @brief Construtor de "Livro"
         * @param t string que será passado para "titulo"
         * @param a string que será passada para "autor"
         * @param id valor que será passado para "id"
         * @param g valor que será passado para "genero"
         * @param e valor que será passado para "edição"
         */
        Livro(std::string t, std::string a, int id, std::string g, int e);

        /**
         * @brief setter que faz a variável "edicao" receber o valor passado por parâmetro
         * @param e valor passado para ser associado a variável "edicao"
         */
        void setEdicao(int e);

        /**
         * @brief setter que faz a variável "genero" receber o valor passado por parâmetro
         * @param g valor passado para ser associado a variável "genero"
         */
        void setGenero(std::string g);

        /**
         * @brief usado para ler o valor constante armazenado em edicao
         * @return retorna o valor da variavel "edicao"
         */
        int getEdicao() const;

        /**
         * @brief usado para ler a string armazenada em "genero"
         * @return retorna a string armazenada em "genero"
         */
        std::string getGenero() const;

        /**
         * @brief método virtual puro de "Obra" que imprime as informações da obra
         * @note necessário implementar em todas as classes derivadas
         */
        void printObra() const override;
};
#endif