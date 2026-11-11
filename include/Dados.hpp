#ifndef DADOS_HPP
#define DADOS_HPP

/**
 * @file Dados.hpp
 * @brief Contrato da classe Dados.
 */

#include <vector>
#include <fstream>

class Usuarios;
class Catalogo;
class Pessoa;
class Emprestimo;

/**
 * @class Dados
 * @brief Usada para gerenciamento dos dados do sistema.
 * Gerencia a persistência das informações de usuários, obras, empréstimos
 * e manutenções, utilizando arquivos de texto.
 */
class Dados {
    private:
        Usuarios *usuarios;
        Catalogo *catalogo;
        friend struct TesteDados;
        friend struct TesteDados2;

        /**
         * @brief Salva os empréstimos de um usuário em um arquivo.
         * @param out Fluxo de saída utilizado para a gravação.
         * @param emprestimos Vetor de ponteiros para os empréstimos.
         */
        void salvarEmprestimos(std::ofstream &out, const std::vector<Emprestimo*> &emprestimos) const;

        /**
         * @brief Carrega os empréstimos de um usuário a partir de um arquivo.
         * @param in Fluxo de entrada utilizado para a leitura.
         * @param p Ponteiro para o usuário que receberá os empréstimos.
         */
        void carregarEmprestimos(std::ifstream &in, Pessoa* p);

        /**
         * @brief Carrega os dados em uma instância temporária.
         * @return true se o carregamento for concluído, false caso contrário.
         */
        bool carregarDadosInterno();

    public:
        /**
         * @brief Constroi um objeto Dados.
         * @param u Ponteiro para o objeto Usuarios.
         * @param c Ponteiro para o objeto Catalogo.
         */
        Dados(Usuarios* u, Catalogo* c);

        /**
         * @brief Retorna os usuários cadastrados. 
         * @return Ponteiro para os usuários cadastrados.
         */
        Usuarios* getUsuarios();

        /**
         * @brief Retorna os usuários cadastrados para consulta. 
         * @return Ponteiro constante para os usuários cadastrados.
         */
        const Usuarios* getUsuarios() const;

        /**
         * @brief Retorna o catálogo de obras.
         * @return Ponteiro para o catálogo de obras.
         */
        Catalogo* getCatalogo();

        /**
         * @brief Retorna o catálogo de obras.
         * @return Ponteiro constante para o catálogo de obras.
         */
        const Catalogo* getCatalogo() const;
        
        /**
         * @brief Salva os dados de usuários e catálogos em um arquivo .txt
         */
        void salvarDados();

        /**
         * @brief Carrega os dados de usuários e catálogos a partir de um arquivo .txt
         * @return true caso os dados sejam carregados com sucesso, false caso contrário.
         */
        bool carregarDados();

        /**
         * @brief Remove uma obra do catálogo, caso não existam registros associados a ela.
         * @param id Identificador da obra a ser removida.
         * @return true se a obra for removida, false se não for encontrada
         * ou estiver associada a empréstimos ou manutenções.
         */
        bool removerObra(int id);

        // Impedem cópias superficiais dos ponteiros pertencentes à classe.
        Dados(const Dados&) = delete;
        Dados& operator=(const Dados&) = delete;

        /**
         * @brief Destrutor da classe Dados.
         * Libera a memória dos objetos recebidos pelo construtor.
         */
        ~Dados();
};
#endif