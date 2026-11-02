#ifndef OBRA_HPP
#define OBRA_HPP

/**
 * @file Obra.hpp
 * @brief Contrato da classe Obra.
 */

#include <string>

/**
 * @class Obra
 * @brief Representa uma obra cadastrada no sistema da biblioteca.
 */
class Obra {

    private:
        std::string titulo, autor;
        int id;
        bool disponivel, danificado;

    public:

        /**
         * @brief Constrói um objeto Obra.
         * @param t Título da obra.
         * @param a Autor da obra.
         * @param id Identificação da obra.
         */
        Obra(const std::string &t, const std::string &a, int id);

        /**
         * @brief Substitui a disponibilidade da obra.
         * @param d Valor de "disponivel".
         */
        void setDisponivel(bool d);

        /**
         * @brief Substitui o dano da obra.
         * @param d Valor de "danificado".
         */
        void setDanificado(bool d);

        /**
         * @brief Substitui o título da obra.
         * @param t String do título.
         */
        void setTitulo(const std::string &t);

        /**
        * @brief Substitui o autor da obra.
        * @param a String do autor.
         */
        void setAutor(const std::string &a);

        /**
         * @brief Retorna o título da obra.
         * @return String "titulo".
         */
        std::string getTitulo() const;

        /**
         * @brief Retorna o autor da obra.
         * @return String "autor".
         */
        std::string getAutor() const;

        /**
         * @brief Retorna a identificação da obra.
         * @return Inteiro "id".
         */
        int getID() const;

        /**
         * @brief Retorna disponibilidade da obra.
         * @return true se estiver disponível, false se não estiver.
         */
        bool isDisponivel() const;

        /**
         * @brief Retorna o dano da obra.
         * @return true se estiver danificada, false se não estiver.
         */
        bool isDanificado() const;

        /**
         * @brief Exibe as informações específicas da obra.
         * @note Método virtual puro, cada classe derivada deve sobrescrever essa função.
         */
        virtual void printObra() const = 0;
        
        /**
         * @brief Destrutor virtual da classe Obra.
         */
        virtual ~Obra() = default;
};
#endif