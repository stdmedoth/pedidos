static int ler_personalizacao();

int personalizacao_copy_image_to_custom_desktop();

static int receber_personalizacao();

int atualizar_personalizacao();


int trocar_desktop(GtkWidget *widget,GtkWidget *event,int posicao);

struct _personalizacao
{
	int janela_init;
	int janela_keep_above;
	int tema;

}personalizacao;


char *desktop_images_vet[] =
{
	THUMBDESKTOP1,
	THUMBDESKTOP2,
	THUMBDESKTOP3,
	THUMBDESKTOP4,
	THUMBDESKTOP5,
	THUMBDESKTOP6,
	THUMB_CTM_DESKTOP
};
