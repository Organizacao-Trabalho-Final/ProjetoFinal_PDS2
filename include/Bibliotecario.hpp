#ifndef BIBLIOTECARIO_HPP
#define BIBLIOTECARIO_HPP

/**
 * @file Bibliotecario.hpp
 * @brief Contrato da classe Bibliotecario.
 */

#include <string>
#include "Pessoa.hpp"

class Data;
class Obra;
class Emprestimo;
class Manutencao;
class TecnicoManutencao;

/**
 * @class Bibliotecario
 * @brief Representa um bibliotecário responsável pelo gerenciamento
 * dos empréstimos, devoluções e encaminhamentos para manutenção.
 *
 * Herda os atributos e comportamentos da classe Pessoa.
 */
class Bibliotecario : public Pessoa {
    public:
        /**
         * @brief Constrói um objeto Bibliotecario.
         * @param n Nome do bibliotecário.
         * @param c CPF do bibliotecário.
         */
        Bibliotecario(std::string n, std::string c);
        
        /**
         * @brief Aprova e registra um novo empréstimo.
         * @param p Ponteiro para o usuário que solicita o empréstimo.
         * @param o Ponteiro para a obra solicitada.
         * @param d Data de realização do empréstimo.
         * @return Ponteiro para o empréstimo criado ou nullptr caso
         * a solicitação não possa ser aprovada.
         */
        Emprestimo* aprovarEmprestimo(Pessoa *p, Obra *o, Data d);
        
        /**
         * @brief Verifica as condições e aprova a renovação de um empréstimo.
         * @param e Ponteiro para o empréstimo a ser renovado.
         * @param hj Data de hoje, utilizada para verificar possíveis atrasos.
         * @return true se a renovação for aprovada, false caso contrário.
         */
        bool aprovarRenovacao(Emprestimo *e, Data hj);
        
        /**
         * @brief Registra a devolução de uma obra emprestada.
         * @param e Ponteiro para o empréstimo a ser encerrado.
         */
        void registrarDevolucao(Emprestimo *e);
        
        /**
         * @brief Verifica se uma obra apresenta danos.
         * @param o Ponteiro para a obra avaliada.
         * @return true se a obra estiver danificada, false caso contrário.
         */
        bool avaliarObra(const Obra *o) const;
        
        /**
         * @brief Encaminha uma obra danificada para manutenção.
         * @param o Ponteiro para a obra que necessita de manutenção.
         * @param tm Ponteiro para o técnico responsável.
         * @param dano Descrição do dano identificado.
         * @param i Data de início da manutenção.
         * @return Ponteiro para a manutenção criada ou nullptr caso
         * o encaminhamento não possa ser realizado.
         *
         * A manutenção criada é associada à lista de manutenções
         * do técnico responsável.
         */
        Manutencao* encaminharManutencao(Obra *o, TecnicoManutencao *tm, std::string dano, Data i);
};
#endif