#ifndef OBRA_H
#define OBRA_H

/**
 * @file Obra.hpp
 * @brief Declaração da classe Obra
 * @date 2026-10-11
 */

#include <string>

/**
 * @class Obra
 * @brief Cria a estrutura da classe obra
 */
class Obra {

    private:
        std::string titulo, autor;
        int id;
        bool disponivel, danificado;

    public:

        /**
         * @brief Construtor de Obra
         * @param t o título da obra
         * @param a o autor da obra
         * @param id a identificação da obra
         */
        Obra(std::string t, std::string a, int id);

        /**
         * @brief setter que faz a variável "disponível" receber o valor passado por parâmetro
         * @param d o valor de "disponivel"
         */
        void setDisponivel(bool d);

        /**
         * @brief setter que faz a variável "danificado" receber o valor passado por parâmetro
         * @param d o valor de "danificado"
         */
        void setDanificado(bool d);

        /**
         * @brief setter que faz a variável "titulo" receber o valor passado por parâmetro
         * @param t string passada para ser o valor de "titulo"
         */
        void setTitulo(std::string t);

        /**
         * @brief setter que faz a variável "autor" receber o valor passado por parâmetro
         * @param a string passada para ser o valor de "título"
         */
        void setAutor(std::string a);

        /**
         * @brief getter usado para ler a string armazenada em "titulo"
         * @return a string "titulo"
         */
        std::string getTitulo() const;

        /**
         * @brief getter usado para ler a string armazenada em "autor"
         * @return retorna a string "autor"
         */
        std::string getAutor() const;

        /**
         * @brief getter usado para ler o valor armazenado na variável "id"
         * @return retorna o inteiro "id"
         */
        int getID() const;

        /**
         * @brief informa se a obra está disponível
         * @return retorna true se estiver disponível e false, caso contrário
         */
        bool isDisponivel() const;

        /**
         * @brief informa se uma obra está danificada
         * @return retorna true a obra estiver danificada e true, caso contrário
         */
        bool isDanificado() const;

        /**
         * @brief imprime as informações da obra
         * @note é um método virtual puro, ou seja as suas classes derivadas devem implementar essa função
         */
        virtual void printObra() const = 0;
        
        /**
         * @brief libera a memória alocada na base
         * @note necessário para herança polimórfica
         */
        virtual ~Obra() = default;
};
#endif