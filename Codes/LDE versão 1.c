// Sintese
//   objetivo "Lista Simplesmente Encadeada"
//   autor "Edson F. da Fonseca & Turma de Estrutura de Dados 2021/1"
//   data "03/03/2021"
#include <stdio.h>
#include <stdlib.h>

//*** Declaracao de tipo de variavel **********************************************
struct tProduto {
	int codigo; // chave de ordenacao
	char descricao[30];
	float valor;
};

struct tNo {
	struct tProduto dado;
	struct tNo *prox;
};

//*** Prototipos ******************************************************************
int menu(void);
void listar(struct tNo *lst);
void incluir(struct tNo **lst, struct tNo *novo);

int main(void) {
	struct tNo *p, *q, *lista=NULL; // vazia
	int opcao;
	
	do {
		opcao = menu();
		switch (opcao) {
			case 1:
				printf("\n\n\n Inclusao\n");
				p = (struct tNo*) malloc(sizeof(struct tNo)); // p passa a apontar para um novo elemento que vai entrar na lista
				printf("Digite o codigo...: ");
				scanf("%d", &(p->dado.codigo)); //scanf("%d", &((*p).dado.codigo));
				printf("Digite a descricao: ");
				fflush(stdin);
				gets(p->dado.descricao);
				printf("Digite o valor....: ");
				scanf("%f", &(p->dado.valor));
										
				incluir(&lista, p);	// Incluir o nó com produto criado na lista			
				// p = elemento novo
				// lista = aponta para o primeiro elemento
				break;
			case 2:
				printf("\n\n\n Listagem\n");
				listar(lista); // Listar (mostrar na tela) todos os produtos
		}
	} while (opcao != 0);
	// Libera a memoria ocupada pelos nos da lista
	p = lista;
	while (p != NULL) {
		q = p; // coloca o q em algum lugar que ele morre
		p = p->prox; // salva o p		
		free(q);						
	}
	return 0;
}

// *** menu ***********************************************************************
int menu(void) {
	int opcao;
	printf("\n\n\n*** menu ***\n");
	printf("1. Incluir produto\n");
	printf("2. Listar produtos\n");
	printf("0. Sair\n\n");
	printf("Digite sua opcao: ");
	scanf("%d", &opcao);
	return opcao;
}

// *** listar *********************************************************************
void listar(struct tNo *lst) {
	struct tNo *p = lst;
	printf("Codigo - Descricao - Valor\n");
	while (p != NULL) {
		printf("%d - %s - %.2f\n", p->dado.codigo, p->dado.descricao, p->dado.valor);
		p = p->prox;				
	}
}

// *** incluir ********************************************************************
void incluir(struct tNo **lst, struct tNo *novo) {
	struct tNo *q;
	if ((*lst) == NULL) { // vazia
		novo->prox = NULL;
		(*lst) = novo;
	}
	else { // inicio, fim, meio
		if (novo->dado.codigo < (*lst)->dado.codigo) { // inicio
			novo->prox = (*lst); // prox aponta para onde lista está apontando (onde anteriormente era o primeiro)
			(*lst) = novo;
			// é preciso escrever as duas linhas acima nessa ordem
		}
		else { // fim, meio
			q = (*lst);
			while (q->prox != NULL) { // percorrer a lista até o ultimo
				q = q->prox; // coloca q no ultimo
			}
			if (novo->dado.codigo > q->dado.codigo) { // fim
				q->prox = novo;
				novo->prox = NULL;
				// q e p sempre apontam para nós
			}
			else { // meio
				q = (*lst);
				while (q->prox->dado.codigo < novo->dado.codigo) {// coloca q no ultimo
					q = q->prox;
				// q->prox->dado.codigo : aponta para o proximo do q
				}
				novo->prox = q->prox;
				q->prox = novo;
			}
		}	
	}					
}

