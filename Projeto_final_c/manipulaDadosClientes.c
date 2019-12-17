#include <stdio.h>
#include <string.h>
#include "estruturaProjeto.h"
#include "headers.h"
#include "cores.h"
#include "abreArquivo.h"
#include "manipulaDadosClientes.h"
#include <string.h>
#include "respostaSN.c"
#include "respostaSN.h"


// função - cadastra os dados de um cliente, gravando-o em um arquivo
// parâmetros - nome da farmacia
// retorno - nenhum
void cadastraCliente(char *nome){
FILE * arq;
Cliente cliente;
int seq,ret=1,valTel,valEstado;
	gotoxy(10,9);
	retornaCor(BRANCO,PRETO);
	printf("%s",nome);
	desenhaMoldura(10,10,18,70,BRANCO,PRETO);
	gotoxy(11,11);
  
		fflush(stdin);
		gotoxy(11,11);
		fprintf(stdout,"CPF = ");
			  
		novaFgets(cliente.CPF, sizeof(cliente.CPF));	
		ret=validaCPF (cliente.CPF);
		if(ret!=1 || strlen(cliente.CPF)>11){
		gotoxy(11,11);
		printf("CPF invalido, informe novamente ");
		getch();
		textbackground(PRETO);
		gotoxy(11,11); 
		printf("                                                           ");
		desenhaMoldura(10,10,18,70,BRANCO,PRETO);
		gotoxy(11,11); 
		} else{
			  // Aqui verifica se o cliente ja cadastrado
			  seq = pesquisaMatriculaCliente(cliente.CPF);
			  if(seq == 0){
			    do{
			      	gotoxy(11,12);         
			      	fprintf(stdout,"Nome = ");
			      	fflush(stdin);
			     	novaFgets(cliente.nome, sizeof(cliente.nome));
			     	if(strlen(cliente.nome)==0 || cliente.nome[0]==32){
				     	gotoxy(11,12); 
				     	printf("Nome invalido, informe novamente ");
				     	getch();
				     	textbackground(PRETO);
						gotoxy(11,12); 
						printf("                                                           ");
						desenhaMoldura(10,10,18,70,BRANCO,PRETO); 
					}
				}while(strlen(cliente.nome)==0 || cliente.nome[0]==32);
			
				
				do{
					gotoxy(11,13);         
				    fprintf(stdout,"Telefone = ");
				    fflush(stdin);
				    novaFgets(cliente.telefone, sizeof(cliente.telefone));
				    valTel=validarTelefone(cliente.telefone);
				    fflush(stdin);
				    if(valTel==1 || valTel==2){
				     	gotoxy(11,13); 
				     	if(valTel==2){
				     		printf("O DDD esta errado,informe novamente                        ");
						}else{
						 	printf("Telefone invalido,informe outro                            ");
						 }
				     	getch();
				     	textbackground(PRETO);
						gotoxy(11,13); 
						printf("                                                           ");
						desenhaMoldura(10,10,18,70,BRANCO,PRETO);
					}
				}while(valTel==1 || valTel==2);
			      
				do{
					gotoxy(11,14);         
					fprintf(stdout,"Endereco(descricao) = ");
				    fflush(stdin);
				    novaFgets(cliente.descrEnd, sizeof(cliente.descrEnd));
					fflush(stdin);
					if(strlen(cliente.descrEnd)==0 || cliente.descrEnd[0]==32){
			     		gotoxy(11,14); 
			     		printf("Endereco invalido, informe novamente ");
			     		getch();
			     		textbackground(PRETO);
						gotoxy(11,14); 
						printf("                                                           ");
						desenhaMoldura(10,10,18,70,BRANCO,PRETO); 
					}
				}while(strlen(cliente.descrEnd)==0 || cliente.descrEnd[0]==32);
					
				do{
					gotoxy(11,15);         
					fprintf(stdout,"Cidade = ");
				  	fflush(stdin);
				  	novaFgets(cliente.cidade,sizeof(cliente.cidade));
				  	fflush(stdin);
				  	if(strlen(cliente.cidade)==0 || cliente.cidade[0]==32){
			     		gotoxy(11,15); 
			     		printf("Cidade invalido, informe novamente ");
			     		getch();
			     		textbackground(PRETO);
						gotoxy(11,15); 
						printf("                                                           ");
						desenhaMoldura(10,10,18,70,BRANCO,PRETO); 
					}
				}while(strlen(cliente.cidade)==0 || cliente.cidade[0]==32);
			  	  
			    do{
					gotoxy(11,16);         
					fprintf(stdout,"Estado(DF) = ");
					fflush(stdin);
				  	novaFgets(cliente.estado,sizeof(cliente.estado));
				  	valEstado=validarEstado(cliente.estado);
				  	if(strlen(cliente.estado)==0 || cliente.estado[0]==32 || valEstado==1 || strlen(cliente.estado)!=2){
			     		gotoxy(11,16); 
			     		printf("Estado invalido, informe novamente ");
			     		getch();
			     		textbackground(PRETO);
						gotoxy(11,16); 
						printf("                                                           ");
						desenhaMoldura(10,10,18,70,BRANCO,PRETO); 
					}
				}while(strlen(cliente.estado)==0 || cliente.estado[0]==32 || valEstado==1 || strlen(cliente.estado)!=2);
				
				cliente.controleCompras=0;	  
				  
				arq = abreArquivo("clientes.txt","ab",APRES_MSG);
			    if(arq != NULL){
			        if(fwrite(&cliente,sizeof(Cliente),1,arq)!= 1){
			            apresentaMsgErro(" Erro ao cadastrar cliente no arquivo","cadastraCliente");
			        }
			        else
					   gotoxy(11,17);
			           fprintf(stdout," Cliente cadastrado com sucesso");
			        if(fclose(arq) != 0)
			           apresentaMsgErro(" Erro ao fechar arquivo clientes.txt","cadastraCliente");
			    }
			}
			else{
     			gotoxy(11,11); 
     			fprintf(stdout," Cliente  com CPF %s ja cadastrada\n",cliente.CPF);
  			}
  			getch();  
		}      
}
// função -pesquisar um cliente através da chave unica dele
// parâmetros - chave unica de pesquisa
// retorno - 0 - cliente  não cadastrado, qualquer número - sequencial no arquivo do cliente
int pesquisaMatriculaCliente(char *matricula){
FILE *arq;
Cliente cliente;
int seq=0,cont=0;
   arq = abreArquivo("clientes.txt","rb",NAO_APRES_MSG);
   if(arq != NULL){
      while(!feof(arq)){
         if(fread(&cliente,sizeof(Cliente),1,arq) == 1){
            cont++;
            if(strcmp(cliente.CPF,matricula)==0){
               seq = cont;
               break;
            }
         }
      }     
       if(fclose(arq) != 0)
          apresentaMsgErro(" Erro ao fechar arquivo clientes.txt","pesquisaMatriculaCliente");
   } 
   return seq;
}
//Objetivo:Apresentar os clientes cadastrados
//Parametros:  referencia a string de cpf, nome da farmacia
//Retorno: Sem Retorono
void apresentaClientes(char *CPf,char *nome){
FILE *arq;
Cliente *clientes;
char **dados=NULL, aux[7],cpf[1000],cpfDefinitivo[11];
int linha,cont=0,i,qtdeItens,itemSelecionado=0,matriculaSelecionada=0,qtdeAlocada=0,existeErro=0,count;
#define TAM_TEXTO 200
   limpaJanela(1,1,60,180,PRETO);
   
   if((clientes = obtemDadosArquivoCliente(&cont))!= NULL){        
      if(cont != 0)
      {
          // ordena os dados dos clientes por nome
          qsort(clientes,cont,sizeof(Cliente),comparaNomeClientes);
          
          // carrega o menu vertical
          dados = (char**) malloc(sizeof(char*)* (cont+1)) ;   
          if(dados != NULL){
                for(i=0;i<cont;i++){   
                   dados[i] = (char*) malloc(sizeof(char)*(TAM_TEXTO+1));
                   if(dados[i] != NULL){
                       sprintf(dados[i],"%-11s - %-49s - %-11s - %-2s - %-34s - %-34s\n",formataCPF(clientes[i].CPF),clientes[i].nome,clientes[i].telefone,maicusculo(clientes[i].estado),clientes[i].cidade,clientes[i].descrEnd);
                       qtdeAlocada++;                     
                   }
                   else{
                       apresentaMsgErro(" Erro ao alocar memoria para um elemento","apresentaClientes");
                       existeErro = 1;
                   }
                }    
          }
          else{
              apresentaMsgErro(" Erro ao alocar memoria ","apresentaClientes");
              existeErro = 1;
          }
          
          // libera memória alocada
          free(clientes);
          
          if(!existeErro)
          {
              for (i=0;i<cont;i+=50)
             {					
                qtdeItens = cont -i > 50? 50: cont-i;
                gotoxy(4,2);
	    		retornaCor(BRANCO,PRETO);
	    		printf("%s",nome);
	    		gotoxy(4,3);
	    		printf("-%-14s - %-49s - %-16s - %-34s - %-34s\n","CPF","Nome do Cliente","telefone","Cidade","endereco");
                itemSelecionado = menuVertical(qtdeItens,&dados[i],VERMELHO,AMARELO,5,5,1,1,BRANCO,BRANCO);
                /////////////
                //PEGAR O CPF
				strcpy(cpf,dados[itemSelecionado-1]);
        					
                cpfDefinitivo[0]=cpf[0];
                cpfDefinitivo[1]=cpf[1];
                cpfDefinitivo[2]=cpf[2];
                cpfDefinitivo[3]=cpf[4];
                cpfDefinitivo[4]=cpf[5];
                cpfDefinitivo[5]=cpf[6];
                cpfDefinitivo[6]=cpf[8];
                cpfDefinitivo[7]=cpf[9];
                cpfDefinitivo[8]=cpf[10];
                cpfDefinitivo[9]=cpf[12];
                cpfDefinitivo[10]=cpf[13];
                cpfDefinitivo[11]='\0';
                
                //TERMINA AQUI
                //////////////
              }
          }     
          if(dados !=NULL)
          {
             for (i=0;i<qtdeAlocada;i++)
                 free(dados[i]); 
             free(dados);           
          }   
      }
      else 
      {
        gotoxy( 10,10);
        textbackground(BRANCO);
        fprintf(stdout," Nao existem clientes cadastrados");
        getch();
      }
      strcpy(CPf,cpfDefinitivo);
   }   

}

