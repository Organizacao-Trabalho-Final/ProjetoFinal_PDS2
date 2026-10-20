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

    Dados::Dados(Usuarios * usuario, Catalogo * catalogo) : usuarios(usuario), catalogo(catalogo), manutencao() {}

    Usuarios * Dados::getUsuarios() const {
        return usuarios;
    }

    Catalogo * Dados::getCatalogo() const {
        return catalogo;
    }

    void Dados::salvarEmprestimos(std::ofstream &out, const std::vector<Emprestimo*> &emprestimos) {
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

    void Dados::carregarEmprestimos(std::ifstream &in, Pessoa* _pessoa, Catalogo* catalogo) {
        
        int _idObra;
        int _dia;
        int _mes;
        int _ano;
        bool _ativo;

        Obra* _obra;
        Emprestimo* _emprestimo;
        std::vector<Emprestimo*> _emprestimos;

        int _numeroEmprestimos;
        in >> _numeroEmprestimos;
        in.ignore(1, ';');

        for(int i = 0; i < _numeroEmprestimos; i++) {

            in >>_idObra;
            in.ignore(1, ';');
            in >>_dia;
            in.ignore(1, ';');
            in >>_mes;
            in.ignore(1, ';');
            in >>_ano;
            in.ignore(1, ';');
            
            _obra = this->catalogo->buscarPorId(_idObra);
            Data data1(_dia, _mes, _ano);
            
            in >>_dia;
            in.ignore(1, ';');
            in >>_mes;
            in.ignore(1, ';');
            in >>_ano;
            in.ignore(1, ';');

            Data data2(_dia, _mes, _ano);

            in >>_ativo;
            in.ignore(1, ';');

            _emprestimo = new Emprestimo(*_obra, *_pessoa, data1);
            _emprestimo->setDevolucao(data2);
            _emprestimo->setAtivo(_ativo);

            _emprestimos.push_back(_emprestimo);

        }

        _pessoa->setEmprestimos(_emprestimos);
    }

    void Dados::SalvarDados() {
        std::ofstream arquivoUsuarios("usuario.txt");
        if(!arquivoUsuarios.is_open()) {
            std::cerr << "Erro ao abrir o arquivo para salvar os dados -> Usuarios." << std::endl;
            return;
        }

        std::ofstream arquivoObras("obras.txt");
        if(!arquivoObras.is_open()) {
            std::cerr << "Erro ao abrir o arquivo para salvar os dados -> Obras." << std::endl;
            return;
        }

        for(Obra *o : catalogo->listarObras()) {
            if(Artigo *a = dynamic_cast<Artigo*>(o)) {
                arquivoObras << "Artigo" << ";";
                arquivoObras << a->getTitulo() << ";";
                arquivoObras << a->getAutor() << ";";
                arquivoObras << a->getID() << ";";
                arquivoObras << a->isDisponivel() << ";";
                arquivoObras << a->isDanificado() << ";";
                arquivoObras << a->getArea() << ";";
                arquivoObras << a->getAno() << std::endl;
            } else if(Livro *l = dynamic_cast<Livro*>(o)) {
                arquivoObras << "Livro" << ";";
                arquivoObras << l->getTitulo() << ";";
                arquivoObras << l->getAutor() << ";";
                arquivoObras << l->getID() << ";";
                arquivoObras << l->isDisponivel() << ";";
                arquivoObras << l->isDanificado() << ";";
                arquivoObras << l->getGenero() << ";";
                arquivoObras << l->getEdicao() << std::endl;
            } else {
                std::cerr << "Tipo de obra desconhecido. Não foi possível salvar os dados." << std::endl;
            }
        } 

        const std::vector<std::pair<Pessoa*, int>> &usuarios_salvar = usuarios->getUsuarios();

        for(const std::pair<Pessoa*, int> &usuario : usuarios_salvar) {  
            
            if(Estudante * estudante = dynamic_cast<Estudante*>(usuario.first)) {
                arquivoUsuarios << "Estudante" << ";";
                arquivoUsuarios << usuario.second << ";";
                arquivoUsuarios << estudante->getNome() << ";";
                arquivoUsuarios << estudante->getCPF() << ";";
                arquivoUsuarios << estudante->getCurso() << ";";
                arquivoUsuarios << estudante->getMatricula() << ";";
                arquivoUsuarios << estudante->getNumEmprestimos() << ";";

                salvarEmprestimos(arquivoUsuarios, estudante->getEmprestimos());
                arquivoUsuarios << std::endl;

            } else if(Professor * professor = dynamic_cast<Professor*>(usuario.first)) {
                arquivoUsuarios << "Professor" << ";";
                arquivoUsuarios << usuario.second << ";";
                arquivoUsuarios << professor->getNome() << ";";
                arquivoUsuarios << professor->getCPF() << ";";
                arquivoUsuarios << professor->getArea() << ";";
                arquivoUsuarios << professor->getNumEmprestimos() << ";";
                
                salvarEmprestimos(arquivoUsuarios, professor->getEmprestimos());
                arquivoUsuarios << std::endl;

            } else if(TecnicoManutencao * tecnico = dynamic_cast<TecnicoManutencao*>(usuario.first)) {
                arquivoUsuarios << "TecnicoManutencao" << ";";
                arquivoUsuarios << usuario.second << ";";
                arquivoUsuarios << tecnico->getNome() << ";";
                arquivoUsuarios << tecnico->getCPF() << ";";
                arquivoUsuarios << tecnico->getNumEmprestimos() << ";";
                
                salvarEmprestimos(arquivoUsuarios, tecnico->getEmprestimos());

                arquivoUsuarios << tecnico->getMaxManutencoes() << ";";
                for(Manutencao *m : tecnico->getManutencoes()) {
                    arquivoUsuarios << m->getObra()->getID() << ";";
                    arquivoUsuarios << m->getTecnico()->getCPF() << ";";
                    arquivoUsuarios << m->getDano() << ";";
                    arquivoUsuarios << m->getReparo() << ";";
                    arquivoUsuarios << m->getInicio().getDia() << ";";
                    arquivoUsuarios << m->getInicio().getMes() << ";";
                    arquivoUsuarios << m->getInicio().getAno() << ";";
                    arquivoUsuarios << static_cast<int>(m->getEstado()) <<";";
                }
                arquivoUsuarios << std::endl;

            } else if(Bibliotecario * bibliotecario = dynamic_cast<Bibliotecario*>(usuario.first)) {
                arquivoUsuarios << "Bibliotecario" << ";";
                arquivoUsuarios << usuario.second << ";";
                arquivoUsuarios << bibliotecario->getNome() << ";";
                arquivoUsuarios << bibliotecario->getCPF() << ";";
                arquivoUsuarios << bibliotecario->getNumEmprestimos() << ";";
                
                salvarEmprestimos(arquivoUsuarios, bibliotecario->getEmprestimos());
                arquivoUsuarios << std::endl;

            } else {
                std::cerr << "Tipo de usuário desconhecido. Não foi possível salvar os dados." << std::endl;
            }
        }

        arquivoUsuarios.close();
        arquivoObras.close();
    }

    void Dados::CarregarDados() {

        std::ifstream arquivoUsuarios("usuario.txt");
        if(!arquivoUsuarios.is_open()) {
            std::cerr << "Erro ao abrir o arquivo para ler dados -> Usuarios." << std::endl;
            return;
        }
        std::ifstream arquivoObras("obras.txt");
        if(!arquivoObras.is_open()) {
            std::cerr << "Erro ao abrir o arquivo para ler dados -> Obras." << std::endl;
            return;
        }

        delete this->catalogo;
        delete this->usuarios;

        this->catalogo = new Catalogo();
        this->usuarios = new Usuarios();

        int _id;
        int _idObra;
        int _dia;
        int _mes;
        int _ano;
        int _edicao;
        bool _ativo;
        bool _danificado;
        bool _disponivel;
        std::string _nome;
        std::string _area;
        std::string _cpf;
        std::string _genero;
        std::string _titulo;
        std::string _autor;
        std::string _curso;
        std::string _matricula;
        std::string _dano;
        std::string _reparo;   

        //Data _data;
        //Data _data2;
        Obra * _obra;
        Pessoa * _pessoa;

        TecnicoManutencao * _tecnico;

        std::string _tipo;

        int _estado;
        int _numeroManutencao;

        Emprestimo * _emprestimo;

        while (std::getline(arquivoObras, _tipo, ';')) {

            if(_tipo == "Artigo") {
                std::getline(arquivoObras, _titulo, ';');
                std::getline(arquivoObras, _autor, ';');
                arquivoObras >> _id;
                arquivoObras.ignore(1, ';');
                arquivoObras >> _disponivel;
                arquivoObras.ignore(1, ';');
                arquivoObras >> _danificado;
                arquivoObras.ignore(1, ';');
                std::getline(arquivoObras, _area, ';');
                arquivoObras >> _ano;

                this->catalogo->cadastrarObra(new Artigo(_titulo, _autor, _id, _area, _ano));
                _obra = this->catalogo->buscarPorTitulo(_titulo);
                _obra->setDanificado(_danificado);
                _obra->setDisponivel(_disponivel);

            } else if(_tipo == "Livro") {
                std::getline(arquivoObras, _titulo, ';');
                std::getline(arquivoObras, _autor, ';');
                arquivoObras >> _id;
                arquivoObras.ignore(1, ';');
                arquivoObras >> _disponivel;
                arquivoObras.ignore(1, ';');
                arquivoObras >> _danificado;
                arquivoObras.ignore(1, ';');
                std::getline(arquivoObras, _genero, ';');
                arquivoObras >> _edicao;

                this->catalogo->cadastrarObra(new Livro(_titulo, _autor, _id, _genero, _edicao));
                _obra = this->catalogo->buscarPorTitulo(_titulo);
                _obra->setDisponivel(_disponivel);
                _obra->setDanificado(_danificado);

            }

            arquivoObras.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );
        }

        while (std::getline(arquivoUsuarios, _tipo, ';')) {

            std::vector<Emprestimo*> _emprestimos(0);

        if(_tipo == "Estudante") {

                arquivoUsuarios >> _id;
                arquivoUsuarios.ignore(1, ';');
                std::getline(arquivoUsuarios, _nome, ';');
                std::getline(arquivoUsuarios, _cpf, ';');
                std::getline(arquivoUsuarios, _curso, ';');
                std::getline(arquivoUsuarios, _matricula, ';');

                this->usuarios->adicionarUsuario(new Estudante(_nome, _cpf, _curso, _matricula), _id);
                _pessoa = this->usuarios->buscarUsuarioId(_id);
                
                carregarEmprestimos(arquivoUsuarios, _pessoa, this->catalogo);

        } else if(_tipo == "Professor") {

                arquivoUsuarios >> _id;
                arquivoUsuarios.ignore(1, ';');
                std::getline(arquivoUsuarios, _nome, ';');
                std::getline(arquivoUsuarios, _cpf, ';');
                std::getline(arquivoUsuarios, _area, ';');

                this->usuarios->adicionarUsuario(new Professor(_nome, _cpf, _area), _id);
                _pessoa = this->usuarios->buscarUsuarioId(_id);

                carregarEmprestimos(arquivoUsuarios, _pessoa, this->catalogo);

        } else if(_tipo == "Bibliotecario") {

                arquivoUsuarios >> _id;
                arquivoUsuarios.ignore(1, ';');
                std::getline(arquivoUsuarios, _nome, ';');
                std::getline(arquivoUsuarios, _cpf, ';');

                this->usuarios->adicionarUsuario(new Bibliotecario(_nome, _cpf), _id);
                _pessoa = this->usuarios->buscarUsuarioId(_id);

                carregarEmprestimos(arquivoUsuarios, _pessoa, this->catalogo);

        } else if(_tipo == "TecnicoManutencao") {

                Manutencao * _manutencao;
                std::vector<Manutencao*> _manutencoes(0);

                arquivoUsuarios >> _id;
                arquivoUsuarios.ignore(1, ';');
                std::getline(arquivoUsuarios, _nome, ';');
                std::getline(arquivoUsuarios, _cpf, ';');

                this->usuarios->adicionarUsuario(new TecnicoManutencao(_nome, _cpf), _id);
                _pessoa = this->usuarios->buscarUsuarioId(_id);

                carregarEmprestimos(arquivoUsuarios, _pessoa, this->catalogo);

                arquivoUsuarios >> _numeroManutencao;
                arquivoUsuarios.ignore(1, ';');

                for(int i = 0; i < _numeroManutencao; i++) {

                    arquivoUsuarios >> _idObra;
                    arquivoUsuarios.ignore(1, ';');
                    std::getline(arquivoUsuarios, _cpf, ';');
                    std::getline(arquivoUsuarios, _dano, ';');
                    std::getline(arquivoUsuarios, _reparo, ';');
                    arquivoUsuarios >> _dia;
                    arquivoUsuarios.ignore(1, ';');
                    arquivoUsuarios >> _mes;
                    arquivoUsuarios.ignore(1, ';');
                    arquivoUsuarios >> _ano;
                    arquivoUsuarios.ignore(1, ';');
                    arquivoUsuarios >> _estado;

                    Data data(_dia, _mes, _ano);
                    _obra = this->catalogo->buscarPorId(_idObra);
                    
                    _manutencao  = new Manutencao(_obra, static_cast<TecnicoManutencao*>(_pessoa), _dano, data);
                    _manutencao->registrarReparo(_reparo);
                    _manutencao->setEstado(static_cast<EstadoManutencao>(_estado));
                    _manutencoes.push_back(_manutencao);

                }

                TecnicoManutencao* _tecnico = static_cast<TecnicoManutencao*>(_pessoa);
                _tecnico->setManutencoes(_manutencoes);

        }
            
            arquivoUsuarios.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );
        }

        arquivoUsuarios.close();
        arquivoObras.close();

    }