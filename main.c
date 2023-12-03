#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

struct Operation
{
    int n;
    float tmp;
    int precedent[50];
    int nmbPrecedent;

    int suivant[50];
    int nmbSuivant;

    int exclusion[50];
    int nmbExclusion;

    char couleurExclusion[10];

    int mark;


};
typedef struct Operation Operation;


void setOp(Operation *Op,int _n)
{
    Op->n  = _n;
    Op->tmp = 0.0;
    Op->nmbExclusion = 0;
    Op->nmbPrecedent = 0;
    Op->nmbSuivant = 0;
    strcpy(Op->couleurExclusion,"none");
    Op->mark = 0;

}

struct Station
{
    int nmbOp;
    Operation Op[50];
    char couleur[10];
    float tmp;
};
typedef struct Station Station;

void setStation( Station * St)
{

    St->nmbOp = 0;

    St->tmp = 0;
    strcpy(St->couleur,"none");

}

void addOp(Operation Op, Station * St)
{
    int k = St->nmbOp;
    St->Op[k] = Op;
    St->nmbOp++;
    strcpy(St->couleur,Op.couleurExclusion);
    St->tmp += Op.tmp;
}


int chargerNmbOperation(Operation Op[100])
{
    int nmbOp = 0;
    FILE* fichier = fopen("exclusions.txt", "r");

    if (!fichier)
    {
        fprintf(stderr, "Impossible d'ouvrir exclusions.txt\n");
        exit(EXIT_FAILURE);
    }

    int a;
    int b;

    while (fscanf(fichier, "%d %d", &a, &b) != EOF)
    {
        int trouveA = 0;
        for(int i= 0 ; i < nmbOp ; i++)
        {
            if(Op[i].n == a)
                trouveA = 1;
        }
        if(trouveA == 0)
        {
            Operation newOp;
            setOp(&newOp,a);
            Op[nmbOp] = newOp;
            nmbOp++;
        }

        int trouveB = 0;
        for(int i= 0 ; i < nmbOp ; i++)
        {
            if(Op[i].n == b)
                trouveB = 1;
        }
        if(trouveB == 0)
        {
            Operation newOp;
            setOp(&newOp,b);
            Op[nmbOp] = newOp;
            nmbOp++;
        }

    }

    fclose(fichier);
    fichier = fopen("precedences.txt", "r");

    if (!fichier)
    {
        fprintf(stderr, "Impossible d'ouvrir exclusions.txt\n");
        exit(EXIT_FAILURE);
    }

    while (fscanf(fichier, "%d %d", &a, &b) != EOF)
    {
        int trouveA = 0;
        for(int i= 0 ; i < nmbOp ; i++)
        {
            if(Op[i].n == a)
                trouveA = 1;
        }
        if(trouveA == 0)
        {
            Operation newOp;
            setOp(&newOp,a);
            Op[nmbOp] = newOp;
            nmbOp++;
        }
        int trouveB = 0;
        for(int i= 0 ; i < nmbOp ; i++)
        {
            if(Op[i].n == b)
                trouveB = 1;
        }
        if(trouveB == 0)
        {
            Operation newOp;
            setOp(&newOp,b);
            Op[nmbOp] = newOp;
            nmbOp++;
        }
    }
    fclose(fichier);
    fichier = fopen("operations.txt", "r");

    if (!fichier)
    {
        fprintf(stderr, "Impossible d'ouvrir exclusions.txt\n");
        exit(EXIT_FAILURE);
    }

    float t;
    while (fscanf(fichier, "%d %f", &a, &t) != EOF)
    {
        int trouveA = 0;
        for(int i= 0 ; i < nmbOp ; i++)
        {
            if(Op[i].n == a)
            {
                trouveA = 1;
                Op[i].tmp = t;

            }

        }
        if(trouveA == 0)
        {
            Operation newOp;
            setOp(&newOp,a);
            Op[nmbOp] = newOp;
            Op[nmbOp].tmp = t;
            nmbOp++;
        }

    }
    fclose(fichier);

    return nmbOp;
}