// função - pesquisa um cliente
// parâmetros 
// retorno - nenhum
void pesquisaCliente(char *Nome){
Cliente *clientes;
int qtdeClientes,matricula,cont=0,i,linha;
char nome[TAM_NOME],opcao;
   if((clientes = obtemDadosArquivoCliente(&qtdeClientes)) != NULL){
	    
	    limpaJanela(10,10,14,70,PRETO);

	    ordenaClientes(qtdeClientes,clientes);
	    fflush(stdin);
	    limpaJanela(1,1,25,80,PRETO); 
	    gotoxy(1,1);
	    retornaCor(BRANCO,PRETO);
	    printf("%s",Nome);
	    desenhaMoldura(2,1,25,160,BRANCO,PRETO);
	    gotoxy(2,3); 
	    fprintf(stdout," Nome a pesquisar = ");
	    novaFgets(nome, sizeof(nome));
	    strUpper(nome);
	    limpaJanela(3,3,3,79,PRETO); 
	    gotoxy(2,3); 
	    retornaCor(BRANCO,PRETO);
	    fprintf(stdout," Clientes com nome = %s",nome);
	    gotoxy(2,4);
	    printf("-%-14s - %-49s - %-16s - %-34s - %-34s\n","CPF","Nome do Cliente","telefone","Cidade","endereco");
	    cont =0;
	    linha = 6;
	    
	    for (i=0;i<qtdeClientes;i++)
	    {
	      if(strIstr(clientes[i].nome,nome)!= NULL)
	      {
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
	        fprintf(stdout,"%-11s - %-49s - %-11s - %-2s - %-34s - %-34s\n",formataCPF(clientes[i].CPF),clientes[i].nome,clientes[i].telefone,maicusculo(clientes[i].estado),clientes[i].cidade,clientes[i].descrEnd);
	        cont++;     
	        }
	    }
	    if(cont == 0)
	    {
	       gotoxy(5,5);
		   retornaCor(BRANCO,PRETO); 
	       fprintf(stdout,"Nao existe cliente cadastrado\n");
	    }   
	     // libera memória alocada
	    free(clientes);
   } 
   else
   {
     desenhaMoldura(10,10,14,70,BRANCO,PRETO);
     gotoxy(20,12);
     retornaCor(BRANCO,PRETO);
     fprintf(stdout,"Nao existe cliente cadastrado\n");     
   }     
   getch();            
       
}

