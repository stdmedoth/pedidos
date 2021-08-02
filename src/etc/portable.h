#ifdef WIN32

int scandir(char *folderpath, struct dirent **namelist, int (*filter)(const struct dirent *), int (*compar)(const struct dirent **, const struct dirent **));

typedef intptr_t ssize_t;

ssize_t getline(char **lineptr, size_t *n, FILE *stream);

#endif

int remove_directory(const char *path) ;
