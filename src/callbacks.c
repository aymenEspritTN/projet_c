#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "liste_electorale.h"

int le_ajout_mode = 0; //0 = AJOUT, 1 = MODIFIER

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
	le_ajout_mode = 0;
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
	GtkWidget *le_affichage = create_le_affichage();
	GtkWidget *le = lookup_widget(button, "le");
	gtk_widget_show(le_affichage);
	gtk_widget_hide(le);
	
	GtkWidget *le_aff_treeview = lookup_widget(GTK_WINDOW(le_affichage), "le_aff_treeview");
	
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	
	treeview_create_render(le_aff_treeview);
	//treeview_vider(le_aff_treeview);
	
	int n = 0;
	ListeElectorale* t = read_file_as_table("le.txt", &n);
	treeview_remplir(le_aff_treeview, t, n);
}

void treeview_create_render(GtkWidget* liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes
			( "id", renderer, "text", id, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes
			( "id tete", renderer, "text", id_tete, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes
			( "orientation", renderer, "text", orientation, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes
			( "date", renderer, "text", date, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes
			( "nbre candidats", renderer, "text", nbre_candidats, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes
			( "id candidats", renderer, "text", id_candidats, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
}
void treeview_vider(GtkWidget* liste)
{
	GtkTreeIter iter;
	GtkListStore *store;
	store = NULL;
	store = gtk_tree_view_get_model(GTK_TREE_VIEW(liste));

	if(store==NULL)
	{
	}
	store=gtk_list_store_new(6, 
				G_TYPE_INT,
				G_TYPE_INT,
				G_TYPE_INT,
				G_TYPE_STRING,
				G_TYPE_INT,
				G_TYPE_STRING
				);
	//gtk_list_store_append(GTK_LIST_STORE(store), &iter);
	gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL (store));
	g_object_unref(store);
}
void treeview_remplir(GtkWidget* liste, ListeElectorale t[], int n)
{
	GtkTreeIter iter;
	GtkListStore *store;
	store = NULL;
	store = gtk_tree_view_get_model(GTK_TREE_VIEW(liste));

	if(store==NULL)
	{

	}
	store=gtk_list_store_new(6, 
				G_TYPE_INT,
				G_TYPE_INT,
				G_TYPE_INT,
				G_TYPE_STRING,
				G_TYPE_INT,
				G_TYPE_STRING
				);

	char _id_candidats[100];
	int i = 0;
	for(i =0; i<n; i++)
	{
		ListeElectorale le = t[i];
		
		sprintf(_id_candidats, "%d|%d|%d",
			le.id_candidats[0], le.id_candidats[1], le.id_candidats[2]);

		gtk_list_store_append(GTK_LIST_STORE(store), &iter);
		gtk_list_store_set(store, &iter, 
			id, le.id, 
			id_tete, le.id_tete, 
			orientation, le.orientation, 
			date, DateToString(le.date),
			nbre_candidats, le.nbre_candidats, 
			id_candidats, _id_candidats,
			-1);
	}
	gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL (store));
	g_object_unref(store);
}

void treeview_search(GtkWidget* liste, char* query)
{
	int n = 0;
	ListeElectorale* t = read_file_as_table("le.txt", &n);
	int found_n = 0;
	ListeElectorale found[n];
	
	int i=0;
	for(i=0; i<n; i++)
	{
		int id = t[i].id;
		if( atoi(query) == id )
		{
			found[found_n] = t[i];
			found_n++;
		}
	}

	treeview_vider(liste);
	treeview_remplir(liste, found, found_n);
}




void
on_le_btn_modif_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *le_modifier = create_le_modifier();
	GtkWidget *le = lookup_widget(button, "le");
	gtk_widget_show(le_modifier);
	gtk_widget_hide(le);
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
	int robotCheck = gtk_toggle_button_get_active(GTK_CHECK_BUTTON(le_ajout_robot));
	int gauche = gtk_toggle_button_get_active(GTK_RADIO_BUTTON(le_ajout_or1));
	int mid = gtk_toggle_button_get_active(GTK_RADIO_BUTTON(le_ajout_or2));
	int droit = gtk_toggle_button_get_active(GTK_RADIO_BUTTON(le_ajout_or3));
	int orientation = 0;
	int nbre_candidats = atoi(gtk_combo_box_get_active_text(le_ajout_nbre_candidats));
	
	if(gauche)orientation = 0;
	if(mid)orientation = 1;
	if(droit)orientation = 2;

	ListeElectorale le;
	le.id = atoi(id);
	le.orientation = orientation;
	le.date.jour = jour;
	le.date.mois = mois;
	le.date.an = an;
	le.id_tete = atoi(id_tete);
	le.nbre_candidats = nbre_candidats;
	le.id_candidats[0] = atoi(id_cand1);
	le.id_candidats[1] = atoi(id_cand2);
	le.id_candidats[2] = atoi(id_cand3);
	
	//gtk_combo_box_get_active_text, gtk_spin_button_get_value_as_int
	//int a = atoi ( string ); //converts str to int
	//sprintf(string, "%d" , a); //converts int to str


	char error[100] = "";


	ListeElectorale existing_le = chercher_le("le.txt", le.id);
	if(existing_le.id != -1 && le_ajout_mode != 1)
	{
		strcat(error, "Cet idee de liste a ete deja choisi (existe)\n");
	}

	
	/*int anyUserDontExist = 0;
	User existing_user = cherche_user("user.txt", le.id_tete);
	if(existing_user.id == -1)
	{
		anyUserDontExist = 1;
		strcat(error, "user avec id tete n'existe pas\n");
	}
	else
	{
		int i = 0;
		for(i = 0; i<le.nbre_candidats; i++)
		{
			existing_user = cherche_user("user.txt", le.id_candidats[i]);
			if(existing_user.id == -1)
			{
				anyUserDontExist = 1;
				strcat(error, "user d'id n'existe pas\n");
				break;
			}
		}
	}*/
	
	if(robotCheck == 0)
	{
		strcat(error, "verifiez que vous n'ete pas un robot\n");
	}
	
	if(strlen(error)>0)
	{
		GtkWidget* dialog = gtk_message_dialog_new (le_ajout,
		                          GTK_DIALOG_DESTROY_WITH_PARENT,
		                          GTK_MESSAGE_INFO,
		                          GTK_BUTTONS_CLOSE,
		                          error);
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
	}
	else
	{
		if(le_ajout_mode == 0)
		{
			ajouter_le("le.txt", le);
			GtkWidget* dialog = gtk_message_dialog_new (le_ajout,
				                  GTK_DIALOG_DESTROY_WITH_PARENT,
				                  GTK_MESSAGE_INFO,
				                  GTK_BUTTONS_CLOSE,
				                  "La liste electorale '%s' a ete ajoute avec succes", id);
			gtk_dialog_run (GTK_DIALOG (dialog));
			gtk_widget_destroy (dialog);
		}
		else
		{
			modifier_le("le.txt", le.id, le);
			GtkWidget* dialog = gtk_message_dialog_new (le_ajout,
				                  GTK_DIALOG_DESTROY_WITH_PARENT,
				                  GTK_MESSAGE_INFO,
				                  GTK_BUTTONS_CLOSE,
				               "La liste electorale '%s' a ete modifier avec succes", id);
			gtk_dialog_run (GTK_DIALOG (dialog));
			gtk_widget_destroy (dialog);
		}
	}
}


void
on_le_modif_btn_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *le_ajout = create_le_ajout();
	GtkWidget *le_modifier = lookup_widget(button, "le_modifier");
	gtk_widget_show(le_ajout);
	gtk_widget_hide(le_modifier);
	
	le_ajout_mode = 1;
	
	GtkWidget *le_ajout_btn = lookup_widget(le_ajout, "le_ajout_addbtn");
	gtk_button_set_label(GTK_BUTTON(le_ajout_btn), "Modifier");
	
	GtkWidget *le_modif_id = lookup_widget(button, "le_modif_id");
	char* id = gtk_entry_get_text(le_modif_id);
	
	ListeElectorale existing = chercher_le("le.txt", atoi(id));
	
	GtkWidget *le_ajout_id = lookup_widget(le_ajout, "le_ajout_id");
	GtkWidget *le_ajout_id_tete = lookup_widget(le_ajout, "le_ajout_id_tete");
	GtkWidget *le_ajout_or1 = lookup_widget(le_ajout, "le_ajout_or1");
	GtkWidget *le_ajout_or2 = lookup_widget(le_ajout, "le_ajout_or2");
	GtkWidget *le_ajout_or3 = lookup_widget(le_ajout, "le_ajout_or3");
	GtkWidget *le_ajout_date_jour = lookup_widget(le_ajout, "le_ajout_date_jour");
	GtkWidget *le_ajout_date_mois = lookup_widget(le_ajout, "le_ajout_date_mois");
	GtkWidget *le_ajout_date_an = lookup_widget(le_ajout, "le_ajout_date_an");
	GtkWidget *le_ajout_nbre_candidats = lookup_widget(le_ajout, "le_ajout_nbre_candidats");
	GtkWidget *le_ajout_cand1 = lookup_widget(le_ajout, "le_ajout_cand1");
	GtkWidget *le_ajout_cand2 = lookup_widget(le_ajout, "le_ajout_cand2");
	GtkWidget *le_ajout_cand3 = lookup_widget(le_ajout, "le_ajout_cand3");
	
	char temp[50] = "";

	sprintf(temp, "%d", existing.id);
	gtk_entry_set_text(GTK_ENTRY(le_ajout_id), temp);

	sprintf(temp, "%d", existing.id_tete);
	gtk_entry_set_text(GTK_ENTRY(le_ajout_id_tete), temp);

	sprintf(temp, "%d", existing.id_candidats[0]);
	gtk_entry_set_text(GTK_ENTRY(le_ajout_cand1), temp);

	sprintf(temp, "%d", existing.id_candidats[1]);
	gtk_entry_set_text(GTK_ENTRY(le_ajout_cand2), temp);

	sprintf(temp, "%d", existing.id_candidats[2]);
	gtk_entry_set_text(GTK_ENTRY(le_ajout_cand3), temp);

	if(existing.orientation == 0)
		gtk_toggle_button_set_active(le_ajout_or1, TRUE);
	if(existing.orientation == 1)
		gtk_toggle_button_set_active(le_ajout_or2, TRUE);
	if(existing.orientation == 2)
		gtk_toggle_button_set_active(le_ajout_or3, TRUE);

	gtk_combo_box_set_active(le_ajout_nbre_candidats, existing.nbre_candidats - 1);
	gtk_spin_button_set_value(le_ajout_date_jour, existing.date.jour);
	gtk_spin_button_set_value(le_ajout_date_mois, existing.date.mois);
	gtk_spin_button_set_value(le_ajout_date_an, existing.date.an);
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


void
on_le_affichage_activate_default       (GtkWindow       *window,
                                        gpointer         user_data)
{

}

