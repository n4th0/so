
/**
 * intento del ejercicio 1 de la practica 1 "malla.c"
 *
 * @author nathan rodriguez 
 *
 */

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char ** argv){

    if (argc != 3) 
        exit(-1);
    
    int col = atoi(argv[1])-1;
    int fil = atoi(argv[2])-1;

    int id = fork();

    for (int i =0; i<col; i++) {
        if (id != 0) {
            id = fork();
        }
    }

    for (int i =0; i<col; i++) {
        if (id == 0) {
            id = fork();
        }
    }
    
    sleep(10);
}
