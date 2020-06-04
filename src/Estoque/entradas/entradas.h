GtkWidget *est_ent_cod_entry,
*est_ent_prod_entry,
*est_ent_subgrp_entry,
*est_ent_qnt_entry,
*est_ent_tipo_combo,
*est_ent_data_entry,
*est_ent_client_entry;

GtkWidget *est_ent_campo_nome_prod,
*est_ent_campo_subgrp_prod,
*est_ent_campo_nome_client;

int est_ent_day_int,
est_ent_mon_int,
est_ent_year_int;

gint est_ent_tipo_int;

GtkWidget *est_ent_confirma_button, 
*est_ent_cancela_button, 
*est_ent_pesquisa_button, 
*est_ent_altera_button, 
*est_ent_exclui_button;

gchar *est_ent_cod_gchar,
*est_ent_prod_gchar,
*est_ent_subgrp_gchar,
*est_ent_qnt_gchar,
*est_ent_data_gchar,
*est_ent_client_gchar;


#include "campos/codigo.c"
#include "campos/produto.c"
#include "campos/subgrupo.c"
#include "campos/tipo.c"
#include "campos/data.c"
#include "campos/quantidade.c"
#include "campos/cliente.c"

#include "confirmar.c"
