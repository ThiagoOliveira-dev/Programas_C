#include <stdlib.h>
#include <stdio.h>
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

	imprimir(lista);
	scanf("%d",&num);
	removerPos(lista,num);
	imprimir(lista);
	return 0;
}