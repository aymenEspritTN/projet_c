#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"


void
on_le_btn_vote_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_le_btn_aj_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_le_btn_supp_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_le_btn_aff_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_le_btn_modif_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_le_ajout_btn_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_le_modif_btn_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_buttonElec_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_le_btn_vote_valider_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_le_vote_blanche_btn_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_gest_le_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
}


void
on_btn_gest_obs_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_gest_adm_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *gestion_admin = create_gestion_admin();
	GtkWidget *gestion_entry = lookup_widget(button, "gestion_entry");
	gtk_widget_show(gestion_admin);
	gtk_widget_hide(gestion_entry);
}

