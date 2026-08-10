#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include "credito.hpp"
#include "pessoa.hpp"
#include "transacao.hpp" // Necessário para o vector de transações
#include <vector>
#include <string>

using namespace std;

class Cliente : public Pessoa
{
private:
    double remuneracao;
    double taxaDeRendimento;
    double saldo;
    string tipoDeConta;
    vector<Transacao *> transacoes; // Coleção exigida pelo diagrama eh o extrato
    CartaoCredito cartao;
    bool temCartao;

public:
    Cliente(const string &n, const string &t, const string &l, const string &s,
            double rem, const string &tipo, double taxa, double sal, bool temCartao);

    void exibirDados() override;

    void setTransacao(Transacao *t);
    vector<Transacao *> getExtrato();

    string getTipoDeConta();
    void setTipoDeConta(const string &tipo);

    double getRemuneracao();
    void setRemuneracao(double novaRemuneracao);

    double getSaldo();
    void setSaldo(double s);

    double getRendimento();
    void setRendimento(double r);

    string getHeader() override {
        return "nome,trabalho,login,senha,conta,remuneracao,saldo,taxa_rendimento";
    }

    // realiza sobrecarga do operador <<
    friend ostream &operator<<(ostream &out, const Cliente &c);

    // cartão de crédito
    bool possuiCartao() const; // get de possui cartão
    CartaoCredito &getCartao();
    void criarCartao();
    void restaurarCartao(double limTot, double limDisp, double valFat, bool bloq, bool fatGerada);
};

bool clienteVinculadoAoGerente(Gerente &gerente, Cliente *cliente);
Cliente cadastrarCliente();
void mostrarDadosCliente(vector<Cliente> &clientes);
double getRemuneracao();
void listarCliente(vector<Cliente> &clientes);

#endif