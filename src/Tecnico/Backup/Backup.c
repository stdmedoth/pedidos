#include "init_backup.c"

int backup_fun(){

	GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget *box = gtk_box_new(1,0);
  	GtkWidget *frame = gtk_frame_new("Backup");
	GtkWidget *init_buttom;

	janelas_gerenciadas.vetor_janelas[REG_BACKUP_WND].reg_id = REG_BACKUP_WND;
	janelas_gerenciadas.vetor_janelas[REG_BACKUP_WND].aberta = 1;
	if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[REG_BACKUP_WND]))
		return 1;

	gtk_widget_set_name(janela,"backups");
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"Backups");
	gtk_window_set_icon_name(GTK_WINDOW(janela),"edit-paste");
	gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));
	gtk_container_set_border_width (GTK_CONTAINER (janela), 10);
  	gtk_widget_set_size_request(janela, 300,300);

  	GtkWidget *backup_file_chooser_box = gtk_box_new(0,0);
  	GtkWidget *backup_file_chooser_frame = gtk_frame_new("Escolha o diretório para exportar o seu backup");
  	backup_file_chooser_button = gtk_file_chooser_button_new("Caminho para o Backup", GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
  	backup_file_chooser_entry = gtk_entry_new();
 	gtk_box_pack_start(GTK_BOX(backup_file_chooser_box), backup_file_chooser_button,0,0,5);
 	gtk_box_pack_start(GTK_BOX(backup_file_chooser_box), backup_file_chooser_entry,0,0,5);
	gtk_container_add(GTK_CONTAINER(backup_file_chooser_frame), backup_file_chooser_box);

	GtkWidget *acoes_box = gtk_box_new(0,0);  	
  	init_buttom = gtk_button_new_with_label("Iniciar criação do backup");
  	gtk_box_pack_start(GTK_BOX(acoes_box), init_buttom,0,0,0);

  	GtkWidget *modules_choose_frame = gtk_frame_new("Escolha os módulos para realizar o backup");
  	GtkWidget *modules_choose_box = gtk_box_new(1,0);
	backup_clientes_check = gtk_check_button_new_with_label("Clientes");
	backup_produtos_check = gtk_check_button_new_with_label("Produtos");
	backup_orcamentos_check = gtk_check_button_new_with_label("Orçamentos");
	backup_pedidos_check = gtk_check_button_new_with_label("Pedidos");
	backup_estoques_check = gtk_check_button_new_with_label("Estoques");
	backup_movimentacoes_check = gtk_check_button_new_with_label("Movimentações");
	backup_bancos_check = gtk_check_button_new_with_label("Bancos");
	backup_titulos_rec_check = gtk_check_button_new_with_label("Títulos à Receber");
	backup_baixas_rec_check = gtk_check_button_new_with_label("Baixas à Receber");
	backup_titulos_pag_check = gtk_check_button_new_with_label("Titulos à Pagar");
	backup_baixas_pag_check = gtk_check_button_new_with_label("Baixas à Pagar");

	gtk_box_pack_start(GTK_BOX(modules_choose_box), backup_clientes_check,0,0,5);
	gtk_box_pack_start(GTK_BOX(modules_choose_box), backup_produtos_check,0,0,5);
	gtk_box_pack_start(GTK_BOX(modules_choose_box), backup_orcamentos_check,0,0,5);
	gtk_box_pack_start(GTK_BOX(modules_choose_box), backup_pedidos_check,0,0,5);
	gtk_box_pack_start(GTK_BOX(modules_choose_box), backup_estoques_check,0,0,5);
	gtk_box_pack_start(GTK_BOX(modules_choose_box), backup_movimentacoes_check,0,0,5);
	gtk_box_pack_start(GTK_BOX(modules_choose_box), backup_bancos_check,0,0,5);
	gtk_box_pack_start(GTK_BOX(modules_choose_box), backup_titulos_rec_check,0,0,5);
	gtk_box_pack_start(GTK_BOX(modules_choose_box), backup_baixas_rec_check,0,0,5);
	gtk_box_pack_start(GTK_BOX(modules_choose_box), backup_titulos_pag_check,0,0,5);
	gtk_box_pack_start(GTK_BOX(modules_choose_box), backup_baixas_pag_check,0,0,5);

	gtk_container_add(GTK_CONTAINER(modules_choose_frame), modules_choose_box);

	gtk_box_pack_start(GTK_BOX(box), modules_choose_frame,0,0,5);
	gtk_box_pack_start(GTK_BOX(box), backup_file_chooser_frame,0,0,5);
	gtk_box_pack_start(GTK_BOX(box), acoes_box,0,0,5);
	

	gtk_container_add(GTK_CONTAINER(frame), box);
	gtk_container_add(GTK_CONTAINER(janela), frame);

	janelas_gerenciadas.vetor_janelas[REG_BACKUP_WND].janela_pointer = janela;
	g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_BACKUP_WND]);
	g_signal_connect(init_buttom,"clicked",G_CALLBACK(backup_iniciar_exportacao),NULL);
	g_signal_connect(backup_file_chooser_button,"file-set",G_CALLBACK(get_filename_to_entry),backup_file_chooser_entry);

	FILE *pathcache = fopen(BACKUP_PATH_FILE, "r");
	if(pathcache){
		char path[MAX_PATH_LEN];
		fgets(path,MAX_PATH_LEN,pathcache);
		gtk_entry_set_text(GTK_ENTRY(backup_file_chooser_entry), path);
		fclose(pathcache);
	}

	gtk_widget_show_all(janela);
	return 0;
}