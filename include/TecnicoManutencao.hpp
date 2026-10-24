#ifndef TECNICOMANUTENCAO_HPP
#define TECNICOMANUTENCAO_HPP

/**
 * @file TecnicoManutencao
 * @brief Declaração da calsse TecnicoManutencao
 * @date 2026-10-13
 */
#include <iostream>
#include <string>
#include <vector>
#include "Pessoa.hpp"

class Manutencao;
class Obra;

/**
 * @class TecnicoManutencao
 * @brief Cria a estrutura da classe TecnicoManutencao
 */
class TecnicoManutencao : public Pessoa {
    private:
        std::vector<Manutencao*> manutencoes;

    public:
        /**
         * @brief Contrutor da classe TecnicoManutencao
         * @param n String com o nome da pessoa
         * @param c String com o CPF da pessoa
         */
        TecnicoManutencao(std::string n, std::string c);

        /**
         * @brief Método que retorna as manutenções do técnico.
         * @return Referência para vetor 'std::vector<Manutencao*>&'.
         */
        std::vector<Manutencao*>& getManutencoes() const;

        /**
         * @brief Método a quantidade de manutenções realizadas pelo técnico.
         * @return Número de manutenções.
         */
        int getMaxManutencoes() const;

        /**
         * @brief Adiciona uma manutenção a lista de manutenções a fazer
         * @param m ponteiro para um objeto do tipo Manutencao
         */
        void adicionarManutencao(Manutencao *m);

        /**
         * @brief Adiciona todas as manutenções de um técnico.
         * @param m Vetor de manutenções 'std::vector<Manutencao*>'.
         */
        void setManutencoes(std::vector<Manutencao*> m);

        /**
         * @brief Consulta a lista de Manutenções a fazer
         * @return Retorna o id da manutenção ainda pendente
         */
        int consultarManutencoesPendentes() const;

        /**
         * @brief Registra qual reparo foi feito na obra
         * @param m Ponteiro para um objeto do tipo Manutencao
         * @param r String com qual reparo foi feito
         */
        void registrarReparo(Manutencao *m, std::string r);

        /**
         * @brief Deixa manutenção como concluída
         * @param m Ponteiro para um objeto do tipo Manutencao
         */
        void concluirManutencao(Manutencao *m);
};
#endif