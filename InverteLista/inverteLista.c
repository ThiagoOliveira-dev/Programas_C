#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Programa inverte uma lista encadeada, excluíndo os elementos repetidos, sem precisar criar novas listas auxiliares, 


typedef struct Novo TNovo;
struct Novo
{
	int num;
	int pos;
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

TNovo *criarNovo(int n, int pos){
	TNovo *novo = malloc(sizeof(TNovo));
	novo->num = n;
	novo->pos = pos;
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
		//printf("Elemento da posicao %d removido\n", pos);
	}	
}


void imprimir(TLista *lista){
	TNovo *aux = lista->inicio;
	while(aux != NULL){
		printf("%d\t",aux->num);
		aux = aux->prox;
	}
}

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


void inverta(TLista *l, int PosFixa){
	TNovo *auxPos = l->inicio;
	TNovo *posAnt = l->inicio;
	TNovo *fim = l->fim;
	TNovo *novo = l->inicio;
	
	// posiciona o elemento novo na posFixa, começando pelo fim da lista.
	while(novo->pos < PosFixa){
		novo = novo->prox;
	}

	// posiciona o elemento posAnt na posiçao anterio ao elemento posFixa.
	while(posAnt->pos < PosFixa - 1){
		posAnt = posAnt->prox;
	}

	//posiciona o elemento auxPos antes do posAnt para poder manipular o elemento posAnt na lista.
	while(auxPos->pos < posAnt->pos - 1 ){
		auxPos = auxPos->prox;
	}

	// consiçao de parada da recursão, quando a PosFixa estiver no primeiro elemento da lista.	
	if((PosFixa != 0) ){
		//condiçao para quando PosFixa estiver no segundo elemento, a posAnt deverá ir para o fim da lista.
		if(posAnt->pos == 0){
			fim->prox = posAnt;
			l->fim = posAnt;
			l->inicio = auxPos->prox;
			posAnt->prox = NULL;
		//para quando a posFixa não estiver no segundo elemento
		}else{
			// O elemento posAnt deverá ir para o final lista, o elemento anterior do posAnt(auxPos) deverá apontar para o proximo
			//elemento do posAnt(novo), depois devemos atualizar a lista, com l->fim apontando para posAnt, e devemos atualizar o 
			//elemento posAnt com NULL, pois estará no fim da lista.
			fim->prox = posAnt;
			auxPos->prox = novo;
			l->fim = posAnt;
			posAnt->prox = NULL;
		}
	PosFixa--;
	inverta(l, PosFixa);// chama a recursão com o valor da posFixa atualizado para mais proximo do inicio da lista.
	}
}

void reoganizaPosicao(TLista *lista){
	TNovo *aux = lista->inicio;
	int pos = 0;

	while(aux != NULL){
		aux->pos = pos;
		pos++;
		aux = aux->prox;
	}
}

int main(){

	TLista *lista = criarLse();
	char n[100];
	char *subs;
	int num;
	int pos = 0;
	int tam;
	
	scanf("%[^\n]",n);// método para o scanf ler uma cadeia de string.

	// a funçao 'strtok' divide uma string em substrings de acordo com o modelo passado pelo parametro.
	subs = strtok( n, " ");// retorna a primeira substring 


	 
	while(subs){ //Enquanto strtok não retorna NULL;
		
		num = atoi(subs);//transforma uma string em interiro
		TNovo *novo = criarNovo(num,pos);
		inserirFim(lista,novo);
		pos++;
		subs = strtok( NULL, " ");// retorna a proxima substring da string original até chegar na ultima substrig e depois retorna NULL


	}
	
	RetiraRepitido(lista);//retira numeros repetidos
	reoganizaPosicao(lista);//precisamos reoganizar as posiçoes de cada elemento depois de retirar os repetidos, pois precisamos 
	//das posições para a funçao 'inverta'.


	
	if(lista->qtd > 0){
		tam = lista->qtd;
		tam--;
		inverta(lista, tam);
		imprimir(lista);
		printf("\n");
	}else
		printf("Lista vazia!\n");
}