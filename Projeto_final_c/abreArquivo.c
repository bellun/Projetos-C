#include <stdio.h>
#include "apresentaMensagem.h"

// função - abre um arquivo qualquer
// parâmetros - endereço de memória onde localiza-se o nome do arquivo
//               endereço de memória onde localiza-se o modo de abertura do arquivo
//               indicador se deve ser apresentada mensagem no caso de erro
// retorno - endereço de memória onde localiza-se a estrutura FILE ou NULL no 
//            caso de erro
FILE * abreArquivo(char *nomeArq,char *modo,int apresMsg)
{
FILE *arq;
char msg[200];
   arq = fopen(nomeArq,modo);
   if(arq == NULL)
   {
      if(apresMsg == 1)
      {  
         sprintf(msg," Erro ao abrir arquivo (%s) no modo (%s)\n",nomeArq,modo);
         apresentaMsgErro(msg,"abreArquivo");
      }   
   }
   return arq;
}
