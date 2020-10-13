int analisa_ender(char *endereco){
  int virgula=0;
  int num_len=12;
  char numero[num_len];
  int pos_virgula=0;

  for(int cont=0;cont<num_len;cont++)
    numero[cont] = '\0';

  for(int cont=0;cont<strlen(endereco);cont++){
    if(endereco[cont] == ','){
      virgula = 1;
      pos_virgula = cont;
    }
    if(virgula){
      int num = 0;
      int pos=0;
      g_print("Iniciando interprete do numero no endereco\n");

      for(int cont2=cont;cont2<strlen(endereco);cont2++){
        if( isdigit(endereco[cont2]) || isspace(endereco[cont2]) ){
          num = 1;
          g_print("%c",endereco[cont2]);
          numero[pos] = endereco[cont2];
          pos++;
          if(pos>=num_len){
            return atoi(numero);
          }
        }else{
          num = 0;
        }
      }

      if(num){
        return atoi(numero);
      }
      break;
    }
  }
  return 0;
}
