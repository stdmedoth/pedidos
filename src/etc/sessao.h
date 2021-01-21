enum{
	SESSAO_NULA,
	SESSAO_TESTE,
	SESSAO_LOGADA
};

struct _sessao{

	int code;
	char *nome;
	int nivel;
	struct _operador *operador;
	GDateTime *criacao;
	GDateTime *ult_ativ;
	GDateTime *expiracao;
	int status_sessao;

}sessao_oper;


void sessao_set_allmodules();

void sessao_set_nonemodules();

void criar_sessao_default();

void criar_sessao_anon();

int fechar_sessao();

int limpar_sessao();

gboolean atalho_fechar_sessao(GtkWidget *widget,  GdkEventKey  *event, gpointer   user_data);

struct _sessao *get_new_sessao_from_oper(int oper_code);
