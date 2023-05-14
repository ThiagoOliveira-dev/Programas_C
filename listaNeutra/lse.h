#include <stdlib.h>
#include <stdio.h>

typedef struct Novo TNovo;
typedef struct Lista TLista;
typedef struct elem Tele;
typedef void (*TImprimir)(void *);
typedef void (*TDestroy)(void *);


TLista *criarLse();
TNovo *criarNovo(int n);
Tele *criarElem(void *cargautil);
Tele *acessarEle(TLista *lista,int pos);
void inserirInicio(TLista *lista,void*novo);
void inserirFim(TLista *lista,void *novo);
void destroy(void *dado);
void removerInicio(TLista *lista,TDestroy);
void removerFim(TLista *lista,TDestroy);
void removerPos(TLista *lista,int pos,TDestroy);
void imprimir(TLista *lista,TImprimir);
void imprimiEle(void *medida);