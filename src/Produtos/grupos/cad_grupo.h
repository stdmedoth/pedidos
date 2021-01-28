GtkWidget *cod_grp_entry;
GtkWidget *nome_grp_entry;
GtkWidget *pai_grp_entry, *painome_grp_entry, *paipsq_grp_button;

GtkWidget *confirma_grp_button, *altera_grp_button, *cancela_grp_button, *exclui_grp_button, *psq_grp_button;

GtkWidget *cad_grp_treeview;

GtkWidget *janela_grupo;
gchar *grpcode, *grpnome, *paigrpcode;
gint grpnivel=0;

int alterando_grp=0,concluindo_grp=0;

int conclui_grupo();
int exclui_grupo();
int cancela_grupo();
int altera_grupo();

int cad_grupo();
//int grp_criar_modelo(GtkTreeStore *modelo);

int codpai_grp();
int rec_familia_nome(char **familia_char,int grupo);
GtkTreeStore *grp_get_tree(GtkTreeStore *modelo, int pai, GtkTreeIter *campo);
struct _grupo *grp_get_grupo(int code_grp);

struct _grupo{
  int code;
  char *nome;
  int pai;
  int nivel;
  char *pai_nome;
};
