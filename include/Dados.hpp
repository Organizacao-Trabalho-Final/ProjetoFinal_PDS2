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
        /**
         * @brief Construtor da classe Dados
         * @param usuario Ponteiro para o objeto Usuarios
         * @param catalogo Ponteiro para o objeto Catalogo
         */
        Dados(Usuarios * usuario, Catalogo * catalogo);
        /**
         * @brief Método utilizado para retornar os usuários cadastrados. 
         * @return Ponteiro para os usuários cadastrados.
         */
        Usuarios * getUsuarios() const;
        /**
         * @brief Método utilizado para retornar o catálogo de itens.
         * @return Ponteiro para o catálogo de itens.
         */
        Catalogo * getCatalogo() const;

    private :

        void salvarEmprestimos(std::ofstream &out, const std::vector<Emprestimo*> &emprestimos);
        void carregarEmprestimos(std::ifstream &in, Pessoa* _pessoa, Catalogo* catalogo);

    public :
        /**
         * @brief Salva os dados de usuários e catálogos em um arquivo .txt
         */
        void SalvarDados();
        /**
         * @brief Carrega os dados de usuários e catálogos a partir de um arquivo .txt
         */
        void CarregarDados();
        /**
         * @brief Destrutor da classe Dados
         */
        ~Dados() = default;

};

#endif