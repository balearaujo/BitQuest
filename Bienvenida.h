#ifndef BIENVENIDA_H
#define BIENVENIDA_H
#include <stdio.h>

#define BLOQUES_KIUT 254 

void pantallaBienvenida() {

    char* logo[] = {
        "  ####   #  #####   ###   #   #  #####  ####  ##### ",
        "  #   #  #    #    #   #  #   #  #     #        #   ",
        "  ####   #    #    #   #  #   #  ###    ####    #   ",
        "  #   #  #    #    #   #  #   #  #          #   #   ",
        "  ####   #    #     ###    ###   #####  ####    #   "
    };

    for(int i=0; i<54; i++){ printf("\x1b[38;5;21m%c\x1b[0m", BLOQUES_KIUT); }
    printf("\n");

    for (int i=0; i<5; i++) {
        for (int j=0; logo[i][j]!='\0'; j++) {
            if (logo[i][j]=='#') {
                printf("\x1b[36;1m%c\x1b[0m", BLOQUES_KIUT);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    for(int i=0; i<54; i++) {printf("\x1b[38;5;21m%c\x1b[0m", BLOQUES_KIUT);}
    printf("\n");

    printf("           [ RECOLECTA LAS MONEDAS Y ESCAPA ]                    \n");
    printf("             >> Presiona ENTER para jugar <<                     \n\n");
}

#endif 