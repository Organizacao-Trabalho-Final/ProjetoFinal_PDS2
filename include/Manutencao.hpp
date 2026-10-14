#ifndef MANUTENCAO_HPP
#define MANUTENCAO_HPP

/**
 * @file Manutencao.hpp
 * @brief Declaração da classe Manutencao
 * @date 2026-10-14
 */
#include <iostream>
#include <string>
#include "Data.hpp"

class Obra;
class TecnicoManutencao;

enum class EstadoManutencao {
    PENDENTE,
    EM_ANDAMENTO,
    CONCLUIDA
};

/**
 * @class Manutencao
 * @brief Cria a estrutura da classe Manutencao
 */
class Manutencao {
    private:
        Obra *obra;
        TecnicoManutencao *tecnico;
        std::string dano;
        std::string reparo;
        Data inicio;
        EstadoManutencao estado;

    public:
        /**
         * @brief Construtor de Manutencao
         * @param o Ponteiro para Obra
         * @param tm Ponteiro para TecnicoManutencao
         * @param d String contendo o dano da obra
         * @param i Objeto do tipo Data contendo a data de início da manutenção 
         */
        Manutencao(Obra *o, TecnicoManutencao *tm, std::string d, Data i);

        /**
         * @brief Usado para passar o ponteiro da Obra, ou seja, o acesso a essa obra
         * @return Retorna *Obra
         */
        Obra* getObra() const;

        /**
         * @brief Usado para passar o ponteiro da obra, ou deja, o acesso a essa obra
         * @return Retorna *TecnicoManutencao
         */
        TecnicoManutencao* getTecnico() const;

        /**
         * @brief Usado para ler qual o dano armazenado na variável "dano"
         * @return Retorna a string "dano"
         */
        std::string getDano() const;

        /**
         * @brief Usado para ler qual vai ser o repara a ser feito na obra
         * @return Retorna a string "reparo"
         */
        std::string getReparo() const;

        /**
         * @brief Usado pra ler qual é a data que se iniciou a manutencao
         * @return Retorna o objeto "inicio" da classe Data
         */
        Data getInicio() const;

        /**
         * @brief Usado para ler o estado da manutenção
         * @return Retorna um dos enumeradores de EstadoManutencao
         */
        EstadoManutencao getEstado() const;

        /**
         * @brief Método capaz de escrever no atributo reparo qual é o reparo a ser feito
         * @param r String com o reparo
         */
        void registrarReparo(std::string r);

        /**
         * @brief Marca a data de início da manutenção, e deixa a obra fora do catálogo
         */
        void iniciar();

        /**
         * @brief Marca a data de término da manutenção e coloca a obra de volta no catálogo
         */
        void concluir();

        /**
         * @brief Destrutor de manutencao
         */
        ~Manutencao() = default;
};
#endif