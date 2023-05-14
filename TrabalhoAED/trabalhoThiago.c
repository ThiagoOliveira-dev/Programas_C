#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define QUALIFY1 10
#define QUALIFY2 8
#define QUALIFY3 5
#define NUMERO_PILOTOS 24

struct Pilotos
{
    int    tempo;
    int    numero;
	char   equipe;
    int    vai_correr;
    struct Pilotos *prox;
};
typedef struct Pilotos TpPilotos;
typedef TpPilotos *PtrPilotos;

typedef struct Lista TLista;
struct Lista
{
	int qtd;
	TpPilotos *inicio;
	TpPilotos *fim;
	
};


TLista *criarLse();
TpPilotos *criarNovo( int numero, char equipe);
void inserirFim(TLista *lista,TpPilotos *novo);
void inserirInicio(TLista *lista,TpPilotos *novo);
TpPilotos *removerfim(TpPilotos *lista);


void imprimir(TpPilotos *aux, int treino);
void RetiraRepitido(TLista *l, int maximo_de_pilotos);
void quem_corre(int qtdVolta, int maximo_de_pilotos, TLista *listaVolta);
void tempo_da_volta(TpPilotos *auxiliarPtr);
void RetiraRepitidoLista(TLista *l, TLista *l2, int maximo_de_pilotos);
void guardaMenor(TpPilotos *inicioLista, TpPilotos *listaVolta);
void gerarvolta(TpPilotos *primeiro, TLista *startPtr, int qtdCarro, int max_de_pilotos, int treino);		
void listaOrdenada(TpPilotos *inicio);
void desata_no(TpPilotos *inicio, TLista *grid);
void eliminaEtapas(TpPilotos *inicio, TLista *grid, int treino);
void zeratempo(TpPilotos *inicio);
void qualify(TpPilotos *inicio, TLista *grid, int voltas_max,int max_de_pilotos, int treino);
void excluiLista(TLista *lista);
void removerfimLista(TLista *lista);


int main(int argc, char const *argv[]){
	int i, j;
	char equipe[] = {'A', 'A', 'B', 'B', 'C', 'C', 'D', 'D', 'E', 'E', 'F', 'F', 'G', 'G', 'H', 'H', 'I', 'I', 'J', 'J', 'L', 'L', 'M', 'M' };
	TLista *listaCompleta = criarLse();
	TLista *grid = criarLse();

	j = 0;
	for(i = 1; i <= NUMERO_PILOTOS; i++ ){
		TpPilotos *novo = criarNovo(i, equipe[j]);
		inserirFim(listaCompleta, novo);
		j++;
		
	}
	qualify(listaCompleta->inicio, grid, QUALIFY1, NUMERO_PILOTOS, 1);
	
	return 0;
}

