GtkWidget *concluir, *alterar, *listar, *excluir;
#include "campos.c"
#include "altera.c"
#include "exclui.c"
#include "lista.c"
#include "conclui.c"

#define MARGEM_D 50
int  cad_terc()
{
	char task[20];
	sprintf(task,"%i",tasker("terceiros")+1);
	g_print("task %s\n",task);	
	
	//linhas
	GtkWidget *horizontal_box_one, 
	*horizontal_box_two, 
	*horizontal_box_three, 
	*horizontal_box_four, 
	*horizontal_box_five, 
	*horizontal_box_six;
	
	//container/visual
	GtkWidget *fixed, *fixed2, *vertical_box, *separator;
	GtkWidget *code, *cnpj, *name, *address, *type;
	GtkWidget *celular1, *telefone1;
	
	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"CADASTRO TERCEIROS");
	gtk_window_set_keep_above(GTK_WINDOW(janela), TRUE);
	gtk_container_set_border_width (GTK_CONTAINER (janela), 10);
	g_signal_connect(GTK_WINDOW(janela),"delete-event",G_CALLBACK(gtk_widget_destroy),&janela);
	gtk_widget_set_size_request(janela,1200,600);
	
	fixed = gtk_fixed_new();
	fixed2 = gtk_fixed_new();
	
	horizontal_box_one = gtk_box_new(0,0);
	horizontal_box_two = gtk_box_new(0,0);
	horizontal_box_three = gtk_box_new(0,0);
	horizontal_box_four = gtk_box_new(0,0);
	horizontal_box_five = gtk_box_new(0,0);
	horizontal_box_six = gtk_box_new(0,0);
	
	vertical_box = gtk_box_new(1,0);
	separator = gtk_separator_new(0);
	
	code_label = gtk_label_new("Codigo: ");
	cnpj_label = gtk_label_new("CNPJ:");
	name_label = gtk_label_new("Nome: ");
	address_label= gtk_label_new("Endereco: ");
	type_label = gtk_label_new("Tipo Terceiro: ");
	
	celular1_label = gtk_label_new("Celular");
	contatoc1_label = gtk_label_new("Contato");
	
	telefone1_label = gtk_label_new("Telefone");
	contatot1_label = gtk_label_new("Contato");
	
	concluir = gtk_button_new_with_label("Concluir");
	alterar = gtk_button_new_with_label("Alterar");
	listar = gtk_button_new_with_label("Listar");
	excluir = gtk_button_new_with_label("Excluir");
	
	code_ter_field = gtk_entry_new();
	cnpj_ter_field = gtk_entry_new();
	name_ter_field = gtk_entry_new();
	address_ter_field = gtk_entry_new();
	type_ter_field = gtk_entry_new();
	
	celular1_entry = gtk_entry_new();
	contatoc1_entry = gtk_entry_new();
	
	telefone1_entry = gtk_entry_new();
	contatot1_entry = gtk_entry_new();
	
	code = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(code),code_label,0,0,0);
	gtk_box_pack_end(GTK_BOX(code),code_ter_field,0,0,0);
	gtk_entry_set_text(GTK_ENTRY(code_ter_field),task);
	gtk_widget_set_size_request(code,50,50);

	cnpj = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(cnpj),cnpj_label,0,0,0);
	gtk_box_pack_end(GTK_BOX(cnpj),cnpj_ter_field,0,0,0);
	gtk_widget_set_size_request(cnpj,240,50);
		
	name = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(name),name_label,0,0,0);
	gtk_box_pack_end(GTK_BOX(name),name_ter_field,0,0,0);
	gtk_widget_set_size_request(name,440,50);
	
	address = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(address),address_label,0,0,0);
	gtk_box_pack_end(GTK_BOX(address),address_ter_field,0,0,0);
	gtk_widget_set_size_request(address,250,50);
	
	type = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(type),type_label,0,0,0);
	gtk_box_pack_end(GTK_BOX(type),type_ter_field,0,0,0);
	gtk_widget_set_size_request(type,50,50);
	

	celular1  = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(celular1),celular1_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(celular1),celular1_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(celular1),contatoc1_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(celular1),contatoc1_entry,0,0,0);

	telefone1 = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(telefone1),telefone1_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(telefone1),telefone1_entry,0,0,0);
	gtk_box_pack_start(GTK_BOX(telefone1),contatot1_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(telefone1),contatot1_entry,0,0,0);
	
	gtk_box_pack_start(GTK_BOX(horizontal_box_one),code,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_one),cnpj,0,0,20);
	
	gtk_box_pack_start(GTK_BOX(horizontal_box_two),name,0,0,10);
	
	gtk_box_pack_start(GTK_BOX(horizontal_box_three),address,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_three),type,0,0,10);
	
	gtk_box_pack_start(GTK_BOX(horizontal_box_four),celular1,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_four),telefone1,0,0,10);
	
	gtk_box_pack_start(GTK_BOX(horizontal_box_six),concluir,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_six),alterar,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_six),listar,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_six),excluir,0,0,10);

	gtk_widget_set_size_request(GTK_WIDGET(concluir),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(alterar),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(listar),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(excluir),100,50);
	
	g_signal_connect(GTK_ENTRY(code_ter_field),"activate",G_CALLBACK(code_terc),code_ter_field);
	g_signal_connect(GTK_ENTRY(cnpj_ter_field),"activate",G_CALLBACK(cnpj_terc),cnpj_ter_field);
	g_signal_connect(GTK_ENTRY(name_ter_field),"activate",G_CALLBACK(name_terc),name_ter_field);
	g_signal_connect(GTK_ENTRY(address_ter_field),"activate",G_CALLBACK(address_terc),address_ter_field);
	g_signal_connect(GTK_ENTRY(type_ter_field),"focus-in-event",G_CALLBACK(janela_tipo_ter),type_ter_field);
	
	g_signal_connect(GTK_ENTRY(celular1_entry),"focus-in-event",G_CALLBACK(mostrar_contatoc1),celular1_entry);
	g_signal_connect(GTK_ENTRY(telefone1_entry),"focus-in-event",G_CALLBACK(mostrar_contatot1),telefone1_entry);
	g_signal_connect(GTK_ENTRY(celular1_entry),"activate",G_CALLBACK(cel1),NULL);
	g_signal_connect(GTK_ENTRY(telefone1_entry),"activate",G_CALLBACK(tel1),NULL);
	g_signal_connect(GTK_ENTRY(contatoc1_entry),"activate",G_CALLBACK(contc1),NULL);
	g_signal_connect(GTK_ENTRY(contatot1_entry),"activate",G_CALLBACK(contt1),NULL);
	
	
	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(code_terc),code_ter_field);
	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(name_terc),name_ter_field);
	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(address_terc),address_ter_field);
	gtk_widget_grab_focus(GTK_WIDGET(cnpj_ter_field));

	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(conclui_ter),concluir);
	g_signal_connect(GTK_BUTTON(alterar),"clicked",G_CALLBACK(altera_ter),alterar);
	g_signal_connect(GTK_BUTTON(listar),"clicked",G_CALLBACK(lista_ter),listar);
	g_signal_connect(GTK_BUTTON(excluir),"clicked",G_CALLBACK(exclui_ter),excluir);
		
	g_signal_connect(janela,"destroy",G_CALLBACK(close_window_callback),janela);
	
	gtk_container_add(GTK_CONTAINER(fixed),separator);
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_one,MARGEM_D,10);
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_two,MARGEM_D,70);
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_three,MARGEM_D,130);
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_four,MARGEM_D,190);
	gtk_fixed_put(GTK_FIXED(fixed2),horizontal_box_six,MARGEM_D,0);
			
	gtk_box_pack_start(GTK_BOX(vertical_box),fixed,0,0,0);
	gtk_box_pack_end(GTK_BOX(vertical_box),fixed2,0,0,20);
	gtk_container_add(GTK_CONTAINER(janela),vertical_box);
	gtk_widget_show_all(janela);
	gtk_widget_hide(contatoc1_label);
	gtk_widget_hide(contatoc1_entry);
	gtk_widget_hide(contatot1_label);
	gtk_widget_hide(contatot1_entry);
	
	return 0;
}
