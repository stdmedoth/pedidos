const char *APP_BINEXE_NAME = NULL;

//#define PEDIDOS_DEVELOP_ENV
#define PEDIDOS_PRODUCTION_ENV

int _argc;
const char **_argv = NULL;
const char *_strargv = NULL;

void load_env();
