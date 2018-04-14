// ------------------------------------------------------------------
// Crée par Benmoussat Mouad, Sehdi Nassim
//
// Bibliotheque contient tous les modeles des LLC, les structures
// ansi que les parties du programmes et autres modules
//---------------------------------------------------
//
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#ifndef TP01_LOG_LLC_BIBLIO_H
#define TP01_LOG_LLC_BIBLIO_H

//Chemin des fichiers de lecture/ecriture

#define LOG_PATH "../logements.txt"            //chemin pour le fichier des logements
#define ARCH_LOG_PATH "../archivelogement.txt" //chemin pour le fichier des archives des logements
#define LOC_PATH "../locataires.txt"           //chemin pour le fichier des locataires
#define ARCH_LOC_PATH "../archivelocataire.txt"//chemin pour le fichier des archives des locatiares
#define LCT_PATH "../locations.txt"            //chemin pour le fichier des locations
#define ARCH_LCT_PATH "../archivelocation.txt" //chemin pour le fichier des archives des locations
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
} FicheLocation;

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

//cette structure sera utilisé pour l'affichage e l'historique
typedef struct Quartier{
    char nomQuartier[25];
    int Nombre;
}FicheHistorique;

typedef struct MaillionQuartier{
    FicheHistorique fiche;
    struct MaillionQuartier * adr;
}ListeHistorique;

/* *********************Les modèles de LLC************************/

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

void liberLocataire(ListeLocataire * cible) {
    //Liberation de tout la liste de la memoire
    ListeLocataire *tmp, *prec;

    tmp = cible;
    while (tmp != NULL) {
        prec = tmp;
        tmp = suivLocataire(tmp);
        free(prec);
    }
}

