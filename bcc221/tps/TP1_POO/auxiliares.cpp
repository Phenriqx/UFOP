#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <format>
#include <sstream>

#include "pessoa.hpp"
#include "cliente.hpp"
#include "gerente.hpp"
#include "auxiliares.hpp"

using namespace std;

void limparTerminal() {
    system("clear");
}

void limparBuffer() {
    cin.ignore(100, '\n');
}

int lerValor(int n) {
    int valor;
    string entrada;

    while (true) {
        try {
            cout << "- ";
            getline(cin, entrada);
            size_t pos;                  // stoi pede uma variável do tipo size_t, por isso nao pode ser int
            valor = stoi(entrada, &pos); // o pos armazena o índice do primeiro char dps do ultimo número lido

            // se pos for diferente do tamanho da entrada, significa que o usuário enviou uma entrada incorreta, como 1aa
            // nesse caso, pos seria 1, e entrada.size() 3, então é uma entrada inválida
            if (pos != entrada.size())
                throw invalid_argument("Insira uma entrada válida.");

            else if (valor >= 1 && valor <= n)
                return valor;
            else
                cout << "Valor inválido! Escolha entre 1 e " << n << ": " << endl;
        } catch(exception &e) {
            cerr << "Valor inválido! Escolha entre 1 e " << n << ": " << endl;
        }
    }

    return -1;
}

string toLowerString(string s) {
    // usando "auto" o compilador deduz automaticamente o tipo da varíavel e usando & passamos por referência, permitindo modificação no objeto
    for (auto &c : s)
        c = tolower(c);

    return s;
}

void carregarClientes(vector<Cliente> &clientes) {
    ifstream file("arquivos/clientes.csv");

    if (!file.is_open()) // verifica se o arquivo existe
        return;

    string linha;
    getline(file, linha); // descarta o cabecalho

    while (getline(file, linha)) { // leitura do arquivo

        stringstream ss(linha);
        string nome, trabalho, login, senha, tipoConta;
        string rem_str, saldo_str, taxa_str;

        // leitura separada por virgula
        getline(ss, nome, ',');
        getline(ss, trabalho, ',');
        getline(ss, login, ',');
        getline(ss, senha, ',');
        getline(ss, tipoConta, ',');
        getline(ss, rem_str, ',');
        getline(ss, saldo_str, ',');
        getline(ss, taxa_str, ',');

        // converte as strings numericas pra double
        double rem = stod(rem_str);
        double saldo = stod(saldo_str);
        double taxa = stod(taxa_str);

        // adiciona no programa
        clientes.push_back(Cliente(nome, trabalho, login, senha, rem, tipoConta, taxa, saldo, false));
    }
    file.close();
}

void carregarGerentes(vector<Gerente> &gerentes) {
    ifstream file("arquivos/gerentes.csv");

    if (!file.is_open())
        return;

    string linha;
    getline(file, linha);

    while (getline(file, linha)) {
        stringstream ss(linha);
        string nome, trabalho, login, senha;

        getline(ss, nome, ',');
        getline(ss, trabalho, ',');
        getline(ss, login, ',');
        getline(ss, senha, ',');

        gerentes.push_back(Gerente(nome, login, senha));
    }
    file.close();
}

void escreverTransacoes(const string& arquivo, const vector<Transacao*>& transacoes) {
    if (transacoes.empty())
        return;

    ofstream file(arquivo);
    file << "tipo,valor,data,horario,clientesEnvolvidos\n";

    for (Transacao* t : transacoes)
        file << *t;

    file.close();
}

void carregarTransacoes(const string& arquivo, vector<Transacao*>& transacoes, vector<Cliente>& clientes) {
    ifstream file(arquivo);
    if (!file.is_open())
        return;

    string linha;
    getline(file, linha); // descarta o header

    while (getline(file, linha)) {
        if (linha.empty()) continue;

        stringstream ss(linha);
        string tipo, valorStr, data, horario, nomeCliente;

        getline(ss, tipo,     ',');
        getline(ss, valorStr, ',');
        getline(ss, data,     ',');
        getline(ss, horario,  ',');

        Transacao* t = new Transacao(tipo, stod(valorStr), data, horario);

        while (getline(ss, nomeCliente, ',')) {
            if (nomeCliente.empty()) continue;

            // Busca o cliente pelo nome no vetor
            for (Cliente& c : clientes) {
                if (c.getNome() == nomeCliente) {
                    t->setClientes(&c);
                    c.setTransacao(t);
                    break;
                }
            }
        }

        transacoes.push_back(t);
    }

    file.close();
}

