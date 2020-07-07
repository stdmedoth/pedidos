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

#define REG_WIN_QNT 15

const char *janelas_nomes[] = {"Cad. Produtos", "Cad. Terceiros", "Cad. Operadores", "Cad. Unidades",
"Cad. Grupos", "Cad. Condições", "Cad. Relatorios", "Orçamentos", "Pedidos", "Cad. Estoque", "Entradas",
"Saídas", "Saldos", "Relat. Produtos", "Relat. Terceiros", "Relat. Movimentos"};

typedef struct{
  int reg_id;
  short aberta;
  int qnt_aberta;
  int qnt_fechada;
  GtkWidget *janela_pointer;
}
janelas_info;

struct{
  janelas_info vetor_janelas[REG_WIN_QNT];
}janelas_gerenciadas;

int ger_janela_fechada(GtkWidget *janela, janelas_info *struct_wnd);

int ger_janela_aberta(GtkWidget *janela, janelas_info *struct_wnd);

int gerenciador_janela();
