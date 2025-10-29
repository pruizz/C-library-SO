#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libreria.h" 

#define DefaultLines 10

int main(int argc, char *argv[]) {
    int n = DefaultLines;
    char *funct = NULL;

    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s <function_name> [n]\n", argv[0]);
        return 1;
    }

    //first arg: name function
    funct = argv[1];
    if (funct[0] != '-'){
        fprintf(stderr, "Usage: %s must start with '-'", funct);
        return 1;
    }

    //second arg (if exists): n lines
    if (argc == 3) {
        n = atoi(argv[2]);
        if (n <= 0){
            fprintf(stderr, "Usage: %d must be optional or greater than 0", n);
            return 1;
        }
    }

    //to execute the function
    if (strcmp(funct, "-head") == 0){
        head(n);
    }else if (strcmp(funct, "-tail") == 0){
        tail(n);
    }else if (strcmp(funct, "-longlines") == 0){
        longlines(n);
    }else {
        fprintf(stderr, "Usage: %s must be '-head', '-tail' or '-longlines'", funct);
        return 1;
    }
    
    return 0;
    
}