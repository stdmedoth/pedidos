#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <mysql/mysql.h>
char *padrao;
int data_format(GtkWidget *widget, gpointer *campo_data)
{
	int err=0,barra1=0,barra2=0;
	char *data,*padrao;
	data = malloc(15);
	padrao = malloc(15);
	data = (gchar *)gtk_entry_get_text(GTK_ENTRY(campo_data));
	g_print("data da geracao: %s\n",data);
	g_print("tamanho do formato: %i\n",strlen(data));
	switch(strlen(data))
	{
		case 6:		
			padrao[0] = data[0];
			padrao[1] = data[1];
			padrao[2] = '/';
			padrao[3] = data[2];
			padrao[4] = data[3];
			padrao[5] = '/';
			padrao[6] = data[4];
			padrao[7] = data[5];
			padrao[8] = '\0';
			gtk_entry_set_text(GTK_ENTRY(campo_data),padrao);
			break;
		case 8:
			if(data[2]!='/'||data[5]!='/')
				popup(NULL,"Padrao deve ser\nxx/xx/xx");
			padrao[0] = data[0];
			padrao[1] = data[1];
			padrao[2] = data[2]; 
			padrao[3] = data[3];
			padrao[4] = data[4];
			padrao[5] = data[5];
			padrao[6] = data[6];
			padrao[7] = data[7];
			padrao[8] = '\0';
			g_print("padrao não modificado\n");
			gtk_entry_set_text(GTK_ENTRY(campo_data),padrao);
			break;
		case 10:
			if(data[2]!=47)
				barra1 = 1;
			if(data[5]!=47)
				barra2 = 1;
			if(barra1||barra2==1)
			{
				popup(NULL,"Não reconheço esse\nformato de data");
			}
			else
			{	
				padrao[0] = data[0];
				padrao[1] = data[1];
				padrao[2] = data[2];
				
				padrao[3] = data[3];
				padrao[4] = data[4];
				padrao[5] = data[5];
				
				padrao[6] = data[6];
				padrao[7] = data[7];
				padrao[8] = data[8];
				padrao[9] = data[9];
				padrao[10] = '\0';
			}
			gtk_entry_set_text(GTK_ENTRY(campo_data),padrao);
			g_print("formato padronizado %s\n",padrao);
			if(err)
			{
				popup(NULL,"data não reconhecida\n");
			}
			gtk_entry_set_text(GTK_ENTRY(campo_data),padrao);
			break;
		default:
			popup(NULL,"padrão de data\nnão reconhecido");
			g_print("strlen data %i\n",strlen(data));
			break;
	}
	return 0;
}
int lists()
{
	GtkWidget *janela,*caixa_maior,*caixa_data,*caixa_check_vendas,*caixa_concluir,*check_data;
	GtkWidget *data,*check_venda,*fixed,*concluir;	
	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(janela),"listagem");
	gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
	fixed = gtk_fixed_new();
	
	caixa_data = gtk_hbox_new(0,0);
	caixa_check_vendas  = gtk_hbox_new(0,0);
	caixa_concluir =  gtk_hbox_new(0,0);
	caixa_maior = gtk_vbox_new(0,0);
	
	check_data = gtk_check_button_new_with_label("Por data");
	data = gtk_entry_new();
	concluir = gtk_button_new_with_label("Concluir");
	gtk_entry_set_text(GTK_ENTRY(data),"00/00/00");
	check_venda = gtk_check_button_new_with_label("Por vendas");
	
	gtk_widget_set_size_request(janela,200,200);
	gtk_widget_set_size_request(check_data,100,75);
	gtk_widget_set_size_request(data,80,40);
	gtk_widget_set_size_request(check_venda,100,75);
	
	gtk_container_add(GTK_CONTAINER(caixa_data),check_data);
	gtk_container_add(GTK_CONTAINER(caixa_data),data);
	
	gtk_container_add(GTK_CONTAINER(caixa_check_vendas),check_venda);
	
	gtk_container_add(GTK_CONTAINER(caixa_concluir),concluir);
	
	gtk_container_add(GTK_CONTAINER(caixa_maior),caixa_data);
	gtk_container_add(GTK_CONTAINER(caixa_maior),caixa_check_vendas);
	gtk_container_add(GTK_CONTAINER(caixa_maior),caixa_concluir);
	
	gtk_container_add(GTK_CONTAINER(fixed),caixa_maior);
	gtk_container_add(GTK_CONTAINER(janela),fixed);	
	
	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(data_format),data);
	g_signal_connect(GTK_WINDOW(janela),"delete-event",G_CALLBACK(gtk_widget_destroy),NULL);
	
	gtk_widget_show_all(janela);
	return 0;
}
