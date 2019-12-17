#include <stdio.h>
#include <string.h>
#include "estruturaProjeto.h"
#include "headers.h"
#include "cores.h"
#include "abreArquivo.h"
#include "manipulaDadosMedicamento.h"
#include <string.h>
#include "respostaSN.h"


// função - cadastra os dados do medicamento, gravando-o em um arquivo
// parâmetros - nome e local da farmácia
// retorno - nenhum
void cadastraMedicamento(char *nome){
	
	FILE * arq;
	Medicamento medicamento;
	int seq,ret=1,validarAlfa=0,validarData;
	gotoxy(10,9);
	retornaCor(BRANCO,PRETO);
	printf("%s",nome);
  	desenhaMoldura(10,10,18,70,BRANCO,PRETO);
  	gotoxy(11,11);
  
	fflush(stdin);
	gotoxy(11,11);
	fprintf(stdout,"Codigo = ");		  
	novaFgets(medicamento.CodigoAlfanumerico, sizeof(medicamento.CodigoAlfanumerico));	
	//validar o cadigo alfa numerico
	validarAlfa=validarCodigoAlfanumerico(medicamento.CodigoAlfanumerico);
	if(strlen(medicamento.CodigoAlfanumerico)!=9 || validarAlfa==0){
	gotoxy(11,11);
	printf("Codigo invalido, informe novamente ");
	getch();
	textbackground(PRETO);
	gotoxy(11,11); 
	printf("                                                           ");
	desenhaMoldura(10,10,18,70,BRANCO,PRETO);
	gotoxy(11,11); 
	}else{
	    // verifica se outro codigo ja esta cadastrado
	    seq = pesquisaCodigo(medicamento.CodigoAlfanumerico);
	    if(seq == 0){
	    	do{
		      	gotoxy(11,12);         
		      	fprintf(stdout,"Descricao do Medicamento = ");
		      	fflush(stdin);
		     	novaFgets(medicamento.DescricaoMedicamento, sizeof(medicamento.DescricaoMedicamento));
	     		if(strlen(medicamento.DescricaoMedicamento)==0 || medicamento.DescricaoMedicamento[0]==32){ 
			     	gotoxy(11,12); 
			     	printf("Descricao do Medicamento invalido, informe novamente ");
			     	getch();
			     	textbackground(PRETO);
					gotoxy(11,12); 
					printf("                                                           ");
					desenhaMoldura(10,10,18,70,BRANCO,PRETO); 
				}
			}while(strlen(medicamento.DescricaoMedicamento)==0 || medicamento.DescricaoMedicamento[0]==32);
	 
		 
			do{
				gotoxy(11,13);         
			    fflush(stdin);
			    leFloat(&medicamento.valorUnitarioCompra,"Valor unitario da compra = ", 13, 11);
			    fflush(stdin);
		    	if(medicamento.valorUnitarioCompra<=0 || medicamento.valorUnitarioCompra>14000 ){
		     		gotoxy(11,13); 
		     		printf("Valor unitario da compra invalido,informe novamente        ");
		    		getch();
			    	textbackground(PRETO);
					gotoxy(11,13); 
					printf("                                                           ");
					desenhaMoldura(10,10,18,70,BRANCO,PRETO);
				}
			}while(medicamento.valorUnitarioCompra<=0 || medicamento.valorUnitarioCompra>14000 );
	      
			do{
				gotoxy(11,14);         
			    fflush(stdin);
			    leFloat(&medicamento.valorUnitarioVenda,"Valor unitario da venda = ", 14, 11);
				fflush(stdin);
				if(medicamento.valorUnitarioVenda<=0||medicamento.valorUnitarioVenda>14000){
		    		gotoxy(11,14); 
		    		printf("Valor unitario da venda invalido, informe novamente ");
		    		getch();
		    		textbackground(PRETO);
					gotoxy(11,14); 
					printf("                                                           ");
					desenhaMoldura(10,10,18,70,BRANCO,PRETO); 
				}
			}while(medicamento.valorUnitarioVenda<=0||medicamento.valorUnitarioVenda>14000);
	 		
			do{
				gotoxy(11,15);
				fflush(stdin);
				leInt(&medicamento.QuantEsto,"Quantidade em estoque  = ", 15, 11);
			  	fflush(stdin);
			  	if(medicamento.QuantEsto<0){// colocar quantidade maxima
		     		gotoxy(11,15); 
		     		printf("Quantidade em estoque invalido, informe novamente ");
		     		getch();
		     		textbackground(PRETO);
					gotoxy(11,15); 
					printf("                                                           ");
					desenhaMoldura(10,10,18,70,BRANCO,PRETO); 
				}
			}while(medicamento.QuantEsto<0);
	  	  
	    	do{
				gotoxy(11,16);         
				fprintf(stdout,"Data de vencimento = ");
				fflush(stdin);
				scanf("%d/%d/%d",&medicamento.dia,&medicamento.mes,&medicamento.ano);
				validarData=valida_data(medicamento.dia,medicamento.mes,medicamento.ano);		
				if(validarData==0){
		     		gotoxy(11,16); 
		     		printf("Data de vencimento invalido, informe novamente ");
		     		getch();
		     		textbackground(PRETO);
					gotoxy(11,16); 
					printf("                                                           ");
					desenhaMoldura(10,10,18,70,BRANCO,PRETO); 
				}
			}while(validarData==0);
		    
		    medicamento.controleCompras=0;	
		  
			arq = abreArquivo("medicamentos.txt","ab",APRES_MSG);
				if(arq != NULL){
	        		if(fwrite(&medicamento,sizeof(Medicamento),1,arq)!= 1){
	            	apresentaMsgErro(" Erro ao cadastrar cliente no arquivo","cadastraCliente");
	        	}
	         	else
			   		gotoxy(11,17);
	           		fprintf(stdout," Medicamento cadastrado com sucesso");
	         	if(fclose(arq) != 0)
	           		apresentaMsgErro(" Erro ao fechar arquivo clientes.txt","cadastraCliente");
				}
		}
		else{
	    	gotoxy(11,11); 
	    	fprintf(stdout," Codigo %s ja cadastrada\n",medicamento.CodigoAlfanumerico);
		} 
		getch(); 
	}    
}

