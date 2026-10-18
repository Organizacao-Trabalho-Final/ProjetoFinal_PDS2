#ifndef DADOS_HPP
#define DADOS_HPP

#include <vector>
#include <fstream>

class Usuarios;
class Catalogo;
class Pessoa;
class Manutencao;
class Emprestimo;
class TecnicoManutencao;

class Dados {

    private :

        Usuarios * usuarios;
        Catalogo * catalogo;
        std::vector<Manutencao*> manutencao;

    public :

        Dados(Usuarios * usuario, Catalogo * catalogo);
        Usuarios * getUsuarios() const;
        Catalogo * getCatalogo() const;

    private :

        void salvarEmprestimos(std::ofstream &out, const std::vector<Emprestimo*> &emprestimos);
        void carregarEmprestimos(std::ifstream &in, Pessoa* _pessoa, Catalogo* catalogo);

    public :

        void SalvarDados();
        void CarregarDados();
        void CarregarUsuarios(Usuarios &usuarios);
        void CarregarCatalogo(Catalogo &catalogo);
        void CarregarTecnicoManutencao(TecnicoManutencao &tecnico);

        ~Dados() = default;

};

#endif