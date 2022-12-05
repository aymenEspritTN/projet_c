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

typedef enum
{
	id,id_tete,orientation,date,nbre_candidats,id_candidats
} LEEnum;

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


ListeElectorale* load_le(char* filename);
int ajouter_le(char* filename, ListeElectorale le);
int modifier_le(char* filename, int id, ListeElectorale nouv);
int supprimer_le(char* filename, int id);
ListeElectorale chercher_le(char* filename, int id);

int L_ordre( char *fichierListeElectorale, ListeElectorale t[], char * fichierusers);
int nbv (char * filename, int idListe);

char* DateToString(Date date);
ListeElectorale* read_file_as_table(char* filename, int* n);

#endif
