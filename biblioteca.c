//
// Created by unifgmorassi on 28/09/2023.
//

#include "biblioteca.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "biblioteca.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void ler_clientes(struct Cliente lista[], int *Quantidade_De_Clientes) {
    FILE *arquivo = fopen("DadosTeste", "rb");//ele abre o arquivo como ler binario
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
    FILE *arquivo = fopen("DadosTeste", "wb");//abre o arquivo como write em binario

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
void ApagaCliente(struct Cliente* lista, int* Quantidade_De_Clientes){
    printf("Digite seu CPF:\n");
    char cpf[15];
    int encontrado = 0;
    int idEncontrado;
    int deletar = 0;
    scanf("%s", cpf);
    for (int x = 0; x < (*Quantidade_De_Clientes); x++) {
        if (strcmp(lista[x].cpf, cpf) == 0) {

            encontrado = 1;
            idEncontrado = x;
        }
    }
    if (encontrado == 1) {
        printf("Digite sua senha: \n");
        long long int senha;
        scanf("%d", &senha);
        if (senha == lista[idEncontrado].senha) {
            deletar = 1;
        }
    }
    if (deletar == 1) {
        for (int x = idEncontrado; x < (*Quantidade_De_Clientes); x++) {
            lista[x] = lista[x + 1];
        }
        (*Quantidade_De_Clientes) -= 1;
        printf("Cliente deletado com sucesso!\n");
    }
}
void ListarClientes(struct Cliente* lista, int Quantidade_De_Clientes){
    printf("Quantidade de Clientes atuais: %d\n",Quantidade_De_Clientes);

    for(int x = 0 ; x < Quantidade_De_Clientes;x++){
        printf("Nome: %s\n",lista[x].nome);
        printf("CPF: %s\n",lista[x].cpf);
        printf("Tipo da conta: %d\n",lista[x].tipo);
        printf("Senha da conta: %d\n",lista[x].senha);
        printf("Saldo da conta: %lf\n",lista[x].saldo);
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
            printf("Valor do débito:\n ");
            scanf("%lf", &valor);
            //double saldo_cliente = lista[idEncontrado].saldo-valor;
            //lista[idEncontrado].saldo = saldo_cliente;
            lista[idEncontrado].saldo -= valor;
            char valor_string[50] ;
            sprintf(valor_string, "%lf",valor);
            char extrato[1000] ;// (char*)malloc(sizeof(char)*1000);
            strcat(extrato,"Debitado: ");// "Depositado: ";
            strcat(extrato,valor_string);
            strcpy( lista[idEncontrado].extrato[lista[idEncontrado].transacoes] ,extrato);
            lista[idEncontrado].transacoes +=1;
            printf("Saldo atual: %lf \n",lista[idEncontrado].saldo);
            //printf("%lf \n",saldo_cliente);
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
        scanf("%lf", &valor);
        saldo_cliente += valor;
        lista[idEncontrado].saldo = saldo_cliente;
        char valor_string[50] ;
        sprintf(valor_string, "%lf",valor);
        char extrato[1000] ;// (char*)malloc(sizeof(char)*1000);
        strcat(extrato,"Depositado: ");// "Depositado: ";
        strcat(extrato,valor_string);
        strcpy( lista[idEncontrado].extrato[lista[idEncontrado].transacoes] ,extrato);
        lista[idEncontrado].transacoes +=1;
        printf("Saldo atual: %lf \n",lista[idEncontrado].saldo);
        printf("%lf \n",saldo_cliente);
    }
    if(encontrado ==0){
        printf("Cliente com cpf %s não encontrado.\n", cpf);
    }
}


void extrato(struct Cliente *lista, int Quantidade_De_Clientes) {
    int  senha;
    char cpf[15];
    printf("Extrato! \n");
    printf("Digite o CPF: \n");
    scanf("%s", &cpf);
    int idEncontrado;
    int encontrado =0;
    for(int x = 0 ; x < Quantidade_De_Clientes;x++){
        if(strcmp(cpf,lista[x].cpf)==0){

            idEncontrado =x;
            encontrado =1;
            //printf("encontrado id: %d!\n",x);
            break;
        }
    }
    if(encontrado ==1){
        printf("Digite sua senha: \n");
        int senhaConta = lista[idEncontrado].senha;
        printf("%d\n",lista[idEncontrado].senha);
        scanf("%d", &senha);
        if(senha == senhaConta){
            int transferencias = lista[idEncontrado].transacoes;
            for(int x = 0 ; x< transferencias;x++){
                printf("%s\n",lista[idEncontrado].extrato[x]);
            }
        }
        else{
            printf("Senha incorreta!\n");
        }
    }
    if(encontrado ==0){
        printf("Cliente com cpf %s não encontrado.\n", cpf);
    }
}

void transferencia(Cliente *lista, int Quantidade_De_Clientes) {
    int  senha;
    char cpf[15];
    printf("Transferencia! \n");
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
            char cpf_Destino[15];
            printf("Digite o CPF da conta do Destino:\n");
            scanf("%s",&cpf_Destino);
            int idEncontrado_Destino;
            int encontrado_Destino =0;
            for(int x = 0 ; x < Quantidade_De_Clientes;x++){
                if(strcmp(cpf_Destino,lista[x].cpf)==0){

                    idEncontrado_Destino =x;
                    encontrado_Destino =1;
                    printf("encontrado id: %d!\n",x);
                    break;
                }
            }
            if(encontrado_Destino == 1){
                double valor;
                printf("Destino encontrado: %s",cpf_Destino);
                printf("Digite o valor a ser tranferido\n");
                scanf("%lf",&valor);
                lista[idEncontrado].saldo -=valor;
                lista[idEncontrado_Destino].saldo += valor;
                char valor_string[50] ;
                sprintf(valor_string, "%lf",valor);
                char extrato[1000] ;// (char*)malloc(sizeof(char)*1000);
                strcat(extrato,"Transferido: ");
                strcat(extrato,valor_string);
                strcat(extrato," da conta: ");
                strcat(extrato,lista[idEncontrado].cpf);
                strcat(extrato," para a conta: ");
                strcat(extrato,lista[idEncontrado_Destino].cpf);
                strcpy( lista[idEncontrado].extrato[lista[idEncontrado].transacoes] ,extrato);
                strcpy( lista[idEncontrado_Destino].extrato[lista[idEncontrado_Destino].transacoes] ,extrato);
                lista[idEncontrado].transacoes +=1;
                lista[idEncontrado_Destino].transacoes +=1;
            }
            else{
                printf("CPF do destino não encontrado!\n");
            }
        }
        else{
            printf("Senha incorreta!\n");
        }
    }
    if(encontrado ==0){
        printf("Cliente com cpf %s não encontrado.\n", cpf);
    }
};