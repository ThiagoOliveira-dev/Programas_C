#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define vagasMax 1024
#define vagasMoto 204
#define vagasEspeiais 204
#define vagasVip 102
#define vagasCarro 512
#define custoPorMin 0.05

typedef struct No TNo;
struct No{
	int modificou;
	int chave;
	int fb;
	int placa;
	char classe;
	int horaEntrada;
	int minEntrada;
	int horaSaida;
	int minSaida;
	float valor;
	TNo *esq;
	TNo *dir;
};

	
TNo *criarRaiz(){
	TNo *raiz = malloc(sizeof(TNo));
	raiz = NULL;
	
	return raiz;
}

int aleatorio(int i, int f){

	//srand(time(NULL));
	return i + rand() % (f - i) + 1;
}
int horarioSaida(int i , int f){
	if(i != f){
		return i + rand() % (f - i) + 1;
	}else{
		return i;
	}
}

int tempoTotal(int hora, int min){
	int minHora;
	minHora = hora * 60;
	return minHora + min;
}

TNo *criaNovoNo(){
	char vetorAux[] = {' ','c','m','e','v'};
	int i = aleatorio(0,4);
	
	TNo *novo = malloc(sizeof(TNo));
	novo->placa = aleatorio(1000,3000);
	novo->horaEntrada = aleatorio(8,22);
	novo->minEntrada = aleatorio(1,59);
	novo->horaSaida = horarioSaida(novo->horaEntrada, 22);
	novo->minSaida = horarioSaida(novo->minEntrada, 59);
	novo->classe = vetorAux[i];
	//a chave é o tempo do horario de saida em minutos.
	novo->chave = tempoTotal(novo->horaSaida, novo->minSaida);
	novo->modificou = 0;
	novo->valor = 0.0;
	novo->fb = 0;


	novo->esq = NULL;
	novo->dir = NULL;

	return novo;
}
TNo *criaNovoNoVaga(int chave, int classe){

	TNo *novo = malloc(sizeof(TNo));
	novo->chave = chave;
	novo->modificou = 0;
	novo->placa = 0;
	novo->horaEntrada = 0;
	novo->minEntrada = 0;
	novo->horaSaida = 0;
	novo->minSaida = 0;
	novo->classe = classe;
	novo->fb = 0;
	novo->valor = 0;


	novo->esq = NULL;
	novo->dir = NULL;

	return novo;
}
int altura (TNo *r) {
   if (r == NULL) 
      return -1; // altura da árvore vazia
   else {
      int he = altura (r->esq);
      int hd = altura (r->dir);
      if (he < hd) return hd + 1 ;
      else return he + 1 ;
   }
}

TNo *atualizaFB(TNo *r){
	int he,hd;
	he = altura(r->esq);
	hd = altura(r->dir);
	r->fb = (he - hd);

	return r;
}

TNo *balanceia(TNo *raiz){
	TNo *filhoEsq = raiz->esq;
	TNo *filhoDir = raiz->dir;
	TNo *ptrPai;
	TNo *ptrFilho; 
	TNo *ptrFilhoDir;
	TNo *ptrFilhoEsq;


	if((raiz->fb < 0) && (filhoDir->fb > 0)){
		//rotaçao dupla a esquerda
		ptrPai = raiz;
		ptrFilho = raiz->dir;
		ptrFilhoEsq = ptrFilho->esq;

		ptrFilho->esq = ptrFilhoEsq->dir;
		ptrFilhoEsq->dir = ptrFilho;
		ptrPai->dir = ptrFilhoEsq->esq;
		ptrFilhoEsq->esq = ptrPai;
		ptrPai = ptrFilhoEsq;
		raiz = ptrFilhoEsq;


	}else if((raiz->fb > 0) && (filhoEsq->fb > 0)){
		//rotaçao simples a direita
		ptrPai = raiz;
		ptrFilho = raiz->esq;

		ptrPai->esq = ptrFilho->dir;
		ptrFilho->dir = ptrPai;
		ptrPai = ptrFilho;
		raiz = ptrFilho;

	}else if((raiz->fb > 0) && (filhoEsq->fb < 0)){
		//rotaçao dupla a direita;
		ptrPai = raiz;
		ptrFilho = raiz->esq;
		ptrFilhoDir = ptrFilho->dir;

		ptrFilho->dir = ptrFilhoDir->esq;
		ptrFilhoDir->esq = ptrFilho;
		ptrPai->esq = ptrFilhoDir->dir;
		ptrFilhoDir->dir = ptrPai;
		ptrPai = ptrFilhoDir;
		raiz = ptrFilhoDir;

	}else if((raiz->fb < 0) && (filhoDir->fb < 0)){
		//rotaçao simples a esquerda
		ptrPai = raiz;
		ptrFilho = raiz->dir;

		ptrPai->dir = ptrFilho->esq;
		ptrFilho->esq = ptrPai;
		ptrPai = ptrFilho;
		raiz = ptrFilho;


	}
	raiz = atualizaFB(raiz);
	return raiz;
}

