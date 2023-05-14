#include <stdlib.h>
#include <stdio.h>

typedef struct Fila TFila;
typedef struct Medida TMedida;
typedef struct elem Tele;
typedef struct Lista TLista;
typedef void (*TDestroy)(void *);
typedef int (*TProcura)(void *,void *);
typedef void (Timprimir)(void *);



Tele *criaElem(void *ele);
TLista *criaLista();
TMedida *criaMedida(int num,double real);

void inserirInicio(TLista *lista,void *novo);
void inserirFim(TLista *lista,void *novo);
void destroyMedida(void *medida);
void removerInicio(TLista *lista,TDestroy destroy);
void removerFim(TLista *lista,TDestroy destroy);
void removerPos(TLista *lista,int pos,TDestroy destroy);
void *acessarPos(TLista *lista,int pos);
void impEle(void *ele);
void imprimir(TLista *lista,Timprimir imp);
int comparaMedida(void *buscado,void *medida);
int buscarMedida(TLista *lista,void *buscado,TProcura buscar);
void enfileira(TFila *fila,void *medida);
