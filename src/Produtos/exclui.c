int exclui_prod()
{
	char stringer[10];
	char query[100];
	int erro;
	MYSQL_RES *estado;
	MYSQL_ROW campo;
	GtkTextBuffer *buffer;
	GtkTextIter inicio,fim;

	gchar *foreign_tables[] = {
		"Produto_Orcamento",
		"precos",
		"saldo_min",
		"saldo_max",
		"movimento_estoque",
		"prod_requisicoes",
		"itens_compras",
		NULL
	};

	gchar *code = (gchar *)gtk_entry_get_text(GTK_ENTRY(codigo_prod_field));
	for(int cont=0;foreign_tables[cont];cont++){
		sprintf(query,"select * from %s where produto = '%s'",foreign_tables[cont], code);
		if(!(estado = consultar(query))){
			popup(NULL,"Não foi possível consultar tabela vinculada ao produto");
			return 1;
		}
		if((campo = mysql_fetch_row(estado))){
			gchar *msg = malloc(100 + strlen(foreign_tables[cont]));
			sprintf(msg,"Produto vinculado à %s, deseja remover essa informação?", foreign_tables[cont]);
			if(PopupBinario(msg, "Sim, remova para mim", "Não! irei utilizar")){
				sprintf(query,"delete from %s where produto = %s", foreign_tables[cont], code);
				if(enviar_query(query)){
					sprintf(msg,"Não foi possível remover o vinculo do produto com %s", foreign_tables[cont]);
					popup(NULL,msg);
					return 1;
				}
			}else{
				return 1;
			}
		}
	}

	sprintf(query,"delete from produtos where code = %s", code);
	if(enviar_query(query)){
		popup(NULL,"Não foi possível deletar produto");
		return 1;
	}

	popup(NULL,"Deletado com sucesso");
	cancelar_prod();
	return 0;
}
