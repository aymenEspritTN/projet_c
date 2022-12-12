#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "liste_electorale.h"
#include "bureau_de_vote.h"
#include "election.h"
#include "user.h"

//0 = AJOUT, 1 = MODIFIER
int le_ajout_mode = 0;
int bv_ajout_mode=0;
int ge_ajout_mode = 0;

char* id_modifie; 

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void
on_btn_statistics_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *next = create_statistics();
	GtkWidget *curr = lookup_widget(button, "gestion_entry");
	gtk_widget_show(next);
	gtk_widget_hide(curr);
}

void
on_le_btn_vote_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *le_vote = create_le_vote();
	GtkWidget *le = lookup_widget(button, "le");
	gtk_widget_show(le_vote);
	gtk_widget_hide(le);
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
	
	GtkWidget *le_supprimer = create_le_supprimer();
	GtkWidget *le = lookup_widget(button, "le");
	gtk_widget_show(le_supprimer);
	gtk_widget_hide(le);
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
		
		sprintf(_id_candidats, "%d, %d, %d",
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
	
	if( strcmp(query, "")==0 )
	{
		int i=0;
		for(i=0; i<n; i++)
		{
			found[found_n] = t[i];
			found_n++;
		}
	}
	else
	{
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
	}
	
	
	GtkWidget* le_affichage = lookup_widget(liste, "le_affichage");
	if(found_n == 0)
	{
		GtkWidget* dialog = gtk_message_dialog_new (le_affichage,
		                          GTK_DIALOG_DESTROY_WITH_PARENT,
		                          GTK_MESSAGE_INFO,
		                          GTK_BUTTONS_CLOSE,
		                          "Aucun resultat trouve");
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
	}

	treeview_vider(liste);
	treeview_remplir(liste, found, found_n);
}




void
on_le_aff_search_btn_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *inp = lookup_widget(button, "le_aff_search");
	GtkWidget *le_aff_treeview = lookup_widget(button, "le_aff_treeview");
	char* query = gtk_entry_get_text(inp);
	treeview_search(le_aff_treeview, query);
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
	char* id_tete = gtk_entry_get_text(le_ajout_id_tete);
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
	char* nbre_candidats = gtk_combo_box_get_active_text(le_ajout_nbre_candidats);
	
	if(gauche)orientation = 0; else if(mid)orientation = 1; else if(droit)orientation = 2;

	ListeElectorale le;
	le.id = atoi(id);
	le.orientation = orientation;
	le.date.jour = jour;
	le.date.mois = mois;
	le.date.an = an;
	le.id_tete = atoi(id_tete);
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

	if(nbre_candidats==NULL)
	{
		strcat(error, "Veuillez selectionner un nombre de candidats.\n");	
	}
	else
	{
		le.nbre_candidats = atoi(nbre_candidats);
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
	
	GtkWidget *le_modifier = lookup_widget(button, "le_modifier");
	GtkWidget *le_modif_id = lookup_widget(button, "le_modif_id");
	char* id = gtk_entry_get_text(le_modif_id);
	ListeElectorale existing = chercher_le("le.txt", atoi(id));
	if(existing.id == -1)
	{
		GtkWidget* dialog = gtk_message_dialog_new (le_modifier,
			                  GTK_DIALOG_DESTROY_WITH_PARENT,
			                  GTK_MESSAGE_ERROR,
			                  GTK_BUTTONS_CLOSE,
			                  "Id est invalide ou n'existe pas.");
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
		return;
	}

	GtkWidget *le_ajout = create_le_ajout();
	gtk_widget_show(le_ajout);
	gtk_widget_hide(le_modifier);
	
	le_ajout_mode = 1;
	
	GtkWidget *le_ajout_btn = lookup_widget(le_ajout, "le_ajout_addbtn");
	gtk_button_set_label(GTK_BUTTON(le_ajout_btn), "Modifier");
	
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

void voter(GtkWidget* button)
{
	GtkWidget* le_vote = lookup_widget(button, "le_vote");
	GtkWidget* le_vote_id_liste = lookup_widget(button, "le_vote_id_liste");
	GtkWidget* le_vote_id_user = lookup_widget(button, "le_vote_id_user");
	char* id_liste = gtk_entry_get_text(le_vote_id_liste);
	char* id_user = gtk_entry_get_text(le_vote_id_user);

	/*User existing_user = chercher_user("user.txt", id_user);
	if(existing_user.id == -1)
	{
		GtkWidget* dialog = gtk_message_dialog_new (le_vote,
			                  GTK_DIALOG_DESTROY_WITH_PARENT,
			                  GTK_MESSAGE_ERROR,
			                  GTK_BUTTONS_CLOSE,
			                  "Id _Utilisateur_ est invalide ou n'existe pas.");
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
		return;
	}
	User existing_le = chercher_user("le.txt", id_liste);
	if(existing_le.id == -1)
	{
		GtkWidget* dialog = gtk_message_dialog_new (le_vote,
			                  GTK_DIALOG_DESTROY_WITH_PARENT,
			                  GTK_MESSAGE_ERROR,
			                  GTK_BUTTONS_CLOSE,
			                  "Id ListeElectorale est invalide ou n'existe pas.");
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
		return;
	}
	existing_user.vote = atoi(id_liste);*/
	
	GtkWidget* dialog = gtk_message_dialog_new (le_vote,
		                  GTK_DIALOG_DESTROY_WITH_PARENT,
		                  GTK_MESSAGE_INFO,
		                  GTK_BUTTONS_CLOSE,
		                  "Vote bien recue. Merci.");
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);
}

void
on_le_btn_vote_valider_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
	voter(button);
}


void
on_le_vote_blanche_btn_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget* le_vote_id_liste = lookup_widget(button, "le_vote_id_liste");
	gtk_entry_set_text(le_vote_id_liste, "-1");
	voter(button);
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
	GtkWidget *auth = create_auth();
	GtkWidget *gestion_entry = lookup_widget(button, "gestion_entry");
	gtk_widget_show(auth);
	gtk_widget_hide(gestion_entry);
}



void
on_le_affichage_activate_default       (GtkWindow       *window,
                                        gpointer         user_data)
{

}


