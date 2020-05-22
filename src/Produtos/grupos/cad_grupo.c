int conclui_subgrupo()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	char mensagem[30];
	int nivel=0;
	concluindo_subgrp=1;
	if(cod_subgrp()!=0)
	{
		gtk_widget_grab_focus(cod_subgrp_entry);
		return 1;
	}
	
	if(nome_subgrp()!=0)
	{
		gtk_widget_grab_focus(nome_subgrp_entry);
		return 1;
	}
	
	if(pai_subgrp()!=0)
	{
		gtk_widget_grab_focus(cod_subgrp_pai_entry);
		return 1;
	}
	
	sprintf(query,"select nivel from grupos where code = %s",subgrp_paicode);
	res = consultar(query);
	if(res==NULL)
	{
		popup(NULL,"Erro ao procurar nivel do grupo pai");
		return 1;
	}
	
	row = mysql_fetch_row(res);
	if(row==NULL)
	{
		popup(NULL,"Erro ao procurar nivel do grupo pai");
		return 1;
	}
	
	nivel = atoi(row[0])+1;
	
	if(alterando_subgrp==0)
	{
		strcpy(mensagem,"Subgrupo criado com sucesso");
		sprintf(query,"insert into grupos(nome,pai,nivel) values('%s',%s,%i)",subgrpnome,subgrp_paicode,nivel);
	}
	else
	{
		strcpy(mensagem,"Subgrupo alterado com sucesso");
		sprintf(query,"update grupos set nome = '%s', pai = %s, nivel = %i where code = %s",subgrpnome,subgrp_paicode,nivel,subgrpcode);
	}
	if(enviar_query(query)!=0)
	{
		return 1;
	}
	cancela_subgrupo();
	gtk_widget_destroy(janela_grupo);
	gtk_widget_destroy(janela_subgrupo);
	cad_grupo();
	popup(NULL,mensagem);

	gtk_widget_grab_focus(cod_subgrp_entry);
	return 0;
}

int cod_subgrp()
{
	subgrpcode = malloc(MAX_CODE_LEN);
	subgrpcode = (gchar*) gtk_entry_get_text(GTK_ENTRY(cod_subgrp_entry));
	if(stoi(subgrpcode)==-1)
	{
		popup(NULL,"O campo deve ser preenchido com um código");
		return 1;
	}
	if(strlen(subgrpcode)>MAX_CODE_LEN)
	{
		popup(NULL,"O código está muito extenso");
		return 1;
	}
	
	return 0;
}

int nome_subgrp()
{
	subgrpnome = malloc(MAX_GRP_LEN);
	subgrpnome = (gchar*) gtk_entry_get_text(GTK_ENTRY(nome_subgrp_entry));
	if(strlen(subgrpnome)>MAX_GRP_LEN)
	{
		popup(NULL,"O nome está muito extenso");
		return 1;
	}
	gtk_widget_grab_focus(cod_subgrp_pai_entry);
	return 0;
}

int pai_subgrp()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *nomepai;
	subgrp_paicode = malloc(MAX_CODE_LEN);
	nomepai = malloc(MAX_GRP_LEN*2);
	subgrp_paicode = (gchar*) gtk_entry_get_text(GTK_ENTRY(cod_subgrp_pai_entry));
	char query[MAX_QUERY_LEN];
	if(stoi(subgrp_paicode)==-1)
	{
		popup(NULL,"O campo deve ser preenchido com um código");
		return 1;
	}
	if(strlen(subgrp_paicode)>MAX_CODE_LEN)
	{
		popup(NULL,"O código está muito extenso");
		return 1;
	}
	sprintf(query,"select a.nome,b.nome from grupos as a inner join grupos as b on a.code = b.pai where b.code = %s",subgrp_paicode);
	res = consultar(query);
	if(res==NULL)
	{
		popup(NULL,"Erro ao procurar nome do grupo pai");
		return 1;
	}
	row = mysql_fetch_row(res);
	if(row==NULL)
	{
		popup(NULL,"Erro ao procurar nome do grupo pai");
		return 1;
	}
	if(strcmp(row[0],"RAIZ"))
		sprintf(nomepai,"%s %s",row[0],row[1]);
	else
		sprintf(nomepai,"%s",row[1]);
	gtk_entry_set_text(GTK_ENTRY(campo_nome_subgrg_pai),nomepai);
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
	sprintf(query,"select nome from grupos where code = %s",subgrpcode);
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
	sprintf(query,"delete from grupos where code = %s",subgrpcode);
	if(enviar_query(query)!=0)
	{
		return 1;
	}
	cancela_subgrupo();
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

	sprintf(query,"select nome,pai from grupos where code = %s",subgrpcode);
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
	gtk_entry_set_text(GTK_ENTRY(cod_subgrp_pai_entry),row[1]);
	gtk_widget_activate(nome_subgrp_entry);
	gtk_widget_activate(cod_subgrp_pai_entry);
	gtk_widget_grab_focus(nome_subgrp_entry);
	alterando_subgrp = 1;
	gtk_widget_set_sensitive(cod_subgrp_entry,FALSE);
	gtk_widget_set_sensitive(psq_subgrpo_button,FALSE);
	return 0;
}

