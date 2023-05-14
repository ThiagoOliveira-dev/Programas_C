#include "libfila.h"


int main(){
	TFila *fila = criaLista();
	int num;
	double real;
	scanf("%d",&num);
	while(num != -1){
		scanf("%lf",&real);
		TMedida *novo = criaMedida(num,real);
		enfileira(fila,novo);
		scanf("%d",&num);
	}
	imprimir(fila,impEle);
//	--remover posiçao--
/*	int n;
	printf("\n");
	scanf("%d",&n);
	removerPos(lista,n,destroyMedida);
	imprimir(lista,impEle);
*/

	int n;
	printf("--Digite o valor buscado-- \n");
	scanf("%d",&n);
	TMedida *buscado = criaMedida(n,0);
	impEle(acessarPos(fila,buscarMedida(fila,buscado,comparaMedida)));


	return 0;
}