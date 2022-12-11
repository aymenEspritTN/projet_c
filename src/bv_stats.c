#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bv_stats.h"


void taux(char * filename,float *tn,float *et)
{int a=0;
float t=0,e=0;
observateur ob;
FILE * f=fopen("observateur.txt", "r");
if(f!=NULL)
  {  while(fscanf(f,"%s %s %s %s %s %d %d",ob.nom,ob.prenom,ob.nationalite,ob.appartenance,ob.sexe,&ob.id,&ob.numbv)!=EOF)
{
     a=a+1;
    
     if(strcmp(ob.nationalite,"tunisien")==0)
        t=t+1;
     else
        e=e+1;
}

*tn=(t/a)*100;
*et=(e/a)*100;
}
fclose(f);
}

float voteblanc(char * filename)
{int a=0;
float vb=0,taux_vb;
utilisateur us;
FILE * f=fopen("user.txt", "r");
if(f!=NULL)
  {  while(fscanf(f,"%s %s %s %s %s %s %d %d %d",us.nom,us.prenom,us.lieu,us.role,us.login,us.mot_de_passe,&us.cin,&us.numbv,&us.vote)!=EOF)
{
     if ((us.vote!=-1)&&(strcmp(us.role,"electeur")==0))
        a=a+1;
     if ((us.vote==0)&&(strcmp(us.role,"electeur")==0))
        vb=vb+1;
}

taux_vb=(vb/a)*100;

}
fclose(f);
return taux_vb;
}



