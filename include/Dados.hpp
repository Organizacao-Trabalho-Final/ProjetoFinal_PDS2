#ifndef DADOS_HPP
#define DADOS_HPP

#include <vector>

class Usuarios;
class Catalogo;
class Manutencao;
class TecnicoManutencao;

class Dados {

    private :

        Usuarios * usuarios;
        Catalogo * catalogo;
        std::vector<Manutencao*> manutencao;

    public :

        Dados(const Usuarios * usuario, const Catalogo * catalogo);
        Usuarios * getUsuarios() const;
        Catalogo * getCatalogo() const;

        void CarregarDados();
        void SalvarDados();
        void CarregarUsuarios(Usuarios &usuarios);
        void CarregarCatalogo(Catalogo &catalogo);
        void CarregarTecnicoManutencao(TecnicoManutencao &tecnico);

        ~Dados() = default;

};

#endif