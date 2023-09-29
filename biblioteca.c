//
// Created by unifgmorassi on 28/09/2023.
//

#include "biblioteca.h"
#include <stdlib.h>
#include <stdio.h>
void ler_clientes(struct Cliente lista[], int *Quantidade_De_Clientes) {
    FILE *arquivo = fopen("tarefas", "rb");//ele abre o arquivo como ler binario
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
    FILE *arquivo = fopen("tarefas", "wb");//abre o arquivo como write em binario

    if (arquivo) {//se ele obter sucesso
        //ele escreve tudo da lista de structs no arquivo q foi aberta
        fwrite(lista, sizeof(struct Cliente), Quantidade_De_Clientes, arquivo);
        fclose(arquivo);//fecha o arquivo
    }
}
void NovoCliente(struct Cliente *lista,int *Quantidade_De_Clientes){
    printf("Digite seu CPF\n");
    long long int cpf;
    int encontrado = 0;
    scanf("%d", &cpf);
    for (int x = 0; x < (*Quantidade_De_Clientes); x++) {
        if (lista[x].cpf == cpf) {
            printf("Cliente ja registrado!\n");
            encontrado = 1;
        }
    }
    if (encontrado == 0) {
        lista[(*Quantidade_De_Clientes)].cpf = cpf;
        printf("Digite seu nome:\n");
        char nome[100];
        scanf("%s", &nome);
        strcpy(lista[(*Quantidade_De_Clientes)].nome, nome);

        printf("Digite sua senha:\n");
        scanf("%d", &lista[(*Quantidade_De_Clientes)].senha);
        printf("Digite qual tipo vai ser sua conta?(1.comum ou 2.plus):\n");
        scanf("%d", &lista[(*Quantidade_De_Clientes)].tipo);
        (*Quantidade_De_Clientes)++;
    }
    else {

    }
    printf("\n");
}
void ApagaCliente(){
    printf("funciona\n");

}
void ListarClientes(struct Cliente* lista, int Quantidade_De_Clientes){

    printf("Quantidade de Clientes atuais: %d\n",Quantidade_De_Clientes);

}
void debito(){
    printf("topp\n");

}
void deposito(){
    printf("muito money\n");

}
void extrato(){
    printf("quanto tem\n");

}
void transferencia(){
    printf("vamos la\n");
};