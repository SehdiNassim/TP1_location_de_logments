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
    int id; //permettant d'identifier le logement, represante reelement la position du maillion dans
    // la liste
    int type;
    int air;
    char nomQuartier[25]; //chaine a une taille cste
    int distCommune;
    int distLoyer;
    int Etat; // = 1 si occupé, 0 sinon
} FicheLogement;

//Definition du type Locataire
typedef struct Locataire {
    int id; //un entier permettant d'identifer le locataire (position dans la liste)
    char nom[25];
    char prenom[25];
    char numTel[11];
} FicheLocataire;

//Definition du type Location
typedef struct Location {
    int idLog;  //Id du logement de la location
    int idLoc; //Id du locataire du logement
    Date dateDeb;
    Date dateFin;
    int loyer;
} FicheLocation;

/* *********************Les modèles de LLC************************/
typedef struct MaillionLogement {
    FicheLogement fiche;
    struct MaillionLogement * adr;
} ListeLogement;

typedef struct MaillionLocataire {
    FicheLocataire fiche;
    struct MaillionLocataire * adr;
} ListeLocataire;

typedef  struct MaillionLocation {
    FicheLocation fiche;
    struct MaillionLocation * adr;
} ListeLocation;

//Modeles d'allocation, affectation et autres
void allouerLog(ListeLogement ** tete) {
    *tete = malloc(sizeof(ListeLogement));
}

void allouerLct(ListeLocation ** tete) {
    *tete = malloc(sizeof(struct MaillionLocation));
}

void allouerLoc(ListeLocataire **tete) {
    *tete = malloc(sizeof(struct MaillionLocataire));
}

FicheLogement ficheLogement(ListeLogement * tete) {
    return tete->fiche;
}

ListeLogement * suivLogement(ListeLogement *cible) {
    return cible->adr;
}
ListeLocataire * suivLocataire(ListeLocataire *cible)  {
    return cible->adr;
}

void liberLogement(ListeLogement * cible) {
    free(cible);
}


void affAdr_Log(ListeLogement *destination, ListeLogement *source) {
    destination->adr = source;
}

void affAdr_Loc(ListeLocataire *destination, ListeLocataire *source) {
    destination->adr = source;
}




//Todo: initLogements, initLocataires
//******************Modules**************************
void initLogment(FILE * f, ListeLogement ** tete) { //Role: lire depuis le fichier et cree la liste
    ListeLogement * tmp, *nouv; //2 Maillion intermediare
    int cpt = 0; //une compteur qui sert a initialiser les id des logements (i.e: leur position dans la liste)

    f = fopen("../logements", "r"); //ouverture du fichier au mode lecture
    allouerLog(&tmp);
    *tete = tmp;
    while (feof(f) == 0) { //lecture jusqu'a arriver a la fin du fichier
        fscanf(f, "%d %d %[^_]%*s %d %d", &tmp->fiche.type,
               &tmp->fiche.air,
               tmp->fiche.nomQuartier,
               &tmp->fiche.distCommune,
               &tmp->fiche.distLoyer);
        cpt++;
        tmp->fiche.id = cpt;
        if (feof(f) != 0) { //cas ou on arrive a la fin apres lecture
            affAdr_Log(tmp, NULL);
        }
        else {
            allouerLog(&nouv);
            affAdr_Log(tmp, nouv);
            tmp = suivLogement(tmp);
        }
    }
    fclose(f);
}

void initLocataire(FILE * f, ListeLocataire **tete) {
    ListeLocataire * tmp, *nouv; //2 Maillion intermediare
    int cpt = 0; //une compteur qui sert a initialiser les id des logements (i.e: leur position dans la liste)

    f = fopen("../locataires", "r"); //ouverture du fichier au mode lecture
    allouerLoc(&tmp);
    *tete = tmp;
    while (feof(f) == 0) { //lecture jusqu'a arriver a la fin du fichier
        fscanf(f, "%[^_]%*s %[^_]%*s %s", tmp->fiche.nom, tmp->fiche.prenom, tmp->fiche.numTel);
        cpt++;
        tmp->fiche.id = cpt;
        if (feof(f) != 0) { //cas ou on arrive a la fin apres lecture
            affAdr_Loc(tmp, NULL);
        }
        else {
            allouerLoc(&nouv);
            affAdr_Loc(tmp, nouv);
            tmp = suivLocataire(tmp);
        }
    }
    fclose(f);
}

void initLocation(FILE* f, ListeLocation ** tete) {

}




#endif //TP01_LOG_LLC_BIBLIO_H
