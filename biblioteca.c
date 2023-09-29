//
// Created by unifgmorassi on 28/09/2023.
//

#include "biblioteca.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void ler_clientes(struct Cliente lista[], int *Quantidade_De_Clientes) {
    FILE *arquivo = fopen("Dados", "rb");//ele abre o arquivo como ler binario
    if (arquivo) {//se obter sucesso ele vai ler com o fread e armazenara no arquivo aberto
        //as informaçoes ficarão na lista q foi passada como parametro
        while (fread(&lista[*Quantidade_De_Clientes], sizeof(struct Cliente), 1, arquivo) == 1) {
            (*Quantidade_De_Clientes)++;//ele vai ler de 1 em 1 até o fim do arquivo, a cada leitura ele soma 1 na quantidade de tarefas
            //para manter o controle de tarefas
        }
        fclose(arquivo);//ele fecha o arquivo
    }
}
void salva_cliente(struct Cliente lista[], int Quantidade_De_Clientes) {
    FILE *arquivo = fopen("Dados", "wb");//abre o arquivo como write em binario

    if (arquivo) {//se ele obter sucesso
        //ele escreve tudo da lista de structs no arquivo q foi aberta
        fwrite(lista, sizeof(struct Cliente), Quantidade_De_Clientes, arquivo);
        fclose(arquivo);//fecha o arquivo
    }
}
void NovoCliente(struct Cliente *lista,int *Quantidade_De_Clientes){
    printf("Digite seu CPF:\n");
    long long int senha,tipo;
    char cpf[15];
    int encontrado = 0;
    int idEncontrado;
    scanf("%s",cpf);
    for (int x = 0; x < (*Quantidade_De_Clientes); x++) {

        if (strcmp(cpf,lista[x].cpf)==0) {
            printf("Cliente ja registrado!\n");
            encontrado = 1;
            idEncontrado =x;
        }
    }
    if (encontrado == 0) {
        Cliente atual;
        atual.saldo =0;
        atual.transacoes =0;
        strcpy(atual.cpf,cpf);
        printf("Digite seu nome:\n");
        char nome[100];
        scanf("%s", &nome);
        strcpy(atual.nome, nome);
        printf("Digite sua senha (6 numeros):\n");
        scanf("%d", &senha);
        atual.senha = senha;
        printf("Digite qual tipo vai ser sua conta?(1.comum ou 2.plus):\n");
        scanf("%d", &tipo);
        atual.tipo = tipo;
        lista[(*Quantidade_De_Clientes)] = atual;
        (*Quantidade_De_Clientes)++;
    }
    else {
        Cliente C_encontrado = lista[idEncontrado];

        int trocar;
        printf("Voce deseja alterar a senha?(1.sim 2.nao)\n");
        scanf("%d",&trocar);
        if(trocar ==1){
            int nova_senha;
            printf("Digite a nova senha:\n");
            scanf("%d",&nova_senha);
            C_encontrado.senha = nova_senha;
            lista[idEncontrado] = C_encontrado;
        }
    }
    printf("\n");
}
void ApagaCliente(){
    printf("funciona\n");

}
void ListarClientes(struct Cliente* lista, int Quantidade_De_Clientes){
    printf("Quantidade de Clientes atuais: %d\n",Quantidade_De_Clientes);

    for(int x = 0 ; x < Quantidade_De_Clientes;x++){
        printf("Nome: %s\n",lista[x].nome);
        printf("CPF: %s\n",lista[x].cpf);
        printf("Tipo da conta: %d\n",lista[x].tipo);
        printf("Senha da conta: %d\n",lista[x].senha);
        printf("Saldo da conta: %d\n",lista[x].saldo);
        printf("\n");
        printf("\n");

    }

}
void debito(struct Cliente *lista, int Quantidade_De_Clientes) {
    int  senha;
    char cpf[15];
    printf("Digite o CPF: \n");
    scanf("%s", &cpf);
    int idEncontrado;
    int encontrado =0;
    for(int x = 0 ; x < Quantidade_De_Clientes;x++){
        if(strcmp(cpf,lista[x].cpf)==0){

            idEncontrado =x;
            encontrado =1;
            printf("encontrado id: %d!\n",x);
            break;
        }
    }
    if(encontrado ==1){
        printf("Digite sua senha: \n");
        int senhaConta = lista[idEncontrado].senha;
        printf("%d\n",lista[idEncontrado].senha);
        scanf("%d", &senha);
        if(senha == senhaConta){
            double valor;
            double saldo_cliente = lista[idEncontrado].saldo;
            printf("Valor do débito:\n ");
            scanf("%d", &valor);
            saldo_cliente -= valor;
            lista[idEncontrado].saldo = saldo_cliente;
            printf("Saldo atual: %d \n",lista[idEncontrado].saldo);
            printf("%d \n",saldo_cliente);
        }
        else{
            printf("Senha incorreta!\n");
        }
    }
    if(encontrado ==0){
        printf("Cliente com cpf %s não encontrado.\n", cpf);
    }
}

void deposito(struct Cliente *lista, int Quantidade_De_Clientes) {
    int  senha;
    char cpf[15];
    printf("Digite o CPF: \n");
    scanf("%s", &cpf);
    int idEncontrado;
    int encontrado =0;
    for(int x = 0 ; x < Quantidade_De_Clientes;x++){
        if(strcmp(cpf,lista[x].cpf)==0){

            idEncontrado =x;
            encontrado =1;
            printf("encontrado id: %d!\n",x);
            break;
        }
    }
    if(encontrado ==1){
            double valor;
            double saldo_cliente = lista[idEncontrado].saldo;
            printf("Valor do deposito:\n ");
            scanf("%d", &valor);
            saldo_cliente += valor;
            lista[idEncontrado].saldo = saldo_cliente;
            printf("Saldo atual: %d \n",lista[idEncontrado].saldo);
            printf("%d \n",saldo_cliente);
    }
    if(encontrado ==0){
        printf("Cliente com cpf %s não encontrado.\n", cpf);
    }
}


void extrato(struct Cliente *lista, int Quantidade_De_Clientes) {
    int cpf;
    printf("Digite o cpf: ");
    scanf("%d", &cpf);


    for (int i = 0; i < Quantidade_De_Clientes; i++) {
        if (lista[i].cpf == cpf) {
            printf("Extrato %s (cpf: %d)\n", lista[i].nome, lista[i].cpf);
            printf("Saldo: %d\n", lista[i].saldo);
            return;
        }
    }
    printf("Cliente com cpf %d não encontrado.\n", cpf);
}

void transferencia(){
    printf("vamos la\n");
};