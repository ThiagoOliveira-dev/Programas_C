#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char *palindrome(char *v, int i, int fim){
	if(i < fim){
		if(v[i] == v[fim]){
			i = i + 1;
			fim = fim - 1;
			return palindrome(v, i, fim);
		}else{
			return "NAO";
		}
	}else{
		return "SIM";
	}

}

int main(int argc, char const *argv[]){

	int n, m;
	char vet[50];
	scanf("%[^\n]", vet);
	
	
	for (int i = 0; i < strlen(vet); ++i)
	{
		vet[i] = toupper(vet[i]);
	}
	

	printf("%s\n",palindrome(vet, 0, strlen(vet)-1));
	
	return 0;
}