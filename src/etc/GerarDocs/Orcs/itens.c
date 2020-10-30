int gerar_orc_itens(FILE *file, struct _orc *orc){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char *query = malloc(MAX_QUERY_LEN);
  char *formata_float = malloc(MAX_PRECO_LEN); //desconto
	char *formata_float2 = malloc(MAX_PRECO_LEN); //quantidade
	char *formata_float3 = malloc(MAX_PRECO_LEN); //preco
  int erro,prods_sem_obs=0;
  double chartofloat,totalfloat;
  int conta_linhas = 0;

  sprintf(query,"select observacoes from Produto_Orcamento where code = %i and length(observacoes) != 0",orc->infos.code);
	if(!(res = consultar(query)))
	{
		popup(NULL,"Erro ao consultar existencia de observacoes");
		autologger("Erro na query de codigo no orcamento\n");
		return 1;
	}
	else
	if((row = mysql_fetch_row(res))==NULL)
		prods_sem_obs = 1;

	sprintf(query,"select p.code, p.nome,  o.unidades,  u.nome,  o.valor_unit,  o.tipodesc,  o.desconto,  o.total, o.observacoes from Produto_Orcamento as o inner join produtos as p on p.code = o.produto join unidades as u on u.code = p.unidades where o.code = %i;",orc->infos.code);

	if(!(res = consultar(query)))
	{
		popup(NULL,"Erro na query! Por favor, Consulte com suporte.");
		autologger("Erro na query de codigo no orcamento\n");
		return 1;
	}

	cont=1;

	fprintf(file,"<div id=\"campo-itens\">\n");
	fprintf(file,"<p><b>Produtos</b></p>\n");
	fprintf(file,"<table>\n");
	fprintf(file,"<tr>\n");
	//fprintf(orc,"<td id=\"prod-row1\">Código</td>\n",IMG_IMP_QNT);
	fprintf(file,"<th id=\"prod-row1\"><img src=\"%s\" alt=\"\">Qnt. Unit.</td>\n",IMG_IMP_QNT);
	fprintf(file,"<th id=\"prod-row1\"><img src=\"%s\" alt=\"\">Descrição do Produto</td>\n",IMG_IMP_PROD);
	if(prods_sem_obs == 0)
	 fprintf(file,"<th id=\"prod-row1\">Obs.</td>\n");
	fprintf(file,"<th id=\"prod-row1\"><img src=\"%s\" alt=\"\">Valor Unitário.</td>\n",IMG_MONEY);
	fprintf(file,"<th id=\"prod-row1\">Desconto</td>\n");
	fprintf(file,"<th id=\"prod-row1\">Valor Total</td>\n");
	fprintf(file,"</tr>\n");

	while((row = mysql_fetch_row(res))!=NULL)
	{
		fprintf(file,"<tr class='tr-estilo'>\n");

		if(row[3][strlen(row[3])-1] != 's'&&atoi(row[2])>1)
			fprintf(file,"<td>%s %ss</td>\n",row[2],row[3]);
		else
			fprintf(file,"<td>%s %s</td>\n",row[2],row[3]);

		if(strlen(row[1])>20)
			row[1][20] = '\0';


		fprintf(file,"<td>%s (Cod. %s)</td>\n",row[1], row[0]);
		if(prods_sem_obs == 0)
			fprintf(file,"<td>%s</td>\n",row[8]);
		sprintf(formata_float,"%s",row[4]);
		critica_real(formata_float,NULL);
		fprintf(file,"<td>R$ %.2f</td>\n",atof(formata_float));

		if(atoi(row[5])==0)//tipo desconto = R$
		{

			sprintf(formata_float,"%s",row[6]);//pega desconto
			critica_real(formata_float,NULL);

			sprintf(formata_float2,"%s",row[2]);//pega quantidade
			sprintf(formata_float3,"%s",row[4]);//pega preco
			critica_real(formata_float2,NULL);
			critica_real(formata_float3,NULL);
			totalfloat = atof(row[2])*atof(row[4]);

			//conversao de R$ para %
			//R$2.2 = 100%
			//R$1.1 = x%

			chartofloat = atof(row[6]);

			chartofloat = chartofloat*100.00;

			if(totalfloat>0)
				chartofloat = chartofloat/totalfloat;

			fprintf(file,"<td>%.2f %c</td>\n",chartofloat,37);//desconto em R$ p/ %
		}
		else
		if(atoi(row[5])==1)//tipo desconto = %
		{

			fprintf(file,"<td>%.2f %c</td>\n",atof(row[6]),37);//desconto em %//atof(row[6]),37);//desconto em %
		}

		sprintf(formata_float,"%s",row[7]);
		critica_real(formata_float,NULL);
		fprintf(file,"<td>R$ %.2f</td>\n",atof(formata_float));//total
		fprintf(file,"</tr>\n");
		conta_linhas++;

		cont++;
	}
	if(cont == 0)
	{
		popup(NULL,"Sem itens no orçamento");
		return 1;
	}
  sprintf(query,"select sum(total) from Produto_Orcamento where code = %i",orc->infos.code);
  res = consultar(query);
  if(res==NULL)
  {
    popup(NULL,"Erro de query! Consulte suporte");
    autologger("Erro ao tentar receber total dos produtos no orcamento");
    return 1;
  }
  if((row = mysql_fetch_row(res))==NULL)
  {
    popup(NULL,"Nenhum Total encontrado\n\tCaso seja erro, consulte suporte");
    autologger("Total dos produtos vazio no orcamento");
    return 1;
  }

  if(row[0])
    orc->valores.valor_prds_liquido = atof(row[0]);
  else{
    popup(NULL,"Valor total dos produtos nulo");
    return 1;
  }

  sprintf(formata_float,"%.2f",orc->valores.valor_prds_liquido);

  fprintf(file,"<td></td>");
  fprintf(file,"<td></td>");
  fprintf(file,"<td></td>");
  fprintf(file,"<td></td>");
  fprintf(file,"<td>Subtotal: R$ %.2f</td>\n",atof(formata_float));
  fprintf(file,"<tr>");
  fprintf(file,"</table>\n");

  fprintf(file,"</div>\n");


  return 0;
}
