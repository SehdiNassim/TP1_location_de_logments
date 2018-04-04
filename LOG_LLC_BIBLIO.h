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
    //Liberation de tout la liste de la memoire
    ListeLogement *tmp, *prec;

    tmp = cible;
    while (tmp != NULL) {
        prec = tmp;
        tmp = suivLogement(tmp);
        free(prec);
    }
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
    int cpt = 1;
    ListeLogement *p = tete;

    if (id == 1) {
        return tete;
    }
    else {
        if (id != 0) {
            while (cpt != id && p != NULL) {
                p = suivLogement(p);
                cpt++;
            }
            return p;
        }
        else
            return NULL;
    }
}

ListeLocataire * idLocataire(ListeLocataire * tete, int id) {
    //retourne l'adresse du maillion a la position id
    int cpt = 1;
    ListeLocataire *p = tete;

    if (id == 1) {
        return tete;
    }
    else {
        if (id != 0) {
            while (cpt < id && p != NULL) {
                p = suivLocataire(p);
                cpt++;
            }
            return p;
        }
        else
            return NULL;
    }
}


//******************Modules**************************

void initLogement(FILE *f, ListeLogement **tete, int *cptId) { //Role: lire depuis le fichier et cree la liste
    ListeLogement * tmp, *nouv; //2 Maillion intermediare
    int cpt = 0; //une compteur qui sert a initialiser les id des logements.txt (i.e: leur position dans la liste)

    f = fopen("../logements.txt", "r"); //ouverture du fichier au mode lecture
    if (f == NULL) perror("fopen");
    else {
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
            } else {
                allouerLog(&nouv);
                affAdr_Log(tmp, nouv);
                tmp = suivLogement(tmp);
            }
        }
        *cptId = cpt; //ceci represente implicitement la longueur de la liste
        // mais sert aussi a l'ajout des nouveaux logements (pour eviter le parcours a
        // chque ajout/suppression)
    }
    fclose(f);
}

void initLocataire(FILE * f, ListeLocataire **tete, int *cptId) {
    ListeLocataire * tmp, *nouv; //2 Maillion intermediare
    int cpt = 0; //une compteur qui sert a initialiser les id des logements.txt (i.e: leur position dans la liste)

    f = fopen("../locataires.txt", "r"); //ouverture du fichier au mode lecture
    if (f == NULL) {
        perror("fopen");
    } else {
        allouerLoc(&tmp);
        *tete = tmp;
        while (feof(f) == 0) { //lecture jusqu'a arriver a la fin du fichier
            fscanf(f, "%[^_]%*s %[^_]%*s %s\n", tmp->fiche.nom, tmp->fiche.prenom, tmp->fiche.numTel);
            cpt++;
            tmp->fiche.id = cpt;
            if (feof(f) != 0) { //cas ou on arrive a la fin apres lecture (i.e: derniere ligne)
                affAdr_Loc(tmp, NULL);
            } else {
                allouerLoc(&nouv);
                affAdr_Loc(tmp, nouv);
                tmp = suivLocataire(tmp);
            }
        }
        *cptId = cpt; //meme chose pour initLogement
    }
    fclose(f);
}

void initLocation(FILE* f, ListeLocation ** tete) {
    ListeLocation *tmp, *nouv; //2 Maillion intermediare

    f = fopen("../locations.txt", "r"); //ouverture du fichier au mode lecture
    if (f == NULL) {
        perror("fopen");
    } else {
        allouerLct(&tmp);
        *tete = tmp;
        while (feof(f) == 0) {
            //lecture jusqu'a arriver a la fin du fichier
            fscanf(f, "%d %d %ld %ld", &tmp->fiche.idLog, &tmp->fiche.idLoc,
                   &tmp->fiche.dateDeb,
                   &tmp->fiche.dateFin);

            if (feof(f) != 0) { //cas ou on arrive a la fin apres lecture
                affAdr_Lct(tmp, NULL);
            } else {
                allouerLct(&nouv);
                affAdr_Lct(tmp, nouv);
                tmp = suivLocation(tmp);
            }
        }
    }
    fclose(f);
}

void sauvLogement(ListeLogement *tete, FILE *f) {
    ListeLogement *tmp = tete;

    f = fopen("../logements.txt", "w"); //ouverture en ecriture
    if (f != NULL) {
        while (tmp != NULL) {
            fprintf(f, "%d %d %s_ %d",
                    tmp->fiche.type, tmp->fiche.air, tmp->fiche.nomQuartier, tmp->fiche.distCommune);
            tmp = suivLogement(tmp);
            if (tmp != NULL)
                fprintf(f, "\n");
        }
    } else {
        perror("fopen");
    }
    fclose(f);
}