int cancela_subgrupo()
{
	char code[MAX_CODE_LEN];
	sprintf(code,"%i",tasker("grupos"));
	gtk_entry_set_text(GTK_ENTRY(cod_subgrp_entry),code);
	gtk_entry_set_text(GTK_ENTRY(nome_subgrp_entry),"");
	gtk_entry_set_text(GTK_ENTRY(cod_subgrp_pai_entry),"");
	gtk_widget_grab_focus(nome_subgrp_entry);
	alterando_subgrp = 0;
	concluindo_subgrp = 0;
	gtk_widget_set_sensitive(cod_subgrp_entry,TRUE);
	return 0;
}


int cad_subgrupo()
{
	GtkWidget *caixa_grande;
	GtkWidget *nome_subgrp_pai_fixed, *nome_subgrp_pai_frame, *nome_subgrp_pai_box;
	GtkWidget *cod_subgrp_frame, *cod_subgrp_box, *cod_subgrp_fixed;
	GtkWidget *nome_subgrp_box, *nome_subgrp_fixed, *nome_subgrp_frame;
	GtkWidget *opcoes_box, *opcoes_fixed, *opcoes_frame;
	GtkWidget *psq_subgrp_img, *psq_subgrp_box;
	GtkWidget *psq_subgrp_pai_button, *psq_subgrp_pai_img;
	char query[MAX_QUERY_LEN];
	char label_pai[MAX_GRP_LEN+strlen("Grupo Pai")];
	char code[8];
	MYSQL_RES *res;
	MYSQL_ROW row;
	
	subgrpcode = malloc(MAX_CODE_LEN);
	janela_subgrupo = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(janela_subgrupo),3);
	gtk_widget_set_size_request(janela_subgrupo,500,350);
	gtk_window_set_keep_above(GTK_WINDOW(janela_subgrupo),TRUE);
	
	caixa_grande = gtk_box_new(1,0);
	
	campo_nome_subgrg = gtk_entry_new();
	campo_nome_subgrg_pai = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(campo_nome_subgrg_pai),"Nome");
	gtk_widget_set_sensitive(campo_nome_subgrg,FALSE);
	gtk_widget_set_sensitive(campo_nome_subgrg_pai,FALSE);
	
	nome_subgrp_pai_fixed = gtk_fixed_new();
	nome_subgrp_pai_frame = gtk_frame_new("Grupo Pai");
	cod_subgrp_pai_entry = gtk_entry_new();
	
	psq_subgrp_pai_button = gtk_button_new();
	psq_subgrp_pai_img = gtk_image_new_from_file(IMG_PESQ);	
	gtk_button_set_image(GTK_BUTTON(psq_subgrp_pai_button),psq_subgrp_pai_img);
	
	psq_subgrpo_button = gtk_button_new();
	psq_subgrp_img = gtk_image_new_from_file(IMG_PESQ);
	gtk_button_set_image(GTK_BUTTON(psq_subgrpo_button),psq_subgrp_img);
	
	nome_subgrp_pai_box = gtk_box_new(1,0);
	psq_subgrp_box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(psq_subgrp_box),cod_subgrp_pai_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(psq_subgrp_box),psq_subgrp_pai_button,0,0,0);
	gtk_box_pack_start(GTK_BOX(nome_subgrp_pai_box),campo_nome_subgrg_pai,0,0,0);
	gtk_box_pack_start(GTK_BOX(nome_subgrp_pai_box),psq_subgrp_box,0,0,0);
	gtk_container_add(GTK_CONTAINER(nome_subgrp_pai_frame),nome_subgrp_pai_box);
	gtk_fixed_put(GTK_FIXED(nome_subgrp_pai_fixed),nome_subgrp_pai_frame,30,20);
	
	cod_subgrp_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(cod_subgrp_entry),"Cód. subgrupo");
	cod_subgrp_frame = gtk_frame_new("Código do Subgrupo");
	cod_subgrp_box = gtk_box_new(0,0);
	cod_subgrp_fixed = gtk_fixed_new();
	cod_subgrp_entry = gtk_entry_new();
	
	gtk_entry_set_width_chars(GTK_ENTRY(cod_subgrp_entry),15);
	
	gtk_box_pack_start(GTK_BOX(cod_subgrp_box),cod_subgrp_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(cod_subgrp_box),psq_subgrpo_button,0,0,0);
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
	gtk_fixed_put(GTK_FIXED(opcoes_fixed),opcoes_frame,30,10);


	gtk_box_pack_start(GTK_BOX(caixa_grande),cod_subgrp_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_grande),nome_subgrp_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_grande),nome_subgrp_pai_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_grande),opcoes_fixed,0,0,0);
	
	sprintf(code,"%i",tasker("grupos"));
	gtk_entry_set_text(GTK_ENTRY(cod_subgrp_entry),code);
	gtk_widget_grab_focus(nome_subgrp_entry);
	
	gtk_container_add(GTK_CONTAINER(janela_subgrupo),caixa_grande);
	
	g_signal_connect(confirma_subgrp_button,"clicked",G_CALLBACK(conclui_subgrupo),NULL);
	g_signal_connect(altera_subgrp_button,"clicked",G_CALLBACK(altera_subgrupo),NULL);
	g_signal_connect(cancela_subgrp_button,"clicked",G_CALLBACK(cancela_subgrupo),NULL);
	g_signal_connect(exclui_subgrp_button,"clicked",G_CALLBACK(exclui_subgrupo),NULL);
	
	g_signal_connect(cod_subgrp_entry,"activate",G_CALLBACK(cod_subgrp),NULL);
	g_signal_connect(nome_subgrp_entry,"activate",G_CALLBACK(nome_subgrp),NULL);
	g_signal_connect(cod_subgrp_pai_entry,"activate",G_CALLBACK(pai_subgrp),NULL);

	
	g_signal_connect(psq_subgrpo_button,"clicked",G_CALLBACK(pesquisa_subgrp),cod_subgrp_entry);
	g_signal_connect(psq_subgrp_pai_button,"clicked",G_CALLBACK(pesquisa_subgrp),cod_subgrp_pai_entry);
	gtk_widget_show_all(janela_subgrupo);
	return 0;
}

