#include "impressao.c"
#define CLI_ROW_POS 2

GtkWidget *msg_abrir_orc_window;
int abrir_orc(GtkWidget *widget,char *uri)
{
	GError *erro;
	//GtkWidget *mount;
	//GdkScreen *screen;
	//GdkDisplay *display;
	//display = gdk_display_get_default();
	//mount = gtk_mount_operation_new(GTK_WINDOW(janela_orcamento));
	//screen = gdk_display_get_default_screen(display);
	//gtk_mount_operation_set_screen(GTK_MOUNT_OPERATION(mount),screen);
	if(gtk_show_uri_on_window(GTK_WINDOW(janela_orcamento),uri,GDK_CURRENT_TIME,&erro)==FALSE)
		return 1 ;
	return 0;
}

int msg_abrir_orc(GtkWidget *parent,char *path)
{
	GtkWidget *link_button;	
	char * uri;
	uri = malloc(MAX_URI_LEN);
	msg_abrir_orc_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(msg_abrir_orc_window),GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_keep_above(GTK_WINDOW(msg_abrir_orc_window),TRUE);
	link_button = gtk_link_button_new_with_label(path,"Abrir Orcamento");
	gtk_link_button_set_visited(GTK_LINK_BUTTON(link_button),FALSE);
	sprintf(uri,"file://%s",path);
	g_print("URI a ser visualizado %s\n",uri);
	gtk_container_add(GTK_CONTAINER(msg_abrir_orc_window),link_button);
	g_signal_connect(link_button,"activate-link",G_CALLBACK(abrir_orc),uri);
	gtk_widget_show_all(msg_abrir_orc_window);
	return 0;
}

