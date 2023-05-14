#include "ponto.h"


TPonto *cria(float x, float y, float z){
	TPonto *novoPonto = malloc(sizeof(TPonto));
	novoPonto->x = x;
	novoPonto->y = y;
	novoPonto->z = z;

	return novoPonto;
}

void acessa(TPonto *p, float *x, float *y, float *z){
	*x = p->x;
	*y = p->y;
	*z = p->z;
}

void atribui(TPonto *p, float x, float y, float z){
	p->x = x;
	p->y = y;
	p->z = z;

}

float distancia(TPonto *p1, TPonto *p2){
	
	float a = p2->x - p1->x;
	float b = p2->y - p1->y;
	float c = p2->z - p1->z;

	return sqrt(a*a+b*b+c*c);

}

void imprimir(float p1, float p2, float p3){
	printf("x: %.2f\n",p1 );
	printf("y: %.2f\n",p2 );
	printf("z: %.2f\n",p3 );
}