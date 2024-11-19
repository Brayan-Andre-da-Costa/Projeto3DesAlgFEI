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
    float valor;      // Valor atual da criptomoeda
    float taxaCompra; // Taxa de compra
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
    char linha[100]; // Buffer para leitura de cada linha

    while (count < maxCriptos && fgets(linha, sizeof(linha), file) != NULL) {
        if (sscanf(linha, "%49s %f %f", criptos[count].nome, &criptos[count].valor, &criptos[count].taxaCompra) == 3) {
            criptos[count].taxaCompra /= 100.0; // Converter para decimal (exemplo: 2.0% -> 0.02)
            count++;
        }
    }

    fclose(file);
    return count;
}

//vender cripto
//------------------------------------------------------------------------------------------


void venderCripto() {
    Cripto criptos[100]; // Suporte para até 100 criptomoedas
    int totalCriptos = ler_criptos(criptos, 100);

    if (totalCriptos == 0) {
        printf("Nenhuma criptomoeda cadastrada!\n");
        return;
    }

    printf("***********************************************************************\n");
    printf("Lista de criptomoedas disponíveis para venda:\n");
    for (int i = 0; i < totalCriptos; i++) {
        printf("%d - %s // Valor: R$ %.2f // Taxa de Venda: %.2f%%\n", i + 1, criptos[i].nome, criptos[i].valor, criptos[i].taxaCompra * 100);
    }

    int opcao;
    printf("Escolha a criptomoeda que deseja vender: ");
    scanf("%d", &opcao);

    if (opcao < 1 || opcao > totalCriptos) {
        printf("Opção inválida!\n");
        return;
    }

    Cripto criptoSelecionada = criptos[opcao - 1];
    float quantidadeVenda, valorVenda, taxa, valorRecebido;
    char confirmacao;
    char senhaUsuario[12];

    printf("Você escolheu: %s\n", criptoSelecionada.nome);
    printf("Digite a quantidade que deseja vender: ");
    scanf("%f", &quantidadeVenda);

    printf("***********************************************************************\n");
    printf("Insira sua SENHA: ");
    scanf("%s", senhaUsuario);

    if (strcmp(senha, senhaUsuario) != 0) {
        printf("Senha incorreta! Operação cancelada.\n");
        return;
    }

    valorVenda = quantidadeVenda * criptoSelecionada.valor;
    taxa = valorVenda * (criptoSelecionada.taxaCompra / 100);
    valorRecebido = valorVenda - taxa;

    printf("***********************************************************************\n");
    printf("Resumo da venda:\n");
    printf("Valor bruto da venda: R$ %.2f\n", valorVenda);
    printf("Valor da taxa: R$ %.2f\n", taxa);
    printf("Valor líquido recebido: R$ %.2f\n", valorRecebido);
    printf("***********************************************************************\n");
    printf("Você realmente deseja vender %s? (S/N): ", criptoSelecionada.nome);
    scanf(" %c", &confirmacao);

    if (toupper(confirmacao) == 'S') {
        // Aqui, você precisará implementar a verificação de saldo dinâmico
        // e o ajuste do saldo, de forma semelhante ao que fazia com `carteira`.

        if (valorRecebido > carteira.real) { // Exemplo de validação simples
            printf("Saldo insuficiente para realizar a venda!\n");
        } else {
            // Ajuste o saldo do usuário dinamicamente
            carteira.real += valorRecebido;
            printf("Venda de %s realizada com sucesso!\n", criptoSelecionada.nome);
            printf("Saldo atualizado: R$ %.2f\n", carteira.real);

            // Aqui, você pode salvar o extrato da operação
            // save_extrato(cpf, dataExt, quantidadeVenda, "Venda de cripto");
        }
    } else {
        printf("Venda cancelada.\n");
    }
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

void pegarNome(const char* cpf){

        FILE *file = fopen("usuarios.txt", "r");

        char nome_a[15];

        if (file == NULL){
            printf("Erro ao abrir o arquivo\n");
            return;
        } 
        while (fscanf(file, "%s %s %[^\n]", cpf_a, sen_a, nome_a) == 3) {
            // Compara o CPF e a senha digitados com os armazenados no arquivo
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
// FUNÇÃO SALVAR CARTEIRA DO USUARIO

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

    // Salva o saldo em reais
    fprintf(file, "Reais: %.2f\n", carteira->real);

    // Salva as criptomoedas dinamicamente
    fprintf(file, "Criptomoedas:\n");
    for (int i = 0; i < carteira->totalCriptos; i++) {
        fprintf(file, "%s: %.4f\n", carteira->criptos[i].nome, carteira->criptos[i].valor);
    }

    fclose(file);
}

// ----------------------------------------------------------------------------------------
// FUNÇÃO PARA CARREGAR A CARTEIRA
void load_carteira(const char* cpf, Carteira* carteira) {
    char nome_arq_c[50];
    snprintf(nome_arq_c, sizeof(nome_arq_c), "%s_carteira.txt", cpf);

    FILE* file = fopen(nome_arq_c, "r");
    if (file == NULL) {
        // Se o arquivo não existir, cria um novo
        printf("Bem-vindo novo Investidor! Criando sua carteira...\n");

        // Temporizador para simular o processo de criação da carteira
        int t = 5; 
        while (t > 0) {
            sleep(1);             
            for (int i = 0; i < t; i++) {
                printf("."); 
            }
            printf("\n"); 
            t--; 
        }

        // Inicializa os valores da carteira para um novo investidor
        carteira->real = 0.0;           // Inicializa o saldo em reais como 0
        carteira->totalCriptos = 0;     // Não há criptomoedas no início

        // Criação do arquivo de carteira com os valores iniciais
        file = fopen(nome_arq_c, "w");
        if (file == NULL) {
            printf("Erro ao criar arquivo de carteira!\n");
            return;
        }

        // Escreve o saldo inicial e criptomoedas vazias no arquivo
        fprintf(file, "Reais: %.2f\n", carteira->real);
        fclose(file);

        return;
    }

    // Leitura do saldo em reais
    fscanf(file, "Reais: %f\n", &carteira->real);

    // Leitura dos saldos das criptomoedas
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

void consultar_saldo(const char* cpf) {
    char nome_arq_c[50];
    snprintf(nome_arq_c, sizeof(nome_arq_c), "%s_carteira.txt", cpf);

    FILE* file = fopen(nome_arq_c, "r");
    if (file == NULL) {
        printf("Investidor não encontrado! Criando sua carteira...\n");
        return;
    }

    // Criação da estrutura de carteira para armazenar os dados lidos
    Carteira carteira;
    int totalCriptos = 0;

    // Leitura do saldo em reais
    fscanf(file, "Reais: %f\n", &carteira.real);

    // Verifique se a leitura do saldo foi bem-sucedida
    printf("Saldo em reais lido: R$ %.2f\n", carteira.real);

    // Leitura dos saldos das criptomoedas
    while (fscanf(file, "%49s: %f\n", carteira.criptos[totalCriptos].nome, &carteira.criptos[totalCriptos].quantidade) == 2) {
        printf("Cripto %d lida: %s - %.4f\n", totalCriptos + 1, carteira.criptos[totalCriptos].nome, carteira.criptos[totalCriptos].quantidade);  // Depuração
        totalCriptos++;
        if (totalCriptos >= MAX_CRIPTOS) break;  // Limita o número de criptomoedas
    }

    fclose(file);

    // Exibindo os saldos
    printf("***********************************************************************\n");
    printf("Saldo do investidor %s:\n", cpf);
    printf("Saldo em Reais: R$ %.2f\n", carteira.real);

    // Exibe as criptomoedas que o investidor possui
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

    FILE* file = fopen(nome_arq_c, "r+");  // Abre o arquivo para leitura e escrita
    if (file == NULL) {
        printf("Erro: Arquivo da carteira não encontrado!\n");
        return;
    }

    float saldoAtual;
    char linha[100];
    char criptos[1000] = "";  // Variável para armazenar as criptomoedas

    // Lê a linha do saldo em reais
    if (fgets(linha, sizeof(linha), file) != NULL) {
        sscanf(linha, "Reais: %f", &saldoAtual);  // Extrai o saldo atual
    } else {
        printf("Erro ao ler o saldo atual.\n");
        fclose(file);
        return;
    }

    // Atualiza o saldo com o depósito
    saldoAtual += deposito;

    // Lê o restante do arquivo para armazenar as criptomoedas
    while (fgets(linha, sizeof(linha), file) != NULL) {
        strcat(criptos, linha);  // Concatena as linhas com as criptomoedas
    }

    // Volta ao início do arquivo para reescrever o saldo e as criptos
    rewind(file);

    // Reescreve o saldo em reais
    fprintf(file, "Reais: %.2f\n", saldoAtual);

    // Reescreve as criptomoedas no arquivo
    fprintf(file, "%s", criptos);

    fclose(file);  // Fecha o arquivo

    // Exibe o resultado
    printf("Valor depositado: R$ %.2f\n", deposito);
    printf("Novo saldo em reais: R$ %.2f\n", saldoAtual);
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

// Função para comprar criptomoeda
void comprarCripto(const char* cpf) {
    Cripto criptos[MAX_CRIPTOS];
    int totalCriptos = ler_criptos(criptos, MAX_CRIPTOS);  // Lê as criptos disponíveis

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
    char confirmacao;
    char senhaUsuario[12];

    // Carrega a carteira do investidor
    Carteira carteira;
    load_carteira(cpf, &carteira);

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
    printf("Confirme sua senha: ");
    scanf("%s", senhaUsuario);

    // Verifica se a senha está correta
    if (strcmp(senha, senhaUsuario) != 0) {
        printf("Senha incorreta! Operação cancelada.\n");
        return;
    }

    // Verifica se o investidor tem saldo suficiente
    if (valorTotal > carteira.real) {
        printf("Saldo insuficiente para realizar a compra!\n");
        return;
    }

    // Atualiza o saldo em reais
    carteira.real -= valorTotal;

    // Atualiza a quantidade da criptomoeda comprada na carteira
    int criptoExistente = 0;
    for (int i = 0; i < carteira.totalCriptos; i++) {
        if (strcmp(carteira.criptos[i].nome, criptoSelecionada.nome) == 0) {
            carteira.criptos[i].valor += quantidadeComprada; // Incrementa a quantidade
            criptoExistente = 1;
            break;
        }
    }

    // Se a criptomoeda não existe na carteira, adiciona ela
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

    // Atualiza o arquivo diretamente
    char nome_arq_c[50];
    snprintf(nome_arq_c, sizeof(nome_arq_c), "%s_carteira.txt", cpf);

    FILE* file = fopen(nome_arq_c, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo da carteira para atualização!\n");
        return;
    }

    fprintf(file, "Reais: %.2f\n", carteira.real);
    for (int i = 0; i < carteira.totalCriptos; i++) {
        fprintf(file, "%s: %.4f\n", carteira.criptos[i].nome, carteira.criptos[i].valor);
    }

    fclose(file);

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



