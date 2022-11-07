#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"


void
on_buttonElec_clicked (GtkButton  *button,gpointer  user_data)
{
GtkWidget *WinElec1;
WinElec1 = create_GE_supprimer();
gtk_widget_show (WinElec1);
}


void
on_buttonAjou_clicked(GtkButton *button, gpointer  user_data)
{
//GtkWidget *winElec2;
//winElec2 = create_winElec2 ();
//gtk_widget_show (winElec2);


}



