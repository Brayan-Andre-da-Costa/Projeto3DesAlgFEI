#include <stdio.h> 
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
//VARIAVEIS GLOBAIS

typedef struct{
    float real;
    float bitcoin;
    float ethereum;
    float ripple;
} Saldos;

Saldos carteira = {0,0,0,0};

int dia, mes, ano;
char senA;

//validação/identificação

char senUser[12];
char senha[12];
char cpf[12];

// login/verificaCad

char cpf_a[12];
char sen_a[9];

//variaveis para extrato

double valorExt;
char dataExt[11];
char descExt[50];

//variaveis para carteira

double cReal;
double cBit;
double cEthe;
double cRipp;

//login ADM

int loginADM(const char* cpf_digitado, const char* senha_digitado, const char* arquivo) {
    FILE *file = fopen(arquivo, "r");

    if (file == NULL) {
        printf("Erro ao acessar os usuarios\n");
        return 0;
    }

    char cpf_a[20], sen_a[20], nome_a[50];
    
    // Lê linha por linha
    while (fscanf(file, "%s %s", cpf_a, sen_a) == 2) {
        // Compara o CPF e a senha digitados com os armazenados no arquivo
        if (strcmp(cpf_a, cpf_digitado) == 0 && strcmp(sen_a, senha_digitado) == 0) {
            fclose(file);
            printf("Login Efetuado com Sucesso.\n");
            return 1;
        }
    }

    fclose(file);
    printf("CPF ou senha incorretos.\n");
    return 0;
}

// atulizar os valores randomicos
//--------------------------------------------------------------------------------
void atualizarValor(float* valor, float variacao) {
    *valor = *valor * (1.0 + variacao);
}


//ATUALIZAR COTAÇÕES ADM
//------------------------------------------------------------------
void attCotacao() {
    char verificar;
    printf("Deseja atualizar a cotação de todas as criptomoedas? (S/N): ");
    scanf(" %c", &verificar);

    if (toupper(verificar) == 'S') {
        srand(time(NULL));

        FILE *file = fopen("criptos.txt", "r");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo criptos.txt para leitura!\n");
            return;
        }

        // Criar um arquivo temporário para armazenar os dados atualizados
        FILE *tempFile = fopen("cripto_temp.txt", "w");
        if (tempFile == NULL) {
            printf("Erro ao criar o arquivo temporário!\n");
            fclose(file);
            return;
        }

        char nome[50];
        float cotacao, taxaCompra, taxaVenda;
        while (fscanf(file, "%s %f %f %f", nome, &cotacao, &taxaCompra, &taxaVenda) == 4) {
            // Gerar uma variação aleatória para cada criptomoeda
            float variacao = (rand() % 101 - 50) / 1000.0; // Variação entre -5% e +5%
            printf("****************************************************\n");
            printf("Atualizando %s:\n", nome);
            printf("  Valor anterior: %.2f\n", cotacao);
            atualizarValor(&cotacao, variacao);
            printf("  Novo valor: %.2f (Variação: %.3f)\n", cotacao, variacao);

            // Escrever os dados atualizados no arquivo temporário
            fprintf(tempFile, "%s %.2f %.4f %.4f\n", nome, cotacao, taxaCompra, taxaVenda);
        }

        fclose(file);
        fclose(tempFile);

        // Substituir o arq original pelo temporario
        remove("criptos.txt");
        rename("cripto_temp.txt", "criptos.txt");

        printf("Cotações atualizadas com sucesso!\n");
    } else {
        printf("Cotações não alteradas.\n");
    }
}
// ----------------------------------------------------------------------------------------
// EXCLUIR CRIPTO

