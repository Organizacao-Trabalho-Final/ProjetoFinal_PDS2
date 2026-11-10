#include "Tratamento.hpp"
#include <cctype>
#include <stdexcept>
#include <cstddef>

    void Tratamento::setMinNum(int m) {
        if (m > max_num) {
            throw std::invalid_argument("Limite mínimo não pode ser maior que o máximo.");
        }
        min_num = m;
    }

    void Tratamento::setMaxNum(int m) {
        if (m < min_num) {
            throw std::invalid_argument("Limite máximo não pode ser menor que o mínimo.");
        }
        max_num = m;
    }

    void Tratamento::setMaxString(int m) {
        if (m < min_string) {
            throw std::invalid_argument("Limite máximo não pode ser menor que o mínimo.");
        }
        max_string = m;
    }

    void Tratamento::setMinString(int m) {
        if (m < 0 || m > max_string) {
            throw std::invalid_argument("Limite mínimo não pode ser maior que o máximo.");
        }
        min_string = m;
    }

    void Tratamento::setCaracterInvalidos(const std::string &c) {
        caracter_invalidos = c;
    }

    int Tratamento::getMaxNum() {
        return max_num;
    }

    int Tratamento::getMinNum() {
        return min_num;
    }

    int Tratamento::getMaxString() {
        return max_string;
    }

    int Tratamento::getMinString() {
        return min_string;
    }

    std::string Tratamento::getCaracterInvalidos() {
        return caracter_invalidos;
    }

    bool Tratamento::isPositivo(int num, std::string tipo) {
        if (num < 0) {
            throw std::invalid_argument(tipo + " negativo -> " + tipo + " precisa ser maior ou igual que 0");
        }
        return true;
    }

    bool Tratamento::isVazio(const std::string &s, std::string tipo) {
        if(s.find_first_not_of(" \t\n\r\f\v") == std::string::npos) {
            throw std::invalid_argument(tipo + " não pode estar vazio.");
        }
        return false;
    }

    bool Tratamento::isNumeroValido(int num, std::string tipo) {
        if (num < min_num) {
            throw std::invalid_argument(tipo + " inválido -> " + tipo + " deve ser maior ou igual a MIN | MIN: " + 
                std::to_string(min_num));
        } else if (num > max_num) {
            throw std::invalid_argument(tipo + " inválido -> " + tipo + " deve ser maior ou igual a MAX | MAX: " +
                std::to_string(max_num));
        }
        return true;
    }

    bool Tratamento::isNumeroValido(int num, int min, int max, std::string tipo) {
        if (min > max) {
            throw std::invalid_argument("Intervalo numérico inválido: MIN não pode ser maior que MAX.");
        }
        if (num < min) {
            throw std::invalid_argument(tipo + " inválido -> " + tipo + " deve que ser maior ou igual a MIN | MIN: " +
                std::to_string(min));
        } else if (num > max) {
            throw std::invalid_argument(tipo + " inválido -> " + tipo + " deve que ser menor ou igual a MAX | MAX: " +
                std::to_string(max));
        }
        return true;
    }

    bool Tratamento::isStringValido(const std::string &s, std::string tipo) {
        isVazio(s, tipo);
        int tamanho = static_cast<int>(s.length());
        if (tamanho > max_string) {
            throw std::invalid_argument(tipo + " muito grande -> precisa ser menor que " + 
                        std::to_string(max_string) + " caracteres");
        } else if (tamanho < min_string) {
            throw std::invalid_argument(tipo + " muito pequeno -> precisa ser maior que " + 
                        std::to_string(min_string) + " caracteres");
        }
        if (pode_num) {
            return true;
        }
        for (char c : s) {
            if (std::isdigit(static_cast<unsigned char>(c))) {
                throw std::invalid_argument(tipo + " não pode conter números.");
            }
        }
        return true;
    }

    bool Tratamento::isStringValido(const std::string &s, int min, int max, bool pode, std::string tipo) {
        if (min < 0 || min > max) {
            throw std::invalid_argument("Limites de caracteres inválidos: MIN deve ser não negativo e menor ou igual a MAX.");
        }
        isVazio(s, tipo);
        int tamanho = static_cast<int>(s.length());
        if (tamanho > max) {
            throw std::invalid_argument(tipo + " muito grande -> precisa ser menor que " + 
                        std::to_string(max) + " caracteres");
        } else if (tamanho < min) {
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
        isVazio(s, tipo);
        for (char c : caracter_invalidos) {
            if (c == ' ') {
                continue;
            }
            for (char css : s) {
                if (css == c) {
                    throw std::invalid_argument("Caracter inválido -> " + tipo + " não pode conter " + std::string(1, css) +
                            "\nProibidos: " + caracter_invalidos);
                }
            }
        }
        return true;
    }

    bool Tratamento::isCaracterValido(const std::string &s, const std::string &invalidos, std::string tipo) {
        if (tipo.empty()){ 
            tipo = "STR";
        }
        isVazio(s, tipo);
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
        if (tipo.empty()){ 
            tipo = "STR";
        }
        isVazio(s, tipo);
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
        if (tipo.empty()){ 
            tipo = "STR";
        }
        isVazio(s, tipo);
        for (char c : s) {
            if (!std::isdigit(static_cast<unsigned char>(c))) {
                throw std::invalid_argument(tipo + " deve conter apenas números");
            }
        }
        return true;
    }

    bool Tratamento::somenteNumeros(const std::string &s) {
        if (s.empty()) {
            return false;
        }
        for (char c : s) {
            if (!std::isdigit(static_cast<unsigned char>(c))) {
                return false;
            }
        }
        return true;
    }

    bool Tratamento::validarCPF(const std::string &c) {
        isVazio(c, "CPF");
        if (!somenteNumeros(c)) {
            throw std::invalid_argument("O CPF deve conter apenas números");
        }
        if (c.length() != 11) {
            throw std::invalid_argument("O CPF deve conter 11 digitos");
        } 
        
        bool iguais = true;
        for (std::size_t i = 1; i < c.length(); ++i) {
            if (c[i] != c[0]) {
                iguais = false;
                break;
            }
        }
        if (iguais) {
            throw std::invalid_argument("CPF inválido: sequência de dígitos repetidos.");
        }
        
        int soma = 0;
        for (int i = 0; i < 9; ++i) {
            soma += (c[i] - '0') * (10 - i);
        }
        int resto = (soma*10)%11;
        int primeiro = (resto == 10) ? 0 : resto;
        if (primeiro != c[9] - '0') {
            throw std::invalid_argument("CPF inválido: primeiro dígito verificador incorreto.");
        }

        soma = 0;
        for (int i = 0; i < 10; ++i) {
            soma += (c[i] - '0') * (11 - i);
        }
        resto = (soma*10)%11;
        int segundo = (resto == 10) ? 0 : resto;
        if (segundo != c[10] - '0') {
            throw std::invalid_argument("CPF inválido: segundo dígito verificador incorreto.");
        }
        return true;
    }

    bool Tratamento::validarMatricula(const std::string &m) {
        isVazio(m, "Matricula");
        int tamanho = static_cast<int>(m.length());
        if (!somenteNumeros(m)) {
            throw std::invalid_argument("A matríciula deve conter apenas números");
        }
        if (tamanho != 10) {
            throw std::invalid_argument("A matrícula deve conter 10 digitos");
        }
        return true;
    }

    bool Tratamento::validarQtdEX(const std::string &s, std::string tipo) {
        int tamanho = static_cast<int>(s.length());
        if (tamanho > max_string) {
            throw std::invalid_argument(tipo + " muito grande -> precisa ser menor que " + 
                        std::to_string(max_string) + " caracteres");
        } else if (tamanho < min_string) {
            throw std::invalid_argument(tipo + " muito pequeno -> precisa ser maior que " + 
                        std::to_string(min_string) + " caracteres");
        }
        return true;
    }

    bool Tratamento::validarQtd(const std::string &s) {
        int tamanho = static_cast<int>(s.length());
        if (tamanho > max_string) {
            return false;
        } else if (tamanho < min_string) {
            return false;
        }
        return true;
    }

    bool Tratamento::validarQtdEX(const std::string &s, int min, int max, std::string tipo) {
        if (min < 0 || min > max) {
            throw std::invalid_argument("Limites de caracteres inválidos: MIN deve ser não negativo e menor ou igual a MAX.");
        }
        int tamanho = static_cast<int>(s.length());
        if (tamanho > max) {
            throw std::invalid_argument(tipo + " muito grande -> precisa ser menor que " + 
                        std::to_string(max) + " caracteres");
        } else if (tamanho < min) {
            throw std::invalid_argument(tipo + " muito pequeno -> precisa ser maior que " + 
                        std::to_string(min) + " caracteres");
        }
        return true;
    }

    bool Tratamento::validarQtd(const std::string &s, int min, int max) {
        if (min < 0 || min > max) {
            return false;
        }
        int tamanho = static_cast<int>(s.length());
        if (tamanho > max) {
            return false;
        } else if (tamanho < min) {
            return false;
        }
        return true;
    }