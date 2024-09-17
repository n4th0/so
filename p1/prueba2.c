#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    FILE *archivo, *archivo2;
    if (argc != 3) {
        return 1;
    }
    char n;


    int fd[2];
    pipe(fd);

    switch (fork()) {
        case 0: // child

            archivo = fopen(argv[1], "r");
            while ((n=getc(archivo))!=EOF) {
                write(fd[1], &n, sizeof(char));
                // printf("ejecuto bucle 1");
            };
            n = EOF;
            write(fd[1], &n, sizeof(char));
            close(fd[1]);
            close(fd[0]);
            fclose(archivo);
            exit(10);
            break;

        default: // parent
            archivo2 = fopen(argv[2], "w");

            int i = 0;
            while (EOF!=n) {
                 read(fd[0], &n, sizeof(char));
                 putc(n, archivo2);
                 i++;
            }
            i--;
            // no se si es legal usar estas funciones
            fseek(archivo2, -2, SEEK_CUR);
            ftruncate(fileno(archivo2), i);

            close(fd[0]);
            close(fd[1]);
            fclose(archivo2);
            exit(10);

            break;
    }



    return 0;
}
