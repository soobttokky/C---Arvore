#include <stdlib.h>
#include <stdio.h>
#define tamanhoDoEspaco 10 

typedef struct ITEM
{
	int valor;
}tipoItem;

typedef struct NOH
{
    tipoItem item;
    struct NOH *esquerda;
    struct NOH *direita;
}tipoNoh;

int alturaArvore(tipoNoh *raiz){

    int alturaDireita = 0;
    int alturaEsquerda = 0;

    if (raiz == NULL){
        return -1;
    }

    alturaEsquerda = alturaArvore(raiz-> esquerda);
    alturaDireita = alturaArvore(raiz->direita);

    if (alturaEsquerda > alturaDireita){
        return alturaEsquerda+1;
    }else{
        return alturaDireita+1;
    }
}

int contarNos(tipoNoh *raiz){
    if (raiz == NULL){
        return 0;
    }else{
        return contarNos(raiz->esquerda)+ contarNos(raiz->direita) + 1;
    }
}

tipoNoh *inicializar(){
    return NULL;
}
tipoItem criarItem(int valor){
    tipoItem item;
    item.valor = valor;
    return item;
}
tipoNoh *alocar(){
    tipoNoh *novoNoh = (tipoNoh*) malloc(sizeof(tipoNoh));
    if (novoNoh != NULL){
        return novoNoh;
    }else{
        printf("Erro ao criar novo nó\n");
        exit(1);
        }
}
tipoNoh *inserir(tipoNoh *raiz, tipoItem item){
    if(raiz == NULL){
        tipoNoh *novoNoh = alocar();
        novoNoh->item = item;
        novoNoh->esquerda = NULL;
        novoNoh->direita = NULL;
        return novoNoh;
    }else{
        if (item.valor > raiz->item.valor){
            raiz->direita = inserir(raiz->direita, item);
        }else if(item.valor < raiz->item.valor){
            raiz-> esquerda = inserir(raiz->esquerda, item);
        }
    }
    return raiz;
}

void imprimir(tipoNoh *raiz, int espaco){
    if(raiz == NULL){
        return;
    }else{
        espaco += tamanhoDoEspaco;

        imprimir(raiz->direita, espaco);

        printf("\n");
        for (int i = tamanhoDoEspaco; i < espaco; i++){
            printf(" ");
        }
        printf("%d\n", raiz->item.valor);

        imprimir(raiz->esquerda, espaco);
    }
}

void apagarArvore(tipoNoh *raiz){
    if (raiz != NULL){
        apagarArvore(raiz->esquerda);
        apagarArvore(raiz->direita);
        free(raiz);
        raiz = NULL;
    }
}

tipoNoh *pesquisar(tipoNoh *raiz, int valor){
    if (raiz != NULL){
        if(raiz->item.valor == valor){
            return raiz;
        }else{
            if (valor > raiz->item.valor){
                return pesquisar(raiz->direita, valor);
            }else{
                return pesquisar(raiz->esquerda,valor);
            }
        }
    }
    return NULL;
}

tipoNoh *minimo(tipoNoh *raiz){
    if (raiz != NULL){
        tipoNoh *nohAuxiliar = raiz;
        while(nohAuxiliar->esquerda != NULL){
            nohAuxiliar = nohAuxiliar->esquerda;
        }
        return nohAuxiliar;
    }
    return NULL;
}

tipoNoh *remover(tipoNoh *raiz, int valor){
    if(raiz != NULL){
        if (valor > raiz->item.valor){
            raiz->direita = remover(raiz->direita,valor);
        }else if(valor < raiz-> item.valor){
            raiz->esquerda = remover(raiz->esquerda, valor);
        }else{
            if(raiz->esquerda == NULL && raiz->direita == NULL){
                free(raiz);
                raiz = NULL;
                return NULL;
            }else if (raiz->esquerda == NULL && raiz->direita != NULL){
                tipoNoh *nohAuxiliar = raiz->direita;
                free(raiz);
                raiz = NULL;
                return nohAuxiliar;
            }else{
                tipoNoh *nohAuxiliar = minimo(raiz->direita);
                tipoItem itemAuxiliar = nohAuxiliar->item;
                raiz = remover(raiz, itemAuxiliar.valor);
                raiz->item = itemAuxiliar;
            }
        }
        return raiz;
    }else{
        return NULL;
    }
}

int main(){
    tipoNoh *raiz = inicializar();
    int opcao=-1;
    int valor=0;

    while(opcao!=0){
        printf("\n---Arvore atual---\n");
		imprimir(raiz, tamanhoDoEspaco);

		valor=0;
		printf("\n---------------MENU---------------\n");
		printf("1: Inserir \n");
		printf("2: Remover \n");
		printf("3: Pesquisar \n");
		printf("0: SAIR \n");
		scanf("%d", &opcao);

		switch(opcao){

			case 1:
			printf("\n------INSERINDO------\n");
			printf("Digite um valor\n");
			scanf("%d",&valor);
			raiz = inserir(raiz, criarItem(valor));
			break;

			case 2:
			printf("\n------REMOVENDO------\n");
			printf("Digite um valor\n");
			scanf("%d",&valor);
			raiz = remover(raiz, valor);
			break;

			case 3:
			printf("\n------PESQUISANDO------\n");
			printf("Digite um valor\n");
			scanf("%d",&valor);

			tipoNoh *nohAuxiliar = pesquisar(raiz, valor);
			if (nohAuxiliar == NULL)
			{
				printf("\nElemento nao encontrado!\n");
			}else {
				printf("\nElemento encontrado com sucesso! \n");
			}
			break;

			case 0:
			printf("\nTchau! Ate a proxima\n");
			break;

			default:
			printf("\nOpcao inválida! \n");
			break;
		}


	}
		apagarArvore(raiz);

	return 0;
}