void
on_auth_btn_login_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *auth = lookup_widget(button, "auth");
	GtkWidget *auth_id = lookup_widget(button, "auth_id");
	GtkWidget *auth_pass = lookup_widget(button, "auth_pass");
	char* login = gtk_entry_get_text(auth_id);
	char* password = gtk_entry_get_text(auth_pass);
	
	//user exists = get_user_by_account("user.txt", login, password);
	User exists;
	exists.cin = -1;
	if(strcmp(login, "9999")==0 && strcmp(password, "0000")==0)
	{
		exists.cin = 99999999;
		exists.role = admin;
	}

	if(exists.cin == -1)
	{
		GtkWidget* dialog = gtk_message_dialog_new (auth,
		                          GTK_DIALOG_DESTROY_WITH_PARENT,
		                          GTK_MESSAGE_INFO,
		                          GTK_BUTTONS_CLOSE,
		                          "Erreur: nom de compte ou mot de passe invalide.");
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
	}
	else
	{
		if(exists.role != admin)
		{
			GtkWidget* dialog = gtk_message_dialog_new (auth,
				                  GTK_DIALOG_DESTROY_WITH_PARENT,
				                  GTK_MESSAGE_INFO,
				                  GTK_BUTTONS_CLOSE,
				                  "Compte n'est pas admin.\nVous ne pouver pas acceder.");
			gtk_dialog_run (GTK_DIALOG (dialog));
			gtk_widget_destroy (dialog);
		}
		else
		{
			GtkWidget *gestion_admin = create_gestion_admin();
			gtk_widget_show(gestion_admin);
			gtk_widget_hide(auth);
		}
	}
}


void
on_le_supp_btn_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *le_supprimer = lookup_widget(button, "le_supprimer");
	GtkWidget *le_supp_id = lookup_widget(le_supprimer, "le_supp_id");
	char* id = gtk_entry_get_text(le_supp_id);
	ListeElectorale existing = chercher_le("le.txt", atoi(id));
	if(existing.id == -1)
	{
		GtkWidget* dialog = gtk_message_dialog_new (le_supprimer,
			                  GTK_DIALOG_DESTROY_WITH_PARENT,
			                  GTK_MESSAGE_WARNING,
			                  GTK_BUTTONS_CLOSE,
			                  "Id est invalide ou n'existe pas.");
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
		return;
	}
	GtkWidget *confirm_dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL,
							GTK_MESSAGE_QUESTION,
							GTK_BUTTONS_OK_CANCEL,
							"Es-tu sûr de vouloir faire ça?");

	int result = gtk_dialog_run(GTK_DIALOG(confirm_dialog));
	gtk_widget_destroy (confirm_dialog);

	if (result == GTK_RESPONSE_OK)
	{
		supprimer_le("le.txt", existing.id);
		GtkWidget* dialog = gtk_message_dialog_new (le_supprimer,
			                  GTK_DIALOG_DESTROY_WITH_PARENT,
			                  GTK_MESSAGE_INFO,
			                  GTK_BUTTONS_CLOSE,
			                  "Supprimer avec succes!");
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
	}
}


void
on_gestion_entry_realize               (GtkWidget       *widget,
                                        gpointer         user_data)
{
	GtkWidget* title = lookup_widget(widget, "gestion_entry_title");
	PangoFontDescription *df = pango_font_description_new();
	pango_font_description_set_size(df,24*PANGO_SCALE);
	gtk_widget_modify_font(title, df);
	gtk_label_set_markup(GTK_LABEL(title), "Gestion Election");
	pango_font_description_free (df);
	//GtkWidget* loading_window = create_loading_window(); gtk_widget_show(loading_window);
}


void
on_le_btn_ret_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *back = create_gestion_entry();
	GtkWidget *current = lookup_widget(button, "le");
	gtk_widget_show(back);
	gtk_widget_hide(current);
}


void
on_le_ajout_btn_ret_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *back = create_le();
	GtkWidget *current = lookup_widget(button, "le_ajout");
	gtk_widget_show(back);
	gtk_widget_hide(current);
}


void
on_le_supp_btn_ret_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *back = create_le();
	GtkWidget *current = lookup_widget(button, "le_supprimer");
	gtk_widget_show(back);
	gtk_widget_hide(current);
}


void
on_le_modif_btn_ret_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *back = create_le();
	GtkWidget *current = lookup_widget(button, "le_modifier");
	gtk_widget_show(back);
	gtk_widget_hide(current);
}


void
on_le_aff_btn_ret_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *back = create_le();
	GtkWidget *current = lookup_widget(button, "le_affichage");
	gtk_widget_show(back);
	gtk_widget_hide(current);
}


void
on_le_vote_btn_ret_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *back = create_le();
	GtkWidget *current = lookup_widget(button, "le_vote");
	gtk_widget_show(back);
	gtk_widget_hide(current);
}


void
on_auth_btn_ret_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *back = create_gestion_entry();
	GtkWidget *current = lookup_widget(button, "auth");
	gtk_widget_show(back);
	gtk_widget_hide(current);
}

void
on_gestion_admin_btn_ret_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *back = create_auth();
	GtkWidget *current = lookup_widget(button, "gestion_admin");
	gtk_widget_show(back);
	gtk_widget_hide(current);
}


void
on_btn_gest_user_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *next = create_user();
	GtkWidget *curr = lookup_widget(button, "gestion_admin");
	gtk_widget_show(next);
	gtk_widget_hide(curr);
}


void
on_btn_gest_bv_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *bv = create_bv();
	GtkWidget *gestion_admin = lookup_widget(button, "gestion_admin");
	gtk_widget_show(bv);
	gtk_widget_hide(gestion_admin);
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
on_btn_gest_ge_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{

	GtkWidget *next = create_ge();
	GtkWidget *curr = lookup_widget(button, "gestion_admin");
	gtk_widget_show(next);
	gtk_widget_hide(curr);
}

void close_loading(gpointer data)
{
	GtkWidget *next = create_gestion_entry();
	GtkWidget *myself = lookup_widget(data, "loading_window");
	gtk_widget_show(next);
	gtk_widget_destroy(myself);
}

