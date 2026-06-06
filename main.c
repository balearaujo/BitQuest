#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "mapas.h"

void dibujar_celda(char celda);
extern long long validar_mov(char *m, int f, int c);
extern long long cnt_monedas(char *m, int t, char moneda);

int main() {
    
    int posX=1;
    int posY=1;
    int fsig, csig;
    int fInicio, cInicio;
    char tecla;

    printf("Iniciando juego...\n");
    printf("Jugador en: (%d, %d)\n", posX, posY);
    long long totalMonedas=cnt_monedas(mapa_nivel1, 3600, 'M');

    while (1) {
        system("cls");

        // Ventana 20X20
        //ya ahora si
        fInicio=posX-10; //aqui la mitad
        if (fInicio<0) fInicio=0;
        if (fInicio>40) fInicio=40; //11-7=4 d antes  ==== 60-20=40

        cInicio=posY -10;
        if (cInicio<0) cInicio=0;
        if (cInicio>40) cInicio=40;

        for (int f=fInicio; f < fInicio+20; f++) { //esto es d camara tia
            for (int c=cInicio; c<cInicio+20; c++) {
                if (f==posX && c==posY) {
                    printf("P"); // Jugador
                } else {
                    dibujar_celda(mapa_nivel1[f*60+c]);
                }
            }
            printf("\n");
        }
        long long monedasRestantes=cnt_monedas(mapa_nivel1, 3600, 'M');
        long long monedasJugador=totalMonedas-monedasRestantes;
        printf("Monedas recolectadas: %lld \n", monedasJugador);

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

                if (mapa_nivel1[posX * 60 + posY] == 'M') {
                    mapa_nivel1[posX * 60 + posY] = '.'; // Se vuelve suelo
                }
                char celda_destino = mapa_nivel1[fsig*20+csig];
                if (celda_destino=='E'){
                    printf("Ganaste!!!");
                    printf("Conseguiste: %d de %d", monedasJugador, totalMonedas);
                }
            }
        }
    }
    return 0;
}