
#include <stdlib.h>
#include "liste_electorale.h"

int L_ordre(char *fichierListeElectorale, ListeElectorale t[], char * fichierusers)
{
	int nbre=0;
	ListeElectorale le;
	FILE* f = fopen(fichierListeElectorale, "r");
	if(f!=NULL)
	{
		while(fscanf(f,
				"%d %d %d %d %d %d %d %d %d %d\n",
				&le.id, &le.id_tete, &le.orientation, &le.nbre_candidats,
				&le.date.jour, &le.date.mois, &le.date.an, 
				&le.id_candidats[0], &le.id_candidats[1], &le.id_candidats[2]
			)!=EOF)
		{
			nbre +=1;
		}
	}
	fclose(f);
	
	t = malloc(sizeof(ListeElectorale) * nbre);
	
	int k=0;
	f = fopen(fichierListeElectorale, "r");
	if(f!=NULL)
	{
		while(fscanf(f,
				"%d %d %d %d %d %d %d %d %d %d\n",
				&le.id, &le.id_tete, &le.orientation, &le.nbre_candidats,
				&le.date.jour, &le.date.mois, &le.date.an, 
				&le.id_candidats[0], &le.id_candidats[1], &le.id_candidats[2]
			)!=EOF)
		{
			t[k] = le; k+=1;
		}
	}
	fclose(f);
	
	ListeElectorale tampon;
	int i, j, min;
	int n = nbre;
	for (i=0;i<n-1;i++)
	{
		min=i;
		for (j=i+1;j<n;j++)
		{
			int curr_v = nbv(fichierusers, t[j].id);
			int min_v = nbv(fichierusers, t[min].id);
			if (curr_v>min_v)
				min=j;
		}
		tampon=t[i];
		t[i]=t[min];
		t[min]=tampon;
	}

	int b = 0;
	FILE * f2=fopen("nouv.txt", "w");
	fclose(f2);
	for(b=0; b<nbre; b++)
	{
		ajouter_le("nouv.txt", t[b]);
	}
	remove(fichierListeElectorale);
	rename("nouv.txt", fichierListeElectorale);

	return nbre;
}
int nbv (char * filename, int idListe)
{
	int nbre=0;
	User u;
	FILE* f = fopen(filename, "r");
	if(f!=NULL)
	{
		while(fscanf(f,"%d %s %s %d %d %d %s %s %d %d %d %d\n", 
			&u.cin, u.nom, u.prenom, &u.role, &u.lieu, &u.numbv, u.login, u.pass, 				&u.date.jour, &u.date.mois, &u.date.an, &u.vote)!=EOF)
		{
			if(u.vote == idListe)
				nbre+=1;
		}
	}
	fclose(f);
	return nbre;
}




