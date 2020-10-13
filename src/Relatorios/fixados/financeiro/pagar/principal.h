int rel_fix_fin_pag_gerar();

int rel_fix_fin_pag_validar();

int rel_fix_fin_pag();

GtkWidget *rel_fix_fin_pag_tit_entry1,*rel_fix_fin_pag_tit_entry2,
*rel_fix_fin_pag_bx_entry1,*rel_fix_fin_pag_bx_entry2,
*rel_fix_fin_pag_ped_entry1,*rel_fix_fin_pag_ped_entry2,
*rel_fix_fin_pag_cli_entry1,*rel_fix_fin_pag_cli_entry2,
*rel_fix_fin_pag_status_combo,
*rel_fix_fin_pag_datacriacao_entry1,*rel_fix_fin_pag_datacriacao_entry2,
*rel_fix_fin_pag_databaixa_entry1,*rel_fix_fin_pag_databaixa_entry2,
*rel_fix_fin_pag_datavencimento_entry1,*rel_fix_fin_pag_datavencimento_entry2,
*rel_fix_fin_pag_valor_combo,*rel_fix_fin_pag_valor_entry;

GtkWidget *rel_fix_fin_pag_tit_button1,*rel_fix_fin_pag_tit_button2,
*rel_fix_fin_pag_bx_button1,*rel_fix_fin_pag_bx_button2,
*rel_fix_fin_pag_ped_button1,*rel_fix_fin_pag_ped_button2,
*rel_fix_fin_pag_cli_button1,*rel_fix_fin_pag_cli_button2,
*rel_fix_fin_pag_datacriacao_button1,*rel_fix_fin_pag_datacriacao_button2,
*rel_fix_fin_pag_databaixa_button1,*rel_fix_fin_pag_databaixa_button2,
*rel_fix_fin_pag_datavencimento_button1,*rel_fix_fin_pag_datavencimento_button2;

gchar *rel_fix_fin_pag_tit_gchar1,*rel_fix_fin_pag_tit_gchar2,
*rel_fix_fin_pag_bx_gchar1,*rel_fix_fin_pag_bx_gchar2,
*rel_fix_fin_pag_ped_gchar1,*rel_fix_fin_pag_ped_gchar2,
*rel_fix_fin_pag_cli_gchar1,*rel_fix_fin_pag_cli_gchar2,
*rel_fix_fin_pag_datacriacao_gchar1,*rel_fix_fin_pag_datacriacao_gchar2,
*rel_fix_fin_pag_databaixa_gchar1,*rel_fix_fin_pag_databaixa_gchar2,
*rel_fix_fin_pag_datavencimento_gchar1,*rel_fix_fin_pag_datavencimento_gchar2,
*rel_fix_fin_pag_valor_gchar;

gint rel_fix_fin_pag_valor_int, rel_fix_fin_pag_status_int;


#include "campos/titulo.c"
#include "campos/baixa.c"
#include "campos/cliente.c"
#include "campos/criacaotit.c"
#include "campos/databaixa.c"
#include "campos/datavencimento.c"
#include "campos/pedido.c"
#include "campos/status.c"
#include "campos/valor.c"

#include "gerar.c"
