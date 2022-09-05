// Sintese
//   objetivo "Lista Binária de Busca"
//   autor "Edson F. da Fonseca & Turma de Estrutura de Dados 2021/1"
//   data "05/05/2021"
#include <stdio.h>
#include <stdlib.h>

//*** Declaracao de tipo de variavel **********************************************
struct tProduto {
	int codigo; // chave de ordenacao
	char descricao[30];
	float valor;
};

struct tNo {
	struct tNo *esq;
	struct tProduto dado;
	struct tNo *dir;
};

//*** Prototipos ******************************************************************
int menu();
void inicializar (struct tNo **raiz);
void incluir(struct tNo **raiz, struct tNo *novo);
//void listar(struct tDescritor lst);
struct tNo *buscar (struct tNo *raiz, int cod);
// void excluir 
void destruir (struct tNo **raiz);
	
int main(void) {
	struct tNo *arvore; // descritor
	struct tNo *p, *q;
	int opcao, codigo;
	
	inicializar(&arvore);
	do {
		opcao = menu();
		switch (opcao) {
			case 1:
				printf("\n\n\nInclusao\n");
				p = (struct tNo*) malloc(sizeof(struct tNo));
				printf("Digite o codigo...: ");
				scanf("%d", &(p->dado.codigo)); //scanf("%d", &((*p).dado.codigo));
				printf("Digite a descricao: ");
				fflush(stdin);
				gets(p->dado.descricao);
				printf("Digite o valor....: ");
				scanf("%f", &(p->dado.valor));				
				incluir(&arvore, p);
				break;
			case 2:
				printf("\n\n\nListagem\n");
				//listar(lista);
				break;
			case 3:
				printf("\n\n\nBuscar\n");
				printf("Digite o codigo...: ");
				scanf("%d", &codigo);
				p = buscar(arvore, codigo);
				if (p == NULL)
					printf("\nCodigo nao encontrado!");
				else {
					printf("\nDescricao: %s\n", p->dado.descricao);
					printf("Valor....: R$ %.2f", p->dado.valor);
				}
				break;
			case 4:
				printf("\n\n\nAlterar\n");
				/*printf("Digite o codigo...: ");
				scanf("%d", &codigo);
				p = consultar(lista, codigo);
				if (p == NULL)
					printf("Codigo nao encontrado!");
				else {
					printf("Descricao: %s\n", p->dado.descricao);
					printf("Valor....: R$ %.2f\n", p->dado.valor);	
					printf("Digite a descricao: ");
					fflush(stdin);
					gets(p->dado.descricao);
					printf("Digite o valor....: ");
					scanf("%f", &(p->dado.valor));				
				}*/
				break;
			case 5:
				printf("\n\n\nExcluir\n");
				/*printf("Digite o codigo...: ");
				scanf("%d", &codigo);
				p = consultar(lista, codigo);
				if (p == NULL)
					printf("Codigo nao encontrado!");
				else {
					printf("Descricao: %s\n", p->dado.descricao);
					printf("Valor....: R$ %.2f\n", p->dado.valor);	
					excluir(&lista, p);	
					// lista deve ser passada por referência pois precisa alterá-la dentro da função			
				}*/
		}
	} while (opcao != 0);
	//destruir(&lista);
	return 0;
}

// *** menu ***********************************************************************
int menu(void) {
	int opcao;
	printf("\n\n\n*** menu ***\n");
	printf("1. Incluir produto\n");
	printf("2. Listar produtos\n");
	printf("3. Consultar produto\n");
	printf("4. Alterar produto\n");
	printf("5. Excluir produto\n");
	printf("0. Sair\n\n");
	printf("Digite sua opcao: ");
	scanf("%d", &opcao);
	return opcao;
}

// *** Inicializar ****************************************************************
void inicializar(struct tNo **raiz) { // ponteiro sendo passado por referência
	(*raiz) = NULL;
}

// *** listar *********************************************************************
/*void listar(struct tDescritor lst) {
	// lst é uma cópia de lista por ter sido passado por valor
	struct tNo *p = lst.ini;
	printf("Codigo - Descricao - Valor\n");
	while (p != NULL) {
		printf("%d - %s - %.2f\n", p->dado.codigo, p->dado.descricao, p->dado.valor);
		p = p->prox;				
	}
}*/

// *** incluir ********************************************************************
void incluir(struct tNo **raiz, struct tNo *novo) {
	// novo é uma cópia do p (dia 05/05 11h03)
	
	if ((*raiz) == NULL) {
		printf("\nBuscar - No: null");
	} 
	else {
		printf("\nBuscar - No: %d", (*raiz)->dado.codigo);	
	}
	
	
	if ((*raiz) == NULL) {
		novo->esq = novo->dir = NULL; // todo nó quando é incluído é uma folha (sem filhos). Depois, pode deixar de ser uma folha
		(*raiz) = novo;
	} else { // procura uma árvore vazia
		if (novo->dado.codigo < (*raiz)->dado.codigo) { // esquerda
			incluir(&((*raiz)->esq), novo); // & pois passa por referência
		} else { // direita
			incluir(&((*raiz)->dir), novo);
			// Ex.: a primeira instância chama o incluir, gerando a segunda instância
		}
	}
}

// *** Buscar ******************************************************************
struct tNo *buscar(struct tNo *raiz, int cod) {
	
	if (raiz == NULL) {
		printf("\nBuscar - No: null");
	} 
	else {
		printf("\nBuscar - No: %d", raiz->dado.codigo);	
	}
	
	
	if ((raiz == NULL) || (raiz->dado.codigo)) { // se chegar em NULL, o nó que está procurando não existe
		return raiz; // se encontrou o que procurava, raiz aponta para ele. Então, retorna ele.
	} 
	if (cod < raiz->dado.codigo) { // esquerda
		return buscar(raiz->esq, cod); 
	} 
	// direita
	return buscar(raiz->dir, cod);
}

// *** Excluir ********************************************************************
/*
void excluir(struct tDescritor *lst, struct tNo *vitima) {
	if (((*lst).ini == vitima) && ((*lst).fim == vitima)) // unico
		// A vítima é, ao mesmo tempo, o início e o fim
		(*lst).ini = (*lst).fim = NULL;
	else { // inicio, fim, meio
		if ((*lst).ini == vitima) { // inicio
			vitima->prox->ant = NULL;
			(*lst).ini = vitima->prox;
		}
		else { // fim, meio
			if ((*lst).fim == vitima) { // fim
				vitima->ant->prox = NULL;
				(*lst).fim = vitima->ant;
			}
			else { // meio
				// Não precisa de um ponteiro auxiliar pois, por ser lista duplamente encadeada
				// já sabe qual é o anterior e o próximo dele.
				vitima->prox->ant = vitima->ant;
				// O ponteiro ant do próximo nó depois da vítima passa a apontar para o nó anterior da vítima.
				vitima->ant->prox = vitima->prox;
				// O ponteiro prox do nó anterior à vítima passa a apontar para o próximo nó depois da vítima.
			}
		}
	}
	(*lst).qtd--;
	free(vitima);
}*/

// *** Destruir *******************************************************************
/*void destruir(struct tNo **raiz) { // *lst - parametro por referencia
	struct tNo *p=(*lst).ini, *q;       // (*lst) - lugar para onde se refere (aponta)
	while (p != NULL) {
		q = p;
		p = p->prox;		
		free(q);						
	}
	inicializar(raiz);
}*/
