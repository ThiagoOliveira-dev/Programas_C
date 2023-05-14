
#include "stdio.h"
#include "stdlib.h"

typedef struct Medida TMedida;
struct Medida
{
	int long chave;
	int tempo;
	double temp;
	double lat, lgt;
	double presao;
	double densidade;
///	TMedida *prox;
};


TMedida *criarMedida(int chave, int tempo, double temp, double lat, double lgt, double presao, double densidade){
	TMedida *medida = malloc(sizeof(TMedida));

	medida->chave = chave;
	medida->tempo = tempo;
	medida->temp = temp;
	medida->lat = lat;
	medida->lgt = lgt;
	medida->presao = presao;
	medida->densidade = densidade;

//	medida->prox = NULL;
	return medida;
}

void imprimirMedida(void *medida){
	TMedida *m = medida;
	if (m!=NULL){
		printf("%ld %d %lf %lf %lf %lf %lf\n",m->chave, m->tempo, m->temp, m->lat, m->lgt, m->presao, m->densidade );
	}else{
		printf("Medida Indefinida\n");
	}
}

int compararMedida(void *buscado, void *medida){
	TMedida *m = medida;
	TMedida *b = buscado;
	int resultado;

	if(b->tempo == m->tempo){
		resultado = 0;
	}else if(b->tempo > m->tempo){
		resultado = 1;
	}else{
		resultado = -1;
	}

	printf("---Comparando medida: retornando:%d ----\n",resultado);
	return resultado;
}

int compararConteudoMedida(int long chave, void *medida){
	TMedida *m = medida;
	int resultado;

	if(chave == m->chave){
		resultado = 0;
	}else if(chave > m->chave){
		resultado = 1;
	}else{
		resultado = -1;
	}

	printf("---Comparando medida: retornando:%d ----\n",resultado);
	return resultado;
}



void 	destroyMedida(void *medida){
	//TMedida *m = medida;
	printf("----Destroy medida ----\n");
	free(medida);
}

// typedef struct ele{
// 	void *cargautil;
// 	void *prox;
// }TELE;


typedef struct ele TELE;
struct ele{
	void *cargautil;
	TELE *prox;
};

TELE *criarELE(void *cargautil){
		TELE *e = malloc(sizeof(TELE));
		e->cargautil = cargautil;
		e->prox = NULL;

		return e;
}

typedef struct lista TLista;
struct lista{
	int qtde;
	TELE *inicio;
	TELE *fim;
};

TLista *criarLSE(){
	TLista *lse = malloc(sizeof(TLista));

	lse->inicio = NULL;
	lse->fim = NULL;
	lse->qtde = 0;

	return lse;
}


void inserirLSE(TLista *lse, void *novo){
	// lista vazia

	TELE *ele = criarELE(novo);

	if (lse->inicio == NULL){
		lse->inicio = ele;
		lse->fim = ele;
	}else{
		ele->prox = lse->inicio;
		lse->inicio = ele;
	}
	lse->qtde++;
}
//
void inserirFimLSE(TLista *lse, void *novo){

	TELE *ele = criarELE(novo);

	if(lse->inicio == NULL){
		lse->inicio = ele;
		lse->fim=ele;
	}else{
		TELE* ultimo = lse->fim;

		ultimo->prox = ele;
		lse->fim= ele;
	}
	lse->qtde++;
}

typedef void (*TDestroyLSE)(void*);
//
void removerLSE(TLista* lse, TDestroyLSE destroy){
	TELE* primeiro = lse->inicio;
	printf("---removendo---\n");
	if (primeiro != NULL){
		void *cargautil=primeiro->cargautil;
		// unico elemento?
		if(lse->inicio == lse->fim){
			lse->inicio=NULL;
			lse->fim=NULL;
		}else{// caso geral
			lse->inicio = primeiro->prox;
		}
		//liberou a memoria
		free(primeiro);
		destroy(cargautil);
		lse->qtde--;
	}

}

//
typedef void (*TImpressoraLSE)(void*);

void imprimirLSE(TLista *lse, TImpressoraLSE imprimir)
{
	TELE *cam = lse->inicio;
	while(cam!=NULL){
	  imprimir(cam->cargautil);
		//printf("%p %p %p\n", cam, cam->cargautil, cam->prox);
		cam=cam->prox;
	}

}

