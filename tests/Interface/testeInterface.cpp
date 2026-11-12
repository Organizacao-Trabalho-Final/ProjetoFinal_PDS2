#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Interface.hpp"
#include "Dados.hpp"
#include "Usuarios.hpp"
#include "Catalogo.hpp"
#include "Livro.hpp"
#include "Artigo.hpp"
#include "Estudante.hpp"
#include "Professor.hpp"
#include "Bibliotecario.hpp"
#include "TecnicoManutencao.hpp"
#include "Emprestimo.hpp"
#include "Manutencao.hpp"
#include "Data.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <unistd.h>

class DiretorioTemporario {
    private:
        std::string anterior;
        std::string caminho;

    public:
        DiretorioTemporario() {
            char atual[4096];
            if (getcwd(atual, sizeof(atual)) == nullptr) {
                throw std::runtime_error("Não foi possível obter o diretório atual.");
            }
            anterior = atual;

            char modelo[] = "/tmp/pds2-interface-XXXXXX";
            char *novo = mkdtemp(modelo);
            if (novo == nullptr) {
                throw std::runtime_error("Não foi possível criar diretório temporário.");
            }
            caminho = novo;
            if (chdir(caminho.c_str()) != 0) {
                rmdir(caminho.c_str());
                throw std::runtime_error("Não foi possível acessar diretório temporário.");
            }
        }

        ~DiretorioTemporario() {
            std::remove("obras.txt");
            std::remove("usuario.txt");
            std::remove("emprestimos.txt");
            chdir(anterior.c_str());
            rmdir(caminho.c_str());
        }
};

class Fluxos {
    private:
        std::istringstream entrada;
        std::ostringstream saida;
        std::streambuf *cinOriginal;
        std::streambuf *coutOriginal;

    public:
        explicit Fluxos(const std::string &texto): entrada(texto), cinOriginal(std::cin.rdbuf()), coutOriginal(std::cout.rdbuf()) {
            std::cin.clear();
            std::cout.clear();
            std::cin.rdbuf(entrada.rdbuf());
            std::cout.rdbuf(saida.rdbuf());
        }

        ~Fluxos() {
            std::cin.rdbuf(cinOriginal);
            std::cout.rdbuf(coutOriginal);
            std::cin.clear();
            std::cout.clear();
        }

        std::string texto() const {
            return saida.str();
        }
};

static std::string executarInterface(Dados &dados, const std::string &entrada) {
    Fluxos fluxos(entrada);
    Interface interface(&dados);
    interface.executar();
    return fluxos.texto();
}

static std::string cpfTeste(unsigned int base) {
    std::ostringstream os;
    os << std::setw(9) << std::setfill('0') << base;
    std::string cpf = os.str();
    int soma = 0;
    for (int i = 0; i < 9; ++i) soma += (cpf[i] - '0') * (10 - i);
    int d1 = (soma * 10) % 11;
    if (d1 == 10) d1 = 0;
    soma = d1 * 2;
    for (int i = 0; i < 9; ++i) soma += (cpf[i] - '0') * (11 - i);
    int d2 = (soma * 10) % 11;
    if (d2 == 10) d2 = 0;
    cpf += static_cast<char>('0' + d1);
    cpf += static_cast<char>('0' + d2);
    return cpf;
}

static Data dataHoje() {
    const std::time_t agora = std::time(nullptr);
    const std::tm *local = std::localtime(&agora);
    if (local == nullptr) return Data(1, 1, 2026);
    return Data(local->tm_mday, local->tm_mon + 1, local->tm_year + 1900);
}

TEST_CASE("Interface - construtor, menus principais vazios e encerramento") {
    DiretorioTemporario dir;
    CHECK_THROWS_AS(Interface(nullptr), std::invalid_argument);

    Dados dados(new Usuarios(), new Catalogo());
    const std::string cpf = cpfTeste(12345678);
    const std::string entrada = "1\n2\n0\n2\n4\n0\n3\n2\n" + cpf + "\n0\n4\n2\n" + cpf + "\n0\n0\n";
    const std::string saida = executarInterface(dados, entrada);

    CHECK(saida.find("Nenhuma obra foi cadastrada até então.") != std::string::npos);
    CHECK(saida.find("Nenhum usuário cadastrado.") != std::string::npos);
    CHECK(saida.find("Usuário não encontrado.") != std::string::npos);
    CHECK(saida.find("Técnico de manutenção não encontrado.") != std::string::npos);
    CHECK(saida.find("Encerrando o sistema...") != std::string::npos);
}

TEST_CASE("Interface - valida opções numéricas e trata fim da entrada") {
    DiretorioTemporario dir;
    Dados dados(new Usuarios(), new Catalogo());
    const std::string saida = executarInterface(dados, "abc\n9\n0\n");
    CHECK(saida.find("Entrada inválida. Digite um número.") != std::string::npos);
    CHECK(saida.find("Opção inválido -> Opção") != std::string::npos);

    Fluxos fluxos("");
    Interface interface(&dados);
    CHECK_THROWS_AS(interface.executar(), std::runtime_error);
}