void qualify(TpPilotos *inicio, TLista *grid, int voltas_max,int max_de_pilotos, int treino){


	if(treino <= 3){
		int qtdCarro;
		
		srand(time(NULL));
		// Loop com a quantidade de voltas de cada treino.
		for (int i = 0; i < voltas_max; i++){
			
			qtdCarro = 1 + rand() % max_de_pilotos + 1;
			// funçao que gera a listaVolta com a quantiddade de carros em cada volta.
			//depois atualiza a listaCompleta e a lista grid.
			gerarvolta(inicio, grid, qtdCarro, max_de_pilotos, treino);
				
		}
		// ordena a listaCompleta com menor tempo.
		listaOrdenada(inicio);
		// imprime com o menor tempo de cada parte treino.
		imprimir(inicio, treino);
		printf("\n\n");

		//elimina os pilotos da listaCompleta de acordo com cada parte do treino e inseri na lista grid
		//no final do treino imprime a lista grid.
		eliminaEtapas(inicio, grid, treino);
		zeratempo(inicio);

		if(treino == 1){
			voltas_max = 8;
			max_de_pilotos = 17;
		}
		if(treino == 2){
			voltas_max = 5;
			max_de_pilotos = 10;
		}
		treino++;
		qualify(inicio, grid, voltas_max, max_de_pilotos, treino);
	}

}
//Cria a lista volta de acordo com a quantidade de pilotos de cada parte do treino, implementa os dados de cada piloto
//e depois copia na lista completa ou na lista grid de acordo com as etapas do treino.
void gerarvolta(TpPilotos *inicioListaCompleta, TLista *grid, int qtdCarro, int max_de_pilotos, int treino){
	TLista *listaVolta = criarLse();
	int numVolta;
	

	if( treino == 1){
			numVolta = 10;
	}if( treino == 2){
			numVolta = 8;
	}if( treino == 3){
			numVolta = 5;
	}
	//cria nós de acordo com a quantidade aleatória passada pelo parametro.
	for (int i = 0; i < qtdCarro; i++){
		TpPilotos *novo = criarNovo(0, 'A');
		inserirFim(listaVolta, novo);
	}
	
	//implemeta o numero do carro aleatoriamente de cada piloto, não repetindo os numeros dos carros ja implementados nesta volta.
	quem_corre(qtdCarro, max_de_pilotos, listaVolta);
	//retira os pilotos que foram gerados aleatoriamente porém que ja estão na lista grid.
	RetiraRepitidoLista(grid, listaVolta, max_de_pilotos);
	//implementa o tempo da volta de cada piloto da lista grid, não ultrapassando 5000ms.
	tempo_da_volta(listaVolta->inicio);
	//compara se o tempo dos pilotos da listaVolta sao menores que o tempo da listaCompleta, caso seja, serão trocados.
	guardaMenor(inicioListaCompleta, listaVolta->inicio);
	//apaga a listavolta
	//excluiLista(listaVolta);

}
// atribui um numero aos pilotos
void quem_corre(int qtdVolta, int maximo_de_pilotos, TLista *listaVolta){
	
	TpPilotos *aux = listaVolta->inicio;
	
	srand(time(NULL));
	while( aux != NULL){

		aux->numero = 1 + rand() % maximo_de_pilotos + 1;
		aux->vai_correr++;
		aux = aux->prox;
	}

	RetiraRepitido(listaVolta, maximo_de_pilotos);

}
void RetiraRepitido(TLista *l, int maximo_de_pilotos){
	
	TpPilotos *lista = l->inicio;//pivo que inicia no primeiro elemento
	TpPilotos *inicio; // Pivo que inicia no segundo elemento
	TpPilotos *ant; // auxiliar para modificar a lista encadeada

	srand(time(NULL));
	while(lista != NULL){//Implenta o pivo 'lista' na estrutura de repetiçao mais externa
		inicio = lista->prox;
		ant = lista;// sempre fica antes de 'inicio'
		while(inicio != NULL){
			//na estrutura de repetiçao interna verifica cada iteraçao do pivo inicio com o pivo 'lista', de modo a colocar
			//o pivo 'inicio' com o mesmo valor do pivo 'lista', e o auxiliar 'ant' sempre antes de 'inicio', para podermos modificar a lista
			if(inicio->numero != lista->numero){
				ant = inicio;
				inicio = inicio->prox;
			}else{
				inicio->numero = 1 + rand() % maximo_de_pilotos + 1;
			}
		}
	lista = lista->prox;
	}
}

