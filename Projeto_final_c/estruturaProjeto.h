#ifndef ESTRUTURA_CLIENTE
#define ESTRUTURA_CLIENTE
#define TAM_NOME 61
#define TAM_NOME_MENU_VERTICAL 40
#define POS_NOME_MENU_VERTICAL 10

// declaração de um novo tipo de dado
typedef struct
{
  char nome[50];
  char CPF[13];
  char telefone[13];
  char descrEnd[34];
  char cidade[34];
  char estado[4];
  int controleCompras;
}Cliente;
// definições
#define APRES_MSG      1
#define NAO_APRES_MSG  0
#endif
//_________________________________________________________________________________________
//_________________________________________________________________________________________

#ifndef ESTRUTURA_MEDICAMENTO
#define ESTRUTURA_MEDICAMENTO
#define TAM_NOME 61
#define TAM_NOME_MENU_VERTICAL 40
#define POS_NOME_MENU_VERTICAL 10

typedef struct
{
  char DescricaoMedicamento[50],CodigoAlfanumerico[11];
  float valorUnitarioCompra,valorUnitarioVenda;
  int QuantEsto,dia,mes,ano;
  int controleCompras;
  
}Medicamento;
// definições
#define APRES_MSG      1
#define NAO_APRES_MSG  0
#endif
//_________________________________________________________________________________________
//_________________________________________________________________________________________


#ifndef ESTRUTURA_VENDA
#define ESTRUTURA_VENDA
#define TAM_NOME 61
#define TAM_NOME_MENU_VERTICAL 40
#define POS_NOME_MENU_VERTICAL 10

typedef struct
{
  char IdentificacaoDoClient[13];
  char IdentificacaoDoMedicamento[11];
  int QuantidadeVendida;
  float VaUnitarioCompra,VaUnitarioVenda;
  int dia,mes,ano;
  
}Venda;
// definições
#define APRES_MSG      1
#define NAO_APRES_MSG  0
#endif