TEST_CASE("Interface - pesquisa e listagem de obras") {
    DiretorioTemporario dir;
    Dados dados(new Usuarios(), new Catalogo());
    Livro *livro = new Livro("Cálculo", "Stewart", 1, "Didático", 2);
    Artigo *artigo = new Artigo("Robótica", "Siciliano", 2, "Engenharia", 2024);
    REQUIRE(dados.getCatalogo()->cadastrarObra(livro));
    REQUIRE(dados.getCatalogo()->cadastrarObra(artigo));

    const std::string entrada = "1\n1\n1\nCálculo\n2\nStewart\n3\n2\n1\nInexistente\n0\n2\n0\n0\n";
    const std::string saida = executarInterface(dados, entrada);

    CHECK(saida.find("Cálculo") != std::string::npos);
    CHECK(saida.find("Robótica") != std::string::npos);
    CHECK(saida.find("Obra não encontrada.") != std::string::npos);
    CHECK(saida.find("Disponibilidade:") != std::string::npos);
}

TEST_CASE("Interface - cadastra livros e artigos e trata cadastro inválido") {
    DiretorioTemporario dir;
    Dados dados(new Usuarios(), new Catalogo());
    const std::string tituloLongo(51, 'A');
    const std::string entrada =
        "1\n3\n1\n" + tituloLongo + "\nAutor\nGênero\n1\n"
        "3\n1\nCálculo\nStewart\nDidático\n2\n"
        "3\n2\nRobótica\nSiciliano\nEngenharia\n2024\n0\n0\n0\n";
    const std::string saida = executarInterface(dados, entrada);

    CHECK(saida.find("Erro ao cadastrar obra:") != std::string::npos);
    CHECK(saida.find("Obra cadastrada com sucesso!") != std::string::npos);
    REQUIRE(dados.getCatalogo()->listarObras().size() == 2);
    CHECK(dynamic_cast<Livro*>(dados.getCatalogo()->listarObras()[0]) != nullptr);
    CHECK(dynamic_cast<Artigo*>(dados.getCatalogo()->listarObras()[1]) != nullptr);
}

TEST_CASE("Interface - atualiza e remove livros e artigos") {
    DiretorioTemporario dir;
    Dados dados(new Usuarios(), new Catalogo());
    Livro *livro = new Livro("Cálculo", "Stewart", 1, "Didático", 1);
    Artigo *artigo = new Artigo("Robótica", "Siciliano", 2, "Engenharia", 2024);
    REQUIRE(dados.getCatalogo()->cadastrarObra(livro));
    REQUIRE(dados.getCatalogo()->cadastrarObra(artigo));

    const std::string tituloLongo(51, 'B');
    const std::string entrada =
        "1\n4\n1\n1\n" + tituloLongo + "\n1\nNovo Cálculo\n2\nNovo Autor\n3\nNovo Gênero\n4\n2\n0\n"
        "4\n2\n1\nNovo Artigo\n2\nNovo Autor Artigo\n3\nComputação\n4\n2025\n0\n"
        "5\n999\n5\n1\n0\n0\n";
    const std::string saida = executarInterface(dados, entrada);

    CHECK(saida.find("Não foi possível atualizar a obra:") != std::string::npos);
    CHECK(saida.find("Informação atualizada com sucesso.") != std::string::npos);
    CHECK(saida.find("Obra não encontrada ou associada a empréstimo/manutenção.") != std::string::npos);
    CHECK(saida.find("Obra removida com sucesso.") != std::string::npos);
    CHECK(dados.getCatalogo()->buscarPorId(1) == nullptr);
    REQUIRE(dados.getCatalogo()->buscarPorId(2) != nullptr);
    CHECK(dados.getCatalogo()->buscarPorId(2)->getTitulo() == "Novo Artigo");
    Artigo *artigoAtualizado = dynamic_cast<Artigo*>(dados.getCatalogo()->buscarPorId(2));
    REQUIRE(artigoAtualizado != nullptr);
    CHECK(artigoAtualizado->getArea() == "Computação");
    CHECK(artigoAtualizado->getAno() == 2025);
}

TEST_CASE("Interface - trata campos vazios e caracteres proibidos na leitura de texto") {
    DiretorioTemporario dir;
    Dados dados(new Usuarios(), new Catalogo());
    const std::string entrada = "1\n1\n1\n\n;\nLivro inexistente\n0\n0\n0\n";
    const std::string saida = executarInterface(dados, entrada);

    CHECK(saida.find("O campo não pode ficar vazio. Tente novamente.") != std::string::npos);
    CHECK(saida.find("Obra não encontrada.") != std::string::npos);
}

TEST_CASE("Interface - cadastra, pesquisa e lista todas as categorias de usuários") {
    DiretorioTemporario dir;
    Dados dados(new Usuarios(), new Catalogo());
    const std::string cpf1 = cpfTeste(12345678);
    const std::string cpf2 = cpfTeste(23456789);
    const std::string cpf3 = cpfTeste(34567890);
    const std::string cpf4 = cpfTeste(45678901);
    const std::string entrada =
        "2\n1\n1\nAna\n" + cpf1 + "\nEngenharia\n2026012345\n"
        "1\n2\nBruno\n" + cpf2 + "\nComputação\n"
        "1\n3\nBia\n" + cpf3 + "\n"
        "1\n4\nCarlos\n" + cpf4 + "\n"
        "2\n1\nAna\n"
        "2\n2\n" + cpf2 + "\n"
        "2\n3\n2\n"
        "2\n1\nInexistente\n"
        "4\n0\n0\n";
    const std::string saida = executarInterface(dados, entrada);

    REQUIRE(dados.getUsuarios()->getUsuarios().size() == 4);
    CHECK(saida.find("Usuário cadastrado com sucesso!") != std::string::npos);
    CHECK(saida.find("Categoria: Estudante") != std::string::npos);
    CHECK(saida.find("Categoria: Professor") != std::string::npos);
    CHECK(saida.find("Categoria: Bibliotecário") != std::string::npos);
    CHECK(saida.find("Categoria: Técnico de manutenção") != std::string::npos);
    CHECK(saida.find("Usuário não encontrado.") != std::string::npos);
}