void escreverCartoes(vector<Cliente>& clientes) {
    ofstream fileCartoes("arquivos/cartoes.csv");
    ofstream fileCompras("arquivos/compras.csv");

    // escreve os headers no csv
    fileCartoes << "nome,temCartao,limiteTotal,limiteDisponivel,valorFatura,bloqueado,faturaGerada\n";
    fileCompras << "nome,descricao,valorTotal,qtdParcelas,parcelasPagas\n";

    for (Cliente& c : clientes) {
        // salva o booleano tem cartao -> 0 ou 1
        fileCartoes << c.getNome() << "," << c.possuiCartao();

        if (c.possuiCartao()) {
            CartaoCredito& cartao = c.getCartao();
            fileCartoes << "," << cartao.getLimiteTotal()
                        << "," << cartao.getLimiteDisponivel()
                        << "," << cartao.getValorFatura()
                        << "," << cartao.estaBloqueado()
                        << "," << cartao.isFaturaGerada();

            // Salva as compras relacionadas com o nome do cliente
            for (const CompraParcelada& comp : cartao.getCompras()) {
                fileCompras << c.getNome() << ","
                            << comp.getDescricao() << ","
                            << comp.getValorTotal() << ","
                            << comp.getQuantidadeParcelas() << ","
                            << comp.getParcelasPagas() << "\n";
            }
        } else {
            // Se não tem cartão, preenche o resto da linha com zeros
            fileCartoes << ",0,0,0,0,0";
        }
        fileCartoes << "\n";
    }
    fileCartoes.close();
    fileCompras.close();
}

void carregarCartoes(vector<Cliente>& clientes) {
    ifstream fileCartoes("arquivos/cartoes.csv");

    if (!fileCartoes.is_open())
        return;

    string linha;
    getline(fileCartoes, linha); // Pula cabeçalho

    while (getline(fileCartoes, linha)) {
        if (linha.empty())
            continue;

        stringstream ss(linha);
        string nome, temCartaoStr, limTotalStr, limDispStr, valFaturaStr, bloqStr, fatGeradaStr;

        getline(ss, nome, ',');
        getline(ss, temCartaoStr, ',');
        getline(ss, limTotalStr, ',');
        getline(ss, limDispStr, ',');
        getline(ss, valFaturaStr, ',');
        getline(ss, bloqStr, ',');
        getline(ss, fatGeradaStr, ',');

        // Se temCartaoStr for "1", restaura os dados
        if (temCartaoStr == "1") {
            Cliente* c = buscaPessoa(clientes, nome);
            if (c != nullptr) {
                c->restaurarCartao(stod(limTotalStr), stod(limDispStr), stod(valFaturaStr), bloqStr == "1", fatGeradaStr == "1");
            }
        }
    }
    fileCartoes.close();

    // Carregar as compras em cada cartão respectivo
    ifstream fileCompras("arquivos/compras.csv");
    if (!fileCompras.is_open())
        return;

    getline(fileCompras, linha); // Pula cabeçalho

    while (getline(fileCompras, linha)) {
        if (linha.empty()) continue;
        stringstream ss(linha);
        string nome, desc, valTotStr, qtdParcStr, pagasStr;

        getline(ss, nome, ',');
        getline(ss, desc, ',');
        getline(ss, valTotStr, ',');
        getline(ss, qtdParcStr, ',');
        getline(ss, pagasStr);

        Cliente* c = buscaPessoa(clientes, nome);
        if (c != nullptr && c->possuiCartao()) {
            c->getCartao().restaurarCompra(desc, stod(valTotStr), stoi(qtdParcStr), stoi(pagasStr));
        }
    }
    fileCompras.close();
}