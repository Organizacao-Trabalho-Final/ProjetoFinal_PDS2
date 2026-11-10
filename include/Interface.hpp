#ifndef INTERFACE_HPP
#define INTERFACE_HPP

/**
 * @file Interface.hpp
 * @brief Contrato da classe Interface.
 */

#include <string>
#include "Dados.hpp"
#include "Tratamento.hpp"
#include "Data.hpp"

class Livro;
class Artigo;
class Pessoa;
class Bibliotecario;
class TecnicoManutencao;
class Emprestimo;

/**
 * @class Interface
 * @brief Gerencia a interação entre o usuário e o sistema da biblioteca.
 *
 * Responsável por apresentar os menus, receber e validar as entradas
 * do usuário e acionar as funcionalidades das demais classes do sistema.
 */
class Interface {
    private:
        Dados *dados; ///> ponteiro para o gerenciamento dos dados.
        Tratamento tratamento; ///> objeto para validação das entradas do usuário.

         /**
         * @brief Exibe e gerencia o menu de operações relacionadas às obras.
         */
        void menuObras();

        /**
         * @brief Exibe e gerencia o menu de operações relacionadas aos usuários.
         */
        void menuUsuarios();

        /**
         * @brief Exibe e gerencia o menu de operações relacionadas aos empréstimos.
         */
        void menuEmprestimos();

         /**
         * @brief Exibe e gerencia o menu de operações relacionadas às manutenções.
         */
        void menuManutencoes();

        /**
         * @brief Exibe e gerencia o menu de operações relacionadas às pesquisas de obras.
         */
        void menuPesquisaObras();

        /**
         * @brief Exibe e gerencia o menu de operações relacionadas às pesquisas de usuários.
         */
        void menuPesquisaUsuarios();

        /**
         * @brief Gerencia os menus de operações entre livros e artigos.
         */
        void menuAtualizacoes();

        /**
         * @brief Exibe e gerencia o menu de operações relacionadas às atualizações de dados de livros.
         * @param l Ponteiro para o livro.
         */
        void menuAtualizacoesLivro(Livro *l);

        /**
         * @brief Exibe e gerencia o menu de operações relacionadas às atualizações de dados de artigos.
         * @param a Ponteiro para o artigo.
         */
        void menuAtualizacoesArtigo(Artigo *a);

        /**
         * @brief Gerencia os menus de operações cadastrais de obras.
         */
        void menuCadastroObras();

        /**
         * @brief Gerencia os menus de operações cadastrais de usuários.
         */
        void menuCadastroUsuarios();

        /**
         * @brief Lê e valida uma opção numérica dentro de um intervalo.
         * @param min Valor mínimo.
         * @param max Valor máximo.
         * @return Opção válida informada pelo usuário.
         */
        int lerOpcao(int min, int max);

        /**
         * @brief Lê e valida uma mensagem de texto.
         * @param msg Mensagem exibida antes da leitura.
         * @return Texto informado pelo usuário, limpo.
         */
        std::string lerTexto(const std::string &msg);

        /**
         * @brief Obtém a data local do computador.
         * @return Objeto Data do dia de hoje.
         */
        Data obterDataAtual() const;

        /**
         * @brief Exibe os dados de um usuário cadastrado.
         * @param p Ponteiro para o usuário cujas informações serão exibidas.
         * @param id Número de identificação do usuário.
         */
        void Interface::printUsuario(Pessoa *p, int id) const;

        /**
         * @brief Localiza um bibliotecário pelo CPF informado.
         * @return Ponteiro para o bibliotecário encontrado ou nullptr caso não exista.
         */
        Bibliotecario* selecionarBibliotecario();

        /**
         * @brief Localiza um técnico de manutenção pelo CPF informado.
         * @return Ponteiro para o técnico encontrado ou nullptr caso não exista.
         */
        TecnicoManutencao* selecionarTecnico();

        /**
         * @brief Localiza e selecionar um empréstimo de um usuário.
         * @param p Ponteiro para o usuário ao qual o empréstimo está associado.
         * @param ativos Se true, exibe somente empréstimos ativos.
         * @param pendentes Se true, exibe somente empréstimos com renovação pendente.
         * @return Ponteiro para o empréstimo selecionado ou nullptr caso não existam opções.
         */
        Emprestimo* selecionarEmprestimo(Pessoa *p, bool ativos, bool pendentes = false);

    public:
        /**
         * @brief Constrói um objeto Interface.
         * @param d Ponteiro para o objeto Dados utilizado pelo sistema.
         */
        Interface(Dados *d);

        /**
         * @brief Inicia a execução da interface do sistema em loop.
         *
         * Apresenta o menu principal e direciona o usuário para as
         * funcionalidades correspondentes à opção selecionada.
         */
        void executar();
};
#endif