TEST_CASE("Interface - rejeita cadastro duplicado e cadastro com dados inválidos") {
    DiretorioTemporario dir;
    Dados dados(new Usuarios(), new Catalogo());
    const std::string cpf = cpfTeste(12345678);
    const std::string entrada =
        "2\n1\n2\nAna\n" + cpf + "\nComputação\n"
        "1\n1\nBia\n" + cpf + "\nEngenharia\n2026012345\n"
        "1\n1\nCaio\n" + cpfTeste(23456789) + "\nEngenharia\n123\n"
        "0\n0\n";
    const std::string saida = executarInterface(dados, entrada);

    CHECK(saida.find("Cadastro não realizado: CPF já cadastrado") != std::string::npos);
    CHECK(saida.find("Erro ao cadastrar usuário:") != std::string::npos);
    CHECK(dados.getUsuarios()->getUsuarios().size() == 1);
}

TEST_CASE("Interface - impede remoção de usuários com registros e remove usuário sem vínculos") {
    DiretorioTemporario dir;
    Dados dados(new Usuarios(), new Catalogo());
    const std::string cpfAluno = cpfTeste(12345678);
    const std::string cpfTecnico = cpfTeste(23456789);
    const std::string cpfBiblio = cpfTeste(34567890);
    Livro *livro = new Livro("Livro", "Autor", 1, "Didático", 1);
    Livro *livro2 = new Livro("Livro 2", "Autor", 2, "Didático", 1);
    REQUIRE(dados.getCatalogo()->cadastrarObra(livro));
    REQUIRE(dados.getCatalogo()->cadastrarObra(livro2));
    Estudante *aluno = new Estudante("Ana", cpfAluno, "Engenharia", "2026012345");
    TecnicoManutencao *tecnico = new TecnicoManutencao("Carlos", cpfTecnico);
    Bibliotecario *biblio = new Bibliotecario("Bia", cpfBiblio);
    REQUIRE(dados.getUsuarios()->adicionarUsuario(aluno, 1));
    REQUIRE(dados.getUsuarios()->adicionarUsuario(tecnico, 2));
    REQUIRE(dados.getUsuarios()->adicionarUsuario(biblio, 3));
    Emprestimo *e = new Emprestimo(*livro, *aluno, dataHoje());
    aluno->registrarEmprestimo(e);
    Manutencao *m = new Manutencao(livro2, tecnico, "Capa rasgada", dataHoje());
    tecnico->adicionarManutencao(m);

    const std::string entrada = "2\n3\n00000000000\n3\n" + cpfAluno + "\n3\n" + cpfTecnico + "\n3\n" + cpfBiblio + "\n0\n0\n";
    const std::string saida = executarInterface(dados, entrada);

    CHECK(saida.find("Usuário não encontrado.") != std::string::npos);
    CHECK(saida.find("o usuário possui histórico de empréstimos") != std::string::npos);
    CHECK(saida.find("o técnico possui manutenções registradas") != std::string::npos);
    CHECK(saida.find("Usuário removido com sucesso.") != std::string::npos);
    CHECK(dados.getUsuarios()->buscarUsuarioCPF(cpfBiblio) == nullptr);
}

TEST_CASE("Interface - realiza empréstimo com aprovação e cobre recusas") {
    DiretorioTemporario dir;
    Dados dados(new Usuarios(), new Catalogo());
    const std::string cpfAluno = cpfTeste(12345678);
    const std::string cpfAluno2 = cpfTeste(23456789);
    const std::string cpfBiblio = cpfTeste(45678901);
    Estudante *aluno = new Estudante("Ana", cpfAluno, "Engenharia", "2026012345");
    Estudante *aluno2 = new Estudante("Bia", cpfAluno2, "Engenharia", "2026012346");
    Bibliotecario *biblio = new Bibliotecario("Bibliotecário", cpfBiblio);
    REQUIRE(dados.getUsuarios()->adicionarUsuario(aluno, 1));
    REQUIRE(dados.getUsuarios()->adicionarUsuario(aluno2, 2));
    REQUIRE(dados.getUsuarios()->adicionarUsuario(biblio, 3));
    Livro *livro = new Livro("Livro", "Autor", 1, "Didático", 1);
    Livro *indisponivel = new Livro("Indisponível", "Autor", 2, "Didático", 1);
    Livro *danificado = new Livro("Danificado", "Autor", 3, "Didático", 1);
    Artigo *artigo = new Artigo("Artigo", "Autor", 4, "Área", 2024);
    REQUIRE(dados.getCatalogo()->cadastrarObra(livro));
    REQUIRE(dados.getCatalogo()->cadastrarObra(indisponivel));
    REQUIRE(dados.getCatalogo()->cadastrarObra(danificado));
    REQUIRE(dados.getCatalogo()->cadastrarObra(artigo));
    indisponivel->setDisponivel(false);
    danificado->setDanificado(true);
    for (int i = 0; i < 3; ++i) {
        Livro *extra = new Livro("Extra " + std::to_string(i), "Autor", 5 + i, "Didático", 1);
        REQUIRE(dados.getCatalogo()->cadastrarObra(extra));
        Emprestimo *ep = new Emprestimo(*extra, *aluno2, dataHoje());
        aluno2->registrarEmprestimo(ep);
        extra->setDisponivel(false);
    }
    Livro *disponivelMax = new Livro("Disponível", "Autor", 8, "Didático", 1);
    REQUIRE(dados.getCatalogo()->cadastrarObra(disponivelMax));

    const std::string entrada =
        "3\n1\n00000000000\n"
        "1\n" + cpfBiblio + "\n"
        "1\n" + cpfAluno + "\n999\n"
        "1\n" + cpfAluno + "\n2\n"
        "1\n" + cpfAluno + "\n3\n"
        "1\n" + cpfAluno + "\n4\n"
        "1\n" + cpfAluno2 + "\n8\n"
        "1\n" + cpfAluno + "\n1\n" + cpfAluno + "\n"
        "1\n" + cpfAluno + "\n1\n" + cpfBiblio + "\n0\n"
        "1\n" + cpfAluno + "\n1\n" + cpfBiblio + "\n1\n"
        "0\n0\n";
    const std::string saida = executarInterface(dados, entrada);

    CHECK(saida.find("Usuário não encontrado.") != std::string::npos);
    CHECK(saida.find("Somente estudantes e professores podem realizar empréstimos.") != std::string::npos);
    CHECK(saida.find("Obra não encontrada.") != std::string::npos);
    CHECK(saida.find("A obra está indisponível no momento.") != std::string::npos);
    CHECK(saida.find("A obra está danificada ou em manutenção") != std::string::npos);
    CHECK(saida.find("Estudantes podem emprestar somente livros.") != std::string::npos);
    CHECK(saida.find("O estudante atingiu o limite de empréstimos ativos.") != std::string::npos);
    CHECK(saida.find("Bibliotecário não encontrado.") != std::string::npos);
    CHECK(saida.find("Empréstimo realizado com sucesso.") != std::string::npos);
    CHECK(aluno->getEmprestimos().size() == 1);
    CHECK(aluno->getEmprestimos()[0]->isAtivo());
    CHECK_FALSE(livro->isDisponivel());
}

