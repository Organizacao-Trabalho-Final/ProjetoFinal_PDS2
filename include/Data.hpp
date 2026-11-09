#ifndef DATA_HPP
#define DATA_HPP

/**
 * @file Data.hpp
 * @brief Contrato da classe Data.
 */
#include <string>

/**
 * @class Data
 * @brief Representa uma data e fornece operações de validação e cálculo entre datas.
 */
class Data {    
    private:
        int dia;
        int mes;
        int ano;

        /**
        * @brief Verifica se o ano é bissexto.
        * @param a Ano a verificar.
        */
        bool isBissexto(int a) const;

        /**
        * @brief Função que retorna a quantidade de dias de um mês de determinado ano.
        * @param m Mês do ano.
        * @param a Ano.
        * @return Quantidade de dias no mês.
        */
        int  diaMes(int m, int a) const;

        /**
        * @brief Calcula a posição de uma data dentro do ano.
        * @return Dia do ano.
        */
        int dias() const;

        /**
        * @brief Avança a data em um dia.
        * @throws std::invalid_argument caso a quantidade de dias seja menor que 1.
        * @throws std::out_of_range caso a soma ultrapasse o ano 9999.
        */
        void addDia();

    public:
        /**
        * @brief Constrói um objeto Data.
        * @param d Dia do mês.
        * @param m Mês do ano.
        * @param a Ano.
        */
        Data(int d, int m, int a);

        /**
        * @brief Retorna o dia.
        * @return Dia do mês.
        */
        int getDia() const;

        /**
        * @brief Retorna o mês do ano.
        * @return Mês do ano.
        */
        int getMes() const;

        /**
        * @brief Retorna o ano.
        * @return Ano.
        */
        int getAno() const;

        /**
        * @brief Retorna a data em formato de texto.
        * @return Data no formato "dia/mes/ano".
        */
        std::string getData() const;

        /**
        * @brief Verifica se a data é válida.
        * @return true se a data for válida; false caso contrário.
        */
        bool isValida() const;

        /**
        * @brief Soma X dias a data atual.
        * @param d Dias a serem somados
        * @return Retorna a data com dias somados.
        */
        Data somarDias(int d) const;

        /**
        * @brief Calcula a diferença de uma Data com a atual.
        * @param d Data a ser comparada.
        * @return Diferença entre as datas.
        */
        int diferencaDatas(const Data &data) const;

        ~Data() = default; ///< Destrutor padrão.
};
#endif