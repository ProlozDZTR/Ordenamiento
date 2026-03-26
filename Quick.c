/*
  Quick Sort
  Versión: 1.5 (MARZO, 2025)

  Autor(es): Pamela Herrera Pérez, Nayeli Velazques Tavera, Edgardo Adrian Franco Martínez.
  
  Descripción general: Este programa implementa el algoritmo Merge Sort para ordenar de manera ascendente una lista de números ingresados 
  (leídos desde un archivo), Escoge un pivote, parte el arreglo en dos en torno a él, de modo que los valores menores o iguales queden a un 
  lado y los mayores al otro, y luego ordena cada parte por separado.

  Recibe:
   1. El tamaño del arreglo (n) como primer argumento de línea de comandos.
   2. El nombre de un archivo de texto como segundo argumento, desde el cual se leerán n números.

  Devuelve:
   Imprime en pantalla la lista de números ordenada en orden ascendente.
   Muestra el tiempo de ejecución (en segundos) que tardó en realizar el ordenamiento.

  Compilación:
   - Windows: gcc Quick.c -o Quick.exe
   - Linux:   gcc Quick.c -o Quick
*/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>

void Intercambiar(int A[], int i, int j)
{
	int temp = A[j];
	A[j] = A[i];
	A[i] = temp;
}

int Pivot(int A[], int p, int r)
{
	int piv = A[p]; //el pivote es el primer elemento
	int i = p + 1;
	int j = r;

	while(i <= j)
	{
		while (A[i] <= piv && i <= r) //avanza i si los elementos son menores al pivote
		{
			i++;
		}
		while (A[j] > piv) //j retrocede si los elementos son mayores que el pivote
		{
			j--;
		}
		if (i < j) //si i aun no supera a j, se intercambian los elementos
		{
			Intercambiar (A, i, j);
		}
	}
	Intercambiar (A, p, j); //e intercambia el pivote con el elemento A[j] para colocarlo en su posición definitiva dentro del subarreglo.
	return j;
}

void QuickSort(int A[], int p, int r)
{
	if (p<r)
	{
		int j = Pivot(A, p, r);
		QuickSort (A, p, j-1); //ordena el subarreglo izquierdo
		QuickSort (A, j+1, r); //ordena el subarreglo derecho 
	}
}

int main (int argc, char * argv[])
{
	if (argc != 3) 
	{
        printf("Ingresa: %s <tamaño_arreglo> <archivo_entrada>\n", argv[0]);
        return 1;
    }
    
      //capturar datos
    int n = atoi(argv[1]); //convierte a numeros enteros
    char *nombreArchivo = argv[2];
    
    // Crear arreglo dinámico
    int *A = (int *)malloc(n * sizeof(int));
    if (A == NULL) {
        printf("Error: no se pudo asignar memoria.\n");
        return 1;
    }
    
      // Abrir archivo
    FILE *archivo = fopen(nombreArchivo, "r");
	if (archivo == NULL) 
	{
   	 printf("Error: No se pudo abrir el archivo %s\n", nombreArchivo);
	 free(A);
  	  return 1;
	}
    
     // Leer datos del archivo
    int i = 0;
    while (i<n && fscanf(archivo, "%d", &A[i]) == 1) {
        i++;
    }
    fclose(archivo);
    
    if (i < n) 
	{
        printf("Advertencia: el archivo solo contenía %d elementos. Usando ese valor.\n", i);
        n = i;
	}
	
    // --------- Inicia medición del tiempo ---------
    clock_t t_inicio, t_fin;
    double tiempo_total;

    t_inicio = clock(); // Marca de inicio
	
	QuickSort (A, 0, n-1);
	
	t_fin = clock(); // Marca de fin
    tiempo_total = (double)(t_fin - t_inicio) / CLOCKS_PER_SEC;
    // --------- Fin medición del tiempo ---------
	
	printf("Arreglo ordenado:\n");
	int j;
    for (j = 0; j < n; j++) 
	{
        printf("%d\n ", A[j]);
    }
    printf("\n");
    	// Mostrar el tiempo de ejecución
    printf("Tiempo de ejecución: %.6f segundos\n", tiempo_total);
	free(A);
    return 0;
}
