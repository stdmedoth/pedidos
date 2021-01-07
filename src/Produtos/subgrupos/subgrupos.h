GtkWidget *add_subgrp_button;
GtkWidget *add_subgrp_window;
GtkWidget *campo_nome_subgrg_pai, *campo_nome_subgrg;
GtkWidget *cod_subgrp_entry, *nome_subgrp_entry, *nome_subgrp_pai_label, *cod_subgrp_pai_entry;

GtkWidget *confirma_subgrp_button, *altera_subgrp_button, *cancela_subgrp_button, *exclui_subgrp_button, *psq_subgrpo_button;
gchar *subgrpcode, *subgrpnome, *subgrp_paicode;

int cad_subgrupo();

int cod_subgrp();
int nome_subgrp();
int pai_subgrp();


int conclui_subgrupo();
int altera_subgrupo();
int cancela_subgrupo();
int exclui_subgrupo();

static int alterando_subgrp=0, concluindo_subgrp=0;
