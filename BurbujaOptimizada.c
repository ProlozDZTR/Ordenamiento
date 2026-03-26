/*
  Burbuja Optimizada
  Versión: 1.3 (MARZO, 2025)

  Autor(es): Pamela Herrera Pérez, Nayeli Velazques Tavera, Edgardo Adrian Franco Martínez.
  
  Descripción general: Este programa implementa el algoritmo Bubble Sort con una versión mejorada para ordenar de manera ascendente una lista de números 
  ingresados leídos desde un archivo, lo hace mediante la comparación de un par de elementos, los compara y posteriormente de ser necesario los intercambia.

  Recibe:
   1. El tamaño del arreglo (n) como primer argumento de línea de comandos.
   2. El nombre de un archivo de texto como segundo argumento, desde el cual se leerán n números.

  Devuelve:
   Imprime en pantalla la lista de números ordenada en orden ascendente.
   Muestra el tiempo de ejecución (en segundos) que tardó en realizar el ordenamiento.

  Compilación:
   - Windows: gcc BurbujaOptimizada.c -o BurbujaOptimizada.exe
   - Linux:   gcc BurbujaOptimizada.c -o BurbujaOptimizada
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define SI 1 
#define NO 0

void Burbuja_Optimizada(int A[], int n)
{
	int cambios = SI; // es el caso base que permite saber si se realizaron intercambios 
	int i = 0;
	while (i<= n-2 && cambios != NO)
	{
		cambios = NO;
		int j;
		for (j=0; j<= (n-2)-i; j++)
		{
			if (A[j]>A[j+1]) //si el elemento actual es más grande que el siguiente se intercambian
			{
				int aux = A[j];
				A[j] = A[j+1];
				A[j+1] = aux;
				cambios = SI;
			}
		}
		i = i + 1;
	}
return;	
}

int main (int argc, char * argv[])
{
	if (argc != 3) // validar argumentos
	{
        printf("Ingresa: %s <tamaño_arreglo> <archivo_entrada>\n", argv[0]);
        return 1;
    }
    
    // Capturar datos
    int n = atoi(argv[1]); 
    char *nombreArchivo = argv[2];
    
    // Crear memoria dinámica
    int *A = (int *)malloc(n * sizeof(int));
    if (A == NULL) {
        printf("Error: no se pudo asignar memoria.\n");
        return 1;
    }
    
    // Abrir archivo
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo %s\n", nombreArchivo);
        free(A);
        return 1;
    }

    // Leer datos del archivo
    int i = 0;
    while (i < n && fscanf(archivo, "%d", &A[i]) == 1) {
        i++;
    }
    fclose(archivo);
	
    if (i < n) // en caso que haya menos datos de los esperados
	{
        printf("Advertencia: el archivo solo contenÃ­a %d elementos. Usando ese valor.\n", i);
        n = i;
	}
	
    // --------- Inicia mediciÃ³n del tiempo ---------
    clock_t t_inicio, t_fin;
    double tiempo_total;

    t_inicio = clock();
    Burbuja_Optimizada(A, n);
    t_fin = clock();
    
    tiempo_total = (double)(t_fin - t_inicio) / CLOCKS_PER_SEC;
    // --------- Fin mediciÃ³n del tiempo ---------
	
    printf("Arreglo ordenado:\n");
    int j;
    for (j = 0; j < n; j++) 
	{
        printf("%d\n ", A[j]);
    }
    printf("\n");

    // Mostrar el tiempo de ejecuciÃ³n
    printf("Tiempo de ejecuciÃ³n: %.6f segundos\n", tiempo_total);

    free(A); // Liberar memoria antes de salir

    return 0;
}
