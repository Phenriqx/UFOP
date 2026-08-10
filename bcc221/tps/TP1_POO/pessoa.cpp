#include "pessoa.hpp"
#include <string>
#include <iostream>

#include "gerente.hpp"

Pessoa::Pessoa(const string &n, const string &t, const string &l, const string &s) : nome(n),
                                                                                     trabalho(t),
                                                                                     login(l),
                                                                                     senha(s)
{
}

void Pessoa::setTrabalho(string &t)
{
    this->trabalho = t;
}
void Pessoa::setSenha(string &s)
{
    this->senha = s;
}
void Pessoa::setLogin(string &l)
{
    this->login = l;
}
void Pessoa::setNome(string &n)
{
    this->nome = n;
}

string Pessoa::getSenha() const
{
    return senha;
}

string Pessoa::getLogin() const
{
    return login;
}

string Pessoa::getTrabalho() const
{
    return trabalho;
}

string Pessoa::getNome() const
{
    return nome;
}

void Pessoa::exibirDados()
{ // ESSA FUNCAO EH VIRTUAL
    cout << "Nome: " << nome << endl;
    cout << "Trabalho: " << trabalho << endl;
    cout << "Login: " << login << endl;
}