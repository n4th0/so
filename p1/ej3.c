#include <stdio.h>
#include <signal.h>
#include <unistd.h>


void alarma(){
    printf("hola mundo desde una alarma\n");
}

int main(){

    while (1) {
        
    
    signal(SIGINT, alarma);
    // alarm(5);
    printf("pid: %d", getpid());
    pause(); // hold on

    printf("sigue\n");

    }

}