void
on_loading_window_realize              (GtkWidget       *widget,
                                        gpointer         user_data)
{
	gtk_timeout_add(5000, close_loading, widget);
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////



void
on_user_btn_ret_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *next = create_gestion_admin();
	GtkWidget *curr = lookup_widget(button, "user");
	gtk_widget_show(next);
	gtk_widget_hide(curr);
}


void
on_button73_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////



void
on_ge_btn_ret_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *next = create_gestion_admin();
	GtkWidget *curr = lookup_widget(button, "ge");
	gtk_widget_show(next);
	gtk_widget_hide(curr);
}


void
on_ge_ajout_btn_ret_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *next = create_ge();
	GtkWidget *curr = lookup_widget(button, "ge_ajouter");
	gtk_widget_show(next);
	gtk_widget_hide(curr);
}


void
on_ge_modif_btn_ret_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *next = create_ge();
	GtkWidget *curr = lookup_widget(button, "ge_modifier");
	gtk_widget_show(next);
	gtk_widget_hide(curr);
}


void
on_ge_supp_btn_ret_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *next = create_ge();
	GtkWidget *curr = lookup_widget(button, "ge_supprimer");
	gtk_widget_show(next);
	gtk_widget_hide(curr);
}


void
on_ge_aff_btn_ret_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *next = create_ge();
	GtkWidget *curr = lookup_widget(button, "ge_affichier");
	gtk_widget_show(next);
	gtk_widget_hide(curr);
}
void
on_butAjou_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *GE_ajouter = lookup_widget(button, "GE_ajouter");
	GtkWidget *ge_entryId = lookup_widget(button, "ge_entryId");
	GtkWidget *ge_spinbutJour = lookup_widget(button, "ge_spinbutJour");
	GtkWidget *ge_spinbutMois = lookup_widget(button, "ge_spinbutMois");
	GtkWidget *ge_spinbutAnnee = lookup_widget(button, "ge_spinbutAnnee");

	GtkWidget *radiobtn5000 = lookup_widget(button, "radiobtn5000");
	GtkWidget *radiobtn10000 = lookup_widget(button, "radiobtn10000");
	GtkWidget *radiobtn25000 = lookup_widget(button, "radiobtn25000");
	GtkWidget *radiobtn50000 = lookup_widget(button, "radiobtn50000");
	GtkWidget *radiobtn100000 = lookup_widget(button, "radiobtn100000");
	GtkWidget *radiobtn500000 = lookup_widget(button, "radiobtn500000");
	GtkWidget *radiobtn__500000= lookup_widget(button, "radiobtn__500000");
	GtkWidget *ge_entryNbc= lookup_widget(button, "ge_entryNbc");
	GtkWidget *ge_combo_muni= lookup_widget(button, "ge_combo_muni");
	GtkWidget *ge_robot = lookup_widget(button, "ge_robot");

	
	
	char* id1 = gtk_entry_get_text(ge_entryId);
	
	int jour = gtk_spin_button_get_value_as_int(ge_spinbutJour);
	int mois = gtk_spin_button_get_value_as_int(ge_spinbutMois);
	int annee = gtk_spin_button_get_value_as_int(ge_spinbutAnnee);



	
	
	int radio5000 = gtk_toggle_button_get_active(GTK_RADIO_BUTTON(radiobtn5000));
	int radio10000 = gtk_toggle_button_get_active(GTK_RADIO_BUTTON(radiobtn10000));
	int radio25000 = gtk_toggle_button_get_active(GTK_RADIO_BUTTON(radiobtn25000));
	int radio50000 = gtk_toggle_button_get_active(GTK_RADIO_BUTTON(radiobtn50000));
	int radio100000 = gtk_toggle_button_get_active(GTK_RADIO_BUTTON(radiobtn100000));
	int radio500000 = gtk_toggle_button_get_active(GTK_RADIO_BUTTON(radiobtn500000));
	int radio__500000 = gtk_toggle_button_get_active(GTK_RADIO_BUTTON(radiobtn__500000));
	
	
	int id2  = atoi (id1);
	int robotCheck = gtk_toggle_button_get_active(GTK_CHECK_BUTTON(ge_robot));
	char* municipalite = gtk_combo_box_get_active_text(ge_combo_muni);
	
	char error[100];
	strcpy(error," ");

	GestionElection ge;
	ge.id=id2;
	
	ge.date.jour = jour;
	ge.date.mois = mois;
	ge.date.an = annee;
	
	if (radio5000==1)
		{strcpy(ge.nombre_d_habitant,"jusqu_a_5000");
		ge.nombre_de_conseiller=10;
		gtk_entry_set_text(GTK_ENTRY(ge_entryNbc),"10");
		}
	else if (radio10000==1)
		{strcpy(ge.nombre_d_habitant,"de_5001_a_10000");;
		ge.nombre_de_conseiller=12;
		gtk_entry_set_text(GTK_ENTRY(ge_entryNbc),"12");
		}
	else if (radio25000==1)
		{strcpy(ge.nombre_d_habitant,"de_10001_a_25000");
		ge.nombre_de_conseiller=16;
		gtk_entry_set_text(GTK_ENTRY(ge_entryNbc),"16");
		}
	else if (radio50000==1)
		{strcpy(ge.nombre_d_habitant,"de25001_a_50000");
		ge.nombre_de_conseiller=22;
		gtk_entry_set_text(GTK_ENTRY(ge_entryNbc),"22");
		}
	else if (radio100000==1)
		{strcpy(ge.nombre_d_habitant,"de_50001_a_100000");
		ge.nombre_de_conseiller=30;
		gtk_entry_set_text(GTK_ENTRY(ge_entryNbc),"30");
		}
	
	else if (radio500000==1)
		{strcpy(ge.nombre_d_habitant,"de_100001_a_500000");
		ge.nombre_de_conseiller=40;
		gtk_entry_set_text(GTK_ENTRY(ge_entryNbc),"40");
		}
	
	else if (radio__500000==1)
		{strcpy(ge.nombre_d_habitant,"plus_que_500000");
		ge.nombre_de_conseiller=60;		
		gtk_entry_set_text(GTK_ENTRY(ge_entryNbc),"60");
		}
			
	GestionElection testid=chercher_Ge(id2,"ge.txt");
	strcpy(ge.municipalite,municipalite);
	if (strlen(municipalite)==0)
	{
		strcat(error,"veuillez choisir une municipalite\n");
	}
		
	if(robotCheck == 0)
	{
		strcat(error, "verifiez que vous n'etes pas un robot\n");
	}
	else if(strlen(id1)!=8)
		{
		strcat(error,"la taille de l id est invalide\n");
		}
	else if ((testid.id) != -1)
	{
		strcat(error,"election existante\n");
	}
	else if ((strlen(id1)==8)&&((testid.id)==-1)&&(robotCheck == 1)&&(strlen(municipalite)!=0))
	{
		ajouter_GE("ge.txt", ge);
		strcat(error,"election ajoutee avec succes\n");			
	}

	GtkWidget* dialog = gtk_message_dialog_new (GE_ajouter,
                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                  GTK_MESSAGE_INFO,
                                  GTK_BUTTONS_CLOSE,error);
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);
	if(strlen(error)>0)
	{
		GtkWidget* dialog = gtk_message_dialog_new (GE_ajouter,
		                          GTK_DIALOG_DESTROY_WITH_PARENT,
		                          GTK_MESSAGE_INFO,
		                          GTK_BUTTONS_CLOSE,
		                          error);
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
	}
	else
	{
		if(ge_ajout_mode == 0)
		{
			ajouter_GE("ge.txt",ge);
			GtkWidget* dialog = gtk_message_dialog_new (GE_ajouter,
				                  GTK_DIALOG_DESTROY_WITH_PARENT,
				                  GTK_MESSAGE_INFO,
				                  GTK_BUTTONS_CLOSE,
				                  "Election '%d' a ete ajoute avec succes",id2);
			gtk_dialog_run (GTK_DIALOG (dialog));
			gtk_widget_destroy (dialog);
		}
		else
		{
			modifier_GE(ge.id,"ge.txt",ge);
			GtkWidget* dialog = gtk_message_dialog_new (GE_ajouter,
				                  GTK_DIALOG_DESTROY_WITH_PARENT,
				                  GTK_MESSAGE_INFO,
				                  GTK_BUTTONS_CLOSE,
				               "Election '%d' a ete modifiee avec succes", id2);
			gtk_dialog_run (GTK_DIALOG (dialog));
			gtk_widget_destroy (dialog);
		}
	}
}


