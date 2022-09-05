// Sintese
//   objetivo "Arvore Binaria de Busca"
//   autor "Edson F. da Fonseca & Turma de Estrutura de Dados 2021/1"
//   data "12/05/2021"
#include <stdio.h>
#include <stdlib.h>

//*** Declaracao de tipo de variavel **********************************************
struct tProduto {
	int codigo; // chave de busca
	char descricao[30];
	float valor;
};

struct tNo {
	struct tNo *esq;
	struct tProduto dado;
	struct tNo *dir;
	int prof;
};

#include "edsonArvore.h"

//*** Prototipos ******************************************************************
int menu(void);
void inicializar(struct tNo**);
void incluir(struct tNo**, struct tNo*);
void caminharEmOrdem(struct tNo*);
void caminharPreOrdem(struct tNo*);
void caminharPosOrdem(struct tNo*);
void desenhar(struct tNo*);
int excluir(struct tNo**, int);
struct tNo *buscar(struct tNo*, int);
void destruir(struct tNo**);
	
int main(void) {
	struct tNo *arvore; // descritor
	struct tNo *p, *q, *r, *s;
	int opcao, codigo, n = 0, codigo2, resp;
	
	inicializar(&arvore);
	do {
		opcao = menu();
		switch (opcao) {
			case 1:
				printf("\n\n\nInclusao\n");
				
				p = (struct tNo*) malloc(sizeof(struct tNo));
				/*printf("Digite o codigo...: ");
				scanf("%d", &(p->dado.codigo)); //scanf("%d", &((*p).dado.codigo));
				printf("Digite a descricao: ");
				fflush(stdin);
				gets(p->dado.descricao);
				printf("Digite o valor....: ");
				scanf("%f", &(p->dado.valor));				
				incluir(&arvore, p);*/
				
				
				p = (struct tNo*) malloc(sizeof(struct tNo));
				p->dado.codigo = 50;
				incluir(&arvore, p);
				p = (struct tNo*) malloc(sizeof(struct tNo));
				p->dado.codigo = 25;
				incluir(&arvore, p);
				p = (struct tNo*) malloc(sizeof(struct tNo));
				p->dado.codigo = 75;
				incluir(&arvore, p);
				p = (struct tNo*) malloc(sizeof(struct tNo));
				p->dado.codigo = 10;
				incluir(&arvore, p);
				p = (struct tNo*) malloc(sizeof(struct tNo));
				p->dado.codigo = 60;
				incluir(&arvore, p);
				p = (struct tNo*) malloc(sizeof(struct tNo));
				p->dado.codigo = 70;
				incluir(&arvore, p);
				/*p = (struct tNo*) malloc(sizeof(struct tNo));
				p->dado.codigo = 23;
				incluir(&arvore, p);
				p = (struct tNo*) malloc(sizeof(struct tNo));
				p->dado.codigo = 25;
				incluir(&arvore, p);*/
				break;
			case 2:
				printf("\n\n\nCaminhamento - Em-ordem\n");
				caminharEmOrdem(arvore);
				break;
			case 3:
				printf("\n\n\nCaminhamento - Pre-ordem\n");
				caminharPreOrdem(arvore);
				break;
			case 4:
				printf("\n\n\nCaminhamento - Pos-ordem\n");
				caminharPosOrdem(arvore);
				break;
			case 5:
				printf("\n\n\nBusca\n");
				printf("Digite o codigo...: ");
				scanf("%d", &codigo);
				p = buscar(arvore, codigo);
				if (p == NULL)
					printf("Codigo nao encontrado!");
				else {
					printf("Descricao: %s\n", p->dado.descricao);
					printf("Valor....: R$ %.2f", p->dado.valor);
				}
				break;
			case 6:
				printf("\n\n\nExcluir\n");
				printf("Digite o codigo...: ");
				scanf("%d", &codigo);
				if (!excluir(&arvore, codigo))
					printf("Codigo nao encontrado!");
				break;
			case 7:
				printf("\n\n\nDesenhar - Representacao de parenteses aninhados\n");
				desenhar(arvore);
				break;
			case 8:
				printf("\n\nAltura\n");
				printf("Digite o codigo...: ");
				scanf("%d", &codigo);
				p = buscar(arvore, codigo);
				if (p == NULL) {
					printf("Codigo nao encontrado!");
				} else {		
					printf("Altura do codigo %d: %d", codigo, altura(p));
				}
				break;
			case 9:
				printf("\n\nGrau\n");
				printf("Digite o codigo...: ");
				scanf("%d", &codigo);
				p = buscar(arvore, codigo);
				if (p == NULL) {
					printf("Codigo nao encontrado!");
				} else {		
					printf("Grau do codigo %d: %d", codigo, grau(p));
				}
				break;
			case 10: 
				printf("\n\nDados\n");
                printf("Raiz: %d\n", arvore->dado.codigo);
                printf("Digite o codigo que deseja saber os filhos: ");
                scanf("%d", &codigo);
                p = buscar(arvore, codigo);
                resp = folha(p);
                if (resp = 0) { 
					printf("Trata-se de um no folha.\n");
				} else {
                    printf("Filho esquerda: %d\n", p->esq->dado.codigo);
                    printf("Filho direita: %d\n", p->dir->dado.codigo);
                    /*if (p->esq == NULL) {
                        printf("Nao possui filho a esquerda.\n");
                    } 
                    if (p->dir == NULL) {
                        printf("Nao possui filho a direita.\n");
                    } else {
                        printf("Trata-se de um no folha.\n");
                    }*/
                }
                getch();
				break;
			case 11:
				printf("\n Profundidade\n");
				do {
					printf("Qual o 1o codigo a ser consultado?\n");
					scanf("%d", &codigo);
					r = buscar(arvore, codigo); //raiz
					if (r == NULL)
						printf("Codigo nao encontrado!\n");
				} while (r == NULL);
				
				do {
					printf("Qual o 2o codigo a ser consultado?\n");
					scanf("%d", &codigo2);
					s = buscar(arvore, codigo2); //codigo
					if (s == NULL)
						printf("Codigo nao encontrado!\n");
				} while (s == NULL);
								
				nivel(r, s, &n);
				printf("Profundidade: %d", n);
				break;
			case 12:
				printf("\n Nivel\n");
				printf("Qual o codigo a ser consultado? \n");
				scanf("%d", &codigo);
				
				r = buscar(arvore, codigo);
				nivel(arvore, r, &n);
				printf("Nivel: %d", n);
				getch();
		}
	} while (opcao != 0);
	destruir(&arvore);
	return 0;
}

