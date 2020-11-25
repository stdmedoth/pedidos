int pdv_princ_wnd();

gboolean pdv_bind_atalhos(GtkWidget *widget, GdkEventKey *event, gpointer   user_data);

GtkWidget *pdv_itens_treeview;

int pdv_add_item_fun();
int pdv_rem_item_fun();
int pdv_psq_item_fun();
int pdv_fecha_cupom_fun();

GtkWidget *pdv_botoes_atalhos;
GtkWidget *pdv_add_item_button;
GtkWidget *pdv_rem_item_button;
GtkWidget *pdv_psq_item_button;
GtkWidget *pdv_fecha_cupom_button;
GtkWidget *pdv_acaoatual_label;

GtkWidget *pdv_prodcod_label;

GtkWidget *pdv_codprod_entry;
GtkWidget *pdv_qntprod_entry;

gchar *pdv_prod_antes_psq;

struct _pdv_item_atual{
  int item;
  int produto;
  float qnt;
  float vlr_unit;
  float total;
};

//status da venda no PDV
enum PDV_STATUS{
  PDV_SEM_VENDA,
  PDV_EM_VENDA,
};

//operacao atual no PDV
enum PDV_OPERS{
  PDV_NULL_OPER,
  PDV_ADD_ITEM_OPER,
  PDV_REM_ITEM_OPER,
  PDV_PSQ_ITEM_OPER,
  PDV_FECHA_CUPOM_OPER
};

//operacoes para adicionar item
enum PDV_ADDITEM_OPER{
  PDV_ADD_PRODCOD,
  PDV_ADD_PRODQNT,
  PDV_ADD_PRODVLR,
  PDV_ADD_PRODDESC,
};

struct _pdv_venda_atual{
  int operacao_atual;
  int status_atual;
  int cliente;
  struct _caixa *caixa_atual;
  struct _CFe *cupom_atual;
  struct _pdv_item_atual *pdv_item_atual;
  int itens_qnt;
}*pdv_venda_atual;

struct _CFe *get_cupom_from_pdv(struct _pdv_venda_atual *pdv);
