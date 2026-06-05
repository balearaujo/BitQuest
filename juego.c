#include <stdio.h>

void dibujar_celda(char celda) {
    switch(celda) {
        case '#': printf("#"); break;
        case '.': printf("."); break; //Punto pequeño
        default:  printf(" "); break;
        //todavia no tienepara salir el mapa
    }
}