void load_env(int argc, char *argv[]){

  APP_BINEXE_NAME = strdup(argv[0]);

  switch (sizeof(void*)){
    case 4:
      #define APP_32BIT
      break;
    case 8:
      #define APP_64BIT
      break;
  }
}
