gchar *codigos_prod;
gchar *nomes_prod;
gchar *preco_prod;
gchar *fornecedor_prod;
gchar *unidade_prod;
GtkWidget *janela;
GtkWidget *code_label, *code_field;
GtkWidget *name_label, *name_field;
GtkWidget *price_label,*price_field;
GtkWidget *supp_label, *supp_field;
GtkWidget *und_label,  *und_field;
GtkWidget *sigla_label,*sigla_field;
GtkWidget *mult_label, *mult_field;
GtkWidget *concluir , *alterar, *listar, *excluir;

int codigos_prod_err=0,
    nomes_prod_err=0,
    preco_prod_err=0,
    fornecedor_prod_err=0,
    unidade_prod_err=0;

#include "campos/codigo.c"
#include "campos/nome.c"
#include "campos/preco.c"
#include "campos/fornecedor.c"
#include "campos/unidade.c"
