static GtkWidget *oper_nome_entry,*oper_senha_entry,*oper_perm_entry;
static gchar *oper_nome_gchar,*oper_senha_gchar;
static int oper_alterando = 0;
int tmp_oper_code=0;
gint oper_perm_int=0;
static GtkWidget *oper_perm_name_entry;

int oper_passa_nome()
{
	oper_nome_gchar = malloc(sizeof(char)*MAX_OPER_LEN);
	oper_nome_gchar =(gchar*) gtk_entry_get_text(GTK_ENTRY(oper_nome_entry));
	gtk_entry_set_max_length(GTK_ENTRY(oper_nome_entry),sizeof(char)*MAX_OPER_LEN);
	if(strlen(oper_nome_gchar)<=0)
	{
		popup(NULL,"Insira o nome!");
		return 1;
	}
	gtk_widget_grab_focus(oper_senha_entry);
	return 0;
}

int oper_passa_senha()
{
	oper_senha_gchar = malloc(sizeof(char)*MAX_SEN_LEN);
	oper_senha_gchar =(gchar*) gtk_entry_get_text(GTK_ENTRY(oper_senha_entry));
	if(strlen(oper_senha_gchar)<=0)
	{
		popup(NULL,"Insira o senha!");
		return 1;
	}
	gtk_entry_set_max_length(GTK_ENTRY(oper_nome_entry),sizeof(char)*MAX_OPER_LEN);
	gtk_widget_grab_focus(oper_perm_entry);
	return 0;
}
int oper_rec_nivel()
{
	oper_perm_int = gtk_spin_button_get_digits(GTK_SPIN_BUTTON(oper_perm_entry))+1;
	return 0;
}
int oper_alterar()
{
	char *query;
	MYSQL_RES *res;
	MYSQL_ROW row;
	query = malloc(MAX_QUERY_LEN);
	if(oper_passa_nome()!=0)
		return 1;
	sprintf(query,"select * from operadores where nome = '%s'",oper_nome_gchar);
	res = consultar(query);
	if(res==NULL)
	{
		popup(NULL,"Erro com a query\n\tConsulte Suporte");
		g_print("Erro com alteracao de operador");
		return 1;
	}
	row = mysql_fetch_row(res);
	if(row==NULL)
	{
		popup(NULL,"Operador não existente");
		return 1;
	}
	tmp_oper_code = atoi(row[0]);
	gtk_entry_set_text(GTK_ENTRY(oper_nome_entry),row[1]);
	gtk_entry_set_text(GTK_ENTRY(oper_senha_entry),row[2]);
	gtk_spin_button_set_digits(GTK_SPIN_BUTTON(oper_perm_entry),atoi(row[3]));
	oper_alterando = 1;
	return 0;
}

int oper_concluir()
{
	char *query;
	int erro;
	MYSQL_RES *res;
	MYSQL_ROW row;
	g_print("Verificado campo nome\n");
	if(oper_passa_nome()!=0)
		return 1;
	g_print("Verificado campo senha\n");
	if(oper_passa_senha()!=0)
		return 1;
	g_print("Verificado campo nivel\n");
	if(oper_rec_nivel()!=0)
		return 1;
	query = malloc(MAX_QUERY_LEN);
	if(oper_alterando == 0)
	{
		sprintf(query,"select * from operadores where nome = '%s'",oper_nome_gchar);
		res = consultar(query);
		if(res==NULL)
		{
			popup(NULL,"Erro com a query\n\tConsulte Suporte");
			g_print("Erro com alteracao de operador");
			return 1;
		}
		row = mysql_fetch_row(res);
		if(row!=NULL)
		{
			popup(NULL,"Operador já existente");
			return 1;
		}
		sprintf(query,"insert into operadores(nome,senha,nivel) values('%s','%s',%i)",oper_nome_gchar,oper_senha_gchar,oper_perm_int);
	}
	else
	{
		sprintf(query,"update operadores set nome = '%s', senha = '%s',nivel = %i where code = %i",oper_nome_gchar,oper_senha_gchar,oper_perm_int,tmp_oper_code);
	}
	erro = enviar_query(query);
	if(erro!=0)
	{
		popup(NULL,"Consulte Suporte!");
		g_print("Erro na query\n");
		return 1;
	}
	if(oper_alterando == 0)
	{
		sprintf(query,"insert into perfil_desktop (desktop_img, tema, janela_init, janelas_keep_above) values(3,1,1,1)");
		erro = enviar_query(query);	
		if(erro!=0)
		{
			popup(NULL,"Consulte Suporte!");
			g_print("Erro na query\n");
			return 1;
		}
	}
	oper_alterando = 0;
	g_print("Ok! operador criado\n");
	popup(NULL,"Operador Criado");
	return 0;
}

