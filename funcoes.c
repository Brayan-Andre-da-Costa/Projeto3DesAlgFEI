#include <stdio.h> 
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

//VARIAVEIS GLOBAIS
int senha = 1234;

int  senAcesso;

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
    int senha = 1234;

    printf("***********************************************************************\n");
    printf("Insira o quanto deseja sacar: ");
    scanf("%f", &saque);

    if (saque>carteira.real){
        printf("O valor sacado e maior do que consta em conta\n");
        }
        else{
            printf("Insira sua SENHA: ");
            scanf("%d", &senAcesso);
            if (senha==senAcesso){
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
// COMPRAR/VENDER CRIPTOMOEDAS

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
    printf("")
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
        scanf("%d", &senAcesso);
        if (senAcesso == senha){
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
        scanf("%d", &senAcesso);
        if (senAcesso == senha){
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
        scanf("%d", &senAcesso);
        if (senAcesso == senha){
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
