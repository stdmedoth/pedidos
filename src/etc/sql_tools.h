int run_sql_from_file(char *sql_path, int stop_on_error);

int mysql_res_to_cvs_file(char *filename, MYSQL_RES *res);

int row_exists(char *table, int id);

int conectar_mysql();

MYSQL_RES *consultar(char *query);

int enviar_query(char *query);
