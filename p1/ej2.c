
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>


int main(){
    int a, b;

    



    switch (fork()) {
        case 0:
            printf("soy hijo %d\n", getpid());
            sleep(4);
            exit(10);
        default:
            wait(&b);

            if ((b & 0x7f) != 0) {
                printf("ha muerto con una señal\n");
            } else {
                printf("ha muerto con un exit(%d)\n", (b>>8) & 0xff);
            }
        
    

    
    }




}
