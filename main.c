#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "mapas.h"

void dibujar_celda(char celda);
extern long long validar_mov(char *m, int f, int c);

int main() {
    
    int posX=1;
    int posY=1;
    int fsig, csig;
    int fInicio, cInicio;
    char tecla;

    printf("Iniciando juego...\n");
    printf("Jugador en: (%d, %d)\n", posX, posY);
    
    while (1) {
        system("cls");

        // Ventana 11x11 
        //Prueba en chiquito primero
        fInicio=posX-5;
        if (fInicio<0) fInicio=0;
        if (fInicio>4) fInicio=4;

        cInicio=posY -5;
        if (cInicio<0) cInicio=0;
        if (cInicio>4) cInicio=4;

        for (int f=fInicio; f < fInicio+11; f++) {
            for (int c=cInicio; c<cInicio+11; c++) {
                if (f==posX && c==posY) {
                    printf("P"); // Jugador
                } else {
                    dibujar_celda(mapa_nivel1[f*15+c]);
                }
            }
            printf("\n");
        }

        // Captura de movimiento 
        tecla=getch();
        if (tecla=='q'||tecla=='Q') break;

        fsig=posX;
        csig=posY;

        if (tecla=='w' || tecla=='W') fsig--;
        else if (tecla=='s' || tecla=='S') fsig++;
        else if (tecla=='a' || tecla=='A') csig--;
        else if (tecla=='d' || tecla=='D') csig++;

        // valida con ensambladror
        if (fsig!=posX || csig!=posY) {
            // Llamamos a validarMov en el .asm
            if (validar_mov(mapa_nivel1, fsig, csig)==1) {
                posX =fsig; 
                posY=csig;

                char celda_destino = mapa_nivel1[fsig*15+csig];
            }
        }
    }
    return 0;
}