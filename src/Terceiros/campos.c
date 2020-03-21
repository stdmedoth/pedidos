gchar *codigos_ter=NULL;
gchar *doc_ter=NULL;
gchar *nomes_ter=NULL;
gchar *endereco_ter=NULL;
gchar *tipo_ter=NULL;
gchar *celular_ter=NULL;
gchar *telefone_ter=NULL;
gchar *contatot_ter=NULL;
gchar *contatoc_ter=NULL;

GtkWidget *code_ter_field, *doc_ter_field, *name_ter_field, *address_ter_field, *type_ter_field;
GtkWidget *code_label, *doc_label, *name_label, *address_label, *type_label,
*telefone_label, *contatot_label,
*celular_label, *contatoc_label;
GtkWidget *code_entry, *doc_entry, *name_entry, *address_entry, *type_entry,
*celular_entry, *contatoc_entry,
*telefone_entry, *contatot_entry;

static int codigos_ter_err=0, doc_ter_err=0, nomes_ter_err=0,endereco_ter_err=0,tipo_ter_err=0;

GtkWidget *janela;
GtkWidget *win_tipo_ter;

#define CONECT_QNT 1
#define CNPJ_N_LEN 14
#define CNPJ_S_LEN 18

#define CPF_N_LEN 14
#define CPF_S_LEN 18

int alterando=0;

#include "campos/codigo.c"
#include "campos/cnpj.c"
#include "campos/cpf.c"
#include "campos/nome.c"
#include "campos/endereco.c"
#include "campos/tipo.c"
#include "campos/contatos.c"
