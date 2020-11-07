GtkWidget *acao_atual,*acao_atual2; //mostrar status de uma janela
GtkEntry *pesquisa_global_alvo;
GtkIconTheme *icone;
static int inicializando=0;

//modulos para ativar
struct modulos
{
	int ativo;
	int cadastro;
	int compras;
	int faturamento;
	int estoque;
	int financeiro;
	int relatorios;
	int tecnicos;
}ativar;

static char *tip_logds[] = {"Rua",
	"Avenida",
	"Praça",
	"Estrada",
	"Alameda",
	"Travessia",
	"Rodovia"};

static int tipo_ter_load = 0;
static int encerramento_brusco=0;
