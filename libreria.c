#include <stdio.h>
#include <stdlib.h>     
#include <string.h>     
#include "libreria.h"   

#define MAX_LINE_BUFFER 1024

int head(int N) {
    char buffer[MAX_LINE_BUFFER]; // Un solo búfer para reutilizar puesto que no es necesario ir almacenando nada -> solo nos quedamos con las N primerad que llegen
    int i = 0;

    if (N <= 0) {
        return 1;
    }
    while (i < N && fgets(buffer, MAX_LINE_BUFFER, stdin) != NULL){
        int len = strlen(buffer);
        if (buffer[len-1] == '\n'){
            buffer[len-1] = '\0';
        } 
        printf("%s", buffer);
        i++;
    }

    return 0;
}


int tail(int N) {
    // Caso 1: EL numero de lineas introducido es <= 0 -> No se imprime nada
    if (N <= 0){
        return 1;
    }
    // Caso 2: Introduce N lineas;
    // Usamos calloc para reservar N "espacios" para punteros de char.
    // calloc(N, tamaño) -> reserva memoria y la inicializa toda a cero (NULL).
    char **lines =  calloc(N,sizeof(char *));
    if (lines == NULL){
        fprintf(stderr, "Error a la hora de reservar memoria");
        exit(1);
    }

    char aux_buffer[MAX_LINE_BUFFER] ;// Creamos un array auxiliar de el maximo tamaño de la cadena para cada linea almacenada
    int num_lines = 0;
    int len = 0;
    int pos; // posicion del array[0-N-1]

    while(fgets(aux_buffer,MAX_LINE_BUFFER,stdin) != NULL){
        //Quitamos los posibles saltos de lineas que con fgets se almacenan en cada linea
        len = strlen(aux_buffer);
        if (len > 0 && aux_buffer[len - 1] == '\n') {
            aux_buffer[len - 1] = '\0';
            len--; // Reducimos la longitud
        }
        
        pos = num_lines % N;
        //Si ya hay un ellemento lo eliminamos 
        if (lines[pos] != NULL){
            free(lines[pos]);
        }
        // Reservamos memoria nueva para la línea actual
        lines[pos] = malloc(len + 1); // +1 para el '\0'

        if (lines[pos] == NULL) {
            fprintf(stderr, "Error: No se pudo reservar memoria para la línea.\n");
            for (int i = 0; i < N; i++) {
            // Solo liberamos si realmente hay una cadena (no es NULL)
                if (lines[i] != NULL) {
                    free(lines[i]);
                }
            }
            // 2. Liberar el array principal reservado con calloc
            free(lines);
            exit(1);
        }

        strcpy(lines[pos],aux_buffer);

        num_lines ++;

    }
    
    // Mostrar solo las n lineas en orden correcto
    int indice_inicio = (num_lines < N) ? 0 : (num_lines % N);
    
    // Decidimos cuántas líneas imprimir en total
    int lineas_a_imprimir = (num_lines < N) ? num_lines : N;

    for (int i = 0; i < lineas_a_imprimir; i++) {
        // Calculamos el índice real dentro del array, dando la vuelta si es necesario
        int indice_real = (indice_inicio + i) % N;
        
        // Imprimimos la línea
        printf("%s\n", lines[indice_real]);
    }
    
    //Limpiar la memoria
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

    if (N <= 0) { //idk if it's necessary because we have a test.c
        return 1;
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
