//
// Created by unifgmorassi on 18/10/2023.
//

#include "biblioteca.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
void limpa(){
    //função para arrumar o bug de pular um scanf
    //ela vai limpar o buffer e arrumar o erro
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}
void ler_clientes(struct Cliente lista[], int *Quantidade_De_Clientes) {
    FILE *arquivo = fopen("BancoDeDadosClientes", "rb");
    if (arquivo) {
        fseek(arquivo, 0, SEEK_END);
        long tamanho_arquivo = ftell(arquivo);
        rewind(arquivo);
        *Quantidade_De_Clientes = tamanho_arquivo / sizeof(struct Cliente);
        fread(lista, sizeof(struct Cliente), *Quantidade_De_Clientes, arquivo);
        fclose(arquivo);
    }
}

/*void ler_clientes(struct Cliente lista[], int *Quantidade_De_Clientes) {
        FILE *arquivo = fopen("BancoDeDadosClientes", "rb");//ele abre o arquivo como ler binario
        if (arquivo) {//se obter sucesso ele vai ler com o fread e armazenara no arquivo aberto
            //as informaçoes ficarão na lista q foi passada como parametro
            while (fread(&lista[*Quantidade_De_Clientes], sizeof(struct Cliente), 1, arquivo) == 1) {
                (*Quantidade_De_Clientes)++;//ele vai ler de 1 em 1 até o fim do arquivo, a cada leitura ele soma 1 na quantidade de clientes
                //para manter o controle de clientes
            }
            fclose(arquivo);//ele fecha o arquivo
        }
    }
*/
void salva_cliente(struct Cliente lista[], int Quantidade_De_Clientes) {
    FILE *arquivo = fopen("BancoDeDadosClientes", "wb");//abre o arquivo como write em binario

    if (arquivo) {//se ele obter sucesso
        //ele escreve tudo da lista de structs no arquivo q foi aberta
        fwrite(lista, sizeof(struct Cliente), Quantidade_De_Clientes, arquivo);
        fclose(arquivo);//fecha o arquivo
    }
}
void NovoCliente(struct Cliente *lista,int *Quantidade_De_Clientes){
    //ele pede o CPF
    printf("Digite seu CPF:\n");
    long long int senha,tipo;
    char cpf[15];
    int encontrado = 0;
    int idEncontrado;
    scanf("%s",cpf);
    limpa();

    //aqui ele vai verificar se ja existe algum cliente com o cpf
    for (int x = 0; x < (*Quantidade_De_Clientes); x++) {

        if (strcmp(cpf,lista[x].cpf)==0) {
            //strcmp vai comparar as 2 string e caso seja 0 quer dizer q são iguais
            // ou seja neste caso como ele vai varrer a lista
            // para encontrar o cliente, caso igual cliente encontrado
            printf("Cliente ja registrado!\n");
            encontrado = 1;
            idEncontrado =x;
            //caso encontrado ele vai salvar o id e a variavel encontrado sera verdadeira
        }
    }
    if (encontrado == 0) {
        //caso nao encontrado ele começa a pedir as informações
        Cliente atual;
        //struct atual que sera preenchida com as informações
        atual.saldo =0;
        //o saldo iniciará com o 0
        atual.transacoes =0;
        //transações é a variavel da struct q
        // vai controlar quantas operções foram feitas
        //e serve para listar o extrato, que na declaração da
        // struct é uma matriz de char onde temos 100 linhas
        // com 1000 colunas q seria cada string q representa o extrato
        strcpy(atual.cpf,cpf);
        //strcpy vai colocar o cpf na struct
        printf("Digite seu nome:\n");
        char nome[100];
        scanf("%100[^\n]s", &nome);
        limpa();
        strcpy(atual.nome, nome);
        //strcpy vai colocar o nome na struct

        printf("Digite sua senha (6 numeros):\n");
        scanf("%d", &senha);
        atual.senha = senha;
        // atualiza na struct a senha
        printf("Digite qual tipo vai ser sua conta?(1.comum ou 2.plus):\n");
        scanf("%d", &tipo);
        atual.tipo = tipo;
        //atualiza na struct o tipo ;
        lista[(*Quantidade_De_Clientes)] = atual;
        //ele vai na lista de cliente e vai colocar na posição atual
        // que é a quantidade de clientes, se for 0, ele vai no indice 0
        // e atualiza a array de struct cliente para o cliente q acabamos de
        // declarar
        (*Quantidade_De_Clientes)++;
        //atualiza a quantidade de clientes global com +1
    }
    else {
        //caso o cliente ja foi encontrado e queira alterar a senha
        Cliente C_encontrado = lista[idEncontrado];
        //ele vai colocar a informação do cliente encontrado da posição onde ele está na lista
        //e vai armazenar na variavel C_encontrado
        int trocar;
        //variavel booleana q vai checar a escolha do cliente
        printf("Voce deseja alterar a senha?(1.sim 2.nao)\n");
        scanf("%d",&trocar);
        if(trocar ==1){
            //caso seja 1 ele quer trocar
            int nova_senha;
            printf("Digite a nova senha:\n");
            scanf("%d",&nova_senha);
            //ele pede a nova senha e atualiza no C_encontrado
            C_encontrado.senha = nova_senha;

            lista[idEncontrado] = C_encontrado;
            //agora na lista na posição do cliente encontrado, ele vai atualizar e
            // colocar o cliente com a nova senha na mesma posição
        }
    }
    printf("\n");
}
void ListarClientes(struct Cliente* lista, int Quantidade_De_Clientes){
    //para listar a função vai receber a lista e a quantidade de clientes
    printf("Quantidade de Clientes atuais: %d\n",Quantidade_De_Clientes);
    //agora no for ele vai varrer a lista da posição 0 até a posição da quantidade de clientes
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
            //strcmp vai comparar as 2 string e caso seja 0 quer dizer q são iguais
            // ou seja neste caso como ele vai varrer a lista
            // para encontrar o cliente, caso igual cliente encontrado
            encontrado = 1;
            //variavel booleana para caso encontrado ou n , (caso n ela mantem em 0)

            idEncontrado = x;
            //variavel para salvar a posição na lista
            break;
            //ele da um break no for para caso seja encontrado
        }
    }
    if(encontrado ==1){
        //caso o cliente seja encontrado ele vai digitar a senha
        printf("Digite sua senha: \n");
        double taxa;
        int tipo = lista[idEncontrado].tipo;
        double limite = -1000;
        //estas variaveis (tipo e limite) tem como objetivo saber o limite da conta de cada pessoa pelo tipo
        //ela sera atualizada nestes ifs para cada tipo de conta
        if(tipo == 1){
            taxa = 1.05;
            limite = -1000;

        }
        else if(tipo == 2){
            limite = -5000;
            taxa = 1.03;
        }
        else{
            taxa = 1.05;
            limite = -1000;

        }
        int senhaConta = lista[idEncontrado].senha;
        scanf("%d", &senha);
        //ele vai pedir agora a senha, e vai comparar com a salva
        if(senha == senhaConta){
            double valor;
            printf("Valor do débito:\n ");
            scanf("%lf", &valor);
            //ele vai pegar o valor q foi digitado para saber o quanto q vai ser subtraido do saldo
            //dependendo do tipo da conta será diferente
            double limite = -1000;

            if(lista[idEncontrado].saldo - valor*taxa >=limite) {
                //nesta verificação ele vai ver se o valor do saldo atual menos o valor q ele quer
                //debitar com a taxa, vai ser maior q o limite, caso sim ele executará estes comandos
                lista[idEncontrado].saldo -= valor * taxa;
                //nesta linha ele atualiza o valor do saldo com a taxa aplicada
                char valor_string[50];
                char valor_taxa_string[50];
                char valor_com_taxa[50];
                //aqui são as variaveis do valor em string(array de char) para escrever o extrato
                sprintf(valor_string, "%.2lf", valor);
                sprintf(valor_taxa_string, "%.2lf", valor * taxa - valor);
                sprintf(valor_com_taxa, "%.2lf", valor * taxa);
                //sprintf tem a função de transformar o double da variavel valor e taxa em string
                char extrato[1000];
                //esta variavel será onde vai ser armazenadoa o extrato;
                strcat(extrato, "Debitado: ");// "Depositado: ";
                strcat(extrato, valor_string);
                strcat(extrato, " com o valor de taxa de : ");
                strcat(extrato, valor_taxa_string);
                strcat(extrato, " Total debitado: ");
                strcat(extrato, valor_com_taxa);
                //o strcat vai concatenar as string da forma que eu quero
                time_t t;
                // este time_t é uma struct da biblioteca time.h
                //q vai armazenar o momento q ocorreu a operação
                struct tm *data_hora;
                char data_string[50];
                // Obtém o tempo atual
                t = time(NULL);
                //esta função time retorna a struct com os valores do momento atual
                //para a variavel t q sera utilizada como feito anteriormente com o
                //sprintf e strcat para salvar o extrato com a data tambem
                data_hora = localtime(&t);
                sprintf(data_string, " Data: %02d/%02d/%04d Hora: %02d:%02d:%02d ", data_hora->tm_mday,
                        data_hora->tm_mon + 1, data_hora->tm_year + 1900, data_hora->tm_hour, data_hora->tm_min,
                        data_hora->tm_sec);
                strcat(extrato, data_string);
                strcpy(lista[idEncontrado].extrato[lista[idEncontrado].transacoes%100], extrato);
                //nesta linha ele vai na posição da quantidade de transações q ele fez e vai salvar a variavel extrato
                // na struct com o strcpy
                lista[idEncontrado].transacoes += 1;
                //depois de salvar na struct ele vai atualizar a quantidade de transações feitas somando +1 na variavel
                //transações do struct cliente
                printf("Saldo atual: %lf \n", lista[idEncontrado].saldo);
                //aqui ele vai mostrar o saldo depois da alteração

            }
            else{
                //caso ele n tenha o valor necessário ele avisará com o print e n realizará a operação
                printf("Saldo insuficiente para o debito! \n");
            }
        }
        else{
            //casos ele erre a senha:
            printf("Senha incorreta!\n");
        }
    }
    if(encontrado ==0){
        //caso n tenha nenhum cliente com o cpf digitado
        printf("Cliente com cpf %s não encontrado.\n", cpf);
    }
}
void ApagaCliente(struct Cliente* lista, int* Quantidade_De_Clientes){
    //função para apagar o cliente
    printf("Digite seu CPF:\n");
    //ele vai pedir o cpf
    char cpf[15];
    //o cpf é um string(array de char)
    int encontrado = 0;
    int idEncontrado;
    int deletar = 0;
    scanf("%s", &cpf);
    //ele vai digitar e vai salvar no CPF
    for (int x = 0; x < (*Quantidade_De_Clientes); x++) {
        if (strcmp(lista[x].cpf, cpf) == 0) {
            //strcmp vai comparar as 2 string e caso seja 0 quer dizer q são iguais
            // ou seja neste caso como ele vai varrer a lista
            // para encontrar o cliente, caso igual cliente encontrado
            encontrado = 1;
            //variavel booleana para caso encontrado ou n , (caso n ela mantem em 0)

            idEncontrado = x;
            //variavel para salvar a posição na lista
        }
    }
    if (encontrado == 1) {
        //caso encontrado ele vai pedir a senha para verificar
        printf("Digite sua senha: \n");
        long long int senha;
        long long int senha_cliente = lista[idEncontrado].senha;
        scanf("%lld", &senha);
        if (senha_cliente == senha) {
            //caso a senha digitada seja igual a senha salva na lista
            printf("Deletando!\n");

            deletar = 1;
            //variavel para saber caso ele queira deletar vai ser ativada
            //caso seja verdadeiro o if
        }
    }
    if (deletar == 1) {
        //ao deletar ele vai percorrer a lista tendo como inicio
        //a posição encontrada.
        // ele vai pegar o cliente da posição da frente e vai atualizar para a anterior
        for (int x = idEncontrado; x < (*Quantidade_De_Clientes); x++) {
            lista[x] = lista[x + 1];
        }
        //depois de atualizar todos os indices da lista ele vai subtrair 1 da quantidade de clientes;
        (*Quantidade_De_Clientes) -= 1;
        printf("Cliente deletado com sucesso!\n");
    }
    else{
        printf("Senha incorreta!\n");
    }
}



