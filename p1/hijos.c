

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void printVector(int *x, int size, int a, int padre){
    printf("Soy el subhijo %d, mis padres son: ", a);
    printf(" %d ", padre);
    for (int i = 0; i<size; i++) {
        printf(" %d ", x[i]);
    }
    printf("\n");
}

int main(int argc, char ** argv){

    if (argc != 3) 
        exit(9);
    

    int x = atoi(argv[1]);
    int y = atoi(argv[2]);

    pid_t superPadre = getpid();

    int *hijos;
    int shmid=shmget(IPC_PRIVATE, sizeof(int)*(x+y), IPC_CREAT|0666);

    hijos = (int *) shmat(shmid, NULL, 0);

    pid_t a = 0;
    
    for (int i = 0; i<x; i++) {
        if (a == 0) {
            a = fork();
            hijos[i] = getpid();
        }    
    }

    if (a == 0) {
        a = 1;
        for (int i = x; i<(x+y); i++) {
            if (a != 0) {
                a =fork();
                hijos[i] = getpid();
            }
        }
    }

    if (getpid() == superPadre) {

        sleep(1);
        printf("Soy el superPadre (%d) mis hijos finales son:", getpid());
        for (int i = 0; i<(x+y); i++) {
            printf(" %d ", hijos[i]);
        }
        printf("\n");
    }
    /// print stuff
    for (int i = 0; i<=x; i++) {
        if (getpid() == hijos[i] && getpid() !=superPadre && getpid()!=hijos[0]) {
            printVector(hijos, i, getpid(), superPadre);
        } 
    }

    for (int i = (x+1); i<(x+y); i++) {
        if (getpid() == hijos[i]) {
            printVector(hijos, x, getpid(), superPadre);
        } 
    }

    if (hijos[0] == getpid()) {
        printf("Soy el subhijo %d, mi padre es: %d\n", getpid(), superPadre);
    }

    shmdt((char *)hijos);
    shmctl(shmid, IPC_RMID, 0);

}