// *** menu ***********************************************************************
int menu(void) {
	int opcao;
	printf("\n\n\n*** menu ***\n");
	printf("1. Incluir produto\n");
	printf("2. Caminhar - em-ordem\n");
	printf("3. Caminhar - pre-ordem\n");
	printf("4. Caminhar - pos-ordem\n");
	printf("5. Buscar produto\n");
	printf("6. Excluir produto\n");
	printf("7. Desenhar\n");
	printf("8. Altura\n");
	printf("9. Grau\n");
	printf("10. Dados\n");
	printf("11. Profundidade\n");
	printf("12. Nivel\n");
	printf("0. Sair\n\n");
	printf("Digite sua opcao: ");
	scanf("%d", &opcao);
	return opcao;
}

// *** Inicializar ****************************************************************
void inicializar(struct tNo **raiz) {
	(*raiz) = NULL;
}

// *** Caminhar Em-ordem **********************************************************
void caminharEmOrdem(struct tNo *raiz) {
	if (raiz == NULL)
		return;
	caminharEmOrdem(raiz->esq);
	printf("%d, ", raiz->dado.codigo);
	caminharEmOrdem(raiz->dir);
}

// *** Caminhar Pre-ordem **********************************************************
void caminharPreOrdem(struct tNo *raiz) {
	if (raiz == NULL)
		return;
	printf("%d, ", raiz->dado.codigo);
	caminharPreOrdem(raiz->esq);
	caminharPreOrdem(raiz->dir);
}

// *** Caminhar Pos-ordem **********************************************************
void caminharPosOrdem(struct tNo *raiz) {
	if (raiz == NULL)
		return;
	caminharPosOrdem(raiz->esq);
	caminharPosOrdem(raiz->dir);
	printf("%d, ", raiz->dado.codigo);
}

// *** Desenhar = representar usando parenteses aninhados **************************
void desenhar(struct tNo *raiz) {
	if (raiz == NULL){
		printf("()");
		return;	
	}
	printf("(%d", raiz->dado.codigo);
	desenhar(raiz->esq);
	desenhar(raiz->dir);
	printf(")");
}

// *** incluir ********************************************************************
void incluir(struct tNo **raiz, struct tNo *novo) {
	if ((*raiz) == NULL) {
		novo->esq = novo->dir = NULL;
		(*raiz) = novo;
	}
	else {
		if (novo->dado.codigo < (*raiz)->dado.codigo) // esquerda
			incluir(&((*raiz)->esq), novo);
		else // direita
			incluir(&((*raiz)->dir), novo);
	}
}

// *** Buscar *********************************************************************
struct tNo *buscar(struct tNo *raiz, int cod) {
	if ((raiz == NULL) || (raiz->dado.codigo == cod))
		return raiz;
	if (cod < raiz->dado.codigo)
		return buscar(raiz->esq, cod); // esquerda
	return buscar(raiz->dir, cod); // direita
}	

// *** Excluir ********************************************************************
int excluir(struct tNo **raiz, int cod) {
	struct tNo *p = (*raiz);
	if ((*raiz) == NULL)
		return 0;
	if ((*raiz)->dado.codigo == cod) { // achei
		if (((*raiz)->esq == NULL) && ((*raiz)->dir == NULL)) { // folha
			(*raiz) = NULL;
			free(p);
			return 1;
		}
		if ((*raiz)->esq == NULL) { // 1 filho direita
			(*raiz) = (*raiz)->dir;
			free(p);
			return 1;
		}
		if ((*raiz)->dir == NULL) { // 1 filho esquerda
			(*raiz) = (*raiz)->esq;
			free(p);
			return 1;
		}
		// 2 filhos
		p = maior((*raiz)->esq);
		(*raiz)->dado = p->dado;
		excluir(&((*raiz)->esq), p->dado.codigo);
		return 1;
	}
	if (cod < (*raiz)->dado.codigo)
		return excluir(&((*raiz)->esq), cod); // esquerda
	return excluir(&((*raiz)->dir), cod); // direita
}

// *** Destruir *******************************************************************
void destruir(struct tNo **raiz) {
	if ((*raiz) == NULL)
		return;
	destruir(&((*raiz)->esq));
	destruir(&((*raiz)->dir));
	free(*raiz);
}
