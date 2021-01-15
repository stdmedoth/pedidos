int gerar_orc_transporte(FILE *file, struct _orc *orc){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char *query = malloc(MAX_QUERY_LEN);

  sprintf(query,"select t.razao, st.cep_entrega, st.vlr_frete, st.valor_desconto_frete, st.observacoes_entrega from servico_transporte as st inner join terceiros as t on st.transportador = t.code where orcamento = %i", orc->infos.code);
  if(!(res = consultar(query))){
    popup(NULL,"Erro ao verificar entrega");
  }else{
    if((row=mysql_fetch_row(res))){
      fprintf(file,"<div id=\"campo-transporte\">\n");
      fprintf(file,"<p><b>Transporte</b></p>\n");
      fprintf(file,"<table>\n");

      fprintf(file,"<tr>\n");
      fprintf(file,"<th id=\"prod-row1\">Transportadora</td>\n");
      fprintf(file,"<th id=\"prod-row1\">CEP Entrega</th>\n");
      fprintf(file,"<th id=\"prod-row1\">Valor Frete</th>\n");
      fprintf(file,"<th id=\"prod-row1\">Valor Desconto</th>\n");
      fprintf(file,"</tr>\n");

      fprintf(file,"<tr>\n");
      if(row[0] && row[1]){
        fprintf(file,"<td>%s</td>\n",row[0]);
        fprintf(file,"<td>%s</td>\n",row[1]);
      }else{
        popup(NULL,"Erro nas informações do transporte");
        return 1;
      }

      if(row[2] && row[3]){
        fprintf(file,"<td>R$ %.2f</td>\n",atof(row[2]));
        fprintf(file,"<td>R$ %.2f</td>\n",atof(row[3]));
        orc->valores.valor_frete_liquido = atof(row[2]) - atof(row[3]);
      }else{
        popup(NULL,"Erro nos Valores do transporte");
        return 1;
      }

      fprintf(file,"</tr>\n");

      fprintf(file,"<tr>\n");
      sprintf(query,"select l.descricao, l.descricao_bairro, c.descricao, l.UF  from logradouro as l inner join cidade as c on l.id_cidade = c.code where CEP = '%s'",row[1]);

      if((res = consultar(query))){

        if((row = mysql_fetch_row(res)))
        {
          fprintf(file,"<td>\n");
          if(row[0])
            fprintf(file,"%s,",row[0]);
          if(orc_transp_num)
            fprintf(file,"%s",orc_transp_num);
          if(row[1])
            fprintf(file,", %s",row[1]);
          if(row[2])
            fprintf(file,", %s",row[2]);
          if(row[3])
            fprintf(file,", %s\n",row[3]);
          fprintf(file,"</td>\n");
        }else
        if(	concluindo_orc==1 ){
          fprintf(file,"<td>\n");
          if(orc_transp_logradouro && orc_transp_num)
            fprintf(file,"%s, %s",orc_transp_logradouro,orc_transp_num);
          if(orc_transp_bairro)
            fprintf(file,", %s",orc_transp_bairro);
          if(orc_transp_cidade)
            fprintf(file,", %s",orc_transp_cidade);
          if(orc_transp_estado)
            fprintf(file,", %s\n",orc_transp_estado);
          fprintf(file,"</td>\n");
        }

      }else{
        popup(NULL,"Erro ao consultar endereços");
        return 1;
      }

      fprintf(file,"</tr>\n");

      fprintf(file,"</table>\n");
      fprintf(file,"</div>\n");
    }
  }
  return 0;
}
