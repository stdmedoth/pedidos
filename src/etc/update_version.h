#define NO_VERSION_DEFINED -1


int choose_version_for_download();

int download_new_version(void) ;

char *search_last_version();

struct _versions *search_all_versions();


struct _versions {
	char *name;
	char *about;
	int assets_qnt;
	char **assets;
	char *created_time;
};

static struct _versions *versions=NULL;

char *update_ext_files_stopper_exceptions[] = {
	"dll",
	"bat",
	NULL
};

static int update_choosed_version = NO_VERSION_DEFINED;

int choose_versions_qnt = 0;

const char *files_remove_on_update[] = {
	DB_TABLES_LIST_FILE,
	NULL
};
