#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


int main(){
    int soc = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servAddr;

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servAddr.sin_port = htons(9999);

    connect(soc,(struct sockaddr *)&servAddr, sizeof(servAddr));

    char buff[1024];
    while (1) {

        printf("\x1b[37m"
               "usr@linux:$ "
               "\x1b[0m");
        //printf("usr@linux:$ ");
        //scanf("%s", buff);
        fgets(buff, sizeof(buff), stdin);

        write(soc, buff, 1024);

        if (strcmp(buff, "exit\n")==0) {
            //printf("by...\n");
            printf( "\x1b[31m" "by...\n" "\x1b[0m");
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
        // FILE *f;
         read(soc, buff, sizeof(buff));

        // while (fgets(buff, sizeof(buff), f) !=NULL)
        //         printf("%s\n", buff);
        //printf("%s",buff);

        int i = 0;
        while (buff[i]!=EOF) {
            printf("%c", buff[i]);
            i++;
        }

        bzero(buff, sizeof(buff));

    }

    close(soc);
}
