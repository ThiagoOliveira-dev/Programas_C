#include <stdlib.h>
#include <stdio.h>

typedef struct Novo TNovo;
struct Novo
{
	int num;
	TNovo *prox;
};


typedef struct Lista TLista;
struct Lista
{
	int qtd;
	TNovo *inicio;
	TNovo *fim;
	
};
TLista *criarLse(){
	TLista *lista = malloc(sizeof(TLista));
	lista->inicio = NULL;
	lista->fim = NULL;
	lista->qtd = 0;

	return lista;
}

TNovo *criarNovo(int n){
	TNovo *novo = malloc(sizeof(TNovo));
	novo->num = n;
	novo->prox = NULL;

	return novo;
}

void inserirInicio(TLista *lista,TNovo *novo){
	if(lista->inicio == NULL){
		lista->inicio = novo;
		lista->fim = novo;
	}else{
		novo->prox = lista->inicio;
		lista->inicio = novo;
	}
	lista->qtd++;
}

void inserirFim(TLista *lista,TNovo *novo){
	if(lista->inicio == NULL){
		lista->inicio = novo;
		lista->fim = novo;
	}else{
		TNovo *ultimo = lista->fim;
		ultimo->prox = novo;
		lista->fim = novo;
	}
	lista->qtd++;
}
  
void removerInicio(TLista *lista){
	TNovo *aux = lista->inicio;
	if(lista->inicio != NULL){
		//unico elemento na lista
		if(lista->inicio == lista->fim){
			lista->inicio = NULL;
			lista->fim = NULL;
		}else{ 
			//lista com mais de um elemento
			lista->inicio = aux->prox;
		}
		free(aux);
		lista->qtd--;
	}else{
		printf("Lista vazia!\n");
	}
	printf("Primeiro Elemento Removido!\n");

}

void removerfim(TLista *lista){
	TNovo *aux = lista->inicio;
	if(lista->inicio == NULL){
		printf("Lista vazia!\n");
	}else if(lista->inicio == lista->fim){//unico elemento na lista
		lista->inicio = NULL;
		lista->fim = NULL;
	}else{ 
		//lista com mais de um elemento
		while(aux->prox != lista->fim){
			aux = aux->prox;
		}
		free(lista->fim);
		lista->fim = aux;
		aux->prox = NULL;
	}
	lista->qtd--;
	printf("Ultimo Elemento Removido!\n");
}

void removerPos(TLista *lista,int pos){
	TNovo *aux = lista->inicio;
	TNovo *ant;
	int cont = 1;
	if(pos == 0){
		removerInicio(lista);
	}else if(pos == lista->qtd -1){
		removerfim(lista);
	}else{
		while(cont != pos){
			cont++;
			ant = aux;
			aux = aux->prox;
		}
		ant->prox = aux->prox;
		free(aux);
		printf("Elemento da posicao %d removido\n", pos);
	}	
}


void imprimir(TLista *lista){
	TNovo *aux = lista->inicio;
	while(aux != NULL){
		printf("%d\n",aux->num);
		aux = aux->prox;
	}
}