void excluirCripto(const char* nomeC ){
    char criptoArq[] = "criptos.txt";
    char linha[200];
    char tempArq[] = "temp.txt" ;
    int cont = 0;
    int encontrado = 0;

    // Excluir usuario no Banco de Dados

    FILE* cripto = fopen(criptoArq, "r");
    FILE* temp = fopen(tempArq, "w");

    if (cripto == NULL || temp == NULL){
        printf("Erro ao abrir os arquivos\n");
        return;
    }

    while (fgets(linha, sizeof(linha), cripto) != NULL) {
        if (strstr(linha, nomeC) == NULL) {
            fputs(linha, temp); // copia as linha fora do alcance da cripto
        } else {
            encontrado = 1;
        }
    }

    fclose(cripto);
    fclose(temp);

    if (encontrado){
        remove(criptoArq);
        rename(tempArq, criptoArq);
        cont += 1;
    }
    else{
        printf(" Cripto %s nao encontrado\n", nomeC);

    }

    if (cont == 1){
        printf("Cripto Removida com sucesso\n");
    }
    else{
        printf("Erro na remoção da cripto, por favor contatar o dev: (55) 40028922");
    }

}


// ----------------------------------------------------------------------------------------
// PEGAR DADOS DA CRIPTO

void dadosCripto(const char* cripto){

    FILE* file = fopen("criptos.txt", "r");

    if (file == NULL){
        perror("Arquivo Inexistente");
    }
    char nome[30];
    float cotacao, taxaC, taxaV;
    int encontrada = 0;

    while (fscanf(file, "%s %f %f %f", nome, &cotacao, &taxaC, &taxaV) == 4) {
        // Compara o CPF e a senha digitados com os armazenados no arquivo
        if (strcmp(nome, cripto) == 0) {
            printf("Nome: %s\n", nome);
            printf("Cotação: %.4f\n", cotacao);
            printf("Taxa de Compra: %.4f\n", taxaC);
            printf("Taxa de Venda: %.4f\n", taxaV);           
            encontrada = 1;
        }
    }
    if (!encontrada){
        printf("Cripto não encontrada\n");
    }

    fclose(file);

}

// ----------------------------------------------------------------------------------------
// LOGIN

int login(const char* cpf_digitado, const char* senha_digitado, const char* arquivo) {
    FILE *file = fopen(arquivo, "r");

    if (file == NULL) {
        printf("Erro ao acessar os usuarios\n");
        return 0;
    }

    char cpf_a[20], sen_a[20], nome_a[50];
    
    // Lê linha por linha
    while (fscanf(file, "%s %s %[^\n]", cpf_a, sen_a, nome_a) == 3) {
        // Compara o CPF e a senha digitados com os armazenados no arquivo
        if (strcmp(cpf_a, cpf_digitado) == 0 && strcmp(sen_a, senha_digitado) == 0) {
            fclose(file);
            printf("Login Efetuado com Sucesso.\n");
            return 1;
        }
    }

    fclose(file);
    printf("CPF ou senha incorretos.\n");
    return 0;
}

// função de cadastrar criptomoedas
//-----------------------------------------------------------------------------------------

void CadCripto(const char* nomeC, float valorC, float taxaCC, float taxaVC){

    FILE *file = fopen("criptos.txt","a");

    if (file == NULL){
        printf("Erro ao abrir o arquivo\n");
        return;
    } 


    fprintf(file, "%s %f %f %f\n", nomeC, valorC, taxaCC, taxaVC);

    fclose(file);
    printf("Cadastro de cripto efetuado com sucesso! \n");
}

// função de excluir usuarios
//-----------------------------------------------------------------------------------------

