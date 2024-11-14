#include <stdio.h> 
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes.h"
#include <ctype.h>

char cpfAcesso[12];
char senhaAcesso[9]; 

int main(){
    printf("Bem-vindo, para acessar o menu de administrador, por favor insira seu cpf e senha\n");
    printf("CPF: ");
    scanf(" %12s" cpfAcesso);
    printf("Senha: ");
    scanf(" %9c" senhaAcesso);

    if (cpfAcesso != 123 && senhaAcesso =! 123){
        printf("Acesso negado!");
        return 1;
    }

    while (true){

    }


}