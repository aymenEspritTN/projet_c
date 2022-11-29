#ifndef LISTE_ELECTORALE_H_
#define LISTE_ELECTORALE_H_
#include <stdio.h>

typedef struct Date
{
	int jour;
	int mois;
	int an;
} Date;

typedef struct
{
	int id;
	int id_tete;
	int orientation;
	Date date;
	int nbre_candidats;
	int id_candidats[3];
} ListeElectorale;

typedef struct
{
	int cin;
	char nom[20];
	char prenom[20];
	int role;
	int lieu;
	int numbv;
	char login[20];
	char pass[20];
	Date date;
	int vote;
} User;


int ajouter_le(char* filename, ListeElectorale le);
int modifier_le(char* filename, int id, ListeElectorale nouv);
int supprimer_le(char* filename, int id);
ListeElectorale chercher_le(char* filename, int id);

int L_ordre( char *fichierListeElectorale, ListeElectorale t[], char * fichierusers);
int nbv (char * filename, int idListe);

#endif
