int conclui_subgrupo()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	
	subgrpnome = malloc(MAX_GRP_LEN);
	subgrpnome = (gchar*) gtk_entry_get_text(GTK_ENTRY(nome_subgrp_entry));
	
	if(alterando_subgrp==0)
		sprintf(query,"insert into subgrupos(nome,pai) values('%s',%s)",subgrpnome,grpcode);
	else
		sprintf(query,"update subgrupos set nome = '%s', pai = %s  where code = %s",subgrpnome,grpcode,subgrpcode);
		
	if(enviar_query(query)!=0)
	{
		return 1;
	}
	gtk_widget_destroy(janela_grupo);
	gtk_widget_destroy(janela_subgrupo);
	cad_grupo();
	if(alterando_subgrp == 0)
		popup(NULL,"Subgrupo criado com sucesso");
	else
		popup(NULL,"Subgrupo alterado com sucesso");
	alterando_subgrp = 0;
	gtk_widget_grab_focus(cod_subgrp_entry);
	return 0;
}

int exclui_subgrupo()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	gchar *nome;
	char query[MAX_QUERY_LEN];
	subgrpcode = malloc(MAX_CODE_LEN);
	subgrpcode = (gchar*) gtk_entry_get_text(GTK_ENTRY(cod_subgrp_entry));
	if(strlen(subgrpcode)<=0)
	{
		popup(NULL,"Insira um código para o subgrupo");
		gtk_widget_grab_focus(cod_subgrp_entry);
		return 1;
	}
	if(strlen(subgrpcode)>MAX_CODE_LEN)
	{
		popup(NULL,"Código muito grande para o subgrupo");
		gtk_widget_grab_focus(cod_subgrp_entry);
		return 1;
	}
	sprintf(query,"select nome from subgrupos where code = %s",subgrpcode);
	if((res = consultar(query))==NULL)
	{
		return 1;
	}
	if((row = mysql_fetch_row(res))==NULL)
	{
		popup(NULL,"Subgrupo não existente");
		gtk_widget_grab_focus(cod_subgrp_entry);
		return 1;	
	}
	sprintf(query,"delete from subgrupos where code = %s",subgrpcode);
	if(enviar_query(query)!=0)
	{
		return 1;
	}
	gtk_widget_destroy(janela_grupo);
	gtk_widget_destroy(janela_subgrupo);
	cad_grupo();
	popup(NULL,"Subgrupo excluido com sucesso");
	gtk_widget_grab_focus(cod_subgrp_entry);
	return 0;
}

int altera_subgrupo()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	subgrpcode = malloc(MAX_CODE_LEN);
	subgrpcode = (gchar*) gtk_entry_get_text(GTK_ENTRY(cod_subgrp_entry));
	char query[MAX_QUERY_LEN];

	sprintf(query,"select nome from subgrupos where code = %s and pai = %s",subgrpcode,grpcode);
	if((res = consultar(query))==NULL)
	{
		return 1;
	}
	if((row = mysql_fetch_row(res))==NULL)
	{
		popup(NULL,"Subgrupo não existente");
		gtk_widget_grab_focus(cod_subgrp_entry);
		return 1;	
	}
	gtk_entry_set_text(GTK_ENTRY(nome_subgrp_entry),row[0]);
	gtk_widget_grab_focus(confirma_subgrp_button);
	alterando_subgrp = 1;
	return 0;
}

int cancela_subgrupo()
{
	
	return 0;
}


