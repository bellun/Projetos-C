void leInt(int *nroInt, char *titulo, int linha, int coluna);
void leFloat(float *nroFloat, char *titulo, int linha, int coluna);
void strUpper(char * str);
void tiraBrEsq(char *str);
void tiraBrDir(char *str);
void desenhaMoldura(int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal,int corFundoAtual, int corLetraAtual);
void limpaJanela(int linhaInicial,int colunaInicial,int linhaFinal, int colFinal,int corFundo);
int menuVertical(int n,char *imenu[],int c1,int c2,int linha,int coluna,int ini, int moldura,int corFundoAtual, int corLetraAtual);
void retornaCor(int corFundo,int corTexto);

char * formataCPF (char *cpf);
char * maicusculo(char *estado);
int validaCPF (char *cpf);

char * novaFgets(char *texto, int tamanho); //validar texto

char * strIstr(char *str1, char *str2);
char * excluiRegArq(char *nomeArq, int tamReg, int regExcluir,int *existeErro);
int validarTelefone(char telefone[]);
int validarEstado(char estado[]);
void leNomeDaFarmacia(char *Nome);

int validaData(int dia, int mes, int ano);
int validaDataRestrita(int dia, int mes, int ano);
