#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "user.h"
#include "callbacks.h"
#include <gtk/gtk.h>

enum
{
	CIN,
	NOM_PRENOM,
	EMAIL,
	BV,
	SEXE,
	VOTE,
	ROLE,
	DATE,
	COLUMNS
};


void ajouter(ut u, char *fname){
GtkWidget *pQuestion;
FILE *f;
int b=0;
gpointer user_data;
ut p;
f=fopen(fname,"a+");
if(f!=NULL)
{	
	while(fscanf(f,"%d %s %s %s %s %d %s %d %d %d %d %d\n",&(p.cin),p.nom,p.prenom,p.email,p.pw,&(p.sexe),(p.role),&(p.vote),&(p.bv),&(p.d.jour),&(p.d.mois),&(p.d.an))!=EOF)
	{	
		if(u.cin==p.cin)
		b=1;
	}
	if(b==0){
	fprintf(f,"%d %s %s %s %s %d %s %d %d %d %d %d\n",u.cin,u.nom,u.prenom,u.email,u.pw,u.sexe,u.role,u.vote,u.bv,u.d.jour,u.d.mois,u.d.an);
	}
	pQuestion=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,b==0?GTK_MESSAGE_INFO:GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,b==0?"Utilisateur ajouté avec succès !":"Utilisateur déja existant !");
	switch(gtk_dialog_run(GTK_DIALOG(pQuestion)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pQuestion);
	break;
	}
	fclose(f);
}
}

void modifier(ut u, char *fname){
ut p;
GtkWidget *pInfo;
gpointer user_data;
FILE *f, *g;
f=fopen(fname,"r");
g=fopen("dump.txt","w");
if(f==NULL||g==NULL)
{
	return;
}
else{
	while(fscanf(f,"%d %s %s %s %s %d %s %d %d %d %d %d\n",&(p.cin),p.nom,p.prenom,p.email,p.pw,&(p.sexe),(p.role),&(p.vote),&(p.bv),&(p.d.jour),&(p.d.mois),&(p.d.an))!=EOF)
	{
		if(p.cin!=u.cin)
			fprintf(g,"%d %s %s %s %s %d %s %d %d %d %d %d\n",p.cin,p.nom,p.prenom,p.email,p.pw,p.sexe,p.role,p.vote,p.bv,p.d.jour,p.d.mois,p.d.an);
		else
			fprintf(g,"%d %s %s %s %s %d %s %d %d %d %d %d\n",u.cin,u.nom,u.prenom,u.email,u.pw,u.sexe,u.role,u.vote,u.bv,u.d.jour,u.d.mois,u.d.an);
	}
	pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Utilisateur modifié avec succès !");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
	fclose(f);
	fclose(g);
remove(fname);
rename("dump.txt",fname);
}
}

