#ifndef CREDITO_HPP
#define CREDITO_HPP

#include <string>
#include <vector>

using namespace std;

class Cliente;
class Gerente;

class CompraParcelada {
private:
    string descricao;
    double valorTotal;
    int quantidadeParcelas;
    double valorParcela;
    int parcelasPagas;

public:
    CompraParcelada(string descricao, double valorTotal, int quantidadeParcelas);

    string getDescricao() const;
    double getValorTotal() const;
    int getQuantidadeParcelas() const;
    double getValorParcela() const;
    int getParcelasPagas() const;
    int getParcelasRestantes() const;
    void setParcelasPagas(int pagas);

    bool estaQuitada() const;
    void pagarUmaParcela();
    void exibirCompra() const;
};

class CartaoCredito {
private:

    double limiteTotal;
    double limiteDisponivel;
    double valorFatura;
    bool bloqueado;
    bool faturaGerada;
    vector<CompraParcelada> comprasParceladas;


public:
    CartaoCredito();

    //getters
    double getLimiteTotal() const;
    double getLimiteDisponivel() const;
    double getValorFatura() const;
    bool estaBloqueado() const;


    void criar(double remuneracao);
    void alterarLimite(double novoLimite);
    void bloquear();
    void desbloquear();
    void gerarFatura();
    void exibirComprasParceladas() const;
    bool pagarFatura(double& saldoCliente);
    void exibirFatura() const;

    bool isFaturaGerada() const;
    const vector<CompraParcelada>& getCompras() const;
    void restaurarDados(double limTot, double limDisp, double valFat, bool bloq, bool fatGerada);
    void restaurarCompra(string desc, double valTot, int qtdParc, int parcPagas);

    //Parcelas
    bool realizarCompraParcelada(string descricao, double valorTotal, int parcelas);

};

void cartaoMain(vector<Cliente>& clientes, vector<Gerente>& gerentes);
void criarCartaoParaCliente(vector<Cliente>& clientes, vector<Gerente>& gerentes);
bool clienteVinculadoAoGerente(Gerente& gerente, Cliente* cliente);
void bloquearCartao(vector<Cliente>& clientes, vector<Gerente>& gerentes);
void desbloquearCartao(vector<Cliente>& clientes, vector<Gerente>& gerentes);

void alterarLimiteCartao(vector<Cliente>& clientes, vector<Gerente>& gerentes);


void realizarCompraParcelada(vector<Cliente>& clientes);
void acessarFatura(vector<Cliente>& clientes);


#endif