#include <stdio.h>
#include "cores.h"
// função - apresenta uma mensagem de erro
// parâmetros - string contendo a msg de erro
//               string com o nomeda função que ocorreu o erro
//               indicador se deve ser apresentada mensagem no caso de erro
//Sem retorno
void apresentaMsgErro( char *msg, char * idFuncao)
{
  desenhaMoldura(22,5,24,75,BRANCO,PRETO);
  gotoxy(6,23);
  fprintf(stdout,"(%s) %s",idFuncao,msg);
  getch();
  limpaJanela(22,5,24,75,BRANCO);
}
