/* ***********************************************************************
 *                      PROGRAMME PRINCIPALE
 *                  TP1 : Location de Logements
 * Edite par:  Benmoussat Mouad Sehdi Nassim
 * **********************************************************************/

#include <stdio.h> //Bibliotheque necessaire pour les entrees sories
#include <conio.h>
#include "LOG_LLC_BIBLIO.h"

int noExit = 1; //condition de sortie du programme

FILE * fLogement;
FILE * fLocations;
FILE * fLocataires;

ListeLocataire * locataires;
ListeLogement * logements;
ListeLocation * locations;



int main() {
    int choix;
    //initialisation des listes a partir du fichier
    initLogement(fLogement, &logements);
    initLocataire(fLocataires, &locataires);
    initLocation(fLocations, &locations, logements);


    // le programme se repete tant que l'utilisateur decide
    while (noExit == 1) {
        system("cls"); //nettoyage de l'ecran a chaque boucle
        printf("Bienvenue au programme \"Gestion de locations\"\n"
                       "\n\t1.Afficher la liste des logements"
                       "\n\t2.Afficher la liste des locataires"
                       "\n\t3.Afficher la liste des locations "
                       "\n\t4.Ajouter/Supprimer un logement"
                       "\n\t5.Ajouter/Supprimer un locataire"
                       "\n\t6.Ajouter/Supprimer une location"
                       "\n\t7.Lister Logement Occupe"
                       "\n\t8.Lister Logements libre a une date"
                       "\n\t9.Consulter L'historique par annee"
                       "\n\t10.Quitter"
                       "\nEntrez votre choix :");
        scanf("%d", &choix);
        system("cls");

        //traitement selon le choix
        switch (choix) {
            case 1:
                afficherLog(logements);
                getch();
                break;
            default:
                noExit = 0;
                break;
        }
    }
    return 0;
}
