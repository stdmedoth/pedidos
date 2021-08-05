void load_env(int argc, char *argv[]){

  const char *exe_filename = get_filename_from_path(argv[0]);
  APP_BINEXE_NAME = strdup(exe_filename);

  printf("%s", APP_BINEXE_NAME);

  switch (sizeof(void*)){
    case 4:
      #define APP_32BIT
      break;
    case 8:
      #define APP_64BIT
      break;
  }
}