void liberLocation(ListeLocation * cible) {
    //Liberation de tout la liste de la memoire
    ListeLocation *tmp, *prec;

    tmp = cible;
    while (tmp != NULL) {
        prec = tmp;
        tmp = suivLocation(tmp);
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

void affVal_Lct(ListeLocation *destination, ListeLocation *source) {

    destination->fiche.idLog = source->fiche.idLog;
    destination->fiche.idLoc = source->fiche.idLoc;
    destination->fiche.dateDeb = source->fiche.dateDeb;
    destination->fiche.dateFin = source->fiche.dateFin;
}

void affVal_Log(ListeLogement *destination, ListeLogement *source) { //destination <- source
    destination->fiche.id = source->fiche.id;
    destination->fiche.type = source->fiche.type;
    destination->fiche.loyer = source->fiche.loyer;
    destination->fiche.air = source->fiche.air;
    destination->fiche.distCommune = source->fiche.distCommune;
    strcpy(destination->fiche.nomQuartier, source->fiche.nomQuartier);
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
int Longueurlistelogement(ListeLogement * tete){
    ListeLogement *p=tete;
    int cpt=0;
    while (p!=NULL){
        cpt++;
        p=suivLogement(p);
    }
    return cpt;
}
ListeLogement * IdArchiveLogement(ListeLogement * tete,int ID ){
    ListeLogement * p=tete;
    while (p!=NULL && p->fiche.id!=ID){
        p=suivLogement(p);
    }
    return p;
}
void allouerQartier(ListeHistorique **tete) {
    *tete = malloc(sizeof(struct MaillionQuartier));
}
void affAdrQuartier(ListeHistorique *destination, ListeHistorique *source) {
    destination->adr = source;
}
ListeHistorique * suivQuartier(ListeHistorique *cible) {
    return cible->adr;
}


//******************Modules**************************

void initLogement(FILE *f, ListeLogement **tete, int *cptId) { //Role: lire depuis le fichier et cree la liste
    ListeLogement * tmp, *nouv; //2 Maillion intermediare
    int cpt = 0; //une compteur qui sert a initialiser les id des logements.txt (i.e: leur position dans la liste)

    f = fopen(LOG_PATH, "r"); //ouverture du fichier au mode lecture
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

void initarchiveLogement(FILE *f, ListeLogement **tete, int *cptId) { //Role: lire depuis le fichier archive et cree la liste
    ListeLogement * tmp, *nouv,*p; //2 Maillion intermediare
    int cpt = 0;

    f = fopen(ARCH_LOG_PATH, "r"); //ouverture du fichier au mode lecture
    if (f == NULL) perror("fopen");
    else {
        allouerLog(&tmp);
        *tete = tmp;
        p=*tete;
        while (feof(f) == 0) { //lecture jusqu'a arriver a la fin du fichier
            fscanf(f, "%d %d %[^_]%*s %d", &tmp->fiche.type,
                   &tmp->fiche.air,
                   tmp->fiche.nomQuartier,
                   &tmp->fiche.distCommune);
            //calcul du loyer
            tmp->fiche.loyer = LB[tmp->fiche.type] + ((tmp->fiche.air - SM[tmp->fiche.type]) * 800);
            if (feof(f) != 0) { //cas ou on arrive a la fin apres lecture
                affAdr_Log(tmp, NULL);
            } else {
                allouerLog(&nouv);
                affAdr_Log(tmp, nouv);
                tmp = suivLogement(tmp);
            }
            cpt++;
        }
        *cptId = cpt; //ceci represente implicitement la longueur de la liste
        // mais sert aussi a l'ajout des nouveaux logements (pour eviter le parcours a
        // chque ajout/suppression)
        while (p!=NULL){
            p->fiche.id=-cpt;
            cpt--;
            p=suivLogement(p);
        }
    }
    fclose(f);
}

void initLocataire(FILE * f, ListeLocataire **tete, int *cptId) {
    ListeLocataire * tmp, *nouv; //2 Maillion intermediare
    int cpt = 0; //une compteur qui sert a initialiser les id des logements.txt (i.e: leur position dans la liste)

    f = fopen(LOC_PATH, "r"); //ouverture du fichier au mode lecture
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

void initarchiveLoc(FILE * f, ListeLocataire **tete, int *cptId) {
    ListeLocataire * tmp, *nouv; //2 Maillion intermediare
    int cpt = 0; //un compteur qui sert a initialiser les id des logements.txt (i.e: leur position dans la liste)

    f = fopen(ARCH_LOC_PATH, "r"); //ouverture du fichier archive au mode lecture
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
        *cptId = cpt; //meme chose que pour initLogement
    }
    fclose(f);
}

void initLocation(FILE* f, ListeLocation ** tete) {
    ListeLocation *tmp, *nouv; //2 Maillion intermediare

    f = fopen(LCT_PATH, "r"); //ouverture du fichier au mode lecture
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

void initarchiveLocation(FILE* f, ListeLocation ** tete) {
    ListeLocation *tmp, *nouv; //2 Maillion intermediare

    f = fopen(ARCH_LCT_PATH, "r"); //ouverture du fichier archive au mode lecture
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

    f = fopen(LOG_PATH, "w"); //ouverture en ecriture
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

void sauvarchiveLogement(ListeLogement *tete, FILE *f) {
    ListeLogement *tmp = tete;

    f = fopen(ARCH_LOG_PATH, "w"); //ouverture en ecriture
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

    f = fopen(LOC_PATH, "w");
    tmp = tete;
    while (tmp != NULL) {
        fprintf(f, "%s_ %s_ %s", tmp->fiche.nom, tmp->fiche.prenom, tmp->fiche.numTel);
        tmp = suivLocataire(tmp);
        if (tmp != NULL)
            fprintf(f, "\n");
    }
}

void sauvarchiveLocataire(ListeLocataire *tete, FILE *f) {
    ListeLocataire *tmp;

    f = fopen(ARCH_LOC_PATH, "w");
    tmp = tete;
    while (tmp != NULL) {
        fprintf(f, "%s_ %s_ %s", tmp->fiche.nom, tmp->fiche.prenom, tmp->fiche.numTel);
        tmp = suivLocataire(tmp);
        if (tmp != NULL)
            fprintf(f, "\n");
    }
}

void sauvLocation(ListeLocation *tete, FILE *f) {
    ListeLocation *tmp;

    f = fopen(LCT_PATH, "w");
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

void sauvarchivelocation(ListeLocation *tete, FILE *f) {
    ListeLocation *tmp;

    f = fopen(ARCH_LCT_PATH, "w");
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

    printf("ID  TYPE     SUPERFICIE        QUARTIER        Dst COMM       LOYER \n");
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
    int jour, mois, an;

    printf("ID LOG  ID LOC  Date Deb  Date Fin");
    while (tmp != NULL) {
        an = tmp->fiche.dateDeb % 10000;
        mois = tmp->fiche.dateDeb / 10000 % 100;
        jour = tmp->fiche.dateDeb / 10000 / 100;

        printf("\n%-6d  %-6d  %d/%d/%-8d  ",
               tmp->fiche.idLog, tmp->fiche.idLoc, jour, mois, an);

        an = tmp->fiche.dateFin % 10000;
        mois = tmp->fiche.dateFin / 10000 % 100;
        jour = tmp->fiche.dateFin / 10000 / 100;

        printf("%d/%d/%-8d", jour, mois, an);
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

void ajouterLct(ListeLocation *tete, int dernierIdLog, int dernierIdLoc) {
    //allocaion
    ListeLocation *nouv;
    allouerLct(&nouv);

    ListeLocation *parcour; //sert a parcour la liste
    int err; //booleen verifie si il y a erruer


    //Lecure des information depuis le clavier
    do {
        err = 0;
        printf("Entrez l'ID du logement (voir la liste des logements) : ");
        scanf("%d", &nouv->fiche.idLog);

        //on verifie si il existe
        if (nouv->fiche.idLog > dernierIdLog) {
            err = 1;
            printf("Logement n'exite pas, voir la liste des logements.\n");
        }
        //on verifie si ce logement est loué
        parcour = tete;
        while (parcour != NULL && !err) {
            if (parcour->fiche.idLog == nouv->fiche.idLog) {
                err = 1;
                printf("Logement deja loue, entrez un autre\n");
            }
            parcour = suivLocation(parcour);
        }
    } while (err == 1);

    do {
        err = 0;
        printf("Entrez l'ID du locataire (voir la liste des locatiares) : ");
        scanf("%d", &nouv->fiche.idLoc);

        //on verifie si ce locataire exite
        if (nouv->fiche.idLoc > dernierIdLoc) {
            err = 1;
            printf("Locataire n'exite pas, voir la liste des locataires.\n");
        }
    } while (err == 1);

    printf("Entrez la date du debut sous la forme JJMMAAAA : ");
    scanf("%ld", &nouv->fiche.dateDeb);

    printf("Entrez la date de fin sous la forme JJMMAAAA : ");
    scanf("%ld", &nouv->fiche.dateFin);

    //chainage
    ListeLocation *dernier = tete;
    while (suivLocation(dernier) != NULL) {
        dernier = suivLocation(dernier); //on parcours jusqu'au dernier
    }
    affAdr_Lct(dernier, nouv);
    affAdr_Lct(nouv, NULL);

    printf("\n Location ajoute.\n");
}

int compareDate(long int date1, long int date2) {
    //retourne 0 si: date1 == date2, 1 si: date1 > date2, -1 si: date1 < date2
    int jour1, mois1, an1;
    int jour2, mois2, an2;

    an1 = date1 % 10000;
    mois1 = date1 / 10000 % 100;
    jour1 = date1 / 10000 / 100;

    an2 = date2 % 10000;
    mois2 = date2 / 10000 % 100;
    jour2 = date2 / 10000 / 100;

    if (date1==date2)
        return 0;

    else {
        if (an1 > an2 ||(an1 == an2 && mois1 > mois2) || (an1 == an2 && mois1 == mois2 && jour1 > jour2))
            return 1;
        else
            return -1;
    }
}

void affichLogDate(ListeLogement *teteLog, ListeLocation *teteLct, long int date) {
    ListeLogement *log = teteLog;
    ListeLocation *lct ;
    char *type, *etat;

    printf("LOGEMENT %-28s ETAT\n","");
    while (log != NULL) {
        lct = teteLct; // pour chaque logment on parcours de nouveau la liste des locations

        switch (log->fiche.type) { //Affichage du type du log sous format chaine
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

        int trouv = 0;
        while (lct != NULL && !trouv) {
            if (lct->fiche.idLog == log->fiche.id) { //si le logement est louée
                trouv = 1;
                int cmpFin = compareDate(date, lct->fiche.dateFin); // on compare la date donnée avec la date de fin
                int cmpDeb = compareDate(date, lct->fiche.dateDeb); //on compara la date donnée avec la date de debut
                if ((cmpFin == 0 || cmpFin == -1) && (cmpDeb == 0 || cmpDeb == 1)) { //voir si il est occupé a la date donne
                    etat = "Occuppe";
                }
                else {
                    etat = "Libre";//logement se trouve dans les locations mais libre dans la date donne
                }
                printf("%-2d %-6s %3dm2 %-20s %s\n", log->fiche.id, type, log->fiche.air, log->fiche.nomQuartier, etat);
            }
            lct = suivLocation(lct);
            if (lct == NULL && trouv == 0) {
                etat = "Libre"; //logement ne se trouve pas dans les locations
                printf("%-2d %-6s %3dm2 %-20s %s\n", log->fiche.id, type, log->fiche.air, log->fiche.nomQuartier, etat);
            }
        }
        log = suivLogement(log);
    }
}

void DecIdLog(ListeLogement ** tete) /* Décrémente tout les id des fiches des maillons de la liste pointée par tete*/
{ ListeLogement * p=*tete;
    while (p != NULL){
        (p->fiche).id--;
        p=suivLogement(p);
    }
}

void DecIdLoc(ListeLocataire ** tete) /* Décrémente tout les id des fiches des maillons de la liste pointée par tete*/
{ ListeLocataire * p=*tete;
    while (p != NULL){
        (p->fiche).id--;
        p=suivLocataire(p);
    }
}

void MajLocationlog(ListeLocation ** tete, int ID) {
    // pour mettre a jour les locations apres une suppresion d'un logement
    // ce qui se resume a décrémenter de 1 tout les idlog superieur a l'id du logement supprimé
    ListeLocation *p=*tete;
    while (p != NULL){
        if ((p->fiche).idLog > ID){(p->fiche).idLog--;}
        p=suivLocation(p);
    }
}

void MajLocationloc(ListeLocation ** tete, int ID) {
    // pour mettre a jour les locations apres une suppresion d'un locataire
    // ce qui se resume a decrémenter de 1 tout les idloc superieur a l'id du locataire supprimé
    ListeLocation *p=*tete;
    while (p != NULL){
        if ((p->fiche).idLoc > ID){(p->fiche).idLoc--;}
        p=suivLocation(p);
    }
}

int ExistLocationLog(ListeLocation * tete, int ID ) {
    // retourne 1 si le logement  avec l'id egale a ID est louéet , 0 sinon
    ListeLocation *p;
    int l=0;
    p=tete;
    while ((p!=NULL) && l==0){
     if ((p->fiche).idLog ==ID){l=1;}
     p=suivLocation(p);
    }
    return l;
}

int ExistLocationLoc(ListeLocation * tete, int ID ) {
    // retourne 1 si le locataire  avec l'id egale a ID occupe un logement , 0 sinon
    ListeLocation *p;
    int l=0;
    p=tete;
    while ((p!=NULL) && l==0){
        if ((p->fiche).idLoc ==ID){l=1;}
        p=suivLocation(p);
    }
    return l;
}

void insertarchivelog(ListeLogement ** tete,ListeLogement * p){
    //on l'utilise pour inserer un logement dans les archives
    //
    p->fiche.id=-(Longueurlistelogement(*tete)+1);
    affAdr_Log(p,*tete);
    *tete=p;

}

void insertarchiveloc(ListeLocataire ** tete,ListeLocataire * p){
    //on l'utilise pour inserer un locataire dans les archives
    //
    affAdr_Loc(p,*tete);
    *tete=p;
}

void insertarchivelocation(ListeLocation ** tete,ListeLocation * p){
    //on l'utilise pour inserer une location dans les archives
    //
    affAdr_Lct(p,*tete);
    *tete=p;
}

void supp_log(ListeLogement **tete1, ListeLocation * tete2, ListeLogement ** tete3,ListeLocation ** tete4){
    //on l'utilise pour supprimer un logement
    //
    ListeLogement *p=*tete1, *q;
    ListeLocation *w=*tete4;
    int ID;
    printf("Donnez l'id du logement que vous voulez supprimer:" );
    scanf("%d",&ID);
    if (ID==1){
        if (ExistLocationLog(tete2,ID)==1){
            printf("Suppression impossible ,logement loué ");
        }
        else{while (w!=NULL){
                if (w->fiche.idLog==ID){w->fiche.idLog=-Longueurlistelogement(*tete3)-1; }
                w=suivLocation(w);
            }
            *tete1=suivLogement(*tete1);
            printf("Le Logement selectionne a etait supprime");
            DecIdLog(tete1);
            insertarchivelog(tete3 ,p);
        }
    }
    else{
        while((p!=NULL) &&((p->fiche).id!=ID)){ q=p ;
        p=suivLogement(p);}
        if (p==NULL){
            printf("Impossible de trouver un logement avec cet ID");
        }
        else{
            if (ExistLocationLog(tete2,ID)==1){printf("Suppression impossible ,logement loué ");}
            else{printf("Le Logement selectionne a etait supprime");
                affAdr_Log(q,suivLogement(p));
                q=suivLogement(p);
                DecIdLog(&q);
                while (w!=NULL){
                    if (w->fiche.idLog==ID){w->fiche.idLog=-Longueurlistelogement(*tete3)-1; }
                    w=suivLocation(w);
                }
                insertarchivelog(tete3 ,p);

            }
        }
    }
    MajLocationlog(&tete2,ID);


}

void supp_loc(ListeLocataire **tete1,ListeLocation * tete2,ListeLocataire ** tete3){
    //on l'utilise pour supprimer un locataire
    //
    ListeLocataire *p=*tete1, *q;
    int ID;
    printf("Donnez l'id du locataire que vous voulez supprimer:" );
    scanf("%d",&ID);
    if (ID==1){
        if (ExistLocationLoc(tete2,ID)==1){
            printf("Suppression impossible ,locataire toujours present ");
        }
        else{*tete1=suivLocataire(*tete1);
            DecIdLoc(tete1);
            insertarchiveloc(tete3,p);
        }
    }
    else{
        while((p!=NULL) &&((p->fiche).id!=ID)){q=p ;
            p=suivLocataire(p);}
        if (p==NULL){
            printf("Impossible de trouver un locataire avec cet ID");
        }
        else{
            if (ExistLocationLoc(tete2,ID)==1){printf("Suppression impossible ,locataire toujours present ");}
            else{printf("%-20s %10s a etait supprimé",(p->fiche).nom,(p->fiche).prenom);
                affAdr_Loc(q,suivLocataire(p));
                q=suivLocataire(p);
                DecIdLoc(&q);
                insertarchiveloc(tete3,p);
            }
        }
    }
    MajLocationloc(&tete2,ID);
}

void supp_location(ListeLocation **tete, ListeLocation **tete2){
    //on l'utilise pour supprimer une location
    //
    ListeLocation *p=*tete,*q;
    int idloc,idlog,trouv=0;
    printf("Entrez l'id du locataire: ");
    scanf("%d",&idloc);
    printf("Entrez l'id du logement: ");
    scanf("%d",&idlog);
    while (p!=NULL && trouv==0){
        if((idlog ==(p->fiche).idLog) && (idloc ==(p->fiche).idLoc)){
            if (p==*tete){*tete=suivLocation(*tete); }
            else { affAdr_Lct(q,suivLocation(p)); }
            insertarchivelocation(tete2,p);
            trouv=1;
        }
        else {q=p;
        p=suivLocation(p);}
    }
    if (p==NULL){ printf("Il n'existe pas de location avec le locataire et le logement que vous avez ecrit ");}

}

void ListLocTyplog(ListeLocation * tete1,ListeLogement * tete2,ListeLocataire * tete3,int ID , ListeLocataire ** tete4){
    //On l'utilise pour donner la liste des locataires occupant un logement de meme type et dont la superficie est superieure a la superficie moyenne
    //
    *tete4=NULL;
    ListeLocataire * q,*w;
    ListeLocation * p=tete1;
    while (p!=NULL){
        if ((idLogement(tete2,(p->fiche).idLog)->fiche).type==ID && (idLogement(tete2,(p->fiche).idLog)->fiche).air > SM[ID])
        {if (*tete4==NULL){allouerLoc(tete4);
                (*tete4)->fiche=(idLocataire(tete3,(p->fiche).idLoc))->fiche;
                affAdr_Loc(*tete4,NULL);
            q=*tete4;}
         else {allouerLoc(&w);
                w->fiche=(idLocataire(tete3,(p->fiche).idLoc))->fiche;
                affAdr_Loc(w,NULL);
                affAdr_Loc(q,w);
               q=suivLocataire(q);
            }
        affAdr_Loc(q,NULL);}
        p=suivLocation(p);
    }
    afficherLoc(*tete4);

}

void triLogementLoyer(ListeLocation *teteLct, ListeLogement *teteLog) {
    ListeLocation *studio, *f2, *f3, *f4;
    ListeLocation *q1, *q2, *q3, *q4;
    ListeLocation *nouv, *listeTrie;

    ListeLogement *logCourant;

    studio = f2 = f3 = f4 = NULL; //initialisation

    //eclatement de la liste, on ne modifie pas la liste initial
    ListeLocation *parcour = teteLct;
    while (parcour != NULL) {
        logCourant = idLogement(teteLog, parcour->fiche.idLog); //retourne l'adresse du logment sepcifié dans la location

        if (logCourant->fiche.type == 0) {
            allouerLct(&nouv);
            affVal_Lct(nouv, parcour);
            affAdr_Lct(nouv, NULL);
            if (studio == NULL) {
                studio = nouv;
            } else {
                affAdr_Lct(q1, nouv);
            }
            q1 = nouv;
        } else if (logCourant->fiche.type == 1) {
            allouerLct(&nouv);
            affVal_Lct(nouv, parcour);
            affAdr_Lct(nouv, NULL);
            if (f2 == NULL) {
                f2 = nouv;
            } else {
                affAdr_Lct(q2, nouv);
            }
            q2 = nouv;
        } else if (logCourant->fiche.type == 2) {
            allouerLct(&nouv);
            affVal_Lct(nouv, parcour);
            affAdr_Lct(nouv, NULL);
            if (f3 == NULL) {
                f3 = nouv;
            } else {
                affAdr_Lct(q3, nouv);
            }
            q3 = nouv;
        } else if (logCourant->fiche.type == 3) {
            allouerLct(&nouv);
            affVal_Lct(nouv, parcour);
            affAdr_Lct(nouv, NULL);
            if (f4 == NULL) {
                f4 = nouv;
            } else {
                affAdr_Lct(q4, nouv);
            }
            q4 = nouv;
        }
        parcour = suivLocation(parcour);
    }


    //tri de chaque liste de location selon le loyer, par principe de bulle
    //---tri de la liste des studios
    ListeLocation *p; //sert a permuter les valeurs
    allouerLct(&p);

    ListeLocation *suiv;
    q1 = studio;

    if (q1 != NULL){
        suiv = suivLocation(q1);
    } else
        suiv = NULL;

    ListeLogement *suivLogCourant;
    int ordone = 0;

    if (suiv != NULL) {
        while (!ordone) {
            ordone = 1;
            logCourant = idLogement(teteLog, q1->fiche.idLog);
            suivLogCourant = idLogement(teteLog, suiv->fiche.idLog);

            if (logCourant->fiche.loyer > suivLogCourant->fiche.loyer) {
                ordone = 0;
                affVal_Lct(p, q1);
                affVal_Lct(q1, suiv);
                affVal_Lct(suiv, p);
            }

            q1 = suiv;
            suiv = suivLocation(suiv);
            if (suiv == NULL && !ordone) {
                //si on arrive a la fin et la liste et non trié on revien au debut
                q1 = studio;
                suiv = suivLocation(q1);
            }
        }
    }

    //tri de la liste des F2
    q2 = f2;
    if (q2 != NULL) {
        suiv = suivLocation(q2);
    } else {
        suiv = NULL;
    }
    ordone = 0;

    if (suiv != NULL) {
        while (!ordone) {
            ordone = 1;
            logCourant = idLogement(teteLog, q2->fiche.idLog);
            suivLogCourant = idLogement(teteLog, suiv->fiche.idLog);

            if (logCourant->fiche.loyer > suivLogCourant->fiche.loyer) {
                ordone = 0;
                affVal_Lct(p, q2);
                affVal_Lct(q2, suiv);
                affVal_Lct(suiv, p);
            }

            q2 = suiv;
            suiv = suivLocation(suiv);
            if (suiv == NULL && !ordone) {
                //si on arrive a la fin et la liste et no trie on revien au debut
                q2 = f2;
                suiv = suivLocation(q2);
            }
        }
    }

    //tri de la liste des F3
    q3 = f3;
    if (q3 != NULL) {
        suiv = suivLocation(q3);
    } else {
        suiv = NULL;
    }
    ordone = 0;

    if (suiv != NULL) {
        while (suiv != NULL && !ordone) {
            ordone = 1;
            logCourant = idLogement(teteLog, q3->fiche.idLog);
            suivLogCourant = idLogement(teteLog, suiv->fiche.idLog);

            if (logCourant->fiche.loyer > suivLogCourant->fiche.loyer) {
                ordone = 0;
                affVal_Lct(p, q3);
                affVal_Lct(q3, suiv);
                affVal_Lct(suiv, p);
            }

            q3 = suiv;
            suiv = suivLocation(suiv);
            if (suiv == NULL && !ordone) {
                q3 = f3;
                suiv = suivLocation(q3);
            }
        }
    }

    //tri de la liste des F4
    q4 = f4;
    if (q4 != NULL  ) {
        suiv = suivLocation(q4);
    } else {
        suiv = NULL;
    }
    ordone = 0;

    if (suiv != NULL) {
        while (!ordone) {
            ordone = 1;
            logCourant = idLogement(teteLog, q4->fiche.idLog);
            suivLogCourant = idLogement(teteLog, suiv->fiche.idLog);

            if (logCourant->fiche.loyer > suivLogCourant->fiche.loyer) {
                ordone = 0;
                affVal_Lct(p, q4);
                affVal_Lct(q4, suiv);
                affVal_Lct(suiv, p);
            }

            q4 = suiv;
            suiv = suivLocation(suiv);
            if (suiv == NULL && !ordone) {
                q4 = f4;
                suiv = suivLocation(q4);
            }
        }
    }

    //Liaison de toute les listes 2 par 2
    //--studio avec F1
    int debut = 1;
    ListeLocation *tete1;
    while (studio != NULL && f2 != NULL) {

        //acces au logement spécifié par la location
        logCourant = idLogement(teteLog, studio->fiche.idLog);
        suivLogCourant = idLogement(teteLog, f2->fiche.idLog);

        //On compare les loyers des location 2 à 2 et on change le chainage selon l'ordre
        if (logCourant->fiche.loyer <= suivLogCourant->fiche.loyer) {

            if (debut) { //si on est au debut de la liste
                tete1 = studio; //on garde la tete1
                p = studio; //p va servir à un pointeur vers le dernier maillion chainé
                suiv = suivLocation(studio);
                affAdr_Lct(studio, f2);
                studio = suiv;
                debut = 0;
            } else {
                affAdr_Lct(p, studio); //chainage du maillion precdent avec le courant
                suiv = suivLocation(studio); //pour ne pas perdre le suivant
                affAdr_Lct(studio, f2);
                p = studio; //le dernier maillion chainé est consideré comme le precedent
                studio = suiv;
            }
        } else {
            if (debut) {
                tete1 = f2;
                p = f2;
                suiv = suivLocation(f2);
                affAdr_Lct(f2, studio);
                f2 = suiv;
                debut = 0;
            } else {
                affAdr_Lct(p, f2);
                suiv = suivLocation(f2);
                affAdr_Lct(f2, studio);
                p = f2;
                studio = suiv;
            }
        }
    } // tete1 est obetnue en fusionnant les deux listes "studio" et "f2"
    if (debut == 1) { //si la boucle ne s'est pas executé
        if (studio == NULL && f2 == NULL) {
            tete1 = NULL;
        } else if (studio == NULL) {
            tete1 = f2;
        } else if (f2 == NULL) {
            tete1 = studio;
        }
    }

    //--tete1 avec F3
    debut = 1;
    ListeLocation *tete2;
    while (tete1 != NULL && f3 != NULL) {

        //acces au logement spécifié par la location
        logCourant = idLogement(teteLog, tete1->fiche.idLog);
        suivLogCourant = idLogement(teteLog, f3->fiche.idLog);

        //On compare les loyers des location 2 à 2 et on change le chainage selon l'ordre
        if (logCourant->fiche.loyer <= suivLogCourant->fiche.loyer) {

            if (debut) { //si on est au debut de la liste
                tete2 = tete1; //on garde la tete1
                p = tete1; //p va servir à un pointeur vers le dernier maillion chainé
                suiv = suivLocation(tete1);
                affAdr_Lct(tete1, f3);
                tete1 = suiv;
                debut = 0;
            } else {
                affAdr_Lct(p, tete1); //chainage du maillion precdent avec le courant
                suiv = suivLocation(tete1); //pour ne pas perdre le suivant
                affAdr_Lct(tete1, f3);
                p = tete1; //le dernier maillion chainé est consideré comme le precedent
                tete1 = suiv;
            }
        } else {
            if (debut) {
                tete2 = f3;
                p = f3;
                suiv = suivLocation(f3);
                affAdr_Lct(f3, tete1);
                f3 = suiv;
                debut = 0;
            } else {
                affAdr_Lct(p, f3);
                suiv = suivLocation(f3);
                affAdr_Lct(f3, tete1);
                p = f3;
                tete1 = suiv;
            }
        }
    } //tete2 est obtenue en fusionannt tete1 avec f3
    if (debut) {
        if (tete1 == NULL && f3 == NULL) {
            tete2 = NULL;
        } else if (tete1 == NULL) {
            tete2 = f3;
        } else if (f3 == NULL) {
            tete2 = tete1;
        }
    }

    debut = 1;
    while (tete2 != NULL && f4 != NULL) {

        //acces au logement spécifié par la location
        logCourant = idLogement(teteLog, tete2->fiche.idLog);
        suivLogCourant = idLogement(teteLog, f4->fiche.idLog);

        //On compare les loyers des location 2 à 2 et on change le chainage selon l'ordre
        if (logCourant->fiche.loyer <= suivLogCourant->fiche.loyer) {

            if (debut) { //si on est au debut de la liste
                listeTrie = tete2; //on garde la tete1
                p = tete2; //p va servir à un pointeur vers le dernier maillion chainé
                suiv = suivLocation(tete2);
                affAdr_Lct(tete2, f4);
                tete2 = suiv;
                debut = 0;
            } else {
                affAdr_Lct(p, tete2); //chainage du maillion precdent avec le courant
                suiv = suivLocation(tete2); //pour ne pas perdre le suivant
                affAdr_Lct(tete2, f4);
                p = tete2; //le dernier maillion chainé est consideré comme le precedent
                tete2 = suiv;
            }
        } else {
            if (debut) {
                listeTrie = f4;
                p = f4;
                suiv = suivLocation(f4);
                affAdr_Lct(f4, tete2);
                f4 = suiv;
                debut = 0;
            } else {
                affAdr_Lct(p, f4);
                suiv = suivLocation(f4);
                affAdr_Lct(f4, tete2);
                p = f4;
                tete2 = suiv;
            }
        }
    } //listeTrie est obtenue en fusionnant tete2 avec f4
    if (debut) {
        if (tete2 == NULL && f4 == NULL)
            listeTrie = NULL;
        else if (tete2 == NULL) {
            listeTrie = f4;
        } else if (f4 == NULL) {
            listeTrie = tete2;
        }
    }

    //affichage de la liste trié
    parcour = listeTrie;
    int jourDeb, moisDeb, anDeb;
    int jourFin, anFin, moisFin;

    printf("ID LOG ID LOC      Date Debut%7sDate Fin%11sLoyer\n","","");
    while (parcour != NULL) {
        anDeb = parcour->fiche.dateDeb % 10000;
        moisDeb = parcour->fiche.dateDeb/ 10000 % 100;
        jourDeb = parcour->fiche.dateDeb/ 10000 / 100;

        anFin = parcour->fiche.dateFin % 10000;
        moisFin = parcour->fiche.dateFin / 10000 % 100;
        jourFin = parcour->fiche.dateFin / 10000 / 100;
        
        logCourant = idLogement(teteLog, parcour->fiche.idLog);

        printf("%5d %5d  %8d/%2d/%-6d  %5d/%2d/%-6d  %10.0f DZD\n", parcour->fiche.idLog, parcour->fiche.idLoc, jourDeb,
               moisDeb, anDeb,
               jourFin, moisFin, anFin, logCourant->fiche.loyer);

        parcour = suivLocation(parcour);
    }
}

ListeLogement * prochCommune(ListeLogement *tete) {
    //retourne une liste trié par les logement les plus proche de la commune et ayany un loyer minimale
    ListeLogement *courant, *suivant;

    //On crée une toute nouvelle liste pour ne pas modifier la liste courante
    ListeLogement *nouv, *listeTrie;

    int debut = 1;

    //On copie la liste courante dans une nouvelle Liste
    courant = tete;
    while (courant != NULL) {
        allouerLog(&nouv);
        affVal_Log(nouv, courant);
        affAdr_Log(nouv, NULL);
        if (debut) {
            listeTrie = nouv;
            debut = 0;
        } else {
            affAdr_Log(suivant, nouv);
        }
        suivant = nouv;
        courant = suivLogement(courant);
    }
    if (courant == NULL && debut == 1) {
        listeTrie = NULL;
    }
    //listeTrie est une copie de tete


    //On tri la liste selon deux critére: la distanceComm la plus petite, si egaux alors le loyer le plus petit
    courant = listeTrie;
    int permute = 1;

    if (courant != NULL) {
        suivant = suivLogement(courant);
        while (suivant != NULL || permute) {
            if (courant->fiche.distCommune > suivant->fiche.distCommune) {
                //simple permutation
                allouerLog(&nouv);
                affVal_Log(nouv, courant);
                affVal_Log(courant, suivant);
                affVal_Log(suivant, nouv);
                permute = 1;
            } else if (courant->fiche.distCommune == suivant->fiche.distCommune) {
                //si ils ont la même distance alors on verifie le loyer
                if (courant->fiche.loyer > suivant->fiche.loyer) {
                    allouerLog(&nouv);
                    affVal_Log(nouv, courant);
                    affVal_Log(courant, suivant);
                    affVal_Log(suivant, nouv);
                    permute = 1;
                }
            }
            courant = suivant;
            suivant = suivLogement(suivant);

            if (suivant == NULL && permute) {
                courant = listeTrie;
                suivant = suivLogement(courant);
                permute = 0;
            }
        }
    }
    return listeTrie;
}


void Histo1(ListeLocation * tete1, ListeLocation * tete2, ListeLogement * tete3,ListeLogement * tete4,ListeHistorique * tete5 )
{    //On l'utilise pour la question 1 de l'historique
    //
    ListeHistorique *p, *d;
    ListeLocation *q = tete1, *w = tete2;
    printf("Entrez l'annee :");
    int ANNEE;
    scanf("%d", &ANNEE);
    tete5=NULL;
    while (q != NULL) {
        if (q->fiche.dateDeb % 10000 == ANNEE || q->fiche.dateFin % 10000 == ANNEE) {
            if (tete5 == NULL) {
                allouerQartier(&tete5);
                strcpy(((tete5)->fiche.nomQuartier), (idLogement(tete3, q->fiche.idLog)->fiche.nomQuartier));
                (tete5)->fiche.Nombre = 1;
                p = tete5;
                affAdrQuartier(tete5, NULL);
            } else {
                while (suivQuartier(p) != NULL &&
                       strncmp(idLogement(tete3, q->fiche.idLog)->fiche.nomQuartier, p->fiche.nomQuartier,
                               strlen(p->fiche.nomQuartier)) != 0) {

                    p = suivQuartier(p);
                }
                if (strncmp(idLogement(tete3, q->fiche.idLog)->fiche.nomQuartier, p->fiche.nomQuartier,
                            strlen(p->fiche.nomQuartier)) == 0) { p->fiche.Nombre++; }
                else {
                    allouerQartier(&d);
                    strcpy(((d)->fiche.nomQuartier), (idLogement(tete3, q->fiche.idLog)->fiche.nomQuartier));
                    (d)->fiche.Nombre = 1;
                    affAdrQuartier(p, d);
                    affAdrQuartier(d, NULL);
                }
            }
        }
        q = suivLocation(q);
        p = tete5;
    }
    while (w != NULL) {
        if (w->fiche.dateDeb % 10000 == ANNEE || w->fiche.dateFin % 10000 == ANNEE) {
            if (w->fiche.idLog > 0) {
                if (tete5 == NULL) {
                    allouerQartier(&tete5);
                    strcpy(((tete5)->fiche.nomQuartier), (idLogement(tete3, w->fiche.idLog)->fiche.nomQuartier));
                    (tete5)->fiche.Nombre = 1;
                    affAdrQuartier(tete5, NULL);
                } else {
                    while (suivQuartier(p) != NULL &&
                           strncmp(idLogement(tete3, w->fiche.idLog)->fiche.nomQuartier, p->fiche.nomQuartier, strlen(p->fiche.nomQuartier)) != 0) {
                        p = suivQuartier(p);
                    }
                    if (strncmp(idLogement(tete3, w->fiche.idLog)->fiche.nomQuartier, p->fiche.nomQuartier,
                                strlen(p->fiche.nomQuartier)) == 0) {
                        p->fiche.Nombre++; }
                    else {
                        allouerQartier(&d);
                        strcpy(((d)->fiche.nomQuartier), (idLogement(tete3, w->fiche.idLog)->fiche.nomQuartier));
                        (d)->fiche.Nombre = 1;
                        affAdrQuartier(p, d);
                        affAdrQuartier(d, NULL);
                    }
                }

            } else {
                if (tete5 == NULL) {
                    allouerQartier(&tete5);
                    strcpy(((tete5)->fiche.nomQuartier), (IdArchiveLogement(tete4, w->fiche.idLog)->fiche.nomQuartier));
                    (tete5)->fiche.Nombre = 1;
                    p = tete5;
                    affAdrQuartier(tete5, NULL);
                } else {
                    while (suivQuartier(p) != NULL &&
                           strncmp(IdArchiveLogement(tete4, w->fiche.idLog)->fiche.nomQuartier, p->fiche.nomQuartier,
                                   strlen(p->fiche.nomQuartier)) !=
                           0) {

                        p = suivQuartier(p);
                    }
                    if (strncmp(IdArchiveLogement(tete4, w->fiche.idLog)->fiche.nomQuartier, p->fiche.nomQuartier,
                                strlen(p->fiche.nomQuartier)) ==
                        0) { p->fiche.Nombre++; }
                    else {
                        allouerQartier(&d);
                        strcpy(((d)->fiche.nomQuartier), (IdArchiveLogement(tete4, w->fiche.idLog)->fiche.nomQuartier));
                        (d)->fiche.Nombre = 1;
                        affAdrQuartier(p, d);
                        affAdrQuartier(d, NULL);
                    }
                }
            }
        }
        p = tete5;
        w = suivLocation(w);
    }
    p = tete5;
    if (p==NULL){ printf("Il y a pas eu de location en %d",ANNEE);}
    else {while (p != NULL) {
        printf("* Dans le quartier %-20s il y a eu %d location(s) \n", p->fiche.nomQuartier, p->fiche.Nombre);
        p = suivQuartier(p);
    }}

}


void Histo2(ListeLocation * tete1, ListeLocation * tete2,ListeLogement * tete3, ListeLogement * tete4 ) {
    //On l'utilise pour la question 2 de l'historique
    //

    ListeLocation *p = tete1, *q = tete2;
    int cpt0, cpt1, cpt2, cpt3, ANNEE;

    cpt0 = cpt1 = cpt2 = cpt3 = 0;

    printf("Entrez l'annee :");
    scanf("%d",&ANNEE);
    while(p!=NULL){
        if (p->fiche.dateDeb % 10000 == ANNEE || p->fiche.dateFin % 10000 == ANNEE){
            switch(idLogement(tete3,p->fiche.idLog)->fiche.type){
                case 0: ++cpt0;
                    break;
                case 1: ++cpt1;
                    break;
                case 2: ++cpt2;
                    break;
                case 3: ++cpt3;
                    break;
                default: break;
            }
        }
        p=suivLocation(p);
    }
    while (q!=NULL){
        if (q->fiche.dateDeb % 10000 == ANNEE || q->fiche.dateFin % 10000 == ANNEE) {
            if (q->fiche.idLog > 0) {
                switch (idLogement(tete3, q->fiche.idLog)->fiche.type) {
                    case 0:
                        ++cpt0;
                        break;
                    case 1:
                        ++cpt1;
                        break;
                    case 2:
                        ++cpt2;
                        break;
                    case 3:
                        ++cpt3;
                        break;
                    default:
                        break;
                }
            } else {

                switch (IdArchiveLogement(tete4, p->fiche.idLog)->fiche.type) {
                    case 0:
                        ++cpt0;
                        break;
                    case 1:
                        ++cpt1;
                        break;
                    case 2:
                        ++cpt2;
                        break;
                    case 3:
                        ++cpt3;
                        break;
                    default:
                        break;
                }
            }
        }
        q = suivLocation(q);
    }
    printf("Pour l'annee %d : \n\t * %d fois studios loues"
                   "\n\t * %d fois F2 loues\n\t * %d fois F3 loues"
                   "\n\t * %d fois F4 loues",
           ANNEE, cpt0, cpt1, cpt2, cpt3);
}
#endif //TP01_LOG_LLC_BIBLIO_H