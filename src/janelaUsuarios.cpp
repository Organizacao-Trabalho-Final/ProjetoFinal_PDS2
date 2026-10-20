#include "janelaUsuarios.hpp"
#include "Pessoa.hpp"
#include "Professor.hpp"
#include "Estudante.hpp"
#include "TecnicoManutencao.hpp"
#include "Bibliotecario.hpp"
#include <vector>
#include <utility>
#include <QLabel>
#include <QSplitter>
#include <QTimer>
#include <QStackedWidget>
#include <QTextEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QListWidget>

JanelaUsuario::JanelaUsuario(QWidget* parent) : QWidget(parent), usuarios(new Usuarios),
                                                infoUsuarioWidget(new QStackedWidget()),
                                                listaUsuariosWidget(new QListWidget()) {

    setMinimumSize(600, 600);

    QVBoxLayout* layout = new QVBoxLayout(this);

    QSplitter* splitterH = new QSplitter(Qt::Horizontal, this);
    QSplitter* splitterV = new QSplitter(Qt::Vertical);

               splitterV->setChildrenCollapsible(false);
               splitterH->setChildrenCollapsible(false);

    QWidget* lista       = JanelaLista(splitterH);
    QWidget* opcoes      = JanelaOpcoes(splitterV);
    QWidget* informacoes = JanelaInformacoes(splitterV);

    splitterV->addWidget(opcoes);
    splitterV->addWidget(informacoes);
    splitterH->addWidget(splitterV);
    splitterH->addWidget(lista);

    layout->addWidget(splitterH);

}

QWidget* JanelaUsuario::JanelaOpcoes(QWidget * parent) {

    QWidget* janelaMain = new QWidget(parent);

             janelaMain->setMaximumHeight(500);
             janelaMain->setMinimumHeight(200);
             //janelaMain->setMaximumWidth(500);
             janelaMain->setMinimumWidth(200);

             janelaMain->setStyleSheet(
                "QWidget {"
                "   background-color: #f0f0f0;"
                "   border: 1px solid #000000;"
                "   border-radius = 12px;"
                "}"
             );

    QHBoxLayout* layout = new QHBoxLayout(janelaMain);

    QListWidget* menu = new QListWidget(janelaMain);
                 menu->setMinimumWidth(150);
                 menu->setMaximumWidth(150);

                 menu->setStyleSheet(
                    "QListWidget {"
                    "   background-color: #ffffff;"
                    "   color: rgb(0, 0, 0);"
                    "   border: 2px solid #000000;"
                    "   border-radius = 12px;"
                    "   padding: 8px;"
                    "}"
                    "QListWidget::item {"
                    "   padding: 12px;"
                    "   border-radius: 6px;"
                    "}"
                    "QListWidget::item:hover {"
                    "   background-color: #e0e0e0;"
                    "}"
                    "QListWidget::item:selected {"
                    "   background-color: #4568a0;"
                    "   color: white;"
                    "}"
                    "QWidget {"
                    "   background-color: #f0f0f0;"
                    "   border: none;"
                    "}"
                 );

    QStackedWidget* janelas = new QStackedWidget(janelaMain);

    QWidget * editar = JanelaEditar(janelaMain);
              editar->setStyleSheet(
                "QWidget {"
                "   background-color: #f0f0f0;"
                "   border: 1px solid #000000;"
                "   border-radius = 12px;"
                "}"
              );

    QWidget * cadastro = JanelaCadastro(janelaMain);
              cadastro->setStyleSheet(
                "QWidget {"
                "   background-color: #f0f0f0;"
                "   border: 1px solid #000000;"
                "   border-radius = 12px;"
                "}"
              );
              
    janelas->addWidget(cadastro);
    janelas->addWidget(editar);

    menu->addItem("Cadastrar");
    menu->addItem("Editar");

    connect(menu, &QListWidget::currentRowChanged, janelas, &QStackedWidget::setCurrentIndex);

    layout->addWidget(menu);
    layout->addWidget(janelas);

    return janelaMain;

}

