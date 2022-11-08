#ifndef LISTE_ELECTORALE_H_
#define LISTE_ELECTORALE_H_
#include <stdio.h>

typedef struct Date
{
	int jour;
	int mois;
	int an;
} Date;

typedef struct ListeElectorale
{
	int id;
	int id_tete;
	int orientation;
	Date date;
	int nbre_candidats;
	int id_candidats[3];
} ListeElectorale;

int ajouter_le(char* filename, ListeElectorale le);
int modifier_le(char* filename, int id, ListeElectorale nouv);
int supprimer_le(char* filename, int id);
ListeElectorale chercher_le(char* filename, int id);

#endif
