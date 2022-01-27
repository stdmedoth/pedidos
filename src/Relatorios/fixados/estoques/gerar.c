
int relat_fix_est_gerar_fun(){
  MYSQL_ROW row,row2;
  MYSQL_RES *res,*res2;
  char query[MAX_QUERY_LEN];
  char *file_path = malloc(MAX_PATH_LEN*2);
  char html_header[] = "<!DOCTYPE html>"
                          "<html>"
                            "<head>"
                              "<meta charset=\"utf-8\"/>"
                              "<title>Relatório de Movimentos</title>"
                              "<link href=\"../../styles/relatorios.css\" rel=\"stylesheet\">"
                            "</head>";
  GDir *dir;
  if(!(dir = g_dir_open(REL_FIX_MOV_PATH,0,NULL))){
      popup(NULL,"Diretorio sendo criado");
      if(g_mkdir_with_parents(REL_FIX_FIN_PATH, 777) == -1){
        popup(NULL,"Não foi possível criar diretorio de relatorios");
        return 1;
      }
  }

  sprintf(file_path,"%s/movimentos.html",REL_FIX_MOV_PATH);

  int est_qnt=0;
  FILE *relat_file = fopen(file_path,"w");
  if(!relat_file){
    popup(NULL,"Não foi possível escrever relatório");
    file_logger(strerror(errno));
    return 1;
  }

  if(relat_fix_est_ped_fun())
    return 1;

  if(relat_fix_est_prod_fun())
    return 1;

  if(relat_fix_est_grp_fun())
    return 1;

  if(relat_fix_est_quebra_fun())
    return 1;

  if(relat_fix_est_totaliza_fun())
    return 1;

  if(relat_fix_est_sintetiza_fun())
    return 1;

  if(relat_fix_est_est_fun())
    return 1;

  //sprintf(query,"select code, ")
  char *ordenacoes[] = {"e.code", "t.razao", "p_all.nome", "g_prc.valor_vist"};
  char *totalizacoes[] = {"e.unidades", "e.total"};

  relat_fix_est_vlrs.pedidos1 = atoi(relat_fix_est_ped_gchar1);
  relat_fix_est_vlrs.pedidos2 = atoi(relat_fix_est_ped_gchar2);

  relat_fix_est_vlrs.produtos1 = atoi(relat_fix_est_prod_gchar1);
  relat_fix_est_vlrs.produtos2 = atoi(relat_fix_est_prod_gchar2);

  relat_fix_est_vlrs.grupos1 = atoi(relat_fix_est_grp_gchar1);
  relat_fix_est_vlrs.grupos2 = atoi(relat_fix_est_grp_gchar2);

  relat_fix_est_vlrs.estoques1 = atoi(relat_fix_est_est_gchar1);
  relat_fix_est_vlrs.estoques2 = atoi(relat_fix_est_est_gchar2);

  relat_fix_est_vlrs.quebra = relat_fix_est_quebra_int;
  relat_fix_est_vlrs.totaliza = relat_fix_est_totaliza_int;
  relat_fix_est_vlrs.sintetiza = relat_fix_est_sintetiza_int;

  fprintf(relat_file,"%s", html_header);
  fprintf(relat_file,"<body>");
  fprintf(relat_file,"<div style='background: Gainsboro;'>");
  fprintf(relat_file,"<h1>Relatório de Movimentos de Estoque</h1>");
  fprintf(relat_file,"<p>%s</p>",data_sys);
  fprintf(relat_file,"</div>");
  fprintf(relat_file,"<table>");
  float totalizacao_entrada=0,totalizacao_saida=0;
  for(int cont=relat_fix_est_vlrs.pedidos1;cont<=relat_fix_est_vlrs.pedidos2;cont++){
      float vlr_ped=0,vlr_frete=0;
      sprintf(query, "select ped.code, t.code, t.razao, DATE_FORMAT(ped.data_mov,'%%d/%%m/%%Y'), tp.nome from pedidos as ped inner join terceiros as t inner join pag_cond as pag inner join tipo_movimentos as tp inner join movimento_estoque as mv on ped.cliente = t.code and ped.pag_cond = pag.code and tp.id = ped.tipo_mov and mv.pedido = ped.code where ped.code = %i",cont);
      if(!(res=consultar(query))){
        popup(NULL,"Erro ao consultar pedido");
        return 1;
      }
      fprintf(relat_file,"<div id='solid-container'>");
      if((row = mysql_fetch_row(res))){
        sprintf(query, "select mv.produto, p.nome, mv.entradas, mv.saidas, mv.code, mv.tipo_mov from movimento_estoque as mv inner join produtos as p on mv.produto = p.code left join pedidos as ped on ped.code = mv.pedido where ped.code = %s and mv.produto >= %s and mv.produto <= %s",
        row[0],
        relat_fix_est_prod_gchar1,
        relat_fix_est_prod_gchar2);

        if(!(res2=consultar(query))){
          popup(NULL,"Erro ao consultar pedido");
          return 1;
        }
        if(mysql_num_rows(res2)){
          fprintf(relat_file,"<tr class='relat-infos'>");
          fprintf(relat_file,"<td>Pedido: %s<td/>",row[0]);
          fprintf(relat_file,"<td>Cliente:  %s:%s<td/>",row[1],row[2]);
          fprintf(relat_file,"<td>Data:  %s<td/>",row[3]);
          fprintf(relat_file,"<td>Tipo:  %s<td/>",row[4]);
          fprintf(relat_file,"</tr>");
        }
        while((row2 = mysql_fetch_row(res2))){
          fprintf(relat_file,"<tr>");
          fprintf(relat_file,"<td>Cod. Prod.: %s | Movimento %s<td/>",row2[0],row2[4]);
          fprintf(relat_file,"<td>%s<td/>",row2[1]);

          //totaliza entradas e saidas
          if( atoi(row[5]) == VENDA || atoi(row[5]) == DEV_COMPRA ){
            fprintf(relat_file,"<td>%.2f -> Saida<td/>",atof(row2[3]));
            totalizacao_saida += atof(row2[2]);
          }

          if( atoi(row[5]) == DEV_VENDA || atoi(row[5]) == COMPRA ){
            fprintf(relat_file,"<td>%.2f -> Entrada<td/>",atof(row2[2]));
            totalizacao_entrada += atof(row2[2]);
          }

          fprintf(relat_file,"</tr>");
          est_qnt++;
        }
      }
      fprintf(relat_file,"</div>");
  }
  sprintf(query, "select mov.code, t.code, t.razao, DATE_FORMAT(mov.data_mov,'%%d/%%m/%%Y'), tp.nome, tp.id from movimento_estoque as mov inner join terceiros as t inner join tipo_movimentos as tp on mov.cliente = t.code and tp.id = mov.tipo_mov where mov.pedido = 0");
  if(!(res=consultar(query))){
    popup(NULL,"Erro ao consultar pedido");
    return 1;
  }
  fprintf(relat_file,"<div id='solid-container'>");
  while((row = mysql_fetch_row(res))){
    fprintf(relat_file,"<tr class='relat-infos'>");
    fprintf(relat_file,"<td>Pedido: Sem Pedido");
    fprintf(relat_file,"<td>Cliente:  %s:%s<td/>",row[1],row[2]);
    fprintf(relat_file,"<td>Data:  %s<td/>",row[3]);
    fprintf(relat_file,"<td>Tipo:  %s<td/>",row[4]);
    fprintf(relat_file,"</tr>");

    if( atoi(row[5]) == VENDA || atoi(row[5]) == DEV_COMPRA )
      sprintf(query, "select mov.produto, p.nome, mov.saidas from movimento_estoque as mov inner join produtos as p on mov.produto = p.code where mov.code = %s and mov.produto >= %s and mov.produto <= %s",
      row[0],
      relat_fix_est_prod_gchar1,
      relat_fix_est_prod_gchar2);

    if( atoi(row[5]) == DEV_VENDA || atoi(row[5]) == COMPRA )
      sprintf(query, "select mov.produto, p.nome, mov.entradas from movimento_estoque as mov inner join produtos as p on mov.produto = p.code where mov.code = %s and mov.produto >= %s and mov.produto <= %s",
      row[0],
      relat_fix_est_prod_gchar1,
      relat_fix_est_prod_gchar2);

    if(!(res2=consultar(query))){
      popup(NULL,"Erro ao consultar pedido");
      return 1;
    }
    while((row2 = mysql_fetch_row(res2))){
      fprintf(relat_file,"<tr>");
      fprintf(relat_file,"<td>Código:  %s  | Movimento %s<td/>",row2[0],row[0]);
      fprintf(relat_file,"<td>%s<td/>",row2[1]);

      //totaliza entradas e saidas
      if( atoi(row[5]) == VENDA || atoi(row[5]) == DEV_COMPRA ){
        fprintf(relat_file,"<td>%.2f -> Saída<td/>",atof(row2[2]));
        totalizacao_saida += atof(row2[2]);
      }

      if( atoi(row[5]) == DEV_VENDA || atoi(row[5]) == COMPRA ){
        fprintf(relat_file,"<td>%.2f -> Entrada<td/>",atof(row2[2]));
        totalizacao_entrada += atof(row2[2]);
      }
      fprintf(relat_file,"</tr>");
      est_qnt++;
    }
  }
  fprintf(relat_file,"</div>");

  if(!est_qnt){
    popup(NULL,"Não Há nada a gerar");
    return 1;
  }

  fprintf(relat_file,"</table>");

  if(relat_fix_est_totaliza_int){
    fprintf(relat_file,"<table>");
    fprintf(relat_file,"<tr>");
    fprintf(relat_file,"<td>Total Entradas:  %.2f<td/>",totalizacao_entrada);
    fprintf(relat_file,"<td>Total Saídas: %.2f<td/>",totalizacao_saida);
    fprintf(relat_file,"</tr>");
    fprintf(relat_file,"</table>");
  }

  fprintf(relat_file,"</body>");
  fprintf(relat_file,"</html>");
  fclose(relat_file);

  if(escolher_finalizacao(file_path)){
    return 1;
  }

  return 0;
}
