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

        return this->dia;

    }

    int Data::getMes() const {

        return this->mes;

    }

    int Data::getAno() const {

        return this->ano;

    }

    std::string Data::getData() const {

        std::string data = std::to_string(this->dia) + "/" +
                           std::to_string(this->mes) + "/" +
                           std::to_string(this->ano) + "/" ;

        return data;

    }

    bool Data::isBissexto(int _ano) const {

        if(_ano < 0) {
            throw std::invalid_argument("Ano inválido -> ANO > 0");           
        } else if(_ano > 9999) {
            throw std::invalid_argument("Ano inválido -> ANO com 4 Digitos");
        }

        if(_ano % 4   == 0 &&
           _ano % 100 != 0 ){
            return true;
        }

        int retirar  = _ano / 100;
            retirar *= 100;
        _ano -= retirar;

        if(_ano       == 0 &&
           _ano % 400 == 0 ){
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

    int Data::Dias(int _dia, int _mes, int _ano) const {

        if(!isValida(_dia, _mes, _ano)) {
            throw std::invalid_argument("Data invalida");
        }

        int dias = 0;

        for(int i = 0; i < _mes; i++) {
            dias += diaMes(i, _ano);
        }

        dias += _dia;

        return dias;

    }

    int Data::Dias() const {

        int _dia = this->dia;
        int _mes = this->mes;
        int _ano = this->ano;

        int dias = 0;

        for(int i = 0; i < _mes; i++) {
            dias += diaMes(i, _ano);
        }

        dias += _dia;

        return dias;

    }

    void Data::addDia() {

        int _dia = this->dia;
        int _mes = this->mes;
        int _ano = this->ano;

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

        this->dia = _dia;
        this->mes = _mes;
        this->ano = _ano;

    }

    bool Data::isValida() const {

        if(this->dia > 31 || this->dia < 1) {
            return false;
        }

        if(this->mes < 0 || this->mes > 12) {
            return false;
        }

        if(this->ano < 0 || this->ano > 9999) {
            return false;
        }

        int dia_mes = diaMes(this->mes, this->ano);

        if(this->dia > dia_mes) {
            return false;
        }
        
        return true;

    }

    bool Data::isValida(int _dia, int _mes, int _ano) const {

        if(_dia > 31 || _dia < 1) {
            return false;
        }

        if(_mes < 0 || _mes > 12) {
            return false;
        }

        if(_ano < 0 || _ano > 9999) {
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

        int _dia = this->dia;
        int _mes = this->mes;
        int _ano = this->ano;

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