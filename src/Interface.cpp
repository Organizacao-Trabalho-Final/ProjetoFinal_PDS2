#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include <vector>
#include <ctime>
#include <algorithm>
#include "Interface.hpp"
#include "Dados.hpp"
#include "Tratamento.hpp"
#include "Catalogo.hpp"
#include "Livro.hpp"
#include "Artigo.hpp"
#include "Usuarios.hpp"
#include "Estudante.hpp"
#include "Professor.hpp"
#include "Bibliotecario.hpp"
#include "TecnicoManutencao.hpp"
    
    Interface::Interface(Dados *d): dados(d) {
        if (d == nullptr) {
            throw std::invalid_argument("Dados não pode ser nullptr.");
        }
    }
    
    void Interface::menuObras() {
        int n;
        do {
            std::cout << "========== MENU DE OBRAS ==========\n" << std::endl;
            std::cout << "1 - Pesquisar obra\n2 - Listar obras\n3 - Cadastrar obra\n4 - Atualizar obra\n5 - Remover obra\n0 - Voltar\n\nOpção:" << std::endl;
        
            n = lerOpcao(0, 5);
            switch (n)
            {
            case 0:
                return;
            
            case 1:
                menuPesquisaObras();
                break;

            case 2: {
                const std::vector<Obra*>& obras = dados->getCatalogo()->listarObras();
                if (obras.empty()) {
                    std::cout << "Nenhuma obra foi cadastrada até então." << std::endl;
                } else {
                    for (Obra *o : obras) {
                        if (o != nullptr) {
                            o->printObra();
                            std::cout << "Disponibilidade: " << (o->isDisponivel() ? "Disponível" : "Indisponível") << std::endl;
                            std::cout << "Danificada: " << (o->isDanificado() ? "Sim" : "Não") << std::endl;
                            std::cout << "Em manutenção: " << (o->isEmManutencao() ? "Sim\n" : "Não\n") << std::endl;
                        }
                    }
                }
                break;
            }
            
            case 3:
                menuCadastroObras();
                break;

            case 4:
                menuAtualizacoes();
                break;

            case 5: {
                int id;
                std::cout << "Digite o número de identificação da obra: " << std::endl;
                id = lerOpcao(1, std::numeric_limits<int>::max());
                bool r = dados->removerObra(id);
                if (r) {
                    std::cout << "Obra removida com sucesso." << std::endl;
                } else {
                    std::cout << "Obra não encontrada ou não pôde ser removida." << std::endl;
                }
                break;
            }
            
            default:
                break;
            }
        } while (n != 0);
    }
    
    void Interface::menuUsuarios() {
        int n;
        do {
            std::cout << "========== MENU DE USUÁRIOS ==========\n" << std::endl;
            std::cout << "1 - Cadastrar usuário\n2 - Consultar usuário\n3 - Remover usuário\n0 - Voltar\n\nOpção:" << std::endl;
        
            n = lerOpcao(0, 3);
            switch (n)
            {
            case 0:
                return;
            
            case 1:
                
                break;

            case 2:
                
                break;
            
            case 3:
                
                break;
            
            default:
                break;
            }
        } while (n != 0);
    }
    
    void Interface::menuEmprestimos() {
        int n;
        do {
            std::cout << "========== MENU DE EMPRÉSTIMOS ==========\n" << std::endl;
            std::cout << "1 - Realizar empréstimo\n2 - Consultar empréstimo\n3 - Devolver obra\n4 - Renovar empréstimo\n0 - Voltar\n\nOpção:" << std::endl;
        
            n = lerOpcao(0, 4);
            switch (n)
            {
            case 0:
                return;
            
            case 1:
                
                break;

            case 2:
                
                break;
            
            case 3:
                
                break;

            case 4:
                
                break;
            
            default:
                break;
            }
        } while (n != 0);
    }
    
    void Interface::menuManutencoes() {
        int n;
        do {
            std::cout << "========== MENU DE MANUTENÇÕES ==========\n" << std::endl;
            std::cout << "1 - Encaminhar para manutenção\n2 - Consultar manutenção\n3 - Concluir manutenção\n0 - Voltar\n\nOpção:" << std::endl;
        
            n = lerOpcao(0, 3);
            switch (n)
            {
            case 0:
                return;
            
            case 1:
                
                break;

            case 2:
                
                break;
            
            case 3:
                
                break;
            
            default:
                break;
            }
        } while (n != 0);
    }

    void Interface::menuPesquisaObras() {
        int n;
        std::string str;
        do {
            std::cout << "========== MENU DE PESQUISA ==========\n" << std::endl;
            std::cout << "1 - Pesquisar por título\n2 - Pesquisar por autor\n3 - Pesquisar por id\n0 - Voltar\n\nOpção:" << std::endl;
        
            n = lerOpcao(0, 3);
            switch (n)
            {
            case 0:
                return;
            
            case 1: {
                std::cout << "Digite o título da obra: " << std::endl;
                std::getline(std::cin, str);
                Obra *o = dados->getCatalogo()->buscarPorTitulo(str);
                if (o != nullptr) {
                    o->printObra();
                } else {
                    std::cout << "Obra não encontrada." << std::endl;
                }
                break;
            }

            case 2: {
                std::cout << "Digite o nome do autor da obra: " << std::endl;
                std::getline(std::cin, str);
                const std::vector<Obra*> obras = dados->getCatalogo()->buscarPorAutor(str);
                if (obras.empty()) {
                    std::cout << "Nennhuma obra desse autor foi encontrada." << std::endl;
                } else {
                    for (Obra *o : obras) {
                        if (o != nullptr) {
                            o->printObra();
                        }
                    }
                }
                break;
            }
            
            case 3: {
                int id = lerOpcao(1, std::numeric_limits<int>::max());
                Obra *o = dados->getCatalogo()->buscarPorId(id);
                if (o != nullptr) {
                    o->printObra();
                } else {
                    std::cout << "Obra não encontrada." << std::endl;
                }
                break;
            }
            
            default:
                break;
            }
        } while (n != 0);
    }

    void Interface::menuAtualizacoes() {
        std::cout << "Digite o número de identificação da obra a ser modificada: " << std::endl;
        int id = lerOpcao(1, std::numeric_limits<int>::max());
        
        Obra *o = dados->getCatalogo()->buscarPorId(id);
        if (Livro *l = dynamic_cast<Livro*>(o)) {
            menuAtualizacoesLivro(l);
        } else if (Artigo *a = dynamic_cast<Artigo*>(o)) {
            menuAtualizacoesArtigo(a);
        } else {
            std::cout << "Obra não encontrada." << std::endl;
        }
    }

    void Interface::menuCadastroObras() {
        std::cout << "========== MENU DE CADASTRO ==========\n" << std::endl;
        std::cout << "1 - Livro\n2 - Artigo\n0 - Voltar\n\nOpção:" << std::endl;
            
        int n = lerOpcao(0, 2);
        if (n == 0) {
            return;
        }

        std::string titulo, autor;
        std::cout << "Digite o título: ";
        std::getline(std::cin, titulo);
        std::cout << "Digite o autor: ";
        std::getline(std::cin, autor);

        int id = dados->getCatalogo()->gerarProximoId();
        if (id == 0) {
            std::cout << "Não foi possível gerar um novo ID." << std::endl;
            return;
        }

        Obra* nova = nullptr;
        try {
            if (n == 1) {
                std::string genero;
                int edicao;
                std::cout << "Digite o gênero: ";
                std::getline(std::cin, genero);
                std::cout << "Digite a edição: ";
                edicao = lerOpcao(1, std::numeric_limits<int>::max());

                nova = new Livro(titulo, autor, id, genero, edicao);
            } else if (n == 2) {
                std::string area;
                int ano;
                std::cout << "Digite a área: ";
                std::getline(std::cin, area);
                std::cout << "Digite o ano de publicação: ";
                ano = lerOpcao(1, 9999);

                nova = new Artigo(titulo, autor, id, area, ano);
            } else std::cout << "Não foi possível cadastrar a obra." << std::endl;

            if (dados->getCatalogo()->cadastrarObra(nova)) {
                std::cout << "Obra cadastrada com sucesso!" << "\nID: " << id << std::endl;
            } else {
                delete nova;
                std::cout << "Não foi possível cadastrar a obra." << std::endl;
            }
        } catch (const std::invalid_argument &e) {
            delete nova;
            std::cout << "Erro ao cadastrar obra: " << e.what() << std::endl;
        }
    }
    
    void Interface::menuAtualizacoesLivro(Livro *l) {
        int n;
        std::string str;
        do {
            std::cout << "========== MENU DE ATUALIZAÇÕES DE LIVROS ==========\n" << std::endl;
            std::cout << "1 - Atualizar título\n2 - Atualizar autor\n3 - Atualizar gênero\n4 - Atualizar edição\n0 - Voltar\n\nOpção:" << std::endl;
            
            n = lerOpcao(0, 4);
            switch (n)
            {
            case 0:
                return;
            
            case 1: {
                std::cout << "Digite o novo título do livro: " << std::endl;
                std::getline(std::cin, str);
                if (!str.empty()) {
                    l->setTitulo(str);
                }
                break;
            }                

            case 2: {
                std::cout << "Digite o novo autor do livro: " << std::endl;
                std::getline(std::cin, str);
                if (!str.empty()) {
                    l->setAutor(str);
                }
                break;
            }
            
            case 3: {
                std::cout << "Digite o novo gênero do livro: " << std::endl;
                std::getline(std::cin, str);
                if (!str.empty()) {
                    l->setGenero(str);
                }
                break;
            }

            case 4: {
                std::cout << "Digite a nova edição do livro: " << std::endl;
                int e = lerOpcao(1, std::numeric_limits<int>::max());
                l->setEdicao(e);
                break;
            }
            
            default:
                break;
            }
        } while (n != 0);
    }

    void Interface::menuAtualizacoesArtigo(Artigo *a) {
        int n;
        std::string str;
        do {
            std::cout << "========== MENU DE ATUALIZAÇÕES DE ARTIGOS ==========\n" << std::endl;
            std::cout << "1 - Atualizar título\n2 - Atualizar autor\n3 Atualizar área\n4 - Atualizar ano de publicação\n0 - Voltar\n\nOpção:" << std::endl;
            
            n = lerOpcao(0, 4);
            switch (n)
            {
            case 0:
                return;
            
            case 1: {
                std::cout << "Digite o novo título do artigo: " << std::endl;
                std::getline(std::cin, str);
                if (!str.empty()) {
                    a->setTitulo(str);
                }
                break;
            }                

            case 2: {
                std::cout << "Digite o novo autor do artigo: " << std::endl;
                std::getline(std::cin, str);
                if (!str.empty()) {
                    a->setAutor(str);
                }
                break;
            }
            
            case 3: {
                std::cout << "Digite a nova área do artigo: " << std::endl;
                std::getline(std::cin, str);
                if (!str.empty()) {
                    a->setArea(str);
                }
                break;
            }

            case 4: {
                std::cout << "Digite o novo ano de publicação: " << std::endl;
                int ano = lerOpcao(1, 9999);
                a->setAno(ano);
                break;
            }
            
            default:
                break;
            }
        } while (n != 0);
    }

    int Interface::lerOpcao(int min, int max) {
        int n;
        while (true) {
            if (std::cin >> n) {
                try {
                    tratamento.isNumeroValido(n, min, max);
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    return n;
                } catch (const std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            } else {
                if (std::cin.eof()) {
                    throw std::runtime_error("Entrada encerrada pelo usuário.");
                }
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Entrada inválida. Digite um número.\n";
            }
        }
    }

    std::string Interface::lerTexto(const std::string &msg) {
        while (true) {
            std::cout << msg;
            std::string texto;
            if (!std::getline(std::cin, texto)) {
                throw std::runtime_error("Entrada encerrada pelo usuário.");
            }
            if (texto.find_first_not_of(" \t\n\r\f\v") == std::string::npos) {
                std::cout << "O campo não pode ficar vazio. Tente novamente.\n";
                continue;
            }
            const std::string textoLimpo = texto.substr(texto.find_first_not_of(" \t\n\r\f\v"), texto.find_last_not_of(" \t\n\r\f\v") - texto.find_first_not_of(" \t\n\r\f\v") + 1);
            try {
                tratamento.isCaracterValido(textoLimpo, ";", "Campo");
                return textoLimpo;
            } catch (const std::invalid_argument &e) {
                std::cout << e.what() << "\n";
            }
        }
    }

    Data Interface::obterDataAtual() const {
        const std::time_t agora = std::time(nullptr);
        const std::tm *dataLocal = std::localtime(&agora);
        if (dataLocal == nullptr) {
            throw std::runtime_error("Não foi possível obter a data atual do computador.");
        }
        return Data(dataLocal->tm_mday, dataLocal->tm_mon + 1, dataLocal->tm_year + 1900);
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