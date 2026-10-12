#ifndef ESTUDANTE_H
#define ESTUDANTE_H

/**
 * @file Estudante.hpp
 * @brief Declaração da classe Estudante
 * @date 2026-10-12
 */
#include <string>
#include "Pessoa.hpp"

/**
 * @class Estudante
 * @brief Cria a estrutura da classe Estudante
 */
class Estudante : public Pessoa {
    private:
        std::string curso;
        std::string matricula;

    public:
        /**
         * @brief Construtor de "Estudante"
         * @param n String a ser passada para "nome", herdada de Pessoa
         * @param cpf String a ser passada para "CPF", herdada de Pessoa
         * @param c String a ser passada para "curso"
         * @param m String a ser passada para "matricula"
         */
        Estudante(std::string n, std::string cpf, std::string c, std::string m);

        /**
         * @brief Usado para ler a string armazenada em "curso"
         * @return Retorna a variável "curso"
         */
        std::string getCurso() const;

        /**
         * @brief Usado para ler a string armazenada em "matricula"
         * @return Retorna a variável "matricula"
         */
        std::string getMatricula() const;

        /**
         * @brief Usado para ler o prazo do empréstimo daquele estudante
         * @return Retorna a quantidade de dias que o estudante ainda tem de prazo
         * @note método virtual, de Pessoa em que o valor não pode ser alterado
         */
        int getPrazo() const override;

        /**
         * @brief Usado para ler o valor máximo de emp´restimos daquele estudante
         * @return Retorna a quantidade máximade empréstimos que aquele estudante fez 
         * @note método virtual, de Pessoa em que o valor não pode ser alterado
         */
        int getMaxEmprestimos() const override;

        /**
         * @brief Método booleano que diz se uma obra está disponível para empréstimos
         * @param o Um ponteiro para Obra como parâmetro que não pode ser alterado pela função
         * @return Retorna true se a Obra esiver disponível ou false caso contrário
         */
        bool podeEmprestar(const Obra *o) const override;
};
#endif