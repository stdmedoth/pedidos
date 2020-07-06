#define NIVEL_GERENCIAL_CODE 3
#define NIVEL_TATICO_CODE 2
#define NIVEL_OPERACIONAL_CODE 1

struct{
	int code;
	char nome[MAX_NAME_LEN];
	int nivel;
}sessao_oper;

static GtkWidget *nome_entry,*senha_entry;
static GtkWidget *janela_login;
static GtkWidget *enviar_login,*fechar_login;
int desktop();
int encerrar();
int g_handle_janela_login;
