gboolean only_number_entry(GtkWidget *widget, GdkEventKey  *event, gpointer   user_data){
  int perms[] = {
    GDK_KEY_Escape,
    GDK_KEY_BackSpace,
    GDK_KEY_Tab,
    GDK_KEY_Return,
    GDK_KEY_KP_Enter,
    GDK_KEY_3270_Enter,
    GDK_KEY_leftarrow,
    GDK_KEY_uparrow,
    GDK_KEY_rightarrow,
    GDK_KEY_downarrow,
    GDK_KEY_Left,
    GDK_KEY_Up,
    GDK_KEY_Right,
    GDK_KEY_Down,
    GDK_KEY_R,
    GDK_KEY_0,
    GDK_KEY_1,
    GDK_KEY_2,
    GDK_KEY_3,
    GDK_KEY_4,
    GDK_KEY_5,
    GDK_KEY_6,
    GDK_KEY_7,
    GDK_KEY_8,
    GDK_KEY_9,
    -1
  };

  for(int cont=0; perms[cont] != -1; cont++){
    if(event->keyval == perms[cont]){
      return FALSE;
    }
  }

  if(event->keyval == ',' || event->keyval == '.'){
    event->keyval = '.';
    return FALSE;
  }

  if(isdigit(event->keyval))
    return FALSE;

  return TRUE;
}

int gtk_entry_cellphone(GtkEditable *editable, gpointer user_data){


  return 0;
}

int gtk_entry_telephone(GtkEditable *editable, gpointer user_data){

  return 0;
}
