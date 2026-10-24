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
        * @param m Limite mínimo de caracteres.
        */
        void setCaracterValidos(std::string c);

        int getMaxNum();
        int getMinNum();
        int getMaxString();
        int getMinString();
        std::string getCaracterValidos();

        bool isVazio(const std::string &s, std::string tipo = "STR");

        bool isPositivo(int num, std::string tipo = "NUM");

        bool isNumeroValido(int num, std::string tipo = "NUM");
        bool isNumeroValido(int num, int min, int max, std::string tipo = "NUM");
        bool isStringValido(const std::string &s, std::string tipo = "STR");
        bool isStringValido(const std::string &s, int min, int max, bool pode_num = false, std::string tipo = "STR");

        bool isCaracterValido(const std::string &s, std::string tipo = "STR");
        bool isCaracterValido(const std::string &s, const std::string &invalidos, std::string tipo = "STR");

        bool temNumeroStringEX(const std::string &s, std::string tipo = "STR");
        bool temNumeroString(const std::string &s);
        bool somenteNumerosEX(const std::string &s, std::string tipo = "STR");
        bool somenteNumeros(const std::string &s);

        bool validarCPF(const std::string &c);
        bool validarMatricula(const std::string &m);
        
        bool validarQtdEX(const std::string &s, std::string tipo = "STR");
        bool validarQtd(const std::string &s);
        bool validarQtdEX(const std::string &s, int min, int max, std::string tipo = "STR");
        bool validarQtd(const std::string &s, int min, int max);

};

#endif