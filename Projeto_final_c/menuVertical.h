
/**************************************************************
*  Nome      : menuVertical                                   *  
*  Descricao : Apresenta um menu vertical e retorna a opcao   *
*              selecionada                                    * 
*  Parâmetros: n - Numero de itens                            *
*              imenu - Descrição dos itens                    *
*              c1 - cor do texto do menu                      *
*              c2 - cor da marca do item selecionado          *
*              linha - linha inicial para instalação do menu  *
*              coluna - coluna inicial para instalação do menu*
*              ini - número da opção inicial do menu a ser    *
*                        selecionada                          *
*              moldura - indicador se deve desenhar o menu    *
*                 dentro de uma moldura                       *
*              corFundoAtual - cor do fundo a ser restituida a*
*                 tela com a retirada do menu                 *      
*              corLetra - cor da letra a ser restituida a     *
*                 tela com a retirada do menu                 *      
*  Retorno   : número do item do menu selecionado             * 
**************************************************************/ 
int menuVertical(int n,char *imenu[],int c1,int c2,int linha,int coluna,int ini,int moldura,int corFundoAtual, int corLetraAtual)
{
		char tecla;	// Recebe a tecla pressionada
		int sel_b;	// Selecao de backup do menu
		int sel;
		int i;  		
		int val;		// 1 = tecla valida encontrada
						// 0 = tecla valida nao encontrada
        int tamMaiorTexto;
        // verifica se desenha com moldura e menu comeca na linha 1
        if(linha ==1 && moldura)
           linha++;
        // verifica se desenha com moldura e menu comeca na coluna 1
        if(coluna== 1 && moldura)
           coluna++;
            
		textcolor(c1);	// Atributo da cor das letras
		if(ini < 1)
		    ini=1;
		else if(ini>n)
           ini=n;
               
		sel=ini-1; 	// Primeiro item selecionado
		for (i=0;i<=n-1;i++)
			{
			    
				if (i==ini-1) textbackground(c2); // Escreve itens do menu
				else textbackground(corFundoAtual);           // e seleciona o item inicial
				gotoxy(coluna,linha+i);                    // setado no argumento passado
				printf(imenu[i]);
				if(i==0)
				  tamMaiorTexto = strlen(imenu[i]);
				else if(strlen(imenu[i]) > tamMaiorTexto)
				  tamMaiorTexto = strlen(imenu[i]);
                
			}
			// desenha a moldura
			if(moldura)
			{
			    desenhaMoldura(linha-1,coluna-1,linha+n,coluna+tamMaiorTexto+2,
                     corFundoAtual, corLetraAtual);
			}    
		do
			{
				do
					{
//						do
//							{
//							} while (!kbhit());
						tecla=getch();
						tecla=toupper(tecla); 

						// Verificar pelas teclas validas pressionadas
						if (tecla==72||tecla==75||tecla==65) val=1;
						else 	if (tecla==77||tecla==80||tecla==90) val=1;
								else 	if (tecla==27||tecla==13) val=1;
										else val=0;

					} while (!val);
				sel_b=sel; // Backup do item atual antes de modifica-lo
				if (tecla==72||tecla==75||tecla==65) sel--; // Sobe
				if (tecla==80||tecla==77||tecla==90) sel++; // Desce
				if (tecla==27) sel_b=-1; 		  // Sai com ESC
				if (sel<=-1) sel=n-1; // Se for menor vai para o ultmo item
				if (sel>=n) sel=0; // Se for maior vai para o primeiro item
				textcolor(c1);
				if (tecla!=13&&tecla!=27)
					{
						// Desseleciona o antigo item do menu...
						gotoxy(coluna,sel_b+linha); textbackground(corFundoAtual); printf(imenu[sel_b]);
						// Seleciona o novo item do menu...
						gotoxy(coluna,sel+linha); textbackground(c2); printf(imenu[sel]);
						// Descarrega o buffer do teclado...
						fflush(stdin);
					}
					
			} while (tecla!=13&&tecla!=27);

		return(sel_b+1); 	// Retorna item selecionado + 1 (nao retorna 0)
}
/**************************************************************
*  Nome      : desenhaMoldura                                 *  
*  Descricao : Desenha uma moldura na tela                    *
*  Parâmetros: linhaInicial - linha inicial da moldura        *
*              colunaInicial - coluna inicial da moldura      *
*              linhaFinal   - linha final da moldura          *
*              colunaFinal - coluna final da moldura          *
*              corFundoAtual - cor do fundo atual             *
*              corLetra  - cor do fundo atual                 *
*  Retorno   : nenhum                                         * 
**************************************************************/ 

void desenhaMoldura(int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal,int corFundoAtual, int corLetraAtual){
    int i=0,qtdeLinhas,qtdeColunas;
    
    qtdeLinhas  = linhaFinal - linhaInicial ;
    qtdeColunas = colunaFinal - colunaInicial ;
    textbackground(7);
    textcolor(8);
    // faz a borda superior
    gotoxy(colunaInicial,linhaInicial);
    for(i=0;i<=qtdeColunas;i++)
    {
        printf("\xCD");
    }

    // faz a borda inferior
    gotoxy(colunaInicial,linhaInicial+qtdeLinhas);
    for(i=0;i<=qtdeColunas;i++)
    {
        printf("\xCD");
    }

    // faz a lateral esquerda    
    for(i=0;i<=qtdeLinhas;i++)
    {
        gotoxy(colunaInicial,linhaInicial+i);
        printf("\xBA");
    }
    // faz a lateral direita
    for(i=0;i<=qtdeLinhas;i++)
    {
        gotoxy(colunaInicial+qtdeColunas,linhaInicial+i);
        printf("\xBA");
    }

    // fecha os cantos da moldura
    gotoxy(colunaInicial,linhaInicial);
    printf("\xC9");
    gotoxy(colunaInicial+qtdeColunas,linhaInicial);
    printf("\xBB");
    gotoxy(colunaInicial,linhaInicial+qtdeLinhas);
    printf("\xC8");
    gotoxy(colunaInicial+qtdeColunas,linhaInicial+qtdeLinhas);
    printf("\xBC");
    retornaCor(corFundoAtual, corLetraAtual);
}

/**************************************************************
*  Nome      : limpaJanela                                    *  
*  Descricao : limpa uma janela da tela                       *
*  Parâmetros: linhaInicial - linha inicial da janela         *
*              colunaInicial - coluna inicial da janela       *
*              linhaFinal   - linha final da janela           *
*              colunaFinal - coluna final da janela           *
*              corFundo - cor do fundo da janela a ser limpa  *
*  Retorno   : nenhum                                         * 
**************************************************************/ 
void limpaJanela(int linhaInicial,int colunaInicial,int linhaFinal, int colFinal,int corFundo){
int coluna=0,linha=0;

    for(coluna=colFinal;coluna>=colunaInicial;coluna--)
    {
        for(linha=linhaFinal;linha>=linhaInicial;linha--)        
        {
            textbackground(corFundo);
            gotoxy(coluna,linha);
            printf(" ");

        }
    }


}
/**************************************************************
*  Nome      : retornaCor                                     *  
*  Descricao : retorna a cor de fundo e de texto              *
*  Parâmetros: corFundo - cor de fundo                        *
*              corTexto - cor do texto                        *
*  Retorno   : nenhum                                         * 
**************************************************************/ 
void retornaCor(int corFundo,int corTexto){
    textbackground(corFundo);
    textcolor(corTexto);
}  
