int command_args(){

  for(int cont=0; commands_args_list[cont]; cont++) {
    if(!strcmp(commands_args_list[cont], _strargv)){
      switch (cont) {
        case 0:
          update_migrates();
          return 1;
        case 1:
          remove_migrates();
          return 1;
        case 2:
          download_changelog_files();
          return 1;
      }
    }
  }

  return 0;
}
