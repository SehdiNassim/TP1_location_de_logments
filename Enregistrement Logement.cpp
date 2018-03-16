//
// Created by X360 on 10/03/2018.
//

#include <stdio.h>
#include "LOG_LLC_BIBLIO.h"

FILE * fLogement;

void enrgLogement(ListeLogement ** tete) {
    fLogement = fopen("logements", "r");
    while (feof(fLogement) != 0) {
        allouerLog(tete);
    }
}