int oper_cancelar()
{


	return 0;
}

int cad_oper()
{
	GtkWidget *janela,*caixa_grande;
	
	GtkWidget *oper_nome_frame, *oper_senha_frame, *oper_perm_frame;	
	GtkWidget *oper_nome_box, *oper_senha_box, *oper_perm_box;
	GtkWidget *oper_nome_fixed, *oper_senha_fixed, *oper_perm_fixed;
	GtkWidget *oper_button_box,*oper_button_fixed;
	GtkWidget *oper_concluir_button, *oper_alterar_button, *oper_excluir_button, *oper_cancelar_button;
		
	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(janela,450,300);	
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_title(GTK_WINDOW(janela),"Operadores");
	gtk_window_set_icon_name(GTK_WINDOW(janela),"applications-development");
			
	oper_perm_name_entry = gtk_label_new(NULL);
	oper_nome_entry = gtk_entry_new();
	oper_senha_entry = gtk_entry_new();
	gtk_entry_set_visibility(GTK_ENTRY(oper_senha_entry),FALSE);
	oper_perm_entry = gtk_spin_button_new_with_range(1,5,1);

	oper_nome_frame = gtk_frame_new("Nome:");
	oper_senha_frame = gtk_frame_new("Senha:");
	oper_perm_frame = gtk_frame_new("Nivel:");
	
	oper_nome_box = gtk_box_new(1,0);
	oper_senha_box = gtk_box_new(1,0);
	oper_perm_box = gtk_box_new(1,0);

	oper_nome_fixed = gtk_fixed_new();
	oper_senha_fixed = gtk_fixed_new();
	oper_perm_fixed = gtk_fixed_new();

	oper_concluir_button = gtk_button_new_with_label("Concluir");
	oper_cancelar_button = gtk_button_new_with_label("Cancelar");
	oper_alterar_button  = gtk_button_new_with_label("Alterar");
	oper_excluir_button  = gtk_button_new_with_label("Deletar");
	
	oper_button_box = gtk_box_new(0,0);
	oper_button_fixed = gtk_fixed_new();

	caixa_grande = gtk_box_new(1,0);
	
	
	gtk_box_pack_start(GTK_BOX(oper_nome_box),oper_nome_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(oper_senha_box),oper_senha_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(oper_perm_box),oper_perm_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(oper_perm_box),oper_perm_name_entry,0,0,0);

	gtk_box_pack_start(GTK_BOX(oper_button_box),oper_concluir_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(oper_button_box),oper_cancelar_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(oper_button_box),oper_alterar_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(oper_button_box),oper_excluir_button,0,0,5);

	gtk_container_add(GTK_CONTAINER(oper_nome_frame),oper_nome_box);
	gtk_container_add(GTK_CONTAINER(oper_senha_frame),oper_senha_box);
	gtk_container_add(GTK_CONTAINER(oper_perm_frame),oper_perm_box);

	gtk_fixed_put(GTK_FIXED(oper_nome_fixed),oper_nome_frame,50,25);
	gtk_fixed_put(GTK_FIXED(oper_senha_fixed),oper_senha_frame,50,0);	
	gtk_fixed_put(GTK_FIXED(oper_perm_fixed),oper_perm_frame,50,0);
	gtk_fixed_put(GTK_FIXED(oper_button_fixed),oper_button_box,50,0);

	gtk_box_pack_start(GTK_BOX(caixa_grande),oper_nome_fixed,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_grande),oper_senha_fixed,0,0,10);
	gtk_box_pack_start(GTK_BOX(caixa_grande),oper_perm_fixed,0,0,10);	
	gtk_box_pack_start(GTK_BOX(caixa_grande),oper_button_fixed,0,0,10);	
	
	g_signal_connect(oper_nome_entry,"activate",G_CALLBACK(oper_passa_nome),NULL);
	g_signal_connect(oper_senha_entry,"activate",G_CALLBACK(oper_passa_senha),NULL);
	g_signal_connect(oper_perm_entry,"change-value",G_CALLBACK(oper_rec_nivel),NULL);
	g_signal_connect(oper_concluir_button,"clicked",G_CALLBACK(oper_concluir),NULL);
	g_signal_connect(oper_alterar_button,"clicked",G_CALLBACK(oper_alterar),NULL);
	g_signal_connect(oper_cancelar_button,"clicked",G_CALLBACK(oper_cancelar),NULL);
	gtk_container_add(GTK_CONTAINER(janela),caixa_grande);
	gtk_widget_show_all(janela);
	return 0;
}