// função - lê os dados dos clientes existentes em arquivo colocando-o na memória
//            com alocação dinâmica
// parâmetros - endereço de memória para guardar a qtde de clientes recuperada
// retorno - endereço de memória onde localiza-se os dados recuperados
//            do arquivo ou NULL no caso de insucesso
Cliente * obtemDadosArquivoCliente(int *qtde)
{
FILE *arq;
Cliente *clientes=NULL;
int i;

    if((arq = abreArquivo("clientes.txt","rb",NAO_APRES_MSG)) != NULL)
    {
        if(fseek(arq,0,SEEK_END)==0)
        {
           *qtde= ftell(arq)/sizeof(Cliente);
           clientes = (Cliente*) malloc(*qtde * 
                                 sizeof(Cliente));
           if(clientes == NULL)
           {
               apresentaMsgErro("Erro de alocacao","obtemDadosArquivoCliente");
           }                      
           else
           {
             rewind(arq);           
             if(fread(clientes,sizeof(Cliente),*qtde,arq)!=*qtde)
             {
                 apresentaMsgErro("Erro de leitura","obtemDadosArquivoCliente");
                 free(clientes);
                 clientes = NULL;
             }             
           }           
        }
       if(fclose(arq) != 0)
       {
           apresentaMsgErro("Erro so fechar arquivo","obtemDadosArquivoCliente");
        }    
                
    }
    return clientes;
}


