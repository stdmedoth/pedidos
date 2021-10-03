#ifndef PEDIDOS_BASIC_HEADER
#define PEDIDOS_BASIC_HEADER

#include <stdio.h>
#include <dirent.h>
#include <locale.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <gtk/gtk.h>
#include <math.h>
#include <libxml/xinclude.h>
#include <libxml/xpath.h>
#include <json-glib-1.0/json-glib/json-glib.h>
#include <cairo/cairo-pdf.h>
#include <curl/curl.h>
#include <time.h>

#ifdef __linux__
#include <mysql/mysql.h>
#endif

#ifdef WIN32
#include <windows.h>
#include <mysql.h>
#endif

#endif
