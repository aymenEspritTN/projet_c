
#ifndef GECALCUL_H_INCLUDED
#define  GECALCUL_H_INCLUDED
#endif
#include <stdio.h>
#include <string.h>


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
char role[20];
char lieu[20];
int numBV;
char login[20];
char mot_de_passe[20];
char sexe;
date1 date;
int vote;
}utilisateur;
 

