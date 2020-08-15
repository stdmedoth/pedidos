int relat_fix_est();

GtkWidget *relat_fix_est_ordem_combo,
*relat_fix_est_prod_entry1,*relat_fix_est_prod_entry2,
*relat_fix_est_grp_entry1,*relat_fix_est_grp_entry2,
*relat_fix_est_cli_entry1,*relat_fix_est_cli_entry2,
*relat_fix_est_quebra_check,
*relat_fix_est_quebra_combo,
*relat_fix_est_sintetiza_combo,
*relat_fix_est_totaliza_combo,
*relat_fix_est_ped_entry1,*relat_fix_est_ped_entry2,
*relat_fix_est_data_entry1,*relat_fix_est_data_entry2,
*relat_fix_est_est_entry1,*relat_fix_est_est_entry2;

gchar *relat_fix_est_ped_gchar1,*relat_fix_est_ped_gchar2,
*relat_fix_est_prod_gchar1,*relat_fix_est_prod_gchar2,
*relat_fix_est_grp_gchar1,*relat_fix_est_grp_gchar2,
*relat_fix_est_est_gchar1,*relat_fix_est_est_gchar2;

gint relat_fix_est_ordem_int,
relat_fix_est_quebra_flag,
relat_fix_est_quebra_int,
relat_fix_est_sintetiza_int,
relat_fix_est_totaliza_int;

GtkWidget *relat_fix_est_gerar_button;

struct relat_vlrs relat_fix_est_vlrs;

#include "campos/pedidos.c"
#include "campos/produtos.c"
#include "campos/grupos.c"
#include "campos/estoque.c"
#include "campos/quebra.c"
#include "campos/sintetiza.c"
#include "campos/totaliza.c"
#include "gerar.c"
