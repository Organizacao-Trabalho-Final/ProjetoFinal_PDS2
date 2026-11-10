#include <cstddef>
#include <limits>
#include "Usuarios.hpp"
#include "Pessoa.hpp"
#include "Estudante.hpp"
#include "Professor.hpp"
#include "Bibliotecario.hpp"
#include "TecnicoManutencao.hpp"

    Usuarios::Usuarios(): usuarios(), proximoId(1) {}

    bool Usuarios::adicionarUsuario(Pessoa *u, int id) {
        if (u == nullptr || id <= 0) {
            return false;
        }
        for (const auto &cadastrado : usuarios) {
            if (cadastrado.first == nullptr) {
                continue;
            }
            if (cadastrado.first == u || cadastrado.second == id || cadastrado.first->getCPF() == u->getCPF()) {
                return false;
            }
        }
        usuarios.push_back(std::make_pair(u, id));
        if (id >= proximoId && id < std::numeric_limits<int>::max()) {
            proximoId = id + 1;
        }
        return true;
    }

    int Usuarios::adicionarUsuario(Pessoa *u) {
        if (u == nullptr || proximoId <= 0 || proximoId >= std::numeric_limits<int>::max()) {
            return 0;
        }
        int id = proximoId;
        if (!adicionarUsuario(u, id)) {
            return 0;
        }
        return id;
    }

    bool Usuarios::removerUsuario(const std::string &nome) {
        for (auto it = usuarios.begin(); it != usuarios.end(); ++it) {
            Pessoa *pessoa = it->first;
            if (pessoa == nullptr || pessoa->getNome() != nome) {
                continue;
            }
            if (!pessoa->getEmprestimos().empty()) {
                return false;
            }
            TecnicoManutencao *tecnico = dynamic_cast<TecnicoManutencao*>(pessoa);
            if (tecnico != nullptr && !tecnico->getManutencoes().empty()) {
                return false;
            }
            delete pessoa;
            usuarios.erase(it);
            return true;
        }
        return false;
    }

    Pessoa* Usuarios::buscarUsuarioNome(const std::string &nome) const {
        for (const auto &usuario : usuarios) {
            if (usuario.first != nullptr && usuario.first->getNome() == nome) {
                return usuario.first;
            }
        }
        return nullptr;
    }

    Pessoa* Usuarios::buscarUsuarioId(const int id) const {
        for (const auto &usuario : usuarios) {
            if (usuario.first != nullptr && usuario.second == id) {
                return usuario.first;
            }
        }
        return nullptr;
    }

    Pessoa* Usuarios::buscarUsuarioCPF(const std::string &cpf) const {
        for (const auto &usuario : usuarios) {
            if (usuario.first != nullptr && usuario.first->getCPF() == cpf) {
                return usuario.first;
            }
        }
        return nullptr;
    }

    std::pair<Pessoa*, int> Usuarios::buscarUsuarioIndex(int index) const {
        if (index < 0 || static_cast<std::size_t>(index) >= usuarios.size()) {
            return std::make_pair(static_cast<Pessoa*>(nullptr), -1);
        }
        return usuarios[index];
    }

    const std::vector<std::pair<Pessoa*, int>>& Usuarios::getUsuarios() const {
        return usuarios;
    }

    std::string Usuarios::getOcupacao(const std::string &cpf) const {
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