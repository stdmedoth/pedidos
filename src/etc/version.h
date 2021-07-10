#ifdef WIN32
#define APP_ENV_SO "Win64"
#endif

#ifdef __linux__
#define APP_ENV_SO "Linux"
#endif

#define GET_APP_VERSION() "1.1.1.4"
#define GET_APP_VERSION_NAME() "v" GET_APP_VERSION() "_" APP_ENV_SO


char *db_version=NULL;

const char *compat_db_versions[] = {
	NULL
};

char *get_db_version();
int check_compat_version();
