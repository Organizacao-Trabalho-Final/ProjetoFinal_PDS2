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
#include "Artigo.hpp"
#include "Livro.hpp"
#include "Data.hpp"
#include "Usuarios.hpp"
#include "Catalogo.hpp"
#include "Manutencao.hpp"
#include "TecnicoManutencao.hpp"
#include "Bibliotecario.hpp"

Dados::Dados(const Usuarios * usuario, const Catalogo * catalogo) : usuarios(new Usuarios()), catalogo(new Catalogo()), manutencao() {}

Usuarios * Dados::getUsuarios() const {
    return usuarios;
}

Catalogo * Dados::getCatalogo() const {
    return catalogo;
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
            arquivoUsuarios << estudante->getMaxEmprestimos() << ";";
            for(Emprestimo *e : estudante->getEmprestimos()) {
                arquivoUsuarios << e->getObra().getID() << ";";
                arquivoUsuarios << e->getRetirada().getDia() << ";";
                arquivoUsuarios << e->getRetirada().getMes() << ";";
                arquivoUsuarios << e->getRetirada().getAno() << ";";
                arquivoUsuarios << e->getDevolucao().getDia() << ";";
                arquivoUsuarios << e->getDevolucao().getMes() << ";";
                arquivoUsuarios << e->getDevolucao().getAno() << ";";
                arquivoUsuarios << e->isAtivo() << ";";
            }
            arquivoUsuarios << std::endl;
        } else if(Professor * professor = dynamic_cast<Professor*>(usuario.first)) {
            arquivoUsuarios << "Professor" << ";";
            arquivoUsuarios << usuario.second << ";";
            arquivoUsuarios << professor->getNome() << ";";
            arquivoUsuarios << professor->getCPF() << ";";
            arquivoUsuarios << professor->getArea() << ";";
            arquivoUsuarios << professor->getMaxEmprestimos() << ";";
            for(Emprestimo *e : professor->getEmprestimos()) {
                arquivoUsuarios << e->getObra().getID() << ";";
                arquivoUsuarios << e->getRetirada().getDia() << ";";
                arquivoUsuarios << e->getRetirada().getMes() << ";";
                arquivoUsuarios << e->getRetirada().getAno() << ";";
                arquivoUsuarios << e->getDevolucao().getDia() << ";";
                arquivoUsuarios << e->getDevolucao().getMes() << ";";
                arquivoUsuarios << e->getDevolucao().getAno() << ";";
                arquivoUsuarios << e->isAtivo() << ";";
            }
            arquivoUsuarios << std::endl;
        } else if(TecnicoManutencao * tecnico = dynamic_cast<TecnicoManutencao*>(usuario.first)) {
            arquivoUsuarios << "TecnicoManutencao" << ";";
            arquivoUsuarios << usuario.second << ";";
            arquivoUsuarios << tecnico->getNome() << ";";
            arquivoUsuarios << tecnico->getCPF() << ";";
            arquivoUsuarios << tecnico->getMaxEmprestimos() << ";";
            for(Emprestimo *e : tecnico->getEmprestimos()) {
                arquivoUsuarios << e->getObra().getID() << ";";
                arquivoUsuarios << e->getRetirada().getDia() << ";";
                arquivoUsuarios << e->getRetirada().getMes() << ";";
                arquivoUsuarios << e->getRetirada().getAno() << ";";
                arquivoUsuarios << e->getDevolucao().getDia() << ";";
                arquivoUsuarios << e->getDevolucao().getMes() << ";";
                arquivoUsuarios << e->getDevolucao().getAno() << ";";
                arquivoUsuarios << e->isAtivo() << ";";
            }
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
            arquivoUsuarios << bibliotecario->getMaxEmprestimos() << ";";
            for(Emprestimo *e : bibliotecario->getEmprestimos()) {
                arquivoUsuarios << e->getObra().getID() << ";";
                arquivoUsuarios << e->getRetirada().getDia() << ";";
                arquivoUsuarios << e->getRetirada().getMes() << ";";
                arquivoUsuarios << e->getRetirada().getAno() << ";";
                arquivoUsuarios << e->getDevolucao().getDia() << ";";
                arquivoUsuarios << e->getDevolucao().getMes() << ";";
                arquivoUsuarios << e->getDevolucao().getAno() << ";";
                arquivoUsuarios << e->isAtivo() << ";";
            }
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

    this->catalogo = new Catalogo();
    this->usuarios = new Usuarios();

    int _id;
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
    Pessoa * pessoa;
    Manutencao * _manutencao;
    TecnicoManutencao * _tecnico;

    std::string _tipo;

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
        }

        arquivoObras.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );
    }

    while (std::getline(arquivoUsuarios, _tipo, ';')) {

       //if(_tipo == "ES")

        arquivoUsuarios.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );
    }

    arquivoUsuarios.close();
    arquivoObras.close();

}