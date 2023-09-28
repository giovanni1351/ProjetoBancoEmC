//
// Created by unifgmorassi on 28/09/2023.
//

#ifndef PROJETOBANCO_BIBLIOTECA_H
#define PROJETOBANCO_BIBLIOTECA_H
#include "stdlib.h"
struct Cliente{
    char nome[100];
    int cpf;
    double saldo;
    char extrato[100][1000];
    int senha;
    int tipo;
};
typedef struct Cliente;
void salva_cliente(struct Cliente lista[], int quantidadeDeTarefas);
void ler_clientes(struct Cliente lista[], int *Quantidade_De_Clientes);


#endif //PROJETOBANCO_BIBLIOTECA_H
