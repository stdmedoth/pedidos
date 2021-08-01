#ifdef WIN32

#if defined(_WIN64)
#define APP_ENV_SO "Win64"
#elif defined(_WIN32)
#define APP_ENV_SO "Win32"
#endif

#endif

#ifdef __linux__
#define APP_ENV_SO "Linux"
#endif

#define GET_APP_VERSION() "1.1.1.5"
#define APP_VERSION_PREFIX "v"
#define APP_VERSION_SUFIX "_"

#define GET_APP_VERSION_NAME() APP_VERSION_PREFIX GET_APP_VERSION() APP_VERSION_SUFIX APP_ENV_SO

char *db_version=NULL;

char *get_db_version();
int check_compat_version();

#include "versions.h"
