#include "cliente.hpp"
#include "transacao.hpp"
#include "auxiliares.hpp"
#include "pessoa.hpp"
#include "credito.hpp"
#include <iostream>
#include <string>
#include <vector>

Cliente::Cliente(const string &n, const string &t, const string &l, const string &s,
                 double rem, const string &tipo, double taxa, double sal, bool temCartao) : Pessoa(n, t, l, s),
                                                                                            taxaDeRendimento(taxa),
                                                                                            saldo(sal),
                                                                                            tipoDeConta(tipo),
                                                                                            temCartao(temCartao)
{

    setRemuneracao(rem);

    if (temCartao)
        cartao.criar(remuneracao);
}

void Cliente::exibirDados()
{
    cout << endl << "\t\tDados do Cliente" << endl;

    Pessoa::exibirDados(); // adiciona a implementacao da classe mae

    // adiciona os dados especificos
    cout << "Remuneração: R$ " << remuneracao << endl;
    cout << "Tipo de Conta: " << tipoDeConta << endl;
    cout << "Saldo Atual: R$ " << saldo << endl;

    string tipoLower = toLowerString(tipoDeConta);

    // se for poupanca mostra a taxa
    if (tipoLower == "poupança")
        cout << "Valor do rendimento mensal: " << taxaDeRendimento << endl;

    cout << endl;
    cout << "Total de transações realizadas: " << transacoes.size() << endl;
    for (auto &t : transacoes)
        t->exibirTransacao();
}

string Cliente::getTipoDeConta()
{
    return tipoDeConta;
}

void Cliente::setTipoDeConta(const string &tipo) {
    tipoDeConta = tipo;
    string tipoLower = toLowerString(tipoDeConta);

    if (tipoLower == "corrente") {
        taxaDeRendimento = 0.0;
    } else if (tipoLower == "poupança") {
        taxaDeRendimento = remuneracao * 0.05;
    }
}

double Cliente::getSaldo()
{
    return saldo;
}

void Cliente::setSaldo(double s)
{
    saldo = s;
}

void Cliente::setTransacao(Transacao *t)
{
    transacoes.push_back(t);
}

vector<Transacao *> Cliente::getExtrato()
{
    return transacoes;
}

double Cliente::getRendimento()
{
    return taxaDeRendimento;
}

double Cliente::getRemuneracao()
{
    return remuneracao;
}

void Cliente::setRemuneracao(double novaRemuneracao)
{
    if (novaRemuneracao < 0)
    {
        cout << "Erro: a remuneração não pode ser negativa." << endl;
        return;
    }

    remuneracao = novaRemuneracao;

    if (toLowerString(tipoDeConta) == "poupança")
    {
        taxaDeRendimento = remuneracao * 0.05;
    }
}

// só possui taxa de rendimento se o tipo da conta for poupança
void Cliente::setRendimento(double r)
{
    string tipoConta = getTipoDeConta();
    if (tipoConta == "poupança")
        taxaDeRendimento = r;
}

// função amiga da classe
// realiza a sobrecarga do operador << para poder salvar os dados no arquivo csv usando {file << cliente} para melhor legibilidade do código
ostream &operator<<(ostream &out, const Cliente &c) {
    out << c.getNome() << ','
        << c.getTrabalho() << ','
        << c.getLogin() << ','
        << c.getSenha() << ','
        << c.tipoDeConta << ','
        << c.remuneracao << ','
        << c.saldo << ','
        << c.taxaDeRendimento
        << endl;

    return out;
}

Cliente cadastrarCliente() {
    string nome, trabalho, login, senha, tipoDeConta;
    double remuneracao, taxaRendimento, saldo;

    cout << "Nome: ";
    getline(cin, nome);
    cout << "Trabalho: ";
    getline(cin, trabalho);
    cout << "Login: ";
    getline(cin, login);
    cout << "Senha: ";
    getline(cin, senha);

    cout << "Tipo de conta (Poupança ou Corrente): ";
    cin >> tipoDeConta;
    while (toLowerString(tipoDeConta) != "poupança" && toLowerString(tipoDeConta) != "corrente") {
        cout << "Erro, escolha entre os tipos disponíveis: Poupança ou Corrente" << endl
             << endl;
        cout << "Tipo de Conta: ";
        cin >> tipoDeConta;
    }

    cout << "Remuneração: ";
    while (!(cin >> remuneracao) || remuneracao < 0) {
        cout << "Erro: Digite um valor numérico válido e não negativo." << endl << endl;

        cin.clear();             // Limpa a flag de erro do cin
        limparBuffer();

        cout << "Remuneração: ";
    }

    taxaRendimento = 0.0;
    if (toLowerString(tipoDeConta) == "poupança") {
        taxaRendimento = remuneracao * 0.05;
        cout << "Valor do seu Rendimento: " << taxaRendimento << endl;
    }

    cout << "Saldo: ";
    while (!(cin >> saldo) || saldo < 0) {
        cout << "Erro: Digite um valor numérico válido e não negativo." << endl << endl;
        cin.clear();             // Limpa a flag de erro do cin
        limparBuffer();

        cout << "Saldo: ";
    }
    cout << endl;

    cout << "Cliente cadastrado !!" << endl;

    return Cliente(nome, trabalho, login, senha, remuneracao, tipoDeConta, taxaRendimento, saldo, false);
}

void listarCliente(vector<Cliente> &clientes) {
    cout << "=== LISTA DE CLIENTES CADASTRADOS ===" << endl;
    if (clientes.empty())
        cout << "Nenhum cliente cadastrado no sistema." << endl;

    else {
        for (Cliente &c : clientes) {
            c.exibirDados();
            cout << "-----------------------------------" << endl;
        }
    }
}

void mostrarDadosCliente(vector<Cliente> &clientes) {
    string nome;
    cout << "Insira o nome do cliente: ";
    getline(cin, nome);


    Cliente *cliente = buscaPessoa(clientes, nome);
    if (cliente == nullptr)
        return;

    cliente->exibirDados();
}

// Cartão de crédito -------------------------------------

void Cliente::criarCartao() {
    if (temCartao) {
        cout << "Este cliente já possui cartão de crédito." << endl;
        return;
    }

    cartao.criar(remuneracao);
    temCartao = true;

    cout << "Cartão criado com sucesso!" << endl;
}

bool Cliente::possuiCartao() const {
    return temCartao;
}

CartaoCredito &Cliente::getCartao() {
    return cartao;
}

void Cliente::restaurarCartao(double limTot, double limDisp, double valFat, bool bloq, bool fatGerada) {
    temCartao = true;
    cartao.restaurarDados(limTot, limDisp, valFat, bloq, fatGerada);
}