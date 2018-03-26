/* ***********************************************************************
 *                      PROGRAMME PRINCIPALE
 *                  TP1 : Location de Logements
 * Edite par:  Benmoussat Mouad Sehdi Nassim
 * **********************************************************************/

#include <stdio.h> //Bibliotheque necessaire pour les entrees sories
#include "LOG_LLC_BIBLIO.h"

int noExit = 1; //condition de sortie du programme

FILE * fLogement;
FILE * fLocations;
FILE * fLocataires;

ListeLocataire * locataires;
ListeLogement * logements;
ListeLocation * locations;


int main() {
    initLogment(fLogement, &logements); //initialisation de la liste a partir du fichier
    initLocataire(fLocataires, &locataires);

    while (noExit == 1) { // le programme se repete tant que l'utilisateur decide
        printf("Bienvenue au programme \"Gestion de locations\"\n"
                       "\n\t1.Enregistrer un logement"
                       "\n\t2.Enregistrer un locataire"
                       "\n\t3.Enregistrer une location"
                       "\n\t4.Ajouter/Supprimer un logement"
                       "\n\t5.Ajouter/Supprimer un locataire"
                       "\n\t6.Ajouter/Supprimer une location"
                       "\n\t7.Lister Logement Occupe"
                       "\n\t8.Lister Logements libre a une date"
                       "\n\t9.Consulter L'historique par annee"
                       "\n\t10.Quitter"
                       "\nEntrez votre choix :");

    }
    return 0;
}