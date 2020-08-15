int cad_titulos_pageber();

GtkWidget *cad_pag_cli_psq_button, *cad_pag_tit_psq_button, *cad_pag_ped_psq_button, *cad_pag_datacri_psq_button, *cad_pag_datavenc_psq_button;

GtkWidget *cad_pag_concluir_button, *cad_pag_cancelar_button, *cad_pag_excluir_button, *cad_pag_alterar_button;

GtkWidget *cad_pag_code_entry;
GtkWidget *cad_pag_cli_entry, *cad_pag_cli_nome_entry;
GtkWidget *cad_pag_ped_entry;
GtkWidget *cad_pag_status_combo;
GtkWidget *cad_pag_parcela_spin;
GtkWidget *cad_pag_datacriacao_entry;
GtkWidget *cad_pag_datavencimento_entry;
GtkWidget *cad_pag_valor_entry;

char *cad_pag_code_gchar;
char *cad_pag_cli_gchar;
char *cad_pag_ped_gchar;
int cad_pag_status_int;
int cad_pag_parcela_int;
char *cad_pag_datacriacao_gchar;
char *cad_pag_datavencimento_gchar;
char *cad_pag_valor_gchar;

static int cad_pag_alterando=0, cad_pag_concluindo=0;


int cad_pag_cancelar_fun();
int cad_pag_alterar_fun();
int cad_pag_concluir_fun();

#include "campos/codigo.c"
#include "campos/parcela.c"
#include "campos/cliente.c"
#include "campos/pedido.c"
#include "campos/status.c"
#include "campos/datacriacao.c"
#include "campos/datavencimento.c"
#include "campos/valor.c"

#include "cancelar.c"
#include "alterar.c"
#include "concluir.c"
