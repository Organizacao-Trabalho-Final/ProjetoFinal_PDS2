#ifndef PESSOA_H
#define PESSOA_H

/**
 * @file Pessoa.hpp
 * @brief declaraçao da classe Pessoa
 * @date 2026-10-11
 */
#include <string>
#include <vector>

class Obra;
class Emprestimo;

/**
 * @class Pessoa
 * @brief cria a estrutura da classe Pessoa
 */
class Pessoa {
    private:
        std::string nome;
        std::string CPF;
        std::vector<Emprestimo*> emprestimos;

    public:
        /**
         * @brief Construtor de Pessoa
         * @param n o nome da pessoa
         * @param c o CPF da pessoa
         */
        Pessoa(std::string n, std::string c);

        /** 
         * @brief usado para ler a string armazenada em nome
         * @return retorna a variável "nome"
         */
        std::string getNome() const;

        /**
         * @brief usado para ler a string armazenada em "CPF"
         * @return retorna "CPF"
         */
        std::string getCPF() const;

        /**
         * @brief usado para ler o valor armazenado em "prazo"
         * @return retorna o prazo para a devolução
         */
        virtual int getPrazo() const;

        /**
         * @brief usado para ler o valor máximo de empréstimos
         * @return retorna o valor máximo de empréstimos da pessoa
         */
        virtual int getMaxEmprestimos() const;

        /**
         * @brief Método para capturar a qunatidade de empréstimos de uma pessoa.
         * @return Quantidade de empréstimos.
         */
        int getNumEmprestimos() const;

        /**
         * @brief Método para bucar e retornar os empréstimos Ativos.
         * @return Quantidade de empréstimos Ativos.
         */
        int getEmprestimosAtivos() const;

        /**
         * @brief Carrega todos os empréstimos de uma pessoa.
         * @param e Vetor de empréstimos 'std::vector<Emprestimo*>'.
         */
        void setEmprestimos(std::vector<Emprestimo*> e);

         /**
         * @brief Método virtual constante que retorna o vetor de ponteiros para os empréstimos da pessoa
         * @return Referência para vetor de 'std::vector<Emprestimo*>'.
         */
        virtual const std::vector<Emprestimo*>& getEmprestimos() const;

        /**
         * @brief método virtual constante que verifica se a pessoa pode pegar aquela obra eprestada
         * @param o um ponteiro para obra
         * @return retorna true se puder e false, caso contrário
         */
        virtual bool podeEmprestar(const Obra *o) const;

        /**
         * @brief Lista os empréstimos ativos da pessoa
         * @return retorna o vetor com os ponteiros para os empréstimos que ainda não foram devolvidos
         */
        std::vector<Emprestimo*> consultarAtivos();

        /**
         * @brief lista todos os empréstimos ja registrados para a pessoa
         * @return retorna um vetor com ponteiros para todos os empréstimos, ativos e encerrados
         */
        std::vector<Emprestimo*> historicoEmprestimos();

        /**
         * @brief registra um emprestimo no vetor de empréstimos
         * @param e ponteiro para empréstimo
         */
        void registrarEmprestimo(Emprestimo *e);
    
        /**
         * @brief método destrutor virtual de pessoa, importante para herança polimórfica
         */
        virtual ~Pessoa() = default;
};
#endif