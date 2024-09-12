/**
 *
 * @author n4th0
 * @contact nrm69@alu.ua.es
 *
 * ejercicio 1 de la practica 1 de sistemas operativos
 * genera una malla con las columnas y filas especificadas en 
 * los argumentos del programa
 *
 * compilación:     gcc ejercicio1.c -o ej1
 * ejecución:       ./ej1 3 3
 * visualización:   pstree -p | grep ej1
 *
 */

#include <unistd.h>
#include <stdlib.h>

#define TIEMPO_ESPERA 10


int main(int argc, char ** argv){

    if (argc != 3)  // si no hay argumentos no se puede realizar el programa
                    // como es debido
        exit(-1);
    
    // se obtienen las medidas
    int col = atoi(argv[1])-1; 
    int fil = atoi(argv[2])-1;



    int id = fork();

    // se generan los hijos que va a tener el proceso principal
    for (int i =0; i<col; i++) {
        if (id != 0) {
            id = fork();
        }
    }

    // se generan los hijos de los hijos que harán la malla
    for (int i =0; i<col; i++) {
        if (id == 0) {
            id = fork();
        }
    }
    
    sleep(TIEMPO_ESPERA); 
    // tiempo de espera para que de tiempo ha visualizarlo
}



