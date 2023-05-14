#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,j,aux,n;
    
    scanf("%d",&n);
    int v[n];
    printf("\n");

    for(i=0;i<n;i++){
        scanf("%d",&v[i]);
    }

    for(j=n-1;j>0;j--){
        for(i=0;i<j;i++){
            if(v[i] > v[j]){
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
        }
    }
    printf("\n");
    for(i=0;i<n;i++){
        printf("%d\t",v[i]);
    }

    return 0;
}
