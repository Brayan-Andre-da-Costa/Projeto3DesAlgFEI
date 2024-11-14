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

int main(){
    printf("Bem-vindo, para acessar o menu de administrador, por favor insira seu cpf e senha\n");
    printf("CPF: ");
    scanf(" %12s", cpfAcesso);
    printf("Senha: ");
    scanf(" %9s", senhaAcesso);

    if (strcmp(cpfAcesso, "123") != 0 || strcmp(senhaAcesso, "123") != 0){
        printf("Acesso negado!");
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
            case 2:
            printf("Digite o cpf que deseja excluir: ");
            scanf(" %11s", cpfExc);
            printf("Dados do úsuario...\n");
            printf("**********************************");
            printf(" \n");
            lerExt(cpfExc);


        }
    }
}