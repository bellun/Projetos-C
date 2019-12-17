#include <stdio.h>
#include <string.h>
#include <time.h>
#include "estruturaProjeto.h"
#include "headers.h"
#include "cores.h"
#include "abreArquivo.h"
#include "manipulaDadosVendas.h"
#include "manipulaDadosClientes.h"
#include "manipulaDadosMedicamento.h"
#include <string.h>
#include "respostaSN.h"
#define TAM_TEXTO 200

//Objetivo: Cadastrar uma venda
//Parametros: nome, local da farmacia 
//Retorno:sem retorno
void cadastraVenda(char *nome){
	
	FILE * arq;
	Venda venda;
	int seq1,seq2,ret=1,quantEstoq,Dia,Mes,Ano;
	gotoxy(10,9);
	retornaCor(BRANCO,PRETO);
	printf("%s",nome);
	desenhaMoldura(10,10,18,70,BRANCO,PRETO);
	gotoxy(11,11);
  
	fflush(stdin);
	gotoxy(11,11);
	fprintf(stdout,"CPF do cliente = ");		  
	novaFgets(venda.IdentificacaoDoClient, sizeof(venda.IdentificacaoDoClient));	//Validar codigo alfa numerico
	
	seq1=pesquisaMatriculaCliente(venda.IdentificacaoDoClient);
	if(seq1 == 0){
		gotoxy(11,11); 
		printf("cliente nao cadastrado");
		getch();
    	textbackground(PRETO);
		gotoxy(11,11); 
		printf("                                                           ");
		desenhaMoldura(10,10,18,70,BRANCO,PRETO);  
	}else {
		fflush(stdin);
		gotoxy(11,12);
		fprintf(stdout,"ID do medicamento = ");		  
		novaFgets(venda.IdentificacaoDoMedicamento, sizeof(venda.IdentificacaoDoMedicamento));
		seq2 = pesquisaCodigoMedicamento(venda.IdentificacaoDoMedicamento,&quantEstoq,&venda.VaUnitarioCompra,&Dia,&Mes,&Ano);
		if(quantEstoq!=0){
			//Pega a data do sistema
			obtemDataHoraAtual(&venda.dia,&venda.mes,&venda.ano);
			if((Ano>venda.ano)|| (Ano==venda.ano && Mes>venda.mes) || (Ano==venda.ano && Mes==venda.mes && Dia>venda.dia)){
						if(seq2 == 0){
							gotoxy(11,12); 
							printf("medicamento nao cadastrado");
							getch();
				    		textbackground(PRETO);
							gotoxy(11,12); 
							printf("                                                           ");
							desenhaMoldura(10,10,18,70,BRANCO,PRETO);  
						}else{
							do{
								fflush(stdin);	  
								leInt(&venda.QuantidadeVendida,"Quantidade vendida  = ", 13, 11);
								if(venda.QuantidadeVendida>quantEstoq){
									gotoxy(11,13);
									printf("Numero mair que a do estoque:A quantidade em estoque e de %d",quantEstoq);
									getch();
					    			textbackground(PRETO);
									gotoxy(11,13); 
									printf("                                                           ");
									desenhaMoldura(10,10,18,70,BRANCO,PRETO);
								}
								if(venda.QuantidadeVendida<1){
									gotoxy(11,13);
									printf("numero invalido,informe novamente");
									getch();
					    			textbackground(PRETO);
									gotoxy(11,13); 
									printf("                                                           ");
									desenhaMoldura(10,10,18,70,BRANCO,PRETO);						
								}
							}while(venda.QuantidadeVendida>quantEstoq || venda.QuantidadeVendida<1);
							
							gotoxy(11,14);
							fprintf(stdout,"Valor unitario da compra = %.3f",venda.VaUnitarioCompra);	
							getch();
							
							do{
								fflush(stdin);	  
								leFloat(&venda.VaUnitarioVenda,"Valor unitario da venda = ", 15, 11);
								if(venda.VaUnitarioVenda<0){
									gotoxy(11,15);
									printf("numero invalido,informe novamente");
									getch();
					    			textbackground(PRETO);
									gotoxy(11,15); 
									printf("                                                           ");
									desenhaMoldura(10,10,18,70,BRANCO,PRETO);						
								}
								
							}while(venda.VaUnitarioVenda<0);
							//Apresenta a hora do sistema
							gotoxy(11,16);
							printf("Data da compra: %d/%d/%d",venda.dia,venda.mes,venda.ano);
							getch();
							//FAZER O CONTROLE QUE PARA NÃO EXCLUIR O CLIENTE
							alteraControleCliente(venda.IdentificacaoDoClient);
							//FAZER O CONTROLE QUE PARA NÃO EXCLUIR O MEDICAMENTO
							alteraControleMedicamento(venda.IdentificacaoDoMedicamento);
							//ALTERAR A QUANTIDADE DE ESTOQUE
							alteraMedicamentoEstoque(venda.IdentificacaoDoMedicamento,venda.QuantidadeVendida);
							//SALVAR NO ARQUIVO	
							arq = abreArquivo("vendas.txt","ab",APRES_MSG);
						    if(arq != NULL){
						        if(fwrite(&venda,sizeof(Venda),1,arq)!= 1){
						            apresentaMsgErro(" Erro ao cadastrar venda no arquivo","cadastraVenda");
						        }
						        else
									gotoxy(11,17);
						        	fprintf(stdout," venda cadastrado com sucesso");
									if(fclose(arq) != 0)
						    			apresentaMsgErro(" Erro ao fechar arquivo vendas.txt","cadastraVenda");
						    }
																		
						}
						
					}else{
						textbackground(PRETO);
						gotoxy(11,12); 
						printf("                                                           ");
						desenhaMoldura(10,10,18,70,BRANCO,PRETO);
						gotoxy(11,12); 
						printf("Produto vencido");	
					}
		}else{
			textbackground(PRETO);
			gotoxy(11,12); 
			printf("                                                           ");
			desenhaMoldura(10,10,18,70,BRANCO,PRETO);
			gotoxy(11,12); 
			printf("estoque esgotado");			
		}
		getch();
	}
}
// função - pesquisar o codigo no arquivo com os dados dos medicamentos
// parâmetros - codigo, a quantidade em estoque,o valor unitarioda compra,o dia, mes ano do vencimento
// retorno - 0 - cliente não cadastrado, qq número - sequencial no arquivo do aluno
int pesquisaCodigoMedicamento(char *codigo,int *quantEstoq,float *compra,int *dia,int *mes, int *ano){
	FILE *arq;
	Medicamento medicamento;
	int seq=0,cont=0;
    arq = abreArquivo("medicamentos.txt","rb",NAO_APRES_MSG);
	if(arq != NULL){
    	while(!feof(arq)){
    
        	if(fread(&medicamento,sizeof(Medicamento),1,arq) == 1){
        		cont++;
            	if(strcmp(medicamento.CodigoAlfanumerico,codigo)==0){
            		*quantEstoq=medicamento.QuantEsto;
            		*compra=medicamento.valorUnitarioCompra;
            		*dia=medicamento.dia;
            		*mes=medicamento.mes;
            		*ano=medicamento.ano;
            		seq = cont;
            		break;
            	}
        	}
    	}     
       if(fclose(arq) != 0)
          apresentaMsgErro(" Erro ao fechar arquivo medicamento.txt","pesquisaMatriculaMedicamento");
    }
   return seq;
}
/***
*  Nome      : obtemDataHoraAtual                          *
*  Descricao : Obtem a data e hora atual do sistema        *
*  Parâmetros:                                             *
*             dia, mes,ano, hora,                          *
*  Retorno   : Nenhum                                      * 
**/ 
void obtemDataHoraAtual(int *dia, int * mes, int *ano){
	time_t t;
	struct tm *dataAtual;
	t = time(NULL);
	dataAtual = localtime(&t);

	*dia      = dataAtual->tm_mday;
	*mes      = dataAtual->tm_mon+1;
	*ano      = 1900+dataAtual->tm_year;

}

