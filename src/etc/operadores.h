#define NIVEL_GERENCIAL_CODE 3
#define NIVEL_TATICO_CODE 2
#define NIVEL_OPERACIONAL_CODE 1

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
