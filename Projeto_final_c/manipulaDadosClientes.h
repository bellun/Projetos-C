#include "estruturaProjeto.h"

int pesquisaMatriculaCliente(char *matricula);
void cadastraCliente(char *nome);
void pesquisaCliente(char *Nome);
Cliente * obtemDadosArquivoCliente(int *qtde);
void ordenaClientes(int qtde, Cliente *clientes);
void excluiCliente(char *nome);
int leRegCliente(int seq, Cliente *cliente);
void apresentaClientes(char *CPf,char *nome);
int comparaNomeClientes(const void * p1, const void *p2);
void alteraCliente(char *nome);
