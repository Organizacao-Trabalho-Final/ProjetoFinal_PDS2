#include <QStackedWidget>
#include <QListWidget>
#include <QSplitter>
#include "janelaCatalogo.hpp"

janelaCatalogo::janelaCatalogo(QWidget * parent) : QWidget(parent) {

    setMinimumSize(600, 600);
    //resize(600, 600);

    QVBoxLayout * layout = new QVBoxLayout(this);

    QSplitter * splitterH = new QSplitter(Qt::Horizontal);
    QSplitter * splitterV = new QSplitter(Qt::Vertical, this);

    splitterH->setChildrenCollapsible(false);
    splitterV->setChildrenCollapsible(false);

    splitterH->addWidget(janelaOpcoes(splitterH));
    splitterH->addWidget(janelaImagem(splitterH));

    splitterV->addWidget(splitterH);
    splitterV->addWidget(janelaInformacoes(splitterV));

    layout->addWidget(splitterV);

}

QWidget* janelaCatalogo::janelaInformacoes(QWidget * parent) {

    QWidget * janela_informacoes = new QWidget(parent);

    QLabel * titulo = new QLabel("Título:", janela_informacoes);
    QLabel * autor = new QLabel("Autor:", janela_informacoes);
    QLabel * ano = new QLabel("Ano:", janela_informacoes);
    QLabel * genero = new QLabel("Gênero:", janela_informacoes);
    QLabel * editora = new QLabel("Editora:", janela_informacoes);

    QVBoxLayout * layout = new QVBoxLayout(janela_informacoes);
    layout->addWidget(titulo);
    layout->addWidget(autor);
    layout->addWidget(ano);
    layout->addWidget(genero);
    layout->addWidget(editora);

    //janela_informacoes->setMinimumHeight(500);

    return janela_informacoes;
}

QWidget* janelaCatalogo::janelaOpcoes(QWidget * parent) {

    QWidget * janela_opcoes = new QWidget(parent);

    QHBoxLayout * layout = new QHBoxLayout(janela_opcoes);

    QStackedWidget * janelas = new QStackedWidget(this);
    QListWidget * menu = new QListWidget(this);

    menu->setMinimumWidth(150);
    menu->setMaximumWidth(150);
    janelas->setMinimumWidth(400);

    janela_opcoes->setStyleSheet(
    "QWidget {"
    "   background-color: #f0f0f0;"
    "   border: 2px solid #000000;"
    "   border-radius = 12px;"
    "}"
    );

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

    layout->addWidget(menu);
    layout->addWidget(janelas);
    
    menu->addItem("Adicionar Obra");
    menu->addItem("Remover Obra");
    menu->addItem("Editar Obra");

    janela_opcoes->setMinimumHeight(200);

    return janela_opcoes;
}

    
QWidget* janelaCatalogo::janelaImagem(QWidget * parent) {

    QWidget * janela_imagem = new QWidget(parent);

    QLabel * preview = new QLabel(janela_imagem);
    preview->setMinimumSize(400, 400);
    preview->setAlignment(Qt::AlignCenter);

    QPushButton * addImagem = new QPushButton("Alterar Imagem", janela_imagem);
    connect(addImagem, &QPushButton::clicked, [this, preview]() {
        adicionarImagem(preview);
    });

    QVBoxLayout * layout = new QVBoxLayout(janela_imagem);
    layout->addWidget(preview);
    layout->addWidget(addImagem);

    janela_imagem->setMinimumWidth(200);

    return janela_imagem;
}

void janelaCatalogo::adicionarImagem(QLabel * preview) {

    QString caminho = QFileDialog::getOpenFileName(
        this,
        "Selecionar Imagem",
        "",
        "Imagens (*.png *.jpg *.jpeg)"
    );

    if(caminho.isEmpty()) {
        return;
    }
    
    QPixmap imagem(caminho);

    preview->setPixmap(
        imagem.scaled(400, 400, Qt::KeepAspectRatio)
    );

}