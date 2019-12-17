#include "cores.h"

/**********************************************************************************************
 Função     : strUpper
 Objetivo   : Converte uma string para maiuscula
 Parâmetros : str - endereço de memória da string a ser convertida para maiuscul
 Retorno   :  void
***********************************************************************************************/
void strUpper(char * str){
int i;
  for (i=0;i<strlen(str);i++){
      str[i] = (char) toupper(str[i]);
  }        
}  

/**************************************************************
*  Nome      : tiraBrEsq                                      *  
*  Descricao : Tira todos os brancos a esquerda de uma string *
*  Parâmetros:                                                *
*             string                                          *
*  Retorno   : Nenhum                                         * 
**************************************************************/ 
void tiraBrEsq(char *str){
char *pStr;    
   pStr = str;	
   while(*pStr == ' ' && *pStr != '\0')
      pStr++;
   strcpy(str,pStr);   
}    
/**************************************************************
*  Nome      : tiraBrDir                                      *  
*  Descricao : Tira todos os brancos a direita  de uma string *
*  Parâmetros:                                                *
*             string                                          *
*  Retorno   : Nenhum                                         * 
**************************************************************/ 
void tiraBrDir(char *str){
char *pStr; 
   if(*str == '\0')
      return;   
   pStr = str+strlen(str)-1;
   while(*pStr == ' ')
      pStr--;
   *(pStr+1) = '\0';
}
/***********************************************************
*  Nome      : leInt                                       *  
*  Descricao : le um numero inteiro                        *
*  Parâmetros: endereço de memória onde será armazenado    *
*               o número inteiro                           *
*              titulo                                      * 
*              linha e coluna para o titulo                *
* Retorno    : sem retorno                                 * 
************************************************************/
void leInt(int *nroInt, char *titulo, int linha, int coluna){
    do
    {
       fflush(stdin);
       gotoxy(coluna,linha);
       printf("%s",titulo); 
    }while(scanf("%d",nroInt) != 1); 
    fflush(stdin);
} 
/***********************************************************
*  Nome      : leFloat                                     *  
*  Descricao : le um numero float                          *
*  Parâmetros: endereço de memória onde será armazenado    *
*               o número float                             *
*              titulo                                      * 
*              linha e coluna para o titulo                *
* Retorno    : sem retorno                                 * 
************************************************************/
void leFloat(float *nroFloat, char *titulo, int linha, int coluna){
    do
    {
       fflush(stdin);
       gotoxy(coluna,linha);
       printf("%s",titulo); 
    }while(scanf("%f",nroFloat) != 1); 
    fflush(stdin);
} 
/**************************************************************
*  Nome      : validaCPF                                      *  
*  Descricao : Valida um CPF                                  *
*  Parâmetros: endereço inicial da string cpf                 *
*  Retorno   : 1 - cpf válido, 0 - cpf inválido               * 
**************************************************************/ 
int validaCPF (char *cpf){
    // cpfs inválidos        
   char *cpfInval[]={"00000000000",
   					 "11111111111",
                     "22222222222",
                     "33333333333",
                     "44444444444",
                     "55555555555",
                     "66666666666",
                     "77777777777",
                     "88888888888",
                     "99999999999"}; 
	int cont,retorno =1,aux2,dig[11],soma=0,digVeri[2];
	if(strlen(cpf) != 11)
	   return 0;
    // verifica se cpf so contem nros iguais  
    for(cont=0;cont<9;cont++){
        if(strcmp(cpfInval[cont],cpf)==0){
            retorno =0;
            break;
        }
    } 
     
    if(retorno ==0)
    	return retorno;
      
    // transforma os caracteres do cpf em números     
    for(cont=0;cont<strlen(cpf);cont++){
        dig[cont] = cpf[cont] - '0';
    }
     
    // obtem o primeiro digito verificador
    aux2=10;
    for(cont=0;cont<9;cont++,aux2--){
        soma+= dig[cont] * aux2;
    }
    digVeri[0]=soma % 11;
    digVeri[0]= digVeri[0]<2 ? 0 : 11-digVeri[0];
     
    // obtem o segundo digito verificador
    soma=0;
    aux2=11;
    for(cont=0;cont<10;cont++,aux2--){
        if(cont==9)
            soma+= digVeri[0] * aux2;
        else
            soma+= dig[cont] * aux2;
    }
    digVeri[1]=soma % 11;
    digVeri[1]= digVeri[1]<2 ? 0 : 11-digVeri[1];
    if(digVeri[0]!=dig[9] || digVeri[1]!=dig[10]){
        retorno =0;               
    }
    return retorno;
}
/**************************************************************
*  Nome      : formataCPF                                     *  
*  Descricao : Formata um CPF                                 *
*  Parâmetros: endereço inicial da string cpf                 *
*  Retorno   : endereço de memória onde comeca a string       * 
*               com CPF formatado ou NULL                     *
**************************************************************/ 
char * formataCPF (char *cpf){
static char cpfFormatado[15];
   if(validaCPF(cpf) == 0)
      return NULL;
   else{
        sprintf(cpfFormatado,"%3.3s.%3.3s.%3.3s-%2.2s",cpf,cpf+3,cpf+6,cpf+9);
        return cpfFormatado;    
   }   
}
/**************************************************************
*  Nome      : formataEstado                                  *  
*  Descricao : colocar maiúsculo o estado                     *
*  Parâmetros: endereço inicial da string estado              *
*  Retorno   : endereço de memória onde comeca a string       * 
*               com Estado formatado ou NULL                  *
**************************************************************/ 
char * maicusculo(char *estado){
	static char Estado[3];
	Estado[0]=toupper(estado[0]);
	Estado[1]=toupper(estado[1]);
	Estado[2]=toupper(estado[2]);
	return Estado; 
}