void excluirUsuario(const char* cpf){
    char cartArq[50];
    char extArq[50];
    char usuariosArq[] = "usuarios.txt";
    char tempArq[] = "temp.txt";
    char linha[200];
    int encontrado = 0;

    snprintf(cartArq, sizeof(cartArq), "%s_carteira.bin", cpf);
    snprintf(extArq, sizeof(extArq), "%s_extrato.bin", cpf);

    int cont = 0;
    //Excluir aquivos

    if (remove(cartArq) == 0) {
        cont += 1;
    } else {
        printf("Erro ao remover o arquivo %s. Ele pode não existir.\n", cartArq);
    }

    if (remove(extArq) == 0) {
        cont += 1;
    } else {
        printf("Erro ao remover o arquivo %s. Ele pode não existir.\n", extArq);
    }

    // Excluir usuario no Banco de Dados

    FILE* usuarios = fopen(usuariosArq, "r");
    FILE* temp = fopen(tempArq, "w");

    if (usuarios == NULL || temp == NULL){
        printf("Erro ao abrir os arquivos\n");
        return;
    }

    while (fgets(linha, sizeof(linha), usuarios) != NULL) {
        if (strstr(linha, cpf) == NULL) {
            fputs(linha, temp); // copia as linha fora do alcance do cpf
        } else {
            encontrado = 1;
        }
    }

    fclose(usuarios);
    fclose(temp);

    if (encontrado){
        remove(usuariosArq);
        rename(tempArq, usuariosArq);
        cont += 1;
    }
    else{
        printf(" Usuário %s nao encontrado\n", cpf);

    }

    if (cont == 3){
        printf("Usuário Removido com sucesso\n");
    }
    else{
        printf("Erro na remoção do usuário, por favor contatar o dev: (55) 40028922");
    }

}

// ----------------------------------------------------------------------------------------
// Verificação de cadastro