void sauvLocataire(ListeLocataire *tete, FILE *f) {
    ListeLocataire *tmp;

    f = fopen("../locataires.txt", "w");
    tmp = tete;
    while (tmp != NULL) {
        fprintf(f, "%s_ %s_ %s_", tmp->fiche.nom, tmp->fiche.prenom, tmp->fiche.numTel);
        tmp = suivLocataire(tmp);
        if (tmp != NULL)
            fprintf(f, "\n");
    }
}

void sauvLocation(ListeLocation *tete, FILE *f) {
    ListeLocation *tmp;

    f = fopen("../locations.txt", "w");
    tmp = tete;
    while (tmp != NULL) {
        fprintf(f, "%d %d %ld %ld",
                tmp->fiche.idLog, tmp->fiche.idLoc, tmp->fiche.dateDeb, tmp->fiche.dateFin);
        tmp = suivLocation(tmp);
        if (tmp != NULL) {
            fprintf(f, "\n");
        }
    }
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
        printf("%-20s %10s%-20s %10s%-12s %10s %d\n",
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

void ajouterLog(ListeLogement *tete, int *id) {
    //On risque pas de modifier la tete donc on fait pas un passage par var
    ListeLogement *nouv;

    allouerLog(&nouv); //on alloue un nouveau logement
    //lecture des infirmations essentiels apartir du clavier
    do {
        printf("Quel est le type du logement (0:studio, 1:F2, 2:F3, 3:F4) : ");
        scanf("%d", &nouv->fiche.type);
    } while (nouv->fiche.type > 3 || nouv->fiche.type < 0);

    printf("Quel est sa superficie :");
    scanf("%d", &nouv->fiche.air);
    fflush(stdin); //sert a restaurer le fichier d'entree pour eviter la lecture du \n dans
    // la lecture du nom de quartier

    printf("Entrez le nom du quartier (terminant par \".\"): ");
    scanf("%[^.]%*s", nouv->fiche.nomQuartier);

    printf("Distance entre quartier et commune : ");
    scanf("%d", &nouv->fiche.distCommune);

    //calcul de loyer
    nouv->fiche.loyer = LB[nouv->fiche.type] + (nouv->fiche.air - SM[nouv->fiche.type]) * 800;

    //affectation d'id
    (*id)++; //incrementation car on ajoute un nouveau logement
    nouv->fiche.id = *id;

    //chainage dans la liste
    ListeLogement *dernier = idLogement(tete, (*id)-1); //le dernier maillion de la liste
    affAdr_Log(dernier, nouv);
    affAdr_Log(nouv, NULL);

    //Affichage des modifications
    printf("\n Votre logement a pour ID: %d\n", nouv->fiche.id);
    printf("\n Le Loyer est de: %.0f DZD", nouv->fiche.loyer);
}

void ajouterLoc(ListeLocataire *tete, int *id) {
    //allocation d'un nouveau maillion
    ListeLocataire *nouv;
    allouerLoc(&nouv);

    //On lit depuis le clavier
    fflush(stdin);
    printf("Entrez le nom du locataire (terminon par \".\") :");
    scanf("%[^.]%*s", nouv->fiche.nom);
    fflush(stdin);

    printf("Entrez le prenom du locataire (terminon par \".\") : ");
    scanf("%[^.]%*s", nouv->fiche.prenom);
    fflush(stdin);

    printf("Entre le numero du telephone (terminon par \".\") : ");
    scanf("%[^.]%*s", nouv->fiche.numTel);

    //Chainage
    ListeLocataire *dernier = idLocataire(tete, *id);
    affAdr_Loc(dernier, nouv);
    affAdr_Loc(nouv, NULL);

    //Affectation d'ID
    (*id)++;
    nouv->fiche.id = *id;

    printf("Votre locataire a pour ID : %d", nouv->fiche.id);
}

void ajouterLct(ListeLocation *tete) {
    //allocaion
    ListeLocation *nouv;
    allouerLct(&nouv);

    //Lecure des information depuis le clavier
    printf("Entrez l'ID du logement (voir la liste des logements) : ");
    scanf("%d", &nouv->fiche.idLog);

    printf("Entrez l'ID du locatair (voir la liste des locatiares) : ");
    scanf("%d", &nouv->fiche.idLoc);

    printf("Entrez la date du debut sous la forme JJMMAAAA : ");
    scanf("%ld", &nouv->fiche.dateDeb);

    printf("Entrez la date de fin sous la forme JJMMAAAA : ");
    scanf("%ld", &nouv->fiche.dateFin);

    //chainage
    ListeLocation *dernier = tete;
    while (suivLocation(dernier) != NULL) {
        dernier = suivLocation(dernier);
    }
    affAdr_Lct(dernier, nouv);
    affAdr_Lct(nouv, NULL);
}

//todo: Module SuppLogement() et autres, a toi de reflichir nassim

#endif //TP01_LOG_LLC_BIBLIO_H