// função - Alterar a variavel controle do cliente para não ser excluido
// parâmetros - o id do cliente
// retorno - Nenhum
void alteraControleCliente(char *idCliente){
	FILE * arq;
	Cliente cliente;
	int seq;
	char opcao;
    
    // verifica se cliente ja cadastrado
    seq = pesquisaMatriculaCliente(idCliente);
	if(seq != 0){
	    if(leRegCliente(seq,&cliente)){  
		 
	        arq = abreArquivo("clientes.txt","r+b",APRES_MSG);
	        if(arq != NULL){ 
				fflush(stdin);
     			cliente.controleCompras=1+cliente.controleCompras;
				      						
	                // posiciona para escrita
	                if(fseek(arq,(seq-1)*sizeof(Cliente),SEEK_SET) == 0)
	                {        
	                   if(fwrite(&cliente,sizeof(cliente),1,arq) == 1)
	                   {
	                     
	                   }
	                   else
	                     apresentaMsgErro ("Erro ao gravar dados","alteraControleCliente");
	                 }
	                 else
	                     apresentaMsgErro ("Erro ao posicionar arquivo ","alteraControleCliente");
	                       
	            
	           }
	           if(fclose(arq) != 0)
	              apresentaMsgErro ("Erro ao fechar arquivo","alteraControleCliente");
	      }
	  }  
	  else
	  {
	    gotoxy(11,13);  
	    retornaCor(BRANCO,PRETO);
	    getch();
	  }

  
}