int gerar_orc()
{
	int vnd_orc();
	g_print("gerando orçamento...\n");
	int cont,error,nav=1;
	char *query;
	char *path;
	char *abrir;
	FILE *navegador;
	int erro;
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	MYSQL_RES *res;
	MYSQL_ROW row;
	abrir = malloc(MAX_PATH_LEN);
	path = malloc(MAX_PATH_LEN);
	path = malloc(MAX_PATH_LEN);
	query = malloc(MAX_QUERY_LEN);
	sprintf(path,"%simp%s.html",ORC_PATH,codigo_orc_gchar);
	sprintf(abrir,"firefox %s",path);
	if(codigo_orc()!=0)
		return 1;
	
	sprintf(query,"select * from orcamentos where code = %s",codigo_orc_gchar);
	vetor = consultar(query);
	if(vetor==NULL)
	{
		popup(NULL,"Erro na query! Por favor, Consulte com suporte.");
		g_print("Erro na query de codigo no orcamento\n");
		autologger("Erro na query de codigo no orcamento\n");
		autologger(query);
		vet_erro[COD_ERR] = 0;
		gtk_widget_grab_focus(codigo_orc_entry);
		fclose(orc);
		return 1;
	}
	campos = mysql_fetch_row(vetor);
	if(campos == NULL)
	{
		sprintf(query,"insert into orcamentos(code,vendedor,cliente,dia,total) values(%s,1,%s,'%s-%s-%s',0.0);",codigo_orc_gchar,cliente_orc_gchar,ano_sys,mes_sys,dia_sys);
		erro = enviar_query(query);
		if(erro != 0 )
		{
			popup(NULL,"Erro ao tentar gerar orçamento");
			fclose(orc);
			return 1;
		}
		for(cont=1;cont<itens_qnt-1;cont++)
		{
			if(ativos[cont].id == 1)
			{
				if(codigo_cli_orc()!=0)
					return 1;			
				if(qnt_prod_orc(qnt_prod_orc_entry[cont],cont)!=0)
					return 1;
				if(preco_prod_orc(preco_prod_orc_entry[cont],cont)!=0)
					return 1;
				if(total_prod_orc(total_prod_orc_entry[cont],cont)!=0)
					return 1;
				if(strlen(ativos[cont].desconto_c)<=0)
				{
					strcpy(ativos[cont].desconto_c,"0.0");
				}
				sprintf(query,"insert into Produto_Orcamento(code,item,produto,unidades,valor_unit,desconto,total) values(%s,%i,%i,%s,%s,%s,%s);",codigo_orc_gchar,cont,ativos[cont].produto, ativos[cont].qnt_c, ativos[cont].preco_c, ativos[cont].desconto_c ,ativos[cont].total_c);
				erro = enviar_query(query);
				if(erro != 0 )
				{
					popup(NULL,"Erro ao tentar gerar orçamento");
					fclose(orc);
					return 1;
				}
				sprintf(query,"update orcamentos set total = (select sum(total) from Produto_Orcamento where code = %s) where code = %s",codigo_orc_gchar,codigo_orc_gchar);
				erro = enviar_query(query);
				if(erro != 0 )
				{
					popup(NULL,"Erro ao tentar gerar orçamento");
					fclose(orc);
					return 1;
				}
			}
		}
		if(ativos_qnt==0)
		{
			popup(NULL,"Não há produtos no orçamento");
			fclose(orc);
			return 1;
		}
		
	}
	else
	{
		gtk_entry_set_text(GTK_ENTRY(cliente_orc_entry),campos[CLI_ROW_POS]);
		if(codigo_cli_orc()!=0)
			return 1;			
	}
	
	orc = fopen(path,"w");
	if(orc==NULL)
	{
		popup(NULL,"Não está sendo possivel gerar o arquivo\n\tFeche o navegador");
		return 1;
	}
	
	sprintf(query,"select distinct (%s%s),o.total from orcamentos as o join terceiros as t where o.code = %s",DATE_QUERY,codigo_orc_gchar,codigo_orc_gchar);
	
	vetor = consultar(query);
	if(vetor==NULL)
	{
		popup(NULL,"Erro na query! Por favor, Consulte com suporte.");
		g_print("Erro na query de codigo no orcamento\n");
		autologger("Erro na query de codigo no orcamento\n");
		autologger(query);
		fclose(orc);
		return 1;
	}	
	campos = mysql_fetch_row(vetor);
	if(campos == NULL)
	{
		popup(NULL,"Erro ao tentar receber orçamento");
		fclose(orc);
		return 1;
	}
	
	fprintf(orc,"<body>\n");
	fprintf(orc,"<div id=\"caixa-imp\">\n");
	if(imp_head()!=0)
		return 1;
	fprintf(orc,"<div id=\"orc-infos\" align=left>\n");
	fprintf(orc,"<table>\n");
	
	fprintf(orc,"<tr>\n");
	fprintf(orc,"<td id=\"info-row1\">Número do Orcamento</td>\n");
	//fprintf(orc,"<td id=\"info-row1\">Cliente:</td>\n"); 
	fprintf(orc,"<td id=\"info-row1\">Data</td>\n");
	fprintf(orc,"</tr>\n");
	
	fprintf(orc,"<tr>\n");
	fprintf(orc,"<td>%s</td>\n",codigo_orc_gchar);
	fprintf(orc,"<td>%s</td>\n",campos[0]);
	fprintf(orc,"<tr>\n");
	
	fprintf(orc,"</table>\n");
	fprintf(orc,"</div>\n");
	
	if(imp_cli(cliente_orc_gchar)!=0)
		return 1;
	sprintf(query,"select p.nome,o.unidades,u.nome,o.valor_unit,o.desconto,o.total from Produto_Orcamento as o inner join produtos as p on p.code = o.produto join unidades as u on u.code = p.unidade where o.code = %s;",codigo_orc_gchar);
	vetor = consultar(query);
	if(vetor==NULL)
	{
		popup(NULL,"Erro na query! Por favor, Consulte com suporte.");
		g_print("Erro na query de codigo no orcamento\n");
		autologger("Erro na query de codigo no orcamento\n");
		autologger(query);
		vet_erro[COD_ERR] = 0;
		gtk_widget_grab_focus(codigo_orc_entry);
		fclose(orc);
		return 1;
	}
	cont=1;
	fprintf(orc,"<div id=\"separator\">\n");
	fprintf(orc,"</div>");
	fprintf(orc,"<div id=\"campo-itens\">\n");
	fprintf(orc,"<table>\n");
	fprintf(orc,"<tr>\n");
	fprintf(orc,"<td id=\"prod-row1\"></td>\n");
	fprintf(orc,"<td id=\"prod-row1\"><img src=\"%s\" alt=\"\">Produto</td>\n",IMG_IMP_PROD);
	fprintf(orc,"<td id=\"prod-row1\"><img src=\"%s\" alt=\"\">Quantidade</td>\n",IMG_IMP_QNT);  
	fprintf(orc,"<td id=\"prod-row1\"><img src=\"%s\" alt=\"\">Preco</td>\n",IMG_MONEY);
	fprintf(orc,"<td id=\"prod-row1\">Desconto </td>\n");
	fprintf(orc,"<td id=\"prod-row1\">Valor Total</td>\n");
	fprintf(orc,"</tr>\n");
	
	while((campos = mysql_fetch_row(vetor))!=NULL)
	{
		fprintf(orc,"<tr>\n");
		fprintf(orc,"<td>Item %i</td>\n",cont);
		fprintf(orc,"<td>%s</td>\n",campos[0]);
		fprintf(orc,"<td>%s %s</td>\n",campos[1],campos[2]);  
		fprintf(orc,"<td>R$ %.2f</td>\n",atof(campos[3]));
		fprintf(orc,"<td>R$ %.2f</td>\n",atof(campos[4]));
		fprintf(orc,"<td>R$ %.2f</td>\n",atof(campos[5]));
		fprintf(orc,"</tr>\n");
		cont++;
	}
	if(cont == 0)
	{
		popup(NULL,"Sem itens no orçamento");
		fclose(orc);
		return 0;
	}
	sprintf(query,"select total from orcamentos where code = %s",codigo_orc_gchar);	
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
	fprintf(orc,"<td id=\"total-geral\">Total Geral: R$ %.2f</td>\n",atof(row[0]));	
	fprintf(orc,"</table>\n");

	fprintf(orc,"<div>\n");

	fprintf(orc,"</div>\n");	
	fprintf(orc,"</div>\n");
	fprintf(orc,"</body>\n");
	fclose(orc);
	g_print("Gerando URI para impressao\n");
	if(msg_abrir_orc(janela_orcamento,path)==0)
	{
		g_print("URI para impressao gerado\n");
		popup(NULL,"Gerado!");
	}
	else
	{
		popup(NULL,"Erro ao tentar gerar URI");
		return 1;
	}
	return 0;
}
