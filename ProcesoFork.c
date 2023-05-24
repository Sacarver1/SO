#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handlerSIGALRM(int sig);

int main() {
    int secRestantes;
    char *entrada;
    entrada = malloc(10 * sizeof(char)); // Asignaci�n de memoria

    pid_t pid = fork(); // Crear un nuevo proceso hijo

    if (pid == -1) {
        fprintf(stderr, "Error al crear el proceso hijo.\n");
        return 1;
    }

    if (pid == 0) {
        // Proceso hijo
        signal(SIGALRM, handlerSIGALRM); // Redefine el manejador de SIGALRM
        printf("Conteo de segundos iniciado.\n");
        secRestantes = alarm(20); // Establece una alarma de 20 segundos

        while (1) {
            sleep(1);
            printf("Segundos restantes: %d\n", secRestantes);
            secRestantes--;
        }
    } else {
        // Proceso padre
        printf("Esperando una cadena de entrada hasta 10 segundos.\n");
        secRestantes = alarm(10); // Espera hasta 10 segundos la entrada

        if (secRestantes > 0) {
            printf("Exist�a una alarma previa con %d segundos restantes.\n", secRestantes);
        }

        scanf("%10s", entrada); // El proceso padre se detendr� aqu�
        printf("Se recibe la entrada de usuario: %s\n", entrada);
    }

    free(entrada);
    return 0;
}

// Rutina de atenci�n de la se�al, notifica la se�al que se recibi�
void handlerSIGALRM(int sig) {
    printf("\nSe recibe la se�al de la alarma #%d\n", sig);
    exit(0);
}

