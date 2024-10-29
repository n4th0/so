#include <stdio.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void putInHistory(char history[], int *historyPointer, char *buffer){
    
    for(int i = 0; i<1024; i++){
        history[*historyPointer] = buffer[i];
        *historyPointer = *historyPointer+1;
        if (buffer[i] == '\n') {
            break;
        }
    }
    history[*historyPointer] = 0;
}

int main(){
    struct sockaddr_in serverAddr;

    int soc = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(9999);

    int a = bind(soc, (struct sockaddr * )&serverAddr,sizeof(serverAddr));
    if (a != 0) {
        printf("error at binding\n");
        return -1;
    }

    listen(soc, 10);

    struct sockaddr_in clientAddr;
    int clientAddrLen = sizeof(clientAddr);

    char buff[1024];
    char history[4096];
    bzero(history, 4096);
    int *historyPointer= malloc(sizeof(int));

    int client = accept(soc, (struct sockaddr *)&clientAddr,  &clientAddrLen);
    if (client >=0) {

        printf("\x1b[32m"
               "client accepted\n"
               "\x1b[0m");
    }
    FILE *fp;
    while (1) {

        read(client, buff, sizeof(buff));
        printf("%s", buff);

        if (strcmp(buff, "exit\n")==0) {
            printf( "\x1b[31m" "the user has left \n" "\x1b[0m");
            break;
        }else if (strcmp(buff, "history\n")==0) {
            write(client, history, *historyPointer);
            //printf("%d", *historyPointer);
        } else{
            putInHistory(history, historyPointer, buff);

            fp = popen(buff, "r");
            //write(soc, buff, 1024); examplejj
            int n = 0;
            while (buff[n]!=EOF && n!=1024) {
                buff[n] = getc(fp);
                n++;
            }
            // int i = 0;
            // while (buff[i]!=EOF) {
            //     printf("%c", buff[i]);
            //     i++;
            // }
            write(client, buff, sizeof(buff));
        }

        bzero(buff,sizeof(buff));
    }

    //fclose(fp);
    close(soc);
}