void deposito(struct Cliente *lista, int Quantidade_De_Clientes) {

    //para o deposito será solicitado apenas o cpf e o valor a ser depoisitado
    char cpf[15];
    printf("Digite o CPF: \n");
    scanf("%s", &cpf);
    int idEncontrado;
    int encontrado =0;
    for(int x = 0 ; x < Quantidade_De_Clientes;x++){
        if(strcmp(cpf,lista[x].cpf)==0){
            //strcmp vai comparar as 2 string e caso seja 0 quer dizer q são iguais
            // ou seja neste caso como ele vai varrer a lista
            // para encontrar o cliente, caso igual cliente encontrado
            encontrado = 1;
            //variavel booleana para caso encontrado ou n , (caso n ela mantem em 0)

            idEncontrado = x;
            //variavel para salvar a posição na lista
            break;
            //ele da um break no for para caso seja encontrado
        }
    }
    if(encontrado ==1){
        //caso seja encontrado o CPF na lista
        double valor;
        double saldo_cliente = lista[idEncontrado].saldo;
        printf("Valor do deposito:\n ");
        scanf("%lf", &valor);
        //ele vai pedir o Valor a ser depositado
        saldo_cliente += valor;
        //ele vai atualizar o saldo_cliente somando o valor digitado
        lista[idEncontrado].saldo = saldo_cliente;
        //apartir daqui será feito o salvamento da operação no extrato
        char valor_string[50] ;
        sprintf(valor_string, "%.2lf",valor);
        //tranforma o valor em string na variavel valor_string
        char extrato[1000] ;
        strcat(extrato,"Depositado: ");
        strcat(extrato,valor_string);
        //ele vai concatenar na extrato o texto desejado
        time_t t;
        struct tm *data_hora;
        char data_string[50];
        // Obtém o tempo atual
        t = time(NULL);
        data_hora = localtime(&t);
        sprintf(data_string," Data: %02d/%02d/%04d Hora: %02d:%02d:%02d ", data_hora->tm_mday, data_hora->tm_mon + 1, data_hora->tm_year + 1900,data_hora->tm_hour, data_hora->tm_min, data_hora->tm_sec);
        strcat(extrato,data_string);
        strcpy( lista[idEncontrado].extrato[lista[idEncontrado].transacoes%100] ,extrato);
        //salva o extrato na posição do idencontrado no extrato na matriz da posição da
        //quantidade de trasaçõeso
        lista[idEncontrado].transacoes +=1;
        //atualiza a quantidade de transações com +1
        printf("Saldo atual: %lf \n",lista[idEncontrado].saldo);
        //printa o saldo do cliente após a operação
    }
    if(encontrado ==0){
        //caso o cpf n seja encontrado ele vai printar:
        printf("Cliente com cpf %s não encontrado.\n", cpf);
    }
}
void transferencia(Cliente *lista, int Quantidade_De_Clientes) {
    //para a transferencia, será solicitado CPF do operante, senha do operante, cpf do destinatário
    //e o valor da transferencia
    int  senha;
    char cpf[15];
    printf("Transferencia! \n");
    printf("Digite o CPF: \n");
    scanf("%s", &cpf);
    int idEncontrado;
    int encontrado =0;
    for(int x = 0 ; x < Quantidade_De_Clientes;x++){
        if(strcmp(cpf,lista[x].cpf)==0){
            //strcmp vai comparar as 2 string e caso seja 0 quer dizer q são iguais
            // ou seja neste caso como ele vai varrer a lista
            // para encontrar o cliente, caso igual cliente encontrado
            encontrado = 1;
            //variavel booleana para caso encontrado ou n , (caso n ela mantem em 0)

            idEncontrado = x;
            //variavel para salvar a posição na lista
            break;
            //ele da um break no for para caso seja encontrado
        }
    }
    if(encontrado ==1){
        //caso o cliente operante seja encontrado ele vai ser solicitado para
        //escrever sua senha
        printf("Digite sua senha: \n");
        int senhaConta = lista[idEncontrado].senha;
        int tipo = lista[idEncontrado].tipo;
        double taxa;
        scanf("%d", &senha);
        double limite = -1000;
        //aqui ele atualizará as variaveis q são responsaveis para aplicar a taxa e verificação
        //do saldo com o limite
        if(tipo == 1){
            taxa = 1.05;
            limite = -1000;

        }
        else if(tipo == 2){
            limite = -5000;
            taxa = 1.03;
        }
        else{
            taxa = 1.05;
            limite = -1000;

        }
        if(senha == senhaConta){
            //se a senha for correta ele vai pedir o cpf do destinatário
            char cpf_Destino[15];
            printf("Digite o CPF da conta do Destino:\n");
            scanf("%s",&cpf_Destino);
            int idEncontrado_Destino;
            int encontrado_Destino =0;
            for(int x = 0 ; x < Quantidade_De_Clientes;x++){
                if(strcmp(cpf_Destino,lista[x].cpf)==0){
                    //strcmp vai comparar as 2 string e caso seja 0 quer dizer q são iguais
                    // ou seja neste caso como ele vai varrer a lista
                    // para encontrar o cliente, caso igual cliente encontrado
                    idEncontrado_Destino =x;
                    //variavel booleana para caso encontrado ou n , (caso n ela mantem em 0)
                    encontrado_Destino =1;
                    //variavel para salvar a posição na lista
                    break;
                    //ele da um break no for para caso seja encontrado
                }
            }
            if(encontrado_Destino == 1){
                //se o destino for encontrado ele vai pedir agora o valor da tranferencia
                double valor;
                printf("Destino encontrado: %s \n",cpf_Destino);
                printf("Digite o valor a ser tranferido\n");
                scanf("%lf",&valor);
                // apos digitar o valor sera debitado da conta
                if(lista[idEncontrado].saldo - valor*taxa >=limite) {
                    //ele vai verificar se o saldo menos o valor com a taxa vai ser maior q o
                    // limite
                    lista[idEncontrado].saldo -= valor * taxa;
                    //subtrai do operando com a taxa
                    lista[idEncontrado_Destino].saldo += valor;
                    printf("Transferencia no valor de %lf realizada com sucesso!\n\n\n",valor);
                    // soma a o destino o valor por inteiro sem taxa
                    char valor_string[50];
                    char valor_taxa_string[50];
                    char valor_com_taxa[50];
                    sprintf(valor_taxa_string, "%.2lf", valor * taxa - valor);
                    sprintf(valor_com_taxa, "%.2lf", valor * taxa);
                    sprintf(valor_string, "%.2lf", valor);
                    //nestas linhas acima está sendo feita a parte do extrato
                    //transformando os valores para string
                    char extrato_origem[1000];
                    //variavel da mensagem do extrato q vai ser salva no cliente que originou a operação
                    char extrato_destino[1000];
                    //variavel da mensagem do extrato q vai ser salva no cliente destino da operação


                    strcat(extrato_origem, "Transferido: ");
                    strcat(extrato_origem, valor_string);
                    strcat(extrato_origem, " da conta: ");
                    strcat(extrato_origem, lista[idEncontrado].cpf);
                    strcat(extrato_origem, " para a conta: ");
                    strcat(extrato_origem, lista[idEncontrado_Destino].cpf);
                    strcat(extrato_origem, " com taxa de: ");
                    strcat(extrato_origem, valor_taxa_string);
                    strcat(extrato_origem, " Total subtraido do operante: ");
                    strcat(extrato_origem, valor_com_taxa);
                    //na linha de baixo ele vai salvar no destino a mesma mensagem até aqui
                    //ou seja igual até aqui para os 2 clientes
                    strcpy(extrato_destino, extrato_origem);
                    // nas linhas a cima ocorre a concatenação na variavel extrato_origem
                    time_t t;
                    struct tm *data_hora;
                    char data_string[50];
                    // Obtém o tempo atual
                    t = time(NULL);
                    data_hora = localtime(&t);
                    sprintf(data_string, " Data: %02d/%02d/%04d Hora: %02d:%02d:%02d ", data_hora->tm_mday,
                            data_hora->tm_mon + 1, data_hora->tm_year + 1900, data_hora->tm_hour, data_hora->tm_min,
                            data_hora->tm_sec);
                    strcat(extrato_origem, data_string);
                    //nas linhas de cima ele salva o momento da operação na msg de extrato do operando
                    strcpy(lista[idEncontrado].extrato[lista[idEncontrado].transacoes%100], extrato_origem);
                    //aqui ele salva a mensagem na conta do cliente na lista da posição do id encontrado
                    // e na matriz de extrato ele salva na posição da transações do cliente de origem

                    //para o extrato do destino antes de colocar a data ele recebe mais informações
                    //exatamente o valor q ele recebeu
                    strcat(extrato_destino, " Valor do destinatário recebido: ");
                    strcat(extrato_destino, valor_string);
                    //apenas depois ele salva a data
                    strcat(extrato_destino, data_string);

                    strcpy(lista[idEncontrado_Destino].extrato[lista[idEncontrado_Destino].transacoes%100],
                           extrato_destino);
                    //aqui ele salva a mensagem na conta do cliente na lista da posição do id encontrado do destino
                    // e na matriz de extrato ele salva na posição da transações do cliente do destino



                    lista[idEncontrado].transacoes += 1;
                    lista[idEncontrado_Destino].transacoes += 1;
                    //nestas 2 linhas o código atualiza a quantidade de transações feitas para o gerenciamento do extrato
                    //soma +1 nas 2 conta, cliente origem e destino

                }
                    // o valor da tranferencia e realizado se os requesitos acima forem corretos
                else{
                    printf("Valor insuficiente para a transferencia! \n");
                }
            }
                //caso o valor nao for suficiete essa mensagem aparece
            else{
                printf("CPF do destino não encontrado!\n");
            }
        }
            //caso a senha n seja compativel mesagem de erro:
        else{
            printf("Senha incorreta!\n");
        }
    }
    //caso o cpf n seja encontrado :
    if(encontrado ==0){
        printf("Cliente com cpf %s não encontrado.\n", cpf);
    }
};



