# Projeto 3 - Gestão de Investidores e Criptomoedas - FEI

O Projeto consiste em ampliar as funcionalidades do Projeto 1, o sistema possibilita o gerenciamento de investidores e criptomoedas, permitindo o monitoramento e controle da realização de transações financeiras virtuais.

A compilação do arquivo está situada somente no projeto.c e adm.c, a qual importa as funções de outro arquivo a partir de método #include "funcoes.h"

Código para compilação do Investidor:
-> gcc projeto.c funcoes.c -o main
-> /main

Código para compilação do Investidor:
-> gcc adm.c funcoes.c -o projeto
-> /main

# Forma de Uso do Gerente

1. Ao compilar o arquivo, o Gerente deve colocar o seu CPF e senha CORRETOS.

2. Ao entrar, é disponibilizado um menu denotando todas possibilidades que existem dentro da exchange.

  - Cadastrar Investidor
  - Excluir Investidor 
  - Cadastro de Criptomoeda
  - Excluir Criptomoeda
  - Consultar Saldo do Investidor
  - Consultar Extrato do Investidor
  - Atualizar Criptomoedas 
  - Sair

3. Cadastro de Investidor.
   
O gerente pode cadastrar um novo investidor informando os seguintes dados:

-Nome do investidor
-CPF do investidor
-Senha do investidor

4. Excluir Investidor
   
Caso o gerente deseje remover o investidor do sistema, ele pode excluir informando o CPF. O sistema localizará os dados do investidor e exibirá as informações associadas           (Saldo, Extrato). Em seguida, o sistema pedirá uma confirmação para a exclusão, garantindo que o processo seja intencional.

5. Cadastro de Criptomoeda

O sistema permite o cadastro de criptomoedas com as seguintes informações:

Nome da criptomoeda
Cotação inicial da criptomoeda
Taxa de compra da criptomoeda
Taxa de venda da criptomoeda

6. Excluir Criptomoeda

Se necessário, o gerente também permite a exclusão de criptomoedas. O usuário deve fornecer o nome da criptomoeda a ser excluída. O sistema então exibirá os dados da criptomoeda e solicitará uma confirmação antes de removê-la do sistema.

7. Consultar Saldo de um Investidor

Para consultar o saldo de um investidor, o gerente deve fornecer o CPF do investidor, e o sistema retornará o saldo disponível para o investidor utilizar em compras ou transações no mercado.

8. Consultar Extrato de um Investidor

O extrato de um investidor contém um histórico detalhado das transações realizadas, como compras e vendas de criptomoedas, movimentações de saldo e outros eventos. Para acessar o extrato, o gerente deve informar o CPF do investidor, e o sistema exibirá todas as transações realizadas até o momento.

9. Atualizar criptomoeda, como a função do investidor, ela atualiza a cotação de todos os valores da criptomoedas, aplicando uma variação de -5% e +5%.

10. Pressionar sair, levará o usuário ao encerramento do programa.

# Lista de Participantes

- Brayan André da Costa. RA 22.124.017-9
- João Vitor Rangel Maciente. RA: 22.124.017-9