int cad_subgrupo()
{
	GtkWidget *caixa_grande;
	GtkWidget *nome_grp_pai_fixed, *nome_grp_pai_label;
	GtkWidget *cod_subgrp_frame, *cod_subgrp_box, *cod_subgrp_fixed;
	GtkWidget *nome_subgrp_box, *nome_subgrp_fixed, *nome_subgrp_frame;
	GtkWidget *opcoes_box, *opcoes_fixed, *opcoes_frame;
	GtkWidget *psq_subgrp_button, *psq_subgrp_img;
	char query[MAX_QUERY_LEN];
	char label_pai[MAX_GRP_LEN+strlen("Grupo Pai")];
	char code[8];
	MYSQL_RES *res;
	MYSQL_ROW row;
	
	grpcode = malloc(MAX_CODE_LEN);
	janela_subgrupo = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(janela_subgrupo),3);
	gtk_widget_set_size_request(janela_subgrupo,400,250);
	gtk_window_set_keep_above(GTK_WINDOW(janela_subgrupo),TRUE);

	if(GTK_IS_WIDGET(nome_grp_entry))
	{
		grpcode =(gchar*) gtk_entry_get_text(GTK_ENTRY(cod_grp_entry));
		if(strlen(grpcode)>MAX_CODE_LEN)
		{
			popup(NULL,"Código do grupo pai está grande");
			autologger("codigo muito grande");
			autologger(grpcode);
			return 1;
		}
		sprintf(query,"select nome from grupos where code = %s",grpcode);
		if((res = consultar(query))==NULL)
		{
			autologger(query);
			return 1;
		}
		if((row = mysql_fetch_row(res))==NULL)
		{
			popup(NULL,"Grupo Pai não existe");
			autologger("Tentou criar subgrupo para grupo não existente");
			gtk_widget_grab_focus(cod_grp_entry);
			return 1;	
		}
	}
	
	caixa_grande = gtk_box_new(1,0);
	nome_grp_pai_fixed = gtk_fixed_new();
	sprintf(label_pai,"Grupo Pai: %s" ,row[0]);
	nome_grp_pai_label = gtk_label_new(label_pai);
	gtk_fixed_put(GTK_FIXED(nome_grp_pai_fixed),nome_grp_pai_label,50,20);
	
	psq_subgrp_button = gtk_button_new();
	psq_subgrp_img = gtk_image_new_from_file(IMG_PESQ);
	gtk_button_set_image(GTK_BUTTON(psq_subgrp_button),psq_subgrp_img);
	
	cod_subgrp_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(cod_subgrp_entry),"Cód. subgrupo");
	cod_subgrp_frame = gtk_frame_new("Código do Subgrupo");
	cod_subgrp_box = gtk_box_new(0,0);
	cod_subgrp_fixed = gtk_fixed_new();
	cod_subgrp_entry = gtk_entry_new();
	
	gtk_entry_set_width_chars(GTK_ENTRY(cod_subgrp_entry),15);
	
	gtk_box_pack_start(GTK_BOX(cod_subgrp_box),cod_subgrp_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(cod_subgrp_box),psq_subgrp_button,0,0,0);
	gtk_container_add(GTK_CONTAINER(cod_subgrp_frame),cod_subgrp_box);
	gtk_fixed_put(GTK_FIXED(cod_subgrp_fixed),cod_subgrp_frame,30,10);
	
	nome_subgrp_entry = gtk_entry_new();
	nome_subgrp_box = gtk_box_new(0,0);
	nome_subgrp_frame = gtk_frame_new("Nome Subgrupo");
	nome_subgrp_fixed = gtk_fixed_new();
	
	gtk_box_pack_start(GTK_BOX(nome_subgrp_box),nome_subgrp_entry,0,0,0);
	gtk_container_add(GTK_CONTAINER(nome_subgrp_frame),nome_subgrp_box);
	gtk_fixed_put(GTK_FIXED(nome_subgrp_fixed),nome_subgrp_frame,30,10);
	
	opcoes_box = gtk_box_new(0,0);
	opcoes_fixed = gtk_fixed_new();
	opcoes_frame = gtk_frame_new("Opcões");
	
	confirma_subgrp_button = gtk_button_new_with_label("Concluir");
	altera_subgrp_button = gtk_button_new_with_label("Alterar");
	cancela_subgrp_button = gtk_button_new_with_label("Cancelar");
	exclui_subgrp_button = gtk_button_new_with_label("Excluir");
	
	gtk_box_pack_start(GTK_BOX(opcoes_box),confirma_subgrp_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(opcoes_box),altera_subgrp_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(opcoes_box),cancela_subgrp_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(opcoes_box),exclui_subgrp_button,0,0,5);
	gtk_container_add(GTK_CONTAINER(opcoes_frame),opcoes_box);
	gtk_fixed_put(GTK_FIXED(opcoes_fixed),opcoes_frame,30,30);


	gtk_box_pack_start(GTK_BOX(caixa_grande),cod_subgrp_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_grande),nome_grp_pai_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_grande),nome_subgrp_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_grande),opcoes_fixed,0,0,0);
	
	sprintf(code,"%i",tasker("subgrupos"));
	gtk_entry_set_text(GTK_ENTRY(cod_subgrp_entry),code);
	gtk_widget_grab_focus(nome_subgrp_entry);
	
	gtk_container_add(GTK_CONTAINER(janela_subgrupo),caixa_grande);
	
	g_signal_connect(confirma_subgrp_button,"clicked",G_CALLBACK(conclui_subgrupo),NULL);
	g_signal_connect(altera_subgrp_button,"clicked",G_CALLBACK(altera_subgrupo),NULL);
	g_signal_connect(cancela_subgrp_button,"clicked",G_CALLBACK(cancela_subgrupo),NULL);
	g_signal_connect(exclui_subgrp_button,"clicked",G_CALLBACK(exclui_subgrupo),NULL);
	g_signal_connect(psq_subgrp_button,"clicked",G_CALLBACK(pesquisa_subgrp),pesquisa_subgrp);
	gtk_widget_show_all(janela_subgrupo);
	return 0;
}