void chargerInfoOp( Operation Op[100],int nmbOp)
{
    FILE* fichier = fopen("exclusions.txt", "r");

    if (!fichier)
    {
        fprintf(stderr, "Impossible d'ouvrir exclusions.txt\n");
        exit(EXIT_FAILURE);
    }

    int a;
    int b;

    while (fscanf(fichier, "%d %d", &a, &b) != EOF)
    {
        for(int i = 0 ; i< nmbOp ; i++ )
        {
            if(Op[i].n == a )
            {
                for(int j = 0 ; j < nmbOp ; j++)
                {
                    if(Op[j].n == b)
                    {
                        Op[i].exclusion[Op[i].nmbExclusion] = j;
                        Op[j].exclusion[Op[j].nmbExclusion] = i;
                        Op[i].nmbExclusion++;
                        Op[j].nmbExclusion++;
                    }
                }
            }
        }
    }

    fclose(fichier);

    fichier = fopen("precedences.txt", "r");

    if (!fichier)
    {
        fprintf(stderr, "Impossible d'ouvrir exclusions.txt\n");
        exit(EXIT_FAILURE);
    }

    while (fscanf(fichier, "%d %d", &a, &b) != EOF)
    {
        for(int i = 0 ; i< nmbOp ; i++ )
        {
            if(Op[i].n == a )
            {
                for(int j = 0 ; j < nmbOp ; j++)
                {
                    if(Op[j].n == b)
                    {
                        Op[i].suivant[Op[i].nmbSuivant] = j;
                        Op[j].precedent[Op[j].nmbPrecedent] = i;
                        Op[i].nmbSuivant++;
                        Op[j].nmbPrecedent++;

                    }
                }
            }
        }
    }

    fclose(fichier);

}

float getTempscycle()
{
    const char *nomFichier = "temps_cycle.txt";
    FILE *fichier = fopen(nomFichier, "r");

    if (fichier == NULL)
    {
        fprintf(stderr, "Impossible d'ouvrir le fichier %s.\n", nomFichier);
        exit(EXIT_FAILURE);
    }

    float nombre;
    if (fscanf(fichier, "%f", &nombre) != 1)
    {
        fprintf(stderr, "Erreur lors de la lecture du nombre dans le fichier %s.\n", nomFichier);
        fclose(fichier);
        exit(EXIT_FAILURE);
    }

    fclose(fichier);
    return nombre;
}

void AsciiArt()
{
    printf(" _______________     \n");
    printf(" / __/ ___/ __/ /__ _______ _____\n");
    printf("/ _// /__/ _// / -_) __/ _ `/ __/\n");
    printf("/___/\\___/___/_/\\__/\\__/\\_,_/_/    \n");
}

void afficherStation(Station St[10],int nmbSt)
{
    for(int i = 0 ; i < nmbSt ; i++)
    {
        printf("STATION %d\n",i+1);
        printf("Liste des operation:\n");
        for(int j = 0 ; j < St[i].nmbOp ; j++)
        {
            printf("(%d) ",St[i].Op[j]);
        }
        printf("\ntemps total d'execution : %f secondes\n\n",St[i].tmp);


    }
}