TEST_CASE("Interface - consulta, solicita, aprova e registra devolução de empréstimo") {
    DiretorioTemporario dir;
    Dados dados(new Usuarios(), new Catalogo());
    const std::string cpfAluno = cpfTeste(12345678);
    const std::string cpfBiblio = cpfTeste(23456789);
    Estudante *aluno = new Estudante("Ana", cpfAluno, "Engenharia", "2026012345");
    Bibliotecario *biblio = new Bibliotecario("Bia", cpfBiblio);
    Livro *livro = new Livro("Livro", "Autor", 1, "Didático", 1);
    REQUIRE(dados.getUsuarios()->adicionarUsuario(aluno, 1));
    REQUIRE(dados.getUsuarios()->adicionarUsuario(biblio, 2));
    REQUIRE(dados.getCatalogo()->cadastrarObra(livro));

    const std::string entrada =
        "3\n2\n" + cpfAluno + "\n"
        "1\n" + cpfAluno + "\n1\n" + cpfBiblio + "\n1\n"
        "2\n" + cpfAluno + "\n"
        "4\n" + cpfAluno + "\n1\n"
        "5\n" + cpfAluno + "\n1\n" + cpfBiblio + "\n"
        "3\n" + cpfAluno + "\n1\n" + cpfBiblio + "\n0\n"
        "0\n0\n";
    const std::string saida = executarInterface(dados, entrada);

    CHECK(saida.find("Esse usuário não possui empréstimos registrados.") != std::string::npos);
    CHECK(saida.find("Empréstimo realizado com sucesso.") != std::string::npos);
    CHECK(saida.find("Solicitação de renovação registrada.") != std::string::npos);
    CHECK(saida.find("Renovação aprovada com sucesso.") != std::string::npos);
CHECK(saida.find("Nova data de devolução:") != std::string::npos);
    CHECK(saida.find("Devolução dentro do prazo.") != std::string::npos);
    CHECK(saida.find("Devolução registrada com sucesso.") != std::string::npos);
    REQUIRE(aluno->getEmprestimos().size() == 1);
    CHECK_FALSE(aluno->getEmprestimos()[0]->isAtivo());
    CHECK(livro->isDisponivel());
}

TEST_CASE("Interface - devolução atrasada e renovação recusada") {
    DiretorioTemporario dir;
    Dados dados(new Usuarios(), new Catalogo());
    const std::string cpfAluno = cpfTeste(12345678);
    const std::string cpfBiblio = cpfTeste(23456789);
    Estudante *aluno = new Estudante("Ana", cpfAluno, "Engenharia", "2026012345");
    Bibliotecario *biblio = new Bibliotecario("Bia", cpfBiblio);
    Livro *livro = new Livro("Livro", "Autor", 1, "Didático", 1);
    REQUIRE(dados.getUsuarios()->adicionarUsuario(aluno, 1));
    REQUIRE(dados.getUsuarios()->adicionarUsuario(biblio, 2));
    REQUIRE(dados.getCatalogo()->cadastrarObra(livro));
    Emprestimo *e = new Emprestimo(*livro, *aluno, Data(1, 1, 2000));
    e->setDevolucao(Data(1, 1, 2000));
    aluno->registrarEmprestimo(e);
    livro->setDisponivel(false);
    REQUIRE(e->solicitarRenovacao());

    const std::string entrada =
        "3\n5\n" + cpfAluno + "\n1\n" + cpfBiblio + "\n"
        "3\n" + cpfAluno + "\n1\n" + cpfBiblio + "\n1\n"
        "0\n0\n";
    const std::string saida = executarInterface(dados, entrada);

    CHECK(saida.find("Renovação recusada: o empréstimo está em atraso.") != std::string::npos);
    CHECK(saida.find("Devolução com") != std::string::npos);
    CHECK(saida.find("dia(s) de atraso.") != std::string::npos);
    CHECK(saida.find("Devolução registrada com sucesso.") != std::string::npos);
    CHECK_FALSE(e->isAtivo());
    CHECK(e->getObra().isDanificado());
    CHECK_FALSE(e->getObra().isDisponivel());
}