QWidget* JanelaUsuario::JanelaCadastro(QWidget * parent) {

    QWidget* janelaMain = new QWidget(parent);
             janelaMain->setStyleSheet(
                "QWidget {"
                "   background-color: #f0f0f0;"
                "   border: 1px solid #000000;"
                "   border-radius = 12px;"
                "}"
             );

    QFormLayout* layout = new QFormLayout(janelaMain);

    QComboBox*  tipoPessoa = new QComboBox(janelaMain);
                tipoPessoa->addItem("Selecione...");
                tipoPessoa->addItem("Estudante");
                tipoPessoa->addItem("Professor");
                tipoPessoa->addItem("Bibliotecário");
                tipoPessoa->addItem("Técnico Manutenção");
            
    QLineEdit*  nome = new QLineEdit(janelaMain);
    QLineEdit*  cpf  = new QLineEdit(janelaMain);

    QSpinBox*   id   = new QSpinBox(janelaMain);
                id->setRange(0, 1000);

    layout->addRow("Nome: ", nome);
    layout->addRow("CPF: ", cpf);
    layout->addRow("ID: ", id);

    QStackedWidget* paginas = new QStackedWidget(janelaMain);
    
    QWidget* estudante = new QWidget(janelaMain);
    
            QFormLayout* formEstudante = new QFormLayout(estudante);
            
            QLineEdit* curso = new QLineEdit(estudante);
            QLineEdit* matricula = new QLineEdit(estudante);

            formEstudante->addRow("Curso: ", curso);
            formEstudante->addRow("Matricula: ", matricula);
            
    QWidget* professor = new QWidget(janelaMain);

            QFormLayout* formProfessor = new QFormLayout(professor);

            QLineEdit* area = new QLineEdit(professor);

            formProfessor->addRow("Área: ", area);

    QWidget* bibliotecario = new QWidget(janelaMain);

    QWidget* tecnico = new QWidget(janelaMain);

    QWidget* vazio = new QWidget(janelaMain);

    paginas->addWidget(vazio);
    paginas->addWidget(estudante);
    paginas->addWidget(professor);
    paginas->addWidget(bibliotecario);
    paginas->addWidget(tecnico);

    connect(tipoPessoa,
        QOverload<int>::of(&QComboBox::currentIndexChanged),
        paginas,
        &QStackedWidget::setCurrentIndex);

    
    QPushButton* botaoCadastrar = new QPushButton("Cadastrar", janelaMain);

    connect(botaoCadastrar, &QPushButton::clicked, this, 
            [this, tipoPessoa, nome, cpf, id, curso, matricula, area]() {

        if(nome->text().isEmpty()) {
            QMessageBox::warning(this, "Erro", "Nome obrigatório!");
            return;
        } else if(cpf->text().isEmpty()) {
            QMessageBox::warning(this, "Erro", "CPF obrigatório!");
            return;
        }

        int _id = id->value();
        std::string _nome = nome->text().toStdString();
        std::string _cpf  = cpf->text().toStdString();

        if(tipoPessoa->currentIndex() == 0) {

            QMessageBox::warning(this, "Erro", "Selecione o tipo de usuário.");
            return;

        } else if(tipoPessoa->currentIndex() == 1) {

            if(!isValidoID(_id)) {
                QMessageBox::warning(this, "Erro", "ID em uso.");
                return;
            } else if(curso->text().isEmpty()) {
                QMessageBox::warning(this, "Erro", "Curso obrigatório!");
                return;
            } else if(matricula->text().isEmpty()) {
                QMessageBox::warning(this, "Erro", "Matricula obrigatório!");
                return;
            }

            std::string _curso = curso->text().toStdString();
            std::string _matricula = matricula->text().toStdString();

            this->usuarios->adicionarUsuario(
                new Estudante(_nome, _cpf, _curso, _matricula), _id
            );

        } else if(tipoPessoa->currentIndex() == 2) {

            if(!isValidoID(_id)) {
                QMessageBox::warning(this, "Erro", "ID em uso.");
                return;
            } else if(area->text().isEmpty()) {
                QMessageBox::warning(this, "Erro", "Área obrigatório!");
                return;
            }

            std::string _area = area->text().toStdString();

            this->usuarios->adicionarUsuario(
                new Professor(_nome, _cpf, _area), _id
            );

        } else if(tipoPessoa->currentIndex() == 3) {

            if(!isValidoID(_id)) {
                QMessageBox::warning(this, "Erro", "ID em uso.");
                return;
            }

            this->usuarios->adicionarUsuario(
                new Bibliotecario(_nome, _cpf), _id
            );

        } else if(tipoPessoa->currentIndex() == 4) {

            if(!isValidoID(_id)) {
                QMessageBox::warning(this, "Erro", "ID em uso.");
                return;
            }

            this->usuarios->adicionarUsuario(
                new TecnicoManutencao(_nome, _cpf), _id
            );
        }

        area->clear();
        nome->clear();
        matricula->clear();
        cpf->clear();
        curso->clear();
        id->setValue(0);    

        atualizarLista();

        QMessageBox::information(this,
        "Cadastro Realizado",
        "Usuário cadastrado com sucesso!"
        );

    });


    layout->addRow(tipoPessoa);
    layout->addRow(paginas);
    layout->addRow(botaoCadastrar);

    return janelaMain;

}