// função - Alterar a variavel de estoque do medicamento
// parâmetros - codigo do medicamento e a quantidade em estoque retirada
// retorno - Nenhum
void alteraMedicamentoEstoque(char *codigo,int quantEstoque){
	
	FILE * arq;
	Medicamento medicamento;
	int seq;
	char opcao;
	desenhaMoldura(10,10,18,70,BRANCO,PRETO);


    // verifica se cliente ja cadastrado
	seq = pesquisaCodigo(codigo);
		if(seq != 0){
	    	if(leRegMedicamento(seq,&medicamento)){
	        	arq = abreArquivo("medicamentos.txt","r+b",APRES_MSG);
	        	if(arq != NULL){ 
	        		fflush(stdin);
	        		medicamento.QuantEsto=medicamento.QuantEsto-quantEstoque;
     				
     				// posiciona para escrita
	                if(fseek(arq,(seq-1)*sizeof(Medicamento),SEEK_SET) == 0)
	                {        
	                   if(fwrite(&medicamento,sizeof(medicamento),1,arq) == 1)
	                   {
	                     
	                   }
	                   else
	                     apresentaMsgErro ("Erro ao gravar dados","alteraMedicamentoEstoque");
	                 }
	                 else
	                     apresentaMsgErro ("Erro ao posicionar arquivo ","alteraMedicamentoEstoque");
	           }
	           
	           if(fclose(arq) != 0)
	              apresentaMsgErro ("Erro ao fechar arquivo","alteraMedicamentoEstoque");
	    	}
		}  
		else{
	    	gotoxy(11,13);  
	    	retornaCor(BRANCO,PRETO);
	    	getch();
		}
}

