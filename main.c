#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "Bienvenida.h"
#include <windows.h>

void dibujar_celda(char celda);
extern long long validar_mov(char *m, int columnas, int f, int c);
extern long long cnt_monedas(char *m, int t, char moneda);
extern long long detectar_obj(char *m,int ancho, int f, int c, char obj);
extern long long cnt_espacios(char *m, int t, char espacios);
extern long long puntaje ( long long monedas, long long pasos, long long niveles);


char* cargar_mapa_desde_txt(const char* nombre_archivo, int tamano) {
    int i=0; //contador inicia en 0
    char ch; //el char que leemos
    
    FILE* archivo=fopen(nombre_archivo, "r"); //nombre del archivo leer
    if (archivo==NULL) { //si el archivo esta vacio no lo guardes 
        printf("No esta el archivo %s\n", nombre_archivo);
        getch();
        exit(1); 
    }

    char* mapa=(char*)malloc((tamano+1)*sizeof(char)); //guardar espacio en memoria para el mapa
    if (mapa==NULL) {
        printf("Error: No se guardo bien la memoria\n"); //revisa que si haya entrado
        fclose(archivo);
        exit(1);
    }

    while ((ch=fgetc(archivo))!=EOF&& i<tamano) {
        if (ch!='\n' && ch!='\r') { //si es salto de linea que no se guarde
            mapa[i]=ch; //guarda el char que leimos
            i++;
        }
    }
    mapa[i]='\0'; //termina la cadena

    fclose(archivo); //cierra el archivo
    return mapa;
}

void mostrarAdvertencia(){
    system ("cls");
                printf("\033[1;31m~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                printf("          NIVEL DE FUEGO         \n");
                printf("      No toques las paredes!     \n");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\033[0m\n\n");
                printf("Presiona cualquier tecla...      \n");
                getch();
}
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
    int pasos_totales=0;
    int monedas_total_jugador=0;

    pantallaBienvenida();
    printf("Iniciando juego...\n");
    printf("Jugador en: (%d, %d)\n", posX, posY);

    mapa_actual = cargar_mapa_desde_txt("mapa_nivel1.txt", 3600);

    long long totalMonedas=cnt_monedas(mapa_actual, 3600, 'M');
    long long totalEspacios=cnt_espacios(mapa_actual, 3600, '.');

    printf("Monedas a recolectar en el mapa: %lld\n", totalMonedas);
    printf("Total de espacios para moverse: %lld\n", totalEspacios);
    printf("Seleccione cualquier tecla para continuar: \n");
    getchar();

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
        printf("Monedas recolectadas: %lld / %lld\n", monedasJugador, totalMonedas);
        printf("Total de espacios en el nivel: %lld \n", totalEspacios);
        printf("Pasos: %d\n", pasos);

        if (tieneLlave==0){ 
            printf("No tienes la llave\n");
        } else {
            printf("Tienes la llave!\n"); }
        
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

            long long estado_mov=validar_mov(mapa_actual,60, fsig,csig);
            if (estado_mov==2){
                system ("cls");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                printf("              PERDISTE           \n");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                printf("Presiona cualquier tecla para salir...\n");
                getch();
                return 0;
            }
            else if (estado_mov==1){
                pasos++;
                celda_destino=mapa_actual[fsig*60+csig];

                if (detectar_obj(mapa_actual,60,fsig,csig,'D')==1){
                    if (tieneLlave){
                        Beep(440, 60);  
                        Beep(554, 60);  
                        Beep(659, 60); 
                        Beep(880, 150);
                        printf("\nLograste abrir la puerta del mal\n");
                        mapa_actual[fsig * 60 + csig] = '.';
                        posX=fsig;
                        posY=csig;

                    }else{
                        Beep(180, 100); 
                        Beep(150, 100); 
                        Beep(130, 250);
                        printf("\nPuerta cerrada, necesitas la llave bro\n");
                    }
                    getch();
                }else if (detectar_obj(mapa_actual,60,fsig,csig,'K')==1) {
                    tieneLlave=1;
                    mapa_actual[fsig* 60 + csig] = '.';
                    posX=fsig;
                    posY=csig;
                    Beep(523, 60);  
                    Beep(659, 60);  
                    Beep(784, 60);  
                    Beep(1046, 200);
                    printf("\n wowowow lograste conseguir la llave magica\n");
                    getch();
                } 
                else if (detectar_obj(mapa_actual,60,fsig,csig,'E')==1){
                    Beep(600, 80);
                    Beep(400, 80);
                    Beep(800, 200);
                    system("cls");
                    pasos_totales +=pasos;
                    monedas_total_jugador +=monedasJugador;
                    long long puntaje_final=puntaje(monedas_total_jugador,pasos_totales,nivel);

                    printf("\033[1;32m~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    printf("             VICTORIA!           \n");
                    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\033[0m\n");
                    printf("===   Estadisticas del nivel  ===\n\n");
                    printf("Pasos realizados: %d\n", pasos);
                    printf("Monedas recolectadas: %lld de %lld\n", monedasJugador, totalMonedas);
                    printf("Nivel completado: %d\n", nivel);
                    printf("PUNTAJE ACUMULADO: %lld puntos\n",puntaje_final);

                    switch (nivel){
                        case 1: //si esta en el nivel 1 avanza a mapa 2
                        printf("Presione cualquier tecla para avanzar al nivel 2...\n");
                        getch();
                        free(mapa_actual); 
                        mapa_actual = cargar_mapa_desde_txt("mapa_nivel2.txt", 3600); 
                        break;

                        case 2:
                        printf("Presione cualquier tecla para avanzar al nivel 3...\n");
                        getch();
                        free(mapa_actual); // Liberamos la memoria del mapa viejo
                        mapa_actual = cargar_mapa_desde_txt("mapa_nivel3.txt", 3600); // Cargamos 
                        break;

                        case 3:
                        printf("Presione cualquier tecla para avanzar al nivel 4...\n");
                        getch();
                        free(mapa_actual); // Liberamos la memoria del mapa viejo
                        mapa_actual = cargar_mapa_desde_txt("mapa_nivel4.txt", 3600); // Cargamo
                        mostrarAdvertencia();
                        break;

                        default:
                        long long puntuajeFini=puntaje(monedas_total_jugador, pasos_totales, nivel);
                        system("cls");

                        pantallaWin();
                        printf("Monedas totales recolectadas: %lld\n", monedas_total_jugador);
                        printf("Pasos totales: %d\n", pasos_totales);
                        printf("Puntaje final: %lld\n",puntaje_final);
                        printf("Niveles completados: %d\n", nivel);
                        printf(">> PUNTUCACION TOTAL: %lld\n\n", puntuajeFini);
                        printf("\x1b[36;1m¡Gracias por jugar! Presiona una tecla para salir... \x1b[0m\n");
                        getch();
                        free(mapa_actual);
                        return 0;
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
                    if (celda_destino== 'M'){
                        mapa_actual[posX*60+posY]='.';
                        Beep(987, 80);
                        Beep(1318,120);
                    }
                    
                }
            }
        }
    }
    return 0;
}