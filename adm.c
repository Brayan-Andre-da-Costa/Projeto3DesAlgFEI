#include <stdio.h> 
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "funcoesADM.h"
#include <ctype.h>

char cpfAcesso[12];
char senhaAcesso[9]; 
char nCad[50];
char cpfCad[12];
char senCad[19];
char cpfExc[12];
int opcao;
char entrar;
char nomeC[10];
float valorC;
float taxaCC;
float taxaVC;
char criptoExcluir[15];
char cpfCon[12];

int main(){
    printf("Bem-vindo, para acessar o menu de administrador, por favor insira seu cpf e senha\n");
    printf("CPF: ");
    scanf(" %12s", cpfAcesso);
    printf("Senha: ");
    scanf(" %9s", senhaAcesso);

    int encontrado = 0;
    if(loginADM(cpfAcesso, senhaAcesso, "acessoR.txt")){
        encontrado = 1;
    }

    if (!encontrado){
        return 1;
    }
    while (true){
        menu2();
        printf("Digite a opção que deseja acessar: ");
        scanf(" %d", &opcao);

        switch(opcao){
            case 1:
                printf("Digite o nome do investidor: ");
                scanf(" %s", nCad);
                printf("Digite o CPF do investidor: ");
                scanf(" %s", cpfCad);
                printf("Digite a senha do investidor: ");
                scanf(" %s", senCad);

                if(verificaCad(cpfCad)){
                    printf("Usuario ja cadastrado\n");
                    return 1;
                }
                cadUsuario(nCad, cpfCad, senCad);
                return 1;
                break;

            case 2:
                printf("Digite o cpf que deseja excluir: ");
                scanf(" %11s", cpfExc);
                if(verificaCad(cpfExc)){
                    printf("Dados do úsuario...\n");
                    printf("CPF: %s\n", cpfExc);
                    pegarNome(cpfExc);
                    printf("**********************************\n");
                    printf("Extrato: \n");
                    printf(" \n");
                    lerExt(cpfExc);
                    printf("**********************************\n");
                    printf("Saldo:\n");
                    printf("\n");
                    lerSaldo(cpfExc);
                    printf("\n");
                    printf("Você realmente deseja excluir esse usuário(S/N)? ");
                    scanf(" %c", &entrar);
                    if (toupper(entrar) == 'N'){
                        printf("Voltando ao menu...\n");
                    }
                    else{
                        printf("excluindo...\n");
                        excluirUsuario(cpfExc);
                    }
                    break;
                    
                }
                printf("Usuário não encontrado.\n");
                break;

            case 3:
                printf("****************************************\n");
                printf("Novo Cadastro de Criptomoeda: \n");
                printf("\n");
                printf("Digite o nome da criptomoeda: ");
                scanf(" %s", nomeC);
                printf("Digite a cotação inicial da criptomoeda: ");
                scanf(" %f", &valorC);
                printf("Digite a taxa de compra da criptomoeda: ");
                scanf(" %f", &taxaCC);
                printf("Digite a taxa de venda da criptomoeda: ");
                scanf(" %f", &taxaVC);
                CadCripto(nomeC, valorC, taxaCC, taxaVC);
                break;

            case 4:
                printf("Digite o nome da criptomoeda: ");
                scanf(" %s", criptoExcluir);
                dadosCripto(criptoExcluir);
                printf("Você realmente quer excluir essa criptomoeda?(S/N) ");
                scanf(" %s", &entrar);
                if(toupper(entrar) == 'N'){
                    printf("Saindo...\n");
                    break;
                }
                excluirCripto(criptoExcluir);
                break;

            case 5:
                printf("Digite o CPF que deseja consultar o saldo: ");
                scanf(" %11s", cpfCon);
                printf("**************************************\n");
                puxar_carteira(cpfCon);
                printf("**************************************\n");
                break;

            case 6: 
                printf("Digite o CPF que deseja consultar o extrato: ");
                scanf(" %11s", cpfCon);
                printf("**************************************\n");
                lerExt(cpfCon);
                printf("**************************************\n");
                break;

            case 7:
                attCotacao();
                break;


            case 8:
                return 1;
        }
    }
}