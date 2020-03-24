GtkWidget *concluir, *alterar, *listar, *excluir;
#include "campos.c"
#include "altera.c"
#include "exclui.c"
#include "lista.c"
#include "conclui.c"
#define MARGEM_D 10

int inicializar_ter()
{
	int i;
	criticar.doc = 1;
	criticar.endereco = 1;
	criticar.nome = 1;
	criticar.tipo = 1;
	criticar.celular = 1;
	criticar.telefone = 1;
	criticar.contatoc = 1;
	criticar.contatot = 1;
	criticar.email = 1;
	criticar.contatoe = 1;
	
	for(i=0;i<=CAMPOS_QNT;i++)
		vet_erro[i] = 0;
	codigos_ter = malloc(10);
	doc_ter = malloc(CNPJ_S_LEN);
	nomes_ter = malloc(MAX_RAZ_LEN);	
	endereco_ter = malloc(MAX_ADR_LEN);
	cep_ter = malloc(CEP_LEN);
	tipo_ter = malloc(MAX_TIPO_LEN);
	memset(tipo_ter,0x0,strlen(tipo_ter));
	celular_ter = malloc(MAX_CEL_LEN);
	telefone_ter = malloc(MAX_TEL_LEN);
	contatoc_ter = malloc(MAX_CONT_LEN);
	contatot_ter = malloc(MAX_CONT_LEN);
	email_ter = malloc(MAX_EMAIL_LEN);
	contatoe_ter = malloc(MAX_CONT_LEN);
	observacoes_ter = malloc(MAX_OBS_LEN);
	buffer = malloc(sizeof(GtkTextBuffer*));
	produto_label = malloc(sizeof(GtkLabel*)*MAX_PROD);
	preco_entry = malloc(sizeof(GtkEntry*)*MAX_PROD);
	precos_caixas = malloc(sizeof(GtkBox*)*MAX_PROD);
	atualizar_preco = malloc(sizeof(GtkButton*)*MAX_PROD);
	remover_preco = malloc(sizeof(GtkButton*)*MAX_PROD);
	vet_cod = malloc(sizeof(gint*)*MAX_PROD);
	return 0;
}
int  cad_terc()
{
	char task[20];
	sprintf(task,"%i",tasker("terceiros"));
	g_print("task %s\n",task);	
	//linhas
	GtkWidget *horizontal_box_one, 
	*horizontal_box_two, 
	*horizontal_box_three, 
	*horizontal_box_four, 
	*horizontal_box_five, 
	*horizontal_box_six;
	
	//container/visual
	GtkWidget *fixed, *fixed2, *box,*vertical_box1, *vertical_box2, *separator;
	GtkWidget *code, *doc, *name, *address, *type;
	GtkWidget *celular, *telefone,*acao, *email, *observacoes;

	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_name(janela,"terceiros");
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"CADASTRO TERCEIROS");
	gtk_window_set_keep_above(GTK_WINDOW(janela), TRUE);
	gtk_container_set_border_width (GTK_CONTAINER (janela), 10);
	g_signal_connect(GTK_WINDOW(janela),"delete-event",G_CALLBACK(gtk_widget_destroy),&janela);
	gtk_widget_set_size_request(janela,900,600);
	
	acao = gtk_box_new(0,0);
	acao_atual = gtk_label_new("Ação atual: ");
	acao_atual2 = gtk_label_new("Cadastrando");
	gtk_widget_set_name(acao_atual2,"acao_atual");
	gtk_box_pack_start(GTK_BOX(acao),acao_atual,0,0,0);
	gtk_box_pack_start(GTK_BOX(acao),acao_atual2,0,0,5);
	
	
	//coluna de precos													*/
	lista_prod_label = gtk_label_new("Produtos Vinculados");
 	precos_scroll_caixa	 = gtk_box_new(1,0);
	precos_scroll_window = gtk_scrolled_window_new(NULL,NULL);
	#ifdef WIN32
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(precos_scroll_window),precos_scroll_caixa);
	#endif
	#ifdef __linux__
	gtk_container_add(GTK_CONTAINER(precos_scroll_window),precos_scroll_caixa);
	#endif
	gtk_box_pack_start(GTK_BOX(precos_scroll_caixa),lista_prod_label,0,0,0);
	/*																	*/
	gtk_widget_set_size_request(precos_scroll_window,200,500);
	
	fixed = gtk_fixed_new();
	fixed2 = gtk_fixed_new();
	
	horizontal_box_one = gtk_box_new(0,0);
	horizontal_box_two = gtk_box_new(0,0);
	horizontal_box_three = gtk_box_new(0,0);
	horizontal_box_four = gtk_box_new(0,0);
	horizontal_box_five = gtk_box_new(0,0);
	horizontal_box_six = gtk_box_new(0,0);
	
	box = gtk_box_new(0,0);
	vertical_box1 = gtk_box_new(1,0);
	vertical_box2 = gtk_box_new(1,0);
	separator = gtk_separator_new(1);
	
	doc_combo = gtk_combo_box_text_new();
	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(doc_combo),0,"Pessoa:");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(doc_combo),"1","Jurica");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(doc_combo),"2","Fisica");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(doc_combo),"3","Sem CNPJ/CPF");
	gtk_combo_box_set_active(GTK_COMBO_BOX(doc_combo),0);
	
	code_label = gtk_label_new("Codigo: ");
	doc_label = gtk_label_new("Documento:");
	name_label = gtk_label_new("Nome: ");
	address_label= gtk_label_new("Endereco: ");
	type_label = gtk_label_new("Tipo Terceiro: ");
	
	celular_label = gtk_label_new("Celular");
	contatoc_label = gtk_label_new("Contato");
	
	telefone_label = gtk_label_new("Telefone");
	contatot_label = gtk_label_new("Contato");
	contatoe_label = gtk_label_new("Contato");
	email_label = gtk_label_new("Email");

	observacoes_label = gtk_label_new("Observações");
	
	concluir = gtk_button_new_with_label("Concluir");
	alterar = gtk_button_new_with_label("Alterar");
	listar = gtk_button_new_with_label("Listar");
	excluir = gtk_button_new_with_label("Excluir");
	
	code_ter_field = gtk_entry_new();
	doc_ter_field = gtk_entry_new();
	name_ter_field = gtk_entry_new();
	address_ter_field = gtk_entry_new();
	type_ter_field = gtk_entry_new();
	celular_ter_field = gtk_entry_new();
	contatoc_ter_field = gtk_entry_new();
	telefone_ter_field = gtk_entry_new();
	contatot_ter_field = gtk_entry_new();
	email_ter_field = gtk_entry_new();
	contatoe_ter_field = gtk_entry_new();
	observacoes_ter_field = gtk_text_view_new();
	
	code = gtk_box_new(1,0);
	gtk_widget_set_name(code,"caixa");
	gtk_box_pack_start(GTK_BOX(code),code_label,0,0,0);
	gtk_box_pack_end(GTK_BOX(code),code_ter_field,0,0,0);
	gtk_entry_set_text(GTK_ENTRY(code_ter_field),task);
	gtk_widget_set_size_request(code_ter_field,50,30);

	doc = gtk_box_new(0,0);
	gtk_widget_set_name(doc,"caixa");
	gtk_box_pack_start(GTK_BOX(doc),doc_combo,0,0,0);
	gtk_box_pack_end(GTK_BOX(doc),doc_ter_field,0,0,0);
	gtk_widget_set_size_request(doc_ter_field,220,30);
		
	name = gtk_box_new(1,0);
	gtk_widget_set_name(name,"caixa");
	gtk_box_pack_start(GTK_BOX(name),name_label,0,0,0);
	gtk_box_pack_end(GTK_BOX(name),name_ter_field,0,0,0);
	gtk_widget_set_size_request(name_ter_field,500,30);
	
	address = gtk_box_new(1,0);
	gtk_widget_set_name(address,"caixa");
	gtk_box_pack_start(GTK_BOX(address),address_label,0,0,0);
	gtk_box_pack_end(GTK_BOX(address),address_ter_field,0,0,0);
	gtk_widget_set_size_request(address_ter_field,325,30);
	
	type = gtk_box_new(1,0);
	gtk_widget_set_name(type,"caixa");
	gtk_box_pack_start(GTK_BOX(type),type_label,0,0,0);
	gtk_box_pack_end(GTK_BOX(type),type_ter_field,0,0,0);
	gtk_widget_set_size_request(type_ter_field,100,30);
	
	celular  = gtk_box_new(1,0);
	gtk_widget_set_name(celular,"borda");
	gtk_box_pack_start(GTK_BOX(celular),celular_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(celular),celular_ter_field,0,0,0);
	gtk_box_pack_start(GTK_BOX(celular),contatoc_label,0,0,10);
	gtk_box_pack_start(GTK_BOX(celular),contatoc_ter_field,0,0,0);
	gtk_widget_set_size_request(celular_ter_field,100,30);
	gtk_widget_set_size_request(contatoc_ter_field,100,30);

	telefone = gtk_box_new(1,0);
	gtk_widget_set_name(telefone,"borda");
	gtk_box_pack_start(GTK_BOX(telefone),telefone_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(telefone),telefone_ter_field,0,0,0);
	gtk_box_pack_start(GTK_BOX(telefone),contatot_label,0,0,10);
	gtk_box_pack_start(GTK_BOX(telefone),contatot_ter_field,0,0,0);
	gtk_widget_set_size_request(telefone_ter_field,100,30);
	gtk_widget_set_size_request(contatot_ter_field,100,30);
	
	email = gtk_box_new(1,0);
	gtk_widget_set_name(email,"borda");
	gtk_box_pack_start(GTK_BOX(email),email_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(email),email_ter_field,0,0,0);
	gtk_box_pack_start(GTK_BOX(email),contatoe_label,0,0,10);
	gtk_box_pack_start(GTK_BOX(email),contatoe_ter_field,0,0,0);
	gtk_widget_set_size_request(email_ter_field,100,30);
	gtk_widget_set_size_request(contatoe_ter_field,100,30);
		
	observacoes = gtk_box_new(1,0);
	gtk_widget_set_name(observacoes,"caixa");
	gtk_box_pack_start(GTK_BOX(observacoes),observacoes_label,0,0,10);
	gtk_box_pack_start(GTK_BOX(observacoes),observacoes_ter_field,0,0,10);
	gtk_widget_set_size_request(observacoes_ter_field,500,100);
	
	gtk_box_pack_start(GTK_BOX(horizontal_box_one),code,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_one),doc,0,0,0);
	
	gtk_box_pack_start(GTK_BOX(horizontal_box_two),name,0,0,10);
	
	gtk_box_pack_start(GTK_BOX(horizontal_box_three),address,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_three),type,0,0,0);
	
	gtk_box_pack_start(GTK_BOX(horizontal_box_four),celular,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_four),telefone,0,0,0);
	gtk_box_pack_start(GTK_BOX(horizontal_box_four),email,0,0,10);
	
	gtk_box_pack_start(GTK_BOX(horizontal_box_five),observacoes,0,0,10);
	
	gtk_box_pack_start(GTK_BOX(horizontal_box_six),concluir,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_six),alterar,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_six),listar,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_six),excluir,0,0,10);

	gtk_widget_set_size_request(GTK_WIDGET(concluir),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(alterar),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(listar),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(excluir),100,50);
	
	
	g_signal_connect(GTK_ENTRY(code_ter_field),"activate",G_CALLBACK(code_terc),code_ter_field);
	
	g_signal_connect(doc_combo,"changed",G_CALLBACK(mover_para_doc),NULL);
	g_signal_connect(GTK_ENTRY(doc_ter_field),"activate",G_CALLBACK(escolha_doc),doc_ter_field);
	
	g_signal_connect(GTK_ENTRY(name_ter_field),"activate",G_CALLBACK(name_terc),name_ter_field);
	g_signal_connect(GTK_ENTRY(address_ter_field),"activate",G_CALLBACK(address_terc),address_ter_field);
	g_signal_connect(GTK_ENTRY(type_ter_field),"focus-in-event",G_CALLBACK(janela_tipo_ter),type_ter_field);
	g_signal_connect(GTK_ENTRY(celular_ter_field),"activate",G_CALLBACK(cel),NULL);
	g_signal_connect(GTK_ENTRY(telefone_ter_field),"activate",G_CALLBACK(tel),NULL);
	g_signal_connect(GTK_ENTRY(contatoc_ter_field),"activate",G_CALLBACK(contc),NULL);
	g_signal_connect(GTK_ENTRY(contatot_ter_field),"activate",G_CALLBACK(contt),NULL);
	g_signal_connect(GTK_ENTRY(email_ter_field),"activate",G_CALLBACK(email_fun),NULL);
	g_signal_connect(GTK_ENTRY(contatoe_ter_field),"activate",G_CALLBACK(contato_email),NULL);
	
	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(code_terc),NULL);
	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(name_terc),NULL);
	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(escolha_doc),NULL);
	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(address_terc),NULL);
	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(cel),NULL);
	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(tel),NULL);
	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(contc),NULL);
	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(contt),NULL);
	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(email_fun),NULL);
	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(contato_email),NULL);
	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(obs),NULL);

	g_signal_connect(GTK_BUTTON(concluir),"clicked",G_CALLBACK(conclui_ter),concluir);
	g_signal_connect(GTK_BUTTON(alterar),"clicked",G_CALLBACK(altera_ter),alterar);
	g_signal_connect(GTK_BUTTON(listar),"clicked",G_CALLBACK(lista_ter),listar);
	g_signal_connect(GTK_BUTTON(excluir),"clicked",G_CALLBACK(exclui_ter),excluir);
		
	g_signal_connect(janela,"destroy",G_CALLBACK(close_window_callback),janela);
	
	gtk_widget_set_name(vertical_box1,"vertical_box1");
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_one,MARGEM_D,20);    //codigo cnpj
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_two,MARGEM_D,80);    //nome
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_three,MARGEM_D,140); //endereco tipo ter
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_four,MARGEM_D,200);  //celular contato telefone contato email contato
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_five,MARGEM_D,330);  //observacoes
	gtk_fixed_put(GTK_FIXED(fixed2),horizontal_box_six,MARGEM_D,30);   //opcoess
	
	gtk_widget_set_name(vertical_box2,"vertical_box2");
	gtk_box_pack_start(GTK_BOX(vertical_box2),precos_scroll_window,0,0,0);
	
	gtk_widget_set_size_request(vertical_box2,300,590);
		
	gtk_box_pack_start(GTK_BOX(vertical_box1),acao,0,0,0);
	gtk_box_pack_start(GTK_BOX(vertical_box1),fixed,0,0,0);
	gtk_box_pack_end(GTK_BOX(vertical_box1),fixed2,0,0,10);
	
	gtk_box_pack_start(GTK_BOX(box),vertical_box1,0,0,0);
	gtk_box_pack_start(GTK_BOX(box),separator,0,0,10);
	gtk_box_pack_start(GTK_BOX(box),vertical_box2,0,0,0);

	gtk_container_add(GTK_CONTAINER(janela),box);
	abrir_css(DESKTOP_STYLE);
	rec_precos();
	gtk_widget_show_all(janela);
	gtk_widget_grab_focus(doc_ter_field);	

	return 0;
}
