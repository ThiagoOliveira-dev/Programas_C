#include "lse.h" 

struct Novo{
	int num;
	TNovo *prox;
};

struct Lista{
	int qtd;
	Tele *inicio;
	Tele *fim;
	
};

struct elem {
	void *dado;
	Tele *prox;
};

Tele *criarElem(void *cargautil){
	Tele *p = malloc(sizeof(Tele));
	p->dado = cargautil;
	p->prox = NULL;

	return p;
}

TLista *criarLse(){
	TLista *lista = malloc(sizeof(TLista));
	lista->inicio = NULL;
	lista->fim = NULL;
	lista->qtd = 0;

	return lista;
}

TNovo *criarNovo(int n){
	TNovo *p = malloc(sizeof(TNovo));
	p->num = n;
	p->prox = NULL;

	return p;
}


void inserirInicio(TLista *lista,void *novo){
	Tele *ele = criarElem(novo);

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
	Tele *ele = criarElem(novo);

	if(lista->inicio == NULL){
		lista->inicio = ele;
		lista->fim = ele;
	}else{
		Tele *ultimo = lista->fim;
		ultimo->prox = ele;
		lista->fim = ele;
	}
	lista->qtd++;
}
void destroy(void *dado){
	//TNovo *p = dado;
	free(dado);
}
void removerInicio(TLista *lista,TDestroy destroy){
	Tele *aux = lista->inicio;
	void *dados = aux->dado;
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
		destroy(dados);
		lista->qtd--;
	}else{
		printf("Lista vazia!\n");
	}
	printf("Primeiro Elemento Removido!\n");

}

void removerFim(TLista *lista,TDestroy destroy){
	Tele *aux = lista->inicio;
	Tele *ultimo = lista->fim;
	void *dado = ultimo->dado;
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
		destroy(dado);
		free(lista->fim);
		lista->fim = aux;
		aux->prox = NULL;
	}
	lista->qtd--;
	printf("Ultimo Elemento Removido!\n");
}

void removerPos(TLista *lista,int pos,TDestroy destroy){
	Tele *aux = lista->inicio;
	Tele *ant;
	int cont = 1;
	if(pos == 1){
		removerInicio(lista,destroy);
	}else if(pos == lista->qtd){
		removerFim(lista,destroy);
	}else{
		void *dado = aux->dado;
		while(cont != pos){
			cont++;
			ant = aux;
			aux = aux->prox;
			dado = aux->dado;
		}
		ant->prox = aux->prox;
		destroy(dado);
		free(aux);
		printf("Elemento da posicao %d removido\n", pos);
	}	
}

Tele *acessarEle(TLista *lista,int pos){
	Tele *aux;
	if(pos == lista->qtd){
		aux = lista->fim;
	}else if(pos == 1){
		aux = lista->inicio;
	}else{
		aux = lista->inicio;
		int cont = 1;
		while(cont != pos){
			aux = aux->prox;
			cont++;
		}
	}
	return aux->dado;
}

void imprimiEle(void *medida){
	TNovo *aux = medida;
	if(medida != NULL){
		printf("%d\n",aux->num);
	}else{
		printf("Medida indefinida\n");
	}
}

void imprimir(TLista *lista,TImprimir imprimi){
	Tele *aux = lista->inicio;
	if(lista->inicio != NULL){
		while(aux != NULL){
			imprimi(aux->dado);
			aux = aux->prox;
		}
	}else{
		printf("Lista vazia!\n");
	}
}