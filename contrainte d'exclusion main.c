#include <stdio.h>
#include <stdlib.h>

// Structure pour la matrice d'adjacence
typedef struct {
    int** matrice;
    int tailleMat;
} Adjacence;

// Structure pour représenter une station et les opérations qui lui sont attribuées
typedef struct {
    int* operations;
    int compteur;
} Station;

// Fonction pour initialiser la matrice d'adjacence
Adjacence initMatrice(int taille) {
    Adjacence adjMatrice;
    adjMatrice.tailleMat = taille;

    // Allouer de la mémoire pour la matrice
    adjMatrice.matrice = (int**)malloc((taille + 1) * sizeof(int*));
    for (int i = 1; i <= taille; i++) {
        adjMatrice.matrice[i] = (int*)malloc((taille + 1) * sizeof(int));
        for (int j = 1; j <= taille; j++) {
            adjMatrice.matrice[i][j] = 0;  // Initialiser à zéro
        }
    }

    return adjMatrice;
}

// Fonction pour lire les contraintes depuis le fichier et mettre à jour la matrice d'adjacence
void Contraintes(FILE* fichier, Adjacence* adjMatrice) {
    int op1, op2;

    // Lire les contraintes du fichier et les ajouter dans la matrice
    while (fscanf(fichier, "%d %d", &op1, &op2) == 2) {
        adjMatrice->matrice[op1][op2] = 1;
        adjMatrice->matrice[op2][op1] = 1;
    }
}

// Fonction pour libérer la mémoire allouée pour la matrice
void freeM(Adjacence* adjMatrice) {
    for (int i = 1; i <= adjMatrice->tailleMat; i++) {
        free(adjMatrice->matrice[i]);
    }
    free(adjMatrice->matrice);
}

// Fonction pour répartir les opérations par station
void assignOperations(const Adjacence* adjMatrice) {
    int maxStations = 1;  // Nombre initial de stations
    Station* stations = (Station*)malloc(maxStations * sizeof(Station));

    // Initialiser la première station
    stations[0].operations = (int*)malloc((adjMatrice->tailleMat + 1) * sizeof(int));
    stations[0].compteur = 0;

    // Liste pour stocker les paires d'opérations incompatibles
    int** incompatibles = (int**)malloc(adjMatrice->tailleMat * sizeof(int*));
    for (int i = 1; i <= adjMatrice->tailleMat; i++) {
        incompatibles[i - 1] = (int*)malloc((adjMatrice->tailleMat + 1) * sizeof(int));
        for (int j = 1; j <= adjMatrice->tailleMat; j++) {
            incompatibles[i - 1][j] = 0;
        }
    }

    // Trouver les paires d'opérations incompatibles
    for (int i = 1; i <= adjMatrice->tailleMat; i++) {
        for (int j = i + 1; j <= adjMatrice->tailleMat; j++) {
            if (adjMatrice->matrice[i][j] == 1) {
                incompatibles[i - 1][j] = 1;
                incompatibles[j - 1][i] = 1;
            }
        }
    }

    // Afficher les paires d'opérations incompatibles
    printf("Operations non effectuables par la meme station :\n");
    for (int i = 1; i <= adjMatrice->tailleMat; i++) {
        for (int j = i + 1; j <= adjMatrice->tailleMat; j++) {
            if (incompatibles[i - 1][j] == 1) {
                printf("%d et %d\n", i, j);
            }
        }
    }
    printf("\n");

    // Attribuer les opérations aux stations
    for (int i = 1; i <= adjMatrice->tailleMat; i++) {
        int attribue = 0;
        // Parcourir les stations existantes
        for (int j = 0; j < maxStations; j++) {
            int b = 0;
            // Vérifier si l'opération est réalisable avec les opérations déjà attribuées à la station
            for (int k = 0; k < stations[j].compteur; k++) {
                if (incompatibles[i - 1][stations[j].operations[k]] == 1) {
                    b = 1;
                    break;
                }
            }
            // Si pas de conflit, attribuer l'opération à la station
            if (!b) {
                stations[j].operations[stations[j].compteur++] = i;
                attribue = 1;
                break;
            }
        }
        // Si toutes les stations sont occupées, ajouter une nouvelle station
        if (!attribue) {
            maxStations++;
            stations = (Station*)realloc(stations, maxStations * sizeof(Station));
            stations[maxStations - 1].operations = (int*)malloc((adjMatrice->tailleMat + 1) * sizeof(int));
            stations[maxStations - 1].compteur = 0;
            stations[maxStations - 1].operations[stations[maxStations - 1].compteur++] = i;
        }
    }

    // Afficher la répartition des opérations par station
    printf("\nRepartition des operations par station :\n");
    for (int i = 0; i < maxStations; i++) {
        printf("Station %d : ", i + 1);
        for (int j = 0; j < stations[i].compteur; j++) {
            printf("%d ", stations[i].operations[j]);
        }
        printf("\n");
    }

    // Libérer la mémoire allouée
    for (int i = 0; i < maxStations; i++) {
        free(stations[i].operations);
    }
    free(stations);

    for (int i = 1; i <= adjMatrice->tailleMat; i++) {
        free(incompatibles[i - 1]);
    }
    free(incompatibles);
}


int main() {
    FILE* fichier = fopen("exclusions.txt", "r");

    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    int maxOperation = 0;  // pour déterminer la taille de la matrice
    int op1, op2;

    // Trouver le nombre maximum d'opérations
    while (fscanf(fichier, "%d %d", &op1, &op2) == 2) {
        maxOperation = (op1 > maxOperation) ? op1 : maxOperation;
        maxOperation = (op2 > maxOperation) ? op2 : maxOperation;
    }

    // Réinitialiser le curseur du fichier
    fseek(fichier, 0, SEEK_SET);

    // Initialiser la matrice d'adjacence
    Adjacence adjMatrice = initMatrice(maxOperation);

    // Lire les contraintes et mettre à jour la matrice
    Contraintes(fichier, &adjMatrice);

    // Fermer le fichier
    fclose(fichier);

    // Répartir les opérations par station
    assignOperations(&adjMatrice);

    // Libérer la mémoire allouée
    freeM(&adjMatrice);

    return 0;
}
