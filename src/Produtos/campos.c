gchar *codigos_prod=NULL;
gchar *nomes_prod=NULL;
gchar *precos_prod=NULL;
gchar *pesos_prod=NULL;
gchar *unidades_prod=NULL;
gchar *fornecedores_prod=NULL;
gchar *grupos_prod=NULL;;
gchar *marcas_prod=NULL;;
gchar *observacoes_prod=NULL;

int tipo_doc;
GtkWidget *doc_combo;

GtkWidget *codigo_prod_field, *nome_prod_field, *preco_prod_field,  *peso_prod_field, *unidade_prod_field,
*fornecedor_prod_field, *grupo_prod_field, *marca_prod_field, *observacao_prod_field;

GtkWidget *code_prod_label,  *nome_prod_label, *preco_prod_label, *peso_prod_label , *unidade_prod_label,
*fornecedor_prod_label, *grupo_prod_label, *marca_prod_label,  *observacao_prod_label;

GtkWidget *botao_mais;
GtkWidget *imagem_mais;

GtkWidget *campo_nome_fornecedor,*campo_nome_grupo;

int *codigo_preco;
/*
GtkWidget *lista_prod_label;
GtkWidget **produto_label,
**preco_entry, 
**precos_caixas, 
**atualizar_preco, 
**remover_preco,
*precos_scroll_caixa,
*precos_scroll_window,
**imagem_ok,
**imagem_cancel;
*/
GtkWidget *janela;
GtkWidget *acao_atual,*acao_atual2;
GtkWidget *win_tipo_prod;

#include "campos/codigo.c"
#include "campos/nome.c"
#include "campos/preco.c"
#include "campos/peso.c"
#include "campos/unidade.c"
#include "campos/grupo.c"
#include "campos/marca.c"
#include "campos/fornecedor.c"
#include "campos/observacao.c"
