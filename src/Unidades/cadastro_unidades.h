gchar *codigos_und;
gchar *nomes_und;
gchar *sigla_und;
gchar *mult_und;

GtkWidget *code_und_label,   *code_und_field, *code_und_frame;
GtkWidget *name_und_label,   *name_und_field, *name_und_frame;
GtkWidget *sigla_und_label,  *sigla_und_field, *sigla_und_frame;
GtkWidget *mult_und_label,   *mult_und_field, *mult_und_frame;
GtkWidget *medida_und_label, *medida_und_field, *medida_und_frame;

int alterando_und=0;
#include "codigo.c"
#include "nome.c"
#include "sigla.c"
#include "multiplo.c"