void
on_ge_modif_btn_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
	char error[100];
	char tmp[50]="";
	GtkWidget *GE_ajouter = create_ge_ajouter();
	GtkWidget *GE_modifier = lookup_widget(button, "GE_modifier");
	gtk_widget_show(GE_ajouter);
	gtk_widget_hide(GE_modifier);
	ge_ajout_mode=1;
	GtkWidget *butAjouGE = lookup_widget(GE_ajouter, "butAjouGE");
	gtk_button_set_label(GTK_BUTTON(butAjouGE), "Modifier");
	
	
	GtkWidget *ge_entrymodifier=lookup_widget(button, "ge_entrymodifier");
	char* id = gtk_entry_get_text(ge_entrymodifier);
	
	GestionElection exist =chercher_Ge(atoi(id),"ge.txt");
	GtkWidget *ge_entryId = lookup_widget(GE_ajouter, "ge_entryId");
	GtkWidget *ge_spinbutJour = lookup_widget(GE_ajouter, "ge_spinbutJour");
	GtkWidget *ge_spinbutMois = lookup_widget(GE_ajouter, "ge_spinbutMois");
	GtkWidget *ge_spinbutAnnee = lookup_widget(GE_ajouter, "ge_spinbutAnnee");

	GtkWidget *radiobtn5000 = lookup_widget(GE_ajouter, "radiobtn5000");
	GtkWidget *radiobtn10000 = lookup_widget(GE_ajouter, "radiobtn10000");
	GtkWidget *radiobtn25000 = lookup_widget(GE_ajouter, "radiobtn25000");
	GtkWidget *radiobtn50000 = lookup_widget(GE_ajouter, "radiobtn50000");
	GtkWidget *radiobtn100000 = lookup_widget(GE_ajouter, "radiobtn100000");
	GtkWidget *radiobtn500000 = lookup_widget(GE_ajouter, "radiobtn500000");
	GtkWidget *radiobtn__500000= lookup_widget(GE_ajouter, "radiobtn__500000");
	GtkWidget *ge_entryNbc= lookup_widget(GE_ajouter, "ge_entryNbc");
	GtkWidget *ge_combo_muni= lookup_widget(GE_ajouter, "ge_combo_muni");
	
	sprintf(tmp, "%d", exist.id);
	gtk_entry_set_text(GTK_ENTRY(ge_entryId),tmp);
	
	gtk_spin_button_set_value((ge_spinbutJour),exist.date.jour);
			
	gtk_spin_button_set_value((ge_spinbutMois),exist.date.mois);

	gtk_spin_button_set_value((ge_spinbutAnnee),exist.date.an);

	if(strcmp(exist.municipalite,"jusqu_a_5000")==0)
	gtk_toggle_button_set_active(radiobtn5000, TRUE);
	if(strcmp(exist.municipalite,"de_5001_a_10000")==0)
	gtk_toggle_button_set_active(radiobtn10000, TRUE);
	if(strcmp(exist.municipalite,"de_10001_a_25000")==0)
	gtk_toggle_button_set_active(radiobtn25000, TRUE);
	if(strcmp(exist.municipalite,"de25001_a_50000")==0)
	gtk_toggle_button_set_active(radiobtn50000, TRUE);
	if(strcmp(exist.municipalite,"de_50001_a_100000")==0)
	gtk_toggle_button_set_active(radiobtn100000, TRUE);
	if(strcmp(exist.municipalite,"de_100001_a_500000")==0)
	gtk_toggle_button_set_active(radiobtn500000, TRUE);
	if(strcmp(exist.municipalite,"plus_que_500000")==0)
	gtk_toggle_button_set_active(radiobtn__500000, TRUE);

	sprintf(tmp, "%d", exist.nombre_de_conseiller);		
	gtk_entry_set_text((ge_entryNbc),tmp);

	gtk_combo_box_set_active(ge_combo_muni,exist.municipalite -1);
}


