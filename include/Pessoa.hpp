#ifndef PESSOA_HPP
#define PESSOA_HPP

/**
 * @file Pessoa.hpp
 * @brief Contrato da classe Pessoa.
 */
#include <string>
#include <vector>

class Obra;
class Emprestimo;

/**
 * @class Pessoa
 * @brief Representa uma pessoa que interage com o sistema da biblioteca.
 *
 * Superclasse de Bibliotecario, Professor, Estudante e TecnicoManutencao.
 */
class Pessoa {
    private:
        std::string nome;
        std::string CPF;
        std::vector<Emprestimo*> emprestimos;

    public:
        /**
         * @brief Constói um objeto Pessoa.
         * @param n Nome da pessoa.
         * @param c CPF da pessoa.
         */
        Pessoa(const std::string &n, const std::string &c);

        /** 
         * @brief Retorna o nome da pessoa.
         * @return Nome da pessoa.
         */
        std::string getNome() const;

        /**
         * @brief Retorna o CPF da pessoa.
         * @return CPF da pessoa.
         */
        std::string getCPF() const;

        /**
         * @brief Retorna o prazo de empréstimo permitido para a pessoa.
         * @return Prazo em dias.
         */
        virtual int getPrazo() const;

        /**
         * @brief Retorna a quantidade máxima de empréstimos simultâneos.
         * @return Limite de empréstimos.
         */
        virtual int getMaxEmprestimos() const;

        /**
         * @brief Retorna a quantidade total de empréstimos registrados.
         * @return Quantidade de empréstimos.
         */
        int getNumEmprestimos() const;

        /**
         * @brief Retorna a quantidade de empréstimos ativos.
         * @return Quantidade de empréstimos ativos.
         */
        int getEmprestimosAtivos() const;

        /**
         * @brief Substitui os empréstimos de uma pessoa.
         * @param e Vetor de empréstimos.
         */
        void setEmprestimos(std::vector<Emprestimo*> &e);

         /**
         * @brief Retorna o vetor de ponteiros para os empréstimos da pessoa.
         * @return Referência para vetor de empréstimos.
         */
        const std::vector<Emprestimo*>& getEmprestimos() const;

        /**
         * @brief Verifica se a pessoa pode realizar o empréstimo de uma obra.
         * @param o Ponteiro para a obra.
         * @return true se o empréstimo puder ser realizado, false caso contrário.
         */
        virtual bool podeEmprestar(const Obra *o) const;

        /**
         * @brief Retorna os empréstimos ativos da pessoa.
         * @return Vetor contendo os empréstimos ativos.
         */
        std::vector<Emprestimo*> consultarAtivos() const;

        /**
         * @brief Exibe e retorna o histórico de empréstimos da pessoa.
         * @return Vetor contendo todos os empréstimos registrados.
         */
        std::vector<Emprestimo*> historicoEmprestimos() const;

        /**
         * @brief Registra um empréstimo para a pessoa.
         * @param e Ponteiro para o empréstimo.
         */
        void registrarEmprestimo(Emprestimo *e);

        // Impedem cópias superficiais dos ponteiros pertencentes à classe.
        Pessoa(const Pessoa&) = delete;
        Pessoa& operator=(const Pessoa&) = delete;
    
        /**
         * @brief Destrutor virtual da classe Pessoa.
         */
        virtual ~Pessoa();
};
#endif