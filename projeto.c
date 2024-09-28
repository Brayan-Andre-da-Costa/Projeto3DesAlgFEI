#include <stdio.h> 
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes.h"

#define NUM_USUARIO 10
#define NUM_EXTRATO 100

struct usuario {
    char cpf[12];  
    char senha[20]; 
};

// void creat_ext(struct usuario u, struct extrato e){
//     char name_arq[50];

//     snprintf(name_arq, sizeof(name_arq), "%s_extrato.bin", u.cpf);

//     FILE *file = fopen(name_arq, "ab");
//     if (file == NULL){
//         printf("erro ao abrir o arquivo");
//         return;
//     }

//     fwrite(&e, sizeof(struct extrato), 1, file);

//     fclose(file);
// }

// struct extrato extrato1 = {"24/09/2024", 100.50, "Comra no supermercado"};


void passarSenha(const char* senUser, const char* CPF);


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

        // for (int i = 0; i < NUM_USUARIO; i++) {
        //     creat_ext(Usuarios[i], extrato1);
        // }

        char s_cpf[12];
        char s_sen[20];  
        char senAcesso[12];


        printf("Digite o CPF: ");
        scanf("%11s", s_cpf);  
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
                const char* CPF = s_cpf;
                const char* senUser = s_sen;
                const char* cpf = s_cpf;
                passarSenha(senUser, CPF);
                menu();

                int op;
                printf("Digite sua opcao: ");
                scanf(" %d", &op);
                if (op == 1) {
                    um();
                } else if (op == 2) {
                    lerExt(cpf);
                } else if (op == 3) {
                    tres();
                } else if (op == 4) {
                    quatro();
                } else if (op == 5) {
                    cinco();
                } else if (op == 6) {
                    seis();
                } else if (op == 7) {
                    sete();
                } else if (op == 8) {
                    break;  
                } else {
                    printf("Opcao invalida, tente novamente.\n");
                }
            }
            break;  
        } 
        else {
            printf("Usuario inexistente\n");
        }       
    }

    return 0;  
}
