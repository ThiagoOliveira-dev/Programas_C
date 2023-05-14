
typedef struct Novo TNovo;
typedef struct Lista TLista;


TLista *criarLse();
TNovo *criarNovo(int n);
void inserirInicio(TLista *lista,TNovo *novo);
void inserirFim(TLista *lista,TNovo *novo);
void removerInicio(TLista *lista);
void removerfim(TLista *lista);
void removerPos(TLista *lista,int pos);
void imprimir(TLista *lista);