void afficher(GtkWidget *liste, char *fname, char *id, char *email, char *nom)
{
ut p;
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;
gchar np[50], sexe[10], date[20];
FILE *f;
store=gtk_tree_view_get_model(liste);
renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes(" CIN", renderer,"text",CIN, NULL);
if (store==NULL)
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
gtk_tree_view_column_set_expand(column,TRUE);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes(" Nom et prénom", renderer,"text",NOM_PRENOM, NULL);
if (store==NULL)
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
gtk_tree_view_column_set_expand(column,TRUE);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes(" Email", renderer,"text",EMAIL, NULL);
if (store==NULL)
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
gtk_tree_view_column_set_resizable(column,TRUE);
gtk_tree_view_column_set_expand(column,TRUE);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes(" BV", renderer,"text",BV, NULL);
if (store==NULL)
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
gtk_tree_view_column_set_expand(column,TRUE);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes(" Sexe", renderer,"text",SEXE, NULL);
if (store==NULL)
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
gtk_tree_view_column_set_expand(column,TRUE);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes(" Vote", renderer,"text",VOTE, NULL);
if (store==NULL)
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
gtk_tree_view_column_set_expand(column,TRUE);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes(" Role", renderer,"text",ROLE, NULL);
if (store==NULL)
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
gtk_tree_view_column_set_expand(column,TRUE);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes(" Date", renderer,"text",DATE, NULL);
if (store==NULL)
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
gtk_tree_view_column_set_expand(column,TRUE);

store=gtk_list_store_new(COLUMNS, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING);
if (strcmp(id,"")==0&&strcmp(email,"")==0&&strcmp(nom,"")==0){
f=fopen(fname,"r");
if(f!=NULL)
{ f = fopen(fname,"a+");
		while(fscanf(f,"%d %s %s %s %s %d %s %d %d %d %d %d\n",&(p.cin),p.nom,p.prenom,p.email,p.pw,&(p.sexe),(p.role),&(p.vote),&(p.bv),&(p.d.jour),&(p.d.mois),&(p.d.an))!=EOF)
	{
sprintf(np, "%s %s", p.nom, p.prenom);
sprintf(date,"%d/%d/%d",p.d.jour,p.d.mois,p.d.an);
sprintf(sexe,p.sexe==0?"Homme":"Femme");
gtk_list_store_append(store,&iter);
gtk_list_store_set(store,&iter,CIN,p.cin,NOM_PRENOM,np,EMAIL,p.email,BV,p.bv,SEXE,sexe,VOTE,p.vote,ROLE,p.role,DATE,date,-1);
	}
	fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
g_object_unref(store);
}
}
else{
f=fopen(fname,"r");
if(f!=NULL)
{ f = fopen(fname,"a+");
		while(fscanf(f,"%d %s %s %s %s %d %s %d %d %d %d %d\n",&(p.cin),p.nom,p.prenom,p.email,p.pw,&(p.sexe),(p.role),&(p.vote),&(p.bv),&(p.d.jour),&(p.d.mois),&(p.d.an))!=EOF)
	{
if(p.cin==atoi(id)||strcmp(p.email,email)==0||strcmp(p.nom,nom)==0){
sprintf(np, "%s %s", p.nom, p.prenom);
sprintf(date,"%d/%d/%d",p.d.jour,p.d.mois,p.d.an);
sprintf(sexe,p.sexe==0?"Homme":"Femme");
gtk_list_store_append(store,&iter);
gtk_list_store_set(store,&iter,CIN,p.cin,NOM_PRENOM,np,EMAIL,p.email,BV,p.bv,SEXE,sexe,VOTE,p.vote,ROLE,p.role,DATE,date,-1);
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

void supprimer(ut u, char *fname)
{
ut p;
GtkWidget *pInfo;
gpointer user_data;
FILE *f, *g;
f=fopen(fname,"r");
g=fopen("dump.txt","w");
if(f!=NULL&&g!=NULL){
	while(fscanf(f,"%d %s %s %s %s %d %s %d %d %d %d %d\n",&(p.cin),p.nom,p.prenom,p.email,p.pw,&(p.sexe),(p.role),&(p.vote),&(p.bv),&(p.d.jour),&(p.d.mois),&(p.d.an))!=EOF)
	{
		if(p.cin!=u.cin)
			fprintf(g,"%d %s %s %s %s %d %s %d %d %d %d %d\n",p.cin,p.nom,p.prenom,p.email,p.pw,p.sexe,p.role,p.vote,p.bv,p.d.jour,p.d.mois,p.d.an);
	}
	pInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Utilisateur supprimé avec succès");
	switch(gtk_dialog_run(GTK_DIALOG(pInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(pInfo);
	break;
	}
	fclose(f);
	fclose(g);
remove(fname);
rename("dump.txt",fname);
}
}

ut chercher(int id, char *fname){
FILE *f;
ut p, e={cin:-1};
f=fopen(fname,"r");
if(f!=NULL)
{
	while(fscanf(f,"%d %s %s %s %s %d %s %d %d %d %d %d\n",&(p.cin),p.nom,p.prenom,p.email,p.pw,&(p.sexe),(p.role),&(p.vote),&(p.bv),&(p.d.jour),&(p.d.mois),&(p.d.an))!=EOF)
	{
	if(p.cin==id)
            return p;
	}
	fclose(f);
}
    return e;

}

char* age_moyen(char *filename){
FILE *f=fopen(filename,"r");
ut p;
int s=0, c=0;
if(f!=0){ 
             
while(fscanf(f,"%d %s %s %s %s %d %s %d %d %d %d %d\n",&(p.cin),p.nom,p.prenom,p.email,p.pw,&(p.sexe),(p.role),&(p.vote),&(p.bv),&(p.d.jour),&(p.d.mois),&(p.d.an))!=EOF)
{
      if(p.role==1&&p.vote!=-1){
	c++;
      	s+=(2022-p.d.an);
}
}
fclose(f);
 }
char *ch = malloc(50);
sprintf(ch, "Age moyen des électeurs : %d", s/c);
return ch;
}
char* e_bv(char *fname){
FILE *f;
f=fopen(fname,"r");
ut p;
int x[100][2] = {};
int b, c=0, n = 0;
char* ch = malloc(500);
char tmp[50];
strcpy(ch, "");
while(fscanf(f,"%d %s %s %s %s %d %s %d %d %d %d %d\n",&(p.cin),p.nom,p.prenom,p.email,p.pw,&(p.sexe),(p.role),&(p.vote),&(p.bv),&(p.d.jour),&(p.d.mois),&(p.d.an))!=EOF)
	{
		b=0;
		for (int i=0;i<100;i++){
			if (x[i][0] == p.bv){
				x[i][1] = x[i][1] + 1;
				b=1;
				break;
			}
		}
        if(b == 0){
			x[n][0] = p.bv;
			x[n][1] = 1;
			n++;
		}
		c++;
	}
	for (int i=0; i<n; i++){
        for (int j=i+1; j<n; j++){
            if (x[i][1] < x[j][1]){
                int s1 = x[j][0];
                int s2 = x[j][1];
                x[j][0] = x[i][0];
                x[j][1] = x[i][1];
                x[i][0] = s1;
                x[i][1] = s2;
            }
	}
	}


	for (int j=0;j<n;j++){
	    sprintf(tmp, "Bureau %d : %d électeurs\n", x[j][0], x[j][1]);
	    strcat(ch, tmp);
}
return ch;
} 

int Check_Email_Addr(char *EM_Addr) {
int count = 0;
int i = 0;
char conv_buf[50];
char *c, *domain;
char *special_chars = "()<>@,;:\"[]";

/* The input is in EBCDIC so convert to ASCII first */
strcpy(conv_buf,EM_Addr);

for(c = conv_buf; *c; c++) {
   /* if '"' and beginning or previous is a '.' or '"' */
   if (*c == 34 && (c == conv_buf || *(c - 1) == 46 || *(c - 1) == 34)) {
      while (*++c) {
         /* if '"' break, End of name */
         if (*c == 34)
            break;
         /* if '' and ' ' */
         if (*c == 92 && (*++c == 32))
            continue;
         /* if not between ' ' & '~' */
         if (*c <= 32 || *c > 127)
            return 0;
         }
      /* if no more characters error */
      if (!*c++)
         return 0;
      /* found '@' */
      if (*c == 64)
         break;
      /* '.' required */
      if (*c != 46)
         return 0;
      continue;
      }
   if (*c == 64) {
      break;
      }
   /* make sure between ' ' && '~' */
   if (*c <= 32 || *c > 127) {
      return 0;
      }
   /* check special chars */
   if (strchr(special_chars, *c)) {
      return 0;
      }
   } /* end of for loop */
/* found '@' */
/* if at beginning or previous = '.' */
if (c == conv_buf || *(c - 1) == 46)
   return 0;
/* next we validate the domain portion */
/* if the next character is NULL */
/* need domain ! */
if (!*(domain = ++c))
   return 0;
do {
   /* if '.' */
   if (*c == 46) {
      /* if beginning or previous = '.' */
      if (c == domain || *(c - 1) == 46)
         return 0;
      /* count '.' need at least 1 */
      count++;
      }
   /* make sure between ' ' and '~' */
   if (*c <= 32 || *c >= 127)
      return 0;
   if (strchr(special_chars, *c))
      return 0;
   } while (*++c); /* while valid char */
return (count >= 1); /* return true if more than 1 '.' */
}

bool valid_cin(char *cin){
if(strspn(cin, "0123456789") == strlen(cin))
return true;
return false;
}

