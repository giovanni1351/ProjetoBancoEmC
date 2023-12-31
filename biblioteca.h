//
// Created by unifgmorassi on 28/09/2023.
//

#ifndef PROJETOBANCO_BIBLIOTECA_H
#define PROJETOBANCO_BIBLIOTECA_H
#include <stdlib.h>

struct Cliente{
    char nome[100];
    char cpf[15];
    double saldo;
    int transacoes;
    char extrato[100][1000];
    long long int senha;
    int tipo ;
};


typedef struct Cliente Cliente;
void salva_cliente(struct Cliente lista[], int quantidadeDeTarefas);
void ler_clientes(struct Cliente lista[], int *Quantidade_De_Clientes);
void NovoCliente(struct Cliente* lista, int* Quantidade_De_Clientes);
void ApagaCliente(struct Cliente* lista, int* Quantidade_De_Clientes);
void ListarClientes(struct Cliente* lista, int Quantidade_De_Clientes);
void debito(struct Cliente *lista, int Quantidade_De_Clientes);
void deposito(struct Cliente *lista, int Quantidade_De_Clientes) ;
void extrato(Cliente *lista, int Quantidade_De_Clientes);
void transferencia(Cliente *lista, int Quantidade_De_Clientes);



#endif //PROJETOBANCO_BIBLIOTECA_H
