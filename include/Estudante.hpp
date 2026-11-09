#ifndef ESTUDANTE_HPP
#define ESTUDANTE_HPP

/**
 * @file Estudante.hpp
 * @brief Contrato da classe Estudante
 */
#include <string>
#include "Pessoa.hpp"

/**
 * @class Estudante
 * @brief Representa um estudante cadastrado no sistema da biblioteca.
 *
 * Herda os dados e comportamentos gerais de Pessoa e acrescenta
 * curso, matrícula e regras específicas de empréstimo.
 */
class Estudante : public Pessoa {
    private:
        std::string curso;
        std::string matricula;

    public:
        /**
         * @brief Constrói um objeto Estudante.
         * @param n Nome do estudante.
         * @param cpf CPF do estudante.
         * @param c Curso do estudante.
         * @param m Matrícula do estudante.
         * @throws std::invalid_argument se curso ou matrícula estiverem vazios.
         */
        Estudante(const std::string &n, const std::string &cpf, const std::string &c, const std::string &m);

        /**
         * @brief Retorna o curso do estudante.
         * @return Curso do estudante.
         */
        std::string getCurso() const;

        /**
         * @brief Retorna a matrícula do estudante.
         * @return Matrícula do estudante.
         */
        std::string getMatricula() const;

        /**
         * @brief Retorna o prazo de empréstimo permitido ao estudante.
         * @return Prazo de empréstimo em dias.
         */
        int getPrazo() const override;

        /**
         * @brief Retorna o número máximo de empréstimos simultâneos permitidos.
         * @return Quantidade máxima de empréstimos.
         */
        int getMaxEmprestimos() const override;

        /**
         * @brief Verifica se o estudante pode realizar o empréstimo de uma obra.
         *
         * O estudante pode pegar apenas livros disponíveis e deve respeitar
         * seu limite de empréstimos ativos.
         *
         * @param o Ponteiro para a obra.
         * @return true se o empréstimo puder ser realizado, false caso contrário.
         */
        bool podeEmprestar(const Obra *o) const override;
};
#endif