int cod_grp()
{
	grpcode = malloc(MAX_CODE_LEN);
	grpcode = (gchar*) gtk_entry_get_text(GTK_ENTRY(cod_grp_entry));
	if(stoi(grpcode)==-1)
	{
		popup(NULL,"O campo deve ser preenchido com um código");
		gtk_widget_grab_focus(nome_grp_entry);
		return 1;
	}
	if(strlen(grpcode)>MAX_CODE_LEN)
	{
		popup(NULL,"O código está muito extenso");
		gtk_widget_grab_focus(nome_grp_entry);
		return 1;
	}

	if(alterando_grp==0&&concluindo_grp==0)
	{
		altera_grupo();
	}
	return 0;	
}

int nome_grp()
{
	grpnome = malloc(MAX_GRP_LEN);
	grpnome = (gchar*) gtk_entry_get_text(GTK_ENTRY(nome_grp_entry));
	if(strlen(grpnome)<=0)
	{
		popup(NULL,"Insira um nome para o grupo");
		gtk_widget_grab_focus(nome_grp_entry);
		return 1;
	}
	if(strlen(grpnome)>MAX_GRP_LEN)
	{
		popup(NULL,"Nome muito grande para o grupo");
		gtk_widget_grab_focus(nome_grp_entry);
		return 1;
	}	
	return 0;
}
int altera_grupo()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	grpcode = malloc(MAX_CODE_LEN);
	grpcode = (gchar*) gtk_entry_get_text(GTK_ENTRY(cod_grp_entry));
	char query[MAX_QUERY_LEN];
	
	sprintf(query,"select nome from grupos where code = %s",grpcode);
	if((res = consultar(query))==NULL)
	{
		return 1;
	}
	if((row = mysql_fetch_row(res))==NULL)
	{
		popup(NULL,"Grupo não existente");
		gtk_widget_grab_focus(cod_grp_entry);
		return 1;	
	}
	gtk_entry_set_text(GTK_ENTRY(nome_grp_entry),row[0]);
	gtk_widget_grab_focus(confirma_grp_button);
	gtk_widget_set_sensitive(cod_grp_entry,FALSE);
	gtk_widget_set_sensitive(psq_grp_button,FALSE);
	alterando_grp = 1;
	return 0;
}