int conclui_grupo()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	gchar *nome;
	char query[MAX_QUERY_LEN];
	nome = malloc(MAX_GRP_LEN);
	nome = (gchar*) gtk_entry_get_text(GTK_ENTRY(nome_grp_entry));
	if(strlen(nome)<=0)
	{
		popup(NULL,"Insira um nome para o grupo");
		return 1;
	}
	if(strlen(nome)>MAX_GRP_LEN)
	{
		popup(NULL,"Nome muito grande para o grupo");
		return 1;
	}
	
	if(alterando_grp==0)
		sprintf(query,"insert into grupos(nome,pai) values('%s',%s)",nome,grpcode);
	else
		sprintf(query,"update grupos set nome = '%s' where code = %s",nome,grpcode);
		
	if(enviar_query(query)!=0)
	{
		return 1;
	}
	gtk_widget_destroy(janela_grupo);
	cad_grupo();
	gtk_entry_set_text(GTK_ENTRY(cod_grp_entry),grpcode);
	
	popup(NULL,"Grupo criado com sucesso");
	return 0;
}

int exclui_grupo()
{
	
	return 0;
}

int cancela_grupo()
{
	
	return 0;
}

GtkWidget *rec_grupos()
{
	GtkWidget *caixa_grande;
	
	return 0;
}
enum {NUM_COLUMNS=1, COLUMNS=0};
int criar_modelo(GtkTreeStore *modelo)
{
	MYSQL_RES *res_pai, *res_filho;
	MYSQL_ROW row_pai,row_filho;
	GtkTreeIter filhos,pais;
	int code_pai=0;
	char query[MAX_QUERY_LEN];
	sprintf(query,"select code,nome from grupos");
	
	res_pai = consultar(query);
	if(res_pai == NULL)
	{
		popup(NULL,"Erro na query");
		return 1;
	}
	
	while((row_pai = mysql_fetch_row(res_pai))!=NULL)
	{
		g_print("Adicionando grupo %s\n",row_pai[1]);
		gtk_tree_store_append(modelo,&pais,NULL);
		gtk_tree_store_set(modelo,&pais,COLUMNS,row_pai[1],-1);
		sprintf(query,"select nome from subgrupos where pai = %i",atoi(row_pai[0]));
		res_filho = consultar(query);
		if(res_filho == NULL)
		{
			popup(NULL,"Erro na query");
			return 1;
		}
		while((row_filho = mysql_fetch_row(res_filho))!=NULL)
		{
			gtk_tree_store_append(modelo,&filhos,&pais);
			gtk_tree_store_set(modelo,&filhos,COLUMNS,row_filho[0],-1);
		}
	}
	return 0;
}

