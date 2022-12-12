#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <gtk/gtk.h>
#include "liste_electorale.h"
/*typedef struct date{
int j;
int m;
int a;
}date;*/

typedef struct ut{
int cin;
char nom[30];
char prenom[30];
char email[40];
char pw[15];
int sexe;
char role[15];
int vote;
int bv;
Date d;
}ut;


void ajouter(ut u, char *fname);
void supprimer(ut u, char *fname);
void modifier(ut u, char *fname);
void afficher(GtkWidget *liste, char *fname, char *id, char *email, char *nom);
ut chercher(int id, char *fname);
char* age_moyen(char *filename);
char* e_bv(char *filename);
int Check_Email_Addr(char *EM_Addr);
bool valid_cin(char *cin);

