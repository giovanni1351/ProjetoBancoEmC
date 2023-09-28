#include <stdio.h>
#include "biblioteca.h"

int main() {
    struct Cliente *lista=malloc(sizeof(struct Cliente)*1000);
    int Quantidade_De_Clientes = 0;
    ler_clientes(lista,&Quantidade_De_Clientes);
    printf("porra");
    while (1) {
        int opcao = 0, ver = 0;

        printf("Seja Bem vindo ao banco!!!\n");
        printf("Opcoes a baixo:\n");
        printf("1.Novo cliente!\n");
        printf("2.Apaga cliente!\n");
        printf("3.Listar todos os clientes!\n");
        printf("4.Débito!\n");
        printf("5.Depositar!\n");
        printf("6.Extrato!\n");
        printf("7.Transferencia\n");
        printf("8.Sair!\n");
        printf("Opcao: ");
        if (scanf("%d", &opcao) != 1) {
            // Tratar erro de entrada inválida, por exemplo:
            printf("Opção inválida. Por favor, insira um número.\n");
            // Limpar o buffer de entrada se necessário
            while (getchar() != '\n');
        }
        switch (opcao) {
            case 1:
                NovoCliente();
                break;
            case 2:
                ApagaCliente();
                break;
            case 3:
                ListarClientes();
                break;
            case 4:
                debito();
                break;
            case 5:
                deposito();
                break;
            case 6:
                extrato();
                break;
            case 7:
                transferencia();
                break;
            case 8:
                ver = 1;
                break;
        }
        if (ver == 1) {
            break;
        }
    }


    return 0;
}