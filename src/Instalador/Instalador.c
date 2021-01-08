#include "Instalador.h"

int main(int argc, char *argv[]){

  gtk_init(&argc, &argv);

  if(assistente_init())
    return 1;

  gtk_main();

}
