#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){


    int n = 0;

    pid_t pid = fork();

    if (pid == 0) {
        printf("proceso %d\n", getpid());
        for(int i = n; i<10; i++){
            printf("proceso %d, padre, i = %d\n", getpid(), i);
            sleep(1);
        }
    }else {
        printf("proceso %d\n", getpid());
        for(int i = n; i<10; i++){
            printf("proceso %d, hijo, i = %d\n", getpid(), i);
            sleep(1);
        }
    }



    printf("proceso con pid: %d, final\n", getpid());

    return 0;
}
