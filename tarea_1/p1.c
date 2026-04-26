#include <stdio.h>
#include <math.h>
#include <time.h>

double sqrt_iter(double a, double tol);
double sqrt_newton(double a, double tol);

int main(void)
{
    printf("Pregunta 1 tarea 2026-1 ELO320\n");


    float x = 0.5;

    float y_1 = sqrt(x);
    float y_2 = sqrt_iter(x, 1e-6);
    float y_3 = sqrt_newton(x, 1e-6);

    printf("Verificamos que las funciones calculan correctamente la raiz cuadrada de ");
    printf("un valor conocido\n");
    printf("Usando sqrt: sqrt(%f) = %f\n", x, y_1);
    printf("Usando sqrt_iter: sqrt(%f) = %f\n", x, y_2);
    printf("Usando sqrt_newton: sqrt(%f) = %f\n", x, y_3);

    // Microbenchmarking para tol = 1e-3, 1e-6, y 1e-9
    // Primero medimos sqrt, que no depende de tol
    const int repeticiones = 10;
    const long int iner_rep = 10000000;
    double elapsed;
    double times[repeticiones];
    volatile double res;
    double time_sqrt;
    for(int i = 0;i < repeticiones; i++) {
        clock_t start = clock(); // inicio timer
        for(int j = 0; j < iner_rep; j++)
            res = sqrt(x);
        clock_t end = clock();
        elapsed = ((double)(end - start) / CLOCKS_PER_SEC) / iner_rep;
        /* printf("Iteracion %d de sqrt: la funcion demoro %.2e segundos\n", i, */
        /*        elapsed); */
        times[i] = elapsed;
    }
    float mean = 0;
    for(int i=0; i < repeticiones; i++)
        mean += times[i];
    mean /= repeticiones;
    time_sqrt = mean;
    printf("Tiempo promedio de sqrt: %.4e\n", mean);

    const double tols[] = {1e-3, 1e-6, 1e-9};
    double times_sqrt_iter[3];
    double times_sqrt_newton[3];
    for(int j_tols = 0; j_tols<3; j_tols++) {
        // Midiendo sqrt_iter
        for(int i = 0;i < repeticiones; i++) {
            clock_t start = clock(); // inicio timer
            for(int j = 0; j < iner_rep; j++)
                res = sqrt_iter(x, tols[j_tols]);
            clock_t end = clock();
            elapsed = ((double)(end - start) / CLOCKS_PER_SEC) / iner_rep;
            times[i] = elapsed;
        }
        mean = 0;
        for(int i=0; i < repeticiones; i++)
            mean += times[i];
        mean /= repeticiones;
        times_sqrt_iter[j_tols] = mean;
        printf("Tiempo promedio de sqrt_iter con tol=%.1e: %.4e\n",
               tols[j_tols], mean);

        // Midiendo sqrt_newton
        for(int i = 0;i < repeticiones; i++) {
            clock_t start = clock(); // inicio timer
            for(int j = 0; j < iner_rep; j++)
                res = sqrt_newton(x, tols[j_tols]);
            clock_t end = clock();
            elapsed = ((double)(end - start) / CLOCKS_PER_SEC) / iner_rep;
            times[i] = elapsed;
        }
        mean = 0;
        for(int i=0; i < repeticiones; i++)
            mean += times[i];
        mean /= repeticiones;
        times_sqrt_newton[j_tols] = mean;

        printf("Tiempo promedio de sqrt_newton con tol=%.1e: %.4e\n",
               tols[j_tols], mean);

    }

    // Imprimir resultado final
    printf("\n\nTiempo de sqrt: %.1e\n", time_sqrt);
    for(int j_tols=0; j_tols<3; j_tols++) {
        printf("Tolerancia = %.1e\n", tols[j_tols]);
        printf("\tsqrt_iter time: %.3e\n", times_sqrt_iter[j_tols]);
        printf("\tsqrt_newton time: %.3e\n", times_sqrt_newton[j_tols]);
    }
    
    return 0;    
}

/* Se debe cumplir que 0 < a < 2 */
/* Por simplicidad, para efecto de la tarea no verificamos esta condición */
double sqrt_iter(double a, double tol)
{
    double x_old, x = a;
    double e = 1 - a;
 
    do {
        x_old = x;
        x = (1 + e / 2) * x;
        e = (e * e) * (0.75 + e / 4);
    } while(fabs((x_old - x) / x) > tol);
    return x;
}


/* Se debe cumplir que a >= 0 */
/* Por simplicidad, para efecto de la tarea no verificamos esta condición */
double sqrt_newton(double a, double tol)
{
    double x_old, x = a;
 
    do {
        x_old = x;
        x = 0.5 * (x + a / x);
    } while(fabs((x_old - x) / x) > tol);
    return x;
}
