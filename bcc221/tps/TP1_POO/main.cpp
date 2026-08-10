#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include "credito.hpp"
#include "pessoa.hpp"
#include "cliente.hpp"
#include "gerente.hpp"
#include "transacao.hpp"
#include "auxiliares.hpp"

using namespace std;

int main() {
    /*
    Inicializa os vetores de clientes, gerentes e transações para poder salvar e ler do arquivo
    */
    int valor;
    vector<Cliente> clientes;
    vector<Gerente> gerentes;
    vector<Transacao *> transacoes;

    clientes.reserve(100);
    gerentes.reserve(100);

    // Carrega o que tiver salvo no arquivo
    carregarClientes(clientes);
    carregarGerentes(gerentes);
    carregarTransacoes("arquivos/transacoes.csv", transacoes, clientes);
    carregarCartoes(clientes);

    do {
        limparTerminal();

        cout << "====== SISTEMA DE GERENCIAMENTO DE BANCO ====== " << endl;
        cout << "1. Cadastrar Cliente" << endl
             << "2. Cadastrar Gerente" << endl
             << "3. Criar transacao" << endl
             << "4. Exibir extrato de um Cliente" << endl
             << "5. Associar gerente a cliente" << endl
             << "6. Listar clientes" << endl
             << "7. Listar gerentes" << endl
             << "8. Cartão de crédito" << endl
             << "9. Salvar dados e sair" << endl;
        cout << "======================================================" << endl;
        valor = lerValor(9);

        limparTerminal();
        switch (valor) {
        // Cadastrar cliente
            case 1: {
                Cliente novoCliente = cadastrarCliente();
                novoCliente.exibirDados();
                clientes.push_back(novoCliente);

                break;
            }
            // Cadastrar gerente
            case 2: {
                Gerente novoGerente = cadastrarGerente();
                novoGerente.exibirDados();
                gerentes.push_back(novoGerente);

                break;
            }
            // Criar transação
            case 3: {
                Transacao *t = criarTransacao(clientes);
                if (t != nullptr)
                {
                    transacoes.push_back(t);
                    for (Cliente *c : t->getClientes())
                        c->setTransacao(t);

                    t->exibirTransacao();
                }

                break;
            }
            // Exibir extrato de um cliente
            case 4: {
                mostrarDadosCliente(clientes);
                break;
            }

            // Associar cliente a gerente
            case 5: {
                vincularCliente(clientes, gerentes);

                break;
            }
            case 6: {
                listarCliente(clientes);
                break;
            }

            case 7: {
                listarGerentes(gerentes);
                break;
            }

            case 8: {
                cartaoMain(clientes, gerentes);
                break;
            }

            case 9: {
                cout << "Salvando registros nos arquivos. Por favor aguarde..." << endl;
                sleep(1);
                escreverCSV("arquivos/clientes.csv", clientes);
                escreverCSV("arquivos/gerentes.csv", gerentes);
                escreverTransacoes("arquivos/transacoes.csv", transacoes);
                escreverCartoes(clientes);

                break;
            }
            default: {
                break;
            }
        }

        if (valor != 9 && valor != 8) {
            cout << endl
                 << "Pressione Enter para voltar ao menu!" << endl;

            cin.get();
        }
    } while (valor != 9);

    for (Transacao *t : transacoes) { // exclui transacoes alocadas dinamicamente
        delete t;
    }

    return 0;
}