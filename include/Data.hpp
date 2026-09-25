#ifndef DATA_H
#define DATA_H

#include <string>

class Data {
    private:
        int dia;
        int mes;
        int ano;

    public:
        Data(int d, int m, int a);

        int getDia() const;
        int getMes() const;
        int getAno() const;
        std::string getData() const;

        bool isValida() const;
        Data somarDias(int d) const;
        int diferencaDatas(Data d) const;

        ~Data() = default;
};
#endif