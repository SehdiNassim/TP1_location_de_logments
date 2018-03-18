//
// Created by X360 on 17/03/2018.
//

#include <stdio.h>
#include "LOG_LLC_BIBLIO.h"

FILE * f;


int main() {
    ListeLogement *tmp;
    ListeLogement *nouv;
    ListeLogement *p ;
    ListeLogement * teteLog = NULL;

//    f = fopen("../logements", "r");
//    allouerLog(&teteLog);
//    tmp = teteLog;
//    while (feof(f) == 0) {
//        scanf("%d", &(tmp->fiche.type));
//        allouerLog(&p);
//        affAdr_Log(tmp, p);
//        tmp = p;
//    }

    allouerLog(&tmp);
    scanf("%d", &(tmp->fiche.type));

    printf("%d", tmp->fiche.type);
    return 0;
}

