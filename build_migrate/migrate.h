MYSQL conectar;

static struct {
  char *server_endereco;
  char *server_user;
  char *server_senha;
  char *server_database;
  int conectado;
}server_confs;

const char *options [] = {
  "empty",
  "new",
  "update",
  "downgrade",
  "reset",
  "list",
  "version",
  0
};

int conectar_mysql();

int rec_vars_from_file();

int rodar_migrate(char *migrate_path);

void help_message();

xmlNodePtr get_tag_by_namepath(xmlDoc *doc, char *namepath);

int check_migrate_exists(int migrate_id);

int list_migrates();

char *get_version();
