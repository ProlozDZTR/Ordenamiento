/*
  Shell
  Descripción general: Este programa implementa el algoritmo Shell para ordenar de manera ascendente una lista de números ingresados 
  (leídos desde un archivo). Es como una versión “con saltos” de Insertion Sort, solo que en lugar comparar elementos que están uno al lado 
  del otro, primero compara e intercambia elementos que están a cierta distancia entre sí. Luego se va reduciendo esa distancia hasta 
  llegar a comparar solo elementos contiguos, pero para ese momento la lista ya está casi ordenada.
  Recibe:
   1. El tamaño del arreglo (n) como primer argumento de línea de comandos.
   2. El nombre de un archivo de texto como segundo argumento, desde el cual se leerán n números.

  Devuelve:
   Imprime en pantalla la lista de números ordenada en orden ascendente.
   Muestra el tiempo de ejecución (en segundos) que tardó en realizar el ordenamiento.

  Compilación:
   - Windows: gcc Shell.c -o Shell.exe
   - Linux:   gcc Shell.c -o Shell
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>


void Shell (int A[], int n)
{
	int k= trunc(n/2); //toma la parte entera de la division
	while(k>=1)
	{
		int b =1; //es el caso base para asegurar que sí hay intercambios
		while (b!=0) //mientras sigan habiendo intercambios
		{
			b=0;
			int i;
			for (i=k; i<= n-1; i++) //recorre todo el arreglo
			{
				if (A[i-k]>A[i]) //si el elemento k es mayor se intercambian
				{
					int temp= A[i];
					A[i]=A[i-k];
					A[i-k]= temp;
					b=b+1;
				}
			}
		}
		k=trunc(k/2);
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
if (archivo == NULL) {
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
	
	Shell (A, n);
	
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
