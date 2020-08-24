#include "impressao.c"
#define CLI_ROW_POS 2

int gerar_orc()
{
	carregar_navimps();

	if(!imps_qnt && !navs_qnt){
		popup(NULL,"Não há impressoras ou navegadores configurados!");
		return 1;
	}

	int cont,color=0;
	char *query;
	int conta_linhas=0;
	int erro,grupo_len,prods_sem_obs=0;
	char code[MAX_CODE_LEN];
	char *formata_float,*formata_float2,*formata_float3;
	double chartofloat,totalfloat;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *gerando_file;
	char **familia_char,*dest,*source;
	conta_linhas = 0;
	gerando_file = malloc(MAX_PATH_LEN*2);

	formata_float = malloc(MAX_PRECO_LEN); //desconto
	formata_float2 = malloc(MAX_PRECO_LEN); //quantidade
	formata_float3 = malloc(MAX_PRECO_LEN); //preco

	familia_char = malloc(MAX_SUBGRUPO*MAX_GRP_LEN+MAX_SUBGRUPO-1);
	source = malloc(MAX_SUBGRUPO*MAX_GRP_LEN+MAX_SUBGRUPO);
	dest = malloc(MAX_SUBGRUPO*MAX_GRP_LEN+MAX_SUBGRUPO);

	query = malloc(MAX_QUERY_LEN);
	if(codigo_orc()!=0)
		return 1;

	sprintf(gerando_file,"%simp%s.html",ORC_PATH,codigo_orc_gchar);

	sprintf(query,"select * from orcamentos where code = %s",codigo_orc_gchar);
	if(!(res = consultar(query)))
	{
		popup(NULL,"Erro na query! Por favor, Consulte com suporte.");
		autologger("Erro na query de codigo no orcamento\n");
		autologger(query);
		vet_erro[COD_ERR] = 0;
		gtk_widget_grab_focus(codigo_orc_entry);
		return 1;
	}
	gerar_total_geral();
	if(!(row = mysql_fetch_row(res)))
	{
			concluir_orc();
			return 1;
	}
	else
	{
		gtk_entry_set_text(GTK_ENTRY(cliente_orc_entry),row[CLI_ROW_POS]);
		if(codigo_cli_orc()!=0)
			return 1;
	}

	if(codigo_cli_orc()!=0)
		return 1;

	if(codigo_orc())
	  return 1;

if(orc_pag_tipo_int == CONDPAG_DT_LVR)
		if(concluir_datas_livres()){
			gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),2);
			return 1;
		}

	if(orc_bnc_code_fun()){
		gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),2);
		return 1;
	}

	orc = fopen(gerando_file,"w");
	if(orc==NULL)
	{
		popup(NULL,"Não está sendo possivel gerar o arquivo\n\tFeche o navegador");
		return 1;
	}

	sprintf(query,"select (%s%s),banco from orcamentos where code = %s",DATE_QUERY,codigo_orc_gchar,codigo_orc_gchar);
	if(!(res = consultar(query)))
	{
		popup(NULL,"Erro na query! Por favor, Consulte com suporte.");
		autologger("Erro na query de codigo no orcamento\n");
		fclose(orc);
		return 1;
	}
	if(!(row = mysql_fetch_row(res)))
	{
		popup(NULL,"Erro ao tentar receber orçamento");
		fclose(orc);
		return 1;
	}
	orc_parcelas.banco = atoi(row[1]);

	fprintf(orc,"<!DOCTYPE html>\n");
	fprintf(orc,"<html>\n");
	fprintf(orc,"<head>\n");
	fprintf(orc,"<meta charset=\"utf-8\"/>");
	fprintf(orc,"<link href=\"%s\" rel=\"stylesheet\">\n",CSS_ORC);
	fprintf(orc,"<title>Orcamento</title>\n");
	fprintf(orc,"</head>\n");

	fprintf(orc,"<body>\n");

	fprintf(orc,"<div id=\"caixa-imp\">\n");
	fprintf(orc,"<div id=\"div-titulo\">\n");
	fprintf(orc,"<img id=\"logo-img\" src=\"%s\" alt=\"PETITTO\">\n",IMG_IMP_LOGO);
	fprintf(orc,"</div>\n");
	fprintf(orc,"<div id=\"orc-infos\" align=left>\n");

	fprintf(orc,"<table>\n");

	fprintf(orc,"<tr>\n");
	fprintf(orc,"<td id=\"info-row1\">Número do Orcamento</td>\n");
	//fprintf(orc,"<td id=\"info-row1\">Cliente:</td>\n");
	fprintf(orc,"<td id=\"info-row1\">Data</td>\n");
	fprintf(orc,"</tr>\n");

	fprintf(orc,"<tr>\n");
	fprintf(orc,"<td>%s</td>\n",codigo_orc_gchar);
	fprintf(orc,"<td>%s</td>\n",row[0]);
	fprintf(orc,"<tr>\n");

	fprintf(orc,"</table>\n");

	fprintf(orc,"</div>\n");

	sprintf(query,"select observacoes from Produto_Orcamento where code = %i and length(observacoes) != 0",atoi(codigo_orc_gchar));
	if(!(res = consultar(query)))
	{
		popup(NULL,"Erro ao consultar existencia de observacoes");
		autologger("Erro na query de codigo no orcamento\n");
		gtk_widget_grab_focus(codigo_orc_entry);
		fclose(orc);
		return 1;
	}
	else
	if((row = mysql_fetch_row(res))==NULL)
		prods_sem_obs = 1;

	if(imp_cli(cliente_orc_gchar)!=0)
		return 1;

	sprintf(query,"select p.code, g.code,  o.unidades,  u.nome,  o.valor_unit,  o.tipodesc,  o.desconto,  o.total, o.observacoes from Produto_Orcamento as o inner join produtos as p inner join grupos as g on p.code = o.produto join unidades as u on u.code = p.unidades and g.code = o.subgrupo where o.code = %s;",codigo_orc_gchar);

	if(!(res = consultar(query)))
	{
		popup(NULL,"Erro na query! Por favor, Consulte com suporte.");
		autologger("Erro na query de codigo no orcamento\n");
		gtk_widget_grab_focus(codigo_orc_entry);
		fclose(orc);
		return 1;
	}

	cont=1;

	fprintf(orc,"<div id=\"separator\">");fprintf(orc,"</div>");
	fprintf(orc,"<div id=\"campo-itens\">\n");
	fprintf(orc,"<p><b>Produtos</b></p>\n");
	fprintf(orc,"<table>\n");
	fprintf(orc,"<tr>\n");
	//fprintf(orc,"<td id=\"prod-row1\">Código</td>\n",IMG_IMP_QNT);
	fprintf(orc,"<th id=\"prod-row1\"><img src=\"%s\" alt=\"\">Qnt. Unit.</td>\n",IMG_IMP_QNT);
	fprintf(orc,"<th id=\"prod-row1\"><img src=\"%s\" alt=\"\">Descrição do Produto</td>\n",IMG_IMP_PROD);
	if(prods_sem_obs == 0)
		fprintf(orc,"<th id=\"prod-row1\">Obs.</td>\n");
	fprintf(orc,"<th id=\"prod-row1\"><img src=\"%s\" alt=\"\">Valor Unitário.</td>\n",IMG_MONEY);
	fprintf(orc,"<th id=\"prod-row1\">Desconto</td>\n");
	fprintf(orc,"<th id=\"prod-row1\">Valor Total</td>\n");
	fprintf(orc,"</tr>\n");

	while((row = mysql_fetch_row(res))!=NULL)
	{
		fprintf(orc,"<tr class='tr-estilo'>\n");

		if(row[3][strlen(row[3])-1] != 's'&&atoi(row[2])>1)
			fprintf(orc,"<td>%s %ss</td>\n",row[2],row[3]);
		else
			fprintf(orc,"<td>%s %s</td>\n",row[2],row[3]);

		if(strlen(row[1])>20)
			row[1][20] = '\0';

		if((grupo_len = rec_familia_nome(familia_char, atoi(row[1]) ))<0){
			popup(NULL,"Erro na criação do html para subgrupo");
			return 1;
		}
		strcpy(dest,"");
		strcpy(source,"");
		for(int cont=grupo_len;cont>0;cont--)
		{
			sprintf(dest,"%s %s",source,familia_char[cont]);

			strcpy(source,dest);
		}

		fprintf(orc,"<td>Cod. %s: %s</td>\n",row[0],dest);
		if(prods_sem_obs == 0)
			fprintf(orc,"<td>%s</td>\n",row[8]);
		sprintf(formata_float,"%s",row[4]);
		critica_real(formata_float,NULL);
		fprintf(orc,"<td>R$ %.2f</td>\n",atof(formata_float));

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

			fprintf(orc,"<td>%.2f %c</td>\n",chartofloat,37);//desconto em R$ p/ %
		}
		else
		if(atoi(row[5])==1)//tipo desconto = %
		{

			fprintf(orc,"<td>%.2f %c</td>\n",atof(row[6]),37);//desconto em %//atof(row[6]),37);//desconto em %
		}

		sprintf(formata_float,"%s",row[7]);
		critica_real(formata_float,NULL);
		fprintf(orc,"<td>R$ %.2f</td>\n",atof(formata_float));//total
		fprintf(orc,"</tr>\n");
		conta_linhas++;

		cont++;
	}
	if(cont == 0)
	{
		popup(NULL,"Sem itens no orçamento");
		fclose(orc);
		return 0;
	}
	sprintf(query,"select sum(total) from Produto_Orcamento where code = %s",codigo_orc_gchar);
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
		autologger("Erro ao tentar receber total dos produtos no orcamento");
		return 1;
	}
	if(row[0])
		orc_valores.valor_prds_liquido = atof(row[0]);

	sprintf(formata_float,"%.2f",orc_valores.valor_prds_liquido);

	fprintf(orc,"<td></td>");
	fprintf(orc,"<td></td>");
	fprintf(orc,"<td></td>");
	fprintf(orc,"<td></td>");
	fprintf(orc,"<td>Subtotal: R$ %.2f</td>\n",atof(formata_float));
	fprintf(orc,"<tr>");
	fprintf(orc,"</table>\n");

	sprintf(query,"select t.razao, st.cep_entrega, st.vlr_frete, st.valor_desconto_frete, st.observacoes_entrega from servico_transporte as st inner join terceiros as t on st.transportador = t.code where orcamento = %s", codigo_orc_gchar);
	if(!(res = consultar(query))){
		popup(NULL,"Erro ao verificar entrega");
	}else{
		if((row=mysql_fetch_row(res))){
			fprintf(orc,"<p><b>Transporte</b></p>\n");
			fprintf(orc,"<table>\n");

			fprintf(orc,"<tr>\n");
			fprintf(orc,"<th id=\"prod-row1\">Transportadora</td>\n");
			fprintf(orc,"<th id=\"prod-row1\">CEP Entrega</th>\n");
			fprintf(orc,"<th id=\"prod-row1\">Valor Frete</th>\n");
			fprintf(orc,"<th id=\"prod-row1\">Valor Desconto</th>\n");
			fprintf(orc,"</tr>\n");

			fprintf(orc,"<tr>\n");
			fprintf(orc,"<td>%s</td>\n",row[0]);
			fprintf(orc,"<td>%s</td>\n",row[1]);
			if(row[2])
				fprintf(orc,"<td>R$ %.2f</td>\n",atof(row[2]));
			if(row[3])
				fprintf(orc,"<td>R$ %.2f</td>\n",atof(row[3]));
			fprintf(orc,"</tr>\n");

			fprintf(orc,"<tr>\n");
			sprintf(query,"select l.descricao, l.descricao_bairro, c.descricao, l.UF  from logradouro as l inner join cidade as c on l.id_cidade = c.id_cidade where CEP = '%s'",row[1]);

			if((res = consultar(query))){

				if((row = mysql_fetch_row(res)))
				{
					fprintf(orc,"<td>\n");
					if(row[0])
						fprintf(orc,"%s,",row[0]);
					if(orc_transp_num)
						fprintf(orc,"%s",orc_transp_num);
					if(row[1])
						fprintf(orc,", %s",row[1]);
					if(row[2])
						fprintf(orc,", %s",row[2]);
					if(row[3])
						fprintf(orc,", %s\n",row[3]);
					fprintf(orc,"</td>\n");
				}else{
					fprintf(orc,"<td>\n");
					if(orc_transp_logradouro && orc_transp_num)
						fprintf(orc,"%s, %s",orc_transp_logradouro,orc_transp_num);
					if(orc_transp_bairro)
						fprintf(orc,", %s",orc_transp_bairro);
					if(orc_transp_cidade)
						fprintf(orc,", %s",orc_transp_cidade);
					if(orc_transp_estado)
						fprintf(orc,", %s\n",orc_transp_estado);
					fprintf(orc,"</td>\n");
				}

			}else{
				popup(NULL,"Erro ao consultar endereços");
				return 1;
			}

			fprintf(orc,"</tr>\n");

			fprintf(orc,"</table>\n");
		}
	}
	fprintf(orc,"</div>\n");
		fprintf(orc,"<div id=\"campo-titulos\">\n");

	fprintf(orc,"<div id=\"campo-totais\">\n");
	fprintf(orc,"<p><b>Totalizações</b></p>\n");
	fprintf(orc,"<table>\n");

	fprintf(orc,"<tr>\n");
	fprintf(orc,"<th id=\"prod-row1\">Parcela</th>\n");
	fprintf(orc,"<th id=\"prod-row1\">Vencimento</th>\n");
	fprintf(orc,"<th id=\"prod-row1\">Valor</th>\n");
	fprintf(orc,"</tr>\n");

	for(int cont=0;cont<orc_parcelas.parcelas_qnt;cont++){
		fprintf(orc,"<tr>\n");
		fprintf(orc,"<td>%i</td>",cont+1);
		fprintf(orc,"<td>%s</td>",orc_parcelas.parcelas_data[cont]);
		fprintf(orc,"<td>R$ %.2f</td>\n",orc_parcelas.parcelas_vlr[cont]);
		fprintf(orc,"</tr>\n");
	}

	fprintf(orc,"<tr>\n");
	fprintf(orc,"<td></td>");
	fprintf(orc,"<td></td>");
	fprintf(orc,"<td>Total: R$ %.2f</td>\n",orc_parcelas.total_geral);
	fprintf(orc,"</tr>\n");

	fprintf(orc,"</table>\n");
	fprintf(orc,"</div>\n");

	fprintf(orc,"<div id=\"banco-infos\">\n");
	sprintf(query,"select * from bancos where code = %i",orc_parcelas.banco);
	if((res = consultar(query))){
		if((row = mysql_fetch_row(res))){
			fprintf(orc,"<div class='wrapper banco'>");
			fprintf(orc,"<div>Banco: %s</div>",row[1]);
			fprintf(orc,"<div>Conta: %s</div>",row[2]);
			fprintf(orc,"<div>Agência:  %s</div>",row[4]);
			fprintf(orc,"<div>Beneficiário:  %s</div>", row[5]);
			fprintf(orc,"<div>CNPJ/CPF:  %s</div>", row[6]);
			fprintf(orc,"</div>");

		}
	}
	fprintf(orc,"</div>\n");

	fprintf(orc,"</div>\n");

	observacoes_orc_get();
	fprintf(orc,"<div id=\"obs-div1\">\n");
	fprintf(orc,"Observacões\n");
	fprintf(orc,"<div id=\"obs-div2\">\n");

	sprintf(query,"select t.code_nfe, o.observacoes from orcamentos as o inner join terceiros as t on o.cliente = t.code where o.code = %i",orc_infos.cliente_code);
	if(!(res = consultar(query))){
		popup(NULL,"Erro ao verificar entrega");
	}else{
		if((row=mysql_fetch_row(res))){
			if(row[0] && row[1])
			{
				if(strlen(row[0]))
					fprintf(orc,"Cod. Cliente : %s<br>",row[0]);
				if(strcmp(row[1],"(null)")!=0)
				{
					fprintf(orc,"%s",row[1]);
				}
			}

		}
	}

	fprintf(orc,"</div>\n");
	fprintf(orc,"</div>\n");
	fprintf(orc,"</div>\n");
	fprintf(orc,"</body>\n");
	fprintf(orc,"</html>\n");
	fclose(orc);

	if(escolher_finalizacao(gerando_file)){
		cancela_orc();
		return 1;
	}

	return 0;
}