// função - pesquisar o codigo no arquivo com os dados dos medicamentos
// parâmetros - codigo
// retorno - 0 - medicamento não cadastrado, qq número - sequencial no arquivo do medicamento
int pesquisaCodigo(char *codigo){
	FILE *arq;
	Medicamento medicamento;
	int seq=0,cont=0;
    arq = abreArquivo("medicamentos.txt","rb",NAO_APRES_MSG);
	if(arq != NULL){
    	while(!feof(arq)){
    
        	if(fread(&medicamento,sizeof(Medicamento),1,arq) == 1){
        		cont++;
            	if(strcmp(medicamento.CodigoAlfanumerico,codigo)==0){
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

//Objetivo:Apresentar os medicamentos com uma molura em forma de tabela
//Parametros: id do medicamento, nome e local da farmácia
//Retorno:sem retorno
void apresentaMedicamento(char *codigo,char *nome){
	FILE *arq;
	Medicamento *medicamento;
	char **dados=NULL, aux[7],linhaDocodigo[500],Codigo[10];;
	int linha,cont=0,i,qtdeItens,itemSelecionado=0,matriculaSelecionada=0,qtdeAlocada=0,existeErro=0,count,j;
	#define TAM_TEXTO 200
	limpaJanela(1,1,60,180,PRETO);
   
   if((medicamento = obtemDadosArquivoMedicamento(&cont))!= NULL){        
    	if(cont != 0){
          
        	// carrega o menu vertical
        	dados = (char**) malloc(sizeof(char*)* (cont+1));   
        	if(dados != NULL){
                for(i=0;i<cont;i++){   
                   dados[i] = (char*) malloc(sizeof(char)*(TAM_TEXTO+1));
                   if(dados[i] != NULL)
				   {
                        sprintf(dados[i],"%-9s - %-50s - %-2d/%2d/%4d  - %-10d - %-15.3f - %-15.3f\n",medicamento[i].CodigoAlfanumerico,medicamento[i].DescricaoMedicamento,medicamento[i].dia,medicamento[i].mes,medicamento[i].ano,medicamento[i].QuantEsto,medicamento[i].valorUnitarioCompra,medicamento[i].valorUnitarioVenda);
                       qtdeAlocada++;                     
                   }
                   else{
                       apresentaMsgErro(" Erro ao alocar memoria para um elemento","apresentaMedicamento");
                       existeErro = 1;
                	}
                }    
        	}
        	else{
            	apresentaMsgErro(" Erro ao alocar memoria ","apresentaMedicamento");
            	existeErro = 1;
    		}
          
        	// libera memória alocada
        	free(medicamento);
          
        	if(!existeErro){
            	for (i=0;i<cont;i+=50){  

	            	qtdeItens = cont -i > 50? 50: cont-i;
	                gotoxy(4,2);
		    		retornaCor(BRANCO,PRETO);
		    		printf("%s",nome);
		    		gotoxy(4,3);
	    			printf("%-10s - %-50s - %-10s - %-10s - %-15s - %-15s\n","-Codigo","Descricao do Medicamento","Vencimento","Estoque","valor Uni Compra","valor Uni Venda");
	                itemSelecionado = menuVertical(qtdeItens,&dados[i],VERMELHO,AMARELO,5,5,1,1,BRANCO,BRANCO);
	                strcpy(linhaDocodigo,dados[itemSelecionado-1]);
	                
	                for(j=0;linhaDocodigo[j]!=32;j++){
	                	Codigo[j]=linhaDocodigo[j];
					}
					Codigo[j]='\0';
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
        	fprintf(stdout," Nao existem medicamentos cadastrados");
        	getch();
    	}
    	strcpy(codigo,Codigo);
	}   
}
// função - lê os dados dos clientes existentes em arquivo colocando-o na memória
//            com alocação dinâmica
// parâmetros - endereço de memória para guardar a qtde de clientes recuperada
// retorno - endereço de memória onde localiza-se os dados recuperados
//            do arquivo ou NULL no caso de falha
Medicamento * obtemDadosArquivoMedicamento(int *qtde){
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

//Objetivo: Buscar um medicamento atraves de partes de uma string
//Parametros:nome e local da farmácia
//Retorno: sem retorno
void pesquisaMedicamento(char *Nome){
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
	    gotoxy(2,4);
	    printf("%-10s - %-50s - %-10s - %-10s - %-15s - %-15s\n","-Codigo","Descricao do Medicamento","Vencimento","Estoque","valor Uni Compra","valor Uni Venda");
	    cont =0;
	    linha = 6;
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
			                                                      
	        fprintf(stdout,"%-9s - %-50s - %-2d/%2d/%5d - %-10d - %-15f - %-15f\n",medicamento[i].CodigoAlfanumerico,medicamento[i].DescricaoMedicamento,medicamento[i].dia,medicamento[i].mes,medicamento[i].ano,medicamento[i].QuantEsto,medicamento[i].valorUnitarioCompra,medicamento[i].valorUnitarioVenda);
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

// função - exclui os dados de um cliente do arquivo
// parâmetros - nenhum
// retorno - nenhum
void excluiMedicamento(char *nome){
	Medicamento medicamento;
	int seq,existeErro;
	char *msg;
	char codigoAlf[10];

	apresentaMedicamento(codigoAlf,nome);
    desenhaMoldura(10,10,18,70,BRANCO,PRETO);
    gotoxy(11,11);
    printf("                                                           ");
    gotoxy(11,12);
    printf("                                                           ");
    gotoxy(11,13);
    printf("                                                           ");
    gotoxy(11,14);
    printf("                                                           ");
    gotoxy(11,15);
    printf("                                                           ");
    gotoxy(11,16);
    printf("                                                           ");
    gotoxy(11,17);
    printf("                                                           ");
    if(medicamento.CodigoAlfanumerico <=0)
    	return;

    // verifica se cliente ja cadastrado
    seq = pesquisaCodigo(codigoAlf);
    if(seq != 0){
    	
    	if(leRegMedicamento(seq,&medicamento)){
	        gotoxy(11,12);                                         
    		fprintf(stdout," %s - %s\n",medicamento.CodigoAlfanumerico,medicamento.DescricaoMedicamento);
    		if(medicamento.controleCompras!=0){
        	gotoxy(11,13);
        	printf("Medicamento nao pode ser excluido, pois ele foi comprado");	
		}else{
    	    gotoxy(11,13);   
	        if(respostaSN("Confirma ") == 'S'){
		        	
	           // exlui registro do arquivo
	           msg = excluiRegArq("medicamentos.txt", sizeof(medicamento),seq,&existeErro);
	           if(!existeErro){
	               gotoxy(11,14);
	               fprintf(stdout,"Exclusao realizada com sucesso");    
	           }    
	           else{
	               apresentaMsgErro(msg,"excluiMedicamento");
	           }            
        	} 
			else{
	        	gotoxy(11,14);
	            fprintf(stdout,"Opcao cancelada com sucesso"); 
			}
			}
    	}     
	}             
	else{
    	gotoxy(11,13);  
    	fprintf(stdout," Medicamento nao cadastrado\n");
	}  
    getch();
}

// Objetivo  : ler o dado de um cliente cujo sequencial é fornecido
// Parâmetros: seq - número do sequencial
//             endereço da estrutura do tipo cliente
// Retorno   : 0 - erro , 1 - ok               
int leRegMedicamento(int seq, Medicamento *medicamento){
	FILE *arq;
	int retorno =1;

	if((arq = abreArquivo("medicamentos.txt","rb",APRES_MSG))!=NULL){  
        if(fseek(arq,(seq-1)*sizeof(Medicamento),SEEK_SET) == 0)
        {        
            if(fread(medicamento,sizeof(Medicamento),1,arq)!=1)
            {
               apresentaMsgErro("Erro de leitura de um cliente","leRegMedicamento");
               retorno =0;                                        
            }
        }  
        else{
            apresentaMsgErro("Erro no posicionamento do arquivo para leitura","leRegMedicamento");
            retorno =0;  
        }
        if(fclose(arq) != 0){
           apresentaMsgErro("Erro ao fechar arquivo para leitura","leRegMedicamento");
        }   
    }
    return retorno;                                                
}
// função - altera os dados de um medicamento em arquivo
// parâmetros - nenhum
// retorno - nenhum
void alteraMedicamento(char *nome){
	
	FILE * arq;
	Medicamento medicamento;
	int seq,valTel,valEstado,validarData;
	char opcao;
    char codigo[12]={"NULL"};
	desenhaMoldura(10,10,18,70,BRANCO,PRETO);
	gotoxy(11,11);
	
	apresentaMedicamento(codigo,nome);
    desenhaMoldura(10,10,18,120,BRANCO,PRETO);
	    
    // verifica se cliente ja cadastrado
	seq = pesquisaCodigo(codigo);
		if(seq != 0){
	    	if(leRegMedicamento(seq,&medicamento)){
	        	arq = abreArquivo("medicamentos.txt","r+b",APRES_MSG);
	        	if(arq != NULL){
	               gotoxy(11,12);                                         
	               fprintf(stdout," %s\n",medicamento.CodigoAlfanumerico);
	               gotoxy(11,13);   
	               if(respostaSN(" Confirma ") == 'S'){
	                	do{
	                		gotoxy(11,13) ;                   
	                		fprintf(stdout,"E-descricao, D-data vencimento, C-valor Unitario Compra, V-valor Unitario Venda, S-quandidade em estoque");
	                		opcao = toupper(getche());
	                 	}while(opcao != 'E' && opcao != 'D' && opcao != 'C' && opcao != 'V' && opcao != 'S'); 
	                	gotoxy(11,14);
	                	fprintf(stdout," Entre com os novos dados \n");
	                	gotoxy(11,15);
	                	
	                	if( opcao == 'E'){
	                		do{
								gotoxy(11,15);         
								fprintf(stdout,"Nova descricao = ");
								fflush(stdin);
							    novaFgets(medicamento.DescricaoMedicamento, sizeof(medicamento.DescricaoMedicamento));
						     	if(strlen(medicamento.DescricaoMedicamento)==0 || medicamento.DescricaoMedicamento[0]==32){ 
								    gotoxy(11,15); 
								    printf("Descricao do Medicamento invalido, informe novamente ");
								    getch();
								    textbackground(PRETO);
									gotoxy(11,15); 
									printf("                                                           ");
									desenhaMoldura(10,10,18,120,BRANCO,PRETO); 
									}
							}while(strlen(medicamento.DescricaoMedicamento)==0 || medicamento.DescricaoMedicamento[0]==32);
								
	            		}
	                	else if(opcao=='D'){
	                		do{
								gotoxy(11,15);         
								fprintf(stdout,"Data de vencimento = ");
								fflush(stdin);
								scanf("%d/%d/%d",&medicamento.dia,&medicamento.mes,&medicamento.ano);
								validarData=valida_data(medicamento.dia,medicamento.mes,medicamento.ano);		
								if(validarData==0){
						     		gotoxy(11,15); 
						     		printf("Data de vencimento invalido, informe novamente ");
						     		getch();
						     		textbackground(PRETO);
									gotoxy(11,15); 
									printf("                                                           ");
									desenhaMoldura(10,10,18,70,BRANCO,PRETO); 
								}
							}while(validarData==0);
	                	}
	                	
	                	else if(opcao=='C'){  
							do{
								gotoxy(11,15);         
							    fflush(stdin);
							    leFloat(&medicamento.valorUnitarioCompra,"Valor unitario da compra = ", 15, 11);
							    fflush(stdin);
						    	if(medicamento.valorUnitarioCompra<=0 || medicamento.valorUnitarioCompra>14000){
						     		gotoxy(11,15); 
						     		printf("Valor unitario da compra invalido,informe novamente        ");
						    		getch();
							    	textbackground(PRETO);
									gotoxy(11,15); 
									printf("                                                           ");
									desenhaMoldura(10,10,18,120,BRANCO,PRETO);
								}
							}while(medicamento.valorUnitarioCompra<=0 || medicamento.valorUnitarioCompra>14000);
						}
						
						else if(opcao=='V'){  
	                   		do{
								gotoxy(11,15);         
								fflush(stdin);
							    leFloat(&medicamento.valorUnitarioVenda,"Valor unitario da venda = ", 15, 11);
								fflush(stdin);
								if(medicamento.valorUnitarioVenda<=0 || medicamento.valorUnitarioVenda>14000){
						    		gotoxy(11,15); 
						    		printf("Valor unitario da venda invalido, informe novamente ");
						    		getch();
						    		textbackground(PRETO);
									gotoxy(11,15); 
									printf("                                                           ");
									desenhaMoldura(10,10,18,120,BRANCO,PRETO); 
								}
							}while(medicamento.valorUnitarioVenda<=0 || medicamento.valorUnitarioVenda>14000);
						}
						
						else if(opcao=='S'){  
	                   		do{
								gotoxy(11,15);         
								fflush(stdin);
								leInt(&medicamento.QuantEsto,"Quantidade em estoque  = ", 15, 11);
							  	fflush(stdin);
							  	if(medicamento.QuantEsto<0){
						     		gotoxy(11,15); 
						     		printf("Quantidade em estoque invalido, informe novamente ");
						     		getch();
						     		textbackground(PRETO);
									gotoxy(11,15); 
									printf("                                                           ");
									desenhaMoldura(10,10,18,120,BRANCO,PRETO); 
								}
							}while(medicamento.QuantEsto<0);
					 	}
					 	
	                	//posiciona para escrita
	                	if(fseek(arq,(seq-1)*sizeof(Medicamento),SEEK_SET) == 0)
	                	{        
	                   	if(fwrite(&medicamento,sizeof(medicamento),1,arq) == 1)
		                   {
		                     gotoxy(11,16);                                    
		                     fprintf(stdout," Alteracao realizada com sucesso\n");
		                     getch();
		                   }
		                   else
		                     apresentaMsgErro ("Erro ao gravar dados","alteraCliente");
		                 }
		                 else
		                     apresentaMsgErro ("Erro ao posicionar arquivo ","alteraCliente");
	                }   
	           }
	           if(fclose(arq) != 0)
	              apresentaMsgErro ("Erro ao fechar arquivo","alteraMedicamento");
	    	}
		}  
		else{
	    	gotoxy(11,13);  
	    	retornaCor(BRANCO,PRETO);
	    	fprintf(stdout," Medicamento nao cadastrado");
	    	getch();
		}
}
// função - validar se o cadigo e so numero e letra
// parâmetros - o cadigo
// retorno - 1 se for valido e 0 se não for valido
int validarCodigoAlfanumerico(char *codigo){
	int tam,cont,flag;
	
	tam=strlen(codigo);
	for(cont=0;cont<tam;cont++){
		if((codigo[cont]>=48 && codigo[cont]<=57)  ||   (codigo[cont]>=65 && codigo[cont]<=90)   ||   (codigo[cont]>=97 && codigo[cont]<=122)){
			flag=1;	
		}
		else{
			flag=0;
			break;
		}
	}
	return flag;
}

//Objetivo: Validacao de data
//parametro: o dia o mes e o ano
//returno: Retorna 1 caso a data seja correta e 0 caso a data esteja incorreta 
int valida_data(int dia, int mes, int ano)
    {
    if ((dia >= 1 && dia <= 31) && (mes >= 1 && mes <= 12) && (ano >= 2005 && ano <= 2050)) //verifica se os numeros sao validos
        {
            if ((dia == 29 && mes == 2) && ((ano % 4) == 0)) //verifica se o ano e bissexto
            {
                return 1;
            }
            if (dia <= 28 && mes == 2) //verifica o mes de feveireiro
            {
                return 1;
            }
            if ((dia <= 30) && (mes == 4 || mes == 6 || mes == 9 || mes == 11)) //verifica os meses de 30 dias
            {
                return 1;
            }
            if ((dia <=31) && (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes ==8 || mes == 10 || mes == 12)) //verifica os meses de 31 dias
            {
                return 1;
            }
            else
            {
                return 0;
            }
      }
       else
           {
                return 0;
           }
}












