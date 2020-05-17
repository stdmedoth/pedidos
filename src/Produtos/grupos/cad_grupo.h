GtkWidget *cod_grp_entry;
GtkWidget *nome_grp_entry;

GtkWidget *add_subgrp_button;
GtkWidget *add_subgrp_window;
GtkWidget *campo_nome_subgrg_pai, *campo_nome_subgrg;
GtkWidget *cod_subgrp_entry, *nome_subgrp_entry, *nome_subgrp_pai_label, *cod_subgrp_pai_entry;

GtkWidget *confirma_grp_button, *altera_grp_button, *cancela_grp_button, *exclui_grp_button, *psq_grp_button;
GtkWidget *confirma_subgrp_button, *altera_subgrp_button, *cancela_subgrp_button, *exclui_subgrp_button, *psq_subgrpo_button;
gchar *subgrpcode, *subgrpnome, *subgrp_paicode;

static GtkWidget *janela_grupo, *janela_subgrupo;
static gchar *grpcode, *grpnome;

int cod_subgrp();	
int nome_subgrp();	
int cancela_subgrupo();
int cancela_grupo();
int pai_subgrp();
int cad_grupo();
int altera_grupo();
int cad_subgrupo();
static int alterando_grp=0,concluindo_grp=0;;
static int alterando_subgrp=0, concluindo_subgrp=0;;

