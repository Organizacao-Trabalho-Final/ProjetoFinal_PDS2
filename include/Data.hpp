#ifndef DATA_H
#define DATA_H

#include <string>

class Data {    
    private:
        int dia; ///< Dia do mês
        int mes; ///< Mes do ano
        int ano; ///< Ano

    public :

        /**
        * @brief Verifica se o ano é bissexto.
        * @param _ano Ano a verificar.
        */
        bool isBissexto(int _ano) const;

        /**
        * @brief Função que retorna a quantidade de dias no mes em agum ano.
        * @param _mes Mês do ano.
        * @param _ano Ano.
        * @return Quantidade de dias no mês.
        */
        int  diaMes(int _mes, int _ano) const;

        /**
        * @brief Converte uma data em dias no ano.
        * @param _dia Dia do ano.
        * @param _mes Mês do ano.
        * @param _ano Ano.
        * @return Dia no ano.
        */
        int  Dias(int _dia, int _mes, int _ano) const;

        /**
        * @brief Converte a data em dias no ano.
        * @return Dia no ano.
        */
        int  Dias() const;

        /**
        * @brief A data muda para um dia a frente.
        */
        void addDia();

    public:

        /**
        * @brief Carrega o dia, mês e ano para os parÂmetros da classe.
        * @param d Dia do ano.
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
        * @brief Retorna o mÊs do ano.
        * @return Mês do ano.
        */
        int getMes() const;

        /**
        * @brief Retorna o ano.
        * @return Ano.
        */
        int getAno() const;

        /**
        * @brief Retorna a data em formato "std::string".
        * @return data (string).
        */
        std::string getData() const;

        /**
        * @brief Verifica se a data é válida.
        * @return False se é inválida e True se Válida.
        */
        bool isValida() const;

        /**
        * @brief Verifica se a data fornecida é válida.
        * @return False se é inválida e True se Válida.
        */
        bool isValida(int _dia, int _mes, int _ano) const;

        /**
        * @brief Soma X dias a data atual.
        * @param d Dias a serem somados
        * @return Retorna a data com dias somados.
        */
        Data somarDias(int d) const;

        /**
        * @brief Calcula a diferença de uma Data com a atual.
        * @param d Data.
        * @return Diferença entre as datas.
        */
        int diferencaDatas(Data d) const;

        ~Data() = default; ///< Destrutor padrão.
};
#endif