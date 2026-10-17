#include "Usuarios.hpp"

Usuarios::Usuarios() : usuarios() {}

void Usuarios::adicionarUsuario(const Pessoa *usuario) {
    int id = usuarios.size() + 1;
    usuarios.push_back(std::make_pair(usuario, id));
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

std::vector<std::pair<Pessoa*, int>> Usuarios::getUsuarios() const {
    return usuarios;
}
