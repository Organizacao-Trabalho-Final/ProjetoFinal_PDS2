#ifndef JANELAUSUARIO_HPP
#define JANELAUSUARIO_HPP

#include <QWidget>
#include "Usuarios.hpp"

class JanelaUsuario : public QWidget {

    Q_OBJECT

    private :

        Usuarios * usuarios;

    public :

        JanelaUsuario(QWidget * parent = nullptr);

        void setUsuarios(Usuarios* u);
        Usuarios& getUsuarios() const;

        QWidget* JanelaLista(QWidget * parent = nullptr);
        QWidget* JanelaCadastro(QWidget * parent = nullptr);
        QWidget* JanelaEditar(QWidget * parent = nullptr);
        QWidget* JanelaInformacoes(QWidget * parent = nullptr);

}

#endif 