// função - ordena os dados dos dos clientes existentes na memória
// parâmetros - qtde de clientes
//               endereço de memória com os dados dos clientes
// retorno - nenhum
void ordenaClientes(int qtde, Cliente *clientes)
{
  
 // ordenação usando qsort
 qsort(clientes,qtde,sizeof(Cliente),comparaNomeClientes);
 //ordenação usando bolha 

}

// função - exclui os dados de um cliente do arquivo
// parâmetros - nenhum
// retorno - nenhum
void excluiCliente(char *nome){

Cliente cliente;
int seq,existeErro;
char *msg;
char posCPF[12];

	apresentaClientes(posCPF,nome);
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
    if(cliente.CPF <=0)
    	return;

    // verifica se cliente ja cadastrado
    seq = pesquisaMatriculaCliente(posCPF);
    if(seq != 0){
    	
      if(leRegCliente(seq,&cliente))
      {   
        gotoxy(11,12);                                         
        fprintf(stdout," %s - %s - %s\n",formataCPF(cliente.CPF),cliente.nome,cliente.telefone);
        if(cliente.controleCompras!=0){
        	gotoxy(11,13);
        	printf("Cliente nao pode ser excluido, pois ele realizou vendas");
        	
		}else{
	        gotoxy(11,13);   
	        if(respostaSN("Confirma ") == 'S'){
	        	
	           // exlui registro do arquivo
	           msg = excluiRegArq("clientes.txt", sizeof(cliente),seq,&existeErro);
	           if(!existeErro)
	           {
	               gotoxy(11,14);
	               fprintf(stdout,"Exclusao realizada com sucesso");    
	           }    
	           else
	           {
	               apresentaMsgErro(msg,"excluiCliente");
	           }            
	        } else{
	        	gotoxy(11,14);
	            fprintf(stdout,"Opcao cancelada com sucesso"); 
			}
		}
      }     
    }             
  else
  {
    gotoxy(11,13);  
    fprintf(stdout," Cliente nao cadastrado\n");
  }  
  getch();   
}



