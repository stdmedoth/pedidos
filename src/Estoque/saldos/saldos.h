/* 
select SUM(e.entradas) - SUM(e.saidas) from movimento_estoque as e inner join pedidos as p inner join Produto_Orcamento as O 
on e.pedido = p.code and O.code = p.code where O.produto = 1; 
*/
static GtkWidget *est_sld_prod_cod_entry, 
*est_sld_grp_cod_entry, 
*est_sld_cod_combo;

static GtkWidget *est_sld_prod_entry;
static GtkWidget *est_sld_prod_nome_entry,*est_sld_grp_nome_entry;

static GtkWidget *est_sld_concluir_button, 
*est_sld_alterar_button, 
*est_sld_cancelar_button;

static gint est_sld_prod_est_int;
static gchar *est_sld_prod_cod_gchar,  *est_sld_subgrp_cod_gchar;

#include "campos/produto.c"
#include "campos/subgrupo.c"
#include "campos/estoque.c"