TEST_CASE("Interface - manutenção: encaminha, consulta, inicia e conclui") {
    DiretorioTemporario dir;
    Dados dados(new Usuarios(), new Catalogo());
    const std::string cpfBiblio = cpfTeste(12345678);
    const std::string cpfTecnico = cpfTeste(23456789);
    Bibliotecario *biblio = new Bibliotecario("Bia", cpfBiblio);
    TecnicoManutencao *tecnico = new TecnicoManutencao("Carlos", cpfTecnico);
    Livro *livro = new Livro("Livro", "Autor", 1, "Didático", 1);
    REQUIRE(dados.getUsuarios()->adicionarUsuario(biblio, 1));
    REQUIRE(dados.getUsuarios()->adicionarUsuario(tecnico, 2));
    REQUIRE(dados.getCatalogo()->cadastrarObra(livro));

    const std::string entrada =
        "4\n1\n999\n"
        "1\n1\n" + cpfTecnico + "\n"
        "1\n1\n" + cpfBiblio + "\n" + cpfBiblio + "\n"
        "1\n1\n" + cpfBiblio + "\n" + cpfTecnico + "\nCapa rasgada\n"
        "2\n" + cpfTecnico + "\n"
        "3\n" + cpfTecnico + "\n1\n"
        "2\n" + cpfTecnico + "\n"
        "4\n" + cpfTecnico + "\n1\nCapa restaurada\n"
        "2\n" + cpfTecnico + "\n"
        "0\n0\n";
    const std::string saida = executarInterface(dados, entrada);

    CHECK(saida.find("Obra não encontrada.") != std::string::npos);
    CHECK(saida.find("Bibliotecário não encontrado.") != std::string::npos);
    CHECK(saida.find("Técnico de manutenção não encontrado.") != std::string::npos);
    CHECK(saida.find("Obra encaminhada para manutenção.") != std::string::npos);
    CHECK(saida.find("Manutenções pendentes: 1") != std::string::npos);
    CHECK(saida.find("Manutenção iniciada.") != std::string::npos);
    CHECK(saida.find("Manutenção concluída.") != std::string::npos);
    REQUIRE(tecnico->getManutencoes().size() == 1);
    CHECK(tecnico->getManutencoes()[0]->getEstado() == EstadoManutencao::CONCLUIDA);
    CHECK(livro->isDisponivel());
    CHECK_FALSE(livro->isDanificado());
}

TEST_CASE("Interface - bloqueia manutenção de obra emprestada e trata técnico sem serviços") {
    DiretorioTemporario dir;
    Dados dados(new Usuarios(), new Catalogo());
    const std::string cpfAluno = cpfTeste(12345678);
    const std::string cpfBiblio = cpfTeste(23456789);
    const std::string cpfTecnico = cpfTeste(34567890);
    Estudante *aluno = new Estudante("Ana", cpfAluno, "Engenharia", "2026012345");
    Bibliotecario *biblio = new Bibliotecario("Bia", cpfBiblio);
    TecnicoManutencao *tecnico = new TecnicoManutencao("Carlos", cpfTecnico);
    Livro *livro = new Livro("Livro", "Autor", 1, "Didático", 1);
    REQUIRE(dados.getUsuarios()->adicionarUsuario(aluno, 1));
    REQUIRE(dados.getUsuarios()->adicionarUsuario(biblio, 2));
    REQUIRE(dados.getUsuarios()->adicionarUsuario(tecnico, 3));
    REQUIRE(dados.getCatalogo()->cadastrarObra(livro));
    Emprestimo *e = new Emprestimo(*livro, *aluno, dataHoje());
    aluno->registrarEmprestimo(e);
    livro->setDisponivel(false);

    const std::string entrada =
        "4\n1\n1\n"
        "3\n" + cpfTecnico + "\n"
        "4\n" + cpfTecnico + "\n"
        "2\n" + cpfTecnico + "\n"
        "0\n0\n";
    const std::string saida = executarInterface(dados, entrada);

    CHECK(saida.find("A obra está emprestada ou já possui uma manutenção em andamento.") != std::string::npos);
    CHECK(saida.find("Nenhuma manutenção correspondente foi encontrada.") != std::string::npos);
    CHECK(saida.find("Nenhuma manutenção registrada para esse técnico.") != std::string::npos);
    CHECK(tecnico->getManutencoes().empty());
}

TEST_CASE("Interface - pesquisa usuario por CPF e ID") {
    DiretorioTemporario dir;
    Dados dados(new Usuarios(), new Catalogo());
    const std::string cpf1 = cpfTeste(12345678);
    const std::string cpf2 = cpfTeste(23456789);

    REQUIRE(dados.getUsuarios()->adicionarUsuario(new Estudante("Ana", cpf1, "Engenharia", "2026012345")) == 1);
    REQUIRE(dados.getUsuarios()->adicionarUsuario(new Professor("Bruno", cpf2, "Física")) == 2);

    const std::string entrada =
    "2\n2\n2\n" + cpf1 + "\n"
    "2\n3\n2\n"
    "2\n2\n00000000000\n"
    "2\n3\n999\n"
    "0\n0\n";

    const std::string saida = executarInterface(dados, entrada);

    CHECK(saida.find("Categoria: Estudante") != std::string::npos);
    CHECK(saida.find("Categoria: Professor") != std::string::npos);
    CHECK(saida.find("Usuário não encontrado.") != std::string::npos);
}

