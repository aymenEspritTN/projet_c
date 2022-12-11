#ifndef BUREAU_DE_VOTE_H_
#define BUREAU_DE_VOTE_H_
#include <stdio.h>

typedef struct
{
char nom[20];
char prenom[20];
char nationalite[20];
char appartenance[30];
char sexe[20]; 
int id,numbv;
} observateur; 

typedef struct
{
char nom[20];
char prenom[20];
char lieu[30];
char role[30];
char login[20];
char mot_de_passe[20];
int cin,numbv;
int vote;
}utilisateur;

void taux(char * filename,float *tn,float *et);
float voteblanc(char * filename);

#endif
