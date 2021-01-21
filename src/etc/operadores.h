enum{
	LOGIN_BIND_ENTRAR,
	LOGIN_BIND_SAIR,
	LOGIN_BIND_QNT
};

gchar *login_bindings[] = {
	"anon",
	"sair"
};

enum{
	NIVEL_OPERACIONAL,
	NIVEL_TATICO,
	NIVEL_GERENCIAL,
	NIVEL_TECNICO,
};

enum OPER_COLS{
	OPER_CODE,
	OPER_NOME,
	OPER_SENHA,
	OPER_NIVEL
};

#define OPER_MAX_NIVEL 10
#define NIVEL_CRIADOR OPER_MAX_NIVEL

gchar *oper_nome_login,*oper_senha_login;
static GtkWidget *nome_entry,*senha_entry;
static GtkWidget *janela_login;
static GtkWidget *enviar_login,*fechar_login;
static int g_handle_janela_login;

void oper_ver_senha(GtkWidget *button, GtkWidget *senha_entry);
void passa_nome();
void passa_senha();
void verifica_senha();
int login();

struct _operador{
	int code;
	gchar *nome;
	gchar *senha;
	int nivel;
};

struct _operador *get_operador(int oper_code);
