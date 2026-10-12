#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

/**
 * @file Emprestimo.hpp
 * @brief declaração da classe Emprestimo
 * @date 2026-10-12
 */
#include "Data.hpp"
class Obra;
class Pessoa;

/**
 * @class Emprestimo
 * @brief Cria a estrutura da classe Emprestimo
 */
class Emprestimo {
    private:
        Obra *obra;
        Pessoa *usuario;
        Data retirada, devolucao;
        bool ativo;

    public:
    /**
     * @brief Construtor de Emprestimo
     * @param o Referencia para uma Obra
     * @param p Referencia para uma Pessoa
     * @param d Objeto do tipo Data
     */
        Emprestimo(Obra &o, Pessoa &p, Data d);

        /**
         * @brief Setter que altera o valor de Ativo
         * @param b Valor booleano passado para alterar "Ativo"
         */
        void setAtivo(bool b);

        /**
         * @brief Usado para ler o valor de "Obra"
         * @return Retorna uma referencia para "Obra"
         */
        Obra& getObra();

        /**
         * @brief Obtém o usuário assiciado a esse empréstimo
         * @return Retorna uma referência para pessoa que não pode ser alterada
         * @note A referencia é válida somente quando o objeto Pessoa Existir
         */
        const Pessoa& getUsuario() const;

        /**
         * @brief Usado para ler qual a data de retirada daquele empréstimo
         * @return Retorna a data que foi realizado o empréstimo
         * @note O valor não é alterado pela funçao
         */
        Data getRetirada() const;

        /**
         * @brief Usado para ler qual a data de devolução daquele empréstimo
         * @return Retorna a data que deverá ser devolvido o empréstimo
         * @note O valor não é alterado pela funçao
         */
        Data getDevolucao() const;

        /**
         * @brief Calcula o tempo de atraso da devolução de um empréstimo
         * @return Retorna os dias de atraso
         *  @note O valor não é alterado pela funçao
         */
        int getAtraso(Data d) const;

        /**
         * @brief Registra como devolução efetuada e coloca a obra disponível novamente
         */
        void encerrarEmprestimo();

        /**
         * @brief Prolonga o tempo que o emprestimo poderá existir sem que haja atraso
         */
        void renovarEmprestimo();

        /**
         * @brief destrutor de "Emprestimo"
         */
        ~Emprestimo() = default;
};
#endif