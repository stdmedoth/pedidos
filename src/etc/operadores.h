enum{
	NIVEL_OPERACIONAL,
	NIVEL_TATICO,
	NIVEL_GERENCIAL,
	NIVEL_TECNICO,
};

#define OPER_MAX_NIVEL 10
#define NIVEL_CRIADOR OPER_MAX_NIVEL

static struct{
	int code;
	char nome[MAX_NAME_LEN];
	int nivel;
}sessao_oper;

gchar *oper_nome_login,*oper_senha_login;
static GtkWidget *nome_entry,*senha_entry;
static GtkWidget *janela_login;
static GtkWidget *enviar_login,*fechar_login;
static int g_handle_janela_login;

void oper_ver_senha(GtkWidget *button, GtkWidget *senha_entry);
void passa_nome();
void passa_senha();
void verifica_senha();
void login();
