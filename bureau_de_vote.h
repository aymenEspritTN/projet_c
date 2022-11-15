#ifndef BUREAU_DE_VOTE_H_
#define BUREAU_DE_VOTE_H_
#include <stdio.h>

typedef struct
{
int id;
int capacite_el;
int capacite_ob;
char adresse[40];
int id_agent;
int salle;
} BureauDeVote; 

int ajouter_bv(char * filename,BureauDeVote bv );
int modifier_bv( char *filename, int id, BureauDeVote bv );
int supprimer_bv(char *filename, int id);
BureauDeVote chercher_bv(char *filename, int id);
void affiche_bv(GtkWidget *liste);


#endif
