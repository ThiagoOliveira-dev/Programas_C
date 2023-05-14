#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,j,n,aux,v[10],troca=0;

    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%d",&v[i]);
    }

    for(j=n-1;j>0;j--){
        for(i=0;i<j;i++){
            if(v[i] > v[i+1]){
                aux = v[i+1];
                v[i+1] = v[i];
                v[i] = aux;
                troca = 1;
            }
        }
        if(troca == 0){
            j = 0;
        }
    }
    printf("\n");
    for(i=0;i<n;i++){
        printf("%d\t",v[i]);
    }
    return 0;
}
