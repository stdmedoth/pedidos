static GtkWidget *est_ent_cod_entry,
*est_ent_prod_entry,
*est_ent_ped_entry,
*est_ent_subgrp_entry,
*est_ent_qnt_entry,
*est_ent_tipo_combo,
*est_ent_data_entry,
*est_ent_client_entry;

GtkWidget *est_ent_est_combo;
gint est_ent_est_int;
gint cancelando_mov_ent_est;

static GtkWidget *est_ent_campo_nome_prod,
*est_ent_campo_subgrp_prod,
*est_ent_campo_nome_client;

int est_ent_day_int,
est_ent_mon_int,
est_ent_year_int;

static gint est_ent_tipo_int;

GtkWidget *est_ent_confirma_button,
*est_ent_cancela_button,
*est_ent_altera_button,
*est_ent_exclui_button;

static gchar *est_ent_cod_gchar,
*est_ent_prod_gchar,
*est_ent_subgrp_gchar,
*est_ent_qnt_gchar,
*est_ent_data_gchar,
*est_ent_client_gchar,
*est_ent_ped_gchar;

static int alterando_mov_ent_est=0, concluindo_mov_ent_est=0;

#define COD_MOV_EST 0
#define EST_MOV_EST 1
#define PED_MOV_EST 2
#define CLI_MOV_EST 3
#define PROD_MOV_EST 4
#define SUBGRP_MOV_EST 5
#define ENTS_MOV_EST 6
#define SAID_MOV_EST 7
#define DATA_MOV_EST 8
#define TIPO_MOV_EST 9

void est_ent_confirmar_fun();
void est_ent_cancelar_fun();
void est_ent_alterar_fun();

#include "campos/codigo.c"
#include "campos/produto.c"
#include "campos/subgrupo.c"
#include "campos/tipo.c"
#include "campos/data.c"
#include "campos/quantidade.c"
#include "campos/cliente.c"
#include "campos/estoque.c"
#include "campos/pedido.c"

#include "cancelar.c"
#include "confirmar.c"
#include "alterar.c"