/***********************************************************
*  Nome      : novaFgets                                   *  
*  Descricao : Le uma string usando a fgets e tira o \n    *
*  Parâmetros: endereço da string                          *
*              tamanho máximo                              * 
*  Retorno   :  NULL ou endereço da string                 * 
************************************************************/ 
char * novaFgets(char *texto, int tamanho){
char *retorno;
   // limpa o buffer de teclado 
   fflush(stdin);      
   if((retorno = fgets(texto,tamanho,stdin)) != NULL){
        if(texto[strlen(texto)-1] == '\n')
          texto[strlen(texto)-1] = '\0';                             
   }
   // limpa o buffer de teclado para eliminar caracteres que foram fornecidos além do tamnho especificado
   fflush(stdin);      
   return retorno;  
}
/***********************************************************
*  Nome      : strIstr                                     *  
*  Descricao : compara duas strings ignorando case         *
*  Parâmetros:                                             *
*             duas strings                                 *
*  Retorno   :                                             * 
*            endereço foi encontrada a string ou NULL      * 
************************************************************/
char * strIstr(char *str1, char *str2){
char*pStr1,*pStr2;
char *retorno=NULL;
   pStr1 = (char*) malloc(sizeof(char) * (strlen(str1)+1));
   if(pStr1 != NULL){
        strcpy(pStr1,str1);
        strUpper(pStr1);
        pStr2 = (char*) malloc(sizeof(char) * (strlen(str2)+1));
        if(pStr2 != NULL){
           strcpy(pStr2,str2);
           strUpper(pStr2);
           retorno = strstr(pStr1,pStr2);
           free(pStr1);
           free(pStr2);
        }  
        else{
        	free(pStr1);
        }     
   }  
   return retorno;  
} 
/****************************************************************
*  Nome      : excluiRegArq                                     *  
*  Descricao : Excluir um registro de um arquivo                *
*  Parâmetros: endereço inicial da string com o nome do arquivo *
*              tamanho de cada registro do arquivo(fixo)        *
*              número do registro a excluir                     *
*              endereço de memória onde será armazenado o erro  *   
*  Retorno   : mensagem de erro                                 * 
*****************************************************************/ 
char * excluiRegArq(char *nomeArq, int tamReg, int regExcluir,int *existeErro){
FILE *arq, *arqTemp;
int cont=0;
char *dados;
static char mensagem[100];
      mensagem[0] = '\0'; 
      *existeErro =0;
      if((arq = fopen(nomeArq,"rb"))== NULL){
           sprintf(mensagem," Erro ao abrir arquivo  para exclusao");    
           *existeErro  = 1;
      }
      else{       
        if((arqTemp = fopen("arqTemp.txt","wb")) ==NULL){
           fclose(arq);
           sprintf(mensagem," Erro ao criar arquivo para exclusao");    
           *existeErro  = 2; 
        }
        else{
          if((dados = (char*)malloc(sizeof(char)*tamReg)) == NULL){
             sprintf(mensagem," Erro ao alocar memoria para exclusao");            
             *existeErro  = 3;
          }
          else{
              while(!feof(arq)){
                if(fread(dados,tamReg,1,arq)==1){
                    cont++;
                    if(cont != regExcluir){
                      if(fwrite(dados,tamReg,1,arqTemp)!=1){
                         sprintf(mensagem,"Erro ao gravar dados para copia ");
                         *existeErro = 4;
                      }
                    } 
                }
                else{
                  if(!feof(arq)){
                     sprintf(mensagem,"Erro ao ler dados para copia");
                     *existeErro = 5;
                  }   
                }  
              }
              free(dados);
          }
          if(fclose(arq) != 0){
                sprintf(mensagem,"Erro ao fechar arquivo para exclusao");
                *existeErro = 6;
          }      
          if(fclose(arqTemp) != 0){
                sprintf(mensagem,"Erro ao fechar arquivo temporario exclusao");
                *existeErro = 7;
          }      
        }
      }
      
      if(!*existeErro){
          if(remove(nomeArq) != 0){
             sprintf(mensagem,"Erro ao remover aquivo original");
             *existeErro = 8;
          }   
          else{   
            if(rename("arqTemp.txt",nomeArq)!=0){
               sprintf(mensagem,"erro ao renomear arquivo");
               *existeErro = 9;
            }   
          }  
      } 
      return mensagem;   
} 
// Objetivo   : Validar o tefelone
// Parâmetros : um char telefone
// Retorno   :  um numero inteiro o para 0 valido e 1,2 para não valido
int validarTelefone(char telefone[]){
	int flag=0,tel,cont;
	char telef[3];
	int vet[68]={11,12,13,14,15,16,17,18,19,21,22,24,27,28,31,32,33,34,35,37,38,41,42,43,44,45,46,47,48,49,51,53,54,55,61,62,62,63,64,65,66,67,68,69,71,73,74,75,77,79,81,82,83,84,85,
				 86,87,88,89,91,92,93,94,95,96,97,98,99};
	
	telef[0]= telefone[0];
	telef[1]= telefone[1];
	telef[2]= '\0';
	tel=atoi(telef);

	for(cont=0;cont<68;cont++){
		if(tel==vet[cont]){
			if(strlen(telefone)==11 || strlen(telefone)==10){
				flag=0;
				break;
			} else {
				flag=1;
				break;
			}	
		}else{
			flag=2;
		}
	}
	
	return flag;
}
// Objetivo   : Validar o estado 
// Parâmetros : um ponteiro char
// Retorno   :  um inteiro 0 para valido e 1 para invalido
int validarEstado(char *estado){
	int flag;
	char Estado[3];
	
	Estado[0]=toupper(estado[0]);
	Estado[1]=toupper(estado[1]);
	Estado[2]='\0';
	
	
	if(strcmp(Estado,"AC")==0 || strcmp(Estado,"AL")==0 || strcmp(Estado,"AP")==0 || strcmp(Estado,"AM")==0 || strcmp(Estado,"BA")==0 || strcmp(Estado,"CE")==0 || 
	   strcmp(Estado,"DF")==0 || strcmp(Estado,"ES")==0 || strcmp(Estado,"GO")==0 || strcmp(Estado,"MA")==0 || strcmp(Estado,"MT")==0 || strcmp(Estado,"MS")==0 || 
	   strcmp(Estado,"MG")==0 || strcmp(Estado,"PA")==0 || strcmp(Estado,"PB")==0 || strcmp(Estado,"PR")==0 || strcmp(Estado,"PE")==0 || strcmp(Estado,"PI")==0 || 
	   strcmp(Estado,"RJ")==0 || strcmp(Estado,"RN")==0 || strcmp(Estado,"RS")==0 || strcmp(Estado,"RO")==0 || strcmp(Estado,"RR")==0 || strcmp(Estado,"SC")==0 ||
	   strcmp(Estado,"SP")==0 || strcmp(Estado,"SE")==0 || strcmp(Estado,"TO")==0 ){
	   	
	   	 	flag=0;
	} else{
		flag=1;
	}
	
	return flag;
	
}