void extrato(struct Cliente *lista, int Quantidade_De_Clientes) {
    // agora para o extrato como nas outras funções será solicitado o cpf e senha
    int  senha;
    char cpf[15];
    printf("Extrato! \n");
    printf("Digite o CPF: \n");
    scanf("%s", &cpf);
    int idEncontrado;
    int encontrado =0;
    for(int x = 0 ; x < Quantidade_De_Clientes;x++){
        if(strcmp(cpf,lista[x].cpf)==0){
            //strcmp vai comparar as 2 string e caso seja 0 quer dizer q são iguais
            // ou seja neste caso como ele vai varrer a lista
            // para encontrar o cliente, caso igual cliente encontrado
            encontrado = 1;
            //variavel booleana para caso encontrado ou n , (caso n ela mantem em 0)

            idEncontrado = x;
            //variavel para salvar a posição na lista
            break;
            //ele da um break no for para caso seja encontrado
        }
    }
    if(encontrado ==1){
        //casos encontrado ai sim sera solicitado a senha
        printf("Digite sua senha: \n");
        int senhaConta = lista[idEncontrado].senha;
        scanf("%d", &senha);
        if(senha == senhaConta){
            //caso a senha seja correta
            while(1) {
                //abrirá um menu com o while true para q ele possa escolher
                //ver o saldo, o extrato ou sair para o menu principal
                int escolha = 0;
                printf("Seja bem vindo ao seu extrato!\n");
                printf("Digite o que deseja fazer(Digite o numero da operação)\n");
                printf("1.Ver saldo\n");
                printf("2.Ver histórico de transferencia\n");
                printf("3.Sair do extrato!\n");
                scanf("%d", &escolha);
                if (escolha == 2) {
                    //caso ele queira ver o histórico de transferencia
                    // ele vai pegar a quantidade de transações q ele fez
                    // e armazenara na variavel transferencisa
                    int transferencias = lista[idEncontrado].transacoes;
                    for (int x = 0; x < transferencias; x++) {
                        //neste for ele vai pegar na matriz extrato da struct cliente na posição do
                        //cliente q foi armazenada no idEncontrado e vai varrer a quantidade de transações
                        //feitas
                        printf("%s\n", lista[idEncontrado].extrato[x]);
                    }
                } else if (escolha == 1) {
                    //caso 1 ele vai apenas printar o saldo
                    double saldo_cliente = lista[idEncontrado].saldo;
                    printf("Seu saldo é:\n");
                    printf("S: %.2lf\n", saldo_cliente);
                }
                else if(escolha == 3){
                    //caso 3 ele vai apenas dar um break no while true assim terminando a
                    // a tarefa extrato
                    break;
                }
            }
        }
        else{
            //caso a senha digitada n seja igual a salva na lista
            printf("Senha incorreta!\n");
        }
    }
    if(encontrado ==0){
        //se o cpf digitado n for encontrado na lista de clientes
        printf("Cliente com cpf %s não encontrado.\n", cpf);
    }
}

