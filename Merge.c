/*
  Merge Sort
  Versión: 1.5 (MARZO, 2025)

  Autor(es): Pamela Herrera Pérez, Nayeli Velazques Tavera, Edgardo Adrian Franco Martínez.
  
  Descripción general: Este programa implementa el algoritmo Merge Sort para ordenar de manera ascendente una lista de números ingresados 
  (leídos desde un archivo). Divide el arreglo en mitades, ordena cada mitad de forma recursiva y después combina los resultados en un solo arreglo ordenado.

  Recibe:
   1. El tamaño del arreglo (n) como primer argumento de línea de comandos.
   2. El nombre de un archivo de texto como segundo argumento, desde el cual se leerán n números.

  Devuelve:
   Imprime en pantalla la lista de números ordenada en orden ascendente.
   Muestra el tiempo de ejecución (en segundos) que tardó en realizar el ordenamiento.

  Compilación:
   - Windows: gcc Merge.c -o Merge.exe
   - Linux:   gcc Merge.c -o Merge
*/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>

void Merge(int A[], int p, int q, int r)
{
	int l = r - p + 1;// tamaño del subarreglo
	int C[l];//arreglo temporal
    int i = p; //indíce para la primer mitad 
	int j = q + 1;// indíce para la segunda mitad
	int  k; //indice para C[]
    
	for (k=0; k < l; k++)
	{
		if (i<=q && j<=r)
		{
			if (A[i]<A[j]) //elige el menor elemento
			{
				C[k]= A[i];
				i++;
			}
			else
			{
				C[k]=A[j];
				j++;
			}
		}
		else if (i<=q) //copia la segunda mitad en la primera
		{
			C[k]=A[i];
			i++;
		}
		else 
		{
			C[k]=A[j];
			j++;
		}
	}
	// Se copian los elementos de arreglo temporal (C) al original (A).
	k=p;
	for (i=0; i<l; i++)
	{
		A[k]=C[i];
		k++;
	}
}

void MergeSort(int A[], int p, int r)
{
	if (p<r)
	{
		int q=(p+r)/2; //calcula el punto medio
		MergeSort(A,p,q); //ordena la primer mitad
		MergeSort(A, q+1, r);//ordena la segunda mitad
		Merge(A, p, q, r); //combina las dos mitades ya ordenadas
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
	
	MergeSort (A, 0, n-1);
	
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
