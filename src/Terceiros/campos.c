#define MAX_EMAIL_LEN 100
#define MAX_OBS_LEN 500
#define CAMPOS_QNT 11
#define MAX_PROD 100
#define CONECT_QNT 1
#define CNPJ_N_LEN 14
#define CNPJ_S_LEN 18
#define CPF_N_LEN 11
#define CPF_S_LEN 14
#define INSERT_QUERY 96

gchar *codigos_ter=NULL;
gchar *doc_ter=NULL;
gchar *nomes_ter=NULL;
gchar *endereco_ter=NULL;
gchar *cep_ter=NULL;
gchar *tipo_ter=NULL;
gchar *celular_ter=NULL;
gchar *telefone_ter=NULL;
gchar *contatot_ter=NULL;
gchar *contatoc_ter=NULL;
gchar *email_ter=NULL;
gchar *contatoe_ter=NULL;
gchar *observacoes_ter=NULL;

int tipo_doc;
GtkWidget *doc_combo;

GtkWidget *code_ter_field, *doc_ter_field, *name_ter_field, *address_ter_field, *cep_ter_field, *type_ter_field,
*telefone_ter_field, *contatot_ter_field, *celular_ter_field, *contatoc_ter_field, 
*email_ter_field, *contatoe_ter_field, *observacoes_ter_field;

GtkWidget *code_label, *doc_label, *name_label, *address_label, *cep_ter_label,*type_label,
*telefone_label, *contatot_label, *celular_label, *contatoc_label, 
*email_label, *contatoe_label, *observacoes_label;

int codigos_ter_prod[MAX_PROD];
GtkWidget *lista_prod_label;
GtkWidget **produto_label,
**preco_entry, 
**precos_caixas, 
**atualizar_preco, 
**remover_preco,
*precos_scroll_caixa,
*precos_scroll_window;


struct parametros
{
	int doc;
	int nome;
	int endereco;
	int tipo;
	int celular;
	int contatoc;
	int telefone;
	int contatot;
	int email;
	int contatoe;
	int observacoes;
}criticar;

int vet_erro[CAMPOS_QNT];
#define COD_ERR 0
#define DOC_ERR 1
#define NOM_ERR 2
#define END_ERR 3
#define TIP_ERR 4
#define CEL_ERR 5
#define CNC_ERR 6
#define TEL_ERR 7
#define CNT_ERR 8
#define EML_ERR 9
#define CNE_ERR 10
#define OBS_ERR 11
//cod
//doc
//nome
//endereco
//tipo
//celular
//contatoc
//telefone
//contatot
//email
//contatoe
//observacoes

GtkWidget *janela;
GtkWidget *acao_atual,*acao_atual2;
GtkWidget *win_tipo_ter;


int alterando=0;

#include "campos/codigo.c"
#include "campos/cnpj.c"
#include "campos/cpf.c"
#include "campos/escolher_doc.c"
#include "campos/nome.c"
#include "campos/endereco.c"
#include "campos/tipo.c"
#include "campos/contatos.c"
#include "campos/observacoes.c"
#include "campos/email.c"
#include "campos/precos.c"
