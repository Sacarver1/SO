#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Uso: %s <numero1> <numero2>\n", argv[0]);
        return 1;
    }

    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    int multiplicacion = num1 * num2;

    printf("El resultado de multiplicar %d por %d es: %d\n", num1, num2, multiplicacion);

    return 0;
}