// Objetivo  : ler o dado de um cliente cujo sequencial é fornecido
// Parâmetros: seq - número do sequencial
//             endereço da estrutura do tipo cliente
// Retorno   : 0 - erro , 1 - ok               
int leRegCliente(int seq, Cliente *cliente)
{
FILE *arq;
int retorno =1;

      if((arq = abreArquivo("clientes.txt","rb",APRES_MSG))!=NULL)
      {  
        if(fseek(arq,(seq-1)*sizeof(Cliente),SEEK_SET) == 0)
        {        
            if(fread(cliente,sizeof(Cliente),1,arq)!=1)
            {
               apresentaMsgErro("Erro de leitura de um cliente","leRegCliente");
               retorno =0;                                        
            }
        }  
        else
        {
            apresentaMsgErro("Erro no posicionamento do arquivo para leitura","leRegCliente");
            retorno =0;  
        }
        if(fclose(arq) != 0)
        {
           apresentaMsgErro("Erro ao fechar arquivo para leitura","leRegCliente");
        }   
      }
      return retorno;                                                
}

// função - compara os dados a serem ordenados pela qsort
// parâmetros - endereço para os elementos a serem pesquisados na ordenação
// retorno - =0 --> dados iguais
//           >0 --> dados desordenados
//           <0 --> dados ordenados 
// função que os nomes a serem ordenados pela qsort
int comparaNomeClientes(const void * p1, const void *p2)
{
Cliente *cliente1,*cliente2;

  cliente1 = (Cliente*)p1;
  cliente2 = (Cliente*) p2;
  return stricmp((*cliente1).nome,(*cliente2).nome); 
}

