#ifndef MANUTENCAO_HPP
#define MANUTENCAO_HPP

/**
 * @file Manutencao.hpp
 * @brief Contrato da classe Manutencao.
 */
#include <iostream>
#include <string>
#include "Data.hpp"

class Obra;
class TecnicoManutencao;
class Dados;

/**
 * @enum EstadoManutencao
 * @brief Representa os possíveis estados de uma manutenção.
 */
enum class EstadoManutencao {
    PENDENTE,
    EM_ANDAMENTO,
    CONCLUIDA
};

/**
 * @class Manutencao
 * @brief Representa o processo de manutenção de uma obra danificada.
 *
 * Armazena a obra, o técnico responsável, o dano identificado,
 * o reparo realizado, a data de início e o estado da manutenção.
 */
class Manutencao {
    private:
        Obra *obra; ///< Obra submetida à manutenção.
        TecnicoManutencao *tecnico; ///< Técnico responsável pela manutenção.
        std::string dano, reparo; ///< Descrição do dano identificado + reparo realiado.
        Data inicio; ///< Data de início da manutenção.
        EstadoManutencao estado; ///< Estado atual da manutenção.

        /**
         * @brief Restaura o estado da manutenção durante o carregamento dos dados.
         * @param e Estado armazenado.
         */
        void setEstado(EstadoManutencao e);

        friend class Dados;

    public:
        /**
         * @brief Constrói um objeto Manutencao.
         * @param o Ponteiro para a obra danificada.
         * @param tm Ponteiro para o técnico responsável.
         * @param d Descrição do dano identificado.
         * @param i Data de início da manutenção.
         */
        Manutencao(Obra *o, TecnicoManutencao *tm, const std::string &d, const Data &i);

        /**
         * @brief Retorna a obra associada à manutenção.
         * @return Ponteiro para a obra.
         */
        Obra* getObra() const;

        /**
         * @brief Usado para passar o ponteiro da obra, ou deja, o acesso a essa obra
         * @return Retorna *TecnicoManutencao
         */
        TecnicoManutencao* getTecnico() const;

        /**
         * @brief Retorna a descrição do dano.
         * @return Descrição do dano.
         */
        std::string getDano() const;

        /**
         * @brief Retorna a descrição do reparo.
         * @return Descrição do reparo realizado.
         */
        std::string getReparo() const;

        /**
         * @brief Retorna a data de início da manutenção.
         * @return Data de início.
         */
        Data getInicio() const;

        /**
         * @brief Retorna o estado atual da manutenção.
         * @return Estado da manutenção.
         */
        EstadoManutencao getEstado() const;

        /**
         * @brief Registra a descrição do reparo realizado.
         * @param r Descrição do reparo.
         */
        void registrarReparo(const std::string &r);

        /**
         * @brief Inicia uma manutenção pendente.
         * Altera o estado para EM_ANDAMENTO e mantém a obra indisponível.
         */
        void iniciar();

        /**
         * * @brief Conclui uma manutenção em andamento.
         * Altera o estado para CONCLUIDA, remove a marcação de dano
         * da obra e torna a obra novamente disponível.
         */
        void concluir();

        /**
         * @brief Destrutor de Manutencao.
         * Não destrói a obra nem o técnico associados.
         */
        ~Manutencao() = default;
};
#endif