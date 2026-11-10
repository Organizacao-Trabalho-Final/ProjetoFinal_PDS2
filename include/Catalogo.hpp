#ifndef CATALOGO_HPP
#define CATALOGO_HPP

/**
 * @file Catalogo.hpp
 * @brief Contrato da classe Catalogo.
 */
#include <string>
#include <vector>
#include "Obra.hpp"

/**
 * @class Catalogo
 * @brief Gerencia as obras cadastradas no sistema.
 */
class Catalogo {
    private:
        std::vector<Obra*> obrasCadastradas;
        int proximoId;
        
        /**
         * @brief Verifica se já existe uma obra com determinado ID.
         * @param id Identificador da obra.
         * @return true se o ID já estiver cadastrado; false caso contrário.
         */
        bool verificarDuplicata(int id) const;

        /**
         * @brief Remove uma obra do catálogo.
         * @param id Identificador da obra.
         * @return true se removida, false se não encontrada.
         */
        bool removerObra(int id);

        /**
         * @brief Gera o próximo ID disponível para uma obra.
         * @return ID gerado ou 0 se não houver ID disponível.
         */
        int gerarProximoId();

        /**
         * @brief Retorna o próximo ID disponível.
         * @return Próximo ID.
         */
        int getProximoId() const;

        /**
         * @brief Atualiza o próximo ID disponível.
         * @param id Novo próximo ID.
         */
        void setProximoId(int id);

        friend struct TesteCatalogo;
        friend class Dados;

    public:
        /**
         * @brief Constrói um catálogo vazio.
         */
        Catalogo();

        /**
         * @brief Cadastra uma obra no catálogo.
         * @param o Ponteiro para a obra a ser cadastrada.
         * @return true se o cadastro for realizado; false caso contrário.
         */
        bool cadastrarObra(Obra *o);

        /**
         * @brief Busca uma obra pelo título.
         * @param t Título procurado.
         * @return Ponteiro para a primeira obra encontrada ou nullptr.
         */
        Obra* buscarPorTitulo(const std::string& t) const;

        /**
         * @brief Busca uma obra pelo ID.
         * @param id ID da obra.
         * @return Ponteiro para a obra encontrada ou nullptr.
         */
        Obra* buscarPorId(int id) const;

        /**
         * @brief Busca as obras de determinado autor.
         * @param a Nome do autor.
         * @return Vetor contendo as obras encontradas.
         */
        std::vector<Obra*> buscarPorAutor(const std::string& a) const;

        /**
         * @brief Retorna as obras cadastradas no catálogo.
         * @return Referência constante para o vetor de obras.
         */
        const std::vector<Obra*>& listarObras() const;

        // Impedem cópias superficiais dos ponteiros pertencentes à classe.
        Catalogo(const Catalogo&) = delete;
        Catalogo& operator=(const Catalogo&) = delete;

        /**
         * @brief Destrutor de Catálogo.
         * Libera as obras cadastradas.
         */
        ~Catalogo();
};
#endif