#include <stdio.h> 
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
//VARIAVEIS GLOBAIS

char senAcesso[12];
char senha[12];


void passarSenha(const char* senAcesso){
    strcpy(senha, senAcesso);
}

char senA;

// FUNÇÃO MENU

void menu(){
    printf("***********************************************************************\n");
    printf("1 - Consultar saldo\n");
    printf("2 - Consultar extrato\n");
    printf("3 - Depositar\n");
    printf("4 - Sacar\n");
    printf("5 - Comprar criptomoedas\n");
    printf("6 - Vender criptomoedas\n");
    printf("7 - Atualizar cotacao\n");
    printf("8 - Sair\n");
}

// ----------------------------------------------------------------------------------------
// FUNÇÃO SALDO

typedef struct{
    float real;
    float bitcoin;
    float ethereum;
    float ripple;
} Saldos;

Saldos carteira = {0,0,0,0};

void um(){
    printf("***********************************************************************\n");
    printf("Voce tem essa quantidade de Reais em sua carteira: R$%.2f\n", carteira.real);
    printf("Voce tem essa quantidade de Bitcoin em sua carteira: %.4f\n", carteira.bitcoin);
    printf("Voce tem essa quantidade de Ethereum em sua carteira: %.4f\n", carteira.ethereum);
    printf("Voce tem essa quantidade de Ripple em sua carteira: %.4f\n", carteira.ripple);
}

// ----------------------------------------------------------------------------------------
// DEPOSITAR

void tres(){
    float deposito;

    printf("***********************************************************************\n");
    printf("Insira o quanto deseja depositar: ");
    scanf("%f", &deposito);

    carteira.real += deposito;
    
    printf("Valor depositado R$ %.2f\n ", deposito);
    printf("Novo saldo R$ %.2f\n ", carteira.real);

}

// ----------------------------------------------------------------------------------------
// SACAR

void quatro(){
    float saque;

    printf("***********************************************************************\n");
    printf("Insira o quanto deseja sacar: ");
    scanf(" %f", &saque);

    if (saque>carteira.real){
        printf("O valor sacado e maior do que consta em conta\n");
    }
    else{         
        printf("Insira sua SENHA: ");
        scanf(" %11s", senAcesso);
        if (strcmp(senha, senAcesso) == 0){
            carteira.real -= saque;
            printf("Valor sacado R$ %.2f\n ", saque);
            printf("Novo saldo R$ %.2f\n ", carteira.real);
        }
        else{
                printf("Senha invalida\n");
        }
    }
}


// ----------------------------------------------------------------------------------------
// COMPRAR CRIPTOS

typedef struct{
    float v_bit;
    float v_eth;
    float v_rip;
} Criptos;

Criptos valoresC = {334745.55,15093.47,2.65};

float valC;
int opcao;
float taxa;
float totct; 
float criptoC;
char verificar;