void Q1(Operation Op[100], int nmbOp, float tmpCycle)
{

    for(int i = 0 ; i < nmbOp ; i++)
    {
        Op[i].mark = 0;
        strcpy(Op[i].couleurExclusion,"none");
    }



    char* listeCouleur[10] =
    {
        "bleu",
        "rouge",
        "vert",
        "jaune",
        "orange",
        "violet",
        "rose",
        "noir",
        "blanc",
        "gris"
    };

    int cmp = 0;
    int end = 0;

    while(end < nmbOp)
    {

        for(int i = 0 ; i< nmbOp ; i++)
        {
            if(strcmp(Op[i].couleurExclusion,"none") == 0)
            {
                int test = 1;
                for(int j = 0 ; j < Op[i].nmbExclusion ; j++)
                {
                    if(strcmp(listeCouleur[cmp],Op[Op[i].exclusion[j]].couleurExclusion) == 0)
                        test = 0;
                }
                if(test == 1)
                {
                    strcpy(Op[i].couleurExclusion,listeCouleur[cmp]);
                    end++;
                }
            }
        }
        cmp++;

    }

    /// Remplissage des stations

    Station St[10];
    int nmbSt =0;
    cmp = 0;



    while(cmp != nmbOp)
    {


        setStation(&St[nmbSt]);

        for(int i = 0 ; i < nmbOp ; i++)
        {
            if(Op[i].mark == 0)
            {
                if(strcmp(St[nmbSt].couleur,Op[i].couleurExclusion) == 0 || strcmp(St[nmbSt].couleur,"none")==0)
                {

                    addOp(Op[i],&St[nmbSt]);
                    cmp++;
                    Op[i].mark = 1;

                }
            }

        }

        nmbSt++;
    }


    afficherStation(St,nmbSt);


}

void Q2(Operation Op[100], int nmbOp, float tmpCycle)
{
    for(int i = 0 ; i < nmbOp ; i++)
    {
        Op[i].mark = 0;
        strcpy(Op[i].couleurExclusion,"none");
    }

    char* listeCouleur[10] =
    {
        "bleu",
        "rouge",
        "vert",
        "jaune",
        "orange",
        "violet",
        "rose",
        "noir",
        "blanc",
        "gris"
    };

    int cmp = 0;
    int end = 0;

    while(end < nmbOp)
    {

        for(int i = 0 ; i< nmbOp ; i++)
        {
            if(strcmp(Op[i].couleurExclusion,"none") == 0)
            {
                int test = 1;
                for(int j = 0 ; j < Op[i].nmbExclusion ; j++)
                {
                    if(strcmp(listeCouleur[cmp],Op[Op[i].exclusion[j]].couleurExclusion) == 0)
                        test = 0;
                }
                if(test == 1)
                {
                    strcpy(Op[i].couleurExclusion,listeCouleur[cmp]);
                    end++;
                }
            }
        }
        cmp++;

    }

    /// Remplissage des stations

    Station St[10];
    int nmbSt =0;
    cmp = 0;



    while(cmp != nmbOp)
    {
        setStation(&St[nmbSt]);

        for(int i = 0 ; i < nmbOp ; i++)
        {
            if(Op[i].mark == 0)
            {
                if(strcmp(St[nmbSt].couleur,Op[i].couleurExclusion) == 0 || strcmp(St[nmbSt].couleur,"none")==0)
                {
                    if(St[nmbSt].tmp + Op[i].tmp <= tmpCycle)
                    {
                        addOp(Op[i],&St[nmbSt]);
                        cmp++;
                        Op[i].mark = 1;
                    }


                }
            }

        }

        nmbSt++;
    }


    afficherStation(St,nmbSt);


}

int precedentDecouvert(Operation Op[100],Operation Act)
{


    for (int j = 0; j < Act.nmbPrecedent; j++)
    {

        if (Op[Act.precedent[j]].mark == 0)
        {

            return 0;

        }

    }
    return 1;
}


void Q3(Operation Op[100], int nmbOp, float tmpCycle)
{
    for(int i = 0 ; i < nmbOp ; i++)
    {
        Op[i].mark = 0;
        strcpy(Op[i].couleurExclusion,"none");
    }

    Operation OpOrdre[100];
    int cmp = 0;

    while( cmp != nmbOp)
    {
        for(int i = 0 ; i < nmbOp ; i++)
        {
            if(Op[i].mark == 0)
            {
                if(precedentDecouvert(Op,Op[i]) == 1)
                {
                    OpOrdre[cmp] = Op[i];
                    cmp++;
                    Op[i].mark = 1;
                }
            }
        }
    }


    Station St[10];
    int nmbSt =0;
    cmp = 0;

    for(int i = 0 ; i < nmbOp ; i++)
        OpOrdre[i].mark = 0;



    while(cmp != nmbOp)
    {
        setStation(&St[nmbSt]);

        for(int i = 0 ; i < nmbOp ; i++)
        {
            if(OpOrdre[i].mark == 0)
            {
                if(St[nmbSt].tmp + OpOrdre[i].tmp > tmpCycle)
                {
                    break;
                }
                else
                {
                    addOp(OpOrdre[i],&St[nmbSt]);
                    cmp++;
                    OpOrdre[i].mark = 1;
                }
            }

        }

        nmbSt++;
    }

    afficherStation(St,nmbSt);

}

