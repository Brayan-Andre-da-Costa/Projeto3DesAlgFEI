#include <stdio.h> 
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes.h"
#include <ctype.h>

#define NUM_USUARIO 10
#define NUM_EXTRATO 100

float deposito;

struct usuario {
    char cpf[12];  
    char senha[20]; 
};

void passarSenha(const char* senUser, const char* CPF);


int main() {
    
    while (true) {

        char s_cpf[11];
        char s_sen[9];  
        char senAcesso[12];
           
        //INICIAR LOGIN


        printf("Digite o CPF: ");
        scanf("%11s", s_cpf);  
        printf("Digite a senha: ");
        scanf("%19s", s_sen);   

        int encontrado = 0;
        if(login(s_cpf, s_sen, "usuarios.txt")){
            encontrado = 1;
        }

        if (encontrado) {
            const char* cpf = s_cpf;
            puxar_carteira(cpf);
            while (true) {
                const char* CPF = s_cpf;
                const char* senUser = s_sen;
                passarSenha(senUser, CPF);
                menu();

                int op;
                printf("Digite sua opcao: ");
                scanf(" %d", &op);
                if (op == 1) {
                    consultar_saldo(cpf);
                } else if (op == 2) {
                    lerExt(cpf);
                } else if (op == 3) {
                    printf("Digite o quanto deseja depositar: ");
                    scanf(" %f", &deposito);
                    depositar(cpf, deposito);
                } else if (op == 4) {
                    quatro();
                } else if (op == 5) {
                    comprarCripto();
                } else if (op == 6) {
                    venderCripto();
                } else if (op == 7) {
                    attCotacao();
                } else if (op == 8) {
                    break;  
                } else {
                    printf("Opcao invalida, tente novamente.\n");
                }
            }
            break;  
        } 
        else {
            printf("CPF/Senha incorreto\n");
        }      

    return 0;
    }
}