void cinco(){
    printf("***********************************************************************\n");
    printf("1 - BITCOIN // Taxa de compra em 2%% \n");
    printf("2 - ETHEREUM // Taxa de compra em 1%%\n");
    printf("3 - RIPPLE // Taxa de compra em 1%%\n");
    printf("Escolha a cripto que deseja comprar: ");
    scanf("%d", &opcao);
    if (opcao ==  1){
        printf("Valor do BITCOIN R$ %.2f\n", valoresC.v_bit);
        printf("Digite o valor que deseja comprar: ");
        scanf("%f", &valC);
        printf("***********************************************************************\n");
        printf("Insira sua SENHA: ");
        scanf("%11s", senAcesso);
        if (strcmp(senha, senAcesso)==0) {
            criptoC =  valC/valoresC.v_bit;
            taxa = valC * 0.02;
            printf("Valor da taxa: R$ %.2f\n", taxa);
            totct = valC + taxa;
            printf("Valor a ser pago pela criptomoeda: R$ %.2f\n", totct);
            printf("***********************************************************************\n");
            printf("Você realmente deseja comprar o BITCOIN? (S/N): ");
            scanf(" %c", &verificar);
            if (toupper(verificar) == 'S'){
                if (totct > carteira.real){
                    printf("Saldo insuficiente!!!\n");
                }
                else{
                    printf("Compra realizada com sucesso!!!\n");
                    carteira.real -= totct;
                    carteira.bitcoin += criptoC;
                    printf("Total de Bitcoins em sua carteira: %.4f\n", carteira.bitcoin);
                }
            }
            else{
                printf("Tudo bem, voltando ao menu...\n");
            }
        }
        else{
            printf("Senha errada\n");    
        }
    }
    else if (opcao == 2){
        printf("Valor do Ethereum R$ %.2f\n", valoresC.v_eth);
        printf("Digite o valor que deseja comprar: ");
        scanf("%f", &valC);
        printf("***********************************************************************\n");
        printf("Insira sua SENHA: ");
        scanf("%11s", senAcesso);
        if (strcmp(senha, senAcesso) == 0){
            criptoC =  valC/valoresC.v_eth;
            taxa = valC * 0.01;
            printf("Valor da taxa: R$ %.2f\n", taxa);
            totct = valC + taxa;
            printf("Valor a ser pago pela criptomoeda: R$ %.2f\n", totct);
            printf("***********************************************************************\n");
            printf("Você realmente deseja comprar o BITCOIN? (S/N): ");
            scanf(" %c", &verificar);
            if (toupper(verificar) == 'S'){
                if (totct > carteira.real){
                    printf("Saldo insuficiente!!!\n");
                }
                else{
                    printf("Compra realizada com sucesso!!!\n");
                    carteira.real -= totct;
                    carteira.ethereum += criptoC;
                    printf("Total de Ethereums em sua carteira: %.4f\n", carteira.ethereum);
                }
            }
            else{
                printf("Tudo bem, voltando ao menu...\n");
            }
        }
        else{
            printf("Senha errada\n");    
        }
       
    }
    else if (opcao == 3){
        printf("Valor do Ripple R$ %.2f\n", valoresC.v_rip);
        printf("Digite o valor que deseja comprar: ");
        scanf("%f", &valC);
        printf("***********************************************************************\n");
        printf("Insira sua SENHA: ");
        scanf("%11s", senAcesso);
        if (strcmp(senha, senAcesso) == 0){
            criptoC =  valC/valoresC.v_rip;
            taxa = valC * 0.01;
            printf("Valor da taxa: R$ %.2f\n", taxa);
            totct = valC + taxa;
            printf("Valor a ser pago pela criptomoeda: R$ %.2f\n", totct);
            printf("***********************************************************************\n");
            printf("Você realmente deseja comprar o BITCOIN? (S/N): ");
            scanf(" %c", &verificar);
            if (toupper(verificar) == 'S'){
                if (totct > carteira.real){
                    printf("Saldo insuficiente!!!\n");
                }
                else{
                    printf("Compra realizada com sucesso!!!\n");
                    carteira.real -= totct;
                    carteira.ripple += criptoC;
                    printf("Total de Ripples em sua carteira: %.4f\n", carteira.ripple);
                }
            }
            else{
                printf("Tudo bem, voltando ao menu...\n");
            }
        }
        else{
            printf("Senha errada\n");    
        }
       
    }
    else{
        printf("Criptomoeda nao encontrada!!!\n");
    }
}
// ----------------------------------------------------------------------------------------
// VENDER CRIPTOS

float qtdC;

