int remove_migrates();
int check_migrates();
int get_migrate_loaded();

struct _migrate{
	int code;
	char *descricao;
	char *arquivo;
	char *versao;
	char *lancamento;
};

int migrates_loaded_qnt;
struct _migrate *migrates_loaded;

enum MIGRATE_COLS{
	MIGRATE_CODE,
	MIGRATE_DESCRICAO,
	MIGRATE_ARQUIVO,
	MIGRATE_VERSAO,
	MIGRATE_LANCAMENTO
};

enum VER_MIGRATES_COLS {
	VER_MIGRATES_VERSION,
	UP_MIGRATE_FILE,
	DOWN_MIGRATE_FILE
};

const char *version_migrates_list[][3] = {
	{"v1.1.1.1" APP_VERSION_SUFIX APP_ENV_SO, "migrate_01.sql", "migrate_down_01.sql"},
	{"v1.1.1.2" APP_VERSION_SUFIX APP_ENV_SO, "migrate_02.sql", "migrate_down_02.sql"},
	{"v1.1.1.3" APP_VERSION_SUFIX APP_ENV_SO, "migrate_03.sql", "migrate_down_03.sql"},
	{"v1.1.1.4" APP_VERSION_SUFIX APP_ENV_SO, "migrate_04.sql", "migrate_down_04.sql"},
	{"v1.1.1.5" APP_VERSION_SUFIX APP_ENV_SO, "migrate_05.sql", "migrate_down_05.sql"},
	{NULL,NULL, NULL}
};
