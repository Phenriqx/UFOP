#include "transacao.hpp"
#include "cliente.hpp"
#include "pessoa.hpp"
#include "auxiliares.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <string>

Transacao::Transacao(const string& t, double v, const string& d, const string& h)
    : valor(v),
      tipo(t),
      data(d),
      horario(h)

{
    // a classe foi inicializada acima
}

string Transacao::getTipo()
{
    return tipo;
}

double Transacao::getValor()
{
    return valor;
}

void Transacao::setValor(double v)
{
    if (v >= 0.001)
        valor = v;
    else
        cout << "Erro: Valor invalido";
}

string Transacao::getData()
{
    return data;
}

void Transacao::setData(const string &d)
{
    data = d;
}

string Transacao::getHorario()
{
    return horario;
}

void Transacao::setHorario(const string& h)
{
    horario = h;
}

void Transacao::setClientes(Cliente *c)
{
    clientesEnvolvidos.push_back(c);
}

vector<Cliente *> Transacao::getClientes()
{
    return clientesEnvolvidos; // ja eh a colecao de clientes envolvidos completa
}

void Transacao::exibirTransacao() {
    cout << "Tipo: " << tipo << endl
         << "Valor: R$ " << valor << endl
         << "Data: " << data << endl
         << "Horario: " << horario << endl;

    cout << "Clientes Envolvidos:" << endl; // impressao dos clientes

    if (clientesEnvolvidos.empty()) // verifica se a lista esta vazia
        cout << "  Nenhum cliente registrado nesta transação." << endl;
    else
        for (Cliente *cliente : clientesEnvolvidos) {
            string nome = cliente->getNome();
            cout << "  - " << nome << endl; // o nome esta protegido na classe pessoa -> usamos getter
        }
}

Transacao *criarTransacao(vector<Cliente> &clientes) {
    double valor;
    string tipo, data, horario;

    cout << "Tipo da Transação (Transferencia, Deposito, Saque): ";
    cin >> tipo;
    string tipoLower = toLowerString(tipo);

    while (tipoLower != "transferencia" && tipoLower != "deposito" && tipoLower != "saque") {
        cout << "Erro: Transação inválida. Escolha entre Transferencia, Deposito ou Saque." << endl << endl;
        cout << "Tipo da Transação (Transferencia, Depósito, Saque): ";
        cin >> tipo;
        tipoLower = toLowerString(tipo);
    }

    cout << "Valor: ";
    while (!(cin >> valor) || valor <= 0) {
        cout << "Erro: O valor da transação deve ser numérico e maior que zero." << endl << endl;
        cin.clear();
        limparBuffer();
        cout << "Valor: ";
    }

    cout << "Data (DD/MM/AAAA): ";
    cin >> data;
    while (data.length() != 10 || data[2] != '/' || data[5] != '/') {
        cout << "Erro: Formato de data inválido. Use exatamente o padrão DD/MM/AAAA." << endl << endl;
        cout << "Data (DD/MM/AAAA): ";
        cin >> data;
    }

    cout << "Horário (HH:MM): ";
    cin >> horario;
    while (horario.length() != 5 || horario[2] != ':') {
        cout << "Erro: Formato de horário inválido. Use exatamente o padrão HH:MM." << endl << endl;
        cout << "Horário (HH:MM): ";
        cin >> horario;
    }

    Transacao *t = new Transacao(tipo, valor, data, horario);

    if (tipoLower == "transferencia") {
        if (!processarTransferencia(*t, clientes, valor))
            return nullptr;
    }

    else if (tipoLower == "saque") {
        if (!processarSaque(*t, clientes, valor))
            return nullptr;
    }

    else if (tipoLower == "deposito") {
        if (!processarDeposito(*t, clientes, valor))
            return nullptr;
    }
    return t;
}

// se o tipo é transferência, precisamos do nome dos clientes que estão envolvidos na transação e verificar se eles estão no vetor de clientes
bool processarTransferencia(Transacao &t, vector<Cliente> &clientes, double valor) {
    Cliente *c1 = nullptr;
    Cliente *c2 = nullptr;

    limparBuffer();

    solicitarCliente(clientes, c1, "Cliente 1 (Pagador): ");
    solicitarCliente(clientes, c2, "Cliente 2 (Destinatário): ");

    if (c1 == c2) {
        cout << "Os clientes não podem ser os mesmos" << endl;
        return false;
    }

    if (!verificaSaldo(*c1, valor))
        return false;

    // c1->setTransacao(&t);
    // c2->setTransacao(&t);
    c1->setSaldo(c1->getSaldo() - valor);
    c2->setSaldo(c2->getSaldo() + valor);

    t.setClientes(c1);
    t.setClientes(c2);
    return true;
}

bool processarSaque(Transacao &t, vector<Cliente> &clientes, double valor) {
    Cliente *c;
    limparBuffer();
    solicitarCliente(clientes, c, "Nome do dono da conta: ");

    if (!verificaSaldo(*c, valor))
        return false;

    // c->setTransacao(&t);
    c->setSaldo(c->getSaldo() - valor);
    t.setClientes(c);

    return true;
}

void solicitarCliente(vector<Cliente> &clientes, Cliente *&c, string mensagem) {
    string pessoa;
    do {
        cout << mensagem;
        getline(cin, pessoa);

        c = buscaPessoa(clientes, pessoa);
    } while (c == nullptr);
}

bool processarDeposito(Transacao &t, vector<Cliente> &clientes, double valor) {
    Cliente *c;
    limparBuffer();
    solicitarCliente(clientes, c,"Nome do dono da conta: ");

    // c->setTransacao(&t);
    c->setSaldo(c->getSaldo() + valor);
    t.setClientes(c);

    return true;
}

bool verificaSaldo(Cliente &c, double valor) {
    if (c.getSaldo() - valor < 0) {
        cout << "O cliente " << c.getNome() << " não tem saldo suficiente para essa operação." << endl;
        return false;
    }
    return true;
}

string Transacao::getHeader() {
    return "tipo,valor,data,horario,clientesEnvolvidos";
}

ostream &operator<<(ostream &out, const Transacao &t) {
    out << t.tipo << "," << t.valor << "," << t.data << "," << t.horario;

    for (Cliente* c : t.clientesEnvolvidos)
        out << "," << c->getNome();
    out << "\n";

    return out;
}