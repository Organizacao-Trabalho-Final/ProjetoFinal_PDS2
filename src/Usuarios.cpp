#include "Usuarios.hpp"

#include "Pessoa.hpp"
#include "Estudante.hpp"
#include "Professor.hpp"
#include "Bibliotecario.hpp"
#include "TecnicoManutencao.hpp"

    Usuarios::Usuarios(): usuarios(0) {}

    void Usuarios::adicionarUsuario(Pessoa *u, int id) {
        if (u == nullptr) {
            return;
        }
        for (const auto &cadastrado : usuarios) {
            if (cadastrado.first == u) {
                return;
            }
        }
        usuarios.push_back(std::make_pair(u, id));
    }

    void Usuarios::removerUsuario(const std::string &nome) {
        for (auto it = usuarios.begin(); it != usuarios.end(); ++it) {
            if (it->first->getNome() == nome) {
                delete it->first;
                usuarios.erase(it);
                return;
            }
        }
    }

    Pessoa* Usuarios::buscarUsuarioNome(const std::string &nome) const {
        for (const auto &usuario : usuarios) {
            if (usuario.first != nullptr && usuario.first->getNome() == nome) {
                return usuario.first;
            }
        }
        return nullptr;
    }

    Pessoa* Usuarios::buscarUsuarioId(int id) const {
        for (const auto &usuario : usuarios) {
            if (usuario.first != nullptr && usuario.second == id) {
                return usuario.first;
            }
        }
        return nullptr;
    }

    Pessoa* Usuarios::buscarUsuarioCPF(std::string &cpf) const {
        for (const auto &usuario : usuarios) {
            if (usuario.first != nullptr && usuario.first->getCPF() == cpf) {
                return usuario.first;
            }
        }
        return nullptr;
    }

    std::pair<Pessoa*, int>& Usuarios::buscarUsuarioIndex(int index) const {
        if (index < 0 || static_cast<std::size_t(index) >= usuarios.size()) {
            return std::make_pair(static_cast<Pessoa*>(nullptr), -1);
        }
        return usuarios[index];
    }

    const std::vector<std::pair<Pessoa*, int>>& Usuarios::getUsuarios() const {
        return usuarios;
    }

    std::string Usuarios::getOcupacao(std::string &cpf) const {
        Pessoa* p = buscarUsuarioCPF(cpf);
        if (p == nullptr) {
            return "ERRO";
        }
        if (dynamic_cast<Estudante*>(p) != nullptr) {
            return "Estudante";
        } else if (dynamic_cast<Professor*>(p) != nullptr) {
            return "Professor";
        } else if (dynamic_cast<Bibliotecario*>(p) != nullptr) {
            return "Bibliotecario";
        } else if (dynamic_cast<TecnicoManutencao*>(p) != nullptr) {
            return "TecnicoManutencao";
        }
        return "ERRO";
    }

    std::string Usuarios::getOcupacao(int index) const {
        if(index < 0 || static_cast<std::size_t>(index) >= usuarios.size()) {
            return "ERRO -> Index Inválido";
        }
        Pessoa* p = usuarios[index].first;
        if (p == nullptr) {
            return "ERRO";
        }
        if (dynamic_cast<Estudante*>(p) != nullptr) {
            return "Estudante";
        } else if (dynamic_cast<Professor*>(p) != nullptr) {
            return "Professor";
        } else if (dynamic_cast<Bibliotecario*>(p) != nullptr) {
            return "Bibliotecario";
        } else if (dynamic_cast<TecnicoManutencao*>(p) != nullptr) {
            return "TecnicoManutencao";
        }
        return "ERRO";
    }

    Usuarios::~Usuarios() {
        for (const auto &usuario : usuarios) {
            delete usuario.first;
        }
        usuarios.clear();
    }