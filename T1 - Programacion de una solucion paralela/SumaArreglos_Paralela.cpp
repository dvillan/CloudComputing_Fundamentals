// SumaArreglos_Paralela.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
# ifdef _OPENMP
    #include <omp.h>
# endif

#define N 1000              // Cantidad de elementos dentro del arreglo 
#define chunk 100           // Tamaño de cada parte que sera procesada por un respectivo hilo
#define mostrar 10          // Cantidad de elemento a imprimir en consola

void imprimeArreglo(float *d);      

int main()
{
    std::cout << "Sumando arreglos en paralelo\n";
    float a[N], b[N], c[N];                                  // Definimos el tamaño de los arreglos 
    int i;                                                   // Definimos iterador

    for (i = 0; i < N; i++)
    {
        a[i] = i * 50;                                       // Establecemos los valores de los elementos 
        b[i] = a[i] + 150;                                   // en cada arreglo
    }
    int partes = chunk;

    // Con la siguiente instruccion definimos el ciclo for para que se ejecute en paralelo
    // usando la libreria OpenMP

    # pragma omp parallel for shared(a, b, c, partes) private(i) schedule(static, partes)

    for (i = 0; i < N; i++)                                  // Realizamos la suma de los arreglos 
    {
        c[i] = a[i] + b[i];
    }

    // Mostramos nuestros arreglos 
    std::cout << "Primeros " << mostrar << " elementos de a: " << std::endl;
    imprimeArreglo(a);
    std::cout << "Primeros " << mostrar << " elementos de b: " << std::endl;
    imprimeArreglo(b);
    std::cout << "Primeros " << mostrar << " elementos de la suma de a + b: " << std::endl;
    imprimeArreglo(c);
}

void imprimeArreglo(float *d)
{
    for (int j = 0; j < mostrar; j++)
    {
        std::cout << d[j] << " - ";
    }
    std::cout << std::endl;
}