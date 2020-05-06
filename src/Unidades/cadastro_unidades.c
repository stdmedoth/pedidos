#include "altera.c"
#include "exclui.c"
#include "conclui.c"

int  cad_und()
{
	char task[20];
	GtkWidget *janela;
	sprintf(task,"%i",tasker("unidades"));
	GtkWidget *fixed, *fixed2, *fixed3;
	GtkWidget *horizontal_box_one, *horizontal_box_two, *horizontal_box_three, *vertical_box;
    GtkWidget *separator1,*separator2;
	GtkWidget *code, *name, *sigla, *mult;
	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_keep_above(GTK_WINDOW(janela), TRUE);
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_title(GTK_WINDOW(janela),"CADASTRO UNIDADES");
	gtk_widget_set_size_request(janela,70,240);
	alterando_und=0;
	fixed = gtk_fixed_new();
	fixed2 = gtk_fixed_new();
	fixed3 = gtk_fixed_new();
	
	horizontal_box_one = gtk_box_new(0,3);
	horizontal_box_two = gtk_box_new(0,3);
	horizontal_box_three = gtk_box_new(0,5);

	vertical_box = gtk_box_new(1,0);

	separator1 = gtk_separator_new(0);
	separator2 = gtk_separator_new(0);
	
	code_und_label = gtk_label_new("Codigo: ");
	name_und_label = gtk_label_new("Nome: ");
	sigla_und_label = gtk_label_new("Sigla Unidade: ");
	mult_und_label = gtk_label_new("Multiplo Unidade");
	
	code_und_field = gtk_entry_new();
	name_und_field = gtk_entry_new();
	sigla_und_field = gtk_entry_new();
	mult_und_field = gtk_entry_new();

	concluir = gtk_button_new_with_label("Concluir");
	alterar = gtk_button_new_with_label("Alterar");
	listar = gtk_button_new_with_label("Listar");
	excluir = gtk_button_new_with_label("Excluir");

	gtk_widget_set_size_request(GTK_WIDGET(concluir),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(alterar),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(listar),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(excluir),100,50);

	code = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(code),code_und_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(code),code_und_field,0,0,0);
	gtk_entry_set_text(GTK_ENTRY(code_und_field),task);
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
	gtk_box_pack_start(GTK_BOX(horizontal_box_one),name,0,0,0);
	gtk_box_pack_start(GTK_BOX(horizontal_box_one),sigla,0,0,0);
	gtk_box_pack_start(GTK_BOX(horizontal_box_one),mult,0,0,0);
	
	gtk_box_pack_start(GTK_BOX(horizontal_box_two),concluir,0,0,0);
	gtk_box_pack_start(GTK_BOX(horizontal_box_two),alterar,0,0,0);
	gtk_box_pack_start(GTK_BOX(horizontal_box_two),listar,0,0,0);
	gtk_box_pack_start(GTK_BOX(horizontal_box_two),excluir,0,0,0);

	g_signal_connect(GTK_WIDGET(code_und_field),"activate",G_CALLBACK(code_und),NULL);
	g_signal_connect(GTK_WIDGET(name_und_field),"activate",G_CALLBACK(name_und),NULL);
	g_signal_connect(GTK_WIDGET(sigla_und_field),"activate",G_CALLBACK(sig_und),NULL);
	g_signal_connect(GTK_WIDGET(mult_und_field),"activate",G_CALLBACK(multiplo_und),NULL);

	g_signal_connect(GTK_WIDGET(concluir),"clicked",G_CALLBACK(code_und),NULL);
	g_signal_connect(GTK_WIDGET(concluir),"clicked",G_CALLBACK(name_und),NULL);
	g_signal_connect(GTK_WIDGET(concluir),"clicked",G_CALLBACK(sig_und),NULL);
	g_signal_connect(GTK_WIDGET(concluir),"clicked",G_CALLBACK(multiplo_und),NULL);
	
	g_signal_connect(GTK_WIDGET(concluir),"clicked",G_CALLBACK(concluido_und),NULL);
	g_signal_connect(GTK_WIDGET(listar),"clicked",G_CALLBACK(pesquisa_und),code_und_field);
	g_signal_connect(GTK_WIDGET(excluir),"clicked",G_CALLBACK(deleta_und),NULL);
	g_signal_connect(GTK_WIDGET(alterar),"clicked",G_CALLBACK(altera_und),NULL);
	
	g_signal_connect(GTK_WIDGET(janela),"destroy",G_CALLBACK(close_window_callback),janela);
	
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_one,30,5);
	gtk_fixed_put(GTK_FIXED(fixed2),horizontal_box_two,30,10);
	gtk_fixed_put(GTK_FIXED(fixed3),horizontal_box_three,100,100);

	gtk_box_pack_start(GTK_BOX(vertical_box),fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(vertical_box),separator1,0,0,10);
	gtk_box_pack_start(GTK_BOX(vertical_box),fixed2,0,0,0);
	gtk_box_pack_start(GTK_BOX(horizontal_box_one),separator2,0,0,10);
	gtk_box_pack_end(GTK_BOX(vertical_box),fixed3,0,0,30);

	gtk_container_add(GTK_CONTAINER(janela),vertical_box);

	gtk_widget_grab_focus (GTK_WIDGET(name_und_field));
	gtk_widget_show_all(janela);

	return 0;
}
