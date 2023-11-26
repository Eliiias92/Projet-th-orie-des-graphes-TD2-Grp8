#include <stdio.h>
#include <stdlib.h>
int precedencelecture(int* plusGrandNombre) {
    // Nom du fichier à ouvrir


    // Ouverture du fichier en mode lecture
    FILE *fichier = fopen("testpt.txt", "r");

    // Vérification si l'ouverture du fichier a réussi
    if (!fichier) {
        fprintf(stderr, "Impossible d'ouvrir le fichier .\n");
        return 1; // Code d'erreur
    }

    // Compteur de lignes
    int nombreLignes = 0;
    char caractere;
    int max = 0;
    // Lecture du fichier caractère par caractère
    while ((caractere = fgetc(fichier)) != EOF) {
        if (caractere > max) {
            max = caractere;

        }
        if (caractere == '\n') {
            nombreLignes++;
        }
    }

    // Fermeture du fichier
    fclose(fichier);


    FILE *f2 = fopen("testpt.txt", "r");

    // Vérification si l'ouverture du fichier a réussi
    if (f2 == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier .\n");
        return 1; // Code d'erreur
    }

    // Variables pour stocker le nombre actuel et le plus grand nombre
    int s1, s2 = 0;
    nombreLignes--;

    // Lecture du fichier nombre par nombre
    for (int i = 0; i < nombreLignes; ++i) {
        fscanf(f2, "%d%d", &s1, &s2);
        if (s1 > *plusGrandNombre)
            *plusGrandNombre = s1;
        if (s2 > *plusGrandNombre)
            *plusGrandNombre = s2;
    }

    // Fermeture du fichier
    fclose(f2);

    // Vérification si des nombres ont été trouvés dans le fichier


    printf("plus grand %d\n", *plusGrandNombre);
    // Affichage du nombre de lignes
    printf("Le fichier  contient %d lignes.\n", nombreLignes);
}




int tabprecede(int* plusGrandNombre,int tab[*plusGrandNombre+1][*plusGrandNombre+1])
{

    for(int k=0;k<*plusGrandNombre+1;k++)
    { for(int z=0;z<*plusGrandNombre+1;z++)
        {tab[k][z]=0;}

    }

    FILE *f3 = fopen("testpt.txt", "r");

    // Vérification si l'ouverture du fichier a réussi
    if (f3 == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier .\n");
        return 1; // Code d'erreur
    }
    int ss1,ss2;

    for (int v=0; v<*plusGrandNombre+1; ++v)
    {
        fscanf(f3,"%d%d",&ss2,&ss1);
        tab[ss1][ss2]=1;

    }

    /*for(int n=0;n<*plusGrandNombre+1;n++)
    { for(int m=0;m<*plusGrandNombre+1;m++)
        {printf("%d",tab[n][m]);}
        printf("\n");

    }*/
    fclose(f3);
    return 0; // Fin du programme sans erreur

}

void readOperations(int *taille,float tabtemps[*taille+1],int *operationCount) {
    FILE *fptr;
    float operationNumber;
    float executionTime;

    // Ouvrir le fichier en mode lecture
    fptr = fopen("opstest.txt", "r");

    // Vérifier si le fichier est ouvert avec succès
    if (fptr == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        exit(1); // Exit with error code
    }

    // Lire chaque paire opération-temps du fichier et incrémenter le nombre d'opérations
    while (fscanf(fptr, "%f %f", &operationNumber, &executionTime) == 2) {
        (*operationCount)++;
    }
    float temps;
    int sommet;

    // Rembobiner le fichier pour relire les opérations
    rewind(fptr);

    // Lire chaque paire opération-temps du fichier et stocker dans le tableau 2D
    for (int i = 0; i < *operationCount; i++) {
        fscanf(fptr, "%d %f", &sommet, &temps);
        tabtemps[sommet]=temps;
    }

    // Fermer le fichier
    fclose(fptr);


}

void ouverturetempscycles(float* tempcyclemax)
{
    FILE *fptr;


    // Ouvrir le fichier en mode lecture
    fptr = fopen("cycle.txt", "r");

    // Vérifier si le fichier est ouvert avec succès
    if (fptr == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        exit(1); // Exit with error code
    }

    fscanf(fptr,"%f",tempcyclemax );




}




