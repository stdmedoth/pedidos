int gerar_orc_bancos(FILE *file, struct _orc *orc){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char *query = malloc(MAX_QUERY_LEN);

  fprintf(file,"<div id=\"banco-infos\">\n");
  sprintf(query,"select * from bancos where code = %i",orc->parcelas.banco);
  if((res = consultar(query))){
    if((row = mysql_fetch_row(res))){
      fprintf(file,"<div class='wrapper banco'>");
      fprintf(file,"<div>Banco: %s</div>",row[1]);
      fprintf(file,"<div>Conta: %s</div>",row[2]);
      fprintf(file,"<div>Agência:  %s</div>",row[4]);
      fprintf(file,"<div>Beneficiário:  %s</div>", row[5]);
      fprintf(file,"<div>CNPJ/CPF:  %s</div>", row[6]);
      fprintf(file,"</div>");
    }
  }

  fprintf(file,"</div>\n");
  return 0;
}
