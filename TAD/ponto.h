#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct ponto TPonto;
struct ponto
{
	float x;
	float y;
	float z;
	
};

TPonto *cria(float x, float y, float z);
void acessa(TPonto *p, float *x, float *y, float *z);
void atribui(TPonto *p, float x, float y, float z);
float distancia(TPonto *p1, TPonto *p2);
void imprimir(float p1, float p2, float p3);