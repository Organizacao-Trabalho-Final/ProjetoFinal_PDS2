#ifndef CATALOGO_H
#define CATALOGO_H

/**
 * @file Catalogo.hpp
 * @brief Declaração da classe Catalogo
 * @date 2026-10-13
 */
#include <string>
#include <vector>
#include "Obra.hpp"

/**
 * @class Catalogo
 * @brief Cria a estrutura da classe Catalogo
 */
class Catalogo {
private:
    std::vector<Obra*> obrasCadastradas;
    
    /**
     * @brief verifica se tem alguma obra duplicado
     * @return Retorna true se tiver, ou falso se não tiver
     */
    bool verificarDuplicata(int id) const;

public:
    /**
     * @brief Construtor padrão de Catalogo
     * @note é inicializado sem a passagem de parâmetros
     */
    Catalogo();

    /**
     * @brief cadastra uma obra no vetor para ponteiros de Obra, ou seja, adiciona a obra ao catálogo
     * @param o Ponteiro para um objeto do tipo Obra
     * @return Retorna true se foi cadastrado ou salse caso contrário
     */
    bool cadastrarObra(Obra *o);

    /**
     * @brief Remove a obra do catálogo, ou seja, do vetor de ponteiros para Obra
     * @param id Identificação daquela obra
     * @return Retorna true se foi removido ou false caso contrário
     */
    bool removerObra(int id);

    /**
     * @brief Altera o título de alguma Obra do catálogo
     * @param id Identificação daquela obra
     * @param t String com o novo título
     * @return Retorna true se foi alterado ou false caso contrário
     */
    bool alterarTituloObra(int id, const std::string& t);

    /**
     * @brief Altera o título de alguma obra no catálogo
     * @param id Identificação daquela obra
     * @param a String com o novo nome do autor
     * @return Retorna true se foi alterado ou false caso contrário
     */
    bool alterarAutorObra(int id, const std::string& a);

    /**
     * @brief Procura por uma obra no catálogo pelo seu título
     * @param t String com o título da obra
     * @return Retorna um ponteiro para a obra
     */
    Obra* buscarPorTitulo(const std::string& t) const;

    /**
     * @brief Procura por uma obra no catálogo pelo ID único.
     * @param _id ID único da Obra.
     * @return Retorna um ponteiro para a obra
     */
    Obra* buscarPorId(int _id) const;

    /**
     * @brief Procura por uma obra pelo seu autor
     * @param a String com o nome do autor
     * @return Retorna um vetor de ponteiros para Obra
     */
    std::vector<Obra*> buscarPorAutor(const std::string& a) const;

    /**
     * @brief Lista todas as obras presentes no catálogo
     * @return Retorna um vetor de pontieros para Obra
     */
    std::vector<Obra*> listarObras() const;

    /**
     * @brief Destrutor de Catálogo
     */
    ~Catalogo() = default;
};
#endif