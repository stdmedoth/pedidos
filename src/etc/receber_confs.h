static struct {
  char *server_endereco;
  char *server_user;
  char *server_senha;
  char *server_database;
}server_confs;


int rec_vars_from_file();
int rec_vars_from_xml_file();
int rec_vars_from_json_file();