void
on_ge_supp_btn_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *GE_supprimer = lookup_widget(button, "GE_supprimer");
	GtkWidget *ge_btn_supp = lookup_widget(button, "ge_btn_supp");
	char* id1 = gtk_entry_get_text(ge_btn_supp);
	int id2 = atoi(id1);
	GestionElection test;
	test=chercher_Ge(id2,"ge.txt");
	if(test.id==-1)
	{
		GtkWidget* dialog = gtk_message_dialog_new (GE_supprimer,
                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                  GTK_MESSAGE_INFO,
                                  GTK_BUTTONS_CLOSE,
                                  "L election '%d' n existe pas", id2);
					gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
	}
	else
	{
		supprimer_GE(id2,"ge.txt");
		GtkWidget* dialog = gtk_message_dialog_new (GE_supprimer,
		                          GTK_DIALOG_DESTROY_WITH_PARENT,
		                          GTK_MESSAGE_INFO,
		                          GTK_BUTTONS_CLOSE,
		                          "L election '%d' a ete supprimee avec succes", id2);
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
	}
}


void
on_ge_btn_ajout_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *next = create_ge_ajouter();
	GtkWidget *curr = lookup_widget(button, "ge");
	gtk_widget_show(next);
	gtk_widget_hide(curr);
}


void
on_ge_btn_modif_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *next = create_ge_modifier();
	GtkWidget *curr = lookup_widget(button, "ge");
	gtk_widget_show(next);
	gtk_widget_hide(curr);
}


void
on_ge_btn_supp_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *next = create_ge_supprimer();
	GtkWidget *curr = lookup_widget(button, "ge");
	gtk_widget_show(next);
	gtk_widget_hide(curr);
}


void
on_ge_btn_aff_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *next = create_ge_affichier();
	GtkWidget *curr = lookup_widget(button, "ge");
	gtk_widget_show(next);
	gtk_widget_hide(curr);
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void
on_bv_ajout_addbtn_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
int x,y,tst,tst2;
        
	GtkWidget *bv_ajout = lookup_widget(button, "bv_ajout");
	GtkWidget *bv_ajoutid = lookup_widget(button, "bv_ajoutId");
	GtkWidget *bv_adresse= lookup_widget(button, "bv_adresse");
        GtkWidget *bv_ajout_combobox= lookup_widget(button, "bv_ajout_combobox");
	GtkWidget *bv_salle_spin = lookup_widget(button, "bv_salle_spin");
        GtkWidget *bv_ajoutidagent = lookup_widget(button, "bv_ajoutidagent");
        GtkWidget *bv_radio1 = lookup_widget(button, "bv_radio1");
        GtkWidget *bv_radio2 = lookup_widget(button, "bv_radio2");
        GtkWidget *bv_radio3 = lookup_widget(button, "bv_radio3");
        GtkWidget *bv_radio4 = lookup_widget(button, "bv_radio4");

	char* id = gtk_entry_get_text(bv_ajoutid);
	char* adresse = gtk_entry_get_text(bv_adresse);
	int capacite_el =atoi(gtk_combo_box_get_active_text(bv_ajout_combobox));
	int salle = gtk_spin_button_get_value_as_int(bv_salle_spin);
	int capacite_ob = 0;
	char* id_agent = gtk_entry_get_text(bv_ajoutidagent);
	if( gtk_toggle_button_get_active(GTK_RADIO_BUTTON(bv_radio1)))
		capacite_ob = 1;
	else if( gtk_toggle_button_get_active(GTK_RADIO_BUTTON(bv_radio2)))
		capacite_ob = 2;
        else if( gtk_toggle_button_get_active(GTK_RADIO_BUTTON(bv_radio3)))
                capacite_ob = 3;
	else if( gtk_toggle_button_get_active(GTK_RADIO_BUTTON(bv_radio4)))
		capacite_ob = 4;

	x=strlen(id);
        y=strlen(id_agent);
	BureauDeVote bv,nouv;
	bv.id = atoi(id);
	bv.capacite_el = capacite_el;
        bv.capacite_ob=capacite_ob;
        strcpy(bv.adresse,adresse);
	bv.id_agent=atoi(id_agent);
        bv.salle=salle;
	
        tst=test("bv.txt", atoi(id));
	if (bv_ajout_mode == 0)
	{
         if(x==8 && y==8 && tst==1)
         {
          ajouter_bv("bv.txt", bv);
	  GtkWidget* dialog = gtk_message_dialog_new (bv_ajout,
                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                  GTK_MESSAGE_INFO,
                                  GTK_BUTTONS_CLOSE,
                                  "Le bv '%s' a ete ajoute avec succes", id);
	  gtk_dialog_run (GTK_DIALOG (dialog));
	  gtk_widget_destroy (dialog);
          }
         else if(x==8 && y==8 && tst==0)
         {
          GtkWidget* dialog = gtk_message_dialog_new (bv_ajout,
                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                  GTK_MESSAGE_INFO,
                                  GTK_BUTTONS_CLOSE,
                                  "id deja existe");
	  gtk_dialog_run (GTK_DIALOG (dialog));
	  gtk_widget_destroy (dialog);
          }

          else
          {
          GtkWidget* dialog = gtk_message_dialog_new (bv_ajout,
                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                  GTK_MESSAGE_INFO,
                                  GTK_BUTTONS_CLOSE,
                                  "la taille du id ou id agent different de 8");
	  gtk_dialog_run (GTK_DIALOG (dialog));
	  gtk_widget_destroy (dialog);
          }
	}
         else if (bv_ajout_mode == 1)
         {
          modifier_bv("bv.txt",atoi(id),bv);
          GtkWidget* dialog = gtk_message_dialog_new (bv_ajout,
                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                  GTK_MESSAGE_INFO,
                                  GTK_BUTTONS_CLOSE,
                                  "modification avec succes");
	  gtk_dialog_run (GTK_DIALOG (dialog));
	  gtk_widget_destroy (dialog);
	}
}



void
on_bv_btn_supprimer_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
        GtkWidget *bv_supprimer = create_bv_supprimer();
	GtkWidget *bv = lookup_widget(button, "bv");
	gtk_widget_show(bv_supprimer);
	gtk_widget_hide(bv);
}


