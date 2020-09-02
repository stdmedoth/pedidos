int rel_fix_fin_rec_gerar(){

  MYSQL_RES *res,*res2,*res3;
  MYSQL_ROW row,row2,row3;

  char query[MAX_QUERY_LEN];
  char status_char[5];
  int fin_qnt=0;
  char *file_path = malloc(strlen(REL_FIX_FIN_PATH)+20);
  char html_header[] = "<!DOCTYPE html>"
  "<html>"
    "<head>"
      "<meta charset=\"utf-8\"/>"
      "<title>Relatório de Títulos à Receber</title>"
      "<link href=\"../../styles/relatorios.css\" rel=\"stylesheet\">"
    "</head>";

  GDir *teste;
  if(!(teste = g_dir_open(REL_FIX_FIN_PATH,0,NULL))){
    if(g_mkdir_with_parents(REL_FIX_FIN_PATH, 777)){
      popup(NULL,"Não foi possível abrir/criar diretório do arquivo");
      return 1;
    }
  }

  sprintf(file_path,"%s/receber.html",REL_FIX_FIN_PATH);
  FILE *file_arq = fopen(file_path,"w");
  if(!file_arq){
    popup(NULL,"Não foi possivel escrever no arquivo");
    return 1;
  }

  if(rel_fix_fin_rec_validar())
    return 1;

  if(rel_fix_fin_rec_status_int){
    strcpy(status_char,"=");
    rel_fix_fin_rec_status_int--;
  }
  else{
    strcpy(status_char,">=");
  }

  fprintf(file_arq,"%s",html_header);
  fprintf(file_arq,"<body>");
  fprintf(file_arq,"<div style='background: Gainsboro;'>");
  fprintf(file_arq,"<h1>Relatório de Títulos à receber</h1>");
  fprintf(file_arq,"<p>%s</p>",data_sys);
  fprintf(file_arq,"</div>");
  fprintf(file_arq,"<table>");

  float parcela = 0, baixa = 0;
  float vlr_total_parcelas=0, vlr_total_baixas=0, vlr_total_faltante=0;

  for(int cont=atoi(rel_fix_fin_rec_tit_gchar1);cont<=atoi(rel_fix_fin_rec_tit_gchar2);cont++){
    sprintf(query,"select tit.code, t.code, t.razao, t.doc, t.ie, tit.pedido, tit.status "
    "from titulos as tit inner join terceiros as t on tit.cliente = t.code "
    "where tit.tipo_titulo = %i and tit.code = %i and status %s %i",
    TP_TIT_REC,
    cont,
    status_char,
    rel_fix_fin_rec_status_int);

    if(!(res = consultar(query))){
      popup(NULL,"Erro ao buscar o título");
      return 1;
    }

    if((row = mysql_fetch_row(res))){
      float total_do_tit=0, total_da_baixa=0, total_a_baixar=0;

      if(atoi(row[1]) < atoi(rel_fix_fin_rec_cli_gchar1) || atoi(row[1]) > atoi(rel_fix_fin_rec_cli_gchar2))
        continue;

      if(atoi(row[5]) < atoi(rel_fix_fin_rec_ped_gchar1) || atoi(row[5]) > atoi(rel_fix_fin_rec_ped_gchar2))
        continue;

      sprintf(query,"select posicao,DATE_FORMAT(data_criacao,'%%d/%%m/%%Y'),DATE_FORMAT(data_vencimento,'%%d/%%m/%%Y'),valor from parcelas_tab where parcelas_id = %s", row[0]);

      if(!(res2 = consultar(query))){
        popup(NULL,"Erro ao consultar parcelas");
        return 1;
      }

      if(mysql_num_rows(res2)){

        fprintf(file_arq,"<tr class='relat-infos'>");
        fprintf(file_arq,"<td>Título: %s<td/>",row[0]);
        fprintf(file_arq,"<td>Terceiro:  %s/%s<td/>",row[1],row[2]);
        fprintf(file_arq,"<td>CNPJ/CPF: %s<br>IE/RG: %s<td/>",row[3],row[4]);
        if(atoi(row[5]))
          fprintf(file_arq,"<td>Pedido: %s<td/>",row[5]);
        else
          fprintf(file_arq,"<td>Pedido: Sem Vínculo<td/>");
        fprintf(file_arq,"<td>Status: %s<td/>",status_tit_str(atoi(row[6])));

        fprintf(file_arq,"</tr>");

        while((row2 = mysql_fetch_row(res2))){
          parcela = atof(row2[3]);

          vlr_total_parcelas += parcela;

          total_do_tit += parcela;

          fprintf(file_arq,"<tr class='tr-focus'>");
          fprintf(file_arq,"<td>Parcela: %s<td/>",row2[0]);
          fprintf(file_arq,"<td>Criação:  %s<td/>",row2[1]);
          fprintf(file_arq,"<td>Vencimento: %s<td/>",row2[2]);
          fprintf(file_arq,"<td>Valor: R$ %.2f<td/>",parcela);
          fprintf(file_arq,"</tr>");
          fin_qnt++;

          sprintf(query,"select id_baixa,DATE_FORMAT(data_criacao,'%%d/%%m/%%Y'),valor from baixas_titulos where parcelas_id = %i and posicao = %i", cont, atoi(row2[0]));
          if(!(res3 = consultar(query))){
            popup(NULL,"Erro ao consultar baixas");
            return 1;
          }

          while((row3 = mysql_fetch_row(res3))){
            baixa =  atof(row3[2]);
            vlr_total_baixas += baixa;
            total_da_baixa += baixa;

            if(atoi(row[0]) < atoi(rel_fix_fin_rec_bx_gchar1) || atoi(row[0]) > atoi(rel_fix_fin_rec_bx_gchar2))
              continue;

            fprintf(file_arq,"<tr>");
            fprintf(file_arq,"<td>Nº Baixa: %s<td/>",row3[0]);
            fprintf(file_arq,"<td><td/>");
            fprintf(file_arq,"<td>Baixado em:  %s<td/>",row3[1]);
            fprintf(file_arq,"<td>Valor Baixado: R$ %.2f<td/>",baixa);
            fprintf(file_arq,"<td>Valor Restante: R$ %.2f<td/>",total_do_tit - total_da_baixa);
            fprintf(file_arq,"</tr>");
          }

          vlr_total_faltante += total_do_tit - total_da_baixa;
        }
      }
      fprintf(file_arq,"<tr><td><b>Total: R$ %.2f</b></td></tr>",total_do_tit);
      fprintf(file_arq,"<tr><td><b>Baixa: R$ %.2f</b></td></tr>",total_da_baixa);
      fprintf(file_arq,"<tr><td><b>À Baixar: R$ %.2f</b></td></tr>",total_do_tit - total_da_baixa);

    }
  }
  fprintf(file_arq,"</table>");

  fprintf(file_arq,"<table class='tabela-conteudo'>");
  fprintf(file_arq,"<tr><td><b>Total em Títulos: R$ %.2f</b></td></tr>",vlr_total_parcelas);
  fprintf(file_arq,"<tr><td><b>Total Baixado: R$ %.2f</b></td></tr>",vlr_total_baixas);
  fprintf(file_arq,"<tr><td><b>Total à Baixar: R$ %.2f</b></td></tr>",vlr_total_parcelas - vlr_total_baixas);
  fprintf(file_arq,"</table>");

  fprintf(file_arq,"</body>");
  fprintf(file_arq,"</html>");
  fclose(file_arq);

  if(!fin_qnt){
    popup(NULL,"Não Há nada a gerar");
    return 1;
  }
  if(escolher_finalizacao(file_path)){
    return 1;
  }
  return 0;
}



