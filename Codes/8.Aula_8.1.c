#include <stdio.h>
#include <stdlib.h>

// PILHA

#include <stdio.h>
#include <stdlib.h>

struct tProduto {
	int codigo; 
	char descricao[30];
	float valor;
};

struct tNo {
	struct tProduto dado;
	struct tNo *prox;
};

// Não tem Descritor

int menu();
void inicializar (struct tNo **pil);
void listar(struct tNo *pil);
void push (struct tNo **pil, struct tNo *novo);
struct tNo *pop (struct tNo **pil);
// asterisco antes de pop porque retorna um ponteiro para um nó
void destruir (struct tNo **pil);

int main (void) {
	struct tNo *pilha; // continua funcionando no conceito de descritor
	struct tNo *p; 
	int opcao, codigo;
	
	inicializar(&pilha);
	
	do {
		opcao = menu();
		switch (opcao) {
			case 1:
				printf("\n\n\n Push\n");
				p = malloc(sizeof(struct tNo));
				printf("Digite o codigo...: ");
				scanf("%d", &(p->dado.codigo)); 
				printf("Digite a descricao: ");
				fflush(stdin);
				gets(p->dado.descricao);
				printf("Digite o valor....: ");
				scanf("%f", &(p->dado.valor));				
				
				push(&pilha, p);				
				break;
			case 2: 
				printf("\n\n\n Pop\n");
				p = pop(&pilha);
				if (p == NULL) {
					printf("Pilha vazia!");
				} 
				else {
					printf("Descricao: %s\n", p->dado.descricao);
					printf("Valor: R$ %.2f", p->dado.valor);
					free(p); // apaga apenas depois que usou ele
				}
				break;
			case 3: 
				printf("\n\n\n Listagem\n");
				listar(pilha);
		}
	} while (opcao != 0);
	
	destruir (&pilha);

	return 0;
}

int menu(void) {
	int opcao;
	printf("\n\n\n*** Menu ***\n");
	printf("1. Push\n");
	printf("2. Pop\n");
	printf("3. Listar - ERRADO\n");
	printf("0. Sair\n\n");
	printf("Digite sua opcao: ");
	scanf("%d", &opcao);
	return opcao;
}

void inicializar (struct tNo **pil) { 
	(*pil)= NULL;	
}

// Listar não faz parte do comportamento da pilha, mas estamos implementando como lista encadeada para ver se está funcionando
void listar(struct tNo *pil) { 
	struct tNo *p = pil;
	
	printf("Codigo - Descricao - Valor\n");
	while (p != NULL) {
		printf("%d - %s - %.2f\n", p->dado.codigo, p->dado.descricao, p->dado.valor);
		p = p->prox;				
	}
}

void push (struct tNo **pil, struct tNo *novo) {
	
	novo->prox = (*pil);
	(*pil) = novo;
	
	// O comportamento é o mesmo se a pilha estiver vazia
}

// pegar a ideia do consultar de fazer ele retornar um nó

struct tNo *pop (struct tNo **pil) { 
	struct tNo *p = (*pil);
	// Como o topo da pilha é do mesmo lado do início da fila, o comportamento é o mesmo.
	
	if ((*pil) != NULL) { // não vazia
		(*pil) = (*pil)->prox;
		return p;
	}
}

void destruir (struct tNo **pil) {
	struct tNo *p = (*pil), *q;
	
	while (p != NULL) {
		q = p; 
		p = p->prox; 	
		free(q);						
	}
	
	inicializar(pil); 
}
