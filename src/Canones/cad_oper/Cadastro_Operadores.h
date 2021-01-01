static GtkWidget *oper_nome_entry,*oper_senha_entry,*oper_perm_entry,*oper_nome_perm_entry;
static char **niveis_gerenciais;
static gchar *oper_nome_gchar,*oper_senha_gchar;
static int oper_alterando = 0;
static int tmp_oper_code=0;
static int oper_perm_int=0,oper_perm_qnt_niveis=0;
static GtkWidget *oper_perm_name_entry;
GtkWidget *cad_oper_concluir_button, *cad_oper_alterar_button, *cad_oper_excluir_button, *cad_oper_cancelar_button;


int oper_cancelar();

int oper_excluir();


int oper_alterar();

int oper_passa_nome();

int oper_passa_senha();


int oper_concluir();

int cad_oper();
