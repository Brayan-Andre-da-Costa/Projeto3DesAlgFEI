#include <stdio.h> 
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes.h"
#include <ctype.h>

#define NUM_USUARIO 10
#define NUM_EXTRATO 100

struct usuario {
    char cpf[12];  
    char senha[20]; 
};

void passarSenha(const char* senUser, const char* CPF);

void save_carteira(const char* cpf);

void load_carteira(const char* cpf);


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
    {"43138734812", "rafa0702"},
    {"47143409834", "wrna123"}
    };
    
    while (true) {

        char s_cpf[11];
        char s_sen[9];  
        char senAcesso[12];
        char entrar;
        char nCad[50];
        char cpfCad[12];
        char senCad[19];


        printf("Você ja possui uma conta?(S/N) ");
        scanf(" %c", &entrar);

        //CADASTRAR USUARIO
    
        if (toupper(entrar) == 'N'){
            printf("Você deseja fazer um cadastro(S/N)? ");
            scanf(" %c", &entrar);
            if (toupper(entrar) == 'N'){
                printf("Tudo bem, saindo...\n");
                return 1;
            }
            printf("Digite seu nome: ");
            scanf(" %s", nCad);
            printf("Digite seu CPF: ");
            scanf(" %s", cpfCad);
            printf("Digite sua senha: ");
            scanf(" %s", senCad);

            if(verificaCad(cpfCad)){
                printf("Usuario ja cadastrado\n");
                return 1;
            }
            cadUsuario(nCad, cpfCad, senCad);
            return 1;
        }
        //ACESSO ADM

        if (toupper(entrar) == 'D'){
            printf("Acesso Restrito!!! Digite a senha de acesso: ");
            char acesso[9];
            scanf(" %s", acesso);
            if (strcmp(acesso, "FEI2024") != 0){
                return 1;
            }
            printf("Bem-vindo! Aqui estão suas opções\n");
            menu2();
            return 1;
        }

            
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
            printf("Login efetuado com sucesso\n");
            const char* cpf = s_cpf;
            load_carteira(cpf);
            while (true) {
                const char* CPF = s_cpf;
                const char* senUser = s_sen;
                passarSenha(senUser, CPF);
                save_carteira(cpf);
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
            printf("CPF/Senha incorretor\n");
        }      

    return 0;
    }
}