float calculaValor(int horaEntrada, int horaSaida, int minEntrada, int minSaida){
	int totalEntrada = tempoTotal(horaEntrada, minEntrada);
	int totalSaida = tempoTotal(horaSaida, minSaida);
	return (totalSaida - totalEntrada) * custoPorMin;
}

TNo *inserir(TNo *raiz, TNo *novo){

	if(raiz == NULL){
		novo->valor = calculaValor(novo->horaEntrada, novo->horaSaida, novo->minEntrada, novo->minSaida);
		return novo;
	}else{
		if(novo->chave < raiz->chave){
			raiz->esq = inserir(raiz->esq, novo);
		}else if(novo->chave > raiz->chave){
			raiz->dir = inserir(raiz->dir, novo);
		}else{
			return raiz;
		}

		raiz = atualizaFB(raiz); 
		if( abs(raiz->fb) > 1 ){
			raiz = balanceia(raiz);	
		}
		return raiz;
	}

}

TNo *removerRaiz(TNo *raiz){
	TNo *ant;
	TNo *atual;

	if(raiz->esq == NULL){
		atual = raiz->dir;
		free(raiz);
		return atual;
	}

	ant = raiz;
	atual = raiz->esq;
	while(atual->dir != NULL){
		ant = atual;
		atual = atual->dir;

	}

	if(ant != raiz){
		ant->dir = atual->esq;
		atual->esq = raiz->esq;

	}
	atual->dir = raiz->dir;
	free(raiz);
	return atual;
}

TNo *removerNo(TNo *raiz, int chave){
	TNo *atual = raiz;
	TNo *ant = NULL;
	while(atual != NULL){
		if(atual->chave == chave){
			if(atual == raiz){
				raiz = removerRaiz(atual);
			}else{
				if(ant->dir == atual){
					ant->dir = removerRaiz(atual);
				}else{
					ant->esq = removerRaiz(atual);
				}
			}

		}
		ant = atual;
		if( chave < atual->chave){
			atual = atual->esq;
		}else{
			atual = atual->dir;
		}
	}
	raiz = atualizaFB(raiz); 
	if( abs(raiz->fb) > 1 ){
		raiz = balanceia(raiz);
	}
	return raiz;

}

void imprimir(TNo *raiz){
	if(raiz != NULL){
		
		imprimir(raiz->esq);
		printf("\n\nclasse: %c\nhorario de entrada: %d:%d \nhorariode saida: %d:%d  \nplaca: %d\nchave:%d\nvalorPago: %.2f\n",raiz->classe, raiz->horaEntrada, raiz->minEntrada,raiz->horaSaida,raiz->minSaida, raiz->placa,raiz->chave, raiz->valor);
		imprimir(raiz->dir);
		
			
	}

}
void imprimirVagas(TNo *raiz){
	if(raiz != NULL){
		
		imprimirVagas(raiz->esq);
		printf("\nCarro Chave: %d\nClasse: %c\n",raiz->chave, raiz->classe );
		imprimirVagas(raiz->dir);
		
	}

}



