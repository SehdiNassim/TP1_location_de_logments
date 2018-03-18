//
// Crée par Benmoussat Mouad, Sehdi Nassim le 08/03/2018
//
// Bibliotheque contient tous les modeles des LLC, les structures et les modules
//
#include <stdio.h>
#include <malloc.h>

#ifndef TP01_LOG_LLC_BIBLIO_H
#define TP01_LOG_LLC_BIBLIO_H

//******DEFINITION DES TYPES UTILISE***************************
//Definition des types de logement, chaque type aura la valeur 0,1,2,3 respectivement
typedef enum {studio = 0, F1, F2, F3} Typelog;

//Declaration des constantes de LB et de SM dans deux tableaux
// Accessible par type du logement      e.g: LB[studio] == 15000 DA, SM[F2] == 65 m²
// pour faciliter le calcul automatique du loyer
const long int LB[F3 + 1] = {15000, 20000, 30000, 40000}; //tableau des LBs
const int SM[F3 + 1] = {20, 45, 65, 85}; //tableau des SMs

//Definition du type date
typedef struct {
    int jour;
    int mois;
    int an;
} Date;

//Definition du type Logement
typedef struct Logement {
    int id; //permettant d'identifier le logement
    int type;
    int air;
    char* nomQuartier;
    int distCommune;
    int distLoyer;
    int Etat; // = 1 si occupé, 0 sinon
} FicheLogement;

//Definition du type Locataire
typedef struct Locataire {
    int id; //un entier permettant d'idantifer le locataire
    char* nom;
    char* prenom;
    int numTel;
} FicheLocataire;

//Definition du type Location
typedef struct Location {
    int idLog;  //Id du logement de la location
    int idLoc; //Id du locataire du logement
    Date dateDeb;
    Date dateFin;
    int loyer;
} FicheLocation;

//todo: modeles LLC

/* *********************Les modèles de LLC************************/
//Definition du type Liste Logement (LLC des logements)
typedef struct MaillionLogement {
    FicheLogement fiche;
    struct MaillionLogement * adr;
} ListeLogement;

//Definition du type Liste Locataire (LLC des locataires)
typedef struct MaillionLocataire {
    FicheLocataire fiche;
    struct MaillionLocataire * adr;
} ListeLocataire;

//Definition du type Liste Location (LLC des Location)
typedef  struct MaillionLocation {
    FicheLocation fiche;
    struct MaillionLocation * adr;
} ListeLocation;

void allouerLog(ListeLogement ** tete) {
    *tete = malloc(sizeof(ListeLogement));
}

void allouerLct(ListeLocation ** tete) {
    *tete = malloc(sizeof(struct MaillionLocation));
}

void allouerLoc(ListeLocataire **tete) {
    *tete = malloc(sizeof(struct MaillionLocataire));
}

FicheLogement Fiche(ListeLogement * tete) {
    return tete->fiche;
}

void affAdr_Log(ListeLogement *distination, ListeLogement *source) {
    distination->adr = source;
}




//Todo: initLogements, initLocataires
//******************Modules**************************



#endif //TP01_LOG_LLC_BIBLIO_H