void Q4(Operation Op[100], int nmbOp, float tmpCycle)
{

    for(int i = 0 ; i < nmbOp ; i++)
    {
        Op[i].mark = 0;
        strcpy(Op[i].couleurExclusion,"none");
    }

    char* listeCouleur[10] =
    {
        "bleu",
        "rouge",
        "vert",
        "jaune",
        "orange",
        "violet",
        "rose",
        "noir",
        "blanc",
        "gris"
    };

    int cmp = 0;
    int end = 0;

    while(end < nmbOp)
    {

        for(int i = 0 ; i< nmbOp ; i++)
        {
            if(strcmp(Op[i].couleurExclusion,"none") == 0)
            {
                int test = 1;
                for(int j = 0 ; j < Op[i].nmbExclusion ; j++)
                {
                    if(strcmp(listeCouleur[cmp],Op[Op[i].exclusion[j]].couleurExclusion) == 0)
                        test = 0;
                }
                if(test == 1)
                {
                    strcpy(Op[i].couleurExclusion,listeCouleur[cmp]);
                    end++;
                }
            }
        }
        cmp++;

    }


    for(int i = 0 ; i < nmbOp ; i++)
        Op[i].mark = 0;

    Operation OpOrdre[100];
    cmp = 0;

    while( cmp != nmbOp)
    {
        for(int i = 0 ; i < nmbOp ; i++)
        {
            if(Op[i].mark == 0)
            {
                if(precedentDecouvert(Op,Op[i]) == 1)
                {
                    OpOrdre[cmp] = Op[i];
                    cmp++;
                    Op[i].mark = 1;
                }
            }
        }
    }


    Station St[10];
    int nmbSt =0;
    cmp = 0;

    for(int i = 0 ; i < nmbOp ; i++)
        OpOrdre[i].mark = 0;

    for(int i = 0 ; i < nmbOp ; i++)
        Op[i].mark = 0;


    while(cmp != nmbOp)
    {
        setStation(&St[nmbSt]);

        for(int i = 0 ; i < nmbOp ; i++)
        {
            if(OpOrdre[i].mark == 0)
            {
                if(strcmp(St[nmbSt].couleur,OpOrdre[i].couleurExclusion) == 0 || strcmp(St[nmbSt].couleur,"none")==0)
                {

                    if(precedentDecouvert(Op,OpOrdre[i]) == 1)
                    {
                        addOp(OpOrdre[i],&St[nmbSt]);
                        cmp++;
                        OpOrdre[i].mark = 1;
                        for(int j = 0 ; j < nmbOp ; j++)
                        {
                            if(OpOrdre[i].n == Op[j].n)
                                Op[j].mark = 1;
                        }

                    }

                }
            }

        }

        nmbSt++;
    }

    afficherStation(St,nmbSt);
}