int cad_grupo()
{
	GtkWidget *visao_geral_grp_scroll, *visao_geral_grp_box, *visao_geral_grp_fixed, *visao_geral_grp_frame;
	GtkWidget *caixa_grande;
	GtkWidget *cod_grupo_frame, *cod_grupo_box, *cod_grupo_fixed;
	GtkWidget *nome_grupo_frame, *nome_grupo_box, *nome_grupo_fixed;
	GtkWidget *add_subgrp_fixed;
	GtkWidget *opcoes_grp_box, *opcoes_grp_frame, *opcoes_grp_fixed;
	GtkWidget *layout_janela_grupo;
	GtkWidget *psq_grp_button, *psq_grp_img;
	GtkWidget *confirma_grp_img, *cancela_grp_img, *exclui_grp_img, *altera_grp_img;
	
	GtkWidget *treeview;
	GtkTreeViewColumn *coluna;
	GtkCellRenderer *celula;
	GtkTreeStore *modelo;
	
	char code[8];

	treeview = gtk_tree_view_new();
	coluna = gtk_tree_view_column_new();
	celula = gtk_cell_renderer_text_new();
	modelo = gtk_tree_store_new(NUM_COLUMNS,G_TYPE_STRING);
	
	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(treeview),TRUE);
	gtk_tree_view_set_show_expanders(GTK_TREE_VIEW(treeview),TRUE);
	gtk_tree_view_column_set_title(coluna,"Grupo de Produtos");
	gtk_tree_view_column_pack_start(coluna,celula,TRUE);
	gtk_tree_view_column_add_attribute(coluna,celula,"text",0);

	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna);

	
	if(criar_modelo(modelo)!=0)
		return 1;
	
	gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),GTK_TREE_MODEL(modelo));
	gtk_widget_set_size_request(treeview,430,210);
	gtk_tree_view_expand_all(GTK_TREE_VIEW(treeview));
	g_object_unref(modelo); 
	
	psq_grp_button = gtk_button_new();
	psq_grp_img = gtk_image_new_from_file(IMG_PESQ);
	gtk_button_set_image(GTK_BUTTON(psq_grp_button),psq_grp_img);	
	
	cod_grupo_frame = gtk_frame_new("Código do Grupo");
	cod_grupo_box = gtk_box_new(0,0);
	cod_grupo_fixed = gtk_fixed_new();
	cod_grp_entry = gtk_entry_new();
	
	gtk_entry_set_width_chars(GTK_ENTRY(cod_grp_entry),10);
	gtk_box_pack_start(GTK_BOX(cod_grupo_box),cod_grp_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(cod_grupo_box),psq_grp_button,0,0,0);
	gtk_container_add(GTK_CONTAINER(cod_grupo_frame),cod_grupo_box);
	gtk_fixed_put(GTK_FIXED(cod_grupo_fixed),cod_grupo_frame,50,20);

	nome_grupo_frame = gtk_frame_new("Nome do Grupo");
	nome_grupo_box = gtk_box_new(0,0);
	nome_grupo_fixed = gtk_fixed_new();
	nome_grp_entry = gtk_entry_new();
	
	gtk_entry_set_width_chars(GTK_ENTRY(nome_grp_entry),20);
	gtk_container_add(GTK_CONTAINER(nome_grupo_frame),nome_grp_entry);
	gtk_box_pack_start(GTK_BOX(nome_grupo_box),nome_grupo_frame,0,0,0);
	gtk_fixed_put(GTK_FIXED(nome_grupo_fixed),nome_grupo_box,50,40);
	
	visao_geral_grp_scroll = gtk_scrolled_window_new(NULL,NULL);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(visao_geral_grp_scroll),GTK_SHADOW_ETCHED_IN);
	visao_geral_grp_box = gtk_box_new(1,0);
	
	visao_geral_grp_fixed = gtk_fixed_new();
	visao_geral_grp_frame = gtk_frame_new("Grupos:");
	gtk_container_set_border_width(GTK_CONTAINER(visao_geral_grp_box),10);
	
	gtk_box_pack_start(GTK_BOX(visao_geral_grp_box),treeview,0,0,0);
	#ifdef __linux__
	gtk_container_add(GTK_CONTAINER(visao_geral_grp_scroll),visao_geral_grp_box);
	#endif
	#ifdef WIN32
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(visao_geral_grp_scroll),visao_geral_grp_box);
	#endif
	
	gtk_widget_set_size_request(visao_geral_grp_scroll,450,225);
	gtk_container_add(GTK_CONTAINER(visao_geral_grp_frame),visao_geral_grp_scroll);
	gtk_fixed_put(GTK_FIXED(visao_geral_grp_fixed),visao_geral_grp_frame,400,20);
	
	add_subgrp_button = gtk_button_new_with_label("Subgrupos");
	add_subgrp_fixed = gtk_fixed_new();
	gtk_fixed_put(GTK_FIXED(add_subgrp_fixed),add_subgrp_button,50,30);
	
	opcoes_grp_box = gtk_box_new(0,0);
	opcoes_grp_frame = gtk_frame_new("Opções");
	opcoes_grp_fixed = gtk_fixed_new();
	
	confirma_grp_img = gtk_image_new_from_file(IMG_OK);
	confirma_grp_button = gtk_button_new_with_label("Confirmar");	
	gtk_button_set_image(GTK_BUTTON(confirma_grp_button),confirma_grp_img);

	altera_grp_img = gtk_image_new_from_file(IMG_ALTER);
	altera_grp_button = gtk_button_new_with_label("Alterar");
	gtk_button_set_image(GTK_BUTTON(altera_grp_button),altera_grp_img);
		
	cancela_grp_img = gtk_image_new_from_file(IMG_CANCEL);
	cancela_grp_button = gtk_button_new_with_label("Cancelar");
	gtk_button_set_image(GTK_BUTTON(cancela_grp_button),cancela_grp_img);
	
	exclui_grp_img = gtk_image_new_from_file(IMG_EXCLUI);
	exclui_grp_button = gtk_button_new_with_label("Excluir");
	gtk_button_set_image(GTK_BUTTON(exclui_grp_button),exclui_grp_img);

	gtk_box_pack_start(GTK_BOX(opcoes_grp_box),confirma_grp_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(opcoes_grp_box),altera_grp_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(opcoes_grp_box),cancela_grp_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(opcoes_grp_box),exclui_grp_button,0,0,5);
	gtk_container_add(GTK_CONTAINER(opcoes_grp_frame),opcoes_grp_box);
	gtk_fixed_put(GTK_FIXED(opcoes_grp_fixed),opcoes_grp_frame,100,350);
	
	layout_janela_grupo = gtk_layout_new(NULL,NULL);
	caixa_grande = gtk_box_new(1,0);
	janela_grupo = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(janela_grupo,900,450);
	gtk_window_set_keep_above(GTK_WINDOW(janela_grupo),TRUE);
	gtk_window_set_position(GTK_WINDOW(janela_grupo),3);
		
	gtk_box_pack_start(GTK_BOX(caixa_grande),cod_grupo_fixed,0,0,0); 
	gtk_box_pack_start(GTK_BOX(caixa_grande),nome_grupo_fixed,0,0,0); 
	gtk_box_pack_start(GTK_BOX(caixa_grande),add_subgrp_fixed,0,0,0); 
	
	gtk_layout_put(GTK_LAYOUT(layout_janela_grupo),caixa_grande,0,0); 
	gtk_layout_put(GTK_LAYOUT(layout_janela_grupo),visao_geral_grp_fixed,0,0); 
	gtk_layout_put(GTK_LAYOUT(layout_janela_grupo),opcoes_grp_fixed,0,0); 
	
	gtk_container_add(GTK_CONTAINER(janela_grupo),layout_janela_grupo);
	
	sprintf(code,"%i",tasker("grupos"));
	
	gtk_entry_set_text(GTK_ENTRY(cod_grp_entry),code);
	
	g_signal_connect(add_subgrp_button,"clicked",G_CALLBACK(cad_subgrupo),NULL);
	g_signal_connect(psq_grp_button,"clicked",G_CALLBACK(pesquisa_grp),cod_grp_entry);
	gtk_widget_show_all(janela_grupo);
	return 0;
}
