#ifndef PROFESSOR_HPP
#define PROFESSOR_HPP

/**
 * @file Professor.hpp
 * @brief Contrato da classe Professor.
 */
#include <string>
#include "Pessoa.hpp"

/**
 * @class Professor
 * @brief Representa um Professor como usuário da biblioteca.
 * 
 * Herda os atributos e comportamentos da classe Pessoa e acrescenta
 * a área de atuação e regras específicas de empréstimo.
 */
class Professor : public Pessoa {
    private:
        std::string area;

    public:
        /**
         * @brief Constroi um objeto Professor.
         * @param n Nome do professor.
         * @param c CPF do professor.
         * @param a Area de atuação do professor.  
         */
        Professor(const std::string &n, const std::string &c, const std::string &a);

        /**
         * @brief Retorna a área de atuação do professor.
         * @return String contendo a área de atuação.
         */
        std::string getArea() const;

        /**
         * @brief Retorna o prazo de empréstimo permitido ao professor.
         * @return Prazo de empréstimo em dias.
         */
        int getPrazo() const override;

        /**
         * @brief Retorna o limite de empréstimos simultâneos do professor.
         * @return Quantidade máxima de empréstimos ativos permitidos.
         */
        int getMaxEmprestimos() const override;

        /**
         * @brief Verifica se o professor pode realizar o empréstimo de uma obra.
         *
         * O professor pode pegar obras disponíveis enquanto respeitar
         * seu limite de empréstimos ativos.
         *
         * @param o Ponteiro para a obra.
         * @return true se o empréstimo puder ser realizado; false caso contrário.
         */
        bool podeEmprestar(const Obra *o) const override;
};
#endif