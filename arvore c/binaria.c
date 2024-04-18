#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define TEST_NUMBER 100

typedef struct noh{
	struct noh * esquerda, * direita;
	int value;
} noh;

void em(noh * n){
	if(n->esquerda) em(n->esquerda);
	printf("%d ", n->value);
	if(n->direita) em(n->direita);
}

void pre(noh * n){
	printf("%d ", n->value);
	if(n->esquerda) pre(n->esquerda);
	if(n->direita) pre(n->direita);
}

void pos(noh * n){
	if(n->esquerda) pos(n->esquerda);
	if(n->direita) pos(n->direita);
	printf("%d ", n->value);
}

noh * new(int value){
	noh * n = malloc(sizeof(noh));
	n->value = value;
	n->esquerda = n->direita = NULL;
	return n;
}

void inserir(noh ** raiz, noh * filho){
	
	if(!*raiz) *raiz = filho;  
	
	else inserir( filho->value <= (*raiz)->value ? &(*raiz)->esquerda : &(*raiz)->direita , filho ); 
}

noh * search(noh * raiz, int valor){
	return !raiz ? NULL : raiz->value == valor ? raiz : search( valor > raiz->value ? raiz->direita : raiz->esquerda , valor );
}

void searchByPointer(noh * raiz, int valor, noh ** salvar){
	*salvar = search(raiz,valor);
}

void apagarArvore(noh *raiz){
    if (raiz != NULL){
        apagarArvore(raiz->esquerda);
        apagarArvore(raiz->direita);
        free(raiz);
        raiz = NULL;
    }
}

int main(){
	
	int test, c, success;
	test = c = success = 0;

	srand(time(NULL));

	noh * raiz = NULL;

	while(c++ < TEST_NUMBER)
		inserir(&raiz, new(rand() % 20));	

	printf("\n > EM ORDEM -> ");
	em(raiz);

	printf("\n\n > PRE ORDEM -> ");
	pre(raiz);

	printf("\n\n > POS ORDEM -> ");
	pos(raiz);

	puts("\n\n > PROCURA TESTE:");

	while(test++ < TEST_NUMBER)
		if(search(raiz, test) != 0){
	 		printf("  - %d\n", test);
	 		success++;
		}

	printf("\n <ENCONTRADO> = %d <NAO ENCONTRADO> = %d\n", success, TEST_NUMBER - success);

}