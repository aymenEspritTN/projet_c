#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "liste_electorale.h"


void
on_le_btn_vote_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_le_btn_aj_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *le_ajout = create_le_ajout();
	GtkWidget *le = lookup_widget(button, "le");
	gtk_widget_show(le_ajout);
	gtk_widget_hide(le);
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
	GtkWidget *le_ajout = lookup_widget(button, "le_ajout");
	GtkWidget *le_ajout_id = lookup_widget(button, "le_ajout_id");
	GtkWidget *le_ajout_id_tete = lookup_widget(button, "le_ajout_id_tete");
	GtkWidget *le_ajout_or1 = lookup_widget(button, "le_ajout_or1");
	GtkWidget *le_ajout_or2 = lookup_widget(button, "le_ajout_or2");
	GtkWidget *le_ajout_or3 = lookup_widget(button, "le_ajout_or3");
	GtkWidget *le_ajout_date_jour = lookup_widget(button, "le_ajout_date_jour");
	GtkWidget *le_ajout_date_mois = lookup_widget(button, "le_ajout_date_mois");
	GtkWidget *le_ajout_date_an = lookup_widget(button, "le_ajout_date_an");
	GtkWidget *le_ajout_nbre_candidats = lookup_widget(button, "le_ajout_nbre_candidats");
	GtkWidget *le_ajout_cand1 = lookup_widget(button, "le_ajout_cand1");
	GtkWidget *le_ajout_cand2 = lookup_widget(button, "le_ajout_cand2");
	GtkWidget *le_ajout_cand3 = lookup_widget(button, "le_ajout_cand3");
	GtkWidget *le_ajout_robot = lookup_widget(button, "le_ajout_robot");
	
	char* id = gtk_entry_get_text(le_ajout_id);
	char* id_tete = gtk_entry_get_text(le_ajout_id);
	char* id_cand1 = gtk_entry_get_text(le_ajout_cand1);
	char* id_cand2 = gtk_entry_get_text(le_ajout_cand2);
	char* id_cand3 = gtk_entry_get_text(le_ajout_cand3);
	int jour = gtk_spin_button_get_value_as_int(le_ajout_date_jour);
	int mois = gtk_spin_button_get_value_as_int(le_ajout_date_mois);
	int an = gtk_spin_button_get_value_as_int(le_ajout_date_an);
	int robotCheck = gtk_toggle_button_get_active(GTK_RADIO_BUTTON(le_ajout_robot));
	int gauche = gtk_toggle_button_get_active(GTK_RADIO_BUTTON(le_ajout_or1));
	int mid = gtk_toggle_button_get_active(GTK_RADIO_BUTTON(le_ajout_or2));
	int droit = gtk_toggle_button_get_active(GTK_RADIO_BUTTON(le_ajout_or3));
	int orientation = gauche || mid || droit;
	int nbre_candidats = atoi(gtk_combo_box_get_active_text(le_ajout_nbre_candidats));
	
	ListeElectorale le;
	le.id = id;
	le.orientation = orientation;
	le.date.jour = jour;
	le.date.mois = mois;
	le.date.an = an;
	le.nbre_candidats = nbre_candidats;
	le.id_candidats[0] = atoi(id_cand1);
	le.id_candidats[1] = atoi(id_cand2);
	le.id_candidats[2] = atoi(id_cand3);
	ajouter_le("le.txt", le);
	
	//gtk_combo_box_get_active_text, gtk_spin_button_get_value_as_int
	//int a = atoi ( string ); //converts str to int
	//sprintf(string, "%d" , a); //converts int to str
	
	GtkWidget* dialog = gtk_message_dialog_new (le_ajout,
                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                  GTK_MESSAGE_INFO,
                                  GTK_BUTTONS_CLOSE,
                                  "La liste electorale '%s' a ete ajoute avec succes", id);
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);
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
	GtkWidget *le = create_le();
	GtkWidget *gestion_entry = lookup_widget(button, "gestion_entry");
	gtk_widget_show(le);
	gtk_widget_hide(gestion_entry);
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


void
on_bv_ajout_addbtn_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{

}