int conclui_grupo()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	gchar *nome;
	concluindo_grp=1;
	char query[MAX_QUERY_LEN];
	char mensagem[30];
	if(cod_grp()!=0)
		return 1;
	if(nome_grp()!=0)
		return 1;
	
	if(alterando_grp==0)
	{
		strcpy(mensagem,"Grupo criado com sucesso");
		sprintf(query,"insert into grupos(nome,pai,nivel) values('%s',1,1)",grpnome);
	}
	else
	{
		strcpy(mensagem,"Grupo alterado com sucesso");
		sprintf(query,"update grupos set nome = '%s' where code = %s",grpnome,grpcode);
	}	
	if(enviar_query(query)!=0)
	{
		return 1;
	}
	cancela_grupo();
	gtk_widget_destroy(janela_grupo);
	cad_grupo();
	
	popup(NULL,mensagem);
	
	return 0;
}

int exclui_grupo()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	
	if(strlen(grpcode)<=0)
	{
		popup(NULL,"Insira um código para o grupo");
		return 1;
	}
	if(strlen(grpcode)>MAX_GRP_LEN)
	{
		popup(NULL,"Código muito grande para o grupo");
		return 1;
	}
	
	//deleta o grupo e os filhos do grupo
	sprintf(query,"delete from grupos where code = %s and pai = %s",grpcode,grpcode);
		
	if(enviar_query(query)!=0)
	{
		popup(NULL,"Não foi possivel excluir grupo");
		return 1;
	}
	
	gtk_widget_destroy(janela_grupo);
	cancela_grupo();
	cad_grupo();
	
	popup(NULL,"Grupo excluído com sucesso");	
	return 0;
}

int cancela_grupo()
{
	char code[MAX_CODE_LEN];
	sprintf(code,"%i",tasker("grupos"));
	gtk_entry_set_text(GTK_ENTRY(cod_grp_entry),code);
	gtk_entry_set_text(GTK_ENTRY(nome_grp_entry),"");
	gtk_widget_grab_focus(nome_grp_entry);
	alterando_grp = 0;
	concluindo_grp = 0;
	gtk_widget_set_sensitive(cod_grp_entry,TRUE);
	return 0;
}

