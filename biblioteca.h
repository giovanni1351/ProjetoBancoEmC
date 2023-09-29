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
    char extrato[100][1000];
    long long int senha;
    int tipo ;
};


typedef struct Cliente Cliente;
void salva_cliente(struct Cliente lista[], int quantidadeDeTarefas);
void ler_clientes(struct Cliente lista[], int *Quantidade_De_Clientes);
void NovoCliente(struct Cliente* lista, int* Quantidade_De_Clientes);
void ApagaCliente();
void ListarClientes(struct Cliente* lista, int Quantidade_De_Clientes);
void debito();
void deposito();
void extrato();
void transferencia();



#endif //PROJETOBANCO_BIBLIOTECA_H
