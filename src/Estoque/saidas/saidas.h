GtkWidget *est_said_cod_entry;
GtkWidget *est_said_prod_entry;
GtkWidget *est_said_subgrp_entry;
GtkWidget *est_said_qnt_entry;
GtkWidget *est_said_tipo_combo;
GtkWidget *est_said_data_entry;
GtkWidget *est_said_client_entry;

GtkWidget *est_said_est_combo;
gint est_said_est_int;

GtkWidget *est_said_ped_entry;

GtkWidget *est_said_campo_nome_prod;
GtkWidget *est_said_campo_subgrp_prod;
GtkWidget *est_said_campo_nome_client;

gint est_said_tipo_int;

GtkWidget *est_said_confirma_button, 
*est_said_cancela_button, 
*est_said_pesquisa_button, 
*est_said_altera_button, 
*est_said_exclui_button;

gchar *est_said_cod_gchar,
*est_said_prod_gchar,
*est_said_subgrp_gchar,
*est_said_qnt_gchar,
*est_said_data_gchar,
*est_said_client_gchar,
*est_said_ped_gchar;

#include "campos/codigo.c"
#include "campos/produto.c"
#include "campos/subgrupo.c"
#include "campos/tipo.c"
#include "campos/data.c"
#include "campos/quantidade.c"
#include "campos/cliente.c"
#include "campos/estoque.c"
#include "campos/pedido.c"

#include "confirmar.c"
