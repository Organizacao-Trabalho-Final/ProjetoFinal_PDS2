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
        
        /**
         * @brief Verifica se já existe uma obra com determinado ID.
         * @param id Identificador da obra.
         * @return true se o ID já estiver cadastrado; false caso contrário.
         */
        bool verificarDuplicata(int id) const;

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
         * @brief Remove uma obra do catálogo.
         * @param id ID da obra.
         * @return true se a obra for removida; false se não for encontrada.
         */
        bool removerObra(int id);

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