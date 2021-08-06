void load_env(int argc, char *argv[]){

  _argc = argc;
  _argv = malloc(sizeof(char *)*argc);

  const char **args = malloc( sizeof(char *) *argc );
  int args_pos = 0;

  for(int cont=0;cont<argc;cont++){
    _argv[cont] = strdup(argv[cont]);

    if(cont){
      args[args_pos] = strdup(argv[cont]);
      args_pos++;
    }
  }

  _strargv = str_array_to_string_delim(args, args_pos, ' ');

  const char *exe_filename = get_filename_from_path(argv[0]);
  APP_BINEXE_NAME = strdup(exe_filename);

  switch (sizeof(void*)){
    case 4:
      #define APP_32BIT
      break;
    case 8:
      #define APP_64BIT
      break;
  }

}
