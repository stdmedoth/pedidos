int row_exists(char *table, int id);

int conectar_mysql();

MYSQL_RES *consultar(char *query);

int enviar_query(char *query);
