#include "CALC.h"
#include <stdio.h>
#include <stdlib.h>

void calc_prog_1(char *host, int opcion, double a, double b)
{
    CLIENT *clnt;
    double *result_1;
    dupla_int operandos_1_arg;  
#ifndef DEBUG
    clnt = clnt_create(host, CALC_PROG, CALC_VERS, "udp"); // <- Crea el manejador de cliente RPC, estableciendo la conexión con el servidor definido por 'host'.
// Usa el programa CALC_PROG y la versión CALC_VERS, comunicándose mediante el protocolo UDP.
    if (clnt == NULL) {
        clnt_pcreateerror(host);
        exit(1);
    }
#endif /* DEBUG */

    operandos_1_arg.a = a;
    operandos_1_arg.b = b;

    switch (opcion) {
        case 1:
            result_1 = suma_1(&operandos_1_arg, clnt);
            break;
        case 2:
            result_1 = resta_1(&operandos_1_arg, clnt);
            break;
        case 3:
            result_1 = multiplicacion_1(&operandos_1_arg, clnt);
            break;
        case 4:
            result_1 = division_1(&operandos_1_arg, clnt);
            break;
        default:
            printf("Opcion invalida.\n");
#ifndef DEBUG
            clnt_destroy(clnt);
#endif
            return;
    }

    if (result_1 == (double *)NULL) {
        clnt_perror(clnt, "Llamada RPC fallida");
    } else {
        printf("El resultado es: %.2f\n", *result_1);
    }

#ifndef DEBUG
    clnt_destroy(clnt);   // <- Cierra la conexión
#endif
}

int main(int argc, char *argv[]) // <- Contiene el código del cliente 
{
    if (argc != 5) {
        printf("Uso: %s <host> <opcion> <a> <b>\n", argv[0]);
        printf("Opciones: 1=Suma 2=Resta 3=Multiplicacion 4=Division\n");
        exit(1);
    }

    char *host = argv[1];
    int opcion = atoi(argv[2]);
    double a = atof(argv[3]);
    double b = atof(argv[4]); // <- personalizado para recibir la dirección IP del servidor, la operación y los valores como argumentos.

    calc_prog_1(host, opcion, a, b);

    return 0;
}