void seis(){
    printf("***********************************************************************\n");
    printf("1 - BITCOIN // Taxa de venda em 3%% \n");
    printf("2 - ETHEREUM // Taxa de venda em 2%%\n");
    printf("3 - RIPPLE // Taxa de venda em 1%%\n");
    printf("Escolha a cripto que deseja vender: ");
    scanf("%d", &opcao);
    if (opcao ==  1){
        printf("Valor do BITCOIN R$ %.2f\n", valoresC.v_bit);
        printf("Digite a quantidade que deseja vender: ");
        scanf(" %f", &qtdC);
        printf("***********************************************************************\n");
        printf("Insira sua SENHA: ");
        scanf(" %11s", senAcesso);
        if (strcmp(senha, senAcesso) == 0){
            criptoC =  qtdC*valoresC.v_bit;
            taxa = criptoC * 0.03;
            printf("Valor da taxa: R$ %.2f\n", taxa);
            totct = criptoC - taxa;
            printf("Valor a ser recebido pela criptomoeda: R$ %.2f\n", totct);
            printf("***********************************************************************\n");
            printf("Você realmente deseja vender o BITCOIN? (S/N): ");
            scanf(" %c", &verificar);
            if (toupper(verificar) == 'S'){
                if (qtdC > carteira.bitcoin){
                    printf("Saldo insuficiente!!!\n");
                }
                else{
                    printf("Compra realizada com sucesso!!!\n");
                    carteira.real += totct;
                    carteira.bitcoin -= qtdC;
                    printf("Total de Bitcoins em sua carteira: %.4f\n", carteira.bitcoin);
                }
            }
            else{
                printf("Tudo bem, voltando ao menu...\n");
            }
        }
        else{
            printf("Senha errada\n");    
        }
    }
    else if (opcao ==  2){
        printf("Valor do ETHEREUM R$ %.2f\n", valoresC.v_eth);
        printf("Digite a quantidade que deseja vender: ");
        scanf(" %f", &qtdC);
        printf("***********************************************************************\n");
        printf("Insira sua SENHA: ");
        scanf(" %11s", senAcesso);
        if (strcmp(senha, senAcesso) == 0){
            criptoC =  qtdC*valoresC.v_eth;
            taxa = criptoC * 0.02;
            printf("Valor da taxa: R$ %.2f\n", taxa);
            totct = criptoC - taxa;
            printf("Valor a ser recebido pela criptomoeda: R$ %.2f\n", totct);
            printf("***********************************************************************\n");
            printf("Você realmente deseja vender o Ethereum? (S/N): ");
            scanf(" %c", &verificar);
            if (toupper(verificar) == 'S'){
                if (qtdC > carteira.ethereum){
                    printf("Saldo insuficiente!!!\n");
                }
                else{
                    printf("Compra realizada com sucesso!!!\n");
                    carteira.real += totct;
                    carteira.ethereum -= qtdC;
                    printf("Total de Em em sua carteira: %.4f\n", carteira.ethereum);
                }
            }
            else{
                printf("Tudo bem, voltando ao menu...\n");
            }
        }
        else{
            printf("Senha errada\n");    
        }
    }
    else if (opcao ==  3){
        printf("Valor do RIPPLE R$ %.2f\n", valoresC.v_rip);
        printf("Digite a quantidade que deseja vender: ");
        scanf(" %f", &qtdC);
        printf("***********************************************************************\n");
        printf("Insira sua SENHA: ");
        scanf(" %11s", senAcesso);
        if (strcmp(senha, senAcesso) == 0){
            criptoC =  qtdC*valoresC.v_rip;
            taxa = criptoC * 0.01;
            printf("Valor da taxa: R$ %.2f\n", taxa);
            totct = criptoC - taxa;
            printf("Valor a ser recebido pela criptomoeda: R$ %.2f\n", totct);
            printf("***********************************************************************\n");
            printf("Você realmente deseja vender a Ripple? (S/N): ");
            scanf(" %c", &verificar);
            if (toupper(verificar) == 'S'){
                if (qtdC > carteira.ripple){
                    printf("Saldo insuficiente!!!\n");
                }
                else{
                    printf("Compra realizada com sucesso!!!\n");
                    carteira.real += totct;
                    carteira.ripple -= qtdC;
                    printf("Total de Ripple em sua carteira: %.4f\n", carteira.ripple);
                }
            }
            else{
                printf("Tudo bem, voltando ao menu...\n");
            }
        }
        else{
            printf("Senha errada\n");    
        }
    }
    else{
        printf("Criptomoeda nao encontrada!!!\n");
    }
}
// ----------------------------------------------------------------------------------------
// ATUALIZAR COTAÇÃO
void sete(){
    printf("Deseja atualizar a cotação de todas as criptomoedas? (S/N): ");
    scanf(" %c", &verificar);
    if (toupper(verificar) == 'S'){

        void atualizarValor(float* valor, float* variacao) {
            *valor = *valor * (1.0 + *variacao);
        }

        srand(time(NULL));

        float variacao_bit =  (rand()% 101 - 50) / 1000.00;
        float variacao_eth =  (rand()% 101 - 50) / 1000.00;
        float variacao_rip =  (rand()% 101 - 50) / 1000.00;

        //att cotação bitcoin
        printf("printf");
        printf("Valor anterior a atualização: %.2f \n", valoresC.v_bit);
        atualizarValor(&valoresC.v_bit, &variacao_bit);
        printf("Atualização da cotação do bitcoin: %.2f\n", valoresC.v_bit);
        printf("variação: %.3f\n", variacao_bit);
        printf("***********************************************************************\n");

        //att cotação ethereum
        printf("Valor anterior a atualização: %.2f \n", valoresC.v_eth);
        atualizarValor(&valoresC.v_eth, &variacao_eth);
        printf("Atualização da cotação do bitcoin: %.2f\n", valoresC.v_eth);
        printf("variação: %.3f\n", variacao_eth);
        printf("***********************************************************************\n");

        //att cotação riple
        printf("Valor anterior a atualização: %.2f \n", valoresC.v_rip);
        atualizarValor(&valoresC.v_rip, &variacao_rip);
        printf("Atualização da cotação do bitcoin: %.2f\n", valoresC.v_rip);
        printf("variação: %.3f\n", variacao_rip);

    }
    else{
        printf("Os valores das criptomoedas não serão alterados! \n");
    }
}