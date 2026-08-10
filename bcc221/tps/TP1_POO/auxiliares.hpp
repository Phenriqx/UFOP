#ifndef AUXILIARES_H
#define AUXILIARES_H

#include <string>
#include <fstream>
#include <vector>

#include "pessoa.hpp"
#include "cliente.hpp"
#include "gerente.hpp"
#include "transacao.hpp"

int lerValor(int n);
void limparTerminal();
void limparBuffer();
string toLowerString(string s);
Cliente* buscaCliente(vector<Cliente>& clientes, const string& nome);


// o template é um tipo genérico que permite a função trabalhar com tipos genéricos, o que permite escrever uma função ao invés de duas ou mais pra tipos diferentes
template<typename T>
void escreverCSV(const string &arquivo, vector<T> vec) {
    if (vec.empty())
    return;

    ofstream file(arquivo);

    file << vec[0].getHeader() << endl;
    for (auto& item: vec)
    file << item;

    file.close();
}

template<typename T>
T* buscaPessoa(vector <T>& pessoas, const string& nome) {
    for (auto& pessoa: pessoas)
        if (pessoa.getNome() == nome)
            return &pessoa;

    cout << nome << " não se encontra no nosso Banco de Dados" << endl;
    return nullptr;
}

void carregarClientes(vector<Cliente>& clientes);
void carregarGerentes(vector<Gerente>& gerentes);
void escreverTransacoes(const string& arquivo, const vector<Transacao*>& transacoes);
void carregarTransacoes(const string& arquivo, vector<Transacao*>& transacoes, vector<Cliente>& clientes);
void carregarCartoes(vector<Cliente>& clientes);
void escreverCartoes(vector<Cliente>& clientes);

#endif