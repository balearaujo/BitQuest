#include <stdio.h>

// codigos ASCII para objetos
#define SYM_PARED 254
#define SYM_MONEDA 184
#define SYM_LLAVE 190
#define SYM_PUERTA 177
#define SYM_SALIDA 175

void dibujar_celda(char celda) {
    switch(celda) {
        case '#': printf("\x1b[38;5;21m%c\x1b[0m", SYM_PARED); break;
        case 'M': printf("\x1b[38;5;11m%c\x1b[0m", SYM_MONEDA); break;
        case 'K': printf("\x1b[38;5;130m%c\x1b[0m", SYM_LLAVE); break;
        case 'D': printf("\x1b[38;5;196m%c\x1b[0m", SYM_PUERTA); break;
        case 'E': printf("\x1b[36m%c\x1b[0m", SYM_SALIDA); break;
        case '.': printf("\x1b[37;1m%c\x1b[0m", 250); break; 
        default:  printf(" "); break;
    }
}

