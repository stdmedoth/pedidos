gchar *codigos_und;
gchar *nomes_und;
gchar *sigla_und;
gchar *mult_und;

GtkWidget *code_label,*code_field;
GtkWidget *name_label,*name_field;
GtkWidget *sigla_label,*sigla_field;
GtkWidget *mult_label, *mult_field;

int codigos_und_err=0,
    nomes_und_err=0,
    sigla_und_err=0,
    mult_und_err=0;

#include "codigo.c"
#include "nome.c"
#include "sigla.c"
#include "multiplo.c"
