#include <stdio.h>
#include <stdlib.h>


//Programa que recebe duas listas e retorna uma lista com a UNIÃO e uma lista com a INTERSEÇÃO.






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
}


void imprimir(TLista *l){
	TNovo *aux = l->inicio;
	while(aux != NULL){
		printf("%d\t",aux->num );
		aux = aux->prox;
	}
}

//funçao que retira os elementos repetidos de uma lista
void RetiraRepitido(TLista *l){
	
	TNovo *lista = l->inicio;//pivo que inicia no primeiro elemento
	TNovo *inicio; // Pivo que inicia no segundo elemento
	TNovo *ant; // auxiliar para modificar a lista encadeada

	
	while(lista != NULL){//Implenta o pivo 'lista' na estrutura de repetiçao mais externa
		inicio = lista->prox;
		ant = lista;// sempre fica antes de 'inicio'
		while(inicio != NULL){
			//na estrutura de repetiçao interna verifica cada iteraçao do pivo inicio com o pivo 'lista', de modo a colocar
			//o pivo 'inicio' com o mesmo valor do pivo 'lista', e o auxiliar 'ant' sempre antes de 'inicio', para podermos modificar a lista
			if(inicio->num != lista->num){
				ant = inicio;
				inicio = inicio->prox;
			}else{
				ant->prox = inicio->prox;
				free(inicio);
				inicio = ant->prox;
				l->qtd--;
			}
		}
	lista = lista->prox;
	}
}


void FuncaoUniao(TLista *Uniao, TLista *lista1, TLista *lista2){

	TNovo *aux1 = lista1->inicio;
	TNovo *aux2 = lista2->inicio;
	int flag;


	RetiraRepitido(lista1);
	RetiraRepitido(lista2);
	while(aux1 != NULL){
		TNovo *novo = criarNovo(aux1->num);
		inserirFim(Uniao,novo);

		aux1 = aux1->prox;

	}

	while(aux2 != NULL ){
		flag = 0;
		aux1 = lista1->inicio;
		while(aux1 != NULL){
			if(aux2->num == aux1->num){
				flag = 1;
			}
			aux1 = aux1->prox;
		}
		if(flag == 0){
			TNovo *novo = criarNovo(aux2->num);
			inserirFim(Uniao,novo);
		}
		aux2 = aux2->prox;
	}
}


void FuncaoIntersecao(TLista *Intersecao, TLista *lista1, TLista *lista2){

	TNovo *aux1 = lista1->inicio;
	TNovo *aux2 = lista2->inicio;
	int flag;

	while(aux2 != NULL ){
		flag = 0;
		aux1 = lista1->inicio;
		while(aux1 != NULL){
			if(aux2->num == aux1->num){
				flag = 1;
			}
			aux1 = aux1->prox;
		}
		if(flag == 1){
			TNovo *novo = criarNovo(aux2->num);
			inserirFim(Intersecao,novo);
		}
		aux2 = aux2->prox;
	}
}


int main(){
	TLista *lista1 = criarLse();
	TLista *lista2 = criarLse();
	TLista *Uniao = criarLse();
	TLista *Intersecao = criarLse();
	int num;
	scanf("%d",&num);
	while(num != 0){
		TNovo *novo = criarNovo(num);
		inserirFim(lista1,novo);
		scanf("%d",&num);
	}
	scanf("%d",&num);
	while(num != 0){
		TNovo *novo = criarNovo(num);
		inserirFim(lista2,novo);
		scanf("%d",&num);
	}

	printf("Lista 1: " );
	imprimir(lista1);

	printf("\n");
	printf("Lista 2: " );
	imprimir(lista2);

	printf("\n");
	printf("Uniao: " );
	FuncaoUniao(Uniao, lista1, lista2);
	imprimir(Uniao);

	printf("\n");
	printf("Intersecao: " );
	FuncaoIntersecao(Intersecao,lista1, lista2);
	imprimir(Intersecao);
	printf("\n");



	
	return 0;
}