TNo *buscaNo(TNo *raiz,int chave, int classe){
		// a chave é o horario de saida em minutos.
		if(raiz != NULL){
			//retorna o caso base da recursão caso o tempo do noCliente seja menor ou igual que o tempo do novoNo(chave) e seja de 
			//classes iguais
			if((raiz->chave <= chave) && (raiz->classe == classe)){
				return raiz;
			}
			//procura à esquerda na arvore Cliente caso o tempo do novoNO(chave) seja menor que o noCliente.
			if(chave < raiz->chave){
				return buscaNo(raiz->esq, chave, classe);
			//procura à direita na arvore Cliente caso o tempo do novoNO(chave) seja maior que o noCliente.
			}else if(chave > raiz->chave){
				return buscaNo(raiz->dir, chave, classe);
			//caso o tempo do noCliente seja igual ao tempo do novoNo(chave) mas de classes diferentes.
			}else{
				TNo *filhoEsq = raiz->esq;
				TNo *filhoDir = raiz->dir;
				if(filhoEsq != NULL){
					if(chave <= filhoEsq->chave){
						return buscaNo(raiz->esq, chave, classe);
					}
				}
				if(filhoDir != NULL){
					if(chave >= filhoDir->chave){
						return buscaNo(raiz->dir, chave, classe);
					}
				}
				return buscaNo(raiz->esq, chave, classe);
				
				
			}
		}else{
			return raiz;
		}
}

TNo *verificaCarroDeSAida(TNo *cliente, TNo *novo){
	TNo *noBuscado = buscaNo(cliente, novo->chave, novo->classe);
	return noBuscado;

}
void contarVagas(TNo *vagas, char classe, int *cont){
	if(vagas != NULL){
		contarVagas(vagas->esq, classe, cont);
		contarVagas(vagas->dir, classe, cont);
		//printf("%c\nbuscado: %c\n iteracao: %d\n\n",vagas->classe,classe, *cont );
		if(vagas->classe == classe){
		*cont = *cont + 1;
		}
	}
}

TNo *verificaVaga(TNo *vagas, TNo *novo){
	int contar_Vagas = 0;
	

	if(vagas != NULL){
		
		contarVagas(vagas, novo->classe, &contar_Vagas);

		if( novo->classe == 'c' ){
			if(contar_Vagas < vagasCarro){
				return novo;
			}
		}
		if(novo->classe == 'm'){
			if(contar_Vagas < vagasMoto){
				return novo;
			}
		}
		if(novo->classe == 'v'){
			if(contar_Vagas < vagasVip){
				return novo;
			}
		}
		if(novo->classe == 'e'){
			if(contar_Vagas < vagasEspeiais){
				return novo;
			}
		}else{
			return NULL;
		}
	}else{
		return vagas;
	}


}

int contaNos(TNo *raiz) { 
    if (raiz == NULL){
    	return 0;
    }else {          
        int conte = contaNos (raiz->esq);         
        int contd = contaNos (raiz->dir); 
        return conte + contd + 1;   
    }
} 


int calculaTempo(int horaEntrada, int horaSaida, int minEntrada, int minSaida){
	int totalEntrada = tempoTotal(horaEntrada, minEntrada);
	int totalSaida = tempoTotal(horaSaida, minSaida);
	return (totalSaida - totalEntrada);
}
void acumuladorTempo(TNo *cliente, int *tempoTotal){
	if(cliente != NULL){
		acumuladorTempo(cliente->esq, tempoTotal);
		acumuladorTempo(cliente->dir, tempoTotal);
		*tempoTotal = *tempoTotal + calculaTempo(cliente->horaEntrada, cliente->horaSaida, cliente->minEntrada, cliente->minSaida);
		
		//printf("%c\nbuscado: %c\n iteracao: %d\n\n",vagas->classe,classe, *cont );

	}
}

