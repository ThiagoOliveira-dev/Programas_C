#include <stdio.h>
#include <stdlib.h>


typedef struct Dado TDado;
struct Dado{
    int n;
};

typedef struct Vetor TVetor;
struct Vetor{
    int pos;
    int tam;
    TDado *vetor;
};

void inserirVD(TVetor *VD, TDado dado){
    if(VD->pos+1 == VD->tam){
        VD->tam = VD->tam*2;
        VD->vetor = realloc(VD->vetor,sizeof(TDado)*VD->tam);
        
    }
    VD->vetor[VD->pos] = dado;
    VD->pos++;
}

void imprimir(TVetor VD){
    int i;
    for(i = 0; i < VD.pos; i++){
        printf("%d\n",VD.vetor[i].n);
    }
}

int main(int argc, char const *argv[]){
    TVetor VDinamico;
    TDado dado;

    VDinamico.pos = 0;
    VDinamico.tam = 2;
    VDinamico.vetor = malloc(sizeof(TDado)*VDinamico.tam);

    while(scanf("%d",&dado.n)){
        inserirVD(&VDinamico,dado);
    }
    imprimir(VDinamico);

    return 0;
}
