
#include <stdio.h>
#include <stdlib.h>
#include "liste_electorale.h"


char* DateToString(Date date)
{
	char* str = malloc(sizeof("00/00/0000"));
	sprintf(str, "%d/%d/%d" , date.jour, date.mois, date.an);
	return str;
}

int ajouter_le(char* filename, ListeElectorale le)
{
    FILE * f=fopen(filename, "a");
    if(f!=NULL)
    {
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
		    if(le.id== id)tr=1;
		}
	}
	fclose(f);
	if(tr==0)
		le.id=-1;
	return le;
}

ListeElectorale* read_file_as_table(char* filename, int* n)
{
	int lines = 0;
	int i = 0;
	char ch;
	FILE* f = fopen(filename, "r");
	while(!feof(f))
	{
		ch = fgetc(f);
		if(ch == '\n')
			lines++;
	}
	fclose(f);
	
	ListeElectorale* t = malloc(sizeof(ListeElectorale) * lines);
	ListeElectorale le;
	if(!t)return NULL;

	f = fopen(filename, "r");
	while(fscanf(f,
		"%d %d %d %d %d %d %d %d %d %d\n",
		&le.id, &le.id_tete, &le.orientation, &le.nbre_candidats,
		&le.date.jour, &le.date.mois, &le.date.an, 
		&le.id_candidats[0], &le.id_candidats[1], &le.id_candidats[2]
		)!=EOF)
	{
		t[i] = le;
		i++;
	}
	fclose(f);
	*n = lines;
	return t;
}


