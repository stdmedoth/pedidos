
int relat_fix_vnd_gerar_fun(){
  MYSQL_ROW row,row2;
  MYSQL_RES *res,*res2;
  char query[MAX_QUERY_LEN];
  char *file_path = malloc(MAX_PATH_LEN*2);
  int prod_qnt=0;

  char html_header[] = "<!DOCTYPE html>\
  <html>\
    <head>\
      <meta charset=\"utf-8\"/>\
      <title>Relatório de Vendas</title>\
      <link href=\"../../styles/relatorios.css\" rel=\"stylesheet\">\
    </head>";

  GDir *dir;
  if(!(dir = g_dir_open(REL_FIX_VND_PATH,0,NULL))){
      popup(NULL,"Diretorio sendo criado");
      if(g_mkdir_with_parents(REL_FIX_VND_PATH, 777)){
        popup(NULL,"Não foi possível criar diretorio de relatorios");
        return 1;
      }
  }

  sprintf(file_path,"%s/vendas.html",REL_FIX_VND_PATH);

  int vnd_qnt=0;
  FILE *relat_file = fopen(file_path,"w");
  if(!relat_file){
    popup(NULL,"Não foi possível escrever relatório");
    file_logger(strerror(errno));
    return 1;
  }

  if(relat_fix_vnd_ped_fun())
    return 1;

  if(relat_fix_vnd_cli_fun())
    return 1;

  if(relat_fix_vnd_prod_fun())
    return 1;

  if(relat_fix_vnd_grp_fun())
    return 1;

  if(relat_fix_vnd_quebra_fun())
    return 1;

  if(relat_fix_vnd_totaliza_fun())
    return 1;

  if(relat_fix_vnd_sintetiza_fun())
    return 1;

  if(relat_fix_vnd_status_fun())
    return 1;

  if(relat_fix_vnd_est_fun())
    return 1;

  //sprintf(query,"select code, ")
  char *ordenacoes[] = {"o.code", "t.razao", "p_all.nome", "g_prc.valor_fat", "g_prc.valor_vist"};
  char *totalizacoes[] = {"po.unidades", "po.total"};

  relat_fix_vnd_vlrs.pedidos1 = atoi(relat_fix_vnd_ped_gchar1);
  relat_fix_vnd_vlrs.pedidos2 = atoi(relat_fix_vnd_ped_gchar2);

  relat_fix_vnd_vlrs.produtos1 = atoi(relat_fix_vnd_prod_gchar1);
  relat_fix_vnd_vlrs.produtos2 = atoi(relat_fix_vnd_prod_gchar2);

  relat_fix_vnd_vlrs.grupos1 = atoi(relat_fix_vnd_grp_gchar1);
  relat_fix_vnd_vlrs.grupos2 = atoi(relat_fix_vnd_grp_gchar2);

  relat_fix_vnd_vlrs.estoques1 = atoi(relat_fix_vnd_est_gchar1);
  relat_fix_vnd_vlrs.estoques2 = atoi(relat_fix_vnd_est_gchar2);

  relat_fix_vnd_vlrs.quebra = relat_fix_vnd_quebra_int;
  relat_fix_vnd_vlrs.totaliza = relat_fix_vnd_totaliza_int;
  relat_fix_vnd_vlrs.sintetiza = relat_fix_vnd_sintetiza_int;

  fprintf(relat_file,html_header);
  fprintf(relat_file,"<body>");
  fprintf(relat_file,"<div style='background: Gainsboro;'>");
  fprintf(relat_file,"<h1>Relatório de Vendas</h1>");
  fprintf(relat_file,"<p>%s</p>",data_sys);
  fprintf(relat_file,"</div>");

  float totalizacao_produtos=0, totalizacao_frete=0, totalizacao_geral=0;
  for(int cont=relat_fix_vnd_vlrs.pedidos1;cont<=relat_fix_vnd_vlrs.pedidos2;cont++){
      float vlr_ped=0,vlr_frete=0;

      if(!relat_fix_vnd_status_int)
        sprintf(query, "select ped.code, t.code, t.razao, t.doc, t.ie, DATE_FORMAT(ped.data_mov,'%%d/%%m/%%Y'), pag.nome, ped.status, t.cidade, t.uf, tc.telefone, tc.email from pedidos as ped inner join terceiros as t inner join pag_cond as pag inner join contatos as tc on ped.cliente = t.code and tc.terceiro = t.code and ped.pag_cond = pag.code where ped.code = %i and ped.status >= 0",cont);
      else
        sprintf(query, "select ped.code, t.code, t.razao, t.doc, t.ie, DATE_FORMAT(ped.data_mov,'%%d/%%m/%%Y'), pag.nome, ped.status, t.cidade, t.uf, tc.telefone, tc.email from pedidos as ped inner join terceiros as t inner join pag_cond as pag on ped.cliente = t.code and ped.pag_cond = pag.code and tc.terceiro = t.code where ped.code = %i and ped.status = %i",cont, relat_fix_vnd_status_int-1);

      if(!(res=consultar(query))){
        popup(NULL,"Erro ao consultar pedido");
        return 1;
      }
      fprintf(relat_file,"<div id='solid-container'>");
      fprintf(relat_file,"<table class='item-table'>");
      if((row = mysql_fetch_row(res))){

        if(atoi(row[1]) < atoi(relat_fix_vnd_cli_gchar1) || atoi(row[1]) > atoi(relat_fix_vnd_cli_gchar2))
          continue;

        fprintf(relat_file,"<tr class='relat-infos'>");
        fprintf(relat_file,"<td>Pedido: %s<td/>",row[0]);
        fprintf(relat_file,"<td>Cliente:  %s:%s<td/>",row[1],row[2]);
        fprintf(relat_file,"<td>CNPJ/CPF: %s<br>IE/RG: %s<td/>",row[3],row[4]);
        fprintf(relat_file,"<td>Data:  %s<td/>",row[5]);
        fprintf(relat_file,"<td>Pagamento:  %s<td/>",row[6]);

        sprintf(query, "select code from titulos where pedido = %i",cont);
        if(!(res2=consultar(query))){
          popup(NULL,"Erro ao consultar títulos");
          return 1;
        }

        if((row2 = mysql_fetch_row(res2))){
          fprintf(relat_file,"<td>Título: %s<td/>",row[0]);
        }else
          fprintf(relat_file,"<td>Sem Financeiro<td/>");

        fprintf(relat_file,"</tr>");

        fprintf(relat_file,"<tr class='relat-infos'>");
        fprintf(relat_file,"<td>Status: %s<td/>",ped_status_from_int(atoi(row[7])));
        fprintf(relat_file,"<td>Cidade/UF: %s/%s<td/>",row[8],row[9]);
        fprintf(relat_file,"<td>Telefone/Email: %s/%s<td/>",row[10],row[11]);
        vnd_qnt++;

        //total dos produtos
        sprintf(query, "select SUM(total) from Produto_Orcamento where code = %i",cont);
        if(!(res2=consultar(query))){
          popup(NULL,"Erro ao consultar pedido");
          return 1;
        }
        if((row2 = mysql_fetch_row(res2))){
          if(row2[0])
            vlr_ped = atof(row2[0]);
        }
        //valor do frete
        sprintf(query, "select SUM(vlr_frete) from servico_transporte where orcamento = %i",cont);
        if(!(res2=consultar(query))){
          popup(NULL,"Erro ao consultar pedido");
          return 1;
        }
        if((row2 = mysql_fetch_row(res2))){
          if(row2[0])
            vlr_frete = atof(row2[0]);
        }

        fprintf(relat_file,"<td>Vlr Frete: R$ %.2f<td/>",vlr_frete);
        fprintf(relat_file,"<td>Vlr Total: R$ %.2f<td/>",vlr_ped);
        fprintf(relat_file,"<td>Totais<td/>");

        totalizacao_frete += vlr_frete;

        fprintf(relat_file,"</tr>");
        fprintf(relat_file,"</table>");
        fprintf(relat_file,"<table>");
        sprintf(query, "select po.produto, p_all.nome, po.unidades, po.valor_unit, po.desconto, po.total from Produto_Orcamento as po inner join produtos_nome_all as p_all inner join grupos as g on po.subgrupo = g.code and p_all.code = g.code where po.code = %s",row[0]);
        if(!(res2=consultar(query))){
          popup(NULL,"Erro ao consultar pedido");
          return 1;
        }
        while((row2 = mysql_fetch_row(res2))){

          if(atoi(row2[0]) < atoi(relat_fix_vnd_prod_gchar1) || atoi(row2[0]) > atoi(relat_fix_vnd_prod_gchar2))
            continue;

          fprintf(relat_file,"<tr>");
          fprintf(relat_file,"<td>Código:  %s<td/>",row2[0]);
          fprintf(relat_file,"<td>%s<td/>",row2[1]);
          fprintf(relat_file,"<td>Qnt.: %.2f<td/>",atof(row2[2]));
          fprintf(relat_file,"<td>Vlr Unit.: R$ %.2f<td/>",atof(row2[3]));
          fprintf(relat_file,"<td>Vlr Desc: R$ %.2f<td/>",atof(row2[4]));
          fprintf(relat_file,"<td>Total: R$ %.2f<td/>",atof(row2[5]));
          totalizacao_produtos += atof(row2[5]);
          fprintf(relat_file,"</tr>");
          prod_qnt++;
        }
        if(!prod_qnt){
          fprintf(relat_file,"<tr>");
          fprintf(relat_file,"<td>Sem produtos no orçamento para os filtros<td/>");
          fprintf(relat_file,"</tr>");
        }
        fprintf(relat_file,"</table>");
        prod_qnt=0;
        totalizacao_geral += vlr_frete + vlr_ped;
        fprintf(relat_file,"<hr>");
      }
  }
  if(!vnd_qnt){
    popup(NULL,"Não Há nada a gerar");
    return 1;
  }
  fprintf(relat_file,"<table>");
  fprintf(relat_file,"<tr class='relat-infos'>");
  fprintf(relat_file,"<th>Total Produtos: R$ %.2f<th/>",totalizacao_produtos);
  fprintf(relat_file,"<th>Total Frete: R$ %.2f<th/>",totalizacao_frete);
  fprintf(relat_file,"<th>Total Geral: R$ %.2f<th/>",totalizacao_geral);
  fprintf(relat_file,"</tr>");

  fprintf(relat_file,"</table>");
  fprintf(relat_file,"</div>");
  fprintf(relat_file,"</body>");
  fprintf(relat_file,"</html>");
  fclose(relat_file);

  if(escolher_finalizacao(file_path)){
    return 1;
  }

  return 0;
}
