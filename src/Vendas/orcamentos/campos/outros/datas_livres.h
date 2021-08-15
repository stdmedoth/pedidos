struct{
  int id;
  GtkWidget *entry1;
  GtkWidget *entry2;
  char *datas;
  float vlrs;
}datas_lives_str[MAX_PARCELAS_QNT];

GtkWidget *orc_pag_datas_parcqnt;
int orc_pag_datas_livres();

GtkWidget *orc_pag_datas_livres_qnt_entry,
*orc_pag_datas_livres_rest,
*orc_pag_datas_livres_fixed;

static int orc_pag_vetor[MAX_PARCELAS_QNT+1];
static int orc_parc_lvr_qnt_int;
int orc_pag_dl_dts_vlrs_fun();
int orc_pag_dl_vlrs_fun();
