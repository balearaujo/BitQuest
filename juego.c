#include <stdio.h>
//despues poner demas colores q ahorita n
void dibujar_celda(char celda) {
    switch(celda) {
        case '#': printf("#"); break;
        case '.': printf("."); break; //Punto pequeño
        case 'M': printf("\033[33mM\033[0m"); break; //amarillo
        default:  printf(" "); break;
        //todavia no tienepara salir el mapa
    }
}