QWidget* JanelaUsuario::JanelaLista(QWidget* parent) {

    QWidget* janelaMain = new QWidget(parent);
             janelaMain->setMaximumWidth(450);

    QVBoxLayout* layout = new QVBoxLayout(janelaMain);

    listaUsuariosWidget = new QListWidget(janelaMain);

    layout->addWidget(listaUsuariosWidget);

    atualizarLista();

    return janelaMain;

}

void JanelaUsuario::limparStacked() {
   while (this->infoUsuarioWidget->count() > 0) {
        QWidget* pagina = this->infoUsuarioWidget->widget(0);
                          this->infoUsuarioWidget->removeWidget(pagina);
        delete pagina;
    }
}

void JanelaUsuario::atualizarLista() {

    listaUsuariosWidget->clear();
    limparStacked();

    std::vector<std::pair<Pessoa*, int>> pessoas =
        usuarios->getUsuarios();

    for (const auto& p : pessoas) {
        int id = p.second;

        int qtdEmprestimos = p.first->Pessoa::getMaxEmprestimos();
        std::string nome = p.first->getNome();
        std::string cpf = p.first->getCPF();
        std::string ocupacao = usuarios->getOcupacao(cpf);

        QString texto = QString("OCUPAÇÃO: %1 | ID: %2 | Nome: %3 | CPF: %4")
            .arg(QString::fromStdString(ocupacao))
            .arg(id)
            .arg(QString::fromStdString(nome))
            .arg(QString::fromStdString(cpf));

        listaUsuariosWidget->addItem(texto);

        QString informacoes = "Nome: " + QString::fromStdString(nome)
                            + "\nOcupação: " + QString::fromStdString(ocupacao)
                            + "\nCPF: " + QString::fromStdString(cpf);
                            + "\nQTD Empréstimos: " + QString::number(qtdEmprestimos);

        QTextEdit* infoWidget = new QTextEdit();

                   infoWidget->setReadOnly(true);
                   infoWidget->setPlainText(informacoes);

        infoUsuarioWidget->addWidget(infoWidget);

    }

}

QWidget* JanelaUsuario::JanelaEditar(QWidget * parent) {

    QWidget* janelaMain = new QWidget(parent);


    return janelaMain;

}

QWidget* JanelaUsuario::JanelaInformacoes(QWidget * parent ) {

    QWidget* janelaMain = new QWidget(parent);

    this->infoUsuarioWidget = new QStackedWidget(janelaMain);

    QVBoxLayout* layout = new QVBoxLayout(janelaMain);
                 layout->addWidget(this->infoUsuarioWidget);

    QTextEdit* vazio = new QTextEdit(janelaMain);

    infoUsuarioWidget->addWidget(vazio);

    connect(this->listaUsuariosWidget, &QListWidget::currentRowChanged, 
        this->infoUsuarioWidget, &QStackedWidget::setCurrentIndex);

    return janelaMain;

}

bool JanelaUsuario::isValidoID(int _id) const {

    Pessoa* pessoa = this->usuarios->buscarUsuarioId(_id);

    if(pessoa == nullptr)
        return true;

    return false;

}