void Q5(Operation Op[100], int nmbOp, float tmpCycle)
{

    for(int i = 0 ; i < nmbOp ; i++)
    {
        Op[i].mark = 0;
        strcpy(Op[i].couleurExclusion,"none");
    }

    char* listeCouleur[10] =
    {
        "bleu",
        "rouge",
        "vert",
        "jaune",
        "orange",
        "violet",
        "rose",
        "noir",
        "blanc",
        "gris"
    };

    int cmp = 0;
    int end = 0;

    while(end < nmbOp)
    {

        for(int i = 0 ; i< nmbOp ; i++)
        {
            if(strcmp(Op[i].couleurExclusion,"none") == 0)
            {
                int test = 1;
                for(int j = 0 ; j < Op[i].nmbExclusion ; j++)
                {
                    if(strcmp(listeCouleur[cmp],Op[Op[i].exclusion[j]].couleurExclusion) == 0)
                        test = 0;
                }
                if(test == 1)
                {
                    strcpy(Op[i].couleurExclusion,listeCouleur[cmp]);
                    end++;
                }
            }
        }
        cmp++;

    }


    for(int i = 0 ; i < nmbOp ; i++)
        Op[i].mark = 0;

    Operation OpOrdre[100];
    cmp = 0;

    while( cmp != nmbOp)
    {
        for(int i = 0 ; i < nmbOp ; i++)
        {
            if(Op[i].mark == 0)
            {
                if(precedentDecouvert(Op,Op[i]) == 1)
                {
                    OpOrdre[cmp] = Op[i];
                    cmp++;
                    Op[i].mark = 1;
                }
            }
        }
    }


    Station St[10];
    int nmbSt =0;
    cmp = 0;

    for(int i = 0 ; i < nmbOp ; i++)
        OpOrdre[i].mark = 0;

    for(int i = 0 ; i < nmbOp ; i++)
        Op[i].mark = 0;


    while(cmp != nmbOp)
    {
        setStation(&St[nmbSt]);

        for(int i = 0 ; i < nmbOp ; i++)
        {
            if(OpOrdre[i].mark == 0)
            {
                if(strcmp(St[nmbSt].couleur,OpOrdre[i].couleurExclusion) == 0 || strcmp(St[nmbSt].couleur,"none")==0)
                {

                    if(precedentDecouvert(Op,OpOrdre[i]) == 1)
                    {
                        if(St[nmbSt].tmp + OpOrdre[i].tmp <= tmpCycle)
                        {
                            addOp(OpOrdre[i],&St[nmbSt]);
                            cmp++;
                            OpOrdre[i].mark = 1;
                            for(int j = 0 ; j < nmbOp ; j++)
                            {
                                if(OpOrdre[i].n == Op[j].n)
                                    Op[j].mark = 1;
                            }
                        }


                    }

                }
            }

        }

        nmbSt++;
    }

    afficherStation(St,nmbSt);
}




int main()
{
    Operation Op[100];

    int nmbOp = chargerNmbOperation(Op);
    chargerInfoOp(Op,nmbOp);
    float tmpCycle = getTempscycle();

    for(int i = 0 ; i < 101 ; i++)
     {
         system("cls");
         AsciiArt();

         printf("\nchargement des donnees: %d%%",i);
         Sleep(1);

     }
     printf("\n\nDonnes recupere, %d operation enregistre\n",nmbOp);
     system("pause");


    while(1==1)
    {

        system("cls");

        AsciiArt();
        printf("\nMenu\n\n");

        printf("Calculer le nombre de stations en fonction de:\n\n");

        printf("1) Des exclusions\n");
        printf("2) Du temps de cycle et des exclusions\n");
        printf("3) Du temps de cycle et des precedences\n");
        printf("4) Des precedences et des exclusions\n");
        printf("5) Du temps de cycle des precedences et des exclusions\n");

        printf("\nChoix: ");
        int c;
        scanf("%d",&c);
        while(c < 1 || c > 5)
        {
            printf("choix incorrect");
            printf("\nChoix: ");
            scanf("%d",&c);
        }

        if(c == 1)
        {
            Q1(Op,nmbOp,tmpCycle);
        }
        else if(c == 2)
        {
            Q2(Op,nmbOp,tmpCycle);
        }
        else if(c == 3)
        {
            Q3(Op,nmbOp,tmpCycle);
        }
        else if(c == 4)
        {
            Q4(Op,nmbOp,tmpCycle);
        }
        else if(c == 5)
        {
            Q5(Op,nmbOp,tmpCycle);
        }

        printf("\n\n");
        system("pause");
    }



    return 0;
}
