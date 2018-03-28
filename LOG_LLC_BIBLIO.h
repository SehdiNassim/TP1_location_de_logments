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

//Definition du type Logement
typedef struct Logement {
    int id; //permettant d'identifier le logement, represante reelement la position du maillion dans
    // la liste
    int type;
    int air;
    char nomQuartier[25]; //chaine a une taille cste
    int distCommune;
    //faute de comprehension d'enonce, distLoyer na pas de sense
    float loyer;
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
    int idLog;  //Id du logement de logement
    int idLoc; //Id du locataire du locataire
    long int dateDeb;  //format date : JJMMAAAA
    long int dateFin;
    //Loyer ne caracterise pas la location
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
ListeLocation * suivLocation(ListeLocation *cible) {
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

void affAdr_Lct(ListeLocation *destination, ListeLocation *source) {
    destination->adr = source;
}

ListeLogement * idLogement(ListeLogement * tete,int id) { //retourne l'adresse du maillion a la postion id
    int cpt = 0;
    ListeLogement *p = tete;

    if (id != 0) {
       while (cpt != id && p != NULL) {
           p = suivLogement(p);
           cpt++;
        }
    }
    return p;
}

ListeLocataire * idLocataire(ListeLocataire * tete, int id) {
    //retourne l'adresse du maillion a la position id
    int cpt = 0;
    ListeLocataire *p = tete;

    if (id != 0) {
        while (cpt != id && p != NULL) {
            p = suivLocataire(p);
            cpt++;
        }
    }
    return p;
}


//******************Modules**************************

void initLogement(FILE *f, ListeLogement **tete) { //Role: lire depuis le fichier et cree la liste
    ListeLogement * tmp, *nouv; //2 Maillion intermediare
    int cpt = 0; //une compteur qui sert a initialiser les id des logements (i.e: leur position dans la liste)

    f = fopen("../logements", "r"); //ouverture du fichier au mode lecture
    allouerLog(&tmp);
    *tete = tmp;
    while (feof(f) == 0) { //lecture jusqu'a arriver a la fin du fichier
        fscanf(f, "%d %d %[^_]%*s %d", &tmp->fiche.type,
               &tmp->fiche.air,
               tmp->fiche.nomQuartier,
               &tmp->fiche.distCommune);
        //affectation de ID
        cpt++;
        tmp->fiche.id = cpt;
        //calcul du loyer
        tmp->fiche.loyer = LB[tmp->fiche.type] + ((tmp->fiche.air - SM[tmp->fiche.type]) * 800);
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
        fscanf(f, "%[^_]%*s %[^_]%*s %[^_]%*s", tmp->fiche.nom, tmp->fiche.prenom, tmp->fiche.numTel);
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

void initLocation(FILE* f, ListeLocation ** tete, ListeLogement *teteLog) {
    ListeLocation *tmp, *nouv; //2 Maillion intermediare
    ListeLogement *log;

    f = fopen("../locations", "r"); //ouverture du fichier au mode lecture
    allouerLct(&tmp);
    *tete = tmp;
    while (feof(f) == 0) {
        //lecture jusqu'a arriver a la fin du fichier
        fscanf(f, "%d %d %ld %ld", &tmp->fiche.idLog, &tmp->fiche.idLoc,
               &tmp->fiche.dateDeb,
               &tmp->fiche.dateFin);

        if (feof(f) != 0) { //cas ou on arrive a la fin apres lecture
            affAdr_Lct(tmp, NULL);
        }
        else {
            allouerLct(&nouv);
            affAdr_Lct(tmp, nouv);
            tmp = suivLocation(tmp);
        }
    }
    fclose(f);
}

void afficherLog(ListeLogement * tete) {
    ListeLogement *tmp = tete;
    char * type; //chaine qui contient le type du logement

    printf("ID  TYPE     SUPERFICIE        QUARTIER        Dst COMM    LOYER \n");
    while (tmp != NULL) {
        switch (tmp->fiche.type) { //Affichage du type du log sous format chaine
            case 0:
                type = "Studio";
                break;
            case 1:
                type = "F2";
                break;
            case 2:
                type = "F3";
                break;
            case 3:
                type = "F4";
                break;
            default:
                type = "XXX"; //en cas d'erreur
        }
        printf("%2d  %7s  %9dm  %20s  %8dm  %8.0f DZD\n", tmp->fiche.id,
               type, tmp->fiche.air, tmp->fiche.nomQuartier, tmp->fiche.distCommune, tmp->fiche.loyer);
        tmp = suivLogement(tmp);
    }
}

void afficherLoc(ListeLocataire *tete) {
    ListeLocataire *tmp = tete;

    printf("NOM %25s PRENOM %23s NUM %18s ID\n","","","");

    while (tmp != NULL) {
        printf("%-20s %10s%-20s %10s%-12s %10s%d",
               tmp->fiche.nom, "", tmp->fiche.prenom, "", tmp->fiche.numTel, "",
               tmp->fiche.id);
        tmp = suivLocataire(tmp);
    }
}

void afficherLct(ListeLocation * tete) {
    ListeLocation *tmp = tete;

    printf("ID LOG  ID LOC  Date Deb  Date Fin");
    while (tmp != NULL) {
        printf("\n%-6d  %-6d  %-8ld  %-8ld",
               tmp->fiche.idLog, tmp->fiche.idLoc, tmp->fiche.dateDeb, tmp->fiche.dateFin);
        tmp = suivLocation(tmp);
    }
}

/*void ajouterLog(ListeLocation *tete) {
    //On risque pas de modifier la tete donc on fait pas un passage par var
    ListeLogement *nouv;

    allouerLog(&nouv); //on alloue un nouveau logement
    printf("Quel est le type du logement (0:studio, 1:F2, 2:F3, 3:F4) : ");
    scanf("%d", &nouv->fiche.type);
    printf("Quel est sa superficie :");
    scanf("%d", &nouv->fiche.air);
    printf("Entrez le nom du quartier : ");
    scanf("%s", nouv->fiche.nomQuartier);
    printf("Distance entre quartier et commune");
    scanf("%d", &nouv->fiche.distCommune);
    printf("Distance entre Loyer et commune")
}*/


#endif //TP01_LOG_LLC_BIBLIO_H
