#ifndef UTILISATEUR_H_INCLUDED
#define utilisateur_H_INCLUDED
#include <stdio.h>
typedef struct
{
int jour;
int mois;
int annee;
}date1;
typedef struct
{
int cin;
char nom[20];
char prenom[20];
int role[20];
int lieu[20];
int numBV;
char login[20];
char mot_de_passe[20];
date1 date;
int vote;
}utilisateur;

int ajouter(char * filename, utilisateur user );
int modifier( char *, int, utilisateur);
int supprimer(char *, int );
utilisateur chercher(char *, int);

#endif
