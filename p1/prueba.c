
/*
 * nathan rodriguez 
 * intento del ejercicio 1 de la practica 1 "malla.c"
 *
 *
 */
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char ** argv){

    if (argc != 3) 
        exit(-1);
    
    int col = atoi(argv[1]);
    int fil = atoi(argv[2]);


    for (int i = 0; i<col; i++) {
        fork();
        wait(NULL);
    }
    


    sleep(4);
}