// função - Apresenta toda as vendas cadastradas
// parâmetros - nome da empresa
// retorno - Nenhum
void apresentaVenda(char *nome){
	FILE *arq;
	Venda *venda;
	char **dados=NULL, aux[7];
	int linha,cont=0,i,qtdeItens,itemSelecionado=0,matriculaSelecionada=0,qtdeAlocada=0,existeErro=0;
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
                        sprintf(dados[i],"%-14s - %-11s - %-2d/%2d/%4d    - %-11d - %-18f - %-10f\n",formataCPF(venda[i].IdentificacaoDoClient),venda[i].IdentificacaoDoMedicamento,venda[i].dia,venda[i].mes,venda[i].ano,venda[i].QuantidadeVendida,venda[i].VaUnitarioCompra,venda[i].VaUnitarioVenda);
                       qtdeAlocada++;                     
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
            	for (i=0;i<cont;i+=50){  

	            	qtdeItens = cont;
	                gotoxy(4,2);
		    		retornaCor(BRANCO,PRETO);
		    		printf("%s",nome);
		    		gotoxy(4,3);
		    		printf("%-15s - %-11s - %-11s - %-11s - %-18s - %-10s\n","CFP do cliente","Medicamento","Data da venda","Quantidade","Valor Uni/ Compra","Valor Uni/ Venda");
	                itemSelecionado = menuVertical(qtdeItens,&dados[i],VERMELHO,AMARELO,5,5,1,1,BRANCO,BRANCO);
        		}
        	}    
          if(dados !=NULL)
          {
             for (i=0;i<qtdeAlocada;i++)
                 free(dados[i]); 
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

// função - lê os dados das vendas existentes em arquivo colocando-o na memória
//            com alocação dinâmica
// parâmetros - endereço de memória para guardar a qtde de clientes recuperada
// retorno - endereço de memória onde localiza-se os dados recuperados
//            do arquivo ou NULL no caso de insucesso
Venda * obtemDadosArquivoVenda(int *qtde){
	FILE *arq;
	Venda *venda=NULL;
	int i;

    if((arq = abreArquivo("vendas.txt","rb",NAO_APRES_MSG)) != NULL){
        if(fseek(arq,0,SEEK_END)==0)
        {
        	*qtde= ftell(arq)/sizeof(Venda);
        	venda = (Venda*) malloc(*qtde * sizeof(Venda));
        	if(venda == NULL)
        	{
        		apresentaMsgErro("Erro de alocacao","obtemDadosArquivoVenda");
        	}                      
        	else
        	{
        		rewind(arq);           
        		if(fread(venda,sizeof(Venda),*qtde,arq)!=*qtde){
            		apresentaMsgErro("Erro de leitura","obtemDadosArquivoVenda");
            		free(venda);
            		venda = NULL;
            	}             
        	}           
    	}
       if(fclose(arq) != 0){
           apresentaMsgErro("Erro so fechar arquivo","obtemDadosArquivoVenda");
        }    
    }
    return venda;
}

// função - pesquisa uma venda pelo id do cliente ou pelo id do medicamento ou pela data d
// parâmetros - nome da empresa
// retorno - petorna a posição da venda selecionada
int pesquisarVenda(char *nome){
	
Venda *venda;
int qtdeVenda,qtdeMedicamento,Dia,Mes,Ano,matricula,cont=0,i,linha,qtdeAlocada,itemSelecionado,qtdeItens,existeErro,itemSelecionado1;
char  **dados=NULL,idMedicamento[TAM_NOME],idCliente[TAM_NOME],opcao;
	if((venda = obtemDadosArquivoVenda(&qtdeVenda)) != NULL){
		
		desenhaMoldura(10,10,20,80,BRANCO,PRETO);
    	gotoxy(11,11);
    	do{
    		fprintf(stdout," C - id do cliente ou M - id do medicamento ou D - data de vencimento");
			opcao = toupper(getch());
     	}while(opcao != 'C' && opcao != 'M' && opcao != 'D');
		limpaJanela(10,10,14,70,PRETO);
		// carrega o menu vertical
        dados = (char**) malloc(sizeof(char*)* (qtdeVenda+1)); 
		switch(opcao){
			case 'C':
		    	fflush(stdin);
		    	limpaJanela(1,1,25,80,PRETO); 
		    	desenhaMoldura(1,1,20,80,BRANCO,PRETO);
		    	gotoxy(2,2); 
		    	fprintf(stdout,"id do cliente = ");
		    	novaFgets(idCliente, sizeof(idCliente));
		    	limpaJanela(2,2,2,79,PRETO); 
		    	gotoxy(2,2); 
		    	fprintf(stdout," venda com o id do cliente= %s",idCliente);
		    	cont =0;
		    	linha = 3;
		    	if(dados != NULL){
		        	for (i=0;i<qtdeVenda;i++){
		        		if(strIstr(venda[i].IdentificacaoDoClient,idCliente)!= NULL){
		        			if(linha >= 18){
				                gotoxy(2,linha);
				                fprintf(stdout," Tecle qq tecla para continuar\n");
				                getch();
				                limpaJanela(3,2,19,79,PRETO);
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
	                gotoxy(4,2);
		    		retornaCor(BRANCO,PRETO);
		    		printf("%s",nome);
		    		gotoxy(4,3);
		    		printf("%-15s - %-11s - %-11s - %-11s - %-18s - %-10s\n","CFP do cliente","Medicamento","Data da venda","Quantidade","Valor Uni/ Compra","Valor Uni/ Venda");
	                itemSelecionado = menuVertical(qtdeItens,&dados[i],VERMELHO,AMARELO,5,5,1,1,BRANCO,BRANCO);
	                itemSelecionado1=pesquisaClienteNaVenda(idCliente, itemSelecionado);
	                
        		}
				   
    			if(dados !=NULL){
            	free(dados);
    			}
	        break;
	        
	        case 'M':
		    	fflush(stdin);
		    	limpaJanela(1,1,25,80,PRETO); 
		    	desenhaMoldura(1,1,20,80,BRANCO,PRETO);
		    	gotoxy(2,2); 
		    	fprintf(stdout,"id do medicamento = ");
		    	novaFgets(idMedicamento, sizeof(idMedicamento));
		    	limpaJanela(2,2,2,79,PRETO); 
		    	gotoxy(2,2); 
		    	fprintf(stdout," venda com o id do medicamento= %s",idMedicamento);
		    	cont =0;
		    	linha = 3;
		    	if(dados != NULL){
		        	for (i=0;i<qtdeVenda;i++){
		        		if(strIstr(venda[i].IdentificacaoDoMedicamento,idMedicamento)!= NULL){
		        			if(linha >= 18){
				                gotoxy(2,linha);
				                fprintf(stdout," Tecle qq tecla para continuar\n");
				                getch();
				                limpaJanela(3,2,19,79,PRETO);
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
	                gotoxy(4,2);
		    		retornaCor(BRANCO,PRETO);
		    		printf("%s",nome);
		    		gotoxy(4,3);
		    		printf("%-15s - %-11s - %-11s - %-11s - %-18s - %-10s\n","CFP do cliente","Medicamento","Data da venda","Quantidade","Valor Uni/ Compra","Valor Uni/ Venda");
	                itemSelecionado = menuVertical(qtdeItens,&dados[i],VERMELHO,AMARELO,5,5,1,1,BRANCO,BRANCO);
	                itemSelecionado1=pesquisaMedicamentoNaVenda(idMedicamento, itemSelecionado);
        		}
				   
    			if(dados !=NULL){
            	free(dados);
    			}
	        break;
	        
	        case 'D':
		    	fflush(stdin);
		    	limpaJanela(1,1,25,80,PRETO); 
		    	desenhaMoldura(1,1,20,80,BRANCO,PRETO);
		    	gotoxy(2,2); 
		    	fprintf(stdout,"data do vencimento = ");
		    	scanf("%d/%d/%d",&Dia,&Mes,&Ano);
		    	limpaJanela(2,2,2,79,PRETO); 
		    	gotoxy(2,2); 
		    	fprintf(stdout," venda com a data de vencimento= %d/%d/%d",Dia,Mes,Ano);
		    	cont =0;
		    	linha = 3;
		    	if(dados != NULL){
		        	for (i=0;i<qtdeVenda;i++){
		        		if(venda[i].dia==Dia && venda[i].mes==Mes &&venda[i].ano==Ano){
		        			if(linha >= 18){
				                gotoxy(2,linha);
				                fprintf(stdout," Tecle qq tecla para continuar\n");
				                getch();
				                limpaJanela(3,2,19,79,PRETO);
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
	                gotoxy(4,2);
		    		retornaCor(BRANCO,PRETO);
		    		printf("%s",nome);
		    		gotoxy(4,3);
		    		printf("%-15s - %-11s - %-11s - %-11s - %-18s - %-10s\n","CFP do cliente","Medicamento","Data da venda","Quantidade","Valor Uni/ Compra","Valor Uni/ Venda");
	                itemSelecionado = menuVertical(qtdeItens,&dados[i],VERMELHO,AMARELO,5,5,1,1,BRANCO,BRANCO);
	                itemSelecionado1=pesquisaDataNaVenda(Dia,Mes,Ano,itemSelecionado);
	                
        		}
				   
    			if(dados !=NULL){
            	free(dados);
    			}
	        break;
    	}
    	// libera memória alocada
    	free(venda);
	}
   else
   {
    	desenhaMoldura(10,10,14,70,BRANCO,PRETO);
    	gotoxy(20,12);
    	fprintf(stdout,"Nao existe aluno cadastrado\n"); 
		getch();    
   } 
   
   return itemSelecionado1;              
}


// função - exclui os dados de uma venda do arquivo
// parâmetros - nome da empresa
// retorno - nenhum
void excluiVenda(char *nome){
	Venda venda;
	int seq,existeErro;
	char *msg;
	char codigoExcluir[10];

	seq=pesquisarVenda(nome);
    desenhaMoldura(10,10,18,70,BRANCO,PRETO);
    if(venda.IdentificacaoDoClient ==0)
    	return;
    // verifica se cliente ja cadastrado
    if(seq != 0){
    	
    	if(leRegVenda(seq,&venda)){
 		   
	        gotoxy(11,12);                                         
    		fprintf(stdout," %-11s - %-9s\n",venda.IdentificacaoDoClient,venda.IdentificacaoDoMedicamento);
    	    gotoxy(11,13);   
	        if(respostaSN("Confirma ") == 'S'){
		        	
	           // exlui registro do arquivo
	           msg = excluiRegArq("vendas.txt", sizeof(venda),seq,&existeErro);
	           if(!existeErro){
	               gotoxy(11,14);
	               fprintf(stdout,"Exclusao realizada com sucesso");    
	           }    
	           else{
	               apresentaMsgErro(msg,"excluiVenda");
	           }            
        	} 
			else{
	        	gotoxy(11,14);
	            fprintf(stdout,"Opcao cancelada com sucesso"); 
			} 
    	}     
	}             
	else{
    	gotoxy(11,13);  
    	fprintf(stdout," Venda nao cadastrado\n");
	}  
	//aumenta a quantidade em estoque
	alteraMedicamentoEstoq(venda.IdentificacaoDoMedicamento,venda.QuantidadeVendida);
	//alterar a variavel de controle do cliente
	alteraControleClient(venda.IdentificacaoDoClient);
	//alterar a variavel de controle do medicamento
	alteraControleMedicamentoMais(venda.IdentificacaoDoMedicamento);
	
	
    getch();
}


// Objetivo  : ler o dado de uma venda cujo sequencial é fornecido
// Parâmetros: seq - número do sequencial
//             endereço da estrutura do tipo cliente
// Retorno   : 0 - erro , 1 - ok               
int leRegVenda(int seq, Venda *venda){
	FILE *arq;
	int retorno =1;

	if((arq = abreArquivo("vendas.txt","rb",APRES_MSG))!=NULL){  
        if(fseek(arq,(seq-1)*sizeof(Venda),SEEK_SET) == 0)
        {        
            if(fread(venda,sizeof(Venda),1,arq)!=1)
            {
               apresentaMsgErro("Erro de leitura de um Venda","leRegVenda");
               retorno =0;                                        
            }
        }  
        else{
            apresentaMsgErro("Erro no posicionamento do arquivo para leitura","leRegVenda");
            retorno =0;  
        }
        if(fclose(arq) != 0){
           apresentaMsgErro("Erro ao fechar arquivo para leitura","leRegVenda");
        }   
    }
    return retorno;                                                
}

// Objetivo  : compara o id formecido com o id do cliente no arquivo e verificar a posição
// Parâmetros: o id do cliente e a posicao 
// Retorno   : retorna a verdadeira posicao no arquivo
int pesquisaClienteNaVenda(char *id, int numero){
FILE *arq;
Venda venda;
int seq=0,cont=0,count=0;
   arq = abreArquivo("vendas.txt","rb",NAO_APRES_MSG);
   if(arq != NULL){
      while(!feof(arq)){
         if(fread(&venda,sizeof(Venda),1,arq) == 1){
            cont++;
            if(strcmp(venda.IdentificacaoDoClient,id)==0){
               count++;
			   seq = cont;
               if(count==numero)
               break;
            }
         }
      }     
       if(fclose(arq) != 0)
          apresentaMsgErro(" Erro ao fechar arquivo clientes.txt","pesquisaMatriculaCliente");
   } 
   return seq;
}

// Objetivo  : compara o id formecido com o id do medicamento no arquivo e verificar a posição
// Parâmetros: o id do medicamento e a posicao 
// Retorno   : retorna a verdadeira posicao no arquivo
int pesquisaMedicamentoNaVenda(char *id, int numero){
FILE *arq;
Venda venda;
int seq=0,cont=0,count=0;
   arq = abreArquivo("vendas.txt","rb",NAO_APRES_MSG);
   if(arq != NULL){
      while(!feof(arq)){
         if(fread(&venda,sizeof(Venda),1,arq) == 1){
            cont++;
            if(strcmp(venda.IdentificacaoDoMedicamento,id)==0){
               count++;
			   seq = cont;
               if(count==numero)
               break;
            }
         }
      }     
       if(fclose(arq) != 0)
          apresentaMsgErro(" Erro ao fechar arquivo clientes.txt","pesquisaMatriculaCliente");
   } 
   return seq;
}

// Objetivo  : Ver qual posição e pra ser returnado
// Parâmetros: o ano,mes e dia e o numero da posição
// Retorno   : o posição do arquivo
int pesquisaDataNaVenda(int Dia,int Mes,int Ano, int numero){
FILE *arq;
Venda venda;
int seq=0,cont=0,count=0;
   arq = abreArquivo("vendas.txt","rb",NAO_APRES_MSG);
   if(arq != NULL){
      while(!feof(arq)){
         if(fread(&venda,sizeof(Venda),1,arq) == 1){
            cont++;
            if(venda.dia==Dia && venda.mes==Mes && venda.ano==Ano){
               count++;
			   seq = cont;
               if(count==numero)
               break;
            }
         }
      }     
       if(fclose(arq) != 0)
          apresentaMsgErro(" Erro ao fechar arquivo clientes.txt","pesquisaMatriculaCliente");
   } 
   return seq;
}

// Objetivo  : Fazer o controle de estoque 
// Parâmetros: Codigo do medicamento
// Retorno   : nenhum
void alteraMedicamentoEstoq(char *codigo,int quantEstoque){
	
	FILE * arq;
	Medicamento medicamento;
	int seq;
	char opcao;
	desenhaMoldura(10,10,18,70,BRANCO,PRETO);


    // verifica se cliente ja cadastrado
	seq = pesquisaCodigo(codigo);
		if(seq != 0){
	    	if(leRegMedicamento(seq,&medicamento)){
	        	arq = abreArquivo("medicamentos.txt","r+b",APRES_MSG);
	        	if(arq != NULL){ 
	        		fflush(stdin);
	        		medicamento.QuantEsto=medicamento.QuantEsto+quantEstoque;
     				
     				// posiciona para escrita
	                if(fseek(arq,(seq-1)*sizeof(Medicamento),SEEK_SET) == 0)
	                {        
	                   if(fwrite(&medicamento,sizeof(medicamento),1,arq) == 1)
	                   {
	                     
	                   }
	                   else
	                     apresentaMsgErro ("Erro ao gravar dados","alteraMedicamentoEstoque");
	                 }
	                 else
	                     apresentaMsgErro ("Erro ao posicionar arquivo ","alteraMedicamentoEstoque");
	           }
	           
	           if(fclose(arq) != 0)
	              apresentaMsgErro ("Erro ao fechar arquivo","alteraMedicamentoEstoque");
	    	}
		}  
		else{
	    	gotoxy(11,13);  
	    	retornaCor(BRANCO,PRETO);
	    	getch();
		}
}



// Objetivo  : diminuir 1 na variavel do controle do clinete.
// Parâmetros: o id do cliente 
// Retorno   : nenhum
void alteraControleClient(char *idCliente){
	FILE * arq;
	Cliente cliente;
	int seq;
	char opcao;
    
    // verifica se cliente ja cadastrado
    seq = pesquisaMatriculaCliente(idCliente);
	if(seq != 0){
	    if(leRegCliente(seq,&cliente)){  
		 
	        arq = abreArquivo("clientes.txt","r+b",APRES_MSG);
	        if(arq != NULL){ 
				fflush(stdin);
     			cliente.controleCompras=cliente.controleCompras-1;
				      						
	                // posiciona para escrita
	                if(fseek(arq,(seq-1)*sizeof(Cliente),SEEK_SET) == 0)
	                {        
	                   if(fwrite(&cliente,sizeof(cliente),1,arq) == 1)
	                   {
	                     
	                   }
	                   else
	                     apresentaMsgErro ("Erro ao gravar dados","alteraControleCliente");
	                 }
	                 else
	                     apresentaMsgErro ("Erro ao posicionar arquivo ","alteraControleCliente");
	                       
	            
	           }
	           if(fclose(arq) != 0)
	              apresentaMsgErro ("Erro ao fechar arquivo","alteraControleCliente");
	      }
	  }  
	  else
	  {
	    gotoxy(11,13);  
	    retornaCor(BRANCO,PRETO);
	    getch();
	  }
}



// Objetivo  : Aumenta 1 na variavel de controle do medicamento.
// Parâmetros: O id do medicamento
// Retorno   : Nenhum
void alteraControleMedicamento(char *idMedicamento){
	FILE * arq;
	Medicamento medicamento;
	int seq;
	char opcao;
    
    // verifica se cliente ja cadastrado
    seq = pesquisaCodigo(idMedicamento);
	if(seq != 0){
	    if(leRegMedicamento(seq,&medicamento)){  
		 
	        arq = abreArquivo("medicamentos.txt","r+b",APRES_MSG);
	        if(arq != NULL){ 
				fflush(stdin);
     			medicamento.controleCompras=medicamento.controleCompras+1;
				      						
	                // posiciona para escrita
	                if(fseek(arq,(seq-1)*sizeof(Medicamento),SEEK_SET) == 0)
	                {        
	                   if(fwrite(&medicamento,sizeof(medicamento),1,arq) == 1)
	                   {
	                     
	                   }
	                   else
	                     apresentaMsgErro ("Erro ao gravar dados","alteraControleMedicamento");
	                 }
	                 else
	                     apresentaMsgErro ("Erro ao posicionar arquivo ","alteraControleMedicamento");
	                       
	            
	           }
	           if(fclose(arq) != 0)
	              apresentaMsgErro ("Erro ao fechar arquivo","alteraControleMedicamento");
	      }
	  }  
	  else
	  {
	    gotoxy(11,13);  
	    retornaCor(BRANCO,PRETO);
	    getch();
	  }
}

// Objetivo  : Diminuir 1 na variavel de controle do medicamento.
// Parâmetros: O id do medicamento
// Retorno   : Nenhum
void alteraControleMedicamentoMais(char *idMedicamento){
	FILE * arq;
	Medicamento medicamento;
	int seq;
	char opcao;
    
    // verifica se cliente ja cadastrado
    seq = pesquisaCodigo(idMedicamento);
	if(seq != 0){
	    if(leRegMedicamento(seq,&medicamento)){  
		 
	        arq = abreArquivo("medicamentos.txt","r+b",APRES_MSG);
	        if(arq != NULL){ 
				fflush(stdin);
     			medicamento.controleCompras=medicamento.controleCompras-1;
				      						
	                // posiciona para escrita
	                if(fseek(arq,(seq-1)*sizeof(Medicamento),SEEK_SET) == 0)
	                {        
	                   if(fwrite(&medicamento,sizeof(medicamento),1,arq) == 1)
	                   {
	                     
	                   }
	                   else
	                     apresentaMsgErro ("Erro ao gravar dados","alteraControleMedicamento");
	                 }
	                 else
	                     apresentaMsgErro ("Erro ao posicionar arquivo ","alteraControleMedicamento");
	                       
	            
	           }
	           if(fclose(arq) != 0)
	              apresentaMsgErro ("Erro ao fechar arquivo","alteraControleMedicamento");
	      }
	  }  
	  else
	  {
	    gotoxy(11,13);  
	    retornaCor(BRANCO,PRETO);
	    getch();
	  }
}








