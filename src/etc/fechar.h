#define GTK_RESPONSE_RESTART 3

#define FECHAR_ATALHO_KEY	GDK_KEY_s
#define F4_ATALHO_KEY	GDK_KEY_F4
#define LOGOUT_ATALHO_KEY	GDK_KEY_F2
static int encerrar_manualmente=0;

void limpar_applicacao();

int encerrar(GtkWidget *buttton,GtkWindow *parent);

void botao_encerrar();

int aplicacao_inicializada();

void encerrando();
