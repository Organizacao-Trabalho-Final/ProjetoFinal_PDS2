#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <istream>
#include <utility>
#include <stdexcept>
#include "Dados.hpp"
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
            if(e == nullptr)
                throw std::invalid_argument("Emprestimo nulo");
            out << e->getObra().getID() << ";"
                << e->getRetirada().getDia() << ";"
                << e->getRetirada().getMes() << ";"
                << e->getRetirada().getAno() << ";"
                << e->getDevolucao().getDia() << ";"
                << e->getDevolucao().getMes() << ";"
                << e->getDevolucao().getAno() << ";"
                << e->isAtivo() << ";"
                << e->isRenovacaoSolicitada() << ";";
        }
    }

    void Dados::carregarEmprestimos(std::ifstream &in, Pessoa *pessoa) {
        int idObra;
        int dia;
        int mes;
        int ano;
        int numeroEmprestimos;
        bool ativo;
        bool renovacaoSolicitada;

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

            if (!(in >> renovacaoSolicitada)) break;
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

            if (renovacaoSolicitada && !emprestimo->solicitarRenovacao()) {
                delete emprestimo;
                in.setstate(std::ios::failbit);
                break;
            }
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

        for (const auto &usuario : usuarios->getUsuarios()) {
            TecnicoManutencao *tecnico = dynamic_cast<TecnicoManutencao*>(usuario.first);
            if (tecnico == nullptr) {
                continue;
            }

            for (Manutencao *m : tecnico->getManutencoes()) {
                if (m == nullptr || m->getObra() == nullptr ||
                    m->getTecnico() != tecnico) {
                    std::cerr << "Manutenção inconsistente. Não foi possível salvar os dados." << std::endl;
                    return;
                }
            }
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

        arquivoObras << "ProximoId;" << catalogo->getProximoId() << std::endl;
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

    bool Dados::carregarDados() {
        Dados temp(new Usuarios(), new Catalogo());
        if (!temp.carregarDadosInterno()) {
            std::cerr << "Falha no carregamento. Os dados atuais foram preservados." << std::endl;
            return false;
        }
        std::swap(usuarios, temp.usuarios);
        std::swap(catalogo, temp.catalogo);
        return true;
    }

    bool Dados::carregarDadosInterno() {
        std::ifstream arquivoUsuarios("usuario.txt");
        std::ifstream arquivoObras("obras.txt");

        if (!arquivoUsuarios.is_open() && !arquivoObras.is_open()) {
            return true;
        }
        if (!arquivoUsuarios.is_open()) {
            std::cerr << "Erro ao abrir o arquivo para ler dados -> Usuarios." << std::endl;
            return false;
        }
        if (!arquivoObras.is_open()) {
            std::cerr << "Erro ao abrir o arquivo para ler dados -> Obras." << std::endl;
            return false;
        }

        int id;
        int idObra;
        int dia;
        int mes;
        int ano;
        int edicao;
        int maiorId = 0;
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
            if (tipo == "ProximoId") {
                if (!(arquivoObras >> id) || id <= 0) {
                    std::cerr << "Próximo ID de obras inválido." << std::endl;
                    return false;
                }
                catalogo->setProximoId(id);
            } else if (tipo == "Artigo") {
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
                    return false;
                }

                if (id <= 0) {
                    return false;
                }

                if (id > maiorId) {
                    maiorId = id;
                }

                Artigo *artigo = new Artigo(titulo, autor, id, area, ano);

                if (catalogo->cadastrarObra(artigo)) {
                    artigo->setDanificado(danificado);
                    artigo->setDisponivel(disponivel);
                } else {
                    delete artigo;
                    std::cerr << "Não foi possível cadastrar o artigo de ID " << id << "." << std::endl;
                    return false;
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
                    return false;
                }

                if (id <= 0) {
                    return false;
                }

                if (id > maiorId) {
                    maiorId = id;
                }

                Livro *livro = new Livro(titulo, autor, id, genero, edicao);

                if (catalogo->cadastrarObra(livro)) {
                    livro->setDisponivel(disponivel);
                    livro->setDanificado(danificado);
                } else {
                    delete livro;
                    std::cerr << "Não foi possível cadastrar o livro de ID " << id << "." << std::endl;
                    return false;
                }
            } else {
                std::cerr << "Tipo de obra desconhecido: " << tipo << std::endl;
                return false;
            }
            arquivoObras.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (maiorId == std::numeric_limits<int>::max()) {
            std::cerr << "Não existe próximo ID disponível." << std::endl;
            return false;
        }

        if (catalogo->getProximoId() <= maiorId) {
            catalogo->setProximoId(maiorId + 1);
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
                    return false;
                }

                pessoa = new Estudante(nome, cpf, curso, matricula);
                if (!usuarios->adicionarUsuario(pessoa, id)) {
                    delete pessoa;
                    std::cerr << "CPF ou ID duplicado ao carregar estudante: " << id << std::endl;
                    return false;
                }
                carregarEmprestimos(arquivoUsuarios, pessoa);
            } else if (tipo == "Professor") {
                arquivoUsuarios >> id;
                arquivoUsuarios.ignore(1, ';');
                std::getline(arquivoUsuarios, nome, ';');
                std::getline(arquivoUsuarios, cpf, ';');
                std::getline(arquivoUsuarios, area, ';');

                if (!arquivoUsuarios) {
                    std::cerr << "Erro ao ler os dados de um professor." << std::endl;
                    return false;
                }

                pessoa = new Professor(nome, cpf, area);
                if (!usuarios->adicionarUsuario(pessoa, id)) {
                    delete pessoa;
                    std::cerr << "CPF ou ID duplicado ao carregar professor: " << id << std::endl;
                    return false;
                }
                carregarEmprestimos(arquivoUsuarios, pessoa);
            } else if (tipo == "Bibliotecario") {
                arquivoUsuarios >> id;
                arquivoUsuarios.ignore(1, ';');
                std::getline(arquivoUsuarios, nome, ';');
                std::getline(arquivoUsuarios, cpf, ';');

                if (!arquivoUsuarios) {
                    std::cerr << "Erro ao ler os dados de um bibliotecário." << std::endl;
                    return false;
                }

                pessoa = new Bibliotecario(nome, cpf);
                if (!usuarios->adicionarUsuario(pessoa, id)) {
                    delete pessoa;
                    std::cerr << "CPF ou ID duplicado ao carregar bibliotecário: " << id << std::endl;
                    return false;
                }
                carregarEmprestimos(arquivoUsuarios, pessoa);
            } else if (tipo == "TecnicoManutencao") {
                arquivoUsuarios >> id;
                arquivoUsuarios.ignore(1, ';');
                std::getline(arquivoUsuarios, nome, ';');
                std::getline(arquivoUsuarios, cpf, ';');

                if (!arquivoUsuarios) {
                    std::cerr << "Erro ao ler os dados de um técnico de manutenção." << std::endl;
                    return false;
                }

                pessoa = new TecnicoManutencao(nome, cpf);
                if (!usuarios->adicionarUsuario(pessoa, id)) {
                    delete pessoa;
                    std::cerr << "CPF ou ID duplicado ao carregar técnico de manutenção: " << id << std::endl;
                    return false;
                }
                carregarEmprestimos(arquivoUsuarios, pessoa);

                if (!arquivoUsuarios) {
                    std::cerr << "Erro ao carregar os empréstimos do técnico." << std::endl;
                    return false; 
                }
                if (!(arquivoUsuarios >> numeroManutencao) || numeroManutencao < 0) {
                    std::cerr << "Quantidade de manutenções inválida." << std::endl;
                    return false;
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
                        estado > static_cast<int>(EstadoManutencao::CONCLUIDA) ||
                        (estado == static_cast<int>(EstadoManutencao::CONCLUIDA) && reparo.empty())) {

                        std::cerr << "Erro ao ler uma manutenção do técnico." << std::endl;

                        for (Manutencao *m : manutencoes) {
                            delete m;
                        }
                        return false;
                    }

                    if (cpf != tecnico->getCPF()) {
                        std::cerr << "CPF da manutenção não corresponde ao técnico responsável." << std::endl;
                        for (Manutencao *m : manutencoes) {
                            delete m;
                        }
                        return false;
                    }

                    Data data(dia, mes, ano);
                    obra = catalogo->buscarPorId(idObra);

                    if (obra == nullptr) {
                        std::cerr << "Obra não encontrada ao carregar manutenção: "
                                << idObra << std::endl;

                        for (Manutencao *m : manutencoes) {
                            delete m;
                        }
                        return false;
                    }

                    Manutencao *manutencao = new Manutencao(obra, tecnico, dano, data);
                    manutencao->registrarReparo(reparo);
                    manutencao->setEstado(static_cast<EstadoManutencao>(estado));
                    manutencoes.push_back(manutencao);
                }
                tecnico->setManutencoes(manutencoes);
            } else {
                std::cerr << "Tipo de usuário desconhecido: " << tipo << std::endl;
                return false;
            }
            if (!arquivoUsuarios) {
                std::cerr << "Erro ao carregar os dados de um usuário." << std::endl;
                return false;
            }
            arquivoUsuarios.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::vector<int> obrasEmprestadas;
        std::vector<int> obrasEmManutencao;
        for (const auto &registro : usuarios->getUsuarios()) {
            Pessoa *p = registro.first;
            if (p == nullptr) {
                return false;
            }

            for (Emprestimo *e : p->getEmprestimos()) {
                if (e == nullptr) {
                    return false;
                }
                if (!e->isAtivo()) {
                    continue;
                }
                if (dynamic_cast<Estudante*>(p) == nullptr && dynamic_cast<Professor*>(p) == nullptr) {
                    return false;
                }

                Obra &o = e->getObra();
                if (o.isDanificado()) {
                    return false;
                }
                for (int id : obrasEmprestadas) {
                    if (id == o.getID()) {
                        return false;
                    }
                }
                obrasEmprestadas.push_back(o.getID());
                o.setDisponivel(false);
            }
        }

        for (const auto &registro : usuarios->getUsuarios()) {
            TecnicoManutencao *tecnico = dynamic_cast<TecnicoManutencao*>(registro.first);
            if (tecnico == nullptr) {
                continue;
            }

            for (Manutencao *m : tecnico->getManutencoes()) {
                if (m == nullptr || m->getObra() == nullptr ||
                    m->getTecnico() != tecnico) {
                    return false;
                }
                if (m->getEstado() == EstadoManutencao::CONCLUIDA) {
                    continue;
                }
                int id = m->getObra()->getID();
                for (int emprestada : obrasEmprestadas) {
                    if (emprestada == id) {
                        return false;
                    }
                }
                for (int manutencao : obrasEmManutencao) {
                    if (manutencao == id) {
                        return false;
                    }
                }
                obrasEmManutencao.push_back(id);
                m->getObra()->setDanificado(true);
                m->getObra()->setDisponivel(false);
            }
        }
        arquivoUsuarios.close();
        arquivoObras.close();
        return true;
    }

    bool Dados::removerObra(int id) {
        if (catalogo == nullptr || usuarios == nullptr) {
            return false;
        }

        Obra *obra = catalogo->buscarPorId(id);
        if (obra == nullptr) {
            return false;
        }

        for (const auto &registro : usuarios->getUsuarios()) {
            Pessoa *pessoa = registro.first;
            if (pessoa == nullptr) {
                continue;
            }

            // Verifica se existe algum empréstimo associado à obra.
            for (Emprestimo *e : pessoa->getEmprestimos()) {
                if (e != nullptr && &e->getObra() == obra) {
                    return false;
                }
            }

            // Verifica se existe alguma manutenção associada à obra.
            TecnicoManutencao *tecnico = dynamic_cast<TecnicoManutencao*>(pessoa);
            if (tecnico != nullptr) {
                for (Manutencao *m : tecnico->getManutencoes()) {
                    if (m != nullptr && m->getObra() == obra) {
                        return false;
                    }
                }
            }
        }
        return catalogo->removerObra(id);
    }