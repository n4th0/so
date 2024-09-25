
/**
 *
 * @author nathan rodriguez 
 *
 */

#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include <stdio.h>
#include <stdlib.h>

void alarma(){
}

int main(int argc, char ** argv){
    pid_t ejec, A, B, X, Y, Z;

    if (argc != 2) 
        exit(-1);

    int alar = atoi(argv[1]);
    
    
    printf("Soy el proceso eject y tengo el pid: %d\n", getpid());
    ejec = getpid(); 
    
    int a = fork();


    if (a == 0) {
        printf("Soy el proceso A y tengo el pid: %d. Mi padre es %d\n", getpid(), ejec);
        A = getpid();
        a = fork();

        if (a == 0) {
            printf("Soy el proceso B y tengo el pid: %d. Mi padre es %d. Mi abuelo es %d\n", getpid(), A, ejec);
            B = getpid();
            a = fork();

            if (a == 0) {
                printf("Soy el proceso X y tengo el pid: %d. Mi padre es %d. Mi abuelo es %d. Mi bisabuelo es %d\n", getpid(), B,A, ejec);
                X = getpid();
                alarm(alar);
                signal(SIGALRM, alarma);
                pause();

            }else {
                a =fork();
                if (a == 0) {
                    printf("Soy el proceso Y y tengo el pid: %d. Mi padre es %d. Mi abuelo es %d. Mi bisabuelo es %d\n", getpid(), B,A, ejec);
                    Y = getpid();
                    alarm(alar);
                    signal(SIGALRM, alarma);
                    pause();

                }else {
                    a= fork();
                    if (a == 0) {
                        printf("Soy el proceso Z y tengo el pid: %d. Mi padre es %d. Mi abuelo es %d. Mi bisabuelo es %d\n", getpid(), B,A, ejec);
                        Z = getpid();
                        alarm(alar);
                        signal(SIGALRM, alarma);
                        pause();
                    }
                }
            }
        }
    }

    if (A == getpid()) {
        wait(NULL);
        printf("Soy A (%d) y muero. \n", getpid());
    }else if (B == getpid()) {
        wait(NULL);
        printf("Soy B (%d) y muero. \n", getpid());
    }else if (Z == getpid()) {
        printf("Soy Z (%d) y muero. \n", getpid());
    }else if (Y == getpid()) {
        printf("Soy Y (%d) y muero. \n", getpid());
    }else if (X == getpid()) {
        printf("Soy X (%d) y muero. \n", getpid());
    }else if (ejec == getpid()) {
        wait(NULL);
        printf("Soy ejec (%d) y muero. \n", getpid());
    }

    // if (A == getpid()) {
    //     waitpid(B, NULL, WCONTINUED);
    //     printf("Soy A (%d) y muero. \n", getpid());
    // }else if (B == getpid()) {
    //     waitpid(X, NULL, WCONTINUED);
    //     printf("Soy B (%d) y muero. \n", getpid());
    // }else if (X == getpid()) {
    //     waitpid(Y, NULL, WCONTINUED);
    //     printf("Soy X (%d) y muero. \n", getpid());
    // }else if (Y == getpid()) {
    //     waitpid(Z, NULL, WCONTINUED);
    //     printf("Soy Y (%d) y muero. \n", getpid());
    // }else if (Z == getpid()) {
    //     printf("Soy Z (%d) y muero. \n", getpid());
    // }else if (ejec == getpid()) {
    //     waitpid(A, NULL, WCONTINUED);
    //     printf("Soy ejec (%d) y muero. \n", getpid());
    // }





}