TEST_CASE("Interface - professor respeita limite de cinco emprestimos") {
    DiretorioTemporario dir;
    Dados dados(new Usuarios(), new Catalogo());
    const std::string cpf = cpfTeste(12345678);
    Professor *prof = new Professor("Bruno", cpf, "Física");
    REQUIRE(dados.getUsuarios()->adicionarUsuario(prof) != 0);

    for (int id = 1; id <= 5; ++id) {
        Livro *l = new Livro("Livro " + std::to_string(id), "Autor", id, "Didático", 1);
        REQUIRE(dados.getCatalogo()->cadastrarObra(l));
        Emprestimo *e = new Emprestimo(*l, *prof, dataHoje());
        prof->registrarEmprestimo(e);
        l->setDisponivel(false);
    }

    Livro *sexto = new Livro("Livro 6", "Autor", 6, "Didático", 1);
    REQUIRE(dados.getCatalogo()->cadastrarObra(sexto));
    REQUIRE(prof->getEmprestimosAtivos() == 5);

    const std::string saida = executarInterface(dados, "3\n1\n" + cpf + "\n6\n0\n0\n");

    CHECK(saida.find("O professor atingiu o limite de empréstimos ativos.") != std::string::npos);
    CHECK(prof->getEmprestimosAtivos() == 5);
    CHECK(sexto->isDisponivel());
}

TEST_CASE("Interface - professor pode emprestar artigo") {
    DiretorioTemporario dir;
    Dados dados(new Usuarios(), new Catalogo());
    const std::string cpfProf = cpfTeste(12345678);
    const std::string cpfBiblio = cpfTeste(23456789);

    Professor *prof = new Professor("Bruno", cpfProf, "Física");
    Bibliotecario *biblio = new Bibliotecario("Bia", cpfBiblio);
    REQUIRE(dados.getUsuarios()->adicionarUsuario(prof) != 0);
    REQUIRE(dados.getUsuarios()->adicionarUsuario(biblio) != 0);

    Artigo *artigo = new Artigo("Robótica", "Autor", 1, "Engenharia", 2024);
    REQUIRE(dados.getCatalogo()->cadastrarObra(artigo));

    const std::string entrada = "3\n1\n" + cpfProf + "\n1\n" + cpfBiblio + "\n1\n0\n0\n";
    const std::string saida = executarInterface(dados, entrada);

    CHECK(saida.find("Empréstimo realizado com sucesso.") != std::string::npos);
    REQUIRE(prof->getEmprestimos().size() == 1);
    CHECK_FALSE(artigo->isDisponivel());
}

TEST_CASE("Interface - consulta manutencoes em todos os estados") {
    DiretorioTemporario dir;
    Dados dados(new Usuarios(), new Catalogo());
    const std::string cpf = cpfTeste(12345678);

    TecnicoManutencao *tecnico = new TecnicoManutencao("Carlos", cpf);
    REQUIRE(dados.getUsuarios()->adicionarUsuario(tecnico) != 0);

    Livro *pendente = new Livro("Pendente", "Autor", 1, "Didático", 1);
    Livro *andamento = new Livro("Andamento", "Autor", 2, "Didático", 1);
    Livro *concluida = new Livro("Concluída", "Autor", 3, "Didático", 1);

    REQUIRE(dados.getCatalogo()->cadastrarObra(pendente));
    REQUIRE(dados.getCatalogo()->cadastrarObra(andamento));
    REQUIRE(dados.getCatalogo()->cadastrarObra(concluida));

    Manutencao *m1 = new Manutencao(pendente, tecnico, "Capa rasgada", dataHoje());
    Manutencao *m2 = new Manutencao(andamento, tecnico, "Folhas soltas", dataHoje());
    Manutencao *m3 = new Manutencao(concluida, tecnico, "Lombada", dataHoje());

    tecnico->adicionarManutencao(m1);
    tecnico->adicionarManutencao(m2);
    tecnico->adicionarManutencao(m3);

    m2->iniciar();
    m3->iniciar();
    m3->registrarReparo("Lombada restaurada");
    m3->concluir();

    const std::string saida = executarInterface(dados, "4\n2\n" + cpf + "\n0\n0\n");

    CHECK(saida.find("Estado: Pendente") != std::string::npos);
    CHECK(saida.find("Estado: Em andamento") != std::string::npos);
    CHECK(saida.find("Estado: Concluída") != std::string::npos);
    CHECK(saida.find("Manutenções pendentes: 1") != std::string::npos);
}

