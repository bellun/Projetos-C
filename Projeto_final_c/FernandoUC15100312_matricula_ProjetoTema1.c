/* Aluno : Fernando Henrique Antero de Moraes-UC15100312

Sintese
Objetivo: Auxiliar no controle de estoque de uma rede de farmácia determinada, cadastrando os clientes e os medicamentos;

Entrada :Nome da farmacia, dados dos clientes e medicamntos e os dados cadastrados nos relatórios
Saida   : Relatorios de vendas, telas de apresentação, busca ou alteração dos dados cadastrados no sistema
*/

#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include "Funcoes_Basicas.h"
#include "headers.h"
#include "cores.h"
#include "menuVertical.h"
#include "estruturaProjeto.h"
#include "manipulaDadosClientes.c"
#include "manipulaDadosMedicamento.c"
#include "manipulaDadosVendas.c"
#include "manipulaDadosRelatorios.c"
#include "abreArquivo.c"
#include "apresentaMensagem.c"
#include <time.h>



int main(void){
// Declaracoes
    int opcao;
    char nome[76];
#define QTDE_ITENS_MENU 5
    char *itensMenu[]={"Cliente",
                       "Medicamento",
                       "Vendas realizadas",
                       "Relatorios",
                       "Sai do programa"};
#define QTDE_ITENS_MENU1 6
    char *itensMenu1[]={"Cadastrar Cliente",
                        "Alterar Cliente",
                        "Excluir Cliente",
                        "Listar",
                        "Pesquisar Cliente",
                        "Voltar"};

#define QTDE_ITENS_MENU2 6
    char *itensMenu2[]={"Cadastrar Medicamento",
                        "Alterar Medicamento",
                        "Excluir Medicamento",
                        "Listar Medicamentos",
                        "Pesquisar Medicamentos",
                        "Voltar"};
#define QTDE_ITENS_MENU3 4
    char *itensMenu3[]={"Incluir Venda",
                        "Excluir Venda",
                        "Listar Venda",
                        "Voltar"};

#define QTDE_ITENS_MENU4 6
    char *itensMenu4[]={"R1- lista",
                        "R2- nome parcial do mecidamento",
                        "R3- vendas realizada pelo cliente",
                        "R4- venda em determinado periodo",
                        "R5- clientes cadastrados, ordenado",
                        "Voltar"};
    int opcaoCliente,opcaoMedicamento,opcaoVenda;
    char lixo[5];


    system("MODE con cols=168 lines=60");
////NOME DA FARCACIA E O NOME 
    leNomeDaFarmacia(nome);
    do{
        limpaJanela(1,1,60,180,PRETO);
        gotoxy(9,8);
        retornaCor(BRANCO,PRETO);
        printf("%s",nome);
        opcao = menuVertical(QTDE_ITENS_MENU,itensMenu,PRETO,AMARELO,10,10,1,1,BRANCO,PRETO);
        retornaCor(BRANCO,PRETO);

        switch(opcao){
            case 1:
                do{
                    limpaJanela(1,1,60,180,PRETO);
                    gotoxy(9,8);
                    retornaCor(BRANCO,PRETO);
                    printf("%s",nome);
                    opcaoCliente = menuVertical(QTDE_ITENS_MENU1,itensMenu1,PRETO,AMARELO,10,10,1,1,BRANCO,PRETO);
                    retornaCor(BRANCO,PRETO);
                    limpaJanela(1,1,25,80,PRETO);
                    switch(opcaoCliente){
                        case 1:
                            cadastraCliente(nome);
                            break;

                        case 2:
                            alteraCliente(nome);
                            break;

                        case 3:
                            excluiCliente(nome);
                            break;

                        case 4:
                            apresentaClientes(lixo,nome);
                            break;

                        case 5:
                            pesquisaCliente(nome);
                            break;

                        case 6:
                            limpaJanela(1,1,25,80,PRETO);
                            gotoxy(15,6);
                            break;
                    }
                }while(opcaoCliente!=6);
                break;
            case 2:
                do{
                    limpaJanela(1,1,60,180,PRETO);
                    gotoxy(9,8);
                    retornaCor(BRANCO,PRETO);
                    printf("%s",nome);
                    opcaoMedicamento = menuVertical(QTDE_ITENS_MENU2,itensMenu2,PRETO,AMARELO,10,10,1,1,BRANCO,PRETO);
                    retornaCor(BRANCO,PRETO);
                    limpaJanela(1,1,25,80,PRETO);
                    switch(opcaoMedicamento){
                        case 1:
                            cadastraMedicamento(nome);
                            break;

                        case 2:
                            alteraMedicamento(nome);
                            break;

                        case 3:
                            excluiMedicamento(nome);
                            break;

                        case 4:
                            apresentaMedicamento(lixo,nome);
                            break;

                        case 5:
                            pesquisaMedicamento(nome);
                            break;

                        case 6:
                            limpaJanela(1,1,25,80,PRETO);
                            gotoxy(15,6);
                            break;
                    }
                }while(opcaoMedicamento!=6);
                break;

            case 3:
                do{
                    limpaJanela(1,1,25,180,PRETO);
                    gotoxy(9,8);
                    retornaCor(BRANCO,PRETO);
                    printf("%s",nome);
                    opcaoVenda = menuVertical(QTDE_ITENS_MENU3,itensMenu3,PRETO,AMARELO,10,10,1,1,BRANCO,PRETO);
                    retornaCor(BRANCO,PRETO);
                    limpaJanela(1,1,25,80,PRETO);
                    switch(opcaoVenda){
                        case 1:
                            cadastraVenda(nome);
                            break;

                        case 2:
                            excluiVenda(nome);
                            break;

                        case 3:
                            apresentaVenda(nome);
                            break;

                        case 4:
                            limpaJanela(1,1,25,80,PRETO);
                            gotoxy(15,6);
                            break;
                    }
                }while(opcaoVenda!=4);
                break;

            case 4:
                do{
                    limpaJanela(1,1,60,180,PRETO);
                    gotoxy(9,8);
                    retornaCor(BRANCO,PRETO);
                    printf("%s",nome);
                    opcaoVenda = menuVertical(QTDE_ITENS_MENU4,itensMenu4,PRETO,AMARELO,10,10,1,1,BRANCO,PRETO);
                    retornaCor(BRANCO,PRETO);
                    limpaJanela(1,1,25,80,PRETO);
                    switch(opcaoVenda){
                        case 1:
                            funcaoRelatorioR1(nome);
                            break;

                        case 2:
                            funcaoRelatorioR2(nome);
                            break;

                        case 3:
                            funcaoRelatorioR3(nome);
                            break;

                        case 4:
                            funcaoRelatorioR4(nome);
                            break;

                        case 5:
                            funcaoRelatorioR5(nome);
                            break;

                        case 6:
                            limpaJanela(1,1,25,80,PRETO);
                            gotoxy(15,6);
                            break;
                    }
                }while(opcaoVenda!=6);
                break;

            case 5:
                limpaJanela(1,1,25,80,PRETO);
                gotoxy(15,6);
                gotoxy(9,8);
                retornaCor(BRANCO,PRETO);
                fprintf(stdout," Programa encerrado.");
                break;
        }
    }while(opcao != 5);
    getch();
    return 0;
}

