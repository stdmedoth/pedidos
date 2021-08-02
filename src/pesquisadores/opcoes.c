void pesquisador_opcoes_selected(GtkEntryCompletion *widget, GtkTreeModel *model, GtkTreeIter *iter, gpointer user_data){
	GValue value=G_VALUE_INIT;
	gtk_tree_model_get_value(model, iter, 2, &value);
	if(G_VALUE_TYPE(&value) == G_TYPE_INT){
		int identificacao = g_value_get_int(&value);
		janelas_gerenciadas.vetor_janelas[identificacao].fun();
		if(controle_menu){
			chama_menu(pesquisador_opcoes_wnd);
		}
		pesquisador_opcoes_caller();
	}

}

void pesquisador_opcoes_caller(){
	if(!pesquisador_opcoes_opened){
		gtk_widget_show_all(pesquisador_opcoes_wnd);
		pesquisador_opcoes_opened = 1;
	}else{
		gtk_widget_hide(pesquisador_opcoes_wnd);
		pesquisador_opcoes_opened = 0;
	}
}

int pesquisador_opcoes_create(){
	int N_COLUMNS=3;

	pesquisador_opcoes_wnd = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(pesquisador_opcoes_wnd),3);
  gtk_window_set_modal(GTK_WINDOW(pesquisador_opcoes_wnd),TRUE);
  gtk_window_set_resizable(GTK_WINDOW(pesquisador_opcoes_wnd),FALSE);
  gtk_window_set_decorated(GTK_WINDOW(pesquisador_opcoes_wnd),FALSE);
  //gtk_window_set_transient_for(GTK_WINDOW(pesquisador_opcoes_wnd),GTK_WINDOW(janela_principal));
	gtk_window_set_keep_above(GTK_WINDOW(pesquisador_opcoes_wnd),TRUE);
  gtk_window_set_title(GTK_WINDOW(pesquisador_opcoes_wnd),"Pesquisador de Opções");
  gtk_window_set_icon_name(GTK_WINDOW(pesquisador_opcoes_wnd),"text-x-generic");

	GtkWidget *box = gtk_box_new(0,0);
	GtkWidget *fixed = gtk_fixed_new();
	GtkWidget *frame = gtk_frame_new("Pesquisar opções");

	pesquisador_opcoes_model = gtk_tree_store_new(N_COLUMNS,G_TYPE_STRING,GDK_TYPE_PIXBUF,G_TYPE_INT);

	//gtk_tree_model_foreach copia os tree_model do menu para um model pesquisador_opcoes_model
	if(ativar.cadastro)
		gtk_tree_model_foreach(GTK_TREE_MODEL(cad_icos_model), gtk_tree_model_append_from_model, pesquisador_opcoes_model);

	if(ativar.compras)
		gtk_tree_model_foreach(GTK_TREE_MODEL(cmp_icos_model), gtk_tree_model_append_from_model, pesquisador_opcoes_model);

	if(ativar.faturamento)
		gtk_tree_model_foreach(GTK_TREE_MODEL(vnd_icos_model), gtk_tree_model_append_from_model, pesquisador_opcoes_model);

	if(ativar.estoque)
		gtk_tree_model_foreach(GTK_TREE_MODEL(est_icos_model), gtk_tree_model_append_from_model, pesquisador_opcoes_model);

	if(ativar.financeiro)
		gtk_tree_model_foreach(GTK_TREE_MODEL(fin_icos_model), gtk_tree_model_append_from_model, pesquisador_opcoes_model);

	if(ativar.marketing)
		gtk_tree_model_foreach(GTK_TREE_MODEL(fin_icos_model), gtk_tree_model_append_from_model, pesquisador_opcoes_model);

	if(ativar.relatorios)
		gtk_tree_model_foreach(GTK_TREE_MODEL(rel_icos_model), gtk_tree_model_append_from_model, pesquisador_opcoes_model);

	if(ativar.tecnicos)
		gtk_tree_model_foreach(GTK_TREE_MODEL(tcn_icos_model), gtk_tree_model_append_from_model, pesquisador_opcoes_model);

	GtkEntryCompletion *completion = gtk_entry_completion_new();
	GtkWidget *search_frame = gtk_frame_new("Insira a opção desejada");
	GtkWidget *search_entry = gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(search_frame), search_entry);

	gtk_entry_completion_set_model(GTK_ENTRY_COMPLETION(completion), GTK_TREE_MODEL(pesquisador_opcoes_model));
	//gtk_entry_completion_set_inline_completion(GTK_ENTRY_COMPLETION(completion),TRUE);
	//gtk_entry_completion_set_popup_single_match(GTK_ENTRY_COMPLETION(completion),FALSE);
	//gtk_entry_completion_set_inline_selection(GTK_ENTRY_COMPLETION(completion),TRUE);
	//gtk_entry_completion_set_popup_completion(GTK_ENTRY_COMPLETION(completion),FALSE);
	gtk_entry_completion_set_text_column(GTK_ENTRY_COMPLETION(completion), 0);
	gtk_entry_set_completion(GTK_ENTRY(search_entry), completion);

	gtk_box_pack_start(GTK_BOX(box), search_frame,5,5,5);
	gtk_container_add(GTK_CONTAINER(frame), box);
	gtk_container_add(GTK_CONTAINER(pesquisador_opcoes_wnd), frame);

	g_signal_connect(completion, "match-selected", G_CALLBACK(pesquisador_opcoes_selected), NULL);

	return 0;
}
int pesquisador_opcoes_update(){

	return 0;
}
int pesquisador_opcoes_clicked(){

	return 0;
}
