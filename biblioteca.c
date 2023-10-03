//
// Created by unifgmorassi on 28/09/2023.
//

#include "biblioteca.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

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
        long long int senha_cliente = lista[idEncontrado].senha;
        scanf("%lld", &senha);
        if (senha_cliente == senha) {
            printf("Deletando!\n");
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
    else{
        printf("Senha incorreta!\n");
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
        double taxa;
        int tipo = lista[idEncontrado].tipo;
        if(tipo == 1){
            taxa = 1.05;
        }
        else if(tipo == 2){
            taxa = 1.03;
        }
        else{
            taxa = 1.05;
        }
        int senhaConta = lista[idEncontrado].senha;
        printf("%d\n",lista[idEncontrado].senha);
        scanf("%d", &senha);
        if(senha == senhaConta){
            double valor;
            printf("Valor do débito:\n ");
            scanf("%lf", &valor);
            //double saldo_cliente = lista[idEncontrado].saldo-valor;
            //lista[idEncontrado].saldo = saldo_cliente;
            lista[idEncontrado].saldo -= valor*taxa;
            char valor_string[50] ;
            char valor_taxa_string[50] ;
            char valor_com_taxa[50];
            sprintf(valor_string, "%.2lf",valor);
            sprintf(valor_taxa_string, "%.2lf",valor *taxa-valor);
            sprintf(valor_com_taxa, "%.2lf",valor*taxa);
            char extrato[1000] ;// (char*)malloc(sizeof(char)*1000);
            strcat(extrato,"Debitado: ");// "Depositado: ";
            strcat(extrato,valor_string);
            strcat(extrato," com o valor de taxa de : ");
            strcat(extrato,valor_taxa_string);
            strcat(extrato, " Total debitado: ");
            strcat(extrato,valor_com_taxa);
            time_t t;
            struct tm *data_hora;
            char data_string[50];
            // Obtém o tempo atual
            t = time(NULL);
            data_hora = localtime(&t);
            sprintf(data_string," Data: %02d/%02d/%04d Hora: %02d:%02d:%02d ", data_hora->tm_mday, data_hora->tm_mon + 1, data_hora->tm_year + 1900,data_hora->tm_hour, data_hora->tm_min, data_hora->tm_sec);
            strcat(extrato,data_string);
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
        sprintf(valor_string, "%.2lf",valor);
        char extrato[1000] ;// (char*)malloc(sizeof(char)*1000);
        strcat(extrato,"Depositado: ");// "Depositado: ";
        strcat(extrato,valor_string);
        time_t t;
        struct tm *data_hora;
        char data_string[50];
        // Obtém o tempo atual
        t = time(NULL);
        data_hora = localtime(&t);
        sprintf(data_string," Data: %02d/%02d/%04d Hora: %02d:%02d:%02d ", data_hora->tm_mday, data_hora->tm_mon + 1, data_hora->tm_year + 1900,data_hora->tm_hour, data_hora->tm_min, data_hora->tm_sec);
        strcat(extrato,data_string);
        strcpy( lista[idEncontrado].extrato[lista[idEncontrado].transacoes] ,extrato);
        lista[idEncontrado].transacoes +=1;
        printf("Saldo atual: %lf \n",lista[idEncontrado].saldo);
        printf("%.2lf \n",saldo_cliente);
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
            while(1) {
                int escolha = 0;
                printf("Seja bem vindo ao seu extrato!\n");
                printf("Digite o que deseja fazer(Digite o numero da operação)\n");
                printf("1.Ver saldo\n");
                printf("2.Ver histórico de transferencia\n");
                printf("3.Sair do extrato!\n");
                scanf("%d", &escolha);
                if (escolha == 2) {
                    int transferencias = lista[idEncontrado].transacoes;
                    for (int x = 0; x < transferencias; x++) {
                        printf("%s\n", lista[idEncontrado].extrato[x]);
                    }
                } else if (escolha == 1) {
                    double saldo_cliente = lista[idEncontrado].saldo;
                    printf("Seu saldo é:\n");
                    printf("S: %.2lf\n", saldo_cliente);
                }
                else if(escolha == 3){
                    break;
                }
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
        int tipo = lista[idEncontrado].tipo;
        double taxa;
        scanf("%d", &senha);
        if(tipo == 1){
            taxa = 1.05;
        }
        else if(tipo == 2){
            taxa = 1.03;
        }
        else{
            taxa = 1.05;
        }
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
                printf("Destino encontrado: %s \n",cpf_Destino);
                printf("Digite o valor a ser tranferido\n");
                scanf("%lf",&valor);
                lista[idEncontrado].saldo -=valor * taxa;
                lista[idEncontrado_Destino].saldo += valor;
                char valor_string[50] ;
                char valor_taxa_string[50] ;
                char valor_com_taxa[50];
                sprintf(valor_taxa_string, "%.2lf",valor *taxa-valor);
                sprintf(valor_com_taxa, "%.2lf",valor*taxa);
                sprintf(valor_string, "%.2lf",valor);
                char extrato_origem[1000] ;
                char extrato_destino[1000] ;

                strcat(extrato_origem,"Transferido: ");
                strcat(extrato_origem,valor_string);
                strcat(extrato_origem," da conta: ");
                strcat(extrato_origem,lista[idEncontrado].cpf);
                strcat(extrato_origem," para a conta: ");
                strcat(extrato_origem,lista[idEncontrado_Destino].cpf);
                strcat(extrato_origem," com taxa de: ");
                strcat(extrato_origem,valor_taxa_string);
                strcat(extrato_origem, " Total subtraido do operante: ");
                strcat(extrato_origem, valor_com_taxa);
                strcpy(extrato_destino,extrato_origem);
                time_t t;
                struct tm *data_hora;
                char data_string[50];
                // Obtém o tempo atual
                t = time(NULL);
                data_hora = localtime(&t);
                sprintf(data_string," Data: %02d/%02d/%04d Hora: %02d:%02d:%02d ", data_hora->tm_mday, data_hora->tm_mon + 1, data_hora->tm_year + 1900,data_hora->tm_hour, data_hora->tm_min, data_hora->tm_sec);
                strcat(extrato_origem,data_string);

                strcpy( lista[idEncontrado].extrato[lista[idEncontrado].transacoes] ,extrato_origem);

                strcat(extrato_destino, " Valor do destinatário recebido: ");
                strcat(extrato_destino,valor_string);
                strcat(extrato_destino,data_string);

                strcpy( lista[idEncontrado_Destino].extrato[lista[idEncontrado_Destino].transacoes] ,extrato_destino);
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