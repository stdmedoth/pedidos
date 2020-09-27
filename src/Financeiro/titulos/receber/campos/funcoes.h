struct _titulo{
  int code;
  int cliente;
  int pedido;
  int status;
  int qnt_parcelas;
  int tipo_titulo;

  GtkTreeView *treeview;
  MYSQL_RES *result;
  MYSQL_ROW row;
};

MYSQL_RES *titulos_get_pendentes(struct _titulo *titulos);

MYSQL_RES *titulos_get_baixados(struct _titulo *titulos);

MYSQL_RES *titulos_get_todos(struct _titulo *titulos);

MYSQL_RES *titulos_por_cliente(struct _titulo *titulos);

MYSQL_RES *titulos_por_cliente_status(struct _titulo *titulos);

GtkWidget *titulos_get_widget(struct _titulo *titulos);

int titulos_update_widget(struct _titulo *titulos);
