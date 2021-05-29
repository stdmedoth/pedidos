#define GET_APP_VERSION() "1.1"

const char *compat_db_versions[] = {
	NULL
};

char *get_db_version();
int check_compat_version();