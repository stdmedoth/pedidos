int reload_nome_grupos(){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];
  int familia[MAX_SUBGRUPO];
  char *source_grp_name = malloc(MAX_SUBGRUPO*MAX_GRP_LEN+MAX_SUBGRUPO+1);
  char *dest_grp_name = malloc(MAX_SUBGRUPO*MAX_GRP_LEN+MAX_SUBGRUPO+1);
  char **familia_char = malloc(MAX_SUBGRUPO*MAX_GRP_LEN+MAX_SUBGRUPO+1);

  int grupo_code=0,grupo_len=0;

  sprintf(query,"delete from produtos_nome_all;");
  if(enviar_query(query)){
    popup(NULL,"Produto falhou na remoção dos dados anteriores");
  }

  sprintf(query,"select code from grupos where code > 1");
  if(!(res= consultar(query))){
    popup(NULL,"Não foi possivel receber produtos");
    return 1;
  }

  while((row = mysql_fetch_row(res))){

    grupo_code = atoi(row[0]);
    if(rec_familia_vet(familia, atoi(row[0]) )!=0){
      popup(NULL,"Erro ao calcular niveis do grupo");
      return 1;
    }

    if((grupo_len = rec_familia_nome(familia_char, grupo_code ))<0){
      popup(NULL,"Erro ao juntar nomes de grupos");
      return 1;
    }

    if(grupo_len == -1){
      popup(NULL,"Erro ao percorrer grupo");
    }else{
      strcpy(dest_grp_name,"");
    	strcpy(source_grp_name,"");


    	for(int cont=grupo_len;cont>0;cont--){

    		if(!familia_char[cont]){
    			popup(NULL,"Elemento do grupo com ponteiro nulo");
    			break;
    		}

    		sprintf(dest_grp_name,"%s %s",source_grp_name,familia_char[cont]);
    		if(strlen(dest_grp_name)>MAX_SUBGRUPO*MAX_GRP_LEN+MAX_SUBGRUPO){
    			popup(NULL,"Nome grupo excedeu memoria");
    		}

    		strcpy(source_grp_name,dest_grp_name);
    		if(strlen(source_grp_name)>MAX_SUBGRUPO*MAX_GRP_LEN+MAX_SUBGRUPO){
    			popup(NULL,"Nome grupo excedeu memoria");
    			break;
    		}
      }
    }

    sprintf(query,"insert into produtos_nome_all(code,nome,referencia) values(%s,'%s','%i')",row[0],dest_grp_name,familia[grupo_len-1]);
    if(enviar_query(query)){
      popup(NULL,"Produto falhou na importação");
    }
  }
  popup(NULL,"Processo Finalizado");
  return 0;
}


int opc_reload_nome_grp(){

  gpointer spinner = carregando_wnd();
  while (g_main_context_pending(NULL))
    g_main_context_iteration(NULL,FALSE);

  reload_nome_grupos();

  gtk_widget_destroy(spinner);

  return 0;
}
