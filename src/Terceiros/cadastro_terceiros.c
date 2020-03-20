GtkWidget *concluir, *alterar, *listar, *excluir;
#include "campos.c"
#include "altera.c"
#include "exclui.c"
#include "lista.c"
#include "conclui.c"

int  cad_terc()
{
	char task[20];
	sprintf(task,"%i",tasker("terceiros"));
	g_print("task %s\n",task);	
	GtkWidget *code_label, *name_label, *address_label, *type_label;
	GtkWidget *fixed, *fixed2, *horizontal_box_one, *horizontal_box_two, *vertical_box, *separator;
	GtkWidget *code, *name, *address, *type;
	
	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"CADASTRO TERCEIROS");
	gtk_window_set_keep_above(GTK_WINDOW(janela), TRUE);
	gtk_container_set_border_width (GTK_CONTAINER (janela), 10);
	g_signal_connect(GTK_WINDOW(janela),"delete-event",G_CALLBACK(gtk_widget_destroy),&janela);
	gtk_widget_set_size_request(janela,750,200);
	
	fixed = gtk_fixed_new();
	fixed2 = gtk_fixed_new();
	
	horizontal_box_one = gtk_box_new(0,3);
	horizontal_box_two = gtk_box_new(0,5);
	
	vertical_box = gtk_box_new(1,0);
	separator = gtk_separator_new(0);
	
	code_label = gtk_label_new("Codigo: ");
	name_label = gtk_label_new("Nome: ");
	address_label= gtk_label_new("Endereco: ");
	type_label = gtk_label_new("Tipo Terceiro: ");
	
	concluir = gtk_button_new_with_label("Concluir");
	alterar = gtk_button_new_with_label("Alterar");
	listar = gtk_button_new_with_label("Listar");
	excluir = gtk_button_new_with_label("Excluir");
	
	code_ter_field = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(code_ter_field),task);
	code = gtk_box_new(1,0);
	name_ter_field = gtk_entry_new();
	address_ter_field = gtk_entry_new();
	type_ter_field = gtk_entry_new();
	
	gtk_box_pack_start(GTK_BOX(code),code_label,0,0,0);
	gtk_box_pack_end(GTK_BOX(code),code_ter_field,0,0,0);
	gtk_widget_set_size_request(code,50,50);
	
	name = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(name),name_label,0,0,0);
	gtk_box_pack_end(GTK_BOX(name),name_ter_field,0,0,0);
	gtk_widget_set_size_request(name,250,50);
	
	address = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(address),address_label,0,0,0);
	gtk_box_pack_end(GTK_BOX(address),address_ter_field,0,0,0);
	gtk_widget_set_size_request(address,250,50);
	
	type = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(type),type_label,0,0,0);
	gtk_box_pack_end(GTK_BOX(type),type_ter_field,0,0,0);
	gtk_widget_set_size_request(type,100,50);
	
	gtk_container_add(GTK_CONTAINER(horizontal_box_one),code);
	gtk_container_add(GTK_CONTAINER(horizontal_box_one),name);
	gtk_container_add(GTK_CONTAINER(horizontal_box_one),address);
	gtk_container_add(GTK_CONTAINER(horizontal_box_one),type);
	
	gtk_container_add(GTK_CONTAINER(horizontal_box_two),concluir);
	gtk_container_add(GTK_CONTAINER(horizontal_box_two),alterar);
	gtk_container_add(GTK_CONTAINER(horizontal_box_two),listar);
	gtk_container_add(GTK_CONTAINER(horizontal_box_two),excluir);
	gtk_widget_set_size_request(GTK_WIDGET(concluir),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(alterar),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(listar),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(excluir),100,50);
	
	g_signal_connect(GTK_ENTRY(code_ter_field),"activate",G_CALLBACK(code_terc),code_ter_field);
	g_signal_connect(GTK_ENTRY(name_ter_field),"activate",G_CALLBACK(name_terc),name_ter_field);
	g_signal_connect(GTK_ENTRY(address_ter_field),"activate",G_CALLBACK(address_terc),address_ter_field);
	g_signal_connect(GTK_ENTRY(type_ter_field),"focus-in-event",G_CALLBACK(janela_tipo_ter),type_ter_field);
	
	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(code_terc),code_ter_field);
	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(name_terc),name_ter_field);
	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(address_terc),address_ter_field);
	//g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(type_terc),type_ter_field);
	gtk_widget_grab_focus(GTK_WIDGET(name_ter_field));

	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(conclui_ter),concluir);
	g_signal_connect(GTK_BUTTON(alterar),"clicked",G_CALLBACK(altera_ter),alterar);
	g_signal_connect(GTK_BUTTON(listar),"clicked",G_CALLBACK(lista_ter),listar);
	g_signal_connect(GTK_BUTTON(excluir),"clicked",G_CALLBACK(exclui_ter),excluir);
		
	g_signal_connect(GTK_BUTTON(janela),"destroy",G_CALLBACK(close_window_callback),NULL);
	
	gtk_container_add(GTK_CONTAINER(horizontal_box_one),separator);
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_one,30,5);
	gtk_fixed_put(GTK_FIXED(fixed2),horizontal_box_two,100,50);
	gtk_box_pack_start(GTK_BOX(vertical_box),fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(vertical_box),fixed2,0,0,0);
	gtk_container_add(GTK_CONTAINER(janela),vertical_box);
	gtk_widget_show_all(janela);
	return 0;
}
