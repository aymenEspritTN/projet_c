#include "gestionutilisateur.h"

int ajouter(char * filename, utilisateur user )
{
    FILE * f=fopen(filename, "a");
    if(f!=NULL)
    {
        fprintf(f," %d %s %s %d %d %d %s %s %d %d %d %d\n",user.cin,user.nom,user.prenom,user.role,user.lieu,user.numBV,user.login,user.mot_de_passe,user.date.jour,user.date.mois,user.date.annee,user.vote);
        fclose(f);
        return 1;
    }
    else return 0;
}
int modifier( char * filename, int cin, utilisateur user )
{
    int tr=0;
   
    FILE * f=fopen(filename, "r");
    FILE * f2=fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
 while(fscanf(f," %d %s %s %d %d %d %s %s %d %d %d %d\n",user.cin,user.nom,user.prenom,user.role,user.lieu,user.numBV,user.login,user.mot_de_passe,user.date.jour,user.date.mois,user.date.annee,user.vote)!=EOF)
        {
            if(user.cin== cin)
            {
                fprintf(f2," %d %s %s %d %d %d %s %s %d %d %d %d\n",user.cin,user.nom,user.prenom,user.role,user.lieu,user.numBV,user.login,user.mot_de_passe,user.date.jour,user.date.mois,user.date.annee,user.vote);
                tr=1;
            }
            else
                fprintf(f2," %d %s %s %d %d %d %s %s %d %d %d %d\n",user.cin,user.nom,user.prenom,user.role,user.lieu,user.numBV,user.login,user.mot_de_passe,user.date.jour,user.date.mois,user.date.annee,user.vote);

        }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return tr;

}

int supprimer(char * filename, int cin)
{
    int tr=0;
    utilisateur user;
    FILE * f=fopen(filename, "r");
    FILE * f2=fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
while(fscanf(f,"  %d %s %s %d %d %d %s %s %d %d %d %d\n",user.cin,user.nom,user.prenom,user.role,user.lieu,user.numBV,user.login,user.mot_de_passe,user.date.jour,user.date.mois,user.date.annee,user.vote)!=EOF)
        {
            if(user.cin==cin)
                tr=1;
            else
      fprintf(f2," %d %s %s %d %d %d %s %s %d %d %d %d\n",user.cin,user.nom,user.prenom,user.role,user.lieu,user.numBV,user.login,user.mot_de_passe,user.date.jour,user.date.mois,user.date.annee,user.vote);
        }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return tr;
}

utilisateur chercher(char * filename, int cin)
{
   utilisateur user;
    int tr=0;
    FILE * f=fopen(filename, "r");
    if(f!=NULL)
    {
while(fscanf(f," %d %s %s %d %d %d %s %s %d %d %d %d\n",user.cin,user.nom,user.prenom,user.role,user.lieu,user.numBV,user.login,user.mot_de_passe,user.date.jour,user.date.mois,user.date.annee,user.vote)!=EOF)
        {
            if(user.cin==cin)
               { tr=1;}
        }
    }
    fclose(f);
    if(tr==0)
      user.cin=-1;
    return user;
}
