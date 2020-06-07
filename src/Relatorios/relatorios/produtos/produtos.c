void relat_prod_fun()
{
	GtkWidget *janela;
	GtkWidget *grid, *caixa;
	
	
	GtkWidget *relat_prod_code_frame, *relat_prod_code_fixed;
	GtkWidget *relat_prod_nome_frame, *relat_prod_nome_fixed;
	GtkWidget *relat_prod_code_box;
	
	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	if(personalizacao.janela_keep_above==1)
		gtk_window_set_keep_above(GTK_WINDOW(janela),TRUE);
	gtk_window_set_position(GTK_WINDOW(janela),3);
	
	relat_prod_code_box = gtk_box_new(0,0);
	psq_relat_prod_code = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(psq_relat_prod_code),gtk_image_new_from_file(IMG_PESQ));
	
	relat_prod_code_entry = gtk_entry_new();
	relat_prod_code_frame = gtk_frame_new("Código");
	relat_prod_code_fixed = gtk_fixed_new();
	gtk_box_pack_start(GTK_BOX(relat_prod_code_box),relat_prod_code_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(relat_prod_code_box),psq_relat_prod_code,0,0,0);
	gtk_container_add(GTK_CONTAINER(relat_prod_code_frame),relat_prod_code_box);
	gtk_fixed_put(GTK_FIXED(relat_prod_code_fixed),relat_prod_code_frame,20,20);
	gtk_entry_set_width_chars(GTK_ENTRY(relat_prod_code_entry),12);
	
	relat_prod_nome_entry = gtk_entry_new();
	relat_prod_nome_frame = gtk_frame_new("Nome");
	relat_prod_nome_fixed = gtk_fixed_new();	
	gtk_container_add(GTK_CONTAINER(relat_prod_nome_frame),relat_prod_nome_entry);
	gtk_fixed_put(GTK_FIXED(relat_prod_nome_fixed),relat_prod_nome_frame,20,20);
	
	grid = gtk_grid_new();
	gtk_grid_attach(GTK_GRID(grid),relat_prod_code_fixed,0,0,1,1);
	gtk_grid_attach(GTK_GRID(grid),relat_prod_nome_fixed,0,1,1,1);
	
	caixa = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(caixa),grid,0,0,0);

	tabelas_bd_id=1;
	g_signal_connect(psq_relat_prod_code,"clicked",G_CALLBACK(psq_prod_relat),relat_prod_code_entry);

	g_signal_connect(relat_prod_code_entry,"activate",G_CALLBACK(relat_prod_codigo_fun),NULL);


	gtk_widget_set_sensitive(relat_prod_nome_entry,FALSE);
	
	gtk_container_add(GTK_CONTAINER(janela),caixa);
	gtk_widget_set_size_request(janela,500,300);
	gtk_widget_show_all(janela);
}
