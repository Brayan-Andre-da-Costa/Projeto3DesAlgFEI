#include <stdio.h> 
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
//VARIAVEIS GLOBAIS

#define MAX_CRIPTOS 100

typedef struct{
    float real;
    float bitcoin;
    float ethereum;
    float ripple;
} Saldos;

struct extrato {
    char dataExt[20];   
    double valorExt;    
    char descExt[100];  
    int tipoExt;        
};

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

typedef struct {
    char nome[50];
    float valor;      
    float taxaCompra; 
    float taxaVenda;
    float quantidade;
} Cripto;

typedef struct {
    float real; 
    Cripto criptos[100];
    int totalCriptos;
} Carteira;

Carteira carteira = {0.0};
     

//ler as criptos que tem no txt
//------------------------------------------------------------------------------------------


int ler_criptos(Cripto* criptos, int maxCriptos) {
    FILE* file = fopen("criptos.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de criptomoedas.\n");
        return 0;
    }

    int count = 0;
    char linha[100]; 

    while (count < maxCriptos && fgets(linha, sizeof(linha), file) != NULL) {
        if (sscanf(linha, "%49s %f %f %f", criptos[count].nome, &criptos[count].valor, &criptos[count].taxaCompra, &criptos[count].taxaVenda) == 4) {
            criptos[count].taxaCompra /= 100.0; 
            criptos[count].taxaVenda /= 100.0;
            count++;
        }
    }

    fclose(file);
    return count;
}

//vender cripto
//------------------------------------------------------------------------------------------

void venderCripto(const char* cpf) {
    Cripto criptos[MAX_CRIPTOS];
    int totalCriptos = ler_criptos(criptos, MAX_CRIPTOS);  

    if (totalCriptos == 0) {
        printf("Nenhuma criptomoeda cadastrada!\n");
        return;
    }

    printf("***********************************************************************\n");
    printf("Lista de criptomoedas disponíveis:\n");
    for (int i = 0; i < totalCriptos; i++) {
        printf("%d - %s // Valor: R$ %.2f // Taxa de Venda: %.2f%%\n", 
               i + 1, criptos[i].nome, criptos[i].valor, criptos[i].taxaVenda * 100);
    }

    int opcao;
    printf("Escolha a criptomoeda que deseja vender: ");
    scanf("%d", &opcao);

    if (opcao < 1 || opcao > totalCriptos) {
        printf("Opção inválida!\n");
        return;
    }

    Cripto criptoSelecionada = criptos[opcao - 1];
    float quantidadeVendida, valorVenda, taxa, valorTotal;

    printf("Você escolheu: %s\n", criptoSelecionada.nome);
    printf("Digite a quantidade de %s que deseja vender: ", criptoSelecionada.nome);
    scanf("%f", &quantidadeVendida);

    // Verifica se a qtd de cripto é maior doq ele tem
    int criptoExistente = 0;
    for (int i = 0; i < carteira.totalCriptos; i++) {
        if (strcmp(carteira.criptos[i].nome, criptoSelecionada.nome) == 0) {
            criptoExistente = 1;
            if (carteira.criptos[i].valor < quantidadeVendida) {
                printf("Quantidade insuficiente de %s para realizar a venda!\n", criptoSelecionada.nome);
                return;
            }
            break;
        }
    }

    if (!criptoExistente) {
        printf("Você não possui essa criptomoeda em sua carteira!\n");
        return;
    }

    valorVenda = quantidadeVendida * criptoSelecionada.valor;
    taxa = valorVenda * criptoSelecionada.taxaVenda;
    valorTotal = valorVenda - taxa; 
    char senhaUsuario[12];

    printf("***********************************************************************\n");
    printf("Resumo da venda:\n");
    printf("Valor da taxa: R$ %.2f\n", taxa);
    printf("Valor total a ser recebido: R$ %.2f\n", valorTotal);
    printf("Quantidade de %s vendida: %.4f\n", criptoSelecionada.nome, quantidadeVendida);
    printf("***********************************************************************\n");
    printf("Para confirmar a venda, digite sua senha: ");
    scanf("%s", senhaUsuario);

    if (strcmp(senha, senhaUsuario) != 0) {
        printf("Senha incorreta! Operação cancelada.\n");
        return;
    }

    // att a struct carteira
    for (int i = 0; i < carteira.totalCriptos; i++) {
        if (strcmp(carteira.criptos[i].nome, criptoSelecionada.nome) == 0) {
            carteira.criptos[i].valor -= quantidadeVendida; 
            break;
        }
    }

    carteira.real += valorTotal;

    char nome_arq_c[50];
    snprintf(nome_arq_c, sizeof(nome_arq_c), "%s_carteira.txt", cpf);

    FILE* file = fopen(nome_arq_c, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo da carteira para atualização!\n");
        return;
    }

    // att o arquivo
    fprintf(file, "Reais: %.2f\n", carteira.real);
    for (int i = 0; i < carteira.totalCriptos; i++) {
        fprintf(file, "%s: %.4f\n", carteira.criptos[i].nome, carteira.criptos[i].valor);
    }

    fclose(file);

    // salva o extrato
    struct extrato e;
    const char* dataAtual = "2024-11-19";  
    snprintf(e.dataExt, sizeof(e.dataExt), "%s", dataAtual);
    e.valorExt = valorTotal;
    snprintf(e.descExt, sizeof(e.descExt), "Venda de %s", criptoSelecionada.nome);
    e.tipoExt = 1;  

    char nome_arq_ext[50];
    snprintf(nome_arq_ext, sizeof(nome_arq_ext), "%s_extrato.bin", cpf);

    FILE *file_ext = fopen(nome_arq_ext, "ab");  
    if (file_ext == NULL) {
        printf("Erro ao abrir o arquivo de extrato!\n");
        return;
    }

    // salva o extrato
    fwrite(&e, sizeof(struct extrato), 1, file_ext);
    fclose(file_ext);

    printf("Venda de %s realizada com sucesso!\n", criptoSelecionada.nome);
    printf("Saldo em reais atualizado: R$ %.2f\n", carteira.real);
}

