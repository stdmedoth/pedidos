MYSQL_RES *titulos_get_pendentes(struct _titulo *titulos);

MYSQL_RES *titulos_get_baixados(struct _titulo *titulos);

MYSQL_RES *titulos_get_todos(struct _titulo *titulos);

MYSQL_RES *titulos_por_cliente(struct _titulo *titulos);

MYSQL_RES *titulos_por_cliente_status(struct _titulo *titulos);


int criar_titulo(struct _titulo *titulo);