#ifndef TRATAMENTO_HPP
#define TRATAMENTO_HPP

#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <exception>

class Tratamento {

    private :

        int min_num = 0; ///< Limite mínimo padrão para um número inteiro. Ex: min_num <= NUM.
        int max_num = 1000; ///< Limite máximo padrão para um número inteiro. Ex: NUM <= max_num.

        int max_string = 50; ///< Limite máximo padrão de caracteres para uma string.
        int min_string = 0; ///< Limite mínimo padrão de caracteres para um string.

        /**
        * Argumento padrão para as strings analisadas 
        * -> True se pode conter números e False se pode conter números.
        * -> Por padrão é False.
        */
        bool pode_num = false;

        std::string caracter_invalidos; ///< Caracteres proibidos em strings.

    public :

        /**
        * @brief Define limite máximo padrão para um número inteiro.
        * @param m Limite máximo.
        */
        void setMaxNum(int m);

        /**
        * @brief Define limite mínimo padrão para um número inteiro.
        * @param m Limite mínimo.
        */
        void setMinNum(int m);

        /**
        * @brief Define limite máximo de caracteres padrão para uma string.
        * @param m Limite máximo de caracteres.
        */
        void setMaxString(int m);

        /**
        * @brief Define limite mínimo de caracteres padrão para uma string.
        * @param m Limite mínimo de caracteres.
        */
        void setMinString(int m);

        /**
        * @brief Define os caracteres pribidos padrão para uma string. 
        * @param c Caracteres proibidos.
        */
        void setCaracterInvalidos(std::string c);

        /**
        * @brief Retorna o limite máximo para números inteiros.
        * @return Limite máximo.
        */
        int getMaxNum();

        /**
        * @brief Retorna o limite mínimo para números inteiros.
        * @return Limite mínimo.
        */
        int getMinNum();

        /**
        * @brief Retorna o limite máximo de caracteres para um string.
        * @return Limite máximo de caracteres.
        */
        int getMaxString();

        /**
        * @brief Retorna o limite mínimo de caracteres para um string.
        * @return Limite mínimo de caracteres.
        */
        int getMinString();

        /**
        * @brief Retorna os caracteres proibidos de uma string.
        * @return Caracteres proibidos.
        */
        std::string getCaracterInvalidos();

        /**
        * @brief Verifica se uma string está vazia e lança um exceção caso esteja.
        * @param s Texto a ser analisado.
        * @param tipo Explicação do texto que será exibida nas exceções -> Nome, Cpf, Area. Obs: não é obrigatório.
        * @return False se não está vazia ou uma Exceção se vazia.
        */
        bool isVazio(const std::string &s, std::string tipo = "STR");

        /**
        * @brief Verifica se um número é positivo e lança uma exceção caso não seja.
        * @param num Número a ser analisado.
        * @param tipo Explicação do valor que será exibida nas exceções. Obs: não é obrigatório.
        * @return True se é um número positivo ou Lança uma exceção caso seja negativo.
        */
        bool isPositivo(int num, std::string tipo = "NUM");

        /**
        * @brief Verifica se o número passado está dentro dos limites padrões defindos. Ex: MIN <= NUM <= MAX.
        * @param num Número a ser analisado.
        * @param tipo Explicação do valor que será exibida nas exceções. Obs: não é obrigatório.
        * @return True se o número está dentro dos limites ou Lança uma exceção caso não esteja.
        */
        bool isNumeroValido(int num, std::string tipo = "NUM");

        /**
        * @brief Verifica se o número passado está dentro dos limites defindos na chamada da função. Ex: MIN <= NUM <= MAX.
        * @param num Número a ser analisado.
        * @param min Limite mínimo.
        * @param max Limite máximo.
        * @param tipo Explicação do valor que será exibida nas exceções. Obs: não é obrigatório.
        * @return True se o número está dentro dos limites ou Lança uma exceção caso não esteja.
        */
        bool isNumeroValido(int num, int min, int max, std::string tipo = "NUM");

        /**
         * @brief Verifica se a string está dentro dos limites de caractres definidos por padrão e se pode ou não conter números. Ex: MIN <= STRING <= MAX.
         * @param s String a ser analisada.
         * @param tipo Explicação da string que será exibida nas exceções. Obs: não é obrigatório.
         * @return True se a string está dentro dos limites ou Lança uma exceção caso não esteja.
         */
        bool isStringValido(const std::string &s, std::string tipo = "STR");

