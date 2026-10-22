#include "Usuarios.hpp"

#include "Pessoa.hpp"
#include "Estudante.hpp"
#include "Professor.hpp"
#include "Bibliotecario.hpp"
#include "TecnicoManutencao.hpp"

Usuarios::Usuarios() : usuarios(0) {}

void Usuarios::adicionarUsuario(Pessoa *usuario, int _id) {
    usuarios.push_back(std::make_pair(usuario, _id));
}

void Usuarios::removerUsuario(const std::string & nome) {
    for (auto it = usuarios.begin(); it != usuarios.end(); ++it) {
        if (it->first->getNome() == nome) {
            usuarios.erase(it);
            return;
        }
    }
}

Pessoa * Usuarios::buscarUsuarioNome(const std::string & nome) const {
    for (const auto & usuario : usuarios) {
        if (usuario.first->getNome() == nome) {
            return usuario.first;
        }
    }
    return nullptr;
}

Pessoa * Usuarios::buscarUsuarioId(int id) const {
    for (const auto & usuario : usuarios) {
        if (usuario.second == id) {
            return usuario.first;
        }
    }
    return nullptr;
}

Pessoa * Usuarios::buscarUsuarioCPF(std::string _cpf) const {
    for (const auto & usuario : usuarios) {
        if (usuario.first->getCPF() == _cpf) {
            return usuario.first;
        }
    }
    return nullptr;
}

std::pair<Pessoa*, int>& Usuarios::buscarUsuarioIndex(int index) {
    if(index < 0 || index > usuarios.size()) {
        std::pair<Pessoa*, int> erro;
        erro.first = nullptr;
        erro.second = -1;
        return erro;
    }
    for (auto & usuario : usuarios) {
        if (usuario.first == usuarios[index].first) {
            return usuario;
        }
    }
    std::pair<Pessoa*, int> erro;
    erro.first = nullptr;
    erro.second = -1;
    return erro;
}

const std::vector<std::pair<Pessoa*, int>>& Usuarios::getUsuarios() const {
    return usuarios;
}

std::string Usuarios::getOcupacao(std::string _cpf) const {
    Pessoa* pessoa = buscarUsuarioCPF(_cpf);
    if (Estudante* e = dynamic_cast<Estudante*>(pessoa)) {
        return "Estudante";
    } else if (Professor* p = dynamic_cast<Professor*>(pessoa)) {
        return "Professor";
    } else if (Bibliotecario* b = dynamic_cast<Bibliotecario*>(pessoa)) {
        return "Bibliotecario";
    } else if (TecnicoManutencao* t = dynamic_cast<TecnicoManutencao*>(pessoa)) {
        return "TecnicoManutencao";
    }
    return "ERRO";
}

std::string Usuarios::getOcupacao(int index) const {
    if(index < 0 || index > usuarios.size()) {
        return "ERRO -> Index Inválido";
    }
    Pessoa* pessoa = usuarios[index].first;
    if (Estudante* e = dynamic_cast<Estudante*>(pessoa)) {
        return "Estudante";
    } else if (Professor* p = dynamic_cast<Professor*>(pessoa)) {
        return "Professor";
    } else if (Bibliotecario* b = dynamic_cast<Bibliotecario*>(pessoa)) {
        return "Bibliotecario";
    } else if (TecnicoManutencao* t = dynamic_cast<TecnicoManutencao*>(pessoa)) {
        return "TecnicoManutencao";
    }
    return "ERRO";
}
