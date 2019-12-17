#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "estruturaProjeto.h"
#include "cores.h"
#include "manipulaDadosVendas.h"
#include "manipulaDadosClientes.h"
//#include "abreArquivo.h"
#include "manipulaDadosRelatorios.h"
#include <string.h>
//#include "respostaSN.h"

//Objetivo:Apresentar todos os dados cadastrados: clientes, medicamentos e vendas
//Parametros: nome e local da farmácia
//Retorno:sem retorno
void funcaoRelatorioR1(char *nome){
	char opcao, lixo[2];
	 
	gotoxy(1,1);
	retornaCor(BRANCO,PRETO);
	printf("%s",nome);
	desenhaMoldura(2,1,10,160,BRANCO,PRETO);
	gotoxy(3,3);
	printf("C - todos os cliente M - todos os medicamento V - todas as vendas: ");
	opcao=getch();
	opcao=toupper(opcao);
	switch(opcao){
		case 'C':
			apresentaClientes(lixo,nome);
		break;
			
		case 'M':
			apresentaMedicamento(lixo,nome);
		break;
		
		case 'V':
			apresentaVenda(nome);
		break;
		
		default:
			printf("apcao invalida, informe novamente.");
			getch();
				
	}	
}
//ESSA FUNÇÃO
// função - lê os dados dos clientes existentes em arquivo colocando-o na memória
//            com alocação dinâmica
// parâmetros - endereço de memória para guardar a qtde de clientes recuperada
// retorno - endereço de memória onde localiza-se os dados recuperados
//            do arquivo ou NULL no caso de insucesso
Medicamento *obtemDadosRelatorioR2(int *qtde){
	FILE *arq;
	Medicamento *medicamento=NULL;
	int i;

    if((arq = abreArquivo("medicamentos.txt","rb",NAO_APRES_MSG)) != NULL){
        if(fseek(arq,0,SEEK_END)==0)
        {
        	*qtde= ftell(arq)/sizeof(Medicamento);
        	medicamento = (Medicamento*) malloc(*qtde * sizeof(Medicamento));
        	if(medicamento == NULL)
        	{
        		apresentaMsgErro("Erro de alocacao","obtemDadosArquivoMedicamento");
        	}                      
        	else
        	{
        		rewind(arq);           
        		if(fread(medicamento,sizeof(Medicamento),*qtde,arq)!=*qtde){
            		apresentaMsgErro("Erro de leitura","obtemDadosArquivoMedicamento");
            		free(medicamento);
            		medicamento = NULL;
            	}             
        	}           
    	}
       if(fclose(arq) != 0){
           apresentaMsgErro("Erro so fechar arquivo","obtemDadosArquivoMedicamento");
        }    
    }
    return medicamento;
}

//Objetivo: Apresentar todos os medicamentos cadastrados pelo fornecimento de sua descrição completa ou parcial
//Parametros:nome e local da farmácia
//Retorno: Sem retorno
void funcaoRelatorioR2(char *Nome){
	Medicamento *medicamento;
	int qtdeMedicamento,matricula,cont=0,i,linha;
	char nome[TAM_NOME],opcao;
	if((medicamento = obtemDadosArquivoMedicamento(&qtdeMedicamento)) != NULL){
	    
		limpaJanela(10,10,14,70,PRETO);
	    fflush(stdin);
	    limpaJanela(1,1,25,80,PRETO); 
	    gotoxy(1,1);
	    retornaCor(BRANCO,PRETO);
	    printf("%s",Nome);
	    desenhaMoldura(2,1,25,160,BRANCO,PRETO);
	    gotoxy(2,3); 
	    fprintf(stdout," Descricao da pesquisar = ");
	    novaFgets(nome, sizeof(nome));
	    strUpper(nome);
	    limpaJanela(3,3,3,79,PRETO); 
	    gotoxy(2,3); 
	    retornaCor(BRANCO,PRETO);
	    fprintf(stdout," Medicamento com a descricao = %s",nome);
	    cont =0;
	    linha = 4;
	    for (i=0;i<qtdeMedicamento;i++){
	    	if(strIstr(medicamento[i].DescricaoMedicamento,nome)!= NULL){
	        	if(linha >= 18){
	        	gotoxy(2,linha);
	        	fprintf(stdout," Tecle qq tecla para continuar\n");
	        	getch();
	        	limpaJanela(4,2,24,159,PRETO);
	        	retornaCor(BRANCO,PRETO);
	        	linha =4;
	        }  
	        gotoxy(2,linha);
	        linha++; 
			                                                      
	        fprintf(stdout,"%-9s - %-50s - %-2d/%2d/%5d - %-10d - %-10f - %-10f\n",medicamento[i].CodigoAlfanumerico,medicamento[i].DescricaoMedicamento,medicamento[i].dia,medicamento[i].mes,medicamento[i].ano,medicamento[i].QuantEsto,medicamento[i].valorUnitarioCompra,medicamento[i].valorUnitarioVenda);
	        cont++;     
	        }
	    }
	    if(cont == 0){
			gotoxy(5,5);
			retornaCor(BRANCO,PRETO); 
	    	fprintf(stdout,"Nao existe medicamento cadastrado\n");
	    }   
	    // libera memória alocada
		free(medicamento);
   } 
   else{
    	desenhaMoldura(10,10,14,70,BRANCO,PRETO);
    	gotoxy(20,12);
    	retornaCor(BRANCO,PRETO);
    	fprintf(stdout,"Nao existe medicamento cadastrado\n");     
   }     
   getch();
}

