int cad_fatores()
{
	//Labels
	GtkWidget *codigo_label,*nome_label,*observacao_label;

	//Entrys
	GtkWidget *codigo_entry,*nome_entry,*observacao_entry;
	
	//Boxs
	GtkWidget *codigo_box,*nome_box,*observacao_box;

	//Fixeds
	GtkWidget *codigo_fixed,*nome_fixed,*observacao_fixed;
	
	//Buttons
	GtkWidget *confirma,*exclui,*pesquisa,*cancela;
	
	//Container
	GtkWidget *caixona,*opcoes;
	
	//Images
	GtkWidget *imagem_confirma,*imagem_exclui,*imagem_pesquisa,*imagem_cancela;
	
	GtkWidget *janela;
	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(janela),"Cadastro de Fatores");
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_widget_set_size_request(GTK_WIDGET(janela),300,300);
	
	imagem_confirma = gtk_image_new_from_file(IMG_OK);
	imagem_exclui = gtk_image_new_from_file(IMG_EXCLUI);
	imagem_pesquisa = gtk_image_new_from_file(IMG_PESQ);
	imagem_cancela = gtk_image_new_from_file(IMG_CANCEL);
	
	
	codigo_label = gtk_label_new("Código:");
	nome_label   = gtk_label_new("Nome:");
	observacao_label = gtk_label_new("Observações");
	
	codigo_entry = gtk_entry_new();
	nome_entry = gtk_entry_new();
	observacao_entry = gtk_text_view_new();
	gtk_widget_set_size_request(observacao_entry,160,100);
	
	codigo_box = gtk_box_new(1,0);
	nome_box = gtk_box_new(1,0);
	observacao_box = gtk_box_new(1,0);
	
	codigo_fixed = gtk_fixed_new();
	nome_fixed = gtk_fixed_new();
	observacao_fixed = gtk_fixed_new();
	
	opcoes = gtk_box_new(0,0);
	confirma = gtk_button_new_with_label("Confirmar");
	exclui = gtk_button_new_with_label("Excluir");
	pesquisa = gtk_button_new_with_label("Pesquisar");
	cancela = gtk_button_new_with_label("Cancelar");

	caixona = gtk_box_new(1,0);
	
	gtk_box_pack_start(GTK_BOX(codigo_box),codigo_label,0,0,0);
	gtk_entry_set_width_chars(GTK_ENTRY(codigo_entry),10);
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(codigo_entry),GTK_ENTRY_ICON_PRIMARY,"emblem-system");
	gtk_entry_set_placeholder_text(GTK_ENTRY(codigo_entry),"Código");
	gtk_box_pack_start(GTK_BOX(codigo_box),codigo_entry,0,0,0);
	
	gtk_box_pack_start(GTK_BOX(nome_box),nome_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(nome_box),nome_entry,0,0,0);
	
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(nome_entry),GTK_ENTRY_ICON_PRIMARY,"format-text-bold");
	gtk_entry_set_placeholder_text(GTK_ENTRY(nome_entry),"Fator");
	
	gtk_box_pack_start(GTK_BOX(observacao_box),observacao_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(observacao_box),observacao_entry,0,0,0);
	
	gtk_fixed_put(GTK_FIXED(codigo_fixed),codigo_box,145,15);
	gtk_fixed_put(GTK_FIXED(nome_fixed),nome_box,120,15);
	gtk_fixed_put(GTK_FIXED(observacao_fixed),observacao_box,120,15);
	
	gtk_box_pack_start(GTK_BOX(opcoes),confirma,0,0,5);
	gtk_button_set_image(GTK_BUTTON(confirma),imagem_confirma);
	gtk_box_pack_start(GTK_BOX(opcoes),exclui,0,0,5);
	gtk_button_set_image(GTK_BUTTON(exclui),imagem_exclui);
	gtk_box_pack_start(GTK_BOX(opcoes),pesquisa,0,0,5);
	gtk_button_set_image(GTK_BUTTON(pesquisa),imagem_pesquisa);
	gtk_box_pack_start(GTK_BOX(opcoes),cancela,0,0,5);
	gtk_button_set_image(GTK_BUTTON(cancela),imagem_cancela);

	gtk_box_pack_start(GTK_BOX(caixona),codigo_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixona),nome_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixona),observacao_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixona),opcoes,0,0,30);

	gtk_container_add(GTK_CONTAINER(janela),caixona);
	
	gtk_widget_show_all(janela);
	return 0;
}

void adicionar_fator()
{
	
	
}
void remover_fator()
{
	
	
}
void listar_fatores()
{
	
}