//new funçao dinamica compra cripto
//------------------------------------------------------------------------------------------

void atualizar_arquivo_carteira(const char* cpf, Carteira* carteira) {
    char nome_arq_c[50];
    snprintf(nome_arq_c, sizeof(nome_arq_c), "%s_carteira.txt", cpf);

    FILE* file = fopen(nome_arq_c, "w");
    if (file == NULL) {
        printf("Erro ao atualizar o arquivo da carteira!\n");
        return;
    }

    fprintf(file, "Reais: %.2f\n", carteira->real);
    for (int i = 0; i < carteira->totalCriptos; i++) {
        fprintf(file, "%s: %.4f\n", carteira->criptos[i].nome, carteira->criptos[i].valor);
    }

    fclose(file);
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
            printf("*******************************\n");
            printf("Nome: %s\n", nome);
            printf("Cotação: %.4f\n", cotacao);
            printf("Taxa de Compra: %.0f%%\n", taxaC);
            printf("Taxa de Venda: %.0f%%\n", taxaV);     
            printf("*******************************\n");      
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
    

    while (fscanf(file, "%s %s %[^\n]", cpf_a, sen_a, nome_a) == 3) {
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

    //excluir usuarios do banco de dados
    FILE* usuarios = fopen(usuariosArq, "r");
    FILE* temp = fopen(tempArq, "w");

    if (usuarios == NULL || temp == NULL){
        printf("Erro ao abrir os arquivos\n");
        return;
    }

    while (fgets(linha, sizeof(linha), usuarios) != NULL) {
        if (strstr(linha, cpf) == NULL) {
            fputs(linha, temp); 
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

void pegarNome(const char* cpf){

        FILE *file = fopen("usuarios.txt", "r");

        char nome_a[15];

        if (file == NULL){
            printf("Erro ao abrir o arquivo\n");
            return;
        } 
        while (fscanf(file, "%s %s %[^\n]", cpf_a, sen_a, nome_a) == 3) {
            if (strcmp(cpf_a, cpf) == 0) {
                fclose(file);
                printf("Nome: %s\n", nome_a);
            }
        }
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
// FUNÇÃO PARA SALVAR A CARTEIRA

void save_carteira(const char* cpf, Carteira* carteira) {
    char nome_arq_c[50];
    snprintf(nome_arq_c, sizeof(nome_arq_c), "%s_carteira.txt", cpf);

    FILE *file = fopen(nome_arq_c, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar a carteira.\n");
        return;
    }

    fprintf(file, "Reais: %.2f\n", carteira->real);

    //salva as criptomoedas
    fprintf(file, "Criptomoedas:\n");
    for (int i = 0; i < carteira->totalCriptos; i++) {
        fprintf(file, "%s: %.4f\n", carteira->criptos[i].nome, carteira->criptos[i].valor);
    }

    fclose(file);
}

// FUNÇAO PARA CARREGAR

void carregar_carteira(const char* cpf, Carteira* carteira) {
    char nome_arq_c[50];
    snprintf(nome_arq_c, sizeof(nome_arq_c), "%s_carteira.txt", cpf);

    FILE* file = fopen(nome_arq_c, "r");
    if (file == NULL) {
        carteira->real = 0.0;  // caso não há carteira, é criado uma zerada
        carteira->totalCriptos = 0;
        return;
    }

    fscanf(file, "Reais: %f\n", &carteira->real);

    carteira->totalCriptos = 0;
    while (fscanf(file, "%49[^:]: %f\n", 
                  carteira->criptos[carteira->totalCriptos].nome, 
                  &carteira->criptos[carteira->totalCriptos].valor) == 2) {
        carteira->totalCriptos++;
    }

    fclose(file);
}

void puxar_carregar_carteira(const char* cpf){
    carregar_carteira(cpf, &carteira);
}

// ----------------------------------------------------------------------------------------
// FUNÇÃO PARA MOSTRA O SALDO DA CARTEIRA

void load_carteira(const char* cpfL, Carteira* carteira) {
    char nome_arq_c[50];
    snprintf(nome_arq_c, sizeof(nome_arq_c), "%s_carteira.txt", cpfL);

    FILE* file = fopen(nome_arq_c, "r");
    if (file == NULL) {
        // Se o arquivo não existir, cria um novo
        printf("Bem-vindo novo Investidor! Criando sua carteira...\n");

        // temporizador
        int t = 5; 
        while (t > 0) {
            sleep(1);             
            for (int i = 0; i < t; i++) {
                printf("."); 
            }
            printf("\n"); 
            t--; 
        }


        carteira->real = 0.0;           // inicializa o real como 0
        carteira->totalCriptos = 0;     // inicializas as cripto como 0

        file = fopen(nome_arq_c, "w");
        if (file == NULL) {
            printf("Erro ao criar arquivo de carteira!\n");
            return;
        }

        fprintf(file, "Reais: %.2f\n", carteira->real);
        fclose(file);

        return;
    }
    fscanf(file, "Reais: %f\n", &carteira->real);

    carteira->totalCriptos = 0;
    while (fscanf(file, "%49[^:]: %f\n", 
                  carteira->criptos[carteira->totalCriptos].nome, &carteira->criptos[carteira->totalCriptos].valor) == 2) {
        carteira->totalCriptos++;
    }

    fclose(file);
}

// ----------------------------------------------------------------------------------------
// FUNÇÃO PARA EXIBIR A CARTEIRA

void puxar_carteira(const char* cpf) {
    Carteira carteira;

    load_carteira(cpf, &carteira);

    // Exibe o saldo em reais
    printf("Saldo em reais: R$ %.2f\n", carteira.real);

    // Exibe as criptomoedas
    printf("Criptomoedas:\n");
    for (int i = 0; i < carteira.totalCriptos; i++) {
        printf("%s: %.4f\n", carteira.criptos[i].nome, carteira.criptos[i].valor);
    }
}
// ----------------------------------------------------------------------------------------
// FUNÇÃO SALVAR EXTRATO

void save_extrato(const char* cpf, const char* dataExt, double valorExt, const char* descExt){
    struct extrato e;

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

    fseek(file, 0, SEEK_END);
    long tam_arq = ftell(file);
    totExt = tam_arq / sizeof(struct extrato);

    extLer = totExt > 100 ? 100: totExt;

    //move o ponteiro para a direita do arquivo
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

void consultar_saldo(const char* cpf) {
    char nome_arq_c[50];
    snprintf(nome_arq_c, sizeof(nome_arq_c), "%s_carteira.txt", cpf);

    FILE* file = fopen(nome_arq_c, "r");
    if (file == NULL) {
        printf("Investidor não encontrado! Criando sua carteira...\n");
        return;
    }

    // criaçãoação da estrutura 
    Carteira carteira;
    int totalCriptos = 0;

    fscanf(file, "Reais: %f\n", &carteira.real);

    printf("Saldo em reais lido: R$ %.2f\n", carteira.real);

    // leitura dos saldos das criptomoedas
    while (fscanf(file, "%49s: %f\n", carteira.criptos[totalCriptos].nome, &carteira.criptos[totalCriptos].quantidade) == 2) {
        printf("Cripto %d lida: %s - %.4f\n", totalCriptos + 1, carteira.criptos[totalCriptos].nome, carteira.criptos[totalCriptos].quantidade);  // Depuração
        totalCriptos++;
        if (totalCriptos >= MAX_CRIPTOS) break;  // Limita o número de criptomoedas
    }

    fclose(file);

    printf("***********************************************************************\n");
    printf("Saldo do investidor %s:\n", cpf);
    printf("Saldo em Reais: R$ %.2f\n", carteira.real);

    if (totalCriptos > 0) {
        for (int i = 0; i < totalCriptos; i++) {
            printf("Saldo de %s: %.4f\n", carteira.criptos[i].nome, carteira.criptos[i].quantidade);
        }
    } else {
        printf("O investidor não possui criptomoedas.\n");
    }

    printf("***********************************************************************\n");
}

// ----------------------------------------------------------------------------------------
// DEPOSITAR
void depositar(const char* cpf, float deposito) {
    char nome_arq_c[50];
    snprintf(nome_arq_c, sizeof(nome_arq_c), "%s_carteira.txt", cpf);

    FILE* file = fopen(nome_arq_c, "r+");  
    if (file == NULL) {
        printf("Erro: Arquivo da carteira não encontrado!\n");
        return;
    }

    float saldoAtual;
    char linha[100];
    char criptos[1000] = "";  

    // Lê a linha do saldo em reais
    if (fgets(linha, sizeof(linha), file) != NULL) {
        sscanf(linha, "Reais: %f", &saldoAtual);  
    } else {
        printf("Erro ao ler o saldo atual.\n");
        fclose(file);
        return;
    }

    saldoAtual += deposito;

    while (fgets(linha, sizeof(linha), file) != NULL) {
        strcat(criptos, linha); 
    }

    rewind(file);
    fprintf(file, "Reais: %.2f\n", saldoAtual);
    fprintf(file, "%s", criptos);
    fclose(file);  

    printf("Valor depositado: R$ %.2f\n", deposito);
    printf("Novo saldo em reais: R$ %.2f\n", saldoAtual);


    struct extrato e;
    const char* dataAtual = "2024-11-19";  
    snprintf(e.dataExt, sizeof(e.dataExt), "%s", dataAtual);
    e.valorExt = deposito;
    snprintf(e.descExt, sizeof(e.descExt), "Depósito realizado");
    e.tipoExt = 2;  


    char nome_arq_ext[50];
    snprintf(nome_arq_ext, sizeof(nome_arq_ext), "%s_extrato.bin", cpf);

    FILE *file_ext = fopen(nome_arq_ext, "ab");  
    if (file_ext == NULL) {
        printf("Erro ao abrir o arquivo de extrato!\n");
        return;
    }

    fwrite(&e, sizeof(struct extrato), 1, file_ext);
    fclose(file_ext);

    printf("Depósito de R$ %.2f realizado com sucesso!\n", deposito);
}
// ----------------------------------------------------------------------------------------
// SACAR

void sacar(const char* cpf) {
    char nome_arq_c[50];
    snprintf(nome_arq_c, sizeof(nome_arq_c), "%s_carteira.txt", cpf);

    FILE* file = fopen(nome_arq_c, "r+");  
    if (file == NULL) {
        printf("Erro: Arquivo da carteira não encontrado!\n");
        return;
    }

    float saldoAtual;
    char linha[100];
    char criptos[1000] = "";  

    if (fgets(linha, sizeof(linha), file) != NULL) {
        sscanf(linha, "Reais: %f", &saldoAtual); 
    } else {
        printf("Erro ao ler o saldo atual.\n");
        fclose(file);
        return;
    }

    float saque;
    printf("Digite o valor para saque: ");
    scanf("%f", &saque);

    if (saldoAtual < saque) {
        printf("Erro: Saldo insuficiente para o saque de R$ %.2f\n", saque);
        fclose(file);
        return;
    }

    saldoAtual -= saque;

    while (fgets(linha, sizeof(linha), file) != NULL) {
        strcat(criptos, linha);  
    }

    rewind(file);
    fprintf(file, "Reais: %.2f\n", saldoAtual);
    fprintf(file, "%s", criptos);

    fclose(file); 

    printf("Saque de R$ %.2f realizado com sucesso!\n", saque);
    printf("Novo saldo em reais: R$ %.2f\n", saldoAtual);

    struct extrato e;
    const char* dataAtual = "2024-11-19";  
    snprintf(e.dataExt, sizeof(e.dataExt), "%s", dataAtual);
    e.valorExt = saque;
    snprintf(e.descExt, sizeof(e.descExt), "Saque realizado");
    e.tipoExt = 1;  

    char nome_arq_ext[50];
    snprintf(nome_arq_ext, sizeof(nome_arq_ext), "%s_extrato.bin", cpf);

    FILE *file_ext = fopen(nome_arq_ext, "ab"); 
    if (file_ext == NULL) {
        printf("Erro ao abrir o arquivo de extrato!\n");
        return;
    }

    fwrite(&e, sizeof(struct extrato), 1, file_ext);
    fclose(file_ext);

    printf("Saque de R$ %.2f realizado com sucesso!\n", saque);
}

void comprarCripto(const char* cpf) {
    Cripto criptos[MAX_CRIPTOS];
    int totalCriptos = ler_criptos(criptos, MAX_CRIPTOS);  

    if (totalCriptos == 0) {
        printf("Nenhuma criptomoeda cadastrada!\n");
        return;
    }

    printf("***********************************************************************\n");
    printf("Lista de criptomoedas disponíveis:\n");
    for (int i = 0; i < totalCriptos; i++) {
        printf("%d - %s // Valor: R$ %.2f // Taxa de Compra: %.2f%%\n", 
               i + 1, criptos[i].nome, criptos[i].valor, criptos[i].taxaCompra * 100);
    }

    int opcao;
    printf("Escolha a criptomoeda que deseja comprar: ");
    scanf("%d", &opcao);

    if (opcao < 1 || opcao > totalCriptos) {
        printf("Opção inválida!\n");
        return;
    }

    Cripto criptoSelecionada = criptos[opcao - 1];
    float valorCompra, taxa, valorTotal, quantidadeComprada;
    char senhaUsuario[12];

    printf("Você escolheu: %s\n", criptoSelecionada.nome);
    printf("Digite o valor em reais que deseja investir: ");
    scanf("%f", &valorCompra);

    taxa = valorCompra * criptoSelecionada.taxaCompra;
    valorTotal = valorCompra + taxa;
    quantidadeComprada = valorCompra / criptoSelecionada.valor;

    printf("***********************************************************************\n");
    printf("Resumo da compra:\n");
    printf("Valor da taxa: R$ %.2f\n", taxa);
    printf("Valor total a ser pago: R$ %.2f\n", valorTotal);
    printf("Quantidade de %s adquirida: %.4f\n", criptoSelecionada.nome, quantidadeComprada);
    printf("***********************************************************************\n");
    printf("Para confirmar a compra, digite sua senha: ");
    scanf("%s", senhaUsuario);

    if (strcmp(senha, senhaUsuario) != 0) {
        printf("Senha incorreta! Operação cancelada.\n");
        return;
    }

    if (valorTotal > carteira.real) {
        printf("Saldo insuficiente para realizar a compra!\n");
        return;
    }

    carteira.real -= valorTotal;

    int criptoExistente = 0;
    for (int i = 0; i < carteira.totalCriptos; i++) {
        if (strcmp(carteira.criptos[i].nome, criptoSelecionada.nome) == 0) {
            carteira.criptos[i].valor += quantidadeComprada; 
            criptoExistente = 1;
            break;
        }
    }


    if (!criptoExistente) {
        if (carteira.totalCriptos < MAX_CRIPTOS) {
            strcpy(carteira.criptos[carteira.totalCriptos].nome, criptoSelecionada.nome);
            carteira.criptos[carteira.totalCriptos].valor = quantidadeComprada;
            carteira.totalCriptos++;
        } else {
            printf("Não foi possível adicionar a criptomoeda. Limite de %d atingido.\n", MAX_CRIPTOS);
            return;
        }
    }

    char nome_arq_c[50];
    snprintf(nome_arq_c, sizeof(nome_arq_c), "%s_carteira.txt", cpf);

    FILE* file = fopen(nome_arq_c, "r+"); 
    if (file == NULL) {
        printf("Erro ao abrir o arquivo da carteira para atualização!\n");
        return;
    }

    fprintf(file, "Reais: %.2f\n", carteira.real);
    for (int i = 0; i < carteira.totalCriptos; i++) {
        fprintf(file, "%s: %.4f\n", carteira.criptos[i].nome, carteira.criptos[i].valor);
    }

    fclose(file);

    struct extrato e;
    const char* dataAtual = "2024-11-19"; 
    snprintf(e.dataExt, sizeof(e.dataExt), "%s", dataAtual);
    e.valorExt = valorTotal;
    snprintf(e.descExt, sizeof(e.descExt), "Compra de %s", criptoSelecionada.nome);
    e.tipoExt = 0;  

    char nome_arq_ext[50];
    snprintf(nome_arq_ext, sizeof(nome_arq_ext), "%s_extrato.bin", cpf);

    FILE *file_ext = fopen(nome_arq_ext, "ab"); 
    if (file_ext == NULL) {
        printf("Erro ao abrir o arquivo de extrato!\n");
        return;
    }

    fwrite(&e, sizeof(struct extrato), 1, file_ext);
    fclose(file_ext);

    printf("Compra de %s realizada com sucesso!\n", criptoSelecionada.nome);
    printf("Saldo restante: R$ %.2f\n", carteira.real);
}

//login ADM
//-------------------------------------------------------------------------------------------
int loginADM(const char* cpf_digitado, const char* senha_digitado, const char* arquivo) {
    FILE *file = fopen(arquivo, "r");

    if (file == NULL) {
        printf("Erro ao acessar os usuarios\n");
        return 0;
    }

    char cpf_a[20], sen_a[20], nome_a[50];
    
    while (fscanf(file, "%s %s", cpf_a, sen_a) == 2) {
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

        //cria um arquivo temporario para armazenar a nova cotaçao
        FILE *tempFile = fopen("cripto_temp.txt", "w");
        if (tempFile == NULL) {
            printf("Erro ao criar o arquivo temporário!\n");
            fclose(file);
            return;
        }

        char nome[50];
        float cotacao, taxaCompra, taxaVenda;
        while (fscanf(file, "%s %f %f %f", nome, &cotacao, &taxaCompra, &taxaVenda) == 4) {
            float variacao = (rand() % 101 - 50) / 1000.0; // Variação entre -5% e +5% na cotacao
            printf("****************************************************\n");
            printf("Atualizando %s:\n", nome);
            printf("  Valor anterior: %.2f\n", cotacao);
            atualizarValor(&cotacao, variacao);
            printf("  Novo valor: %.2f (Variação: %.3f)\n", cotacao, variacao);

            fprintf(tempFile, "%s %.2f %.4f %.4f\n", nome, cotacao, taxaCompra, taxaVenda);
        }

        fclose(file);
        fclose(tempFile);

        // substitui o arq otiginal pelo temp
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

    FILE* cripto = fopen(criptoArq, "r");
    FILE* temp = fopen(tempArq, "w");

    if (cripto == NULL || temp == NULL){
        printf("Erro ao abrir os arquivos\n");
        return;
    }

    while (fgets(linha, sizeof(linha), cripto) != NULL) {
        if (strstr(linha, nomeC) == NULL) {
            fputs(linha, temp); 
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



