#include "estruturaProjeto.h"

void cadastraVenda(char *nome);
int pesquisaCodigoMedicamento(char *codigo,int *quantEstoq,float *compra,int *dia,int *mes, int *ano);
void obtemDataHoraAtual(int *dia, int * mes, int *ano);
void alteraControleCliente(char *idCliente);
void alteraMedicamentoEstoque(char *codigo,int quantEstoque);
void apresentaVenda(char *nome);
Venda * obtemDadosArquivoVenda(int *qtde);
void excluiVenda(char *nome);
int pesquisarVenda(char *nome);
int leRegVenda(int seq, Venda *venda);
int pesquisaClienteNaVenda(char *id, int numero);
int pesquisaMedicamentoNaVenda(char *id, int numero);
int pesquisaDataNaVenda(int Dia,int Mes,int Ano, int numero);
void alteraMedicamentoEstoq(char *codigo,int quantEstoque);
void alteraControleClient(char *idCliente);
void alteraControleMedicamento(char *idMedicamento);
void alteraControleMedicamentoMais(char *idMedicamento);
