#include <string>
#include <stdexcept>
#include "Data.hpp"

    Data::Data(int d, int m, int a):
    dia(d), mes(m), ano(a) {
        if (!isValida()) {
            throw std::invalid_argument("Data invalida");
        }
    }

    int Data::getDia() const {
        return dia;
    }

    int Data::getMes() const {
        return mes;
    }

    int Data::getAno() const {
        return ano;
    }

    std::string Data::getData() const {
        std::string data = std::to_string(dia) + "/" +
                           std::to_string(mes) + "/" +
                           std::to_string(ano);
        return data;
    }

    bool Data::isBissexto(int a) const {
        if (a < 1) {
            throw std::invalid_argument("Ano inválido -> ANO > 0");           
        } else if (a > 9999) {
            throw std::invalid_argument("Ano inválido -> ANO com 4 Digitos");
        }
        if (a % 4   == 0 && a % 100 != 0) {
            return true;
        }
        if (a % 100 == 0 && a % 400 == 0) {
            return true;
        } 
        return false;
    }

    int Data::diaMes(int m, int a) const {
        if (isBissexto(a)) {
            if (m == 2) {
                return 29;
            }
        } else {
            if (m == 2) {
                return 28;
            }
        }
        // 4 6 9 11 -> Verificando meses com 30 dias
        if (m == 4 || m == 6 || m == 9 || m == 11) {
            return 30;               
        }
        //1 3 5 7 8 10 12 -> Verificando meses com 31 dias
        if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) {
            return 31;                
        }
        return 0;
    }

    int Data::dias(int d, int m, int a) const {
        if (!isValida(d, m, a)) {
            throw std::invalid_argument("Data invalida");
        }

        int dias = 0;
        for (int i = 1; i < m; i++) {
            dias += diaMes(i, a);
        }
        dias += d;
        return dias;
    }

    int Data::dias() const {
        int d = dia;
        int m = mes;
        int a = ano;

        int dias = 0;
        for(int i = 1; i < m; i++) {
            dias += diaMes(i, a);
        }
        dias += d;
        return dias;
    }

    void Data::addDia() {
        int d = dia;
        int m = mes;
        int a = ano;

        int diam = diaMes(m, a);
        d++;
        if (d > diam) {
            d = 1;
            m++;
        }
        if (m > 12) {
            m = 1;
            a++;
        }
        dia = d;
        mes = m;
        ano = a;
    }

    bool Data::isValida() const {
        if (dia > 31 || dia < 1) {
            return false;
        }
        if (mes < 1 || mes > 12) {
            return false;
        }
        if (ano < 1 || ano > 9999) {
            return false;
        }

        int diam = diaMes(mes, ano);
        if (dia > diam) {
            return false;
        }
        return true;
    }

    bool Data::isValida(int d, int m, int a) const {
        if (d > 31 || d < 1) {
            return false;
        }
        if (m < 1 || m > 12) {
            return false;
        }
        if (a < 1 || a > 9999) {
            return false;
        }

        int diames = diaMes(m, a);
        if (d > diames) {
            return false;
        }
        return true;
    }

    Data Data::somarDias(int dias) const {
        if (dias < 1) {
            throw std::invalid_argument("'dias' inválido -> d > 0");
        }

        int d = dia;
        int m = mes;
        int a = ano;
        Data prazo(d, m, a);

        while(dias > 0) {
            prazo.addDia();
            dias--;
        }
        return prazo;
    }

    int Data::diferencaDatas(const Data &data) const {
        int diasAtual = dias();
        int diasDado = data.dias();

        for (int i = 1; i < ano; i++) {
            diasAtual += isBissexto(i) ? 366 : 365;
        }
        for (int i = 1; i < data.getAno(); i++) {
            diasDado += isBissexto(i) ? 366 : 365;
        }
        return diasDado - diasAtual;
    }