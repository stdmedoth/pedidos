void load_env(){
  switch (sizeof(void*)){
    case 4:
      #define APP_32BIT
      break;
    case 8:
      #define APP_64BIT
      break;
  }
}
