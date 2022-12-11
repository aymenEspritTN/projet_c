#include <stdio.h>
#include <stdlib.h>
#include "bureau_de_vote.h"
#include <string.h>
#include <gtk/gtk.h>

int ajouter_bv(char * filename,BureauDeVote bv)
{
    FILE * f=fopen(filename, "a");
    if(f!=NULL)
    {
        fprintf(f,"%d %d %d %s %d %d\n",bv.id,bv.capacite_el,bv.capacite_ob,
					bv.adresse,bv.id_agent,bv.salle);
        fclose(f);
        return 1;
    }
    else return 0;
}

int modifier_bv( char *filename, int id, BureauDeVote nouv )
{
    int tr=0;
    BureauDeVote bv;
    FILE * f=fopen(filename, "r");
    FILE * f2=fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%d %d %d %s %d %d",&bv.id,&bv.capacite_el,&bv.capacite_ob,
                                            bv.adresse,&bv.id_agent,&bv.salle)!=EOF)
        {
            if(bv.id== id)
            {
                fprintf(f2,"%d %d %d %s %d %d\n",nouv.id,nouv.capacite_el,nouv.capacite_ob,
					nouv.adresse,nouv.id_agent,nouv.salle);
                tr=1;
            }
            else
                fprintf(f2,"%d %d %d %s %d %d\n",bv.id,bv.capacite_el,bv.capacite_ob,
					       bv.adresse,bv.id_agent,bv.salle);

        }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return tr;

}

int supprimer_bv(char *filename, int id)
{
    int tr=0;
    BureauDeVote bv;
    FILE * f=fopen(filename, "r");
    FILE * f2=fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%d %d %d %s %d %d",&bv.id,&bv.capacite_el,&bv.capacite_ob,
                                            bv.adresse,&bv.id_agent,&bv.salle)!=EOF)
        {
            if(bv.id== id)
                tr=1;
            else
                fprintf(f2,"%d %d %d %s %d %d\n",bv.id,bv.capacite_el,bv.capacite_ob,
					       bv.adresse,bv.id_agent,bv.salle);
        }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return tr;
}

BureauDeVote chercher_bv(char *filename, int id)
{
    BureauDeVote bv;
    int tr=0;
    FILE * f=fopen(filename, "r");
    if(f!=NULL)
    {
        while(tr==0&& fscanf(f,"%d %d %d %s %d %d",&bv.id,&bv.capacite_el,&bv.capacite_ob,
                                            bv.adresse,&bv.id_agent,&bv.salle)!=EOF)
        {
            if(bv.id== id)
                tr=1;
        }
    }
    fclose(f);
    if(tr==0)
        bv.id=-1;
    return bv;

}

enum
{
   Id,
   Capacite_el,
   Capacite_ob,
   Adresse,
   Id_agent,
   Salle,
   COLUMNS
};
void affiche_bv(GtkWidget *liste)
{
  BureauDeVote bv;
  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;
  GtkTreeIter iter;
  GtkListStore *store;
  
  int id;
  int capacite_el;
  int capacite_ob;
  char adresse[40];
  int id_agent;
  int salle;
  store=NULL;

FILE *f;
store=gtk_tree_view_get_model(liste);
if(store==NULL)
{
renderer=gtk_cell_renderer_text_new();   
column=gtk_tree_view_column_new_with_attributes("id",renderer,"text",Id,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();   column=gtk_tree_view_column_new_with_attributes("capacite_el",renderer,"text",Capacite_el,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();   column=gtk_tree_view_column_new_with_attributes("capacite_ob",renderer,"text",Capacite_ob,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();   
column=gtk_tree_view_column_new_with_attributes("adresse",renderer,"text",Adresse,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();   
column=gtk_tree_view_column_new_with_attributes("id_agent",renderer,"text",Id_agent,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();   
column=gtk_tree_view_column_new_with_attributes("salle",renderer,"text",Salle,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

store=gtk_list_store_new(COLUMNS,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT);

f=fopen("bv.txt","r");
if(f==NULL)
{
 return;
}
else
{f=fopen("bv.txt","a+");
  while(fscanf(f,"%d %d %d %s %d %d",&bv.id,&bv.capacite_el,&bv.capacite_ob,bv.adresse,&bv.id_agent,&bv.salle)!=EOF)
{ 
gtk_list_store_append(store,&iter);
gtk_list_store_set(store, &iter, Id, bv.id, Capacite_el, bv.capacite_el, Capacite_ob, bv.capacite_ob, Adresse, bv.adresse, Id_agent, bv.id_agent, Salle, bv.salle, -1);
}
fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL (store));
g_object_unref(store);
gtk_tree_view_set_enable_search(GTK_TREE_VIEW(liste),TRUE);
}
}}



int test(char *filename, int id)
{
    BureauDeVote bv;
    int a=1;
    FILE * f=fopen(filename, "r");
    if(f!=NULL)
    {
        while(a==1 && fscanf(f,"%d %d %d %s %d %d",&bv.id,&bv.capacite_el,&bv.capacite_ob,bv.adresse,&bv.id_agent,&bv.salle)!=EOF)
        {
            if(bv.id== id)
                a=0;
        }
    }
    fclose(f);
    return a;

}

int ajouter2_bv(char * filename,BureauDeVote bv)
{
    FILE * f=fopen(filename, "w");
    if(f!=NULL)
    {
        fprintf(f,"%d %d %d %s %d %d\n",bv.id,bv.capacite_el,bv.capacite_ob,
					bv.adresse,bv.id_agent,bv.salle);
        fclose(f);
        return 1;
    }
    else return 0;
}


void affiche2_bv(GtkWidget *liste)
{
  BureauDeVote bv;
  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;
  GtkTreeIter iter;
  GtkListStore *store;
  
  int id;
  int capacite_el;
  int capacite_ob;
  char adresse[40];
  int id_agent;
  int salle;
  store=NULL;

FILE *f;
store=gtk_tree_view_get_model(liste);
if(store==NULL)
{
renderer=gtk_cell_renderer_text_new();   
column=gtk_tree_view_column_new_with_attributes("id",renderer,"text",Id,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();   column=gtk_tree_view_column_new_with_attributes("capacite_el",renderer,"text",Capacite_el,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();   column=gtk_tree_view_column_new_with_attributes("capacite_ob",renderer,"text",Capacite_ob,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();   
column=gtk_tree_view_column_new_with_attributes("adresse",renderer,"text",Adresse,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();   
column=gtk_tree_view_column_new_with_attributes("id_agent",renderer,"text",Id_agent,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();   
column=gtk_tree_view_column_new_with_attributes("salle",renderer,"text",Salle,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

store=gtk_list_store_new(COLUMNS,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT);

f=fopen("bv2.txt","r");
if(f==NULL)
{
 return;
}
else
{f=fopen("bv2.txt","a+");
  while(fscanf(f,"%d %d %d %s %d %d",&bv.id,&bv.capacite_el,&bv.capacite_ob,bv.adresse,&bv.id_agent,&bv.salle)!=EOF)
{ 
gtk_list_store_append(store,&iter);
gtk_list_store_set(store, &iter, Id, bv.id, Capacite_el, bv.capacite_el, Capacite_ob, bv.capacite_ob, Adresse, bv.adresse, Id_agent, bv.id_agent, Salle, bv.salle, -1);
}
fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL (store));
g_object_unref(store);
gtk_tree_view_set_enable_search(GTK_TREE_VIEW(liste),TRUE);
}
}}




  