void
on_bv_btn_ajout_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *bv_ajout = create_bv_ajout();
	GtkWidget *bv = lookup_widget(button, "bv");
	gtk_widget_show(bv_ajout);
	gtk_widget_hide(bv);
        bv_ajout_mode=0;
}


void
on_bv_btn_afficher_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
        GtkWidget *bv_aff_treev;
        GtkWidget *bv_affichage = create_bv_affichage();
	GtkWidget *bv = lookup_widget(button, "bv");
	gtk_widget_show(bv_affichage);
	gtk_widget_hide(bv);
 	bv_aff_treev=lookup_widget(bv_affichage,"bv_aff_treev");
	affiche_bv(bv_aff_treev);
}


void
on_bv_btn_modifier_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *bv_modifier = create_bv_modifier();
	GtkWidget *bv = lookup_widget(button, "bv");
	gtk_widget_show(bv_modifier);
	gtk_widget_hide(bv);
	bv_ajout_mode=1;
}


void
on_bv_button_supprimer_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
	int x;
    GtkWidget *bv_supprime = lookup_widget(button, "bv_supprimer");   
    GtkWidget *bv_supprimer = lookup_widget(button, "bv_inp_supprimer");
    char* id = gtk_entry_get_text(bv_supprimer);
    x=test("bv.txt", atoi(id));
    if(x==0)
    {
    supprimer_bv("bv.txt",atoi(id));
    GtkWidget* dialog = gtk_message_dialog_new (bv_supprime,
                              GTK_DIALOG_DESTROY_WITH_PARENT,
                              GTK_MESSAGE_INFO,
                              GTK_BUTTONS_CLOSE,
                              "Le bv '%s' a ete supprimer avec succes", id);
     gtk_dialog_run (GTK_DIALOG (dialog));
     gtk_widget_destroy (dialog);
     }
     else
     {
     GtkWidget* dialog = gtk_message_dialog_new (bv_supprime,
                              GTK_DIALOG_DESTROY_WITH_PARENT,
                              GTK_MESSAGE_INFO,
                              GTK_BUTTONS_CLOSE,
                              "id n'existe pas");
     gtk_dialog_run (GTK_DIALOG (dialog));
     gtk_widget_destroy (dialog);
     }
}



void
on_bv_modif_btn_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
	int x;
	BureauDeVote bv;
        GtkWidget *bv_modifier = lookup_widget(button, "bv_modifier"); 
        GtkWidget *bv_modifie = lookup_widget(button, "bv_inp_modifier");
        char* id_modifie = gtk_entry_get_text(bv_modifie);
        
        bv=chercher_bv("bv.txt",atoi(id_modifie));
        x=test("bv.txt", atoi(id_modifie));
        if (x==1)
        {
	GtkWidget* dialog = gtk_message_dialog_new (bv_modifier,
                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                  GTK_MESSAGE_INFO,
                                  GTK_BUTTONS_CLOSE,
                                  "id n'existe pas");
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);
        }
        else
        {
	GtkWidget *bv_ajout = create_bv_ajout();
	gtk_widget_show(bv_ajout);
	gtk_widget_hide(bv_modifier);
        
        GtkWidget *bv_ajout_addbtn = lookup_widget(bv_ajout, "bv_ajout_addbtn");
	GtkWidget *bv_ajoutid = lookup_widget(bv_ajout, "bv_ajoutId");
	GtkWidget *bv_adresse= lookup_widget(bv_ajout, "bv_adresse");
        GtkWidget *bv_ajout_combobox= lookup_widget(bv_ajout, "bv_ajout_combobox");
	GtkWidget *bv_salle_spin = lookup_widget(bv_ajout, "bv_salle_spin");
        GtkWidget *bv_ajoutidagent = lookup_widget(bv_ajout, "bv_ajoutidagent");
        GtkWidget *bv_radio1 = lookup_widget(bv_ajout, "bv_radio1");
        GtkWidget *bv_radio2 = lookup_widget(bv_ajout, "bv_radio2");
        GtkWidget *bv_radio3 = lookup_widget(bv_ajout, "bv_radio3");
        GtkWidget *bv_radio4 = lookup_widget(bv_ajout, "bv_radio4");
        
        char temp[50];
        sprintf(temp , "%d" ,bv.id);
	gtk_entry_set_text(GTK_ENTRY(bv_ajoutid),temp);
	gtk_entry_set_text(GTK_ENTRY(bv_adresse),bv.adresse);
        sprintf(temp , "%d" ,bv.id_agent);
	gtk_entry_set_text(GTK_ENTRY(bv_ajoutidagent),temp);
        if(bv.capacite_ob == 1)
               gtk_toggle_button_set_active(bv_radio1,TRUE);
	if(bv.capacite_ob == 2)
               gtk_toggle_button_set_active(bv_radio2,TRUE);
	if(bv.capacite_ob == 3)
               gtk_toggle_button_set_active(bv_radio3,TRUE);
	if(bv.capacite_ob == 4)
               gtk_toggle_button_set_active(bv_radio4,TRUE);

	gtk_combo_box_set_active(bv_ajout_combobox,bv.capacite_el);
	gtk_spin_button_set_value(bv_salle_spin,bv.salle);
        gtk_button_set_label(GTK_BUTTON(bv_ajout_addbtn), "Modifier");
	}
}


void
on_bv_ajout_btn_ret_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *next = create_bv();
	GtkWidget *curr = lookup_widget(button, "bv_ajout");
	gtk_widget_show(next);
	gtk_widget_hide(curr);
}


void
on_bv_supp_btn_ret_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *next = create_bv();
	GtkWidget *curr = lookup_widget(button, "bv_supprimer");
	gtk_widget_show(next);
	gtk_widget_hide(curr);
}


void
on_bv_modifier_btn_ret_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *next = create_bv();
	GtkWidget *curr = lookup_widget(button, "bv_modifier");
	gtk_widget_show(next);
	gtk_widget_hide(curr);
}


void
on_bv_aff_btn_ret_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *next = create_bv();
	GtkWidget *curr = lookup_widget(button, "bv_affichage");
	gtk_widget_show(next);
	gtk_widget_hide(curr);
}


