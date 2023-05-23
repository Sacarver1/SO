#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

void imprimeDePipe(int leePipe); // Funcionalidad para el hijo
void enviaAPipe(int escribePipe); // Funcionalidad para el padre
void handlerAlarma(int sig); // Manejador de señal para la alarma

int main() {
    pid_t procHijo;
    int pipeFileDescriptors[2]; // Descriptores de ambos extremos

    if (pipe(pipeFileDescriptors) == -1) { // Genera pipe
        printf("Error al crear pipe\n");
        exit(1);
    }

    procHijo = fork(); // Genera proceso hijo

    if (procHijo < 0) {
        int errnum = errno; // Preservamos código de error
        printf("Error %d al generar proceso hijo con fork\n", errnum);
        exit(1);
    }

    if (procHijo == 0) {
        // Es el hijo, cierra pipe de envío y procede
        close(pipeFileDescriptors[1]);
        imprimeDePipe(pipeFileDescriptors[0]);
    }

    if (procHijo > 0) {
        // Es el padre, cierra pide de recepción y procede
        close(pipeFileDescriptors[0]);
        enviaAPipe(pipeFileDescriptors[1]);
    }

    return 0;
}

void imprimeDePipe(int leePipe) {
    char buf; // Carácter de buffer
    printf("Proceso hijo, esperando cadena...\n");
    signal(SIGALRM, handlerAlarma); // Configura el manejador de señal para la alarma
    alarm(10); // Establece una alarma de 10 segundos
    while (read(leePipe, &buf, 1) > 0) {
        write(STDOUT_FILENO, &buf, 1);
    }
    write(STDOUT_FILENO, "\n", 1); // Fin de línea
    close(leePipe);
    printf("Proceso hijo, finalizando\n");
    exit(0);
}

void enviaAPipe(int escribePipe) {
    char buf[6]; // Buffer de hasta 5 caracteres
    printf("Proceso padre, ingresa una cadena de 5 caracteres y enter:\n");
    signal(SIGALRM, handlerAlarma); // Configura el manejador de señal para la alarma
    alarm(10); // Establece una alarma de 10 segundos
    scanf("%5s", buf);
    printf("\n\n"); // Separa la entrada de las futuras salidas
    write(escribePipe, &buf, strlen(buf));
    close(escribePipe); // Presenta EOF al proceso hijo
    wait(NULL); // Espera terminación de hijo
    printf("Hijo terminado, terminando proceso padre\n");
    exit(0);
}

void handlerAlarma(int sig) {
    printf("Tiempo de espera agotado. Programa cancelado.\n");
    exit(0);
}
