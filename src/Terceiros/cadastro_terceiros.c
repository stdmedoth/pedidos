int alterando_ter=0;
GtkWidget *concluir_ter_buttom, *alterar_ter_buttom, *listar_ter_buttom, *excluir_ter_buttom;
#include "campos.c"
#include "altera.c"
#include "exclui.c"
#include "lista.c"
#include "conclui.c"

int inicializar_ter()
{
	int i;
	
	for(i=0;i<=CAMPOS_QNT;i++)
		vet_erro[i] = 0;
	
	//char *
	codigos_ter = malloc(CODE_LEN);
	doc_ter = malloc(CNPJ_S_LEN);
	nomes_ter = malloc(MAX_RAZ_LEN);	
	endereco_ter = malloc(MAX_ADR_LEN);
	cep_ter = malloc(MAX_CEP_LEN);
	tipo_ter = malloc(MAX_TIPO_LEN);
	memset(tipo_ter,0x0,strlen(tipo_ter));
	celular_ter = malloc(MAX_CEL_LEN);
	telefone_ter = malloc(MAX_TEL_LEN);
	contatoc_ter = malloc(MAX_CONT_LEN);
	contatot_ter = malloc(MAX_CONT_LEN);
	email_ter = malloc(MAX_EMAIL_LEN);
	contatoe_ter = malloc(MAX_CONT_LEN);
	observacoes_ter = malloc(MAX_OBS_LEN);
	prazo_ter = malloc(MAX_DATE_LEN);
	
	//GtkWidget *
	buffer = malloc(sizeof(GtkTextBuffer*));
	produto_label = malloc(sizeof(GtkLabel*)*MAX_PROD);
	codigo_preco = malloc(sizeof(int*)*MAX_PROD);
	preco_entry = malloc(sizeof(GtkEntry*)*MAX_PROD);
	precos_caixas = malloc(sizeof(GtkBox*)*MAX_PROD);
	atualizar_preco = malloc(sizeof(GtkButton*)*MAX_PROD);
	remover_preco = malloc(sizeof(GtkButton*)*MAX_PROD);
	imagem_ok = malloc(sizeof(GtkImage*)*MAX_PROD);
	imagem_cancel = malloc(sizeof(GtkImage*)*MAX_PROD);
	imagem_dinheiro = malloc(sizeof(GtkImage*)*MAX_PROD);
	atualizar_preco = malloc(sizeof(GtkButton*)*MAX_PROD);
	remover_preco = malloc(sizeof(GtkButton*)*MAX_PROD);
	return 0;
}
int  cad_terc()
{
	char task[20];
	sprintf(task,"%i",tasker("terceiros"));
	g_print("task %s\n",task);	
	//linhas

	GtkWidget *janela;
	GtkWidget *horizontal_box_one, 
	*horizontal_box_two, 
	*horizontal_box_three, 
	*horizontal_box_four, 
	*horizontal_box_five, 
	*horizontal_box_six,
	*horizontal_box_seven;
	
	GtkWidget *caixa_grande;
	//container/visual
	GtkWidget *fixed, *fixed2, *box,*vertical_box1, *vertical_box2, *separator;
	GtkWidget *fixed3, *box2,*vertical_box3;
	GtkWidget *fixed4 , *box3, *vertical_box4;
	GtkWidget *fixed5 ,*box4, *vertical_box5;
	GtkWidget *fixed6 ,*box5, *vertical_box6;
	GtkWidget *opcoes;
	GtkWidget *code, *doc, *inscr, *name, *address, *cep,*type, *address_num;
	GtkWidget *celular, *telefone,*acao, *email, *observacoes,*prazo;
	GtkWidget *observacoes_scroll;
	GtkWidget *cid_uf_boxv1,*cid_uf_boxv2,*cid_uf_boxh;
	GtkWidget *addr_log_num_box,*addr_log_num_fixed;
	
	GtkWidget *ter_entrega_frame,*ter_endereco_frame;
	
	GtkWidget *ter_img_box, 
	*ter_img_frame, 
	*ter_img_buttons_box;

	frete_pago_flag = gtk_check_button_new_with_label("Frete Pago?");
	frete_pago_box = gtk_box_new(1,0);
	gtk_widget_set_name(frete_pago_box,"caixa");
	frete_pago_frame = gtk_frame_new("Valor mínimo para frete Pago");
	frete_pago_entry = gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(frete_pago_frame),frete_pago_entry);
	gtk_box_pack_start(GTK_BOX(frete_pago_box),frete_pago_flag,0,0,0);
	gtk_box_pack_start(GTK_BOX(frete_pago_box),frete_pago_frame,0,0,0);
	
	ter_notebook = gtk_notebook_new();
		
	ter_principal_box = gtk_box_new(1,0);
	ter_contatos_box = gtk_box_new(1,0);
	ter_entrega_box = gtk_box_new(0,0);
	ter_outros_box = gtk_box_new(1,0);
	opcoes = gtk_box_new(0,0);
	caixa_grande = gtk_box_new(1,0);
	
	cid_uf_boxv1 = gtk_box_new(1,0);
	cid_uf_boxv2 = gtk_box_new(1,0);
	cid_uf_boxh = gtk_box_new(0,0);
	
	ter_principal_label = gtk_label_new("Dados");
	ter_contatos_label = gtk_label_new("Contatos");
	ter_entrega_label = gtk_label_new("Sobre Entrega");
	ter_outros_label = gtk_label_new("Outros");
	
	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_name(janela,"terceiros");
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"CADASTRO TERCEIROS");
	gtk_window_set_keep_above(GTK_WINDOW(janela), TRUE);
	gtk_container_set_border_width (GTK_CONTAINER (janela), 10);
	g_signal_connect(GTK_WINDOW(janela),"delete-event",G_CALLBACK(gtk_widget_destroy),&janela);
	gtk_widget_set_size_request(janela,800,600);
	
	acao = gtk_box_new(0,0);
	acao_atual = gtk_label_new("Ação atual: ");
	acao_atual2 = gtk_label_new("Cadastrando");
	gtk_widget_set_name(acao_atual2,"acao_atual");
	gtk_box_pack_start(GTK_BOX(acao),acao_atual,0,0,0);
	gtk_box_pack_start(GTK_BOX(acao),acao_atual2,0,0,5);
	
	
	//coluna de precos	
	imagem_mais = gtk_image_new_from_file(IMG_MAIS);												
	botao_mais = gtk_button_new_with_label("Vincular um Preço/Produto");
	gtk_button_set_image(GTK_BUTTON(botao_mais),imagem_mais);
	

	lista_vinc_label = gtk_label_new("Preços Vinculados:");
 	precos_scroll_caixa	 = gtk_box_new(1,0);
	precos_scroll_window = gtk_scrolled_window_new(NULL,NULL);
	#ifdef WIN32
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(precos_scroll_window),precos_scroll_caixa);
	#endif
	#ifdef __linux__
	gtk_container_add(GTK_CONTAINER(precos_scroll_window),precos_scroll_caixa);
	#endif
	gtk_box_pack_start(GTK_BOX(precos_scroll_caixa),lista_vinc_label,0,0,20);
	/*																	*/
	gtk_widget_set_size_request(precos_scroll_window,200,500);
	
	fixed = gtk_fixed_new();
	fixed2 = gtk_fixed_new();
	fixed3 = gtk_fixed_new();
	fixed4 = gtk_fixed_new();
	fixed5 = gtk_fixed_new();
	
	horizontal_box_one = gtk_box_new(0,0);
	horizontal_box_two = gtk_box_new(0,0);
	horizontal_box_three = gtk_box_new(0,0);
	horizontal_box_four = gtk_box_new(0,0);
	horizontal_box_five = gtk_box_new(0,0);
	horizontal_box_six = gtk_box_new(0,0);
	horizontal_box_seven = gtk_box_new(0,0);
	
	box = gtk_box_new(0,0);
	box2 = gtk_box_new(0,0);
	box3 = gtk_box_new(0,0);
	box4 = gtk_box_new(0,0);
	vertical_box1 = gtk_box_new(1,0);
	vertical_box2 = gtk_box_new(1,0);
	vertical_box3 = gtk_box_new(1,0);
	vertical_box4 = gtk_box_new(1,0);
	vertical_box5 = gtk_box_new(1,0);
	vertical_box6 = gtk_box_new(1,0);
	separator = gtk_separator_new(1);
	
	doc_combo = gtk_combo_box_text_new();
	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(doc_combo),0,"Pessoa:");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(doc_combo),"1","Jurídica");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(doc_combo),"2","Física");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(doc_combo),"3","Sem CNPJ/CPF");
	gtk_combo_box_set_active(GTK_COMBO_BOX(doc_combo),0);
	
	code_label = gtk_label_new("Codigo: ");
	doc_label = gtk_label_new("Documento:");
	
	name_label = gtk_label_new("Nome: ");
	
	inscr_label = gtk_label_new("IE:");
	
	addr_log_num_box = gtk_box_new(0,0);
	addr_log_num_fixed = gtk_fixed_new();
	address_num = gtk_box_new(1,0);
	cep_label = gtk_label_new("Cep: ");
	address_label= gtk_label_new("Logradouro: ");
	cidade_label= gtk_label_new("Cidade: ");
	address_num_label = gtk_label_new("Número: ");
	address_num_field = gtk_entry_new();
	uf_label = gtk_label_new("UF: ");
	uf_ter_field = gtk_entry_new();
	
	gtk_entry_set_width_chars(GTK_ENTRY(address_num_field),8);
	gtk_box_pack_start(GTK_BOX(address_num),address_num_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(address_num),address_num_field,0,0,0);
	gtk_fixed_put(GTK_FIXED(addr_log_num_fixed),address_num,0,0);
	
	rua_combo = gtk_combo_box_text_new();
	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(rua_combo),0,("Tipo:"));
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(rua_combo),"1",(tip_logds[0]));
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(rua_combo),"2",(tip_logds[1]));
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(rua_combo),"3",(tip_logds[2]));
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(rua_combo),"4",(tip_logds[3]));
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(rua_combo),"5",(tip_logds[4]));
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(rua_combo),"6",(tip_logds[5]));
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(rua_combo),"7",(tip_logds[6]));
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(rua_combo),"8",("Outros"));
	gtk_combo_box_set_active(GTK_COMBO_BOX(rua_combo),0);
	
	type_label = gtk_frame_new("Tipo Terceiro: ");	
	celular_label = gtk_label_new("Celular");
	contatoc_label = gtk_label_new("Contato");
	
	telefone_label = gtk_label_new("Telefone");
	contatot_label = gtk_label_new("Contato");
	contatoe_label = gtk_label_new("Contato");
	email_label = gtk_label_new("Email");
	
	concluir_ter_buttom = gtk_button_new_with_label("Concluir");
	alterar_ter_buttom = gtk_button_new_with_label("Alterar");
	listar_ter_buttom = gtk_button_new_with_label("Pesquisar");
	excluir_ter_buttom = gtk_button_new_with_label("Excluir");
	
	code_ter_field = gtk_entry_new();
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(code_ter_field),GTK_ENTRY_ICON_PRIMARY,"emblem-system");
	
	doc_ter_field = gtk_entry_new();
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(doc_ter_field),GTK_ENTRY_ICON_PRIMARY,"user-info");

	inscr_ter_field = gtk_entry_new();
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(inscr_ter_field),GTK_ENTRY_ICON_PRIMARY,"user-info");
	
	name_ter_field = gtk_entry_new();
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(name_ter_field),GTK_ENTRY_ICON_PRIMARY,"avatar-default");
	
	cep_ter_field = gtk_entry_new();
	address_ter_field = gtk_entry_new();                     
	cidade_ter_field = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(cep_ter_field),"");
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(address_ter_field),GTK_ENTRY_ICON_PRIMARY,"mark-location");
	
	type_ter_field = gtk_combo_box_text_new();
	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(type_ter_field),0,("Escolha o tipo"));
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(type_ter_field),"1",("Cliente"));
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(type_ter_field),"2",("Fornecedor"));
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(type_ter_field),"3",("Ambos"));
	gtk_combo_box_set_active(GTK_COMBO_BOX(type_ter_field),0);
	
	celular_ter_field = gtk_entry_new();
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(celular_ter_field),GTK_ENTRY_ICON_PRIMARY,"pda");
	
	contatoc_ter_field = gtk_entry_new();
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(contatoc_ter_field),GTK_ENTRY_ICON_PRIMARY,"contact-new");
	
	telefone_ter_field = gtk_entry_new();
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(telefone_ter_field),GTK_ENTRY_ICON_PRIMARY,"modem");
	
	contatot_ter_field = gtk_entry_new();
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(contatot_ter_field),GTK_ENTRY_ICON_PRIMARY,"contact-new");
	
	email_ter_field = gtk_entry_new();
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(email_ter_field),GTK_ENTRY_ICON_PRIMARY,"mail-read");
	
	contatoe_ter_field = gtk_entry_new();
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(contatoe_ter_field),GTK_ENTRY_ICON_PRIMARY,"contact-new");
	
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
		
	inscr = gtk_box_new(0,0);
	gtk_widget_set_name(inscr,"caixa");
	gtk_box_pack_start(GTK_BOX(inscr),inscr_label,0,0,5);
	gtk_box_pack_end(GTK_BOX(inscr),inscr_ter_field,0,0,15);
	gtk_widget_set_size_request(inscr_ter_field,220,30);
	
	name = gtk_box_new(1,0);
	gtk_widget_set_name(name,"caixa");
	gtk_box_pack_start(GTK_BOX(name),name_label,0,0,0);
	gtk_box_pack_end(GTK_BOX(name),name_ter_field,0,0,0);
	gtk_widget_set_size_request(name_ter_field,500,30);
	
	ter_endereco_frame = gtk_frame_new("Endereço Cliente");
	ter_entrega_frame = gtk_frame_new("Endereço Entrega");
	
	address = gtk_box_new(1,0);
	gtk_widget_set_name(address,"caixa");
	
	cep = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(cep),cep_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(cep),cep_ter_field,0,0,0);
	gtk_box_pack_start(GTK_BOX(cep),rua_combo,0,0,10);
	gtk_box_pack_start(GTK_BOX(address),cep,0,0,5);
	gtk_box_pack_start(GTK_BOX(addr_log_num_box),address,0,0,5);
	gtk_box_pack_start(GTK_BOX(addr_log_num_box),addr_log_num_fixed,0,0,5);
	gtk_container_add(GTK_CONTAINER(ter_endereco_frame),addr_log_num_box);
	
	gtk_box_pack_start(GTK_BOX(address),address_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(address),address_ter_field,0,0,0);
	
	gtk_box_pack_start(GTK_BOX(cid_uf_boxv1),cidade_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(cid_uf_boxv1),cidade_ter_field,0,0,5);
	gtk_box_pack_start(GTK_BOX(cid_uf_boxv2),uf_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(cid_uf_boxv2),uf_ter_field,0,0,5);
	gtk_box_pack_start(GTK_BOX(cid_uf_boxh),cid_uf_boxv1,0,0,10);
	gtk_box_pack_start(GTK_BOX(cid_uf_boxh),cid_uf_boxv2,0,0,10);
	gtk_entry_set_width_chars(GTK_ENTRY(uf_ter_field),5);

	gtk_box_pack_start(GTK_BOX(address),cid_uf_boxh,0,0,5);
	gtk_widget_set_size_request(address_ter_field,325,30);
		
	type = gtk_box_new(1,0);
	
	gtk_widget_set_name(type,"caixa");
	gtk_container_add(GTK_CONTAINER(type_label),type_ter_field);
	gtk_box_pack_start(GTK_BOX(type),type_label,0,0,0);
	
	celular  = gtk_box_new(1,0);
	//gtk_widget_set_name(celular,"borda");
	gtk_box_pack_start(GTK_BOX(celular),celular_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(celular),celular_ter_field,0,0,0);
	gtk_box_pack_start(GTK_BOX(celular),contatoc_label,0,0,10);
	gtk_box_pack_start(GTK_BOX(celular),contatoc_ter_field,0,0,0);
	gtk_widget_set_size_request(celular_ter_field,100,30);
	gtk_widget_set_size_request(contatoc_ter_field,100,30);

	telefone = gtk_box_new(1,0);
	//gtk_widget_set_name(telefone,"borda");
	gtk_box_pack_start(GTK_BOX(telefone),telefone_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(telefone),telefone_ter_field,0,0,0);
	gtk_box_pack_start(GTK_BOX(telefone),contatot_label,0,0,10);
	gtk_box_pack_start(GTK_BOX(telefone),contatot_ter_field,0,0,0);
	gtk_widget_set_size_request(telefone_ter_field,100,30);
	gtk_widget_set_size_request(contatot_ter_field,100,30);
	
	email = gtk_box_new(1,0);
	//gtk_widget_set_name(email,"borda");
	gtk_box_pack_start(GTK_BOX(email),email_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(email),email_ter_field,0,0,0);
	gtk_box_pack_start(GTK_BOX(email),contatoe_label,0,0,10);
	gtk_box_pack_start(GTK_BOX(email),contatoe_ter_field,0,0,0);
	gtk_widget_set_size_request(email_ter_field,100,30);
	gtk_widget_set_size_request(contatoe_ter_field,100,30);
		
	observacoes = gtk_box_new(1,0);
	observacoes_label = gtk_label_new("Observações");
	observacoes_ter_field = gtk_text_view_new();
	observacoes_scroll = gtk_scrolled_window_new(NULL,NULL);
	gtk_widget_set_name(observacoes,"caixa");
	gtk_box_pack_start(GTK_BOX(observacoes),observacoes_label,0,0,10);
	gtk_box_pack_start(GTK_BOX(observacoes),observacoes_ter_field,0,0,10);
	#ifdef __linux__
	gtk_container_add(GTK_CONTAINER(observacoes_scroll),observacoes);
	#endif
	#ifdef WIN32
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(observacoes_scroll),observacoes);
	#endif
	gtk_widget_set_size_request(observacoes_ter_field,500,100);
	gtk_widget_set_size_request(observacoes_scroll,500,120);
	gtk_widget_set_size_request(observacoes,500,120);
	
	prazo = gtk_box_new(1,0);
	gtk_widget_set_name(prazo,"caixa");
	prazo_ter_label = gtk_label_new("Prazo padrão");
	prazo_ter_field = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(prazo),prazo_ter_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(prazo),prazo_ter_field,0,0,0);
	
	ter_img_box = gtk_box_new(1,0);
	ter_img_buttons_box = gtk_box_new(0,0);
	ter_img_frame = gtk_frame_new("Insira uma imagem");
	ter_img_image = gtk_image_new_from_file(NULL);
	ter_img_button_inserir = gtk_button_new_with_label("Inserir");
	ter_img_button_retirar = gtk_button_new_with_label("Retirar");
	
	gtk_container_add(GTK_CONTAINER(ter_img_frame),ter_img_image);
	gtk_widget_set_size_request(GTK_WIDGET(ter_img_frame),200,200);
	gtk_widget_set_size_request(GTK_WIDGET(ter_img_image),200,200);
	gtk_box_pack_start(GTK_BOX(ter_img_buttons_box),ter_img_button_inserir,0,0,10);
	gtk_box_pack_start(GTK_BOX(ter_img_buttons_box),ter_img_button_retirar,0,0,10);
	
	gtk_box_pack_start(GTK_BOX(ter_img_box),ter_img_frame,0,0,10);
	gtk_box_pack_start(GTK_BOX(ter_img_box),ter_img_buttons_box,0,0,10);	
	
	gtk_box_pack_start(GTK_BOX(horizontal_box_one),code,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_one),doc,0,0,0);
	
	gtk_box_pack_start(GTK_BOX(horizontal_box_two),inscr,0,0,10);
	
	gtk_box_pack_start(GTK_BOX(horizontal_box_three),name,0,0,10);
	
	gtk_box_pack_start(GTK_BOX(horizontal_box_four),ter_endereco_frame,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_four),type,0,0,0);
	
	gtk_box_pack_start(GTK_BOX(horizontal_box_five),observacoes_scroll,0,0,20);
	
	gtk_box_pack_start(GTK_BOX(horizontal_box_six),celular,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_six),telefone,0,0,0);
	gtk_box_pack_start(GTK_BOX(horizontal_box_six),email,0,0,10);
	gtk_box_pack_end(GTK_BOX(horizontal_box_six),ter_img_box,0,0,10);
	
	gtk_box_pack_start(GTK_BOX(horizontal_box_seven),prazo,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_seven),frete_pago_box,0,0,10);

	gtk_box_pack_start(GTK_BOX(opcoes),concluir_ter_buttom,0,0,10);
	gtk_box_pack_start(GTK_BOX(opcoes),alterar_ter_buttom,0,0,10);
	gtk_box_pack_start(GTK_BOX(opcoes),listar_ter_buttom,0,0,10);
	gtk_box_pack_start(GTK_BOX(opcoes),excluir_ter_buttom,0,0,10);

	gtk_widget_set_size_request(GTK_WIDGET(concluir_ter_buttom),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(alterar_ter_buttom),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(listar_ter_buttom),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(excluir_ter_buttom),100,50);
	
	
	g_signal_connect(GTK_ENTRY(code_ter_field),"activate",G_CALLBACK(code_terc),code_ter_field);
	g_signal_connect(doc_combo,"changed",G_CALLBACK(mover_para_doc),NULL);
	g_signal_connect(GTK_ENTRY(doc_ter_field),"activate",G_CALLBACK(escolha_doc),doc_ter_field);
	g_signal_connect(GTK_ENTRY(inscr_ter_field),"activate",G_CALLBACK(inscr_terc),NULL);
	g_signal_connect(GTK_ENTRY(name_ter_field),"activate",G_CALLBACK(name_terc),name_ter_field);
	g_signal_connect(GTK_ENTRY(cep_ter_field),"activate",G_CALLBACK(cep_terc),NULL);
	g_signal_connect(GTK_ENTRY(address_ter_field),"activate",G_CALLBACK(address_terc),NULL);
	g_signal_connect(GTK_ENTRY(cidade_ter_field),"activate",G_CALLBACK(cidade_terc),NULL);
	g_signal_connect(GTK_ENTRY(uf_ter_field),"activate",G_CALLBACK(uf_terc),NULL);
	g_signal_connect(GTK_ENTRY(address_num_field),"activate",G_CALLBACK(numrua),NULL);
	g_signal_connect(type_ter_field,"changed",G_CALLBACK(escolha_tipo_ter),type_ter_field);
	g_signal_connect(GTK_ENTRY(prazo_ter_field),"activate",G_CALLBACK(prazo_fun),NULL);
	g_signal_connect(GTK_ENTRY(celular_ter_field),"activate",G_CALLBACK(cel),NULL);
	g_signal_connect(GTK_ENTRY(telefone_ter_field),"activate",G_CALLBACK(tel),NULL);
	g_signal_connect(GTK_ENTRY(contatoc_ter_field),"activate",G_CALLBACK(contc),NULL);
	g_signal_connect(GTK_ENTRY(contatot_ter_field),"activate",G_CALLBACK(contt),NULL);
	g_signal_connect(GTK_ENTRY(email_ter_field),"activate",G_CALLBACK(email_fun),NULL);
	g_signal_connect(GTK_ENTRY(contatoe_ter_field),"activate",G_CALLBACK(contato_email),NULL);
	
	g_signal_connect(GTK_ENTRY(frete_pago_flag),"toggled",G_CALLBACK(verifica_frete),NULL);
	
	g_signal_connect(GTK_BUTTON(botao_mais),"clicked",G_CALLBACK(add_vinc_prod_cli),NULL);

	g_signal_connect(GTK_BUTTON(concluir_ter_buttom),"clicked",G_CALLBACK(conclui_ter),concluir_ter_buttom);
	g_signal_connect(GTK_BUTTON(alterar_ter_buttom),"clicked",G_CALLBACK(altera_ter),alterar_ter_buttom);
	g_signal_connect(GTK_BUTTON(listar_ter_buttom),"clicked",G_CALLBACK(pesquisar_terceiros),listar_ter_buttom);
	g_signal_connect(GTK_BUTTON(excluir_ter_buttom),"clicked",G_CALLBACK(exclui_ter),excluir_ter_buttom);
		
	g_signal_connect(janela,"destroy",G_CALLBACK(close_window_callback),janela);
	
	//page 0
	//na page 0 é usado dois vertical_Box por causa da parte de dados e preços
	gtk_widget_set_name(vertical_box1,"vertical_box1");
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_one,MARGEM_D,20);    //codigo cnpj
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_two,MARGEM_D,80);    //inscricao
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_three,MARGEM_D,120); //nome
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_four,MARGEM_D,180);  //cep/endereco tipo ter
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_five,MARGEM_D,380);  //observacoes	
	gtk_fixed_put(GTK_FIXED(fixed2),horizontal_box_six,MARGEM_D,20);   //contatos
	gtk_fixed_put(GTK_FIXED(fixed4),horizontal_box_seven,MARGEM_D,20); //outros
	
	 //
	
	gtk_widget_set_name(vertical_box2,"vertical_box2"); //campo dos precos para cliente
	gtk_box_pack_start(GTK_BOX(vertical_box2),botao_mais,0,0,0);
	gtk_box_pack_start(GTK_BOX(vertical_box2),precos_scroll_window,0,0,0);
	gtk_widget_set_size_request(vertical_box2,300,400);
	
	gtk_box_pack_start(GTK_BOX(vertical_box1),acao,0,0,0);//campo dos dados em clientes
	gtk_box_pack_start(GTK_BOX(vertical_box1),fixed,0,0,0);
	gtk_widget_set_size_request(vertical_box2,300,400);
	
	gtk_box_pack_start(GTK_BOX(box),vertical_box1,0,0,0);
	gtk_box_pack_start(GTK_BOX(box),separator,0,0,10);
	gtk_box_pack_start(GTK_BOX(box),vertical_box2,0,0,0);	

	//page 1
	gtk_fixed_put(GTK_FIXED(fixed2),horizontal_box_six,MARGEM_D,30); //celular  telefone  email      imagem
																	//contato   contato  contato
	gtk_box_pack_start(GTK_BOX(vertical_box3),fixed2,0,0,10);
	
	gtk_box_pack_start(GTK_BOX(box2),vertical_box3,0,0,0);	
	
	//page 2
	box3 = entrega_campos();
	
	//page 3
	
	gtk_box_pack_start(GTK_BOX(vertical_box4),fixed4,0,0,10);
	
	gtk_box_pack_start(GTK_BOX(box4),vertical_box4,0,0,0);	
	
	//pages on notebook
	gtk_box_pack_start(GTK_BOX(ter_principal_box),box,0,0,0);

	gtk_box_pack_start(GTK_BOX(ter_contatos_box),box2,0,0,0);

	gtk_box_pack_start(GTK_BOX(ter_entrega_box),box3,0,0,0);

	gtk_box_pack_start(GTK_BOX(ter_outros_box),box4,0,0,0);
	
	
	gtk_notebook_append_page(GTK_NOTEBOOK(ter_notebook),ter_principal_box,ter_principal_label);
	gtk_notebook_append_page(GTK_NOTEBOOK(ter_notebook),ter_contatos_box,ter_contatos_label);
	gtk_notebook_append_page(GTK_NOTEBOOK(ter_notebook),ter_entrega_box,ter_entrega_label);
	gtk_notebook_append_page(GTK_NOTEBOOK(ter_notebook),ter_outros_box,ter_outros_label);

	gtk_box_pack_start(GTK_BOX(caixa_grande),ter_notebook,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_grande),opcoes,0,0,10);

	gtk_container_add(GTK_CONTAINER(janela),caixa_grande);
	abrir_css(DESKTOP_STYLE);
	rec_precos();
	gtk_widget_set_sensitive(frete_pago_entry,FALSE);
	gtk_widget_set_sensitive(GTK_WIDGET(botao_mais),FALSE);
	gtk_widget_show_all(janela);
	gtk_widget_grab_focus(doc_ter_field);	

	return 0;
}
