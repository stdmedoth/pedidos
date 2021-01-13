#define GTK_RESPONSE_RESTART 3

#define FECHAR_ATALHO_KEY GDK_KEY_s
#define LOGOUT_ATALHO_KEY GDK_KEY_F2
static int encerrar_manualmente=0;

int fechar_sessao();

int limpar_sessao();

void limpar_applicacao();

int encerrar(GtkWidget *buttton,GtkWindow *parent);

void botao_encerrar();

gboolean atalho_fechar_sessao(GtkWidget *widget,  GdkEventKey  *event, gpointer   user_data);

int aplicacao_inicializada();

void encerrando();
