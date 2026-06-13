#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "mapas.h"

void dibujar_celda(char celda);
extern long long validar_mov(char *m, int columnas, int f, int c);
extern long long cnt_monedas(char *m, int t, char moneda);
extern long long detectar_obj(char *m,int ancho, int f, int c, char obj);
extern long long cnt_espacios(char *m, int t, char espacios);
extern long long puntaje ( long long monedas, long long pasos, long long niveles);

int main() {
    
    int posX=1;
    int posY=1;
    int fsig, csig;
    int fInicio, cInicio;
    int tieneLlave=0;
    char celda_destino;
    char tecla;
    char *mapa_actual;
    int nivel=1;
    int pasos=0;

    printf("Iniciando juego...\n");
    printf("Jugador en: (%d, %d)\n", posX, posY);


    long long totalMonedas=cnt_monedas(mapa_nivel1, 3600, 'M');
    long long totalEspacios=cnt_espacios(mapa_nivel1, 3600, '.');

    printf("Monedas a recolectar en el mapa: %lld\n", totalMonedas);
    printf("Total de espacios para moverse: %lld\n", totalEspacios);
    printf("Seleccione cualquier tecla para continuar: \n");
    getchar();

    mapa_actual=mapa_nivel1;

    while (1) {
        system("cls");

        // Ventana 20X20
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
                    dibujar_celda(mapa_actual[f*60+c]);
                }
            }
            printf("\n");
        }


        long long monedasRestantes=cnt_monedas(mapa_actual, 3600, 'M');
        long long monedasJugador=totalMonedas-monedasRestantes;


        printf("NIVEL %d\n", nivel);
        printf("Monedas recolectadas: %lld / %lld\n", monedasJugador);
        printf("Total de espacios en el nivel: %lld \n", totalEspacios);
        printf("Pasos: %d\n", pasos);

        if (tieneLlave==0){ 
            printf("No tienes la llave\n");
        } else {
            printf("Tiene llaves la llave!\n"); }
        
        printf ("Controles: W A S D | SALIR: Q\n");
        
        // Captura de movimiento 
        tecla=getch();
        if (tecla=='q'||tecla=='Q') break;

        fsig=posX;
        csig=posY;

        int movimiento=0;
        if (tecla=='w' || tecla=='W') {fsig--; movimiento=1;}
        else if (tecla=='s' || tecla=='S') {fsig++; movimiento=1;}
        else if (tecla=='a' || tecla=='A') {csig--; movimiento=1;}
        else if (tecla=='d' || tecla=='D') {csig++; movimiento=1;}

        if (movimiento){
            if (validar_mov(mapa_actual, 60, fsig, csig)==1) {
                pasos++;
                celda_destino=mapa_actual[fsig*60+csig];

                if(celda_destino=='D'){
                    if (tieneLlave){
                        printf("\nLograste abrir la puerta del mal\n");
                        mapa_actual[fsig * 60 + csig] = '.';
                        posX=fsig;
                        posY=csig;
                    }else{
                        printf("\nPuerta cerrada, necesitas la llave bro\n");
                    }
                    getch();
                }else if (celda_destino == 'K') {
                    tieneLlave=1;
                    mapa_actual[fsig* 60 + csig] = '.';
                    posX=fsig;
                    posY=csig;
                    printf("\n wowowow lograste conseguir la llave magica");
                    getch();
                } 
                else if (celda_destino=='E'){
                    system("cls");
                    printf("Ganaste!!!\n");
                    printf("Conseguiste: %d de %d\n", monedasJugador, totalMonedas);
                    printf("Niveles completados: %d", nivel);

                    switch (nivel){
                        case 1: //si esta en el nivel 1 avanza a mapa 2
                        printf("Presione cualquier tecla para avanzar al nivel 2...\n");
                        getch();
                        mapa_actual=mapa_nivel2;
                        break;

                        case 2:
                        printf("Presione cualquier tecla para avanzar al nivel 3...\n");
                        getch();
                        mapa_actual=mapa_nivel3; //si nivel 2 a mapa 3
                        break;

                        default:
                        printf("Presione cualquier tecla para salir\n");
                        getch();
                        break;
                    }
                    nivel++; //incrementar nivel
                    posX=1;  //resetear otras variables
                    posY=1;
                    tieneLlave=0;
                    totalMonedas =cnt_monedas(mapa_actual,3600, 'M');
                    totalEspacios=cnt_espacios(mapa_actual, 3600, '.');
                    pasos=0;
                }else{
                    posX=fsig;
                    posY=csig;
                    if (mapa_actual [posX*60+posY]== 'M'){
                        mapa_actual[posX*60+posY]='.';
                    }
                    
                }
            }
        }
    }
    return 0;
}