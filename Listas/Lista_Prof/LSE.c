#include "stdio.h"
#include "stdlib.h"

typedef struct Medida TMedida;
struct Medida
{
	int long chave;

	int tempo;
	double temp;
	double lat, logt;
	double presao;
	double densidade;

	TMedida *prox;
//	double lat, log;
};



TMedida *criarMedida(int tempo){
	TMedida *medida = malloc(sizeof(TMedida));

	medida->tempo = tempo;
	//medida->temp = temp;
	medida->prox = NULL;

	return medida;
}


typedef struct lista TLista;
struct lista{
	int qtde;
	TMedida *inicio;
	TMedida *fim;
};

TLista *criarLSE(){
	TLista *lse = malloc(sizeof(TLista));

	lse->inicio = NULL;
	lse->fim = NULL;
	lse->qtde = 0;

	return lse;
}

void inserirLSE(TLista *lse, TMedida *novo){
	// lista vazia
	if (lse->inicio == NULL){
		lse->inicio = novo;
		lse->fim = novo;
	}else{
		novo->prox = lse->inicio;
		lse->inicio = novo;
	}
	lse->qtde++;
}

void inserirFimLSE(TLista *lse, TMedida *novo){

	if(lse->inicio == NULL){
		lse->inicio = novo;
		lse->fim=novo;
	}else{
		TMedida* ultimo = lse->fim;

		ultimo->prox = novo;
		lse->fim= novo;
	}
	lse->qtde++;
}

void removerLSE(TLista* lse){
	TMedida* primeiro = lse->inicio;
	printf("---removendo---\n");
	if (primeiro != NULL){
		// unico elemento?
		if(lse->inicio == lse->fim){
			lse->inicio=NULL;
			lse->fim=NULL;
		}else{// caso geral
			lse->inicio = primeiro->prox;
		}
		//liberou a memoria
		free(primeiro);
		lse->qtde--;
	}

}

void imprimirLSE(TLista *lse)
{
	TMedida *cam = lse->inicio;
	while(cam!=NULL){
		printf("%d\n", cam->tempo);
		cam=cam->prox;
	}

}

void removerFinalLSE(TLista *lse){
		TMedida *cam=lse->inicio;
		if (lse->inicio==NULL){ // lista vazia
			printf("Lista vazia\n");
		}else if (lse->inicio == lse->fim){ // unico
			lse->inicio = NULL;
			lse->fim = NULL;
			lse->qtde = 0;
			free(cam);
		}else{ // pelo menos dois elementos na lista
			while(cam->prox!=lse->fim){
				cam = cam->prox;
			}
			free(lse->fim);
			lse->fim=cam;
			cam->prox=NULL;
			lse->qtde--;
		}
}

void removerPosicaoLSE(TLista *lse, int pos){
	if (pos == 1){
		removerLSE(lse);
	}else if(pos == lse->qtde){
		removerFinalLSE(lse);
	}else{
		TMedida *cam = lse->inicio;
		TMedida *anterior = NULL;
		int contador = 1;
		while(pos > contador){
			anterior = cam;
			cam = cam->prox;
			contador++;
		}
		anterior->prox = cam->prox;
		free(cam);
		lse->qtde--;
	}
}

TMedida *acessarLSE(TLista *lse, int pos){
	TMedida *cam = NULL;
	if ( (pos>0) && (pos<=lse->qtde) ){
		cam = lse->inicio;
		int contador = 1;
		while(contador<pos){
			cam = cam->prox;
			contador++;
		}
	}
	return cam;
}


TMedida *buscarLSE(TLista *lse, double temperatura){
	TMedida *cam = NULL;

	cam = lse->inicio;
	while( (cam!=NULL) && (cam->temp != temperatura)){
		cam = cam->prox;
	}
	return cam;
}

void removerConteudoLSE(TLista *lse, int long chave){
		TMedida *cam = lse->inicio;
		TMedida *anterior = NULL;
		while ( (cam!=NULL) && (chave != cam->chave) ){
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

//ordenacao por insercao
//inserirConteudoLSE(TLista *lse, int long chave, TMedida *novo){




int main(int argc, char const *argv[])
{
	int tempo;
	double temperatura;
	// criar lista encadeada vazia

	TLista* lst = criarLSE();
	int long chave=1;

	scanf("%d",&tempo);
	while(tempo>=0){
		//scanf("%lf",&temperatura);
		// criar instancia do TMedida
		TMedida* m = criarMedida(tempo);

		// inserir elemento na lista
		inserirFimLSE(lst, m);

		chave = chave + 1;

		scanf("%d", &tempo);
	}
	// imprimir
	imprimirLSE(lst);
	removerFinalLSE(lst);
	printf("Removeu do final\n");

	imprimirLSE(lst);
	//removerPosicaoLSE(lst,2);
	//printf("Removeu na posicao\n");

	//imprimirLSE(lst);
	//TMedida *m = acessarLSE(lst,2);
	//printf("acessou: %d %lf\n", m->tempo, m->temp);



	// removerLSE(lst);
	//
	// imprimirLSE(lst);
	//
	// removerLSE(lst);
	//
	// imprimirLSE(lst);
	//
	// removerLSE(lst);
	return 0;
}
