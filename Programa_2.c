/*
IINTEGRANTES: 
Aguilar Martinez Fernando, 
Gonzalez Ordaz Ariel, 
Gutierrez Tapia Marco Antonio, 
Sandoval Madrigal Michelle
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

bool CrearColumnas(double ***, int);
bool CrearFilas(double **, int);
bool CrearVector(double **, int);
void LlenarVector(double *, int);
void LlenarMatriz(double**, int);
void ImprimirMatriz(double**, int);
double Determinante(double **, int);
int esDominante(double **,int);
void TriangularMatriz(double **, int);

int main(int argc, char const *argv[])
{
	double **md = NULL;
	double *vec = NULL;
	double correccion, determinante;
	int num, aux, cori, corj;
	int i;
	char var;
	int res = 0;

	do
	{
		printf("\nIngrese el tamanio de la matriz: ");
		scanf("%d", &num);

		if(CrearColumnas(&md, num))
		{
			if (CrearFilas(md, num))
			{
				if(CrearVector(&vec, num))
				{


					LlenarMatriz(md, num);
					printf("\nMatriz: ");
					ImprimirMatriz(md, num);
					aux = 2;
					do
		            {
		                printf("\n\nQuiere corregir algun elemento?\n1. Si\n2. No\nRespuesta: ");
		                scanf("%d", &aux);

		                if (aux == 1)
		                {
		                    printf("Ingrese la fila del elemento que desea corregir: ");
		                    scanf("%d", &cori);
		                    printf("Ingrese la columna del elemento que desea corregir: ");
		                    scanf("%d", &corj);
		                    printf("Ingrese el nuevo valor para esa posici?: ");
		                    scanf("%lf", &correccion);

		                    if (cori >= 0 && cori < num && corj >= 0 && corj < num)
		                    {
		                        md[cori][corj] = correccion;
		                        printf("\nMatriz Corregida:\n");
		                        ImprimirMatriz(md, num);
		                    }
		                    else
		                    {
		                        printf("Las coordenadas est? fuera de rango.\n");
		                    }
		                }
		            } while (aux == 1);

		            LlenarVector(vec, num);

		            if(esDominante(md, num) == 1)
		            {
		            	printf("\nLa matriz es dominante diagonalmente");
		            	determinante = Determinante(md, num);
		            	if (determinante == 0)
		            	{
		            		printf("\nEl sistema no tiene solucion");
		            		printf("\nDesea agregar otra matriz?\n1. Si\n2. No\nRespuesta: ");
		            		scanf("%d", &res);
		            	}else
		            	{
		            		printf("\nQuiere hacer la solución de sistemas?");
		            		getchar();
		            	}
		            }else
		            {
		            	printf("\nLa matriz no es dominante diagonalmente");
		            	TriangularMatriz(md, num);
		            	ImprimirMatriz(md, num);
		            	determinante = Determinante(md, num);
		            	printf("\nDeterminante = %lf", determinante);
		            	if (determinante == 0)
		            	{
		            		printf("\nEl sistema no tiene solucion");
		            		printf("\nDesea agregar otra matriz?\n1. Si\n2. No\nRespuesta: ");
		            		scanf("%d", &res);
		            	}else
		            	{
		            		printf("\nQuiere hacer la solución de sistemas?");
		            		getchar();
		            	}
		            }

					for (i = 0; i < num; i++)
		    		{
		        		free(md[i]);
		    		}

		    		free(md);
		    	}else
		    	{
		    		for (i = 0; i < num; i++)
		    		{
		        		free(md[i]);
		    		}

		    		free(md);
		    		exit(1);
		    	}
			}else
			{
				exit(1);
				free(md);
			}
		}else
		{
			exit(1);
		}
	}while(res == 1);

	return 0;
}

bool CrearColumnas(double ***matriz, int num)
{
	*matriz = (double **) malloc(sizeof(double *) * num);
	if(*matriz == NULL)
	{
		printf("\nNo hay memoria suficiente");
		return false;
	}else
	{
		return true;
	}
}

bool CrearFilas(double **md, int num)
{
	int i, j;
	for(i = 0; i < num; ++i)
	{
		*(md + i) = (double *) malloc(sizeof(double) * num);
		if(*(md + i) == NULL)
		{
			printf("\nNo hay memoria suficiente");
			for(j = 0; j < i; ++j)
			{
				free(*( md +j ));
			}
			free(md);
			return false;
		}
	}
	return true;
}

bool CrearVector(double **vec, int num)
{
	*vec = (double *) malloc(sizeof(double) * num);
	if (vec = NULL)
	{
		printf("\nNo hay memoria suficiente");
		return false;
	}else
	{
		return true;
	}
}

void LlenarVector(double *vec, int num)
{
	int i;
	for (i = 0; i < num; i++) {
    	printf("\n\nIngrese el elemento %d del vector: ", i + 1);
    	scanf("%lf", &vec[i]);
    }
}

void LlenarMatriz(double **md, int num)
{
	int i , j;
	for (i = 0; i < num; ++i)
	{
		for (j = 0; j < num; ++j)
		{
			printf("\nIngrese el elemento (%d , %d)", i, j);
			scanf("%lf", *(md + i) + j);
		}
	}
}

void ImprimirMatriz(double **md, int num)
{
	int i, j;
	for (i = 0; i < num; ++i)
	{
		printf("\n");
		for(j = 0; j < num; ++j)
		{
			printf("%lf\t", *(*(md + i) + j));
		}
	}
}


double Determinante(double **md, int num)
{
double **matriz_copia = NULL;
    int i, j, k;
    double determinante = 1.0;

    if (CrearColumnas(&matriz_copia, num) && CrearFilas(matriz_copia, num)) {
        for (i = 0; i < num; i++) {
            for (j = 0; j < num; j++) {
                matriz_copia[i][j] = md[i][j];
            }
        }
    } else {
        return 0.0; // Error al crear la copia de la matriz
    }

    for (i = 0; i < num; i++) {
        for (j = i + 1; j < num; j++) {
            double factor = matriz_copia[j][i] / matriz_copia[i][i];
            for (k = i; k < num; k++) {
                matriz_copia[j][k] -= factor * matriz_copia[i][k];
            }
        }
        determinante *= matriz_copia[i][i];
    }

    for (i = 0; i < num; i++) {
        free(matriz_copia[i]);
    }
    free(matriz_copia);

    return determinante;
}

int esDominante(double **md,int num) 
{
    int dominante = 1;
    int i,j;
	for (i = 0; i < num; i++) {
        double suma = 0.0;
        for (j = 0; j < num; j++) {
            if (i != j) {
                suma += fabs(md[i][j]);
            }
        }
        if (fabs(md[i][i]) <= suma) {
            dominante = 0;
            break;
        }
    }
    return dominante;
}

void TriangularMatriz(double **matriz, int n) 
{
	int i, j, k;
    for (k = 0; k < n; k++) {
        for (i = k + 1; i < n; i++) {
            double factor = matriz[i][k] / matriz[k][k];
            for (j = k; j < n; j++) {
                matriz[i][j] -= factor * matriz[k][j];
            }
        }
    }
}

