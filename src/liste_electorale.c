
#include <stdio.h>
#include <stdlib.h>
#include "liste_electorale.h"

int ajouter_le(char* filename, ListeElectorale le)
{
    FILE * f=fopen(filename, "a");
    if(f!=NULL)
    {
	/*char id_candidats[le.nbre_candidats+1];
	int i=0;
	for(i=0; i<le.nbre_candidats; i++)
	{
		id_candidats[i] = ... + " "
	}
	id_candidats[le.nbre_candidats] = '\0';*/

        fprintf(f,"%d %d %d %d %d %d %d %d %d %d\n",
		le.id, le.id_tete, le.orientation, le.nbre_candidats,
		le.date.jour, le.date.mois, le.date.an, 
		le.id_candidats[0], le.id_candidats[1], le.id_candidats[2]);

        fclose(f);
        return 1;
    }
    else return 0;
}


int modifier_le(char* filename, int id, ListeElectorale nouv)
{
	int tr=0;
	ListeElectorale le;
	FILE * f=fopen(filename, "r");
	FILE * f2=fopen("nouv.txt", "w");
	if(f!=NULL && f2!=NULL)
	{
		while(fscanf(f,
				"%d %d %d %d %d %d %d %d %d %d\n",
				&le.id, &le.id_tete, &le.orientation, &le.nbre_candidats,
				&le.date.jour, &le.date.mois, &le.date.an, 
				&le.id_candidats[0], &le.id_candidats[1], &le.id_candidats[2]
			)!=EOF)
		{
		    if(le.id== id)
		    {
			fprintf(f2,"%d %d %d %d %d %d %d %d %d %d\n",
				nouv.id, nouv.id_tete, nouv.orientation, nouv.nbre_candidats,
				nouv.date.jour, nouv.date.mois, nouv.date.an, 
				nouv.id_candidats[0], nouv.id_candidats[1], nouv.id_candidats[2]);
			tr=1;
		    }
		    else
			fprintf(f2,"%d %d %d %d %d %d %d %d %d %d\n",
				le.id, le.id_tete, le.orientation, le.nbre_candidats,
				le.date.jour, le.date.mois, le.date.an, 
				le.id_candidats[0], le.id_candidats[1], le.id_candidats[2]);

		}
	}
	fclose(f);
	fclose(f2);
	remove(filename);
	rename("nouv.txt", filename);
	return tr;
}


int supprimer_le(char* filename, int id)
{
	int tr=0;
	ListeElectorale le;
	FILE * f=fopen(filename, "r");
	FILE * f2=fopen("nouv.txt", "w");
	if(f!=NULL && f2!=NULL)
	{
		while(fscanf(f,
				"%d %d %d %d %d %d %d %d %d %d\n",
				&le.id, &le.id_tete, &le.orientation, &le.nbre_candidats,
				&le.date.jour, &le.date.mois, &le.date.an, 
				&le.id_candidats[0], &le.id_candidats[1], &le.id_candidats[2]
			)!=EOF)
		{
		    if(le.id == id)
			tr=1;
		    else
			fprintf(f2,"%d %d %d %d %d %d %d %d %d %d\n",
				le.id, le.id_tete, le.orientation, le.nbre_candidats,
				le.date.jour, le.date.mois, le.date.an, 
				le.id_candidats[0], le.id_candidats[1], le.id_candidats[2]);
		}
	}
	fclose(f);
	fclose(f2);
	remove(filename);
	rename("nouv.txt", filename);
	return tr;
}

ListeElectorale chercher_le(char* filename, int id)
{
	ListeElectorale le;
	int tr = 0;
	FILE * f=fopen(filename, "r");
	if(f!=NULL)
	{
		while(tr==0 && fscanf(f,
				"%d %d %d %d %d %d %d %d %d %d\n",
				&le.id, &le.id_tete, &le.orientation, &le.nbre_candidats,
				&le.date.jour, &le.date.mois, &le.date.an, 
				&le.id_candidats[0], &le.id_candidats[1], &le.id_candidats[2]
			)!=EOF)
		{
		    if(le.id== id)
			{
				tr=1;
				//printf("id found:%d", id);
			}
		}
	}
	fclose(f);
	if(tr==0)
		le.id=-1;
	return le;
}