//tira os elementos de l da lista l2;
void RetiraRepitidoLista(TLista *l, TLista *l2, int maximo_de_pilotos){
	
	TpPilotos *lista = l->inicio;//pivo que inicia no primeiro elemento
	TpPilotos *inicio; // Pivo que inicia no segundo elemento
	TpPilotos *ant; // auxiliar para modificar a lista encadeada
	srand(time(NULL));
	while(lista != NULL){//Implenta o pivo 'lista' na estrutura de repetiçao mais externa
		inicio = l2->inicio;
		ant = inicio;// sempre fica antes de 'inicio'
		while(inicio != NULL){
			//na estrutura de repetiçao interna verifica cada iteraçao do pivo inicio com o pivo 'lista', de modo a colocar
			//o pivo 'inicio' com o mesmo valor do pivo 'lista', e o auxiliar 'ant' sempre antes de 'inicio', para podermos modificar a lista
			if(inicio->numero != lista->numero){
				ant = inicio;
				inicio = inicio->prox;
			}else{
				inicio->numero = 1 + rand() % maximo_de_pilotos + 1;
			}
		}
	lista = lista->prox;
	}
}
//atribui o tempo da volta para cada piloto
void tempo_da_volta(TpPilotos *auxiliarPtr){
	srand(time(NULL));
	while(auxiliarPtr != NULL){
		auxiliarPtr->tempo = 1000 + rand() % 5001;
		auxiliarPtr = auxiliarPtr->prox;
	}
}
//criei um pivo para a lista completa e um pivo para a lista volta, depois comparei cada pivo da listaCompleta com a listaVolta
// e fiz as trocas necessarias.
void guardaMenor(TpPilotos *inicioLista, TpPilotos *listaVolta){
	TpPilotos *listaCompleta = inicioLista;
	while(listaVolta != NULL){
		listaCompleta = inicioLista;
		while(listaCompleta != NULL){
			if(listaVolta->numero == listaCompleta->numero ){
				listaCompleta->vai_correr++;
				if(listaVolta->tempo < listaCompleta->tempo){
					listaCompleta->tempo = listaVolta->tempo;
				}

			}
			listaCompleta = listaCompleta->prox;
		}
	listaVolta = listaVolta->prox;
	}
}
void removerfimLista(TLista *lista){
	TpPilotos *aux = lista->inicio;
	if(lista->inicio == lista->fim){//unico elemento na lista
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
//Não consegui excluir
void excluiLista(TLista *lista){
	if(lista->inicio != NULL){
		removerfimLista(lista);
		excluiLista(lista);
	}
	//free(lista);
	
}

//InsertionSort
void listaOrdenada(TpPilotos *inicio){
	TpPilotos *menor;
	TpPilotos *aux;
	
	for( TpPilotos *i = inicio; i != NULL; i = i->prox){
		menor = i;
		for (TpPilotos *j = i->prox; j != NULL; j = j->prox){
			if(j->tempo < menor->tempo){
				menor = j;
			}
		}
		aux->numero = i->numero;
		aux->tempo = i->tempo;
		aux->equipe = i->equipe;
		aux-> vai_correr = i->vai_correr;

		i->numero = menor->numero;
		i->tempo = menor->tempo;
		i->equipe = menor->equipe;
		i->vai_correr = menor->vai_correr;

		menor->numero = aux->numero;
		menor->tempo = aux->tempo;
		menor->equipe = aux->equipe;
		menor->vai_correr = aux-> vai_correr;

	}

		
}
// Implementa a lista grid, retirando os elementos necessarios de cada etapa do treino da listaCompleta 
//e inserindo no inicio da lista grid, e no final das etapas imprimi a lista grid.
void eliminaEtapas(TpPilotos *inicioListaCompleta, TLista *grid, int treino){
	int eliminados;

	if(treino == 1){
		eliminados = 7;
	}
	if(treino == 2){
		eliminados = 7;
	}
	if(treino == 3){
		eliminados = 10;
	}

	for (int i = 0; i < eliminados; i++){
		desata_no(inicioListaCompleta, grid);
	}

	if(treino == 3){
		imprimir(grid->inicio, 4);
		printf("\n\n");

	}
}
//Inseri no inicio da lista grid o ultimo elemento da listaCompleta ja ordenada.
void desata_no(TpPilotos *inicioListaCompleta, TLista *grid){
	inserirInicio(grid, removerfim(inicioListaCompleta));

}
//Zera o tempo no final de cada etapa do treino.
void zeratempo(TpPilotos *inicio){
	while(inicio != NULL){
		inicio->tempo = 5000;
		inicio->vai_correr = 0;
		inicio = inicio->prox;
	}
}

void imprimir(TpPilotos *aux, int treino){
	int pos = 1;
	if(treino == 1){
		printf("Q1\n");
		printf("----------------------------------\n");
	}
	if(treino == 2){
		printf("Q2\n");
		printf("----------------------------------\n");
	}
	if(treino == 3){
		printf("Q3\n");
		printf("----------------------------------\n");
	}
	if(treino == 4){
		printf("GRID LARGADA\n");
		printf("----------------------------------\n");
	}

	printf("| pos. | plto | equipe | tempo |");
	printf("\n");
	while(aux != NULL){
		printf("|  %d  |  %d  |  %c  |  %d  | %d",pos,aux->numero,aux->equipe,aux->tempo,aux->vai_correr);
		
		printf("\n");

		pos++;
		aux = aux->prox;
	}
	printf("----------------------------------\n");
}

TLista *criarLse(){
	TLista *lista = malloc(sizeof(TLista));
	lista->inicio = NULL;
	lista->fim = NULL;
	lista->qtd = 0;

	return lista;
}

TpPilotos *criarNovo( int numero, char equipe){
	TpPilotos *novo = malloc(sizeof(TpPilotos));
	novo->tempo = 5000;
	novo->numero = numero;
	novo->equipe = equipe;
	novo->vai_correr = 0;
	novo->prox = NULL;

	return novo;
}


void inserirFim(TLista *lista,TpPilotos *novo){
	if(lista->inicio == NULL){
		lista->inicio = novo;
		lista->fim = novo;
	}else{
		TpPilotos *ultimo = lista->fim;
		ultimo->prox = novo;
		lista->fim = novo;
	}
	lista->qtd++;
}
void inserirInicio(TLista *lista,TpPilotos *novo){
	if(lista->inicio == NULL){
		lista->inicio = novo;
		lista->fim = novo;
	}else{
		novo->prox = lista->inicio;
		lista->inicio = novo;
	}
	lista->qtd++;
}

TpPilotos *removerfim(TpPilotos *lista){
	TpPilotos *aux = lista;
	TpPilotos *auxAnt;
	if(lista == NULL){
		printf("Lista vazia!\n");
	}else{ 
		//lista com mais de um elemento
		while(aux->prox != NULL){
			auxAnt = aux;
			aux = aux->prox;
		}
		auxAnt->prox = NULL;
	}
	return aux;

	//printf("Ultimo Elemento Removido!\n");
}