//Objetivo: Chamar a função que é utilizada para pesquisar vendas e Mostrar os dados de todas as vendas realizadas para um clienteinformado pelo usuário através de sua chave ou parte de seu nome;
//Parametros:nome e local da farmácia
//Retorno:sem retorno
void funcaoRelatorioR3(char *nome){
	pesquisarVendaNome(nome);
	
}
//Objetivo: Buscar vendas dentro de uma data especifica
//Parametros:nome e local da farmácia
//Retorno:sem retorno
void funcaoRelatorioR4(char *nome){

	int dia1=12,dia2=12;
	int mes1=12,mes2=12;
	int ano1,ano2;
	int ret1,ret2;
	float somaVenda=0,somaCompra=0;
	
	FILE *arq;
	Venda *venda;
	char **dados=NULL, aux[7];
	int linha,cont=0,i,qtdeItens,itemSelecionado=0,matriculaSelecionada=0,qtdeAlocada=0,existeErro=0,a=0;
	#define TAM_TEXTO 200
		
	desenhaMoldura(10,10,18,120,BRANCO,PRETO);
	do {
		leInt(&dia1,"digite o dia DE: ",11, 11);
		leInt(&mes1,"digite o mes DE: ",12, 11);
		leInt(&ano1,"digite o ano DE: ",13, 11);
		leInt(&dia2,"digite o dia ATE: ",14, 11);
		leInt(&mes2,"digite o mes ATE: ",15, 11);
		leInt(&ano2,"digite o ano ATE: ",16, 11);
		
		ret1 = valida_data(dia1, mes1, ano1);
		ret2 = valida_data(dia2, mes2, ano2);
		
		if(ret1 == 0 || ret2 == 0) {
			
	    gotoxy(10,9);
		printf("Data invalida, informe novamente ");
		getch();
		textbackground(PRETO);
		gotoxy(11,11); 
		printf("                                                                                        ");
		gotoxy(12,25); 
		printf("                                                                                        ");
		gotoxy(13,25);              
		printf("                                                                                        ");
		desenhaMoldura(10,10,18,70,BRANCO,PRETO);
			
		}
	} while(ret1 == 0 || ret2 == 0);


	limpaJanela(1,1,60,180,PRETO);

	if((venda = obtemDadosArquivoVenda(&cont))!= NULL){        
	    	if(cont != 0){
	          
	        	// carrega o menu vertical
	        	dados = (char**) malloc(sizeof(char*)* (cont+1));   
	        	if(dados != NULL){
	                for(i=0;i<cont;i++){   
	                   dados[i] = (char*) malloc(sizeof(char)*(TAM_TEXTO+1));
	                   if(dados[i] != NULL)
					   {
							desenhaMoldura(10,10,18,120,BRANCO,PRETO);
					   	   
	                       if(((ano1 == venda[i].ano && mes1 <= venda[i].mes && dia1 <= venda[i].dia) || (ano1 < venda[i].ano)) && ((ano2 == venda[i].ano && mes2 >= venda[i].mes && dia2 >= venda[i].dia) ||(ano2 > venda[i].ano))) {
						        sprintf(dados[a],"%-14s - %-11s - %-2d/%2d/%4d    - %-11d - %-18f - %-10f\n",formataCPF(venda[i].IdentificacaoDoClient),venda[i].IdentificacaoDoMedicamento,venda[i].dia,venda[i].mes,venda[i].ano,venda[i].QuantidadeVendida,venda[i].VaUnitarioCompra,venda[i].VaUnitarioVenda);
								qtdeAlocada++;
								somaVenda+=venda[i].VaUnitarioVenda;
								somaCompra+=venda[i].VaUnitarioCompra;
	                            a++;
						   
						   }                    
						    
	                   }
	                   else{
	                       apresentaMsgErro(" Erro ao alocar memoria para um elemento","apresentaVenda");
	                       existeErro = 1;
	                	}
	                }    
	        	}
	        	else{
	            	apresentaMsgErro(" Erro ao alocar memoria ","apresentaVenda");
	            	existeErro = 1;
	    		}
	          
	        	// libera memória alocada
	        	free(venda);
	          
	        	if(!existeErro){
	            	for (i=0;i<a;i+=10){  
	
		            	qtdeItens = a -i > 10? 10: a-i;
		                gotoxy(4,2);
			    		retornaCor(BRANCO,PRETO);
			    		printf("%s",nome);
			    		gotoxy(4,a+6);
			    		printf("Total de compra----------%.3f",somaCompra);
			    		gotoxy(4,a+7);
		        		printf("Total de venda----------%.3f",somaVenda);
		        		gotoxy(4,3);
		        		printf("%-15s - %-11s - %-11s - %-11s - %-18s - %-10s\n","CFP do cliente","Medicamento","Data da venda","Quantidade","Valor Uni/ Compra","Valor Uni/ Venda");
		                itemSelecionado = menuVertical(qtdeItens,&dados[i],VERMELHO,AMARELO,5,5,1,1,BRANCO,BRANCO);
	        		}
	        	}    
	          if(dados !=NULL)
	          {
	                free(dados);           
	          }   
	      }
	    	else{
	    		gotoxy( 10,10);
	        	textbackground(BRANCO);
	        	fprintf(stdout," Nao existem vendas realizada");
	        	getch();
	    	}
		}   
	 
}

