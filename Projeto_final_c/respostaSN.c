#include <stdio.h>
#include <ctype.h>
char respostaSN(char *perg)
{
char resp;
   do
   {
      fprintf(stdout," %s S/N?",perg);
      resp = toupper(getch());
   }while(resp != 'S' && resp != 'N');
   return resp;
}
