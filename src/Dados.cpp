#include "Dados.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <istream>
#include <utility>
#include "Estudante.hpp"
#include "Emprestimo.hpp"
#include "Professor.hpp"
#include "Pessoa.hpp"
#include "Artigo.hpp"
#include "Livro.hpp"
#include "Data.hpp"
#include "Usuarios.hpp"
#include "Catalogo.hpp"
#include "Manutencao.hpp"
#include "TecnicoManutencao.hpp"
#include "Bibliotecario.hpp"

    Dados::Dados(Usuarios *u, Catalogo *c):
    usuarios(u), catalogo(c) {}

    Usuarios* Dados::getUsuarios() {
        return usuarios;
    }

    const Usuarios* Dados::getUsuarios() const {
        return usuarios;
    }

    Catalogo* Dados::getCatalogo() {
        return catalogo;
    }

    const Catalogo* Dados::getCatalogo() const {
        return catalogo;
    }

    Dados::~Dados() {
        delete usuarios;
        delete catalogo;
    }

    void Dados::salvarEmprestimos(std::ofstream &out, const std::vector<Emprestimo*> &emprestimos) const {
        for (Emprestimo *e : emprestimos) {
            out << e->getObra().getID() << ";"
                << e->getRetirada().getDia() << ";"
                << e->getRetirada().getMes() << ";"
                << e->getRetirada().getAno() << ";"
                << e->getDevolucao().getDia() << ";"
                << e->getDevolucao().getMes() << ";"
                << e->getDevolucao().getAno() << ";"
                << e->isAtivo() << ";";
        }
    }

    void Dados::carregarEmprestimos(std::ifstream &in, Pessoa *pessoa) {
        int idObra;
        int dia;
        int mes;
        int ano;
        bool ativo;
        int numeroEmprestimos;

        Obra *obra;
        Emprestimo *emprestimo;
        std::vector<Emprestimo*> emprestimos;

        if (pessoa == nullptr || catalogo == nullptr) {
            in.setstate(std::ios::failbit);
            return;
        }
        if (!(in >> numeroEmprestimos) || numeroEmprestimos < 0) {
            in.setstate(std::ios::failbit);
            return;
        }

        in.ignore(1, ';');

        for (int i = 0; i < numeroEmprestimos; i++) {
            if (!(in >> idObra)) {
                break;
            }
            in.ignore(1, ';');
            if (!(in >> dia)) break;
            in.ignore(1, ';');
            if (!(in >> mes)) break;
            in.ignore(1, ';');
            if (!(in >> ano)) break;
            in.ignore(1, ';');

            Data data1(dia, mes, ano);

            if (!(in >> dia)) break;
            in.ignore(1, ';');
            if (!(in >> mes)) break;
            in.ignore(1, ';');
            if (!(in >> ano)) break;
            in.ignore(1, ';');

            Data data2(dia, mes, ano);

            if (!(in >> ativo)) break;
            in.ignore(1, ';');

            obra = catalogo->buscarPorId(idObra);

            if (obra == nullptr) {
                std::cerr << "Obra não encontrada ao carregar empréstimo: "
                        << idObra << std::endl;
                in.setstate(std::ios::failbit);
                break;
            }

            emprestimo = new Emprestimo(*obra, *pessoa, data1);
            emprestimo->setDevolucao(data2);
            emprestimo->setAtivo(ativo);
            emprestimos.push_back(emprestimo);
        }
        if (!in) {
            for (Emprestimo *e : emprestimos) {
                delete e;
            }
            return;
        }
        pessoa->setEmprestimos(emprestimos);
    }

    void Dados::salvarDados() {
        if (usuarios == nullptr || catalogo == nullptr) {
            std::cerr << "Não foi possível salvar os dados: usuários ou catálogo não inicializados."
                    << std::endl;
            return;
        }

        std::ofstream arquivoUsuarios("usuario.txt");
        if (!arquivoUsuarios.is_open()) {
            std::cerr << "Erro ao abrir o arquivo para salvar os dados -> Usuarios." << std::endl;
            return;
        }

        std::ofstream arquivoObras("obras.txt");
        if (!arquivoObras.is_open()) {
            std::cerr << "Erro ao abrir o arquivo para salvar os dados -> Obras." << std::endl;
            return;
        }

        for (Obra *o : catalogo->listarObras()) {
            if (o == nullptr) {
                continue;
            }
            if (Artigo *a = dynamic_cast<Artigo*>(o)) {
                arquivoObras << "Artigo" << ";";
                arquivoObras << a->getTitulo() << ";";
                arquivoObras << a->getAutor() << ";";
                arquivoObras << a->getID() << ";";
                arquivoObras << a->isDisponivel() << ";";
                arquivoObras << a->isDanificado() << ";";
                arquivoObras << a->getArea() << ";";
                arquivoObras << a->getAno() << std::endl;
            } else if (Livro *l = dynamic_cast<Livro*>(o)) {
                arquivoObras << "Livro" << ";";
                arquivoObras << l->getTitulo() << ";";
                arquivoObras << l->getAutor() << ";";
                arquivoObras << l->getID() << ";";
                arquivoObras << l->isDisponivel() << ";";
                arquivoObras << l->isDanificado() << ";";
                arquivoObras << l->getGenero() << ";";
                arquivoObras << l->getEdicao() << std::endl;
            } else {
                std::cerr << "Tipo de obra desconhecido. Não foi possível salvar os dados."
                        << std::endl;
            }
        }

        const std::vector<std::pair<Pessoa*, int>> &usuariosSalvar = usuarios->getUsuarios();

        for (const std::pair<Pessoa*, int> &usuario : usuariosSalvar) {
            if (usuario.first == nullptr) {
                continue;
            }
            if (Estudante *estudante = dynamic_cast<Estudante*>(usuario.first)) {
                arquivoUsuarios << "Estudante" << ";";
                arquivoUsuarios << usuario.second << ";";
                arquivoUsuarios << estudante->getNome() << ";";
                arquivoUsuarios << estudante->getCPF() << ";";
                arquivoUsuarios << estudante->getCurso() << ";";
                arquivoUsuarios << estudante->getMatricula() << ";";
                arquivoUsuarios << estudante->getNumEmprestimos() << ";";

                salvarEmprestimos(arquivoUsuarios, estudante->getEmprestimos());
                arquivoUsuarios << std::endl;
            } else if (Professor *professor = dynamic_cast<Professor*>(usuario.first)) {
                arquivoUsuarios << "Professor" << ";";
                arquivoUsuarios << usuario.second << ";";
                arquivoUsuarios << professor->getNome() << ";";
                arquivoUsuarios << professor->getCPF() << ";";
                arquivoUsuarios << professor->getArea() << ";";
                arquivoUsuarios << professor->getNumEmprestimos() << ";";

                salvarEmprestimos(arquivoUsuarios, professor->getEmprestimos());
                arquivoUsuarios << std::endl;
            } else if (TecnicoManutencao *tecnico = dynamic_cast<TecnicoManutencao*>(usuario.first)) {
                arquivoUsuarios << "TecnicoManutencao" << ";";
                arquivoUsuarios << usuario.second << ";";
                arquivoUsuarios << tecnico->getNome() << ";";
                arquivoUsuarios << tecnico->getCPF() << ";";
                arquivoUsuarios << tecnico->getNumEmprestimos() << ";";

                salvarEmprestimos(arquivoUsuarios, tecnico->getEmprestimos());
                arquivoUsuarios << tecnico->getManutencoes().size() << ";";

                for (Manutencao *m : tecnico->getManutencoes()) {
                    arquivoUsuarios << m->getObra()->getID() << ";";
                    arquivoUsuarios << m->getTecnico()->getCPF() << ";";
                    arquivoUsuarios << m->getDano() << ";";
                    arquivoUsuarios << m->getReparo() << ";";
                    arquivoUsuarios << m->getInicio().getDia() << ";";
                    arquivoUsuarios << m->getInicio().getMes() << ";";
                    arquivoUsuarios << m->getInicio().getAno() << ";";
                    arquivoUsuarios << static_cast<int>(m->getEstado()) << ";";
                }
                arquivoUsuarios << std::endl;
            } else if (Bibliotecario *bibliotecario = dynamic_cast<Bibliotecario*>(usuario.first)) {
                arquivoUsuarios << "Bibliotecario" << ";";
                arquivoUsuarios << usuario.second << ";";
                arquivoUsuarios << bibliotecario->getNome() << ";";
                arquivoUsuarios << bibliotecario->getCPF() << ";";
                arquivoUsuarios << bibliotecario->getNumEmprestimos() << ";";

                salvarEmprestimos(arquivoUsuarios, bibliotecario->getEmprestimos());
                arquivoUsuarios << std::endl;
            } else {
                std::cerr << "Tipo de usuário desconhecido. Não foi possível salvar os dados."
                        << std::endl;
            }
        }

        arquivoUsuarios.close();
        arquivoObras.close();

        if (!arquivoUsuarios || !arquivoObras) {
            std::cerr << "Erro durante a gravação dos arquivos de dados." << std::endl;
        }
    }

    void Dados::carregarDados() {
        std::ifstream arquivoUsuarios("usuario.txt");
        if (!arquivoUsuarios.is_open()) {
            std::cerr << "Erro ao abrir o arquivo para ler dados -> Usuarios." << std::endl;
            return;
        }

        std::ifstream arquivoObras("obras.txt");
        if (!arquivoObras.is_open()) {
            std::cerr << "Erro ao abrir o arquivo para ler dados -> Obras." << std::endl;
            return;
        }

        delete usuarios;
        delete catalogo;
        catalogo = new Catalogo();
        usuarios = new Usuarios();

        int id;
        int idObra;
        int dia;
        int mes;
        int ano;
        int edicao;
        bool ativo;
        bool danificado;
        bool disponivel;

        std::string nome;
        std::string area;
        std::string cpf;
        std::string genero;
        std::string titulo;
        std::string autor;
        std::string curso;
        std::string matricula;
        std::string dano;
        std::string reparo;
        std::string tipo;

        Obra *obra;
        Pessoa *pessoa;

        int estado;
        int numeroManutencao;

        while (std::getline(arquivoObras, tipo, ';')) {
            if (tipo == "Artigo") {
                std::getline(arquivoObras, titulo, ';');
                std::getline(arquivoObras, autor, ';');
                arquivoObras >> id;
                arquivoObras.ignore(1, ';');
                arquivoObras >> disponivel;
                arquivoObras.ignore(1, ';');
                arquivoObras >> danificado;
                arquivoObras.ignore(1, ';');
                std::getline(arquivoObras, area, ';');
                arquivoObras >> ano;

                if (!arquivoObras) {
                    std::cerr << "Erro ao ler os dados de um artigo." << std::endl;
                    return;
                }

                Artigo *artigo = new Artigo(titulo, autor, id, area, ano);

                if (catalogo->cadastrarObra(artigo)) {
                    artigo->setDanificado(danificado);
                    artigo->setDisponivel(disponivel);
                } else {
                    delete artigo;
                    std::cerr << "Não foi possível cadastrar o artigo de ID "
                            << id << "." << std::endl;
                }
            } else if (tipo == "Livro") {
                std::getline(arquivoObras, titulo, ';');
                std::getline(arquivoObras, autor, ';');
                arquivoObras >> id;
                arquivoObras.ignore(1, ';');
                arquivoObras >> disponivel;
                arquivoObras.ignore(1, ';');
                arquivoObras >> danificado;
                arquivoObras.ignore(1, ';');
                std::getline(arquivoObras, genero, ';');
                arquivoObras >> edicao;

                if (!arquivoObras) {
                    std::cerr << "Erro ao ler os dados de um livro." << std::endl;
                    return;
                }

                Livro *livro = new Livro(titulo, autor, id, genero, edicao);

                if (catalogo->cadastrarObra(livro)) {
                    livro->setDisponivel(disponivel);
                    livro->setDanificado(danificado);
                } else {
                    delete livro;
                    std::cerr << "Não foi possível cadastrar o livro de ID "
                            << id << "." << std::endl;
                }
            }
            arquivoObras.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        while (std::getline(arquivoUsuarios, tipo, ';')) {
            if (tipo == "Estudante") {
                arquivoUsuarios >> id;
                arquivoUsuarios.ignore(1, ';');
                std::getline(arquivoUsuarios, nome, ';');
                std::getline(arquivoUsuarios, cpf, ';');
                std::getline(arquivoUsuarios, curso, ';');
                std::getline(arquivoUsuarios, matricula, ';');

                if (!arquivoUsuarios) {
                    std::cerr << "Erro ao ler os dados de um estudante." << std::endl;
                    return;
                }

                usuarios->adicionarUsuario(new Estudante(nome, cpf, curso, matricula), id);
                pessoa = usuarios->buscarUsuarioId(id);
                carregarEmprestimos(arquivoUsuarios, pessoa);
            } else if (tipo == "Professor") {
                arquivoUsuarios >> id;
                arquivoUsuarios.ignore(1, ';');
                std::getline(arquivoUsuarios, nome, ';');
                std::getline(arquivoUsuarios, cpf, ';');
                std::getline(arquivoUsuarios, area, ';');

                if (!arquivoUsuarios) {
                    std::cerr << "Erro ao ler os dados de um professor." << std::endl;
                    return;
                }

                usuarios->adicionarUsuario(new Professor(nome, cpf, area), id);
                pessoa = usuarios->buscarUsuarioId(id);
                carregarEmprestimos(arquivoUsuarios, pessoa);
            } else if (tipo == "Bibliotecario") {
                arquivoUsuarios >> id;
                arquivoUsuarios.ignore(1, ';');
                std::getline(arquivoUsuarios, nome, ';');
                std::getline(arquivoUsuarios, cpf, ';');

                if (!arquivoUsuarios) {
                    std::cerr << "Erro ao ler os dados de um bibliotecário." << std::endl;
                    return;
                }

                usuarios->adicionarUsuario(new Bibliotecario(nome, cpf), id);
                pessoa = usuarios->buscarUsuarioId(id);
                carregarEmprestimos(arquivoUsuarios, pessoa);
            } else if (tipo == "TecnicoManutencao") {
                arquivoUsuarios >> id;
                arquivoUsuarios.ignore(1, ';');
                std::getline(arquivoUsuarios, nome, ';');
                std::getline(arquivoUsuarios, cpf, ';');

                if (!arquivoUsuarios) {
                    std::cerr << "Erro ao ler os dados de um técnico de manutenção." << std::endl;
                    return;
                }

                usuarios->adicionarUsuario(new TecnicoManutencao(nome, cpf), id);
                pessoa = usuarios->buscarUsuarioId(id);
                carregarEmprestimos(arquivoUsuarios, pessoa);

                if (!arquivoUsuarios) {
                    std::cerr << "Erro ao carregar os empréstimos do técnico." << std::endl;
                    return;
                }
                if (!(arquivoUsuarios >> numeroManutencao) || numeroManutencao < 0) {
                    std::cerr << "Quantidade de manutenções inválida." << std::endl;
                    return;
                }

                arquivoUsuarios.ignore(1, ';');
                std::vector<Manutencao*> manutencoes;
                TecnicoManutencao *tecnico = static_cast<TecnicoManutencao*>(pessoa);

                for (int i = 0; i < numeroManutencao; i++) {
                    arquivoUsuarios >> idObra;
                    arquivoUsuarios.ignore(1, ';');
                    std::getline(arquivoUsuarios, cpf, ';');
                    std::getline(arquivoUsuarios, dano, ';');
                    std::getline(arquivoUsuarios, reparo, ';');
                    arquivoUsuarios >> dia;
                    arquivoUsuarios.ignore(1, ';');
                    arquivoUsuarios >> mes;
                    arquivoUsuarios.ignore(1, ';');
                    arquivoUsuarios >> ano;
                    arquivoUsuarios.ignore(1, ';');
                    arquivoUsuarios >> estado;
                    arquivoUsuarios.ignore(1, ';');

                    if (!arquivoUsuarios ||
                        estado < static_cast<int>(EstadoManutencao::PENDENTE) ||
                        estado > static_cast<int>(EstadoManutencao::CONCLUIDA)) {

                        std::cerr << "Erro ao ler uma manutenção do técnico." << std::endl;

                        for (Manutencao *m : manutencoes) {
                            delete m;
                        }
                        return;
                    }

                    Data data(dia, mes, ano);
                    obra = catalogo->buscarPorId(idObra);

                    if (obra == nullptr) {
                        std::cerr << "Obra não encontrada ao carregar manutenção: "
                                << idObra << std::endl;

                        for (Manutencao *m : manutencoes) {
                            delete m;
                        }
                        return;
                    }

                    Manutencao *manutencao = new Manutencao(obra, tecnico, dano, data);
                    manutencao->registrarReparo(reparo);
                    manutencao->setEstado(static_cast<EstadoManutencao>(estado));
                    manutencoes.push_back(manutencao);
                }
                tecnico->setManutencoes(manutencoes);
            }

            if (!arquivoUsuarios) {
                std::cerr << "Erro ao carregar os dados de um usuário." << std::endl;
                return;
            }
            arquivoUsuarios.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        arquivoUsuarios.close();
        arquivoObras.close();
    }