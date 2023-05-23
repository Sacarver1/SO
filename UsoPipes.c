#include <stdio.h>

#include <errno.h>

#include <unistd.h>

#include <string.h>

#include <stdlib.h>

#include <sys/wait.h>


void imprimeDePipe(int leePipe); 

void enviaAPipe(int escribePipe); 


int main() {

    pid_t procHijo;

    int pipeFileDescriptors[2]; 


    if(pipe(pipeFileDescriptors) == -1) { 

        printf("Error al crear pipe\n");

        exit(1);

    }


    procHijo=fork(); 


    if(procHijo<0) {

        int errnum=errno; 

        printf("Error %d al generar proceso hijo con fork\n",errnum);

        exit(1);

    }

    if(procHijo==0) {

  

        close(pipeFileDescriptors[1]);

        imprimeDePipe(pipeFileDescriptors[0]);

    }

    if(procHijo>0) {

   

        close(pipeFileDescriptors[0]);

        enviaAPipe(pipeFileDescriptors[1]);

    }

    return 0;

}

void imprimeDePipe(int leePipe) {

    char buf; //Carácter de buffer

    printf("Proceso hijo, esperando cadena...\n");

    while (read(leePipe, &buf, 1) > 0)

    write(STDOUT_FILENO, &buf, 1);

    write(STDOUT_FILENO, "\n", 1); //Fin de línea

    close(leePipe);

    printf("Proceso hijo, finalizando\n");

    exit(0);

}

/**

* Funcionalidad para el padre, lee una cadena de hasta 10 caracteres,

* la escribe a su extremo del pipe, cierra su extremo y espera a que

* un proceso hijo termine antes de terminar su propio proceso.

**/

void enviaAPipe(int escribePipe) {

    char buf[10]; //Buffer de hasta 256 caracteres.

    printf("Proceso padre, ingresa una cadena de 10 caracteres y enter:\n");

    scanf("%10c", &buf);

    printf("\n\n"); //Separa la entrada de las futuras salidas.

    write(escribePipe, &buf, strlen(buf));

    close(escribePipe); //Presenta EOF al proceso hijo

    wait(NULL); //Espera terminación de hijo

    printf("Hijo terminado, terminando proceso padre\n");

    exit(0);

}