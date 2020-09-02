int relat_fix_vnd();

GtkWidget *relat_fix_vnd_ordem_combo,
*relat_fix_vnd_prod_entry1,*relat_fix_vnd_prod_entry2,
*relat_fix_vnd_grp_entry1,*relat_fix_vnd_grp_entry2,
*relat_fix_vnd_cli_entry1,*relat_fix_vnd_cli_entry2,
*relat_fix_vnd_status_combo,
*relat_fix_vnd_quebra_check,
*relat_fix_vnd_quebra_combo,
*relat_fix_vnd_sintetiza_combo,
*relat_fix_vnd_totaliza_combo,
*relat_fix_vnd_ped_entry1,*relat_fix_vnd_ped_entry2,
*relat_fix_vnd_data_entry1,*relat_fix_vnd_data_entry2,
*relat_fix_vnd_est_entry1,*relat_fix_vnd_est_entry2;

gchar *relat_fix_vnd_cli_gchar1, *relat_fix_vnd_cli_gchar2,
*relat_fix_vnd_ped_gchar1,*relat_fix_vnd_ped_gchar2,
*relat_fix_vnd_prod_gchar1,*relat_fix_vnd_prod_gchar2,
*relat_fix_vnd_grp_gchar1,*relat_fix_vnd_grp_gchar2,
*relat_fix_vnd_est_gchar1,*relat_fix_vnd_est_gchar2;

gint relat_fix_vnd_status_int,
relat_fix_vnd_ordem_int,
relat_fix_vnd_quebra_flag,
relat_fix_vnd_quebra_int,
relat_fix_vnd_sintetiza_int,
relat_fix_vnd_totaliza_int;

GtkWidget *relat_fix_vnd_gerar_button;

struct relat_vlrs relat_fix_vnd_vlrs;

#include "campos/pedidos.c"
#include "campos/produtos.c"
#include "campos/clientes.c"
#include "campos/grupos.c"
#include "campos/estoque.c"
#include "campos/quebra.c"
#include "campos/sintetiza.c"
#include "campos/status.c"
#include "campos/totaliza.c"
#include "gerar.c"
