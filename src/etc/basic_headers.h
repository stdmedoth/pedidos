#ifndef PEDIDOS_BASIC_HEADER
#define PEDIDOS_BASIC_HEADER

#include <stdio.h>
#include <locale.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <gtk/gtk.h>
#include <libxml/xinclude.h>
#include <curl/curl.h>
#include <libxml/xpath.h>
#include <time.h>

#ifdef __linux__
#include <mariadb/mysql.h>
#endif

#ifdef WIN32
#include <windows.h>
#include <mysql/mysql.h>
#endif

#include "defines.h"

#endif