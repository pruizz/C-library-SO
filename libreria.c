#include <stdio.h>
#include <stdlib.h>     
#include <string.h>     
#include "libreria.h"   



int head(int N) {
    // TODO: Implementar función
    return 0;
}


int tail(int N) {
    // TODO: Implementar función
    return 0;
}


int longlines(int N) {
    #define max 1024 //ns si tenemos q ponerlo global para toda la libreria
    typedef struct {
        char *text; //the text we are saving
        int length; //to know which are the longest lines
    } Line;
    Line *lines = NULL;
    int cont = 0;
    int capacity = 10;  //for example
    char buffer[max];
    int len;
    int i;
    int j;
    Line *temp;

    if (N <= 0) { //idk if it's necessary because we have a test.c
        return 0;
    }

    lines = malloc(capacity * sizeof(Line)); //pointer to the reserved memory block
    if (lines == NULL) {
        fprintf(stderr, "Memory error\n");
        return 1;
    }
    //read lines from stdin
    while (fgets(buffer, max, stdin) != NULL){
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
