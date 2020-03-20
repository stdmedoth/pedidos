gchar *codigos_ter;
gchar *nomes_ter;
gchar *endereco_ter;
gchar *tipo_ter;
GtkWidget *code_ter_field, *name_ter_field, *address_ter_field, *type_ter_field;
static int codigos_ter_err=0, nomes_ter_err=0,endereco_ter_err=0,tipo_ter_err=0;
GtkWidget *janela;
GtkWidget *win_tipo_ter;

#include "codigo.c"
#include "nome.c"
#include "endereco.c"
#include "tipo.c"
