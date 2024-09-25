#include <stdio.h> 
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes.h"

#define NUM_USUARIO 10
#define NUM_EXTRATO 100

struct extrato {
    char desc[100];
};

struct usuario {
    char cpf[12];  
    char senha[20]; 
};

int main() {

    struct usuario Usuarios[NUM_USUARIO] = {
    {"47169633817", "garro10"},
    {"47143403454", "senha143"},
    {"47143409804", "brayan12"},
    {"47143408904", "se22a123"},
    {"47144509564", "senhqwr3"},
    {"47143409834", "seqwa123"},
    {"47147609887", "s1n0a123"},
    {"47143423674", "senhanr3"},
    {"47143409856", "seqfa123"},
    {"47143409834", "wrna123"}
    };
    
    while (true) {

        char s_cpf[12];
        char s_sen[20];  

        printf("Digite o CPF: ");
        scanf("%11s", s_cpf);  // 
        printf("Digite a senha: ");
        scanf("%19s", s_sen);   

        int encontrado = 0;
        for (int i = 0; i < NUM_USUARIO; i++) {
            if (strcmp(Usuarios[i].cpf, s_cpf) == 0 && strcmp(Usuarios[i].senha, s_sen) == 0) {
                encontrado = 1;
                break;
            }
        }

        if (encontrado) {
            printf("Login efetuado com sucesso\n");

            while (true) {
                senA = s_sen;
                menu();
                int op;
                printf("Digite sua opcao: ");
                scanf("%d", &op);
                if (op == 1) {
                    um();
                } else if (op == 2) {
                    // dois();
                } else if (op == 3) {
                    tres();
                } else if (op == 4) {
                    quatro(senA);
                } else if (op == 5) {
                    cinco(senA);
                } else if (op == 6) {
                    seis(senA);
                } else if (op == 7) {
                    sete();
                } else if (op == 8) {
                    break;  
                } else {
                    printf("Opcao invalida, tente novamente.\n");
                }
            }
            break;  
        } else {
            printf("Usuario inexistente\n");
        }       
    }

    return 0;  
}
