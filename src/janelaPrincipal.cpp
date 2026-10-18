#include <QLabel>
#include <QHBoxLayout>
#include <QListWidget>
#include <QStackedWidget>
#include "janelaCatalogo.hpp"
#include "janelaPrincipal.hpp"

janelaPrincipal::janelaPrincipal(QWidget * parent) : QMainWindow(parent) {

    setMinimumSize(800, 600);
    //resize(800, 600);

    QWidget * central = new QWidget(this);
    QHBoxLayout * layout = new QHBoxLayout(central);

    QStackedWidget * janelas = new QStackedWidget(central);
    QListWidget * menu = new QListWidget(central);

    layout->addWidget(menu);
    layout->addWidget(janelas);

    menu->setMinimumWidth(200);
    menu->setMaximumWidth(200);
    janelas->setMinimumWidth(600);

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
    );

    menu->addItem("Usuários");
    menu->addItem("Catálogo");
    menu->addItem("Empréstimos");
    menu->addItem("Devoluções");
    menu->addItem("Manutenção");
    menu->addItem("Configurações");

    
    //janelas->addWidget(new janelaUsuarios(central));
    janelas->addWidget(new janelaCatalogo(central));
    //janelas->addWidget(new janelaEmprestimos(central));
    //janelas->addWidget(new janelaDevolucoes(central));
    //janelas->addWidget(new janelaManutencao(central));
    //janelas->addWidget(new janelaConfiguracoes(central));
    

    janelas->addWidget(new QLabel("Usuários", central));
    //janelas->addWidget(new QLabel("Catálogo", central));
    janelas->addWidget(new QLabel("Empréstimos", central));
    janelas->addWidget(new QLabel("Devoluções", central));
    janelas->addWidget(new QLabel("Manutenção", central));
    janelas->addWidget(new QLabel("Configurações", central));

    connect(menu, &QListWidget::currentRowChanged, janelas, &QStackedWidget::setCurrentIndex);
    
    setCentralWidget(central);

}