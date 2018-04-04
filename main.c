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

//les variables suivantes seront modifiees a chaque ajout, suppression, etc..
int idLogements; //dernier Id de la liste logements
int idLocataires; //dernier Id de la liste locataires

int main() {
    int choix;
    //initialisation des listes a partir du fichier
    initLogement(fLogement, &logements, &idLogements);
    initLocataire(fLocataires, &locataires, &idLocataires);
    initLocation(fLocations, &locations);


    // le programme se repete tant que l'utilisateur decide
    while (noExit == 1) {
        system("cls"); //nettoyage de l'ecran a chaque boucle
        printf("Bienvenue au programme \"Gestion de locations\"\n"
                       "\n\t1.Afficher la liste des logements existant"
                       "\n\t2.Afficher la liste des locataires existant"
                       "\n\t3.Afficher la liste des locations existant"
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
                getch(); //fonction non standard do windows qui pause l'execution jusqua apui sur clavier
                break;
            case 2:
                afficherLoc(locataires);
                getch();
                break;
            case 3:
                afficherLct(locations);
                getch();
                break;
            case 4:
                printf("1.Ajouter\n2.Supprimer\n0.Retour\n");
                int choix2 = 0;
                scanf("%d", &choix2);
                //traitement des 2 cas
                switch (choix2) {
                    case 1:
                        ajouterLog(logements, &idLogements);
                        getch();
                        break;
                    /*case 2:
                     * Module suppLogement, a toi nassim */
                    default:
                        break;
                }
                break;
            case 5: //reste a ajouter ici suppLocataire()
                ajouterLoc(locataires, &idLocataires);
                getch();
                break;
            default:
                noExit = 0;
                break;
        }
    }
    //sauvegrade de toute modifications
    sauvLogement(logements, fLogement);
    sauvLocataire(locataires, fLocataires);
    sauvLocation(locations, fLocations);
    liberLogement(logements);
    return 0;
}
