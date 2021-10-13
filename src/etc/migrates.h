int error_migrate_popup();
int update_migrates();
int remove_migrates();
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

#define UP_MIGRATE_PREFIX "migrate_"
#define DOWN_MIGRATE_PREFIX "migrate_down_"

const char *version_migrates_list[][3] = {
	{
		"v1.1.1.1"APP_VERSION_SUFIX APP_ENV_SO,
		UP_MIGRATE_PREFIX"01.sql",
		DOWN_MIGRATE_PREFIX"01.sql"
	},
	{
		"v1.1.1.2"APP_VERSION_SUFIX APP_ENV_SO,
		UP_MIGRATE_PREFIX"02.sql",
		DOWN_MIGRATE_PREFIX"02.sql"},
	{
		"v1.1.1.3"APP_VERSION_SUFIX APP_ENV_SO,
		UP_MIGRATE_PREFIX"03.sql",
		DOWN_MIGRATE_PREFIX"03.sql"
	},
	{
		"v1.1.1.4"APP_VERSION_SUFIX APP_ENV_SO,
		UP_MIGRATE_PREFIX"04.sql",
		DOWN_MIGRATE_PREFIX"04.sql"
	},
	{
		"v1.1.1.5"APP_VERSION_SUFIX APP_ENV_SO,
		UP_MIGRATE_PREFIX"05.sql",
		DOWN_MIGRATE_PREFIX"05.sql"
	},
	{
		"v1.1.1.6"APP_VERSION_SUFIX APP_ENV_SO,
		UP_MIGRATE_PREFIX"06.sql",
		DOWN_MIGRATE_PREFIX"06.sql"
	},
	{NULL,NULL, NULL}
};
