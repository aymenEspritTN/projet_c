#include "election_calcul.h"
#include <stdio.h>


void TPHF( char *filename, float *f, float *h)
{
     
    int nf=0;
    int nh =0;
    int nb_vote=0;
   
    utilisateur u;

    FILE *f1=fopen(filename, "r");
    if(f1!=NULL)
    {
        while(fscanf(f1," %d %s %s %s %s %d %s %s %d %d %d  %d %s %d  ",&u.cin,u.nom,u.prenom,u.role,u.lieu,&u.numBV,u.login,u.mot_de_passe,&u.date.jour,
                         &u.date.mois,&u.date.annee,u.sexe,&u.vote)!=EOF)
        {
          if((strcmp(u.role,"electeur"))==0 && (u.vote!=-1))
          {
             nb_vote=nb_vote+1;
              if(u.sexe=='h')
               {
               
                nh=nh+1;
               }
             
              else   
              {
             
               nf=nf+1;
              }
          }
             
        }
     
      *f=(float)nf/nb_vote;
      *h=(float)nh/nb_vote;
      
      
    }
    fclose(f1);
}
float TPE(char *filename)
{
   int nb_electeur_vote=0;
   int nb_electeur=0;
   float tauxpele;
   utilisateur u;
   FILE *f1=fopen(filename,"r");
   if(f1!=NULL)
   {
    while(fscanf(f1,"  %d %s %s %s %s %d %s %s %d %d %d  %d %s %d  ",&u.cin,u.nom,u.prenom,u.role,u.lieu,&u.numBV,u.login,u.mot_de_passe,&u.date.jour,
        &u.date.mois,&u.date.annee,u.sexe,&u.vote)!=EOF)
    {
          if((strcmp(u.role,"electeur"))==0)
          {
            nb_electeur=nb_electeur+1;
             if(u.vote !=-1)
		 nb_electeur_vote=nb_electeur_vote+1;
             
          }

    }

   
   }
   tauxpele= (float)nb_electeur_vote/nb_electeur;
  fclose(f1);
return tauxpele;
}







