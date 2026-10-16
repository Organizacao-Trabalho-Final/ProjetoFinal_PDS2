#include <string>
#include "../include/Data.hpp"
#include <iostream>
#include <exception>

    Data::Data(int d, int m, int a) : dia(d), mes(m), ano(a) {
        if(!isValida()) {
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
                           std::to_string(ano) + "/" ;
        return data;
    }

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////// PRIVATE /////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

    bool Data::isBissexto(int a) const {
        if(a < 0) {
            throw std::invalid_argument("Ano inválido -> ANO > 0");           
        } else if(a > 9999) {
            throw std::invalid_argument("Ano inválido -> ANO com 4 Digitos");
        }
        if(a % 4   == 0 &&
           a % 100 != 0 ){
            return true;
        }

        int  retirar  = a / 100;
        retirar *= 100;
        a -= retirar;

        if(a       == 0 &&
           a % 400 == 0 ){
            return true;
        } 

        return false;
    }

    int Data::diaMes(int _mes, int _ano)const {
        if(isBissexto(_ano)) {
            if(_mes == 2) {
                return 29;
            }
        } else {
            if(_mes == 2) {
                return 28;
            }
        }
        // 4 6 9 11 -> Verificando meses com 30 dias
        if(  _mes   == 4   ||
             _mes   == 6   ||
             _mes   == 9   ||
             _mes   == 11  ){
                return 30;               
        }
        //1 3 5 7 8 10 12 -> Verificando meses com 31 dias
        if(  _mes   == 1   ||
             _mes   == 3   ||
             _mes   == 5   ||
             _mes   == 7   ||
             _mes   == 8   ||
             _mes   == 10  ||
             _mes   == 12  ){
                return 31;                
        }
        return 0;
    }

    int Data::Dias(int _dia, int m, int a) const {
        if(!isValida(_dia, m, a)) {
            throw std::invalid_argument("Data invalida");
        }

        int dias = 0;

        for(int i = 0; i < m; i++) {
            dias += diaMes(i, a);
        }

        dias += _dia;

        return dias;
    }

    int Data::Dias() const {
        int _dia = dia;
        int m = mes;
        int a = ano;

        int dias = 0;

        for(int i = 0; i < m; i++) {
            dias += diaMes(i, a);
        }

        dias += _dia;

        return dias;
    }

    void Data::addDia() {
        int _dia = dia;
        int _mes = mes;
        int _ano = ano;

        int dia_mes = diaMes(_mes, _ano);
        _dia++;

        if(_dia > dia_mes) {
            _dia = 1;
            _mes++;
        }
        if(_mes > 12) {
            _mes = 1;
            _ano++;
        }
        dia = _dia;
        mes = _mes;
        ano = _ano;
    }

/////////////////////////////////////////////////////////////////////////////
//////////////////////////////// PUBLIC /////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

    bool Data::isValida() const {
        if(dia > 31 || dia < 1) {
            return false;
        }
        if(mes < 0 || mes > 12) {
            return false;
        }
        if(ano < 1 || ano > 9999) {
            return false;
        }

        int dia_mes = diaMes(mes, ano);

        if(dia > dia_mes) {
            return false;
        }

        return true;
    }

    bool Data::isValida(int _dia, int _mes, int _ano) const {
        if(_dia > 31 || _dia < 1) {
            return false;
        }
        if(_mes < 1 || _mes > 12) {
            return false;
        }
        if(_ano < 1 || _ano > 9999) {
            return false;
        }
        int dia_mes = diaMes(_mes, _ano);
        if(_dia > dia_mes) {
            return false;
        }
        return true;
    }

    Data Data::somarDias(int d) const {
        if(d < 1) {
            throw std::invalid_argument("'d' inválido -> d > 0");
        }

        int _dia = dia;
        int _mes = mes;
        int _ano = ano;

        Data prazo(_dia, _mes, _ano);

        while(d > 0) {
            prazo.addDia();
            d--;
        }

        return prazo;
    }

    int Data::diferencaDatas(Data d) const {
        int _dia = d.getDia();
        int _mes = d.getMes();
        int _ano = d.getAno();

        int dif;

        int _dias_atual = Dias();
        int _dias_dado  = Dias(_dia, _mes, _ano);

        dif = _dias_dado - _dias_atual;
        return dif;
    }

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////