#ifndef EMPRESTIMOLISTA_HPP
#define EMPRESTIMOLISTA_HPP

#include <vector>
#include <utility>

class Emprestimo;

template <typename T>

class EmprestimosLista {

    private :

        std::vector<pair<Emprestimo*, int>> emprestimos;

    public :

        EmprestimosLista();
        
        void getEmprestimoID(int id) const;
        
        void ligar(Emprestimo * e, T p);

}

#endif