void removerFinalLSE(TLista *lse, TDestroyLSE destroy){
		TELE *cam=lse->inicio;
		if (lse->inicio==NULL){ // lista vazia
			printf("Lista vazia\n");
		}else if (lse->inicio == lse->fim){ // unico
			lse->inicio = NULL;
			lse->fim = NULL;
			lse->qtde = 0;

			destroy(cam->cargautil);
			free(cam);
		}else{ // pelo menos dois elementos na lista
			while(cam->prox!=lse->fim){
				cam = cam->prox;
			}
			destroy(lse->fim->cargautil);
			free(lse->fim);
			lse->fim=cam;
			cam->prox=NULL;
			lse->qtde--;
		}
}
//
void removerPosicaoLSE(TLista *lse, int pos, TDestroyLSE destroy){
	if (pos == 1){
		removerLSE(lse, destroy);
	}else if(pos == lse->qtde){
		removerFinalLSE(lse,destroy);
	}else{
		TELE *cam = lse->inicio;
		TELE *anterior = NULL;
		int contador = 1;
		while(pos > contador){
			anterior = cam;
			cam = cam->prox;
			contador++;
		}
		anterior->prox = cam->prox;
		destroy(cam->cargautil);
		free(cam);
		lse->qtde--;
	}
}
//
void *acessarLSE(TLista *lse, int pos){
	TELE *cam = NULL;
	void *cargautil = NULL;
	if ( (pos>0) && (pos<=lse->qtde) ){
		cam = lse->inicio;
		int contador = 1;
		while(contador<pos){
			cam = cam->prox;
			contador++;
		}
		cargautil = cam->cargautil;
	}

	return cargautil;
}
//
typedef int (*TCompararLSE)(void*,void*);
//
void *buscarLSE(TLista *lse, void* buscado, TCompararLSE comparar){
	TELE *cam = NULL;

	cam = lse->inicio;
	while( (cam!=NULL) && comparar(buscado,cam->cargautil)!=0){
		cam = cam->prox;
	}
	if(cam == NULL){
		return NULL;
	}else{
		return cam->cargautil;
	}
}

typedef int (*TCompararConteudoLSE)(int long,void*);

void removerConteudoLSE(TLista *lse, int long chave, TCompararConteudoLSE comparar){
		TELE *cam = lse->inicio;
		TELE *anterior = NULL;
		while ( (cam!=NULL) && comparar(chave, cam->cargautil) != 0 ){
			anterior = cam;
			cam = cam->prox;
		}
		if (cam==NULL){
			printf("404 - Not Found\n");
		}else{
			 if(lse->inicio == lse->fim){
					lse->fim=NULL;
					lse->inicio=NULL;
				}else if (cam == lse->inicio){
					lse->inicio = cam->prox;
				}else if(cam == lse->fim){
					lse->fim = anterior;
					anterior->prox = NULL;
				}else{
					anterior->prox = cam->prox;
				}
				free(cam);
				lse->qtde--;
		}
}

// //ordenacao por insercao
// inserirConteudoLSE(TLista *lse, int long chave, TMedida *novo){
//
// }


int main(int argc, char const *argv[])
{
	int tempo;
	double temperatura;
	double lat, lgt, presao, densidade;
	// criar lista encadeada vazia

	TLista* lst = criarLSE();
	int long chave=1;

	scanf("%d",&tempo);
	while(tempo>=0){
		scanf("%lf%lf%lf%lf%lf",&temperatura, &lat, &lgt, &presao, &densidade);
		// criar instancia do TMedida
		TMedida* m = criarMedida(chave, tempo, temperatura, lat, lgt, presao, densidade);

//		imprimirMedida(m);

		// inserir elemento na lista
		inserirFimLSE(lst, m);

		//imprimirMedida(acessarLSE(lst,lst->qtde));

		chave = chave + 1;

		scanf("%d", &tempo);
		//printf("dentro\n");
	}
	//printf("%p %p\n", imprimirLSE, imprimirMedida);
	// imprimir
	imprimirLSE(lst, imprimirMedida);
	// removerFinalLSE(lst);
	// printf("Removeu do final\n");
	//
	// imprimirLSE(lst);
	// removerPosicaoLSE(lst,2);
	// printf("Removeu na posicao\n");
	//
	// imprimirLSE(lst);
	// TMedida *m = acessarLSE(lst,2);
	// printf("acessou: %d %lf\n", m->tempo, m->temp);
	//

	//removerLSE(lst, destroyMedida);

	//quem eh o buscado?
	// printf("informe tempo buscado:"); scanf("%d%lf",&tempo,&temperatura);
	// TMedida *buscado = criarMedida(0,tempo,temperatura,0,0,0,0);
	// TMedida *resultado = buscarLSE(lst, buscado, compararMedida);
	// imprimirMedida(resultado);

	removerConteudoLSE(lst, 3, compararConteudoMedida);
	//removerFinalLSE(lst,destroyMedida);

	removerPosicaoLSE(lst,1,destroyMedida);

	imprimirLSE(lst, imprimirMedida);

	return 0;
}
