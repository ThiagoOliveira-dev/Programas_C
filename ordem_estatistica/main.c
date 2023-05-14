#include <stdio.h>
#include <stdlib.h>
//Pragrama para achar k-esima maior ordem estatista:

int main(){
    int i,k,tam,li,ls,pivo,in,su;

    printf("digite o tamanho do vetor: ");
    scanf("%d",&tam);
    int v[tam],aux[tam];

    printf("Digite o vetor: ");
    for(i=0;i<tam;i++){
        scanf("%d",&v[i]);

    }

    printf("Digite a k-esima ordem desejada: ");
    scanf("%d",&k);
    li = 0;
    ls = tam-1;

    while(pivo != (k-1)){
        pivo = (li + ls)/2;
        in = 0;
        su = tam - 1;
        for(i=0;i<tam;i++){
            if(v[i] < v[pivo]){
                aux[in] = v[i];
                in++;
            }else if(v[i] > v[pivo]){
                aux[su] = v[i];
                su--;
            }
        }
        //printf("\npivo: %d in:%d su:%d\n",pivo,in,su);
        aux[in] = v[pivo];
        pivo = in;
        printf("\n");
        for(i=0;i<tam;i++){
            v[i] = aux[i];
            //printf("%d\t",v[i]);
        }
        if(pivo < k-1){
            li = pivo;
            ls = tam - 1;
        }else if(pivo > k-1){
            li = 0;
            ls = pivo;
        }
    }
    printf("A k-esima ordem: %d",v[pivo]);

    return 0;
}
