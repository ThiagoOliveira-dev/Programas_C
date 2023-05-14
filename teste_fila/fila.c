#include "libfila.h"

typedef struct Medida TMedida;
struct Medida
{
	int num;
	double real;
	
	
};

typedef struct elem Tele;
struct elem
{
	void *cargautil;
	Tele *prox;
};

typedef struct Lista TLista;
struct Lista
{
	int qtd;
	Tele *inicio;
	Tele *fim;
};

typedef struct Fila TFila;
struct Fila
{
	int tamnaho;
	TLista *lse;
};



Tele *criaElem(void *ele){
	Tele *novo = malloc(sizeof(Tele));
	novo->cargautil = ele;
	novo->prox = NULL;

	return novo;
}

TLista *criaLista(){
	TLista *lista = malloc(sizeof(TLista));
	lista->inicio = NULL;
	lista->fim = NULL;
	lista->qtd = 0;

	return lista;
}


TMedida *criaMedida(int num,double real){
	TMedida *novo = malloc(sizeof(TMedida));
	novo->num = num;
	novo->real = real;

	return novo;
}
void inserirInicio(TLista *lista,void *novo){
	Tele *ele = criaElem(novo);
	if(lista->inicio == NULL){
		lista->inicio = ele;
		lista->fim = ele;
	}else{
		ele->prox = lista->inicio;
		lista->inicio = ele;
	}
	lista->qtd++;
}

void inserirFim(TLista *lista,void *novo){
	Tele *ele = criaElem(novo);
	if(lista->inicio == NULL){
		lista->inicio = ele;
		lista->fim = ele;
	}else{
		Tele *fim = lista->fim;
		fim->prox = ele;
		lista->fim = ele;
	}
	lista->qtd++;
}

void destroyMedida(void *medida){
	free(medida);
}

typedef void (*TDestroy)(void *);
void removerInicio(TLista *lista,TDestroy destroy){
	Tele *aux = lista->inicio;
	if(lista->inicio != NULL){
		if(lista->inicio == lista->fim){
			lista->inicio = NULL;
			lista->fim = NULL;
		}else{
			lista->inicio = aux->prox;
		}
		destroy(aux->cargautil);
		free(aux);
		lista->qtd--;
	}else{
		printf("Lista vazia!\n");
	}
}
void removerFim(TLista *lista,TDestroy destroy){
	Tele *aux = lista->inicio;
	if(lista->inicio != NULL){
		if(lista->inicio == lista->fim){
			lista->inicio = NULL;
			lista->fim = NULL;
			destroy(aux->cargautil);
			free(aux);
		}else{
			Tele *fim = lista->fim;
			while(aux->prox != fim){
				aux = aux->prox;
			}
			destroy(fim->cargautil);
			free(fim);
			aux->prox = NULL;
			fim = aux;
		}
		
		lista->qtd--;
	}else{
		printf("Lista vazia!\n");
	}
}

void removerPos(TLista *lista,int pos,TDestroy destroy){
	if((pos > 0) && (pos <= lista->qtd)){
		if(lista->inicio != NULL){
			if(pos == lista->qtd){
				removerFim(lista,destroy);
			}else if(pos == 1){
				removerInicio(lista,destroy);
			}else{
				int cont = 1;
				Tele *aux = lista->inicio;
				Tele *ant;
				while(cont != pos){
					ant = aux;
					aux = aux->prox;
					cont++;
				}
				ant->prox = aux->prox;
				destroy(aux->cargautil);
				free(aux);
			}
			lista->qtd--;
		}else
			printf("Lista Vazia!\n");
	}else
		printf("Posiçao invalida!\n");

}

void *acessarPos(TLista *lista,int pos){
	if((pos > 0) && (pos <= lista->qtd)){
		if(lista->inicio != NULL){
			int cont = 1;
			Tele *aux = lista->inicio;
			while(cont != pos){
				aux = aux->prox;
				cont++;
			}
			return aux->cargautil;
		}else
			printf("Lista Vazia!\n");
	}else
		printf("Posiçao invalida!\n");
}

int comparaMedida(void *buscado,void *medida){
	TMedida *b = buscado;
	TMedida *m = medida;

	if(b->num == m->num){
		return 0;
	}else
		return 1;
}

typedef int (*TProcura)(void *,void *);
int buscarMedida(TLista *lista,void *buscado,TProcura buscar){
	int pos = 1;
	Tele *aux = lista->inicio;
	while(buscar(buscado,aux->cargautil) != 0){
		aux = aux->prox;
		pos++;
	}
	return pos;
}

void impEle(void *ele){
	TMedida *m = ele;
	if(m != NULL){
		printf("%d %.1lf\n",m->num,m->real);
	}else{
		printf("Medida invalida!\n");
	}
}
typedef void (Timprimir)(void *);
void imprimir(TLista *lista,Timprimir imp){
	Tele *aux = lista->inicio;
	while(aux != NULL){
		imp(aux->cargautil);
		aux = aux->prox;
	}
}


void enfileira(TFila *fila,void *medida){
	inserirFim(fila,medida);
}