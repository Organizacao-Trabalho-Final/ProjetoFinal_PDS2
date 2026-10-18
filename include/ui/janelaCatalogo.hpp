#ifndef JANELACATALOGO_HPP
#define JANELACATALOGO_HPP

#include <QWidget>
#include <vector>
#include <utility>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QPixmap>
#include <QString>
#include "Catalogo.hpp"

class janelaCatalogo : public QWidget {

    Q_OBJECT

    private :

        Catalogo * catalogo;
        std::vector<std::pair<QString, int>> caminhoImagem;

    public :

        janelaCatalogo(QWidget * parent = nullptr);
        QWidget* janelaInformacoes(QWidget * parent = nullptr);
        QWidget* janelaImagem(QWidget * parent = nullptr);
        QWidget* janelaOpcoes(QWidget * parent = nullptr);
        void adicionarImagem(QLabel * preview);

};

#endif