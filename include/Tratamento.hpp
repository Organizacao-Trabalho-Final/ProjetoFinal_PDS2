#ifndef TRATAMENTO_HPP
#define TRATAMENTO_HPP

#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <exception>

class Tratamento {

    private :

        int min_num = 0;
        int max_num = 1000;

        int max_string = 50;
        int min_string = 0;

        bool pode_num = false;

        std::string caracter_invalidos;

    public :

        void setMaxNum(int m);
        void setMinNum(int m);
        void setMaxString(int m);
        void setMinString(int m);
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