// Objetivo   :Ler o nome e o local da farmaria e quarda em um arquivo, cria o arquiva apenas a primeira vez
// Parâmetros : Ponteiro nome 
// Retorno   : Nenhum
void leNomeDaFarmacia(char *Nome){
	
	int tam;
	char nome[28],local[30],nom[76]={"Empresa: "},loc[8]={"local: "}, *lerDoArquivo;
	FILE *arquivo,*arquivo1;
	
	arquivo=fopen("nome_Empresa.txt","rb");
	if(arquivo==NULL){
		arquivo1=fopen("nome_Empresa.txt","wb");
		do{
			printf("informe o nome da empresa: ");
			fflush(stdin);
			novaFgets(nome, sizeof(nome));
			system("cls");	
		}while(strlen(nome)==0 || nome[0]==32);
		do{
			printf("informe o local da empresa: ");
			fflush(stdin);
			novaFgets(local, sizeof(local));
			system("cls");
			
		}while(strlen(nome)==0 || nome[0]==32);	
		
		strcat(nom,nome);
		strcat(nom,"   ");
		strcat(nom,loc);
		strcat(nom,local);
		strcpy(Nome,nom);
		
		fwrite(nom,1,sizeof(nom),arquivo1);
	} else{
		arquivo1=fopen("nome_Empresa.txt","rb");
		fseek(arquivo1,0,SEEK_END);
		tam=ftell(arquivo1);
		rewind(arquivo1);
		lerDoArquivo = malloc(sizeof(char)*tam);	
		fread(lerDoArquivo,1,tam,arquivo1);
		strcpy(Nome,lerDoArquivo);	
			
	} 
	
	fclose(arquivo1);
	fclose(arquivo);
}


/***
*  Nome      : validaData                                  *
*  Descricao : Efetua a validação de uma data a partir das *
*             informações do dia mes e ano (com seculo)    *
*  Parâmetros:                                             *
*             dia, mes e ano                               *
*  Retorno   :                                             * 
*            1 - data valida                               * 
*            0 - data invalida                             *
**/ 
int validaData(int dia, int mes, int ano)
{
int retorno=1;
    if(ano<0 || mes<1 || mes >12 || dia >31)
       return 0;
    switch(mes)
    {
       case 4:
       case 6:
       case 9:
       case 11:
            if(dia > 30)
               retorno =0;
            break;
       case 2:
            printf(" %d\n",(ano%4 == 0 && ano %100 !=0) ||(ano % 400 == 0));
            if((ano%4 == 0 && ano %100 !=0) ||(ano % 400 == 0))
            {
               if(dia >29)
                  retorno = 0;
            }
            else
            {
               if(dia >28)
                  retorno =0;
            }
            break;
    }
    return retorno;
}

