#ifndef PROFESSOR_H
#define PROFESSOR_H

/**
 * @file Professor.hpp
 * @brief Declaração da classe Professor
 * @date 2026-10-12
 */
#include <string>
#include "Pessoa.hpp"

/**
 * @class Professor
 * @brief Cria a estrutura da classe Professor
 */
class Professor : public Pessoa {
    private:
        std::string area;

    public:
        /**
         * @brief Contrutor da classe Professor
         * @param n string a ser passada para "nome", herdada de Pessoa
         * @param c string a ser passada para "CPF", herdada de Pessoa
         * @param a string a ser passada para "area"  
         */
        Professor(std::string n, std::string c, std::string a);

        /**
         * @brief Usado para ler a string armazenada em area
         * @return Retorna a variável "area"
         */
        std::string getArea() const;

        /**
         * @brief Usado para ler o prazo que o professor tem para a devolução da obra
         * @return O valor em dias do prazo do empréstimo do professor
         */
        int getPrazo() const override;

        /**
         * @brief usado para ler o valor máximo de empréstimos
         * @return retorna o valor máximo de empréstimos da pessoa
         * @note Método virtual da classe Pessoa
         */
        int getMaxEmprestimos() const override;

        /**
         * 
         *//**
         * @brief método virtual constante que verifica se a pessoa pode pegar aquela obra eprestada
         * @param o um ponteiro para obra
         * @return retorna true se puder e false, caso contrário
         * @note Método virtual da classe Pessoa
         */
        bool podeEmprestar(const Obra *o) const override;
};
#endif