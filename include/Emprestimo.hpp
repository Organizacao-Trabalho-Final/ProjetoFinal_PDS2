#ifndef EMPRESTIMO_HPP
#define EMPRESTIMO_HPP

/**
 * @file Emprestimo.hpp
 * @brief Contrato da classe Emprestimo.
 */
#include "Data.hpp"

class Obra;
class Pessoa;

/**
 * @class Emprestimo
 * @brief Representa o empréstimo de uma obra a um usuário.
 *
 * Armazena a obra emprestada, o usuário responsável, as datas de
 * retirada e devolução e o estado atual do empréstimo.
 */
class Emprestimo {
    private:
        Obra *obra; ///< Obra associada ao empréstimo.
        Pessoa *usuario; ///< Usuário responsável pelo empréstimo.
        Data retirada, devolucao; ///< Data de retirada + previsão de devolução da obra.
        bool ativo; ///< Indica se o empréstimo está ativo.

    public:
        /**
         * @brief Constrói um objeto Emprestimo.
         * @param o Obra que será emprestada.
         * @param p Usuário responsável pelo empréstimo.
         * @param d Data de retirada da obra.
         */
        Emprestimo(Obra &o, Pessoa &p, const Data d);

        /**
         * @brief Altera o estado do empréstimo.
         * @param b Novo estado do empréstimo.
         */
        void setAtivo(bool b);

        /**
         * @brief Informa se o empréstimo está ativo.
         * @return true se o empréstimo estiver ativo; false caso contrário.
         */
        bool isAtivo() const;

        /**
         * @brief Retorna a obra associada ao empréstimo.
         * @return Referência para a obra emprestada.
         */
        Obra& getObra();

        /**
         * @brief Retorna o usuário responsável pelo empréstimo.
         * @return Referência constante para o usuário.
         */
        const Pessoa& getUsuario() const;

        /**
         * @brief Retorna a data de retirada da obra.
         * @return Data de retirada.
         */
        Data getRetirada() const;

        /**
         * @brief Retorna a data prevista para devolução da obra.
         * @return Data prevista para devolução.
         */
        Data getDevolucao() const;

        /**
         * @brief Altera a data prevista para devolução.
         * @param d Nova data de devolução.
         */
        void setDevolucao(Data d);

        /**
         * @brief Calcula a quantidade de dias de atraso do empréstimo.
         * @param d Data usada como referência para o cálculo.
         * @return Quantidade de dias de atraso ou zero se não houver atraso.
         */
        int getAtraso(Data d) const;

        /**
         * @brief Encerra o empréstimo.
         * Altera o estado do empréstimo para inativo.
         */
        void encerrarEmprestimo();

        /**
         * @brief Renova o empréstimo.
         * Adiciona à data de devolução um novo período correspondente
         * ao prazo permitido para o usuário.
         */
        void renovarEmprestimo();

        /**
         * @brief Exibe as informações do empréstimo.
         * Mostra a obra, o usuário, as datas de retirada e devolução
         * e o estado atual do empréstimo.
         */
        void printEmprestimo() const;

        /**
         * @brief Destrutor padrão da classe Emprestimo.
         */
        ~Emprestimo() = default;
};
#endif