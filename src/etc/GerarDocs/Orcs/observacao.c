int gerar_orc_observacao(FILE *file, struct _orc *orc){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char *query = malloc(MAX_QUERY_LEN);

  fprintf(file,"<div id=\"obs-div1\">\n");
  fprintf(file,"Observacões\n");
  fprintf(file,"<div id=\"obs-div2\">\n");

  sprintf(query,"select t.code_nfe, o.observacoes from orcamentos as o inner join terceiros as t on o.cliente = t.code where o.code = %i",orc->infos.cliente);
  if(!(res = consultar(query))){
    popup(NULL,"Erro ao verificar entrega");
  }else{
    if((row=mysql_fetch_row(res))){
      if(row[0] && row[1])
      {
        if(strlen(row[0]))
          fprintf(file,"Cod. Cliente : %s<br>",row[0]);
        if(strcmp(row[1],"(null)")!=0)
        {
          fprintf(file,"%s",row[1]);
        }
      }

    }
  }
  fprintf(file,"</div>\n");
  fprintf(file,"</div>\n");

  return 0;
}
