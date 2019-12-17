#include "estruturaProjeto.h"

void cadastraMedicamento(char *nome);
int pesquisaCodigo(char *codigo);
void apresentaMedicamento(char *codigo,char *nome);
Medicamento * obtemDadosArquivoMedicamento(int *qtde);
void pesquisaMedicamento(char *Nome);
void excluiMedicamento(char *nome);
int leRegMedicamento(int seq, Medicamento *medicamento);
void alteraMedicamento(char *nome);
int validarCodigoAlfanumerico(char *codigo);
int validaDataRestrita(int dia, int mes, int ano);
int valida_data(int dia, int mes, int ano);

