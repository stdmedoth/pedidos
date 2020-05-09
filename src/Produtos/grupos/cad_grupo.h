GtkWidget *cod_grp_entry;
GtkWidget *nome_grp_entry;

GtkWidget *add_subgrp_button;
GtkWidget *add_subgrp_window;
GtkWidget *cod_subgrp_entry;
GtkWidget *nome_subgrp_entry, *nome_subgrp_pai_label, *nome_subgrp_pai_entry;

GtkWidget *confirma_grp_button, *altera_grp_button, *cancela_grp_button, *exclui_grp_button;
GtkWidget *confirma_subgrp_button, *altera_subgrp_button, *cancela_subgrp_button, *exclui_subgrp_button;
gchar *subgrpcode, *subgrpnome;

static GtkWidget *janela_grupo, *janela_subgrupo;
static gchar *grpcode;
int cad_grupo();
int cad_subgrupo();
static int alterando_grp=0;
static int alterando_subgrp=0;

