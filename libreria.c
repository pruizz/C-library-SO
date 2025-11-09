#include <stdio.h>
#include <stdlib.h>     
#include <string.h>     
#include "libreria.h"   

#define MAX_LINE_BUFFER 1024

int head(int N) {
    char buffer[MAX_LINE_BUFFER]; // Un solo búfer para reutilizar puesto que no es necesario ir almacenando nada -> solo nos quedamos con las N primerad que llegen
    int i = 0;

    if (N <= 0) {
        return 0;
    }
    while (i < N && fgets(buffer, MAX_LINE_BUFFER, stdin) != NULL){
        printf("%s", buffer);
        i++;
    }

    return 0;
}


int tail(int N) {
    if (N <= 0){
        return 0;
    }
    
    // Usamos calloc para reservar N "espacios" para punteros de char.
    char **lines =  calloc(N,sizeof(char *));
    if (lines == NULL){
        fprintf(stderr, "Error a la hora de reservar memoria");
        return 1;
    }

    char aux_buffer[MAX_LINE_BUFFER] ;
    int num_lines = 0;
    int len = 0;
    int pos;

    while(fgets(aux_buffer,MAX_LINE_BUFFER,stdin) != NULL){
        //Quitamos los posibles saltos de lineas que con fgets se almacenan en cada linea
        len = strlen(aux_buffer);
        if (len > 0 && aux_buffer[len - 1] == '\n') {
            aux_buffer[len - 1] = '\0';
            len--; 
        }
        pos = num_lines % N;
        // Caso de que ya haya un elemento dentro del array
        if (lines[pos] != NULL){
            free(lines[pos]);
        }
        // Reservamos memoria nueva para la línea actual
        lines[pos] = malloc(len + 1); // +1 para el '\0'

        if (lines[pos] == NULL) { // Si para alguna reserva de memoria por linea se produce un error hay que salir pero antes borra todo lo creado hasta ese momento
            fprintf(stderr, "Error: No se pudo reservar memoria para la línea.\n");
            for (int i = 0; i < N; i++) {
                if (lines[i] != NULL) {
                    free(lines[i]);
                }
            }
            
            free(lines);
            return 1;
        }

        strcpy(lines[pos],aux_buffer);

        num_lines ++;

    }
    
    
    int indice_inicio = (num_lines < N) ? 0 : (num_lines % N);
    int lineas_a_imprimir = (num_lines < N) ? num_lines : N;

    for (int i = 0; i < lineas_a_imprimir; i++) {
        int indice_real = (indice_inicio + i) % N;
    
        printf("%s\n", lines[indice_real]);
    }
    
    //Limpiar la memoria antes de salir
    for (int i = 0; i<N ; i++){
        if (lines[i] != NULL) {
            free(lines[i]);
        }
    }
    free(lines);
    return 0;
}


int longlines(int N) {
    typedef struct {
        char *text; //the text we are saving
        int length; //to know which are the longest lines
    } Line;
    Line *lines = NULL;
    int cont = 0;
    int capacity = 10;  //for example
    char buffer[MAX_LINE_BUFFER];
    int len;
    int i;
    int j;
    Line *temp;

    if (N <= 0) { 
        return 0;
    }

    lines = malloc(capacity * sizeof(Line)); //pointer to the reserved memory block
    if (lines == NULL) {
        fprintf(stderr, "Memory error\n");
        return 1;
    }
    //read lines from stdin
    while (fgets(buffer, MAX_LINE_BUFFER, stdin) != NULL){
        len = strlen(buffer);
        if (buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
            len--;
        }
        if (cont >= capacity){
            capacity = capacity * 2;
            Line *temp = realloc(lines, capacity * sizeof(Line));
            if (temp == NULL) {
                fprintf(stderr, "Memory error\n");
                for (i = 0; i < cont; i++) {
                    free(lines[i].text);
                }
                free(lines);
                return 0;
            }
            lines = temp;
        }
        lines[cont].text = malloc(len + 1);
        strcpy(lines[cont].text, buffer);
        lines[cont].length = len;
        cont++;
    }
    //sort lines from longest to shortest
    /*hemos utilizado el clásico algoritmo burbuja para ordenar por longitud a pesar
     de que buscando en internet vimos que podiamos implementar un quicksort, pero 
     dado nuestra poca experiencia en C creíamos que era demasiado "artificial" utilizar
     ese quicksort */
    for(i = 0; i < cont - 1; i++){
        for(j = i + 1; j < cont; j++){
            if(lines[j].length > lines[i].length){
                Line temp = lines[i];
                lines[i] = lines[j];
                lines[j] = temp;
            }
        }
    }
    //print n lines
    if (N > cont){ //to control if there are less than n lines
        N = cont;
    }
    for (i = 0; i < N; i++){
        printf("%s\n", lines[i].text);
        free(lines[i].text);
    }
    free(lines);
    return 0;
}