void
on_bv_btn_ret_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *next = create_gestion_admin();
	GtkWidget *curr = lookup_widget(button, "bv");
	gtk_widget_show(next);
	gtk_widget_hide(curr);
}


void
on_statistics_btn_ret_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *next = create_gestion_entry();
	GtkWidget *curr = lookup_widget(button, "statistics");
	gtk_widget_show(next);
	gtk_widget_hide(curr);
}
































void
on_button_aj_clicked                   (GtkWidget      *objet,
                                        gpointer         user_data)
{
GtkWidget *aj1, *aj2, *aj3, *aj4, *aj5, *aj6, *aj7, *aj8, *aj9, *aj10, *aj11, *aj12, *aj13, *aj14, *pInfo;
ut u;
char ch[100];
strcpy(ch, "");
aj1=lookup_widget(objet,"aj1");
aj2=lookup_widget(objet,"aj2");
aj3=lookup_widget(objet,"aj3");
aj4=lookup_widget(objet,"aj4");
aj5=lookup_widget(objet,"aj5");
aj6=lookup_widget(objet,"aj6");
aj7=lookup_widget(objet,"aj7");
aj8=lookup_widget(objet,"aj8");
aj9=lookup_widget(objet,"aj9");
aj10=lookup_widget(objet,"aj10");
aj11=lookup_widget(objet,"aj11");
aj12=lookup_widget(objet,"aj12");
aj13=lookup_widget(objet,"aj13");
aj14=lookup_widget(objet,"aj14");
bool a=gtk_toggle_button_get_active(GTK_CHECK_BUTTON(aj13));
u.cin=atoi(gtk_entry_get_text(GTK_ENTRY(aj1)));
strcpy(u.nom,gtk_entry_get_text(GTK_ENTRY(aj2)));
strcpy(u.prenom,gtk_entry_get_text(GTK_ENTRY(aj3)));
strcpy(u.email,gtk_entry_get_text(GTK_ENTRY(aj4)));
strcpy(u.pw,gtk_entry_get_text(GTK_ENTRY(aj5)));
u.bv = atoi(gtk_entry_get_text(GTK_ENTRY(aj6)));
u.sexe=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(aj7))?0:1;
u.d.jour=gtk_spin_button_get_value(GTK_SPIN_BUTTON(aj9));
u.d.mois=gtk_spin_button_get_value(GTK_SPIN_BUTTON(aj10));
u.d.an=gtk_spin_button_get_value(GTK_SPIN_BUTTON(aj11));
u.vote=gtk_spin_button_get_value(GTK_SPIN_BUTTON(aj12));
strcpy(u.role,gtk_entry_get_text(GTK_ENTRY(aj14)));

if(!Check_Email_Addr(u.email))
strcat(ch, "Email invalide\n");
if(!valid_cin(gtk_entry_get_text(GTK_ENTRY(aj1))))
strcat(ch, "CIN invalide\n");
if(!a)
strcat(ch, "Veuillez confirmer");
if(strcmp(ch,"")==0)
ajouter(u, "user.txt");
else{
pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,ch);
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
}

}


void
on_user_quit_aj_clicked                (GtkButton      *button,
                                        gpointer         user_data)
{
	GtkWidget *user;
	GtkWidget *aj;
	aj=lookup_widget(button,"aj");
	gtk_widget_destroy(aj);
	user=lookup_widget(button,"user");
	user=create_user();
	gtk_widget_show(user);
}


void
on_user_ajout_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *user;
	GtkWidget *aj;
	user=lookup_widget(button,"user");
	gtk_widget_destroy(user);
	aj=lookup_widget(button,"aj");
	aj=create_aj();
	gtk_widget_show(aj);

}


void
on_user_modifier_clicked               (GtkButton      *button,
                                        gpointer         user_data)
{

	GtkWidget *user;
	GtkWidget *modif;
	user=lookup_widget(button,"user");
	gtk_widget_destroy(user);
	modif=lookup_widget(button,"modif");
	modif=create_modif();
	gtk_widget_show(modif);
}


void
on_user_affichier_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{

	GtkWidget *user;
	GtkWidget *aff;
	user=lookup_widget(button,"user");
	gtk_widget_destroy(user);
	aff=lookup_widget(button,"aff");
	aff=create_aff();
	gtk_widget_show(aff);
	GtkWidget *treeview;
	treeview=lookup_widget(aff,"treeview");
	afficher(treeview,"user.txt", "", "", "");


}


void
on_button_mod_clicked                  (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *mod1, *mod2, *mod3, *mod4, *mod5, *mod6, *mod7, *mod8, *mod9, *mod10, *mod11, *mod12, *mod13, *mod14, *pInfo;
ut u;
mod1=lookup_widget(objet,"mod1");
mod2=lookup_widget(objet,"mod2");
mod3=lookup_widget(objet,"mod3");
mod4=lookup_widget(objet,"mod4");
mod5=lookup_widget(objet,"mod5");
mod6=lookup_widget(objet,"mod6");
mod7=lookup_widget(objet,"mod7");
mod8=lookup_widget(objet,"mod8");
mod9=lookup_widget(objet,"mod9");
mod10=lookup_widget(objet,"mod10");
mod11=lookup_widget(objet,"mod11");
mod12=lookup_widget(objet,"mod12");
mod13=lookup_widget(objet,"mod13");
mod14=lookup_widget(objet,"mod14");
u.cin=atoi(gtk_entry_get_text(GTK_ENTRY(mod1)));
strcpy(u.role,gtk_entry_get_text(GTK_ENTRY(mod14)));
strcpy(u.nom,gtk_entry_get_text(GTK_ENTRY(mod2)));
strcpy(u.prenom,gtk_entry_get_text(GTK_ENTRY(mod3)));
strcpy(u.email,gtk_entry_get_text(GTK_ENTRY(mod4)));
strcpy(u.pw,gtk_entry_get_text(GTK_ENTRY(mod5)));
u.bv = atoi(gtk_entry_get_text(GTK_ENTRY(mod6)));
u.sexe=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(mod7))?0:1;
u.d.jour=gtk_spin_button_get_value(GTK_SPIN_BUTTON(mod9));
u.d.mois=gtk_spin_button_get_value(GTK_SPIN_BUTTON(mod10));
u.d.an=gtk_spin_button_get_value(GTK_SPIN_BUTTON(mod11));
u.vote=gtk_spin_button_get_value(GTK_SPIN_BUTTON(mod12));
bool a=gtk_toggle_button_get_active(GTK_CHECK_BUTTON(mod13));
if(a)
modifier(u,"user.txt");
else{
pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"Veuillez confirmer");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
}

}


