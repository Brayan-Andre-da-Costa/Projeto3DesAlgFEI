#include <stdio.h> 
#include <stdbool.h>
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
    printf("sffadfsd")
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
    printf("Voce tem essa quantidade de Reais em sua carteira: R$%.3f\n", carteira.real);
    printf("Voce tem essa quantidade de Bitcoin em sua carteira: R$%.3f\n", carteira.bitcoin);
    printf("Voce tem essa quantidade de Ethereum em sua carteira: R$%.3f\n", carteira.ethereum);
    printf("Voce tem essa quantidade de Ripple em sua carteira: R$%.3f\n", carteira.ripple);
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
float bitC;
char verificar;

void cinco(){
    printf("***********************************************************************\n");
    printf("1 - BITCOIN // Taxa de compra em 2% \n");
    printf("2 - ETHEREUM // Taxa de compra em 1%\n");
    printf("3 - RIPPLE // Taxa de compra em 1%\n");
    printf("Escolha a cripto que deseja comprar: ");
    scanf("%d", &opcao);
    if (opcao ==  1){
        printf("Valor do BITCOIN R$ %.2f\n", valoresC.v_bit);
        printf("Digite o valor que deseja comprar: ");
        scanf("%f", &valC);
        printf("Insira sua SENHA: ");
        scanf("%d", &senAcesso);
        if (senAcesso == senha){
            bitC =  valoresC.v_bit/valC;
            taxa = valC * 0.02;
            printf("Valor da taxa: R$ %.2f\n", taxa);
            totct = valC + taxa;
            printf("Valor a ser pago pela criptomoeda: R$ %.2f\n", totct);
            printf("Você realmente deseja comprar o BITCOIN? (S/N)");
            scanf("%s", &verificar);
            if (verificar == "Y"){
                if (totct > carteira.real){
                    printf("Saldo insuficiente!!!\n");
                }
                else{
                    printf("Compra realizada com sucesso!!!\n");
                    carteira.real -= totct;
                    carteira.bitcoin += bitC;
                }
            }
            else{
                printf("Tudo bem, voltando ao menu...");
            }
        }
        else{
            printf("Senha errada");    
        }
    }
    else if (opcao == 2){
       
    }
    else if (opcao == 3){
        
    }
    else{
        printf("Criptomoeda nao encontrada!!!");
    }
    


}
