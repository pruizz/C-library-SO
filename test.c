#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libreria.h" 

#define DEFAULT_LINES 10

int main(int argc, char *argv[]) {
    int n = DEFAULT_LINES;
    char *funct = NULL;

    //Comrpobación de que el numero de argumentos es el correcto en cantidad
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Uso: %s -<nombre_funcion(head,tail,longlines)>) [n]\n", argv[0]);
        return 1;
    }

    //Comprobar que el primer argumento contenga -
    funct = argv[1];
    if (funct[0] != '-'){
        fprintf(stderr, "Uso: %s debe empezar por '-'", funct);
        return 1;
    }

    //Segundo argumento que sea un numero N valido > 0
    if (argc == 3) {
        n = atoi(argv[2]);
        if (n <= 0){
            fprintf(stderr, "Usage: %d must be optional or greater than 0", n);
            return 1;
        }
    }

    //Para ejecutar la funcion se compara el argumento con el nombre de la función
    if (strcmp(funct, "-head") == 0){
        head(n);
    }else if (strcmp(funct, "-tail") == 0){
        tail(n);
    }else if (strcmp(funct, "-longlines") == 0){
        longlines(n);
    }else {
        fprintf(stderr, "Uso: %s  nombre_funcion debe ser '-head', '-tail' o '-longlines'", funct);
        return 1;
    }
    
    return 0;
    
}