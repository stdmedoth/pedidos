#define MAX_WND1_ABRT 1
#define MAX_WNDN_ABRT 1

#define REG_CAD_PROD 0
#define REG_CAD_TER 1
#define REG_CAD_OPER 2
#define REG_CAD_UND 3
#define REG_CAD_GRP 4
#define REG_CAD_COND 5
#define REG_CAD_RELAT 6

#define REG_CAD_ORC 7
#define REG_CAD_PED 8

#define REG_CAD_EST 9
#define REG_ENTS 10
#define REG_SAIDS 11
#define REG_SALD 12

#define REG_PROD_RELAT 13
#define REG_TER_RELAT 14
#define REG_MOV_RELAT 15

#define REG_SUP_WIN 16

#define REG_PARAM_WIN 17

#define REG_REL_FIX_PROD_WIN 18
#define REG_REL_FIX_TER_WIN 19
#define REG_REL_FIX_VND_WIN 20
#define REG_REL_FIX_CMP_WIN 21
#define REG_REL_FIX_SAID_WIN 22
#define REG_REL_FIX_ENT_WIN 23

#define REG_REL_FIX_ICONS_WIN 24

#define REG_PRINC_WIN 9990
#define REG_INIT_FUN_WIN 9991
#define REG_WIN_ENCERRA 9992

#define REG_WIN_QNT 24

const char *janelas_nomes[] = {"Cad. Produtos", "Cad. Terceiros", "Cad. Operadores", "Cad. Unidades",
"Cad. Grupos", "Cad. Condições", "Cad. Relatorios", "Orçamentos", "Pedidos", "Cad. Estoque", "Entradas",
"Saídas", "Saldos", "Relat. Produtos", "Relat. Terceiros", "Relat. Movimentos", "Suporte", "Parametros",
"Relatorio Fixo de Produtos", "Relatorio Fixo de Terceiros", "Relatorio Fixo de Vendas", "Relatorio Fixo de Compras",
"Relatorio Fixo de Saidas", "Relatorio Fixo de Entradas", "Relatorios Fixos Menu"};

typedef struct{
  int reg_id;
  short aberta;
  int qnt_aberta;
  int qnt_fechada;
  int criada;
  int sys_close_wnd;
  int (*fun) ();
  GtkWidget *janela_pointer;
}
janelas_info;

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