int rel_fix_fin_rec_validar(){
  if(rel_fix_fin_rec_ped1_fun())
    return 1;
  if(rel_fix_fin_rec_ped2_fun())
    return 1;

  if(rel_fix_fin_rec_tit1_fun())
    return 1;
  if(rel_fix_fin_rec_tit2_fun())
    return 1;

  if(rel_fix_fin_rec_status_fun())
    return 1;

  if(rel_fix_fin_rec_bx1_fun())
    return 1;
  if(rel_fix_fin_rec_bx2_fun())
    return 1;

  if(rel_fix_fin_rec_cli1_fun())
    return 1;
  if(rel_fix_fin_rec_cli2_fun())
    return 1;

  if(rel_fix_fin_rec_datacriacao1_fun())
    return 1;
  if(rel_fix_fin_rec_datacriacao2_fun())
    return 1;

  if(rel_fix_fin_rec_databaixa1_fun())
    return 1;
  if(rel_fix_fin_rec_databaixa2_fun())
    return 1;

  if(rel_fix_fin_rec_datavencimento1_fun())
    return 1;
  if(rel_fix_fin_rec_datavencimento2_fun())
    return 1;

  if(rel_fix_fin_rec_combovalor_fun())
    return 1;

  if(rel_fix_fin_rec_entryvalor_fun())
    return 1;

  return 0;
}