GtkWidget *rec_grupos()
{
	GtkWidget *caixa_grande;
	
	return 0;
}
enum {N_COLUMNS=3,COLUMN0=0, COLUMN1=1, COLUMN2=2};
int criar_modelo(GtkTreeStore *modelo)
{
	
	//GtkWidget *scrollwindow;
	//GtkTreeViewColumn *coluna1, *coluna2, *coluna3;
	//GtkCellRenderer *celula1, *celula2, *celula3;
	//GtkWidget *treeview;
	GtkTreeIter colunas, campos;
	GtkTreeIter filhos[6];
	//GtkWidget *pesquisa_entry;
	//GtkWidget *caixa_grande;
	
	//GtkWidget *escolher_campo_button, *escolher_campo_img, *escolher_campo_fixed;
	
	MYSQL_RES *res[6];
	MYSQL_ROW row[6];

	char query[MAX_QUERY_LEN];
	sprintf(query,"select b.code, b.nome, a.nome from grupos as a inner join grupos as b on a.code = b.pai where b.code > 0 and b.pai = 1");
	res[ROW_0] = consultar(query);
	if(res[ROW_0] == NULL)
	{
		return 1;
	}
	//RAIZ
	while((row[ROW_0] = mysql_fetch_row(res[ROW_0]))!=NULL)
	{
		if(atoi(row[ROW_0][0])!=1)
		{
			gtk_tree_store_append(modelo,&campos,NULL);
			g_print("Inserindo codigo: %s nome: %s\n",row[ROW_0][0],row[ROW_0][1]);
			gtk_tree_store_set(modelo,&campos, COLUMN0,row[ROW_0][0], COLUMN1,row[ROW_0][1],COLUMN2,row[ROW_0][2],-1);
			sprintf(query,"select b.code, b.nome, a.nome from grupos as a inner join grupos as b on a.code = b.pai where b.pai = %s",row[ROW_0][0]);
			res[ROW_1] = consultar(query);
			if(res[ROW_1] == NULL)
			{
				return 1;
			}
			//camada 2
			while((row[ROW_1] = mysql_fetch_row(res[ROW_1]))!=NULL)
			{
				gtk_tree_store_append(modelo,&filhos[ROW_1],&campos);
				g_print("Inserindo codigo: %s nome: %s\n",row[ROW_1][0],row[ROW_1][1]);
				gtk_tree_store_set(modelo,&filhos[ROW_1], COLUMN0,row[ROW_1][0], COLUMN1,row[ROW_1][1],COLUMN2,row[ROW_1][2],-1);
				sprintf(query,"select b.code, b.nome, a.nome from grupos as a inner join grupos as b on a.code = b.pai where b.pai = %s",row[ROW_1][0]);
				res[ROW_2] = consultar(query);					
				if(res[ROW_2] == NULL)	
				{
					return 1;
				}
				//camada 3
				while((row[ROW_2] = mysql_fetch_row(res[ROW_2]))!=NULL)
				{
					gtk_tree_store_append(modelo,&filhos[ROW_2],&filhos[ROW_1]);
					g_print("Inserindo codigo: %s nome: %s\n",row[ROW_2][0],row[ROW_2][1]);
					gtk_tree_store_set(modelo,&filhos[ROW_2], COLUMN0,row[ROW_2][0], COLUMN1,row[ROW_2][1],COLUMN2,row[ROW_2][2],-1);
					sprintf(query,"select b.code, b.nome, a.nome from grupos as a inner join grupos as b on a.code = b.pai where b.pai = %s",row[ROW_2][0]);
					res[ROW_3] = consultar(query);
					if(res[ROW_3] == NULL)
					{
						return 1;
					}
					//camada 4
					while((row[ROW_3] = mysql_fetch_row(res[ROW_3]))!=NULL)
					{
						gtk_tree_store_append(modelo,&filhos[ROW_3],&filhos[ROW_2]);
						g_print("Inserindo codigo: %s nome: %s\n",row[ROW_3][0],row[ROW_3][1]);
						gtk_tree_store_set(modelo,&filhos[ROW_3], COLUMN0,row[ROW_3][0], COLUMN1,row[ROW_3][1],COLUMN2,row[ROW_3][2],-1);
						sprintf(query,"select b.code, b.nome, a.nome from grupos as a inner join grupos as b on a.code = b.pai where b.pai = %s",row[ROW_3][0]);
						res[ROW_4] = consultar(query);
						if(res[ROW_4] == NULL)
						{
							return 1;
						}
						//camada 5
						while((row[ROW_4] = mysql_fetch_row(res[ROW_4]))!=NULL)
						{
							gtk_tree_store_append(modelo,&filhos[ROW_4],&filhos[ROW_3]);
							g_print("Inserindo codigo: %s nome: %s\n",row[ROW_4][0],row[ROW_4][1]);
							gtk_tree_store_set(modelo,&filhos[ROW_4], COLUMN0,row[ROW_4][0], COLUMN1,row[ROW_4][1],COLUMN2,row[ROW_4][2],-1);
							sprintf(query,"select b.code, b.nome, a.nome from grupos as a inner join grupos as b on a.code = b.pai where b.pai = %s",row[ROW_4][0]);
							res[ROW_5] = consultar(query);
							if(res[ROW_5] == NULL)
							{
								return 1;
							}
							while((row[ROW_5] = mysql_fetch_row(res[ROW_5]))!=NULL)
							{
								gtk_tree_store_append(modelo,&filhos[ROW_5],&filhos[ROW_4]);
								g_print("Inserindo codigo: %s nome: %s\n",row[ROW_5][0],row[ROW_5][1]);
								gtk_tree_store_set(modelo,&filhos[ROW_5], COLUMN0,row[ROW_5][0], COLUMN1,row[ROW_5][1],COLUMN2,row[ROW_5][2],-1);
							}
						}
					}
				}
			}
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
	GtkWidget *psq_grp_img;
	GtkWidget *confirma_grp_img, *cancela_grp_img, *exclui_grp_img, *altera_grp_img;
	
	GtkWidget *treeview;
	GtkTreeViewColumn *coluna1, *coluna2, *coluna3;
	GtkCellRenderer *celula1, *celula2, *celula3;
	GtkTreeStore *modelo;
	
	char code[8];

	treeview = gtk_tree_view_new();
	coluna1 = gtk_tree_view_column_new();
	coluna2 = gtk_tree_view_column_new();
	coluna3 = gtk_tree_view_column_new();
	celula1 = gtk_cell_renderer_text_new();
	celula2 = gtk_cell_renderer_text_new();
	celula3 = gtk_cell_renderer_text_new();
	modelo = gtk_tree_store_new(N_COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	
	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(treeview),TRUE);
	//gtk_tree_view_set_show_expanders(GTK_TREE_VIEW(treeview),TRUE);
	gtk_tree_view_column_set_title(coluna1,"Código");
	gtk_tree_view_column_pack_start(coluna1,celula1,TRUE);
	gtk_tree_view_column_add_attribute(coluna1,celula1,"text",0);

	gtk_tree_view_column_set_title(coluna2,"Nome");
	gtk_tree_view_column_pack_start(coluna2,celula2,TRUE);
	gtk_tree_view_column_add_attribute(coluna2,celula2,"text",1);
	
	gtk_tree_view_column_set_title(coluna3,"Pai");
	gtk_tree_view_column_pack_start(coluna3,celula3,TRUE);
	gtk_tree_view_column_add_attribute(coluna3,celula3,"text",2);

	gtk_tree_view_set_enable_tree_lines(GTK_TREE_VIEW(treeview),TRUE);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna1);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna2);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna3	);
	gtk_tree_view_set_level_indentation(GTK_TREE_VIEW(treeview),20);
	
	if(criar_modelo(modelo)!=0)
		return 1;

	gtk_tree_view_column_set_visible(coluna1,FALSE);
	gtk_tree_view_column_set_visible(coluna3,FALSE);
	
	gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),GTK_TREE_MODEL(modelo));
	gtk_widget_set_size_request(treeview,430,210);
	//gtk_tree_view_expand_all(GTK_TREE_VIEW(treeview));
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
	gtk_window_set_icon_name(GTK_WINDOW(janela_grupo),"emblem-documents");
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
	
	g_signal_connect(cod_grp_entry,"activate",G_CALLBACK(cod_grp),NULL);
	g_signal_connect(confirma_grp_button,"clicked",G_CALLBACK(conclui_grupo),NULL);
	g_signal_connect(altera_grp_button,"clicked",G_CALLBACK(altera_grupo),NULL);
	g_signal_connect(cancela_grp_button,"clicked",G_CALLBACK(cancela_grupo),NULL);
	g_signal_connect(exclui_grp_button,"clicked",G_CALLBACK(exclui_grupo),NULL);
	
	gtk_widget_show_all(janela_grupo);
	return 0;
}
