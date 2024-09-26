# Projeto 1 - Exchange Criptomoedas - FEI
O Projeto consiste em criar uma exchange de Criptomoeda em linguagem C, a qual deverá ter funcões como: consulta de saldo e extrato, deposito, saque, compra, venda e atualizar a cotação das cirptomoedas. 

A compilaçãp do arquivo está situada somente no projeto.c, a qual importa as funções de outro arquivo a partir de método #include "funcoes.h"

Código para compilação:

1. gcc projeto.c funcoes.c -o projeto
2. ./projeto

# Forma de Uso

1. Ao compilar o arquivo, o usuário deve colocar o seu CPF  e senha CORRETOS.

2. Ao entrar, é disponibilizado um menu denotando todas possibilidades que existem dentro da exchange.
   
   a) Consultar saldo
   b) Consultar Extrato
   c) Depositar
   d) Sacar
   e) Comprar Criptomoedas
   f) Vender Criptomoedas
   g) Atualizar criptomoedas
   h) Sair
   
3. Consultar saldo disponliza a carteira atual do usuário, entre elas, Reais, Bitcoin, Ethereum e Riple.

4. Consultar Extrato mostrará todas as ultimas 100 transações do usuário.

5. Ao selecionar Depositar, é solicitado ao usuário o valor que deseja depoistar, atualizando sua carteira.

6. Ao selecionar Sacar, é solicitado ao usuário o valor a ser sacado, e sua senha de acesso.

7. Em Comprar criptomoedas, o usuário deve selecionar o tipo de cripto que deseja comprar, listadas de 1 a 3, apresentando todas as taxas referentes. Posterior a isso, ele deve inserir o valor em REAIS em que será trocado pela correspondente critomoeada, e calculado a taxa referente. Uma solicitação de senha e uma confirmação serão apresentadas, e em caso de confirmação, a criptomoeda é adicionada em sua carteira, e o real descrementado.

8. A funçao de vender se baseia na anterior(Comprar criptomoeda), porém os valores de taxas, e calculos são diferentes. Nesse caso o user deve inserir a quantidade de CRIPTOMOEDA, para assim calcular esse cima da cotação atual da moeda selecionada. Por fim, a cripto é decrementada e o real somado a sua carteira.

9. Em Atualizar criptomoeda, como o próprio nome diz, ela atualiza a cotação de todos os valores da criptomoedas, aplicando uma variação de -5% e +5%.

10. Pressionar sair, levará o usuário ao encerramento do programa.

# Lista de Participantes

1. Brayan André da Costa. RA 22.124.017-9
2. João Vito Rangel Maciente. RA: 22.124.017-9

