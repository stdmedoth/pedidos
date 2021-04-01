/* Pedidos - Software Gerencial
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <locale.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <gtk/gtk.h>
#include <libxml/xinclude.h>
//#include <json-glib-1.0/json-glib/json-glib.h>
#include <cairo/cairo-pdf.h>
#include <curl/curl.h>
#include <time.h>

#ifdef __linux__
#include <mysql/mysql.h>
#endif

#ifdef WIN32
#include <windows.h>
#include <mysql/mysql.h>
#endif

#include "../etc/libs.h"
#include "../etc/libs.c"

int main(int argc, char *argv[])
{
	gtk_disable_setlocale();
	//setlocale(LC_ALL,"");
	setlocale(LC_COLLATE,"pt_BR");
	//setlocale(LC_CTYPE,"pt_BR");
	setlocale(LC_MONETARY,"en_US");
	setlocale(LC_NUMERIC,"en_US");

	gtk_init(NULL, NULL);

	limpar_sessao();
	limpar_applicacao();

	if(rec_vars_from_file())
		return 1;

	load_styles();

	if(init())
		return 1;

	carregar_interface();

	gtk_main();
	return 0;
}