int verificaCad(const char* cpf_digitado){

    FILE *file = fopen("usuarios.txt","r"); 

    if(file == NULL){
        perror("Erro ao acessar o usuarios\n");
        return 0;
    }

    
    while (fscanf(file, "%s", cpf_a) == 1) {
        if (strcmp(cpf_a, cpf_digitado) == 0) {
            
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}



// ----------------------------------------------------------------------------------------
// FUNÇÃO PASSAR SENHA e CPF DO USUARIO DE ARQUIVO PROJETO PARA FUNCOES

void passarSenha(const char* senUser, const char* CPF){
    strcpy(senha, senUser);
    strcpy(cpf, CPF);
}

// ----------------------------------------------------------------------------------------
// FUNÇÃO GERAR DATA ATUAL

void pegarData(int *dia, int *mes){
    
    time_t d = time(NULL);

    struct tm *dataA = localtime(&d);

    *dia = dataA->tm_mday - 1;
    *mes = dataA->tm_mon + 1;    
}

void lerSaldo(const char* cpf){

    char nome_arq_c[50];
    Saldos carteira;

    snprintf(nome_arq_c, sizeof(nome_arq_c), "%s_carteira.bin", cpf);

    FILE *file = fopen(nome_arq_c,"rb");
    if (file == NULL){
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    if (fread(&carteira, sizeof(Saldos), 1, file) != 1) {
        printf("Erro ao ler os dados da carteira para o CPF: %s\n", cpf);
        fclose(file);
        return;
    }

    fclose(file);

    printf("Usuário/CPF %s:\n", cpf);
    printf("Saldo em Reais: R$ %.2f\n", carteira.real);
    printf("Saldo em Bitcoin: %.8f BTC\n", carteira.bitcoin);
    printf("Saldo em Ripple: %.2f XRP\n", carteira.ripple);
    printf("Saldo em Ethereum: %.8f ETH\n", carteira.ethereum);


}

void cadUsuario(char *nCad, char *cpfCad, char *senCad){

    FILE *file = fopen("usuarios.txt","a");
    if (file == NULL){
        printf("Erro ao abrir o arquivo\n");
        return;
    } 

    fprintf(file, "%s %s %s\n", cpfCad, senCad, nCad);

    fclose(file);
    printf("Cadastro efetuado com sucesso! \n");
}
// ----------------------------------------------------------------------------------------
// FUNÇÃO SALVAR CARTEIRA DO USUARIO


void save_carteira(const char* cpf){

    char nome_arq_c[50];
    snprintf(nome_arq_c, sizeof(nome_arq_c), "%s_carteira.bin", cpf);

    FILE *file = fopen(nome_arq_c,"wb");
    if (file == NULL){
        printf("Erro ao abrir o arquivo\n");
        return;
    } 

    fwrite(&carteira, sizeof(Saldos), 1, file);

    fclose(file);
}
// ----------------------------------------------------------------------------------------
// FUNÇÃO LER O FILE CARTEIRA E RESTABELECER OS VALORES

void load_carteira(const char* cpf){

    char nome_arq_c[50];

    snprintf(nome_arq_c, sizeof(nome_arq_c), "%s_carteira.bin", cpf);

    FILE *file = fopen(nome_arq_c, "rb");
    if (file == NULL){
        printf("Bem-vindo novo Investidor! Criando sua carteira em\n");
        //temporizador
        int t = 5; 

        while (t > 0) {
            sleep(1);             
            for (int i = 0; i < t; i++) {
                printf("."); 
            }
            printf("\n"); 
            t--; 
        }
        return;

    }
    fread(&carteira, sizeof(Saldos), 1, file);

    fclose(file);
}


// ----------------------------------------------------------------------------------------
// FUNÇÃO SALVAR EXTRATO

struct extrato {
    char dataExt[11];
    double valorExt;
    char descExt[50];
};

void save_extrato(const char* cpf, const char* dataExt, double valorExt, const char* descExt){
    struct extrato e;

    //determinação de envio
    strncpy(e.dataExt, dataExt, sizeof(e, dataExt) -1);
    e.valorExt = valorExt;
    strncpy(e.descExt, descExt, sizeof(e.descExt)-1);

    char nome_arq[50];

    snprintf(nome_arq, sizeof(nome_arq), "%s_extrato.bin", cpf);

    FILE *file = fopen(nome_arq,"ab");
    if (file == NULL){
        printf("Erro ao abrir o arquivo\n");
    } 

    fwrite(&e, sizeof(struct extrato), 1, file);

    fclose(file);
}

// ----------------------------------------------------------------------------------------
// FUNÇAO LER EXTRATO // Consultar Saldo

void lerExt(const char* cpf){
    struct extrato e;
    char nome_arq[50];
    int totExt, extLer, i;

    snprintf(nome_arq, sizeof(nome_arq), "%s_extrato.bin", cpf);

    FILE *file = fopen(nome_arq, "rb");
    if (file == NULL){
        printf("Ainda não há extrato em sua conta!\n");
        return;
    } 

    //calcula a qtd de extrato no arquivo - end - size - cal 
    fseek(file, 0, SEEK_END);
    long tam_arq = ftell(file);
    totExt = tam_arq / sizeof(struct extrato);

    //vai determinar quantos extratos serão lidos a partir do calculo anterior, com um limite de 100
    extLer = totExt > 100 ? 100: totExt;

    //move o ponteiro de inicio de leitura para o inicio do arquivo
    fseek(file, -(extLer * sizeof(struct extrato)), SEEK_END);

    for (i = 0; i < extLer;i++){
        printf("*******************************************\n");
        fread(&e, sizeof(struct extrato),1,file);
        printf("Data: %s\n", e.dataExt);
        printf("Valor: %.3f\n", e.valorExt);
        printf("Descrição da transação: %s\n", e.descExt);
        
    }

    fclose(file);


}



// ----------------------------------------------------------------------------------------
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
    pegarData(&dia, &mes);
    sprintf(dataExt," %02d/%02d\n", dia, mes);
}

void menu2(){
    printf("***********************************************************************\n");
    printf("1 - Cadastrar Investidor\n");
    printf("2 - Excluir Investidor\n");
    printf("3 - Cadastrar Criptomoeda\n");
    printf("4 - Excluir Critomoeda\n");
    printf("5 - Consultar Saldo de um Investidor\n");
    printf("6 - Consultar Extrato de um Investidor\n");
    printf("7 - Atualizar a Cotação de Criptomoedas\n");
    printf("8 - Sair\n");
    printf(" \n");
}

// ----------------------------------------------------------------------------------------
// FUNÇÃO SALDO

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
    valorExt = deposito;
    sprintf(descExt,"Deposito em Reais.");
    save_extrato(cpf, dataExt, valorExt, descExt);

}

// ----------------------------------------------------------------------------------------
// SACAR

void quatro(){
    float saque;

    printf("***********************************************************************\n");
    printf("Insira o quanto deseja sacar: ");
    scanf(" %f", &saque);

    if (saque>carteira.real){
        printf("O valor sacado e maior do que consta em conta\n");
    }
    else{         
        printf("Insira sua SENHA: ");
        scanf(" %11s", senUser);
        if (strcmp(senha, senUser) == 0){
            carteira.real -= saque;
            printf("Valor sacado R$ %.2f\n ", saque);
            printf("Novo saldo R$ %.2f\n ", carteira.real);
            valorExt = saque;
            sprintf(descExt,"Saque em Reais");
            save_extrato(cpf, dataExt, valorExt, descExt);
        }
        else{
                printf("Senha invalida\n");
        }
    }
}


// ----------------------------------------------------------------------------------------
// COMPRAR CRIPTOS

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
        scanf("%11s", senUser);
        if (strcmp(senha, senUser)==0) {
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
                    valorExt = criptoC;
                    sprintf(descExt,"Compra de Bitcoin.");
                    save_extrato(cpf, dataExt, valorExt, descExt);
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
        scanf("%11s", senUser);
        if (strcmp(senha, senUser) == 0){
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
                    valorExt = criptoC;
                    sprintf(descExt,"Compra de Ethereum.");
                    save_extrato(cpf, dataExt, valorExt, descExt);
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
        scanf("%11s", senUser);
        if (strcmp(senha, senUser) == 0){
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
                    valorExt = criptoC;
                    sprintf(descExt,"Compra de Ripple.");
                    save_extrato(cpf, dataExt, valorExt, descExt);
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
// ----------------------------------------------------------------------------------------
// VENDER CRIPTOS

float qtdC;

void seis(){
    printf("***********************************************************************\n");
    printf("1 - BITCOIN // Taxa de venda em 3%% \n");
    printf("2 - ETHEREUM // Taxa de venda em 2%%\n");
    printf("3 - RIPPLE // Taxa de venda em 1%%\n");
    printf("Escolha a cripto que deseja vender: ");
    scanf("%d", &opcao);
    if (opcao ==  1){
        printf("Valor do BITCOIN R$ %.2f\n", valoresC.v_bit);
        printf("Digite a quantidade que deseja vender: ");
        scanf(" %f", &qtdC);
        printf("***********************************************************************\n");
        printf("Insira sua SENHA: ");
        scanf(" %11s", senUser);
        if (strcmp(senha, senUser) == 0){
            criptoC =  qtdC*valoresC.v_bit;
            taxa = criptoC * 0.03;
            printf("Valor da taxa: R$ %.2f\n", taxa);
            totct = criptoC - taxa;
            printf("Valor a ser recebido pela criptomoeda: R$ %.2f\n", totct);
            printf("***********************************************************************\n");
            printf("Você realmente deseja vender o BITCOIN? (S/N): ");
            scanf(" %c", &verificar);
            if (toupper(verificar) == 'S'){
                if (qtdC > carteira.bitcoin){
                    printf("Saldo insuficiente!!!\n");
                }
                else{
                    printf("Venda realizada com sucesso!!!\n");
                    carteira.real += totct;
                    carteira.bitcoin -= qtdC;
                    printf("Total de Bitcoins em sua carteira: %.4f\n", carteira.bitcoin);
                    valorExt = qtdC;
                    sprintf(descExt,"Venda de Bitcoin.");
                    save_extrato(cpf, dataExt, valorExt, descExt);
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
    else if (opcao ==  2){
        printf("Valor do ETHEREUM R$ %.2f\n", valoresC.v_eth);
        printf("Digite a quantidade que deseja vender: ");
        scanf(" %f", &qtdC);
        printf("***********************************************************************\n");
        printf("Insira sua SENHA: ");
        scanf(" %11s", senUser);
        if (strcmp(senha, senUser) == 0){
            criptoC =  qtdC*valoresC.v_eth;
            taxa = criptoC * 0.02;
            printf("Valor da taxa: R$ %.2f\n", taxa);
            totct = criptoC - taxa;
            printf("Valor a ser recebido pela criptomoeda: R$ %.2f\n", totct);
            printf("***********************************************************************\n");
            printf("Você realmente deseja vender o Ethereum? (S/N): ");
            scanf(" %c", &verificar);
            if (toupper(verificar) == 'S'){
                if (qtdC > carteira.ethereum){
                    printf("Saldo insuficiente!!!\n");
                }
                else{
                    printf("Compra realizada com sucesso!!!\n");
                    carteira.real += totct;
                    carteira.ethereum -= qtdC;
                    printf("Total de Ethereum em sua carteira: %.4f\n", carteira.ethereum);
                    valorExt = qtdC;
                    sprintf(descExt,"Venda de Ethereum.");
                    save_extrato(cpf, dataExt, valorExt, descExt);
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
    else if (opcao ==  3){
        printf("Valor do RIPPLE R$ %.2f\n", valoresC.v_rip);
        printf("Digite a quantidade que deseja vender: ");
        scanf(" %f", &qtdC);
        printf("***********************************************************************\n");
        printf("Insira sua SENHA: ");
        scanf(" %11s", senUser);
        if (strcmp(senha, senUser) == 0){
            criptoC =  qtdC*valoresC.v_rip;
            taxa = criptoC * 0.01;
            printf("Valor da taxa: R$ %.2f\n", taxa);
            totct = criptoC - taxa;
            printf("Valor a ser recebido pela criptomoeda: R$ %.2f\n", totct);
            printf("***********************************************************************\n");
            printf("Você realmente deseja vender a Ripple? (S/N): ");
            scanf(" %c", &verificar);
            if (toupper(verificar) == 'S'){
                if (qtdC > carteira.ripple){
                    printf("Saldo insuficiente!!!\n");
                }
                else{
                    printf("Compra realizada com sucesso!!!\n");
                    carteira.real += totct;
                    carteira.ripple -= qtdC;
                    printf("Total de Ripple em sua carteira: %.4f\n", carteira.ripple);
                    valorExt = qtdC;
                    sprintf(descExt,"Venda de Ripple.");
                    save_extrato(cpf, dataExt, valorExt, descExt);
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

// ----------------------------------------------------------------------------------------
// ATUALIZAR COTAÇÃO
void sete(){
    printf("Deseja atualizar a cotação de todas as criptomoedas? (S/N): ");
    scanf(" %c", &verificar);
    if (toupper(verificar) == 'S'){

        void atualizarValor(float* valor, float* variacao) {
            *valor = *valor * (1.0 + *variacao);
        }

        srand(time(NULL));

        float variacao_bit =  (rand()% 101 - 50) / 1000.00;
        float variacao_eth =  (rand()% 101 - 50) / 1000.00;
        float variacao_rip =  (rand()% 101 - 50) / 1000.00;

        //att cotação bitcoin
        printf("Valor anterior a atualização: %.2f \n", valoresC.v_bit);
        atualizarValor(&valoresC.v_bit, &variacao_bit);
        printf("Atualização da cotação do bitcoin: %.2f\n", valoresC.v_bit);
        printf("variação: %.3f\n", variacao_bit);
        printf("***********************************************************************\n");

        //att cotação ethereum
        printf("Valor anterior a atualização: %.2f \n", valoresC.v_eth);
        atualizarValor(&valoresC.v_eth, &variacao_eth);
        printf("Atualização da cotação do Ethereum: %.2f\n", valoresC.v_eth);
        printf("variação: %.3f\n", variacao_eth);
        printf("***********************************************************************\n");

        //att cotação riple
        printf("Valor anterior a atualização: %.2f \n", valoresC.v_rip);
        atualizarValor(&valoresC.v_rip, &variacao_rip);
        printf("Atualização da cotação do Ripple: %.2f\n", valoresC.v_rip);
        printf("variação: %.3f\n", variacao_rip);

    }
    else{
        printf("Os valores das criptomoedas não serão alterados! \n");
    }
}