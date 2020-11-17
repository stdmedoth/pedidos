int cotacao_resultado_fun(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  char *file_path = malloc(strlen(COT_RES_PATH)+20);
  char html_header[] = "<!DOCTYPE html>"
  "<html>"
    "<head>"
      "<meta charset=\"utf-8\"/>"
      "<title>Resultado da cotação</title>"
      "<link href=\"../styles/relatorios.css\" rel=\"stylesheet\">"
    "</head>";

  sprintf(file_path,"%scot_res.html",COT_RES_PATH);
  FILE *file_arq = fopen(file_path,"w");
  if(!file_arq){
    autologger(file_path);
    popup(NULL,"Não foi possível abrir arquivo");
    return 1;
  }
  fprintf(file_arq,html_header);
  fprintf(file_arq,"<body>");
  fprintf(file_arq,"<div style='background: Gainsboro;'>");
  fprintf(file_arq,"<h1>Resultado da Cotação</h1>");
  fprintf(file_arq,"<p>%s</p>",data_sys);
  fprintf(file_arq,"</div>");

  fprintf(file_arq,"<div>");

  int itens_qnt=0;
  cotac_gerresultado = 1;
  if(cotac_code_fun())
    return 1;

  sprintf(query,"select pr.code, ter.razao, p.code, p.nome, pr.quantidade, DATE_FORMAT(pr.data,'%%d/%%m/%%Y'), pr.prioridade, ic.qnt, ic.preco, ic.qnt * ic.preco, u.nome from itens_cotacoes as ic inner join produtos as p inner join prod_requisicoes as pr inner join terceiros as ter inner join unidades as u on u.code = p.unidades and ic.requisicao = pr.code and pr.produto = p.code and ic.participante_id = ter.code where ic.cotacoes_id = %i order by ic.requisicao, ic.qnt, (ic.qnt * ic.preco);", atoi(cotac_code_gchar));
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar cotação");
    return 1;
  }
  fprintf(file_arq,"<table>");

  fprintf(file_arq,"<tr class='relat-infos'>");

  fprintf(file_arq,"<th>Requisição</th>");

  fprintf(file_arq,"<th>Participante</th>");

  fprintf(file_arq,"<th>Produto</th>");

  fprintf(file_arq,"<th>Qnt Solicitada</th>");

  fprintf(file_arq,"<th>Data Solicitação</th>");

  fprintf(file_arq,"<th>Prioridade</th>");

  fprintf(file_arq,"<th>Quantidade cotada</th>");

  fprintf(file_arq,"<th>Preço</th>");

  fprintf(file_arq,"<th>Total</th>");

  fprintf(file_arq,"</tr>");

  while((row = mysql_fetch_row(res))){
    fprintf(file_arq,"<tr class='tr-focus'>");

    fprintf(file_arq,"<td>%s</td>",row[0]);
    fprintf(file_arq,"<td>%s</td>",row[1]);
    fprintf(file_arq,"<td>%s: %s</td>",row[2],row[3]);
    fprintf(file_arq,"<td>%.2f %s</td>",atof(row[4]), row[10]);
    fprintf(file_arq,"<td>%s</td>",row[5]);
    fprintf(file_arq,"<td>%s</td>",req_prod_get_prior_name(atoi(row[6])));
    fprintf(file_arq,"<td>%.2f %s</td>",atof(row[7]), row[10]);
    fprintf(file_arq,"<td>%.2f</td>",atof(row[8]));
    fprintf(file_arq,"<td>%.2f</td>",atof(row[9]));

    fprintf(file_arq,"</tr>");

    itens_qnt++;
  }
  if(!itens_qnt){
    fclose(file_arq);
    popup(NULL,"Não há itens para serem cotados");
    return 1;
  }

  fprintf(file_arq,"</table>");
  fprintf(file_arq,"</div>");
  fprintf(file_arq,"</body>");
  fprintf(file_arq,"</html>");
  fclose(file_arq);
  if(escolher_finalizacao(file_path)){
    return 1;
  }

  cotac_gerresultado = 0;
  return 0;
}
