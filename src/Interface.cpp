#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include "Interface.hpp"
#include "Dados.hpp"
#include "Tratamento.hpp"
    
    Interface::Interface(Dados *d): dados(d) {
        if (d == nullptr) {
            throw std::invalid_argument("Dados não pode ser nullptr.");
        }
    }
    
    void Interface::menuObras() {
        std::cout << "Menu de Obras" << std::endl;
    }
    
    void Interface::menuUsuarios() {
        std::cout << "Menu de Usuarios" << std::endl;
    }
    
    void Interface::menuEmprestimos() {
        std::cout << "Menu de Emprestimos" << std::endl;
    }
    
    void Interface::menuManutencoes() {
        std::cout << "Menu de Manutencoes" << std::endl;
    }
    
    int Interface::lerOpcao(int min, int max) {
        int n;
        while (true) {
            if (std::cin >> n) {
                try {
                    tratamento.isNumeroValido(n, min, max);
                    return n;
                } catch (const std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                }
            } else {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
    
    void Interface::executar() {
        int n;
        do {
            std::cout << "========== BIBLIOTECA ==========\n" << std::endl;
            std::cout << "1 - Obras\n2 - Usuários\n3 - Empréstimos\n4 - Manutenções\n0 - Sair\n\nOpção:" << std::endl;
        
            n = lerOpcao(0, 4);
            switch (n)
            {
            case 0:
                return;
            
            case 1:
                menuObras();
                break;

            case 2:
                menuUsuarios();
                break;
            
            case 3:
                menuEmprestimos();
                break;

            case 4:
                menuManutencoes();
                break;
            
            default:
                break;
            }
        } while (n != 0);
    }