int precedvalide(int* plusGrandNombre,int tabcouleurs[*plusGrandNombre+1],int tabpred[*plusGrandNombre+1][*plusGrandNombre+1],int* tache,float tabtemps[*plusGrandNombre+1])
{
    for (int n = 0; n < *plusGrandNombre + 1; n++) {


        if (tabpred[*tache][n]==1)
        {
            if(tabcouleurs[n]==1)
            {//printf("\ntache:%d",*tache);
                //printf("antecedant:%d\n",n);

                return 1;
            }


        }

    }

    /*if(tabtemps[*tache]>0)
    {
        printf("test2sure");
        return 1;
        }*/

    return 0;
}




int fin(int* plusGrandNombre,float tabtemps[*plusGrandNombre+1],int tabcouleurs[*plusGrandNombre+1] )
{

    for(int y=0;y<*plusGrandNombre+1;y++)
{if(tabtemps[y]>0&&tabcouleurs[y]==0)
{

    return 1;
}
}
    return 0;

}



void tritempspred(int* plusGrandNombre,float tabtemps[*plusGrandNombre+1], int tabpred[*plusGrandNombre+1][*plusGrandNombre+1], int workstations [*plusGrandNombre+1][*plusGrandNombre+1],float* cyclemax)
{
   float tempstot=0;
   int indiceworkstation=0;
   int terminer=1;
   int tabcouleurs[*plusGrandNombre+1];
    for(int z=0;z<*plusGrandNombre+1;z++)
    {tabcouleurs[z]=0;}
    int prece;
   int j=0;
   int* tache=&j;
   int finit=1;
   while(finit==1)
   {
   while (terminer==1)
   {terminer=0;
       for(int y=0;y<*plusGrandNombre+1;y++)
       {*tache=y;
           prece=precedvalide(plusGrandNombre,tabcouleurs,tabpred,tache,tabtemps);
           //printf("\n preced:%d",prece);
           if(y==1)
           {prece=1;}
       if((tempstot+tabtemps[y])<=*cyclemax && prece==1 && tabcouleurs[y]==0)
       {
           tabcouleurs[y]=1;
           terminer=1;
           //printf("jjj");
           workstations[indiceworkstation][y]=1;
           tempstot=tempstot+tabtemps[y];


       }



       }
     /*  for(int y=0;y<*plusGrandNombre+1;y++)
       {
           if(tabcouleurs[y]==1)
               printf("tache:%d\n",y);

       }*/

   }
       printf("\n");
   indiceworkstation++;
   tempstot=0;
   terminer=1;
   finit=fin( plusGrandNombre, tabtemps, tabcouleurs);

   }

}





int main() {
    int pg = 0;
    int *plusGrandNombre = &pg;
    precedencelecture(plusGrandNombre);
    float cycle;
    float* cyclemax= &cycle;
    int tab[*plusGrandNombre + 1][*plusGrandNombre + 1];
    tabprecede(plusGrandNombre, tab);

    for (int n = 0; n < *plusGrandNombre + 1; n++) {
        for (int m = 0; m < *plusGrandNombre + 1; m++) {
            printf("%d", tab[n][m]);
        }
        printf("\n");
    }
    int resultat [*plusGrandNombre+1][*plusGrandNombre+1];

    for(int k=0;k<*plusGrandNombre+1;k++)
    { for(int z=0;z<*plusGrandNombre+1;z++)
        {resultat[k][z]=0;}

    }

    float tabtemps[*plusGrandNombre+1];
    for(int z=0;z<*plusGrandNombre+1;z++)
    {tabtemps[z]=0;}



    // Lire les opérations et les temps du fichier
    int operationCount = 0;
     readOperations(plusGrandNombre,tabtemps,&operationCount);
    for (int i = 0; i <*plusGrandNombre+1; i++) {
        if(tabtemps[i]>0)
        { printf("Opération %d : Temps d'exécution %.2f\n",i,tabtemps[i]);}
    }
    ouverturetempscycles(cyclemax);
    for(int j=0;j<*plusGrandNombre+1;j++ )
    {
        if(tabtemps[j]>*cyclemax)
        { for(int z=0;z<*plusGrandNombre+1;z++ )
            {
                tab[j][z]=0;
            }
            tabtemps[j]=0;
            printf("\nla tache:%d a ete suprimee car son temps de cycle etait trop long nv temps:%.2f\n",j,tabtemps[j]);


        }


    }




    tritempspred( plusGrandNombre, tabtemps, tab,resultat,cyclemax );
    int max=0;



    for (int n = 0; n < *plusGrandNombre + 1; n++) {
        printf("station %d:",n);
        for (int m = 0; m < *plusGrandNombre + 1; m++) {
            if(resultat[n][m]==1)
            {printf("%d", m);}
        }
        printf("\n");
    }
    return 0;
}