/* ***********************************************************************
 *                      PROGRAMME PRINCIPALE
 *                  TP1 : Location de Logements
 * Edite par:  Benmoussat Mouad Sehdi Nassim
 * **********************************************************************/

#include <stdio.h> //Bibliotheques necessaire pour les entrees sories
#include <conio.h>
#include "LOG_LLC_BIBLIO.h"

int noExit = 1; //condition de sortie du programme

FILE * fLogement;
FILE * fLocations;
FILE * fLocataires;
FILE * farchivelogement;
FILE * farchivelocataire;
FILE * farchivelocation;


ListeLocataire * locataires,*archivelocataire,*Lstudio,*LF2,*LF3,*LF4;
ListeLogement * logements,*archivelogements;
ListeLocation * locations , *archivelocation;
ListeHistorique * historiqueQuartier;
//les variables suivantes seront modifiees a chaque ajout, suppression, etc..
int idLogements,idarchiveLogements; //dernier Id de la liste logements
int idLocataires,idarchivelocataire; //dernier Id de la liste locataires

int main() {
    int choix;
    //initialisation des listes a partir du fichier
    initLogement(fLogement, &logements, &idLogements);
    initarchiveLogement(farchivelogement, &archivelogements, &idarchiveLogements);
    initarchiveLoc(farchivelocataire,&archivelocataire,&idarchivelocataire);
    initLocataire(fLocataires, &locataires, &idLocataires);
    initLocation(fLocations, &locations);
    initarchiveLocation(farchivelocation,&archivelocation);



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
                       "\n\t7.Lister les logements selon une date"
                       "\n\t8.Trier la liste des logements selon le loyer"
                       "\n\t9.Consulter L'historique par annee"
                       "\n\t10.afficher les archives"
                       "\n\t11.afficher les locataires occupant un logement de meme type et dont l'air est superieur a la SM"
                       "\n\t12.Sauvegarder et Quitter"
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
                    case 2:
                        supp_log(&logements,locations,&archivelogements,&archivelocation);
                        getch();
                     /* Module suppLogement, a toi nassim */
                    default:
                        break;
                }
                break;
            case 5: //reste a ajouter ici suppLocataire()
                printf("1.Ajouter\n2.Supprimer\n0.Retour\n");
                int choix3 = 0;
                scanf("%d", &choix3);
                //traitement des 2 cas
                switch (choix3) {
                    case 1:
                        ajouterLoc(locataires, &idLocataires);
                        getch();
                        break;
                    case 2:
                        supp_loc(&locataires,locations,&archivelocataire);
                        getch();

                    default:
                        break;
                }
                break;
            case 6:
                printf("1.Ajouter\n2.Supprimer\n0.Retour\n");
                int choix4 = 0;
                scanf("%d", &choix4);
                //traitement des 2 cas
                switch (choix4) {
                    case 1:
                        ajouterLct(locations, idLogements, idLocataires);
                        getch();
                        break;
                    case 2:
                        supp_location(&locations,&archivelocation);
                        getch();
                    default:
                        break;
                }
                break;
            case 7:
                printf("Entrez date sous forme JJMMAAAA: \n");
                long int date = 0;
                scanf("%ld", &date);
                system("cls");
                affichLogDate(logements, locations, date);
                getch();
                break;
            case 8:
                triLogementLoyer(locations, logements);
                getch();
                break;
            case 9:
                printf("1.Nombre de location par quartier\n"
                       "2.Nombre de location par type de logement\n");
                int choix9;
                scanf("%d",&choix9);
                switch(choix9){
                    case 1:
                        Histo1(locations,archivelocation,logements,archivelogements,historiqueQuartier);
                        getch();
                        break;
                    case 2:
                        Histo2(locations,archivelocation,logements,archivelogements);
                        getch();
                        break;
                    default:
                        getch();
                        break;
                }
                break;
            case 10:
                printf("1.Archive des logement\n2.Archive des locataires\n3.Archive des location\n0.Retour");
                int choix10;
                scanf("%d",&choix10);
                system("cls");
                switch(choix10){
                    case 1 :
                        afficherLog(archivelogements);
                        getch();
                        break;
                    case 2 :
                        afficherLoc(archivelocataire);
                        getch();
                        break;
                    case 3 :
                        afficherLct(archivelocation);
                        getch();
                        break;
                    default:
                        break;
                }
                break;
            case 11:
                printf("Choisissez le type de logement :\n 1.Studio \n 2.F2 \n 3.F3 \n 4.F4 \n");
                Typelog choix11;
                scanf("%d",&choix11);
                switch(choix11){
                    case 1:
                        ListLocTyplog(locations,logements,locataires,0,&Lstudio);
                        getch();
                        break;
                    case 2:
                        ListLocTyplog(locations,logements,locataires,1,&LF2);
                        getch();
                        break;
                    case 3:
                        ListLocTyplog(locations,logements,locataires,2,&LF3);
                        getch();
                        break;
                    case 4:
                        ListLocTyplog(locations,logements,locataires,3,&LF4);
                        getch();
                        break;
                    default: getch();
                        break;
                }
                break;
            case 12:
                noExit = 0;
                break;
            default:
                system("cls");
                break;
        }
    }
    //sauvegrade de toute modifications
    sauvLogement(logements, fLogement);
    sauvarchiveLogement(archivelogements,farchivelogement);
    sauvLocataire(locataires, fLocataires);
    sauvarchiveLocataire(archivelocataire,farchivelocataire);
    sauvLocation(locations, fLocations);
    sauvarchivelocation(archivelocation,farchivelocation);
    //puis on libere la memoire
    liberLogement(logements);
    liberLogement(archivelogements);
    liberLocation(locations);
    liberLocation(archivelocation);
    liberLocataire(locataires);
    liberLocataire(archivelocataire);
    return 0;
}