int main(int argc, char const *argv[]){
	int tempoMinOcupacaoMax = 100;
	int tempoMaxOcupacaoMax = 0;
	int contOcupacaoMax = 0;
	int maior = 0;
	int auxCarroDeSaida;
	int acumuladorVagas = 0;
	int contadorVagas = 0;
	int acumulador_tempo = 0;
	int contTempo = 0;
	int chave;
	int i;

	TNo *verifica_Vaga;
	TNo *carroDeSaida;
	TNo *cliente = criarRaiz();
	TNo *aux = criarRaiz();
	TNo *vagas = criarRaiz();

	srand(time(NULL));
	TNo *novo = criaNovoNo();
	TNo *novoVaga = criaNovoNoVaga(novo->chave,novo->classe);
	if(cliente == NULL){
		cliente = inserir(cliente, novo);
		vagas = inserir(vagas, novoVaga);
	}
	acumuladorVagas = acumuladorVagas + contaNos(vagas);
	contadorVagas++;
	

	for(i = 0; i < vagasMax; i++){

		
		//cria novo nó com os valores aleatorios.
		TNo *novo = criaNovoNo();
		TNo *novoVaga = criaNovoNoVaga(novo->chave,novo->classe);

		// A funçao verificaCarroDeSAida verifica se na arvore cliente existe um carro com tempo de saída menor que 
		//o tempo de entrado do novo nó e da mesma classe, se existir retorna o no buscado(carroDeSaida).
		//a funçao não altera a quantidade de vagas, pois na condicional adicionamos um novo elemento no lugar do no buscado.
		carroDeSaida = verificaCarroDeSAida(cliente, novo);
		if(carroDeSaida != NULL){// fazemos a atualização das arvores cliente e vagas.
			acumulador_tempo = acumulador_tempo + calculaTempo(carroDeSaida->horaEntrada, carroDeSaida->horaSaida, carroDeSaida->minEntrada, carroDeSaida->minSaida);
			contTempo++;
			auxCarroDeSaida = carroDeSaida->chave;
			cliente = removerNo(cliente, carroDeSaida->chave);
			vagas = removerNo(vagas, auxCarroDeSaida);

			cliente = inserir(cliente, novo);
			vagas = inserir(vagas, novoVaga);
		}else{
			//faz a verificaçao das vagas de acordo com a classe do carro caso nao entre na funçao verificaCarroDeSAida.
			//se houver vagas disponiveis de acordo com as regras retorna novo senao retorna NULL.
			verifica_Vaga =  verificaVaga(vagas, novo);
			//ocupa uma nova vaga em cliente e atualiza vagas.
			if(verifica_Vaga != NULL){
				cliente = inserir(cliente, novo);
				vagas = inserir(vagas, novoVaga);
				acumuladorVagas = acumuladorVagas + contaNos(vagas);
				contadorVagas++;
				contOcupacaoMax++;
				//caso estaja dentro do limite da ocupaçao maxima
				if(contOcupacaoMax > maior){
					if(novo->horaEntrada < tempoMinOcupacaoMax){
						tempoMinOcupacaoMax = novo->horaEntrada;
					}
					if(novo->horaSaida > tempoMaxOcupacaoMax){
						tempoMaxOcupacaoMax = novo->horaSaida;
					}

				}

				if(contOcupacaoMax > maior){
					maior = contOcupacaoMax;
				}

			}

		}
		
	}
	

	printf("Media de vagas ocupadas:\n");
	printf("%d vagas\n", (acumuladorVagas/contadorVagas) );
	printf("\n");
	acumuladorTempo(cliente, &acumulador_tempo);
	contTempo = contTempo + contaNos(cliente);
	printf("Tempo medio de vagas ocupadas: %d min\n", acumulador_tempo/contTempo);
	printf("\n");
	printf("Tempo de maior vagas ocupadas:\n");
	printf("De %d:00 ate %d:00\n",tempoMinOcupacaoMax, tempoMaxOcupacaoMax );
	printf("Maior quantidade de carros: %d\n", contOcupacaoMax);

	return 0;
}