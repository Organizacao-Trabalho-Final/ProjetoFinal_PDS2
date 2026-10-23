#include "Tratamento.hpp"

    void Tratamento::setMinNum(int m) {
        this->min_num = m;
    }

    void Tratamento::setMaxNum(int m) {
        this->max_num = m;
    }

    void Tratamento::setMaxString(int m) {
        this->max_string = m;
    }

    void Tratamento::setMinString(int m) {
        this->min_string = m;
    }

    void Tratamento::setCaracterValidos(std::string c) {
        this->caracter_invalidos = c;
    }

    int Tratamento::getMaxNum() {
        return this->max_num;
    }

    int Tratamento::getMinNum() {
        return this->min_num;
    }

    int Tratamento::getMaxString() {
        return this->max_string;
    }

    int Tratamento::getMinString() {
        return this->min_string;
    }

    std::string Tratamento::getCaracterValidos() {
        return this->caracter_invalidos;
    }

    bool Tratamento::isPositivo(int num, std::string tipo) {
        if (num < 0) {
            throw std::invalid_argument(tipo + " negativo -> " + tipo + " precisa ser maior ou igual que 0");
        }
        return true;
    }

    bool Tratamento::isVazio(const std::string &s, std::string tipo) {
        if(s.empty()) {
            throw std::invalid_argument(tipo + " não pode estar vazio.");
        }
        return false;
    }

    bool Tratamento::isNumeroValido(int num, std::string tipo) {
        if (num < this->min_num) {
            throw std::invalid_argument(tipo + " inválido -> " + tipo + " tem que ser maior que MIN | MIN: " + 
                std::to_string(this->min_num));
        } else if (num > this->max_num) {
            throw std::invalid_argument(tipo + " inválido -> " + tipo + " tem que ser menor que MAX | MAX: " +
                std::to_string(this->max_num));
        }
        return true;
    }

    bool Tratamento::isNumeroValido(int num, int min, int max, std::string tipo) {
        if (num < min) {
            throw std::invalid_argument(tipo + " inválido -> " + tipo + " tem que ser maior que MIN | MIN: " +
                std::to_string(min));
        } else if (num > max) {
            throw std::invalid_argument(tipo + " inválido -> " + tipo + " tem que ser menor que MAX | MAX: " +
                std::to_string(max));
        }
        return true;
    }

    bool Tratamento::isStringValido(const std::string &s, std::string tipo) {
        this->isVazio(s, tipo);
        if (s.length() > this->max_string) {
            throw std::invalid_argument(tipo + " muito grande -> precisa ser menor que " + 
                        std::to_string(this->max_string) + " caracteres");
        } else if (s.length() < this->min_string) {
            throw std::invalid_argument(tipo + " muito pequeno -> precisa ser maior que " + 
                        std::to_string(this->min_string) + " caracteres");
        }
        if (this->pode_num) {
            return true;
        }
        for (char c : s) {
            if (std::isdigit(static_cast<unsigned char>(c))) {
                throw std::invalid_argument(tipo + " não pode contar números.");
            }
        }
        return true;
    }

    bool Tratamento::isStringValido(const std::string &s, int min, int max, bool pode, std::string tipo) {
        this->isVazio(s, tipo);
        if (s.length() > max) {
            throw std::invalid_argument(tipo + " muito grande -> precisa ser menor que " + 
                        std::to_string(max) + " caracteres");
        } else if (s.length() < min) {
            throw std::invalid_argument(tipo + " muito pequeno -> precisa ser maior que " + 
                        std::to_string(min) + " caracteres");
        }
        if (pode) {
            return true;
        }
        for (char c : s) {
            if (std::isdigit(static_cast<unsigned char>(c))) {
                throw std::invalid_argument(tipo + " não pode contar números.");
            }
        }
        return true;
    }

    bool Tratamento::isCaracterValido(const std::string &s, std::string tipo) {
        this->isVazio(s, tipo);
        for (char c : this->caracter_invalidos) {
            if (c == ' ') {
                continue;
            }
            for (char css : s) {
                if (css == c) {
                    throw std::invalid_argument("Caracter inválido -> " + tipo + " não pode conter " + std::string(1, css) +
                            "\nProibidos: " + this->caracter_invalidos);
                }
            }
        }
        return true;
    }

    bool Tratamento::isCaracterValido(const std::string &s, const std::string &invalidos, std::string tipo) {
        this->isVazio(s, tipo);
        for (char c : invalidos) {
            if (c == ' ') {
                continue;
            }
            for (char css : s) {
                if (css == c) {
                    throw std::invalid_argument("Caracter inválido -> " + tipo + " não pode conter " + std::string(1, css) +
                            "\nProibidos: " + invalidos);
                }
            }
        }
        return true;
    }

    bool Tratamento::temNumeroStringEX(const std::string &s, std::string tipo) {
        this->isVazio(s, tipo);
        for (char c : s) {
            if (std::isdigit(static_cast<unsigned char>(c))) {
                throw std::invalid_argument(tipo + " não pode conter números");
            }
        }
        return false;
    }

    bool Tratamento::temNumeroString(const std::string &s) {
        for (char c : s) {
            if (std::isdigit(static_cast<unsigned char>(c))) {
                return true;
            }
        }
        return false;
    }

    bool Tratamento::somenteNumerosEX(const std::string &s, std::string tipo) {
        for (char c : s) {
            if (!std::isdigit(static_cast<unsigned char>(c))) {
                throw std::invalid_argument(tipo + " deve conter apenas números");
            }
        }
        return true;
    }

    bool Tratamento::somenteNumeros(const std::string &s) {
        for (char c : s) {
            if (!std::isdigit(static_cast<unsigned char>(c))) {
                return false;
            }
        }
        return true;
    }

    bool Tratamento::validarCPF(const std::string &c) {
        this->isVazio(c, "CPF");
        if (!this->somenteNumeros(c)) {
            throw std::invalid_argument("O CPF deve conter apenas números");
        }
        if (c.length() != 11) {
            throw std::invalid_argument("O CPF deve conter 11 digitos");
        } 
        return true;
    }

    bool Tratamento::validarMatricula(const std::string &m) {
        this->isVazio(m, "Matricula");
        if (!this->somenteNumeros(m)) {
            throw std::invalid_argument("A matrciula deve conter apenas números");
        }
        if (m.length() != 10) {
            throw std::invalid_argument("A matricula deve conter 10 digitos");
        }
        return true;
    }

    bool Tratamento::validarQtdEX(const std::string &s, std::string tipo) {
        this->isVazio(s, tipo);
        if (s.length() > this->max_string) {
            throw std::invalid_argument(tipo + " muito grande -> precisa ser menor que " + 
                        std::to_string(this->max_string) + " caracteres");
        } else if (s.length() < this->min_string) {
            throw std::invalid_argument(tipo + " muito pequeno -> precisa ser maior que " + 
                        std::to_string(this->min_string) + " caracteres");
        }
        return true;
    }

    bool Tratamento::validarQtd(const std::string &s) {
        if (s.length() > this->max_string) {
            return false;
        } else if (s.length() < this->min_string) {
            return false;
        }
        return true;
    }

    bool Tratamento::validarQtdEX(const std::string &s, int min, int max, std::string tipo) {
        this->isVazio(s, tipo);
        if (s.length() > max) {
            throw std::invalid_argument(tipo + " muito grande -> precisa ser menor que " + 
                        std::to_string(max) + " caracteres");
        } else if (s.length() < min) {
            throw std::invalid_argument(tipo + " muito pequeno -> precisa ser maior que " + 
                        std::to_string(min) + " caracteres");
        }
        return true;
    }

    bool Tratamento::validarQtd(const std::string &s, int min, int max) {
        if (s.length() > max) {
            return false;
        } else if (s.length() < min) {
            return false;
        }
        return true;
    }