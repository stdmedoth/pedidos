#ifdef WIN32

typedef intptr_t ssize_t;

ssize_t getline(char **lineptr, size_t *n, FILE *stream);

#endif