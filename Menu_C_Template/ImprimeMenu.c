#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//Teclados
#define ACIMA 72
#define ABAIXO 80
#define ESC 27
#define ENTER 13
#define MAX_OPCOES 10
#define NOME_OPCOES 100
#define IMG_OP 16

//Protótipo
int menu(int qtOp,char opcoes[][NOME_OPCOES],char *apresentaMenu);


//Principal
int main(){
	//Variaveis
	char menuTeste[3][NOME_OPCOES];
	int opMenu;
	
	//Texto do menu
	strcpy(menuTeste[0],"1-Clientes\n");
	strcpy(menuTeste[1],"2-Medicamentos\n");
	strcpy(menuTeste[2],"3-Sair\n");
	
	//Desenvolvimento
	system("color a9");			//Cor de fundo e cor da letra  
	
	opMenu = menu(3,menuTeste,"Menu Principal");	
	printf("%d",opMenu);	

	//finalização
	printf("\n");
	system("pause");
	return 0;
}
//Funções



//Imprime e informa opção escolhida de um menu de opções
//Recebe a quantidade de opções, o endereçamento de uma matriz com as opções armazenadas e endereçamento da string com o título do menu;
//Retorna a opção escolhida, 0 em caso de finalização do programa pelo ESC;
int menu(int qtOp,char opcoes[][NOME_OPCOES],char *apresentaMenu){
	//variaveis
	int tecla = -1,opAtual = 1,cont;	// a tecla vai receber a numeração do botão clicado de acordo com a  tabela ASCII
	
	//desenvolvimento
	do{
		//Impressão inicial do menu
		if(tecla == -1){
			printf("\t\t\t%s\n",apresentaMenu);
			
			for(cont = 0;cont<qtOp;cont++){
				if(opAtual == cont+1){
					printf(" %c %s",IMG_OP,opcoes[cont]);
				}else{
					printf("   %s",opcoes[cont]);
				}
				
			}	
		}
		
		//leitura do teclado
		tecla = getch();
		system("cls");
		
		//imprimindo menu
		if(tecla == ACIMA){
			//Informar posição atual do cursor
			if(opAtual > 1){
				opAtual--;
			}
			
			//Imprimindo o menu
			printf("\t\t\t%s\n",apresentaMenu);
			for(cont = 0;cont<qtOp;cont++){
				if(opAtual == cont+1){
					printf(" %c %s",IMG_OP,opcoes[cont]);
				}else{
					printf("   %s",opcoes[cont]);
				}
				
			}	
			
		}else if(tecla == ABAIXO){
			
			//informar posição atual do cursor
			if(opAtual < qtOp){
				opAtual++;
			}
			
			
			//Imprimindo o menu
			printf("\t\t\t%s\n",apresentaMenu);
			for(cont = 0;cont<qtOp;cont++){
				if(opAtual == cont+1){
					printf(" %c %s",IMG_OP,opcoes[cont]);
				}else{
					printf("   %s",opcoes[cont]);
				}
				
			}	
		
		}
		
		
		
	}while(tecla != ESC && tecla != ENTER);
	
	if(tecla == ESC){
		return 0;
	}
	
	return opAtual;
		
}