//Objetivo:Pesquisar os dados dos clientes cadastrados pelo nome.
//Parametros:nome e local da farmácia
//Retorno:sem retorno
void funcaoRelatorioR5(char *nome){
	pesquisaCliente(nome);
}



//Objetivo: pesquisar uma venda pelo nome
//parametros: nome e local da farmácia
//Retorno: sem retorno
void pesquisarVendaNome(char *nome){
	
Venda *venda;
int qtdeVenda,matricula,cont=0,i,linha,qtdeAlocada,itemSelecionado,qtdeItens,existeErro;
char  **dados=NULL,idCliente[TAM_NOME];
	if((venda = obtemDadosArquivoVenda(&qtdeVenda)) != NULL){
		
		desenhaMoldura(10,10,7,80,BRANCO,PRETO);
    	gotoxy(11,11);
		limpaJanela(10,10,14,70,PRETO);
		// carrega o menu vertical
        dados = (char**) malloc(sizeof(char*)* (qtdeVenda+1)); 
    	fflush(stdin);
    	limpaJanela(1,1,25,80,PRETO); 
    	desenhaMoldura(1,1,7,80,BRANCO,PRETO);
    	gotoxy(2,2); 
    	fprintf(stdout,"id do cliente = ");
    	novaFgets(idCliente, sizeof(idCliente));
    	limpaJanela(2,2,2,79,PRETO); 
    	gotoxy(2,2); 
    	fprintf(stdout," venda com o id do cliente= %s",idCliente);
    	cont =0;
    	linha = 3;
    	system("cls");
    	if(dados != NULL){
        	for (i=0;i<qtdeVenda;i++){
        		if(strIstr(venda[i].IdentificacaoDoClient,idCliente)!= NULL){
        			if(linha >= 18){
		                gotoxy(2,linha);
		                fprintf(stdout," Tecle qq tecla para continuar\n");
		                getch();
		                limpaJanela(3,2,19,79,BRANCO);
		                linha =3;
             		}  
	            	gotoxy(2,linha);
	            	linha++;    
       				dados[cont] = (char*) malloc(sizeof(char)*(TAM_TEXTO+1));
       				if(dados[cont] != NULL)
	   				{
						fflush(stdin);
            			sprintf(dados[cont],"%-11s - %-9s - %-2d/%2d/%4d - %-5d - %-10f - %-10f\n",venda[i].IdentificacaoDoClient,venda[i].IdentificacaoDoMedicamento,venda[i].dia,venda[i].mes,venda[i].ano,venda[i].QuantidadeVendida,venda[i].VaUnitarioCompra,venda[i].VaUnitarioVenda);
    					qtdeAlocada++;
						cont++;                       
       				}
      		 		else{
           				apresentaMsgErro(" Erro ao alocar memoria para um elemento","apresentaMedicamento");
           				existeErro = 1;
    				} 
        		}
        	}
	    }else{
        	apresentaMsgErro(" Erro ao alocar memoria ","apresentaMedicamento");
		}
    	for (i=0;i<cont;i+=10){  

        	qtdeItens = cont -i > 10? 10: cont-i;
            gotoxy(4,3);
    		retornaCor(BRANCO,PRETO);
    		printf("%s",nome);
            itemSelecionado = menuVertical(qtdeItens,&dados[i],VERMELHO,AMARELO,5,5,1,1,BRANCO,BRANCO);
            
		}
		   
		if(dados !=NULL){
    	free(dados);
		}
    	// libera memória alocada
    	free(venda);
	}
   else
   {
    	desenhaMoldura(10,10,14,70,BRANCO,PRETO);
    	gotoxy(20,12);
    	getch();
    	getch();
    	fprintf(stdout,"Nao existe aluno cadastrado\n"); 
		getch();    
   } 
               
}