TEST_CASE("Interface - obra com emprestimo encerrado pode ser encaminhada para manutencao") {
    DiretorioTemporario dir;
    Dados dados(new Usuarios(), new Catalogo());

    const std::string cpfAluno = cpfTeste(12345678);
    const std::string cpfBiblio = cpfTeste(23456789);
    const std::string cpfTecnico = cpfTeste(34567890);

    Estudante *aluno = new Estudante("Ana", cpfAluno, "Engenharia", "2026012345");
    Bibliotecario *biblio = new Bibliotecario("Bia", cpfBiblio);
    TecnicoManutencao *tecnico = new TecnicoManutencao("Carlos", cpfTecnico);

    REQUIRE(dados.getUsuarios()->adicionarUsuario(aluno) != 0);
    REQUIRE(dados.getUsuarios()->adicionarUsuario(biblio) != 0);
    REQUIRE(dados.getUsuarios()->adicionarUsuario(tecnico) != 0);

    Livro *livro = new Livro("Livro devolvido", "Autor", 1, "Didático", 1);
    REQUIRE(dados.getCatalogo()->cadastrarObra(livro));

    Emprestimo *e = new Emprestimo(*livro, *aluno, dataHoje());
    aluno->registrarEmprestimo(e);
    livro->setDisponivel(false);
    biblio->registrarDevolucao(e);

    REQUIRE_FALSE(e->isAtivo());
    REQUIRE(livro->isDisponivel());

    const std::string entrada =
        "4\n1\n1\n" + cpfBiblio + "\n" + cpfTecnico + "\nRachadura na capa\n0\n0\n";

    const std::string saida = executarInterface(dados, entrada);

    CHECK(saida.find("Obra encaminhada para manutenção.") != std::string::npos);
    REQUIRE(tecnico->getManutencoes().size() == 1);
    CHECK(livro->isEmManutencao());
    CHECK_FALSE(livro->isDisponivel());
}

TEST_CASE("Interface - nao permite remover obra com historico de emprestimo ou manutencao") {
    DiretorioTemporario dir;
    Dados dados(new Usuarios(), new Catalogo());

    const std::string cpfAluno = cpfTeste(12345678);
    const std::string cpfTecnico = cpfTeste(23456789);

    Estudante *aluno = new Estudante("Ana", cpfAluno, "Engenharia", "2026012345");
    TecnicoManutencao *tecnico = new TecnicoManutencao("Carlos", cpfTecnico);

    REQUIRE(dados.getUsuarios()->adicionarUsuario(aluno) != 0);
    REQUIRE(dados.getUsuarios()->adicionarUsuario(tecnico) != 0);

    Livro *comHistorico = new Livro("Com empréstimo", "Autor", 1, "Didático", 1);
    Livro *comManutencao = new Livro("Com manutenção", "Autor", 2, "Didático", 1);

    REQUIRE(dados.getCatalogo()->cadastrarObra(comHistorico));
    REQUIRE(dados.getCatalogo()->cadastrarObra(comManutencao));

    Emprestimo *e = new Emprestimo(*comHistorico, *aluno, dataHoje());
    aluno->registrarEmprestimo(e);
    e->encerrarEmprestimo();

    Manutencao *m = new Manutencao(comManutencao, tecnico, "Dano", dataHoje());
    tecnico->adicionarManutencao(m);

    const std::string saida = executarInterface(dados, "1\n5\n1\n5\n2\n0\n0\n");

    CHECK(saida.find("Obra não encontrada ou associada a empréstimo/manutenção.") != std::string::npos);
    CHECK(dados.getCatalogo()->buscarPorId(1) == comHistorico);
    CHECK(dados.getCatalogo()->buscarPorId(2) == comManutencao);
}

TEST_CASE("Interface - selecao de emprestimo permite cancelar e valida indice") {
    DiretorioTemporario dir;
    Dados dados(new Usuarios(), new Catalogo());

    const std::string cpfAluno = cpfTeste(12345678);
    Estudante *aluno = new Estudante("Ana", cpfAluno, "Engenharia", "2026012345");
    REQUIRE(dados.getUsuarios()->adicionarUsuario(aluno) != 0);

    Livro *livro = new Livro("Livro", "Autor", 1, "Didático", 1);
    REQUIRE(dados.getCatalogo()->cadastrarObra(livro));

    Emprestimo *e = new Emprestimo(*livro, *aluno, dataHoje());
    aluno->registrarEmprestimo(e);
    livro->setDisponivel(false);

    const std::string entrada = "3\n4\n" + cpfAluno + "\n9\n0\n0\n0\n";
    const std::string saida = executarInterface(dados, entrada);

    CHECK(saida.find("Opção inválido -> Opção") != std::string::npos);
    CHECK_FALSE(e->isRenovacaoSolicitada());
}

TEST_CASE("Interface - trata renovacao duplicada e aprovacao sem pendencia") {
    DiretorioTemporario dir;
    Dados dados(new Usuarios(), new Catalogo());
    const std::string cpfAluno = cpfTeste(12345678);
    const std::string cpfBiblio = cpfTeste(23456789);

    Estudante *aluno = new Estudante("Ana", cpfAluno, "Engenharia", "2026012345");
    Bibliotecario *biblio = new Bibliotecario("Bia", cpfBiblio);
    Livro *livro = new Livro("Livro", "Autor", 1, "Didático", 1);

    REQUIRE(dados.getUsuarios()->adicionarUsuario(aluno, 1));
    REQUIRE(dados.getUsuarios()->adicionarUsuario(biblio, 2));
    REQUIRE(dados.getCatalogo()->cadastrarObra(livro));

    Emprestimo *e = new Emprestimo(*livro, *aluno, dataHoje());
    aluno->registrarEmprestimo(e);
    livro->setDisponivel(false);
    REQUIRE(e->solicitarRenovacao());

    const std::string entrada =
        "3\n4\n" + cpfAluno + "\n1\n"
        "5\n" + cpfAluno + "\n1\n" + cpfBiblio + "\n"
        "5\n" + cpfAluno + "\n"
        "0\n0\n";

    const std::string saida = executarInterface(dados, entrada);

    CHECK(saida.find("Não foi possível solicitar a renovação.") != std::string::npos);
    CHECK(saida.find("Renovação aprovada com sucesso.") != std::string::npos);
CHECK(saida.find("Nova data de devolução:") != std::string::npos);
    CHECK(saida.find("Nenhum empréstimo correspondente foi encontrado.") != std::string::npos);
    CHECK_FALSE(e->isRenovacaoSolicitada());
    CHECK(e->isAtivo());
}

