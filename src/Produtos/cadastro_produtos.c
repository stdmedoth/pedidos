#include "campos.c"
#include "altera.c"
#include "exclui.c"
#include "lista.c"
#include "conclui.c"

int  cad_prod()
{
	char task[20];
	sprintf(task,"%i",tasker("produtos"));
	GtkWidget *fixed, *fixed2, *fixed3;
	GtkWidget *horizontal_box_one, *horizontal_box_two, *horizontal_box_three, *vertical_box;
    GtkWidget *separator1,*separator2;
	GtkWidget *name, *price, *supp, *und;
	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_keep_above(GTK_WINDOW(janela), TRUE);
	gtk_window_set_title(GTK_WINDOW(janela),"CADASTRO PRODUTOS");
	gtk_widget_set_size_request(janela,70,400);
	
	fixed = gtk_fixed_new();
	fixed2 = gtk_fixed_new();
	fixed3 = gtk_fixed_new();
	
	horizontal_box_one = gtk_box_new(0,3);
	horizontal_box_two = gtk_box_new(0,3);
	horizontal_box_three = gtk_box_new(0,5);

	vertical_box = gtk_box_new(1,0);

	separator1 = gtk_separator_new(0);
	separator2 = gtk_separator_new(0);
	
	name_label = gtk_label_new("Nome: ");
	price_label= gtk_label_new("Preço: ");
	supp_label = gtk_label_new("fornecedor do produto: ");
	und_label = gtk_label_new("Tipo Unidade");
	
	name_field = gtk_entry_new();
	price_field = gtk_entry_new();
	supp_field = gtk_entry_new();
	und_field = gtk_entry_new();

	concluir = gtk_button_new_with_label("Concluir");
	alterar = gtk_button_new_with_label("Alterar");
	listar = gtk_button_new_with_label("Listar");
	excluir = gtk_button_new_with_label("Excluir");

	gtk_widget_set_size_request(GTK_WIDGET(concluir),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(alterar),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(listar),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(excluir),100,50);

	name = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(name),name_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(name),name_field,0,0,0);
	gtk_widget_set_size_request(name,250,50);

	price = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(price),price_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(price),price_field,0,0,0);
	gtk_widget_set_size_request(price,25,50);

	supp = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(supp),supp_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(supp),supp_field,0,0,0);
	gtk_widget_set_size_request(supp,275,50);

	und = gtk_box_new(1,0);
	gtk_box_pack_start(GTK_BOX(und),und_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(und),und_field,0,0,0);
	gtk_widget_set_size_request(und,25,50);
	
	gtk_box_pack_start(GTK_BOX(horizontal_box_one),name,0,0,0);
	gtk_box_pack_start(GTK_BOX(horizontal_box_one),price,0,0,0);
	gtk_box_pack_start(GTK_BOX(horizontal_box_one),supp,0,0,0);

	gtk_box_pack_start(GTK_BOX(horizontal_box_two),und,0,0,0);
	
	gtk_box_pack_start(GTK_BOX(horizontal_box_three),concluir,0,0,0);
	gtk_box_pack_start(GTK_BOX(horizontal_box_three),alterar,0,0,0);
	gtk_box_pack_start(GTK_BOX(horizontal_box_three),listar,0,0,0);
	gtk_box_pack_start(GTK_BOX(horizontal_box_three),excluir,0,0,0);

	g_signal_connect(GTK_WIDGET(name_field),"activate",G_CALLBACK(name_prod),NULL);
	g_signal_connect(GTK_WIDGET(price_field),"activate",G_CALLBACK(price_prod),NULL);
	g_signal_connect(GTK_WIDGET(supp_field),"activate",G_CALLBACK(supp_prod),NULL);
	g_signal_connect(GTK_WIDGET(und_field),"activate",G_CALLBACK(und_prod),NULL);

	g_signal_connect(GTK_WIDGET(concluir),"clicked",G_CALLBACK(name_prod),name_field);
	g_signal_connect(GTK_WIDGET(concluir),"clicked",G_CALLBACK(price_prod),price_field);
	g_signal_connect(GTK_WIDGET(concluir),"clicked",G_CALLBACK(supp_prod),supp_field);
	g_signal_connect(GTK_WIDGET(concluir),"clicked",G_CALLBACK(und_prod),und_field);
	
	g_signal_connect(GTK_WIDGET(concluir),"clicked",G_CALLBACK(concluido_prod),NULL);
	g_signal_connect(GTK_WIDGET(listar),"clicked",G_CALLBACK(listagem_prod),NULL);
	g_signal_connect(GTK_WIDGET(excluir),"clicked",G_CALLBACK(deleta_prod),NULL);
	g_signal_connect(GTK_WIDGET(alterar),"clicked",G_CALLBACK(altera_prod),NULL);
	
	g_signal_connect(GTK_WIDGET(janela),"destroy",G_CALLBACK(close_window_callback),janela);
	
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_one,30,5);
	gtk_fixed_put(GTK_FIXED(fixed2),horizontal_box_two,30,10);
	gtk_fixed_put(GTK_FIXED(fixed3),horizontal_box_three,100,50);

	gtk_box_pack_start(GTK_BOX(vertical_box),fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(vertical_box),separator1,0,0,10);
	gtk_box_pack_start(GTK_BOX(vertical_box),fixed2,0,0,0);
	gtk_box_pack_start(GTK_BOX(horizontal_box_one),separator2,0,0,10);
	gtk_box_pack_end(GTK_BOX(vertical_box),fixed3,0,0,30);

	gtk_container_add(GTK_CONTAINER(janela),vertical_box);

	gtk_widget_grab_focus (GTK_WIDGET(name_field));
	gtk_widget_show_all(janela);

	return 0;
}
