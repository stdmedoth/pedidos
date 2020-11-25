#define MAX_WND1_ABRT 1
#define MAX_WNDN_ABRT 1

enum{
REG_CAD_PROD,
REG_CAD_TER,
REG_CAD_OPER,
REG_CAD_UND,
REG_CAD_GRP,
REG_CAD_COND,
REG_CAD_RELAT,
REG_CAD_ORC,
REG_CAD_PED,
REG_CAD_EST,
REG_ENTS,
REG_SAIDS,
REG_SALD,
REG_PROD_RELAT,
REG_TER_RELAT,
REG_MOV_RELAT,
REG_SUP_WIN,
REG_PARAM_WIN,
REG_REL_FIX_PROD_WIN,
REG_REL_FIX_TER_WIN,
REG_REL_FIX_VND_WIN,
REG_REL_FIX_CMP_WIN,
REG_REL_FIX_EST_WIN,
REG_REL_FIX_ICONS_WIN,
CAD_TIT_PAG_WND,
CAD_TIT_REC_WND,
CAD_BX_PAG_WND,
CAD_BX_REC_WND,
REG_REL_FIX_FINREC_WIN,
REG_REL_FIX_FINPAG_WIN,
CAD_BANCOS_WND,
CAD_TRSP_WND,
REG_NOTIF,
CAD_CONT_FIX_WND,
IMPORT_TITS_WND,
KANBAN_PRINC_WND,
REG_PDV_WND,
REG_SOLIT_WND,
REG_COTAC_WND,
REG_ORDCMP_WND,
REG_ENTCMP_WND,
REG_ANLMKT_PROD,
REG_MODMAIL_PROD,
REG_WIN_QNT,
};

#define REG_PRINC_WIN 9990
#define REG_INIT_FUN_WIN 9991
#define REG_WIN_ENCERRA 9992

#define REG_CORRECT_FINAL 99999

static const char *janelas_nomes[] = {
  "Cad. Produtos",
  "Cad. Terceiros",
  "Cad. Operadores",
  "Cad. Unidades",
  "Cad. Grupos",
  "Cad. Condições",
  "Cad. Relatorios",
  "Orçamentos",
  "Pedidos",
  "Cad. Estoque",
  "Entradas",
  "Saídas",
  "Saldos",
  "Relat. Produtos",
  "Relat. Terceiros",
  "Relat. Movimentos",
  "Suporte",
  "Parametros",
  "Relatorio Fixo de Produtos",
  "Relatorio Fixo de Terceiros",
  "Relatorio Fixo de Vendas",
  "Relatorio Fixo de Compras",
  "Relatorio Fixo de Movimentos de Estoque",
  "Relatorios Fixos Menu",
  "Cadastro de Títulos Pagar",
  "Cadastro de Títulos Receber",
  "Cadastro de Baixas Pagar",
  "Cadastro de Baixas Receber",
  "Relatório Contas à Receber",
  "Relatório Contas à Pagar",
  "Cadastro de Bancos",
  "Cadastro de Transportes",
  "Notificações",
  "Contas Fixas",
  "Importador de títulos",
  "Kanban",
  "PDV",
  "Solicitação de Materiais",
  "Cotação de Materiais",
  "Ordem de Compra",
  "Entrada de Documentos",
  "Análise de Marketing",
  "Modelo de Emails"
};

typedef struct _janelas_info{
  int reg_id;
  short aberta;
  int qnt_aberta;
  int qnt_fechada;
  int criada;
  int sys_close_wnd;
  int (*fun) ();
  GtkWidget *janela_pointer;
}janelas_info;

static struct{
  janelas_info vetor_janelas[REG_WIN_QNT+1];
  janelas_info principal;
  janelas_info fundo_inicializacao;
  janelas_info encerramento;
  janelas_info aplicacao;
}janelas_gerenciadas;

int iniciar_gerenciador_janela();

int ger_janela_fechada(GtkWidget *janela, janelas_info *struct_wnd);

int ger_janela_aberta(GtkWidget *janela, janelas_info *struct_wnd);

int gerenciador_janela();
