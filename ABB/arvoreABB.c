#include <stdio.h>
#include <stdlib.h>

typedef struct No TNo;
struct No{
	int chave;
	int valor;
	TNo *esq;
	TNo *dir;
};
	
TNo *criarRaiz(){
	TNo *raiz = malloc(sizeof(TNo));
	raiz = NULL;

	return raiz;
}


TNo *criaNovoNo(int chave){
	TNo *novo = malloc(sizeof(TNo));

	novo->chave = chave;
	novo->valor = 0;
	novo->esq = NULL;
	novo->dir = NULL;

	return novo;
}

TNo *inserir(TNo *raiz, TNo *novo){

	if(raiz == NULL){
		return novo;
	}
	if(novo->chave < raiz->chave){
		raiz->esq = inserir(raiz->esq, novo);
	}else{
		raiz->dir = inserir(raiz->dir, novo);
	}
	return raiz;

}

TNo *removerRaiz(TNo *raiz){
	TNo *ant;
	TNo *atual;

	if(raiz->esq == NULL){
		atual = raiz->dir;
		free(raiz);
		return atual;
	}

	ant = raiz;
	atual = raiz->esq;
	while(atual->dir != NULL){
		ant = atual;
		atual = atual->dir;

	}

	if(ant != raiz){
		ant->dir = atual->esq;
		atual->esq = raiz->esq;

	}
	atual->dir = raiz->dir;
	free(raiz);
	return atual;
}

TNo *removerNo(TNo *raiz, int chave){
	TNo *atual = raiz;
	TNo *ant = NULL;
	while(atual != NULL){
		if(atual->chave == chave){
			if(atual == raiz){
				raiz = removerRaiz(atual);
			}else{
				if(ant->dir == atual){
					ant->dir = removerRaiz(atual);
				}else{
					ant->esq = removerRaiz(atual);
				}
			}
		}
		ant = atual;
		if( chave < atual->chave){
			atual = atual->esq;
		}else{
			atual = atual->dir;
		}
	}
	return raiz;

}

void imprimir(TNo *raiz){
	if(raiz != NULL){
		
		imprimir(raiz->esq);
		printf("%d\n", raiz->chave);
		imprimir(raiz->dir);
	

	}

}

int main(int argc, char const *argv[]){
	int chave;
	int valor;
	TNo *arvore = criarRaiz();
	scanf("%d",&chave);
	while(chave != 0){
		TNo *novo = criaNovoNo(chave);
		arvore = inserir(arvore, novo);
		scanf("%d",&chave);

	}
	imprimir(arvore);
	scanf("%d",&chave);
	arvore = removerNo(arvore, chave);
	printf("\n");
	imprimir(arvore);
	return 0;
}