TEST_CASE("Interface - interrompe devolucao quando bibliotecario nao e encontrado") {
    DiretorioTemporario dir;
    Dados dados(new Usuarios(), new Catalogo());
    const std::string cpfAluno = cpfTeste(12345678);
    const std::string cpfProf = cpfTeste(23456789);

    Estudante *aluno = new Estudante("Ana", cpfAluno, "Engenharia", "2026012345");
    Professor *prof = new Professor("Bruno", cpfProf, "Física");
    Livro *livro = new Livro("Livro", "Autor", 1, "Didático", 1);

    REQUIRE(dados.getUsuarios()->adicionarUsuario(aluno, 1));
    REQUIRE(dados.getUsuarios()->adicionarUsuario(prof, 2));
    REQUIRE(dados.getCatalogo()->cadastrarObra(livro));

    Emprestimo *e = new Emprestimo(*livro, *aluno, dataHoje());
    aluno->registrarEmprestimo(e);
    livro->setDisponivel(false);

    const std::string entrada = "3\n3\n" + cpfAluno + "\n1\n" + cpfProf + "\n0\n0\n";
    const std::string saida = executarInterface(dados, entrada);

    CHECK(saida.find("Bibliotecário não encontrado.") != std::string::npos);
    CHECK(e->isAtivo());
    CHECK_FALSE(livro->isDisponivel());
}

TEST_CASE("Interface - consulta emprestimos ativos, pendentes e encerrados") {
    DiretorioTemporario dir;
    Dados dados(new Usuarios(), new Catalogo());
    const std::string cpf = cpfTeste(12345678);

    Estudante *aluno = new Estudante("Ana", cpf, "Engenharia", "2026012345");
    REQUIRE(dados.getUsuarios()->adicionarUsuario(aluno, 1));

    Livro *l1 = new Livro("Ativo", "Autor", 1, "Didático", 1);
    Livro *l2 = new Livro("Encerrado", "Autor", 2, "Didático", 1);
    REQUIRE(dados.getCatalogo()->cadastrarObra(l1));
    REQUIRE(dados.getCatalogo()->cadastrarObra(l2));

    Emprestimo *e1 = new Emprestimo(*l1, *aluno, dataHoje());
    Emprestimo *e2 = new Emprestimo(*l2, *aluno, dataHoje());
    aluno->registrarEmprestimo(e1);
    aluno->registrarEmprestimo(e2);

    REQUIRE(e1->solicitarRenovacao());
    e2->encerrarEmprestimo();

    const std::string saida = executarInterface(dados, "3\n2\n" + cpf + "\n0\n0\n");

    CHECK(saida.find("Estado: Ativo") != std::string::npos);
    CHECK(saida.find("Renovação: aguardando aprovação.") != std::string::npos);
    CHECK(saida.find("Estado: Encerrado") != std::string::npos);
    CHECK(saida.find("Atraso:") != std::string::npos);
}

TEST_CASE("Interface - permite cancelar inicio de manutencao") {
    DiretorioTemporario dir;
    Dados dados(new Usuarios(), new Catalogo());
    const std::string cpf = cpfTeste(12345678);

    TecnicoManutencao *tecnico = new TecnicoManutencao("Carlos", cpf);
    REQUIRE(dados.getUsuarios()->adicionarUsuario(tecnico, 1));

    Livro *livro = new Livro("Livro", "Autor", 1, "Didático", 1);
    REQUIRE(dados.getCatalogo()->cadastrarObra(livro));

    Manutencao *m = new Manutencao(livro, tecnico, "Capa rasgada", dataHoje());
    tecnico->adicionarManutencao(m);

    const std::string entrada =
        "4\n3\n" + cpf + "\n0\n"
        "4\n" + cpf + "\n"
        "0\n0\n";

    const std::string saida = executarInterface(dados, entrada);

    CHECK(saida.find("Selecione a manutenção (0 para cancelar):") != std::string::npos);
    CHECK(saida.find("Nenhuma manutenção correspondente foi encontrada.") != std::string::npos);
    CHECK(m->getEstado() == EstadoManutencao::PENDENTE);
    CHECK(livro->isEmManutencao());
}

TEST_CASE("Interface - repete leitura de edicao e ano invalidos") {
    DiretorioTemporario dir;
    Dados dados(new Usuarios(), new Catalogo());

    const std::string entrada =
        "1\n3\n1\nLivro teste\nAutor\nDidático\n0\n2\n"
        "3\n2\nArtigo teste\nAutora\nEngenharia\n10000\n2024\n"
        "0\n0\n";

    const std::string saida = executarInterface(dados, entrada);

    CHECK(saida.find("Opção inválido -> Opção") != std::string::npos);
    CHECK(saida.find("Obra cadastrada com sucesso!") != std::string::npos);
    REQUIRE(dados.getCatalogo()->listarObras().size() == 2);
    CHECK(dynamic_cast<Livro*>(dados.getCatalogo()->listarObras()[0]) != nullptr);
    CHECK(dynamic_cast<Artigo*>(dados.getCatalogo()->listarObras()[1]) != nullptr);
}