        /**
        * @brief Verifica se a string está dentro dos limites de caractres definidos na chamada da função e se pode ou não conter números. Ex: MIN <= NUM <= MAX.
        * @param s String a ser analisada.
        * @param min Limite mínimo de caracteres.
        * @param max Limite máximo de caracteres.
        * @param pode Define se a string pode ou não conter números.
        * @param tipo Explicação da string que será exibida nas exceções. Obs: não é obrigatório.
        * @return True se a string está dentro dos limites ou Lança uma exceção caso não esteja.
        */
        bool isStringValido(const std::string &s, int min, int max, bool pode = false, std::string tipo = "STR");

        /**
        * @brief Verifica se a string contém algum dos caracteres padrões proibidos. 
        * @param s String a ser analisada.
        * @param tipo Explicação da string que será exibida nas exceções. Obs: não é obrigatório.
        * @return True se a string não contém caracteres proibidos ou Lança uma exceção caso tenha.
        */
        bool isCaracterValido(const std::string &s, std::string tipo = "STR");

        /**
        * @brief Verifica se a string contém algum dos caracteres proibidos passados na chamada da função. 
        * @param s String a ser analisada.
        * @param tipo Explicação da string que será exibida nas exceções. Obs: não é obrigatório.
        * @return True se a string não contém caracteres proibidos ou Lança uma exceção caso tenha.
        */
        bool isCaracterValido(const std::string &s, const std::string &invalidos, std::string tipo);

        /**
        * @brief Verifica se a string contém pelo menos um número. 
        * @param s String a ser analisada.
        * @param tipo Explicação do valor que será exibida nas exceções. Obs: não é obrigatório.
        * @return False se a string não contém números ou Lança uma exceção caso tenha.
        */
        bool temNumeroStringEX(const std::string &s, std::string tipo);

        /**
        * @brief Verifica se a string contém pelo menos um número e não lança nenhuma exceção. 
        * @param s String a ser analisada.
        * @return True se a string contém algum número ou False caso não tenha.
        */
        bool temNumeroString(const std::string &s);

        /**
        * @brief Verifica se a string contém apenas números e lança exceções caso não tenha. 
        * @param s String a ser analisada.
        * @param tipo Explicação do valor que será exibida nas exceções. Obs: não é obrigatório.
        * @return True se a string contém apenas números ou Lança uma exceção caso não tenha.
        */
        bool somenteNumerosEX(const std::string &s, std::string tipo = "STR");

        /**
        * @brief Verifica se a string contém apenas números e não lança exceções. 
        * @param s String a ser analisada.
        * @return True se a string contém apenas números ou False caso contrário.
        */
        bool somenteNumeros(const std::string &s);
        /**
         * @brief Verifica se o CPF é válido, ou seja, se contém apenas números e possui 11 dígitos.
         * @param c CPF a ser analisado.
         * @return True se o CPF é válido ou Lança uma exceção caso não seja.
         */
        bool validarCPF(const std::string &c);
        /**
         * @brief Verifica se a matrícula é válida, ou seja, se contém apenas números e possui 10 dígitos.
         * @param m Matrícula a ser analisada.
         * @return True se a matrícula é válida ou Lança uma exceção caso não seja.
         */
        bool validarMatricula(const std::string &m);
        /**
         * @brief Verifica se a quantidade de caracteres da string está dentro dos limites padrões definidos. Ex: MIN <= STRING <= MAX.
         * @param s String a ser analisada.
         * @param tipo Explicação da string que será exibida nas exceções. Obs: não é obrigatório.
         * @return True se a string está dentro dos limites ou Lança uma exceção caso não esteja.
         */
        bool validarQtdEX(const std::string &s, std::string tipo = "STR");
        /**
         * @brief Verifica se a quantidade de caracteres da string está dentro dos limites padrões definidos. Ex: MIN <= STRING <= MAX.
         * @param s String a ser analisada.
         * @return True se a string está dentro dos limites ou Lança uma exceção caso não esteja.
         */
        bool validarQtd(const std::string &s);
        /**
         * @brief Verifica se a quantidade de caracteres da string está dentro dos limites definidos na chamada da função. Ex: MIN <= STRING <= MAX.
         * @param s String a ser analisada.
         * @param min Limite mínimo de caracteres.
         * @param max Limite máximo de caracteres.
         * @param tipo Explicação da string que será exibida nas exceções. Obs: não é obrigatório.
         * @return True se a string está dentro dos limites ou Lança uma exceção caso não esteja.
         */
        bool validarQtdEX(const std::string &s, int min, int max, std::string tipo = "STR");
        /**
         * @brief Verifica se a quantidade de caracteres da string está dentro dos limites definidos na chamada da função. Ex: MIN <= STRING <= MAX.
         * @param s String a ser analisada.
         * @param min Limite mínimo de caracteres.
         * @param max Limite máximo de caracteres.
         * @return True se a string está dentro dos limites ou Lança uma exceção caso não esteja.
         */
        bool validarQtd(const std::string &s, int min, int max);

};

#endif