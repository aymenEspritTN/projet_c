
#include <stdlib.h>
#include "liste_electorale.h"
#include "user.h"

int L_ordre(char *fichierListeElectorale, ListeElectorale *ts[], char * fichierusers)
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
	
	*ts = malloc(sizeof(ListeElectorale) * nbre);
	ListeElectorale* t = *ts;
	
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
int nbv (char * fichierusers, int idListe)
{
	int nbre=0;
	User p;
	FILE* f = fopen(fichierusers, "r");
	if(f!=NULL)
	{
		while(fscanf(f,"%d %s %s %s %s %d %d %d %d %d %d %d\n"
			,&(p.cin),p.nom,p.prenom,p.email,p.pw,&(p.sexe),
			&(p.role),&(p.vote),&(p.bv),&(p.date.jour),&(p.date.mois),&(p.date.an))!=EOF)
		{
			if(p.vote == idListe)
				nbre+=1;
		}
	}
	fclose(f);
	return nbre;
}




