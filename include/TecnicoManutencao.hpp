#ifndef TECNICOMANUTENCAO_HPP
#define TECNICOMANUTENCAO_HPP

/**
 * @file TecnicoManutencao.hpp
 * @brief Contrato da classe TecnicoManutencao.
 */

#include <string>
#include <vector>
#include "Pessoa.hpp"

class Manutencao;

/**
 * @class TecnicoManutencao
 * @brief Representa um técnico responsável pelas manutenções
 * da biblioteca e permite consultar esses dados.
 *
 * Herda os atributos e comportamentos da classe Pessoa.
 */
class TecnicoManutencao : public Pessoa {
    private:
        std::vector<Manutencao*> manutencoes;

    public:
        /**
         * @brief Constrói um objeto TecnicoManutencao.
         * @param n Nome do técnico.
         * @param c CPF do técnico.
         */
        TecnicoManutencao(std::string n, std::string c);

        /**
         * @brief Retorna a lista de manutenções associadas ao técnico.
         * @return Referência ao vetor de ponteiros para Manutencao.
         */
        const std::vector<Manutencao*>& getManutencoes() const;

        /**
         * @brief Adiciona uma manutenção à lista do técnico.
         * @param m Ponteiro para a manutenção a ser associada.
         */
        void adicionarManutencao(Manutencao *m);

        /**
         * @brief Substitui a lista de manutenções associadas ao técnico.
         * @param m Vetor de ponteiros para as manutenções.
         */
        void setManutencoes(const std::vector<Manutencao*>& m);

        /**
         * @brief Consulta a quantidade de manutenções pendentes do técnico.
         * @return Número de manutenções com estado PENDENTE.
         */
        int consultarManutencoesPendentes() const;

        /**
         * @brief Registra o reparo realizado em uma manutenção.
         * @param m Ponteiro para a manutenção correspondente.
         * @param r Descrição do reparo realizado.
         */
        void registrarReparo(Manutencao *m, const std::string& r);

        /**
         * @brief Conclui uma manutenção atribuída ao técnico.
         * @param m Ponteiro para a manutenção a ser concluída.
         */
        void concluirManutencao(Manutencao *m);

        /**
         * @brief Destrói o técnico e libera as manutenções sob sua propriedade.
         *
         * @note Os objetos apontados pelo vetor manutencoes são destruídos
         * junto com o técnico.
         */
        ~TecnicoManutencao() override;
};
#endif