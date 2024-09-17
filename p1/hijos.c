

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void printVector(int *x, int size){
    printf("vector: ");
    for (int i = 0; i<size; i++) {
        printf(" %d ", x[i]);
    }
    printf("\n");

}

int main(int argc, char ** argv){

    if (argc != 3) {
        exit(9);
    }

    int x = atoi(argv[1]);
    int y = atoi(argv[2]);

    pid_t hijos[x];
    pid_t superPadre = getpid();

    pid_t a = 0;
    
    for (int i = 0; i<x; i++) {
        if (a == 0) {
            a = fork();
        }    
    }

    printf("soy %d\n", getpid());

    if (a == 0) {
        a = 1;
        for (int i = 0; i<y; i++) {
            if (a != 0) {
                a =fork();
            }
        }
    }
    
    printVector(hijos, x);
    sleep(5);



}