void
on_user_quit_mod_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *user;
	GtkWidget *modif;
	modif=lookup_widget(button,"modif");
	gtk_widget_destroy(modif);
	user=lookup_widget(button,"user");
	user=create_user();
	gtk_widget_show(user);

}


void
on_check_id_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *mod1, *mod2, *mod3, *mod4, *mod5, *mod6, *mod7, *mod8, *mod9, *mod10, *mod11, *mod12, *mod13, *mod14, *pInfo;
int a=0;
int id;
char bv[10], role[20];
FILE *f;
mod1=lookup_widget(objet,"mod1");
mod2=lookup_widget(objet,"mod2");
mod3=lookup_widget(objet,"mod3");
mod4=lookup_widget(objet,"mod4");
mod5=lookup_widget(objet,"mod5");
mod6=lookup_widget(objet,"mod6");
mod7=lookup_widget(objet,"mod7");
mod8=lookup_widget(objet,"mod8");
mod9=lookup_widget(objet,"mod9");
mod10=lookup_widget(objet,"mod10");
mod11=lookup_widget(objet,"mod11");
mod12=lookup_widget(objet,"mod12");
mod13=lookup_widget(objet,"mod13");
mod14=lookup_widget(objet,"mod14");
id = atoi(gtk_entry_get_text(GTK_ENTRY(mod1)));
ut p = chercher(id, "user.txt");
if(p.cin!=-1){
sprintf(bv,"%d",p.bv);
sprintf(role,"%s",p.role);
gtk_entry_set_text(GTK_ENTRY(mod2),p.nom);
gtk_entry_set_text(GTK_ENTRY(mod3),p.prenom);
gtk_entry_set_text(GTK_ENTRY(mod4),p.email);
gtk_entry_set_text(GTK_ENTRY(mod5),p.pw);
gtk_entry_set_text(GTK_ENTRY(mod6),bv);
gtk_entry_set_text(GTK_ENTRY(mod14),role);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(mod7),p.sexe==0?TRUE:FALSE);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(mod8),p.sexe==0?FALSE:TRUE);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(mod9),p.d.jour);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(mod10),p.d.mois);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(mod11),p.d.an);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(mod12),p.vote);
}
else{
pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"Utilisateur introuvable");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
}

}


void
on_treeview_row_activated              (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
	guint id;
	ut u;
	GtkWidget *pInfo, *objet, *af;
	GtkTreeModel *model=gtk_tree_view_get_model(treeview);
	if(gtk_tree_model_get_iter(model,&iter,path)){
	gtk_tree_model_get(GTK_LIST_STORE(model),&iter,0,&id,-1);
	u.cin=id;
	pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_QUESTION,GTK_BUTTONS_YES_NO,"Voulez-vous vraiment\nsupprimer cet utilisateur?");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_YES:
	gtk_widget_destroy(pInfo);
	supprimer(u,"user.txt");
	afficher(treeview,"user.txt", "", "", "");
	break;
	case GTK_RESPONSE_NO:
	gtk_widget_destroy(pInfo);
	break;
}	
}

}


void
on_button7_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *treeview, *af, *e1, *e2, *e3;
char id[10], email[50], nom[20];
af=lookup_widget(objet,"af");
treeview=lookup_widget(af,"treeview");
e1=lookup_widget(objet, "entry1");
e2=lookup_widget(objet, "entry2");
e3=lookup_widget(objet, "entry3");
strcpy(id,gtk_entry_get_text(GTK_ENTRY(e1)));
strcpy(email,gtk_entry_get_text(GTK_ENTRY(e2)));
strcpy(nom,gtk_entry_get_text(GTK_ENTRY(e3)));
afficher(treeview, "user.txt", id, email, nom);
}


void
on_button8_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *pInfo;
char *ch = age_moyen("user.txt");
pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,ch);
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
}


void
on_button9_activate                    (GtkButton      *button,
                                        gpointer         user_data)
{
GtkWidget *pInfo;
char *ch = e_bv("user.txt");
pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,ch);
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}

}


void
on_user_quit_aff_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *user;
	GtkWidget *af;
	af=lookup_widget(button,"af");
	gtk_widget_destroy(af);
	user=lookup_widget(button,"user");
	user=create_user();
	gtk_widget_show(user);

}


void
on_bv_btn_search_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
BureauDeVote bv;
    int x;
    GtkWidget *bv_affichage=create_bv_affichage();
    GtkWidget *bv_chercher = lookup_widget(button, "bv_aff_search");
    char* id = gtk_entry_get_text(bv_chercher);
    bv=chercher_bv("bv.txt", atoi(id));
    x=test("bv.txt", atoi(id));
    if(x==1 && (strlen(id)>0))
{
        GtkWidget* dialog = gtk_message_dialog_new (bv_affichage,
                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                  GTK_MESSAGE_INFO,
                                  GTK_BUTTONS_CLOSE,
                                  "id n'existe pas");
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);
}
else if(strlen(id)==0)
{    GtkWidget *bv_aff_treev;
    
    GtkWidget *W1 = lookup_widget(button, "bv_affichage");
    gtk_widget_show(bv_affichage);
    gtk_widget_hide(W1);
    bv_aff_treev=lookup_widget(bv_affichage,"bv_aff_treev");
    affiche_bv(bv_aff_treev);
}
else 
{
    ajouter2_bv("bv2.txt",bv);	
    GtkWidget *bv_aff_treev;
    
    GtkWidget *W1 = lookup_widget(button, "bv_affichage");
    gtk_widget_show(bv_affichage);
    gtk_widget_hide(W1);
    bv_aff_treev=lookup_widget(bv_affichage,"bv_aff_treev");
    affiche2_bv(bv_aff_treev);
}
}

