#include <stdio.h> 
#include <stdbool.h>
#include "funcoes.h"

int senha = 1234;
int cpf = 12;
int main(){
    while (true){
    int s_cpf;
    int s_sen;
    printf("Digite o CPF: ");
    scanf("%d", &s_cpf);
    printf("Digite a senha: ");
    scanf("%d", &s_sen);
        if (s_cpf == cpf && s_sen == senha){
            printf("Login efetuado com sucesso\n");
            break;
        }
        else{
            printf("Usuario inexistente\n");
            }       
        }
    while(true){
        menu();
        int op;
        printf("Digite sua opcao: ");
        scanf("%d", &op);
        if (op==1){
            um();
        }
        else if(op==2){
            // dois();
        }
        else if(op==3){
            tres();
        }
        else if(op==4){
            quatro();
        }
        else if(op==5){
            cinco();
        }
        else if(op==6){
            // seis();
        }
        else if(op==7){
            // sete();
        }
        else if(op==8){
            break;
        }
    }
return 0;  
}
