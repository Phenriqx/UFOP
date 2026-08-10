#ifndef PESSOA_HPP
#define PESSOA_HPP

#include <string>
#include <iostream>

using namespace std;

class Pessoa
{
protected:
    string nome;
    string trabalho;

private:
    string login;
    string senha;

public:
    virtual void exibirDados();

    void setTrabalho(string &t);
    void setSenha(string &s);
    void setLogin(string &l);
    void setNome(string &n);

    string getSenha() const;
    string getLogin() const;
    string getTrabalho() const;
    string getNome() const;

    // friend void getInfoCSV(const Pessoa& p, Gerente& g);

    virtual string getHeader() = 0;

    Pessoa(const string &n = "NOME", const string &t = "TRABALHO", const string &l = "LOGIN", const string &s = "SENHA");
    virtual ~Pessoa() = default; // destrutor de classe virtual
};

#endif
