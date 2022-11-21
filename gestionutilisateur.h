#ifndef UTILISATEUR_H_INCLUDED
#define utilisateur_H_INCLUDED
#include <stdio.h>
typedef struct
{
int jour;
int mois;
int annee;
}date;
typedef struct
{
int cin;
char nom[20];
char prenom[20];
char role[20];
char lieu[20];
int numBV;
char login[20];
char mot_de_passe[20];
date date1;
}utilisateur;

int ajouter(char * filename, utilisateur user );
int modifier( char *, int, utilisateur);
int supprimer(char *, int );
utilisateur chercher(char *, int);

#endif
