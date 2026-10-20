#ifndef JANELAUSUARIO_HPP
#define JANELAUSUARIO_HPP

#include <QWidget>
#include "Pessoa.hpp"
#include "Usuarios.hpp"

class QStackedWidget;
class QListWidget;

class JanelaUsuario : public QWidget {

    Q_OBJECT

    private :

        Usuarios * usuarios;

        QListWidget* listaUsuariosWidget;
        QStackedWidget* infoUsuarioWidget;
        QStackedWidget* editarUsuarioWidget;

        void atualizarLista();
        void limparStacked();

    public :

        JanelaUsuario(QWidget * parent = nullptr);

        void setUsuarios(Usuarios* u);
        Usuarios& getUsuarios() const;

        QWidget* JanelaLista(QWidget * parent = nullptr);
        QWidget* JanelaOpcoes(QWidget * parent = nullptr);
        QWidget* JanelaCadastro(QWidget * parent = nullptr);
        QWidget* JanelaOcupacao(std::string ocupacao, QWidget * parent = nullptr);
        QWidget* JanelaEditar(QWidget * parent = nullptr);
        QWidget* JanelaInformacoes(QWidget * parent = nullptr);

        bool isValidoID(int _id) const;

};

#endif 