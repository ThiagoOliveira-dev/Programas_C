#include "lse.h"

int main(){
	TLista *lista = criarLse();
	int num;
	scanf("%d",&num);
	while(num != -1){
		TNovo *novo = criarNovo(num);
		//inserirInicio(lista,novo);
		inserirFim(lista,novo);
		scanf("%d",&num);
	}

	imprimir(lista,imprimiEle);
	//removerFim(lista,destroy);
	//imprimir(lista,imprimiEle);
	scanf("%d",&num);
	removerPos(lista,num,destroy);
	imprimir(lista,imprimiEle);
	int pos;
	scanf("%d",&pos);
	imprimiEle(acessarEle(lista,pos));
	return 0;
}