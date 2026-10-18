#include <QtCore>
#include <QWidget>
#include <QApplication>
#include "janelaPrincipal.hpp"

int main(int argc, char * argv[]) {

    QApplication app(argc, argv);

    janelaPrincipal principal;

    principal.show();
    return app.exec();

}