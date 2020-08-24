#include "altera.c"
#include "exclui.c"
#include "conclui.c"

int  cad_und()
{
	char task[20];
	GtkWidget *janela;
	sprintf(task,"%i",tasker("unidades"));
	GtkWidget *fixed, *fixed2, *fixed3, *fixed4;
	GtkWidget *horizontal_box_one, *horizontal_box_two, *horizontal_box_three, *horizontal_box_four, *vertical_box;
  GtkWidget *medida_und_fixed;
  GtkWidget *separator1,*separator2;
	GtkWidget *code, *name, *sigla, *mult;

	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	if(personalizacao.janela_keep_above==1)
		gtk_window_set_keep_above(GTK_WINDOW(janela), TRUE);
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_icon_name(GTK_WINDOW(janela),"applications-engineering");
	gtk_window_set_title(GTK_WINDOW(janela),"CADASTRO UNIDADES");
	gtk_widget_set_size_request(janela,70,240);

	janelas_gerenciadas.vetor_janelas[REG_CAD_UND].reg_id = REG_CAD_UND;
	janelas_gerenciadas.vetor_janelas[REG_CAD_UND].aberta = 1;
	if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[REG_CAD_UND]))
		return 1;
	janelas_gerenciadas.vetor_janelas[REG_CAD_UND].janela_pointer = janela;

	alterando_und=0;

	psq_cad_und_button = gtk_button_new();
	psq_cad_und_img = gtk_image_new_from_file(IMG_PESQ);
	psq_cad_und_box = gtk_box_new(0,0);
	gtk_button_set_image(GTK_BUTTON(psq_cad_und_button),psq_cad_und_img);

	fixed = gtk_fixed_new();
	fixed2 = gtk_fixed_new();
	fixed3 = gtk_fixed_new();
	fixed4 = gtk_fixed_new();

	horizontal_box_one = gtk_box_new(0,3);
	horizontal_box_two = gtk_box_new(0,3);
	horizontal_box_three = gtk_box_new(0,5);
	horizontal_box_four = gtk_box_new(0,5);

	vertical_box = gtk_box_new(1,0);

	separator1 = gtk_separator_new(0);
	separator2 = gtk_separator_new(0);

	medida_und_combo_box = gtk_combo_box_text_new();
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(medida_und_combo_box),"Tipo"); //0
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(medida_und_combo_box),"Comprimento"); //1
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(medida_und_combo_box),"Massa"); //2
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(medida_und_combo_box),"Tempo"); //3
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(medida_und_combo_box),"Unidade"); //4
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(medida_und_combo_box),"Volume"); //5
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(medida_und_combo_box),"Genérico"); //6
	gtk_combo_box_set_active(GTK_COMBO_BOX(medida_und_combo_box),0);

	code_und_frame = gtk_frame_new("Código");
	name_und_frame = gtk_frame_new("Nome");
	sigla_und_frame = gtk_frame_new("Sigla");
	mult_und_frame = gtk_frame_new("Multiplo");

	code_und_label = gtk_label_new("Codigo: ");
	name_und_label = gtk_label_new("Nome: ");
	sigla_und_label = gtk_label_new("Sigla: ");
	mult_und_label = gtk_label_new("Multiplo");

	code_und_field = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(code_und_field),8);
	name_und_field = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(name_und_field),15);
	sigla_und_field = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(sigla_und_field),5);
	mult_und_field = gtk_spin_button_new_with_range(1,10000,1);
	gtk_entry_set_width_chars(GTK_ENTRY(mult_und_field),8);

	und_concluir_button = gtk_button_new_with_label("Concluir");
	und_alterar_button = gtk_button_new_with_label("Alterar");
	und_excluir_button = gtk_button_new_with_label("Excluir");

	gtk_widget_set_size_request(GTK_WIDGET(und_concluir_button),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(und_alterar_button),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(und_excluir_button),100,50);

	code = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(code),code_und_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(psq_cad_und_box),code_und_field,0,0,0);
	gtk_box_pack_start(GTK_BOX(psq_cad_und_box),psq_cad_und_button,0,0,5);
	gtk_box_pack_start(GTK_BOX(code),psq_cad_und_box,0,0,0);
	gtk_entry_set_text(GTK_ENTRY(code_und_field),task);
	gtk_entry_set_width_chars(GTK_ENTRY(code_und_field),10);
	gtk_widget_set_size_request(code,25,50);

	name = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(name),name_und_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(name),name_und_field,0,0,0);
	gtk_widget_set_size_request(name,250,50);

	sigla = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(sigla),sigla_und_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(sigla),sigla_und_field,0,0,0);
	gtk_widget_set_size_request(sigla,25,50);

	mult = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(mult),mult_und_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(mult),mult_und_field,0,0,0);
	gtk_widget_set_size_request(mult,25,50);

	gtk_box_pack_start(GTK_BOX(horizontal_box_one),code,0,0,0);
	gtk_box_pack_start(GTK_BOX(horizontal_box_two),name,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_two),sigla,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_three),mult,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_three),medida_und_combo_box,0,0,10);

	gtk_box_pack_start(GTK_BOX(horizontal_box_four),und_concluir_button,0,0,0);
	gtk_box_pack_start(GTK_BOX(horizontal_box_four),und_alterar_button,0,0,0);
	//gtk_box_pack_start(GTK_BOX(horizontal_box_four),listar,0,0,0);
	gtk_box_pack_start(GTK_BOX(horizontal_box_four),und_excluir_button,0,0,0);

	g_signal_connect(GTK_WIDGET(code_und_field),"activate",G_CALLBACK(code_und),NULL);
	g_signal_connect(GTK_WIDGET(name_und_field),"activate",G_CALLBACK(name_und),NULL);
	g_signal_connect(GTK_WIDGET(sigla_und_field),"activate",G_CALLBACK(sig_und),NULL);
	g_signal_connect(GTK_WIDGET(mult_und_field),"activate",G_CALLBACK(multiplo_und),NULL);

	g_signal_connect(GTK_WIDGET(und_concluir_button),"clicked",G_CALLBACK(code_und),NULL);
	g_signal_connect(GTK_WIDGET(und_concluir_button),"clicked",G_CALLBACK(name_und),NULL);
	g_signal_connect(GTK_WIDGET(und_concluir_button),"clicked",G_CALLBACK(sig_und),NULL);
	g_signal_connect(GTK_WIDGET(und_concluir_button),"clicked",G_CALLBACK(multiplo_und),NULL);

	g_signal_connect(GTK_WIDGET(und_concluir_button),"clicked",G_CALLBACK(concluido_und),NULL);
	g_signal_connect(GTK_WIDGET(und_excluir_button),"clicked",G_CALLBACK(deleta_und),NULL);
	g_signal_connect(GTK_WIDGET(und_alterar_button),"clicked",G_CALLBACK(altera_und),NULL);

	g_signal_connect(GTK_WIDGET(psq_cad_und_button),"clicked",G_CALLBACK(pesquisa_und),code_und_field);

g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_CAD_UND]);

	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_one,30,5);
	gtk_box_pack_start(GTK_BOX(horizontal_box_one),separator2,0,0,10);

	gtk_fixed_put(GTK_FIXED(fixed2),horizontal_box_two,20,10);
	gtk_fixed_put(GTK_FIXED(fixed3),horizontal_box_three,20,10);
	gtk_fixed_put(GTK_FIXED(fixed4),horizontal_box_four,40,20);

	gtk_box_pack_start(GTK_BOX(vertical_box),fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(vertical_box),separator1,0,0,10);
	gtk_box_pack_start(GTK_BOX(vertical_box),fixed2,0,0,0);
	gtk_box_pack_start(GTK_BOX(vertical_box),fixed3,0,0,30);
	gtk_box_pack_end(GTK_BOX(vertical_box),fixed4,0,0,30);

	gtk_container_add(GTK_CONTAINER(janela),vertical_box);

	gtk_widget_grab_focus (GTK_WIDGET(name_und_field));
	gtk_widget_show_all(janela);

	return 0;
}
