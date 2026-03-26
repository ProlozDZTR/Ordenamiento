/*
  Selection
  Versión: 1.6 (MARZO, 2025)

  Autor(es): Pamela Herrera Pérez, Nayeli Velazques Tavera, Edgardo Adrian Franco Martínez.
  
  Descripción general: Este programa implementa el algoritmo Selection Sort para ordenar de manera ascendente una lista de números ingresados 
  (leídos desde un archivo), toma el primer elemento y los compara con el resto hasta encontrar el más pequeño y entonces los intercambia, después 
  toma el segundo elemento y se repite la acción.

  Recibe:
   1. El tamaño del arreglo (n) como primer argumento de línea de comandos.
   2. El nombre de un archivo de texto como segundo argumento, desde el cual se leerán n números.

  Devuelve:
   Imprime en pantalla la lista de números ordenada en orden ascendente.
   Muestra el tiempo de ejecución (en segundos) que tardó en realizar el ordenamiento.

  Compilación:
   - Windows: gcc Selection.c -o Selection.exe
   - Linux:   gcc Selection.c -o Selection
*/

#include<stdio.h>
#include<stdlib.h>
#include <time.h>

void Selection (int A[], int n)
{
	int k;
	for (k=0; k<= n-2; k++) //recorre hasta el penúltimo elemento porque el ultimo queda ordenado
	{
		int p=k;
		int i;
		for (i=k+1; i<= n-1; i++) //busca el elemento mas pequeño
		{
			if (A[i]<A[p])
			{
				p=i;
			}
		}
		//intercambiar el elemento mas pequeño
		int temp= A[p]; 
		A[p]=A[k];
		A[k]= temp;
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
    if (A == NULL) 
	{
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
    while (i < n && fscanf(archivo, "%d", &A[i]) == 1) {
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
	
	Selection (A, n);
	
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
