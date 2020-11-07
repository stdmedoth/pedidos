MYSQL intgr_con;

GtkWidget *integr_opc_wdt, *integr_server_wdt, *integr_tabprefix_wdt, *integr_bd_wdt, *integr_usuario_wdt, *integr_senha_wdt ;

static struct{
	struct{
    int nul;
	}criticar;

	struct{
		char *server;
		char *user;
		char *pass;
		char *banco;
		int intgr_id;
		char *prefix_tab;
	}config;
}integracoes;

enum{
	WC_INTGR
};

int ler_intgr_params();

void criar_intgr_params(FILE *xmlf);

int atualizar_intgr_params();

int receber_intgr_params();
