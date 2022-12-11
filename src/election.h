#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#endif
#include <gtk/gtk.h>
#include "liste_electorale.h"
/*typedef struct 
{
int jour;
int mois;
int annee;
} Date;*/

typedef struct 
{ 
int id ;
Date date;
char nombre_d_habitant[20];
int nombre_de_conseiller;
char municipalite[20];

} GestionElection ;


int ajouter_GE(char *filename,GestionElection GE);
int modifier_GE(int id, char * filename,GestionElection GE);
int supprimer_GE(int id, char * filename);
GestionElection chercher_Ge(int id, char * filename);

void affiche_ge(GtkWidget *liste,char *id);

