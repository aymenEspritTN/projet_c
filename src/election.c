#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "election.h" 
#include <gtk/gtk.h>

GtkWidget *liste;

int ajouter_GE(char *filename,GestionElection GE)
{
    FILE * f=fopen(filename, "a");
    if(f!=NULL)
    {
        fprintf(f,"%d %d %d %d %s %d %s\n " ,GE.id,GE.date.jour,GE.date.mois,GE.date.an,GE.nombre_d_habitant,GE.nombre_de_conseiller,GE.municipalite);
        fclose(f);
        return 1;
    }
    else return 0;
}



int modifier_GE(int id, char * filename,GestionElection nouv)
{
    int tr=0;
    GestionElection p;
    FILE * f=fopen(filename, "r");
    FILE * f2=fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%d %d %d %d %s %d %s\n " ,&p.id,&p.date.jour,&p.date.mois,&p.date.an,p.nombre_d_habitant,&p.nombre_de_conseiller,p.municipalite)!=EOF)
        {
            if(p.id==id)
            {
                fprintf(f2,"%d %d %d %d %s %d %s\n ",nouv.id,nouv.date.jour,nouv.date.mois,nouv.date.an,nouv.nombre_d_habitant,nouv.nombre_de_conseiller, nouv.municipalite);
                tr=1;
            }
            else
                fprintf(f2,"%d %d %d %d %s %d %s\n ",p.id,p.date.jour,p.date.mois,p.date.an,p.nombre_d_habitant,p.nombre_de_conseiller,p.municipalite);

        }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return tr;
}

int supprimer_GE(int id, char * filename)
{
    int tr=0;
    GestionElection p;
    FILE * f=fopen(filename, "r");
    FILE * f2=fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%d %d %d %d %s %d %s\n " ,&p.id,&p.date.jour,&p.date.mois,&p.date.an,p.nombre_d_habitant,&p.nombre_de_conseiller,p.municipalite)!=EOF)
        {
            if(p.id==id)
                tr=1;
            else
                fprintf(f2,"%d %d %d %d %s %d %s\n",p.id,p.date.jour,p.date.mois,p.date.an,p.nombre_d_habitant,p.nombre_de_conseiller,p.municipalite);
        }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return tr;
}


GestionElection chercher_Ge(int id, char * filename)
{
    GestionElection p;
    int tr=0;
    FILE * f=fopen(filename, "r");
    if(f!=NULL)
    {
        while(tr==0&& fscanf(f,"%d %d %d %d %s %d %s\n ",&p.id,&p.date.jour,&p.date.mois,&p.date.an,p.nombre_d_habitant,&p.nombre_de_conseiller,p.municipalite)!=EOF)
        {
             if(p.id==id)
                tr=1;
        }
    }
    fclose(f);
    if(tr==0)
        p.id=-1;
    return p;

}


enum
{
   Id,
   Date_de_creation,	
   Nombre_d_habitant,
   Nombre_de_conseiller,
   Municipalite,
   COLUMNS
};


void affiche_ge(GtkWidget *liste, char *id1)
{
  GestionElection ge;
  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;
  GtkTreeIter iter;
  GtkListStore *store;
  char var1[20],var2[20];
  int id;
  Date date;
  char nombre_d_habitant;
  int nombre_de_conseiller;
  char municipalite[20];
  store=NULL;

FILE *f;
store=gtk_tree_view_get_model(liste);
if(store==NULL)
{
renderer=gtk_cell_renderer_text_new();   column=gtk_tree_view_column_new_with_attributes("id",renderer,"text",Id,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


renderer=gtk_cell_renderer_text_new();   column=gtk_tree_view_column_new_with_attributes("date",renderer,"text",Date_de_creation,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();   column=gtk_tree_view_column_new_with_attributes("nombre_d_habitant",renderer,"text",Nombre_d_habitant,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();   column=gtk_tree_view_column_new_with_attributes("nombre_de_conseiller",renderer,"text",Nombre_de_conseiller,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();   column=gtk_tree_view_column_new_with_attributes("municipalite",renderer,"text",Municipalite,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


store=gtk_list_store_new(COLUMNS,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_STRING);

if (strcmp(id1,"")==0)
{
f=fopen("ge.txt","r");
if(f==NULL)
{
 return;
}
else
{f=fopen("ge.txt","a+");
  while(fscanf(f,"%d %d %d %d %s %d %s\n ",&ge.id,&ge.date.jour,&ge.date.mois,&ge.date.an,ge.nombre_d_habitant,&ge.nombre_de_conseiller,ge.municipalite)!=EOF)
{ 


sprintf(var2,"%d / %d / %d",ge.date.jour,ge.date.mois,ge.date.an);

gtk_list_store_append(store,&iter);
gtk_list_store_set(store, &iter, Id,ge.id,Date_de_creation,var2,Nombre_d_habitant,ge.nombre_d_habitant,Nombre_de_conseiller,ge.nombre_de_conseiller,Municipalite,
ge.municipalite,-1);
}
fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL (store));
g_object_unref(store);

}
}
else{
f=fopen("ge.txt","r");
if(f!=NULL)
{ f = fopen("ge.txt","a+");
		while(fscanf(f,"%d %d %d %d %s %d %s\n ",&ge.id,&ge.date.jour,&ge.date.mois,&ge.date.an,ge.nombre_d_habitant,&ge.nombre_de_conseiller,ge.municipalite)!=EOF)
	{
if(ge.id==atoi(id1)){

sprintf(var2,"%d / %d / %d",ge.date.jour,ge.date.mois,ge.date.an);

gtk_list_store_append(store,&iter);
gtk_list_store_set(store, &iter, Id,ge.id,Date_de_creation,var2,Nombre_d_habitant,ge.nombre_d_habitant,Nombre_de_conseiller,ge.nombre_de_conseiller,Municipalite,
ge.municipalite,-1);
}
	}
	fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
g_object_unref(store);
}
}
gtk_tree_view_set_reorderable(GTK_TREE_VIEW(liste),TRUE);
gtk_tree_view_set_rules_hint(GTK_TREE_VIEW(liste),TRUE);
gtk_tree_view_set_enable_search(GTK_TREE_VIEW(liste),TRUE);
gtk_tree_view_set_search_column(GTK_TREE_VIEW(liste),0);
gtk_tree_view_set_enable_tree_lines(GTK_TREE_VIEW(liste),TRUE);
gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(liste),GTK_TREE_VIEW_GRID_LINES_BOTH);

}
}




