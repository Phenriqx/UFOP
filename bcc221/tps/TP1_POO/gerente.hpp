#ifndef GERENTE_HPP
#define GERENTE_HPP

#include "pessoa.hpp"
#include <vector>
#include <string>

using namespace std;

// Forward declaration para evitar dependência circular
class Cliente;

class Gerente : public Pessoa {
private:
    vector<Cliente *> clientes; // clientes vinculados

public:
    Gerente(const string& n, const string& l, const string& s);

    void exibirDados() override;

    vector<Cliente *> getClientes();
    void setCliente(Cliente *c);

    string getHeader() override {
        return "nome,trabalho,login,senha";
    }

    friend ostream& operator<<(ostream& out, const Gerente& g);
};

Gerente cadastrarGerente();
void vincularCliente(vector <Cliente>& clientes, vector<Gerente>& gerentes);
void listarGerentes(vector <Gerente>& gerente);

#endif