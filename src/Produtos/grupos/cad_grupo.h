GtkWidget *cod_grp_entry;
GtkWidget *nome_grp_entry;

GtkWidget *confirma_grp_button, *altera_grp_button, *cancela_grp_button, *exclui_grp_button, *psq_grp_button;

GtkWidget *cad_grp_treeview;

static GtkWidget *janela_grupo, *janela_subgrupo;
static gchar *grpcode, *grpnome;

int cad_grupo();
//int grp_criar_modelo(GtkTreeStore *modelo);

int conclui_grupo();
int exclui_grupo();
int cancela_grupo();
int altera_grupo();

int rec_familia_nome(char **familia_char,int grupo);

static int alterando_grp=0,concluindo_grp=0;

GtkTreeStore *grp_get_tree(GtkTreeStore *modelo, int pai, GtkTreeIter *campo);
