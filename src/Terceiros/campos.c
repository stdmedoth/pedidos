gchar *codigos_ter;
gchar *cnpj_ter;
gchar *nomes_ter;
gchar *endereco_ter;
gchar *tipo_ter;
GtkWidget *code_ter_field, *cnpj_ter_field, *name_ter_field, *address_ter_field, *type_ter_field;

GtkWidget *code_label, *cnpj_label, *name_label, *address_label, *type_label,
*telefone1_label, *contatot1_label,
*celular1_label, *contatoc1_label;

GtkWidget *code_entry, *cnpj_entry, *name_entry, *address_entry, *type_entry,
*celular1_entry, *contatoc1_entry,
*telefone1_entry, *contatot1_entry;


gchar *celular1_ter;
gchar *telefone1_ter;

gchar *contatot1_ter;
gchar *contatoc1_ter;

static int codigos_ter_err=0, cnpj_ter_err=0, nomes_ter_err=0,endereco_ter_err=0,tipo_ter_err=0;

GtkWidget *janela;
GtkWidget *win_tipo_ter;

#define CONECT_QNT 1
#define CNPJ_N_LEN 14
#define CNPJ_S_LEN 18


#include "campos/codigo.c"
#include "campos/cnpj.c"
#include "campos/nome.c"
#include "campos/endereco.c"
#include "campos/tipo.c"
#include "campos/contatos.c"
