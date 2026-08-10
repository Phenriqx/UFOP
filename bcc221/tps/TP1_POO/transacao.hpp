#ifndef TRANSACAO_HPP
#define TRANSACAO_HPP

#include <string>
#include <vector>

using namespace std;

class Cliente; // tem que avisar que a classe existe pra nao ter que chamar o arquivo aq

class Transacao {
private:
    double valor;
    string tipo;
    string data;
    string horario;
    vector<Cliente *> clientesEnvolvidos; // Coleção de clientes exigida

public:
    Transacao(const string &t, double v, const string &d, const string &h);

    // Métodos Getters e Setters de acordo com o UML
    string getTipo();

    double getValor();
    void setValor(double v);

    string getData();
    void setData(const string &d);

    string getHorario();
    void setHorario(const string &h);

    vector<Cliente *> getClientes();
    void setClientes(Cliente *c);

    // Método para exibir as informações da transação
    void exibirTransacao();

    string getHeader();

    friend ostream &operator<<(ostream &out, const Transacao& t);
};

Transacao *criarTransacao(vector<Cliente> &clientes);
bool processarTransferencia(Transacao &t, vector<Cliente> &clientes, double valor);
bool processarSaque(Transacao &t, vector<Cliente> &clientes, double valor);
void solicitarCliente(vector<Cliente> &clientes, Cliente *&c, string mensagem);
bool processarDeposito(Transacao &t, vector<Cliente> &clientes, double valor);
bool verificaSaldo(Cliente &c, double valor);

#endif