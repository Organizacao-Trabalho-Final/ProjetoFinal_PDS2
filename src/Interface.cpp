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
#include "Emprestimo.hpp"
#include "Data.hpp"
#include "Obra.hpp"
#include "Livro.hpp"
#include "Artigo.hpp"
#include "Pessoa.hpp"
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

    void Interface::executar() {
        int n;
        do {
            std::cout << "========== SISTEMA DE GERENCIAMENTO DA BIBLIOTECA ==========\n" << std::endl;
            std::cout << "1 - Obras\n2 - Usuários\n3 - Empréstimos\n4 - Manutenções\n0 - Salvar e sair\n\nOpção:" << std::endl;
        
            n = lerOpcao(0, 4);
            switch (n)
            {
            case 0:
                std::cout << "Encerrando o sistema..." << std::endl;
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
                std::cout << "Digite o número de identificação da obra: " << std::endl;
                int id = lerOpcao(1, std::numeric_limits<int>::max());
                bool r = dados->removerObra(id);
                if (r) {
                    std::cout << "Obra removida com sucesso." << std::endl;
                } else {
                    std::cout << "Obra não encontrada ou associada a empréstimo/manutenção." << std::endl;
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
            std::cout << "1 - Cadastrar usuário\n2 - Pesquisar usuário\n3 - Remover usuário\n4 - Listar usuários\n0 - Voltar\n\nOpção:" << std::endl;
        
            n = lerOpcao(0, 4);
            switch (n)
            {
            case 0:
                return;
            
            case 1:
                menuCadastroUsuarios();
                break;

            case 2:
                menuPesquisaUsuarios();
                break;
            
            case 3: {
                std::string cpf = lerTexto("CPF do usuário que deseja remover: ");
                Pessoa *p = dados->getUsuarios()->buscarUsuarioCPF(cpf);

                if (p == nullptr) {
                    std::cout << "Usuário não encontrado." << std::endl;
                    break;
                }
                if (!p->getEmprestimos().empty()) {
                    std::cout << "Não é possível remover: o usuário possui histórico de empréstimos." << std::endl;
                    break;
                }

                TecnicoManutencao *tecnico = dynamic_cast<TecnicoManutencao*>(p);
                if (tecnico != nullptr && !tecnico->getManutencoes().empty()) {
                    std::cout << "Não é possível remover: o técnico possui manutenções registradas." << std::endl;
                    break;
                }
                if (dados->getUsuarios()->removerUsuarioCPF(cpf)) {
                    std::cout << "Usuário removido com sucesso." << std::endl;
                } else {
                    std::cout << "Não foi possível remover o usuário." << std::endl;
                }
                break;
            }

            case 4: {
                const std::vector<std::pair<Pessoa*, int> > &lista = dados->getUsuarios()->getUsuarios();
                if (lista.empty()) {
                    std::cout << "Nenhum usuário cadastrado." << std::endl;
                } else {
                    for (const auto &registro : lista) {
                        printUsuario(registro.first, registro.second);
                    }
                }
                break;
            }
            
            default:
                break;
            }
        } while (n != 0);
    }
    
    void Interface::menuEmprestimos() {
        int n;
        do {
            std::cout << "========== MENU DE EMPRÉSTIMOS ==========\n" << std::endl;
            std::cout << "1 - Realizar empréstimo\n2 - Consultar empréstimo\n3 - Devolver obra\n4 - Renovar empréstimo\n5 - Aprovar renovação\n0 - Voltar\n\nOpção:" << std::endl;
        
            n = lerOpcao(0, 5);
            switch (n)
            {
            case 0:
                return;
            
            case 1:
                realizarEmprestimo();
                break;

            case 2:
                
                break;
            
            case 3:
                
                break;

            case 4:
                
                break;

            case 5:
                
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
            std::cout << "========== MENU DE PESQUISA DE OBRAS ==========\n" << std::endl;
            std::cout << "1 - Pesquisar por título\n2 - Pesquisar por autor\n3 - Pesquisar por ID\n0 - Voltar\n\nOpção:" << std::endl;
        
            n = lerOpcao(0, 3);
            switch (n)
            {
            case 0:
                return;
            
            case 1: {
                str = lerTexto("Digite o título da obra: ");
                Obra *o = dados->getCatalogo()->buscarPorTitulo(str);
                if (o != nullptr) {
                    o->printObra();
                } else {
                    std::cout << "Obra não encontrada." << std::endl;
                }
                break;
            }

            case 2: {
                str = lerTexto("Digite o nome do autor da obra: ");
                const std::vector<Obra*> obras = dados->getCatalogo()->buscarPorAutor(str);
                if (obras.empty()) {
                    std::cout << "Nenhuma obra desse autor foi encontrada." << std::endl;
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
                std::cout << "Digite o ID da obra: ";
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
        std::cout << "Digite o ID da obra a ser modificada: " << std::endl;
        int id = lerOpcao(1, std::numeric_limits<int>::max());
        
        Obra *o = dados->getCatalogo()->buscarPorId(id);
        if (Livro *l = dynamic_cast<Livro*>(o)) {
            menuAtualizacoesLivro(l);
        } else if (Artigo *a = dynamic_cast<Artigo*>(o)) {
            menuAtualizacoesArtigo(a);
        } else std::cout << "Obra não encontrada." << std::endl;
    }

    void Interface::menuCadastroObras() {
        std::cout << "========== MENU DE CADASTRO DE OBRAS ==========\n" << std::endl;
        std::cout << "1 - Livro\n2 - Artigo\n0 - Voltar\n\nOpção:" << std::endl;
            
        int n = lerOpcao(0, 2);
        if (n == 0) {
            return;
        }

        Obra *nova = nullptr;
        try {
            const std::string titulo = lerTexto("Digite o título: ");
            const std::string autor = lerTexto("Digite o autor: ");
            int id = dados->getCatalogo()->gerarProximoId();

            if (id == 0) {
                std::cout << "Não foi possível gerar um novo ID." << std::endl;
                return;
            }

            if (n == 1) {
                const std::string genero = lerTexto("Digite o gênero: ");
                std::cout << "Digite a edição: ";
                const int edicao = lerOpcao(1, std::numeric_limits<int>::max());
                nova = new Livro(titulo, autor, id, genero, edicao);
            } else if (n == 2) {
                const std::string area = lerTexto("Digite a área: ");
                std::cout << "Digite o ano de publicação: ";
                const int ano = lerOpcao(1, 9999);
                nova = new Artigo(titulo, autor, id, area, ano);
            } else std::cout << "Não foi possível cadastrar a obra." << std::endl;

            if (dados->getCatalogo()->cadastrarObra(nova)) {
                nova = nullptr;
                std::cout << "Obra cadastrada com sucesso! ID: " << id << std::endl;
            } else {
                std::cout << "Não foi possível cadastrar a obra." << std::endl;
            }
        } catch (const std::invalid_argument &e) {
            delete nova;
            std::cout << "Erro ao cadastrar obra: " << e.what() << std::endl;
        }
        delete nova;
    }
    
    void Interface::menuAtualizacoesLivro(Livro *l) {
        int n;
        std::string str;
        do {
            std::cout << "========== MENU DE ATUALIZAÇÕES DE LIVROS ==========\n" << std::endl;
            std::cout << "1 - Atualizar título\n2 - Atualizar autor\n3 - Atualizar gênero\n4 - Atualizar edição\n0 - Voltar\n\nOpção:" << std::endl;
            
            n = lerOpcao(0, 4);
            try {
                switch (n)
                {
                case 0:
                    return;
                
                case 1: {
                    l->setTitulo(lerTexto("Digite o novo título: "));
                    break;
                }                

                case 2: {
                    l->setAutor(lerTexto("Digite o novo autor: "));
                    break;
                }
                
                case 3: {
                    l->setGenero(lerTexto("Digite o novo gênero: "));
                    break;
                }

                case 4: {
                    std::cout << "Digite a nova edição: ";
                    l->setEdicao(lerOpcao(1, std::numeric_limits<int>::max()));
                    break;
                }
                
                default:
                    break;
                }

                if (n != 0) {
                    std::cout << "Informação atualizada com sucesso." << std::endl;
                }
            } catch (const std::exception &e) {
                std::cout << "Não foi possível atualizar a obra: " << e.what() << std::endl;
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
            try {
                switch (n)
                {
                case 0:
                    return;
                
                case 1: {
                    a->setTitulo(lerTexto("Digite o novo título: "));
                    break;
                }                

                case 2: {
                    a->setAutor(lerTexto("Digite o novo autor: "));
                    break;
                }
                
                case 3: {
                    a->setArea(lerTexto("Digite a nova área: "));
                    break;
                }

                case 4: {
                    std::cout << "Digite o novo ano de publicação: ";
                    a->setAno(lerOpcao(1, 9999));
                    break;
                }
                
                default:
                    break;
                }

                if (n != 0) {
                    std::cout << "Informação atualizada com sucesso." << std::endl;
                }
            } catch (const std::exception &e) {
                std::cout << "Não foi possível atualizar a obra: " << e.what() << std::endl;
            }
        } while (n != 0);
    }

    void Interface::menuCadastroUsuarios() {
        std::cout << "========== MENU DE CADASTRO DE USUÁRIOS ==========\n" << std::endl;
        std::cout << "1 - Estudante\n2 - Professor\n3 - Bibliotecário\n4 - Técnico de manutenção\n0 - Voltar\n\nOpção:" << std::endl;

        int n = lerOpcao(0, 4);
        if (n == 0) {
            return;
        }

        Pessoa *novo = nullptr;
        try {
            std::string nome = lerTexto("Nome completo: ");
            std::string cpf = lerTexto("CPF: ");

            if (n == 1) {
                std::string curso = lerTexto("Curso: ");
                std::string matricula = lerTexto("Matrícul: ");
                novo = new Estudante(nome, cpf, curso, matricula);
            } else if (n == 2) {
                std::string area = lerTexto("Área de atuação: ");
                novo = new Professor(nome, cpf, area);
            } else if (n == 3) {
                novo = new Bibliotecario(nome, cpf);
            } else {
                novo = new TecnicoManutencao(nome, cpf);
            }

            int id = dados->getUsuarios()->adicionarUsuario(novo);
            if (id == 0) {
                std::cout << "Cadastro não realizado: CPF já cadastrado ou identificador indisponível." << std::endl;
            } else {
                novo = nullptr;
                std::cout << "Usuário cadastrado com sucesso! ID: " << id << std::endl;
            }
        } catch (const std::exception &e) {
            std::cout << "Erro ao cadastrar usuário: " << e.what() << '\n';
        }
        delete novo;
    }

    void Interface::menuPesquisaUsuarios() {
        std::cout << "========== MENU DE PESQUISA DE USUÁRIOS ==========\n" << std::endl;
        std::cout << "1 - Pesquisar por nome\n2 - Pesquisar por CPF\n3 - Pesquisar por ID\n0 - Voltar\n" << "Opção: " << std::endl;
        int n = lerOpcao(0, 3);
        Pessoa *p = nullptr;

        switch (n)
        {
        case 0:
            return;

        case 1: {
            p = dados->getUsuarios()->buscarUsuarioNome(lerTexto("Nome: "));
            break;
        }

        case 2: {
            p = dados->getUsuarios()->buscarUsuarioCPF(lerTexto("CPF: "));
            break;
        }

        case 3: {
            std::cout << "ID: ";
            p = dados->getUsuarios()->buscarUsuarioId(lerOpcao(1, std::numeric_limits<int>::max()));
            break;
        }
        
        default:
            break;
        }
    }

    void Interface::realizarEmprestimo() {
        Pessoa *u = dados->getUsuarios()->buscarUsuarioCPF(lerTexto("CPF: "));
        if (u == nullptr) {
            std::cout << "Usuário não encontrado." << std::endl;
            return;
        }
        if (dynamic_cast<Estudante*>(u) == nullptr && dynamic_cast<Professor*>(u) == nullptr) {
            std::cout << "Somente estudantes e professores podem realizar empréstimos." << std::endl;
            return;
        }

        std::cout << "ID da obra: ";
        Obra *o = dados->getCatalogo()->buscarPorId(lerOpcao(1, std::numeric_limits<int>::max()));
        if (o == nullptr) {
            std::cout << "Obra não encontrada." << std::endl;
            return;
        }
        if (!o->isDisponivel()) {
            std::cout << "A obra está indisponível no momento." << std::endl;
            return;
        }
        if (o->isDanificado() || o->isEmManutencao()) {
            std::cout<< "A obra está danificada ou em manutenção e não pode ser emprestada." << std::endl;
            return;
        }
        if (Estudante *e = dynamic_cast<Estudante*>(u)) {
            if (dynamic_cast<Livro*>(o) == nullptr) {
                std::cout << "Estudantes podem emprestar somente livros." << std::endl;
                return;
            }
            if (e->getEmprestimosAtivos() >= e->getMaxEmprestimos()) {
                std::cout << "O estudante atingiu o limite de empréstimos ativos." << std::endl;
                return;
            }
        } else if (Professor *p = dynamic_cast<Professor*>(u)) {
            if (p->getEmprestimosAtivos() >= p->getMaxEmprestimos()) {
                std::cout << "O professor atingiu o limite de empréstimos ativos." << std::endl;
                return;
            }
        }

        Bibliotecario *b = selecionarBibliotecario();
        if (b == nullptr) {
            return;
        }

        Emprestimo *ep = b->aprovarEmprestimo(u, o, obterDataAtual());
        if (ep == nullptr) {
            std::cout << "O empréstimo não pôde ser aprovado. Verifique as regras de empréstimo." << std::endl;
        } else {
            std::cout << "Empréstimo realizado com sucesso." << std::endl;
            std::cout << "Data de retirada: " << ep->getRetirada().getData() << std::endl;
            std::cout << "Data prevista para devolução: " << ep->getDevolucao().getData() << std::endl;
            std::cout << "Prazo: " << u->getPrazo() << " dias." << std::endl;
        }
        return;
    }

    int Interface::lerOpcao(int min, int max) {
        int n;
        while (true) {
            if (std::cin >> n) {
                try {
                    tratamento.isNumeroValido(n, min, max, "Opção");
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
                std::cout << "Entrada inválida. Digite um número." << std::endl;
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
                std::cout << "O campo não pode ficar vazio. Tente novamente." << std::endl;
                continue;
            }
            std::string limpo = texto.substr(texto.find_first_not_of(" \t\n\r\f\v"), texto.find_last_not_of(" \t\n\r\f\v") - texto.find_first_not_of(" \t\n\r\f\v") + 1);
            try {
                tratamento.isCaracterValido(limpo, ";", "Campo");
                return limpo;
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

    void Interface::printUsuario(Pessoa *p, int id) const {
        if (p == nullptr) {
            return;
        }
        std::cout << "\n========================================\n";
        std::cout << "ID: " << id << "\nNome: " << p->getNome() << "\nCPF: " << p->getCPF() << std::endl;
        if (Estudante *e = dynamic_cast<Estudante*>(p)) {
            std::cout << "Categoria: Estudante\n" << "Curso: " << e->getCurso() << "\nMatrícula: " << e->getMatricula() << std::endl;
            std::cout << "Empréstimos ativos: " << e->getEmprestimosAtivos() << "\nEmpréstimos registrados: " << e->getNumEmprestimos() << std::endl;
        } else if (Professor *pf = dynamic_cast<Professor*>(p)) {
            std::cout << "Categoria: Professor\n" << "Área: " << pf->getArea() << std::endl;
            std::cout << "Empréstimos ativos: " << pf->getEmprestimosAtivos() << "\nEmpréstimos registrados: " << pf->getNumEmprestimos() << std::endl;
        } else if (dynamic_cast<Bibliotecario*>(p) != nullptr) {
            std::cout << "Categoria: Bibliotecário" << std::endl;
        } else if (TecnicoManutencao *tm = dynamic_cast<TecnicoManutencao*>(p)) {
            std::cout << "Categoria: Técnico de manutenção\n" << "Manutenções pendentes: " << tm->consultarManutencoesPendentes() << std::endl;
        }
        std::cout << "========================================\n";
    }

    Bibliotecario* Interface::selecionarBibliotecario() {
        std::string cpf = lerTexto("CPF do bibliotecário responsável: ");
        Pessoa *p = dados->getUsuarios()->buscarUsuarioCPF(cpf);

        Bibliotecario *b = dynamic_cast<Bibliotecario*>(p);
        if (b == nullptr) {
            std::cout << "Bibliotecário não encontrado. " << "Cadastre ou informe um CPF válido." << std::endl;
        }
        return b;
    }

    TecnicoManutencao* Interface::selecionarTecnico() {
        std::string cpf = lerTexto("CPF do técnico de manutenção: ");
        Pessoa *p = dados->getUsuarios()->buscarUsuarioCPF(cpf);

        TecnicoManutencao *tm = dynamic_cast<TecnicoManutencao*>(p);
        if (tm == nullptr) {
            std::cout << "Técnico de manutenção não encontrado." << std::endl;
        }
        return tm;
    }

    Emprestimo* Interface::selecionarEmprestimo(Pessoa *p, bool ativos, bool pendentes) {
        if (p == nullptr) {
            return nullptr;
        }

        std::vector<Emprestimo*> opcoes;
        const std::vector<Emprestimo*> &emprestimos = p->getEmprestimos();
        for (Emprestimo *e : emprestimos) {
            if (e == nullptr) {
                continue;
            }
            if (ativos && !e->isAtivo()) {
                continue;
            }
            if (pendentes && !e->isRenovacaoSolicitada()) {
                continue;
            }
            opcoes.push_back(e);
        }

        if (opcoes.empty()) {
            std::cout << "Nenhum empréstimo correspondente foi encontrado." << std::endl;
            return nullptr;
        }

        std::cout << "\nEmpréstimos encontrados:" << std::endl;
        for (std::size_t i = 0; i < opcoes.size(); ++i) {
            Emprestimo *e = opcoes[i];

            std::cout << i + 1 << " - " << e->getObra().getTitulo() << " (ID da obra: " << e->getObra().getID() << ")" << std::endl;
            std::cout << "Retirada: " << e->getRetirada().getData() << std::endl;
            std::cout << "Devolução: " << e->getDevolucao().getData() << std::endl;
            std::cout << "Empréstimo " << (e->isAtivo() ? "ativo" : "encerrado") << std::endl;
            if (e->isRenovacaoSolicitada()) {
                std::cout << "Renovação pendente." << std::endl;
            }
        }

        std::cout << "Selecione o empréstimo (0 para cancelar): ";
        int n = lerOpcao(0, static_cast<int>(opcoes.size()));
        if (n == 0) {
            return nullptr;
        }
        return opcoes[static_cast<std::size_t>(n - 1)];
    }