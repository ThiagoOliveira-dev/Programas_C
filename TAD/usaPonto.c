#include "ponto.h"

int main(int argc, char const *argv[])
{
	TPonto *ponto1;
	TPonto *ponto2;
	float x, y, z;
	float x1, y1, z1;
	float x2,y2,z2;
	float p1,p2,p3;
	scanf("%f %f %f", &x, &y, &z);
	while((x!=0) && (y!=0) && (z!=0)){
		ponto1 = cria(x,y,z);
		acessa(ponto1, &p1, &p2, &p3);
		imprimir(p1,p2,p3);


		scanf("%f %f %f", &x1, &y1, &z1);
		atribui(ponto1, x1, y1, z1);
		acessa(ponto1, &p1, &p2, &p3);
		imprimir(p1,p2,p3);

		scanf("%f %f %f", &x2, &y2, &z2);
		ponto2 = cria(x2,y2,z2);
		acessa(ponto2, &p1, &p2, &p3);
		imprimir(p1,p2,p3);

		printf("%.2f\n", distancia(ponto1,ponto2));

		scanf("%f %f %f", &x, &y, &z);
	}
	return 0;
}