// função - altera os dados de um cliente em arquivo
// parâmetros - nenhum
// retorno - nenhum
void alteraCliente(char *nome){
	FILE * arq;
	Cliente cliente;
	int seq,valTel,valEstado;
	char opcao;
    char posCPF[12]={"NULL"};
	desenhaMoldura(10,10,18,70,BRANCO,PRETO);
	gotoxy(11,11);
//   cliente.CPF = apresentaClientes();
 	apresentaClientes(posCPF,nome);
    desenhaMoldura(10,10,18,70,BRANCO,PRETO);
    
    // verifica se cliente ja cadastrado
    seq = pesquisaMatriculaCliente(posCPF);
	  if(seq != 0)
	  {
	      if(leRegCliente(seq,&cliente))
	      {   
	        arq = abreArquivo("clientes.txt","r+b",APRES_MSG);
	        if(arq != NULL)
	        {
	               gotoxy(11,12);                                         
	               fprintf(stdout," %s - %s - %s\n",cliente.CPF,cliente.nome,cliente.telefone);
	               gotoxy(11,13);   
	               if(respostaSN(" Confirma ") == 'S')
	               {
	                 do
	                 {
	                   gotoxy(11,13) ;                   
	                   fprintf(stdout,"N - Nome, T - telefone, E - endereco, C - cidade, S - estado");
	                   opcao = toupper(getche());
	                 }while(opcao != 'T' && opcao != 'N' && opcao != 'E' && opcao != 'C' && opcao != 'S'); 
	                 gotoxy(11,14);
	                 fprintf(stdout," Entre com os novos dados \n");
	                 gotoxy(11,15);
	                 if( opcao == 'N')
	                 {
	                 	do{
      						gotoxy(11,15);         
      						fprintf(stdout,"Nome = ");
      						fflush(stdin);
     						novaFgets(cliente.nome, sizeof(cliente.nome));
     						if(strlen(cliente.nome)==0 || cliente.nome[0]==32){
	     						gotoxy(11,15); 
	     						printf("Nome invalido, informe novamente ");
	     						getch();
	     						textbackground(PRETO);
								gotoxy(11,15); 
								printf("                                                           ");
								desenhaMoldura(10,10,18,70,BRANCO,PRETO); 
							}
						}while(strlen(cliente.nome)==0 || cliente.nome[0]==32);
	                 }
	                 else if(opcao=='T')
	                 {
					 	do{
							gotoxy(11,15);         
						    fprintf(stdout,"Telefone = ");
						    fflush(stdin);
						    novaFgets(cliente.telefone, sizeof(cliente.telefone));
						    valTel=validarTelefone(cliente.telefone);
						    fflush(stdin);
						    if(valTel==1 || valTel==2){
						     	gotoxy(11,15); 
						     	if(valTel==2){
						     		printf("O DDD esta errado,informe novamente                        ");
								}else{
								 	printf("Telefone invalido,informe outro                            ");
								 }
						     	getch();
						     	textbackground(PRETO);
								gotoxy(11,15); 
								printf("                                                           ");
								desenhaMoldura(10,10,18,70,BRANCO,PRETO);
							}
						}while(valTel==1 || valTel==2);
	                 }
	                else if(opcao=='E')
	                 {  
	                   	do{
							gotoxy(11,15);         
							fprintf(stdout,"Endereco(descricao) = ");
						    fflush(stdin);
						    novaFgets(cliente.descrEnd, sizeof(cliente.descrEnd));
							fflush(stdin);
							if(strlen(cliente.descrEnd)==0 || cliente.descrEnd[0]==32){
					     		gotoxy(11,15); 
					     		printf("Endereco invalido, informe novamente ");
					     		getch();
					     		textbackground(PRETO);
								gotoxy(11,15); 
								printf("                                                           ");
								desenhaMoldura(10,10,18,70,BRANCO,PRETO); 
							}
						}while(strlen(cliente.descrEnd)==0 || cliente.descrEnd[0]==32);
					 }
					 else if(opcao=='C')
	                 {  
	                   do{
							gotoxy(11,15);         
							fprintf(stdout,"Cidade = ");
						  	fflush(stdin);
						  	novaFgets(cliente.cidade,sizeof(cliente.cidade));
						  	fflush(stdin);
						  	if(strlen(cliente.cidade)==0 || cliente.cidade[0]==32){
					     		gotoxy(11,15); 
					     		printf("Cidade invalido, informe novamente ");
					     		getch();
					     		textbackground(PRETO);
								gotoxy(11,15); 
								printf("                                                           ");
								desenhaMoldura(10,10,18,70,BRANCO,PRETO); 
							}
						}while(strlen(cliente.cidade)==0 || cliente.cidade[0]==32);
					}
					else if(opcao=='S')
	                 {  
	                    do{
							gotoxy(11,15);         
							fprintf(stdout,"Estado = ");
							fflush(stdin);
						  	novaFgets(cliente.estado,sizeof(cliente.estado));
						  	valEstado=validarEstado(cliente.estado);
						  	if(strlen(cliente.estado)==0 || cliente.estado[0]==32 || valEstado==1 || strlen(cliente.estado)!=2){
					     		gotoxy(11,15); 
					     		printf("Estado invalido, informe novamente ");
					     		getch();
					     		textbackground(PRETO);
								gotoxy(11,15); 
								printf("                                                           ");
								desenhaMoldura(10,10,18,70,BRANCO,PRETO); 
							}
						}while(strlen(cliente.estado)==0 || cliente.estado[0]==32 || valEstado==1 || strlen(cliente.estado)!=2);
					 }
	                // posiciona para escrita
	                if(fseek(arq,(seq-1)*sizeof(Cliente),SEEK_SET) == 0)
	                {        
	                   if(fwrite(&cliente,sizeof(cliente),1,arq) == 1)
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
	              apresentaMsgErro ("Erro ao fechar arquivo","alteraCliente");
	      }
	  }  
	  else
	  {
	    gotoxy(11,13);  
	    retornaCor(BRANCO,PRETO);
	    fprintf(stdout," Cliente nao cadastrado");
	    getch();
	  }

  
}




