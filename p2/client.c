#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


int main(int argc, char ** argv){
    int soc = socket(AF_INET, SOCK_STREAM, 0);
    if (soc == -1) {
            printf( "\x1b[31m" "****************************************\n" "\x1b[0m");
            printf( "\x1b[31m" "**     ERROR AT CREATE THE SOCKET     **\n" "\x1b[0m");
            printf( "\x1b[31m" "****************************************\n" "\x1b[0m");
            exit(-1);
    }else {
            printf( "\x1b[32m" "****************************************\n" "\x1b[0m");
            printf( "\x1b[32m" "**     THE SOCKET HAS BEEN CREATED    **\n" "\x1b[0m");
            printf( "\x1b[32m" "****************************************\n" "\x1b[0m");
    
    }

    struct sockaddr_in servAddr;

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);
    servAddr.sin_port = htons(9999);

    if(0 !=connect(soc,(struct sockaddr *)&servAddr, sizeof(servAddr))){
            printf( "\x1b[31m" "****************************************\n" "\x1b[0m");
            printf( "\x1b[31m" "**         ERROR AT CONNECTION        **\n" "\x1b[0m");
            printf( "\x1b[31m" "****************************************\n" "\x1b[0m");
            exit(-1);

    }else {
            printf( "\x1b[32m" "****************************************\n" "\x1b[0m");
            printf( "\x1b[32m" "**    THE SOCKET HAS BEEN CONNECTED   **\n" "\x1b[0m");
            printf( "\x1b[32m" "****************************************\n" "\x1b[0m");
    }

    char buff[1024];
    while (1) {

        printf("\x1b[37m" "usr@linux:$ " "\x1b[0m"); 
        //printf("usr@linux:$ ");
        //scanf("%s", buff);

        fgets(buff, sizeof(buff), stdin);

        write(soc, buff, 1024);

        if (strcmp(buff, "exit\n")==0 || strcmp(buff, "exit -s\n")==0 ) {
            //printf("by...\n");
            printf( "\x1b[31m" "quiting...\n" "\x1b[0m");
            close(soc);
            exit(0);
        }else if (strcmp(buff, "history\n")==0) {
            read(soc, buff, sizeof(buff));
            int i = 0;
            while (buff[i]!=0) {
                printf("%c", buff[i]);
                i++;
            }
            bzero(buff, sizeof(buff));
            continue;
        }
        read(soc, buff, sizeof(buff));


        int i = 0;
        while (buff[i]!=EOF && i<1024) {
            printf("%c", buff[i]);
            i++;
        }

        bzero(buff, sizeof(buff));
    }

    close(soc);
}
