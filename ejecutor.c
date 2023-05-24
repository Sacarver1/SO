#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Uso: %s <numero1> <numero2>\n", argv[0]);
        return 1;
    }

    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);

    printf("Programa ejecutor / PID: %d\n", getpid());
    printf("1. Suma\n");
    printf("2. Multiplicación\n");
    printf("Ingrese su selección: ");

    int seleccion;
    scanf("%d", &seleccion);

    char* programa;
    char* arg1 = argv[1];
    char* arg2 = argv[2];

    switch (seleccion) {
        case 1:
            programa = "./suma";
            break;
        case 2:
            programa = "./multiplicacion";
            break;
        default:
            printf("Selección no válida.\n");
            return 1;
    }

    char* const args[] = {programa, arg1, arg2, NULL};

    printf("Presione cualquier tecla para continuar...\n");
    getchar();

    execv(programa, args);

    printf("Hubo un error en la ejecución. Cancelando...\n");

    return -1;
}

