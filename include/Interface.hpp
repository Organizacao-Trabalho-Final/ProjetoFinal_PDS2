#ifndef INTERFACE_HPP
#define INTERFACE_HPP

/**
 * @file Interface.hpp
 * @brief Contrato da classe Interface.
 */

#include "Dados.hpp"
#include "Tratamento.hpp"

class Livro;
class Artigo;

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
         * @brief Gerencia os menus de operações entre livros e artigos.
         */
        void menuAtualizacoes();

        /**
         * @brief Gerencia os menus de operações cadastrais de obras.
         */
        void menuCadastroObras();

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
         * @brief Lê e valida uma opção numérica dentro de um intervalo.
         * @param min Valor mínimo.
         * @param max Valor máximo.
         * @return Opção válida informada pelo usuário.
         */
        int lerOpcao(int min, int max);

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