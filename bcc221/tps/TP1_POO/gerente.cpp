#include "gerente.hpp"
#include "cliente.hpp"
#include "auxiliares.hpp"

#include <iostream>
#include <string>
#include <vector>

Gerente::Gerente(const string &n, const string &l, const string &s)
: Pessoa(n, "Gerente", l, s)

{
    // o gerente foi construido na chamada
}

vector<Cliente *> Gerente::getClientes()
{
    return clientes;
}

void Gerente::setCliente(Cliente *c)
{
    clientes.push_back(c);
}

void Gerente::exibirDados()
{
    cout << endl << "\t\tDados do Gerente" << endl;
    Pessoa::exibirDados();

    std::cout << "Quantidade de clientes vinculados: " << clientes.size() << endl;
    std::cout << "Clientes vinculados: ";

    if(clientes.size() == 0)
        std::cout << "Não há clientes vinculados" << endl;
    else
    {
        for (const auto &cliente : clientes)
        {
            std::cout <<endl;
            cliente->exibirDados();
        }
    }
}

ostream &operator<<(ostream &out, const Gerente &g)
{
    out << g.nome << ','
        << g.trabalho << ','
        << g.getLogin() << ','
        << g.getSenha() << ','
        << endl;

    return out;
}

Gerente cadastrarGerente() {
    string nome, login, senha;

    cout << "Nome: ";
    getline(cin,nome);
    cout << "Login: ";
    getline(cin, login);
    cout << "Senha: ";
    getline(cin, senha);

    return Gerente(nome, login, senha);
}

void vincularCliente(vector<Cliente> &clientes, vector<Gerente> &gerentes) {
    string nomeG, nomeC;
    cout << "Nome do Gerente: ";
    getline(cin, nomeG);
    cout << "Nome do Cliente: ";
    getline(cin, nomeC);

    Gerente *gEncontrado = buscaPessoa(gerentes, nomeG);
    Cliente *cEncontrado = buscaPessoa(clientes, nomeC);
    if (gEncontrado == nullptr || cEncontrado == nullptr)
        return;

    gEncontrado->setCliente(cEncontrado); // adiciona o cliente ao gerente
    cout << "Cliente '" << nomeC << "' associado com sucesso ao Gerente '" << nomeG << "'!" << endl;
}

void listarGerentes(vector<Gerente> &gerentes) {
    cout << "=== LISTA DE GERENTES CADASTRADOS ===" << endl;
    if (gerentes.empty())
        cout << "Nenhum gerente cadastrado no sistema." << endl;

    else
    {
        for (Gerente &g : gerentes)
        {
            g.exibirDados();
            cout << "-----------------------------------" << endl;
        }
    }
}