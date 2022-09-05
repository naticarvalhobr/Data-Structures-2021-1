#include <stdio.h>
#include <stdlib.h>

// FILA

struct tProduto {
	int codigo; 
	char descricao[30];
	float valor;
};

struct tNo {
	struct tProduto dado;
	struct tNo *prox;
};

struct tDescritor {
	struct tNo *ini;
	struct tNo *fim;
};

int menu();
void inicializar (struct tDescritor *fil);
void listar(struct tDescritor fil); 
void enqueue (struct tDescritor *fil, struct tNo *novo);
struct tNo *dequeue (struct tDescritor *fil);
// asterisco antes de dequeue porque retorna um ponteiro para um nó
void destruir (struct tDescritor *fil);

int main (void) {
	struct tDescritor fila; // descritor
	struct tNo *p, *q; 
	int opcao, codigo;
	
	inicializar(&fila);
	
	do {
		opcao = menu();
		switch (opcao) {
			case 1:
				printf("\n\n\n Enqueue\n");
				p = malloc(sizeof(struct tNo));
				printf("Digite o codigo...: ");
				scanf("%d", &(p->dado.codigo)); 
				printf("Digite a descricao: ");
				fflush(stdin);
				gets(p->dado.descricao);
				printf("Digite o valor....: ");
				scanf("%f", &(p->dado.valor));				
				
				enqueue(&fila, p);				
				break;
			case 2: 
				printf("\n\n\n Dequeue\n");
				p = dequeue (&fila);
				if (p == NULL) {
					printf("Fila vazia!");
				} 
				else {
					printf("Descricao: %s\n", p->dado.descricao);
					printf("Valor: R$ %.2f", p->dado.valor);
					free(p); // apaga apenas depois que usou ele
				}
				break;
			case 3: 
				printf("\n\n\n Listagem\n");
				listar(fila);
		}
	} while (opcao != 0);
	
	destruir (&fila);

	return 0;
}

int menu(void) {
	int opcao;
	printf("\n\n\n*** Menu ***\n");
	printf("1. Enqueue\n");
	printf("2. Dequeue\n");
	printf("3. Listar - ERRADO\n");
	printf("0. Sair\n\n");
	printf("Digite sua opcao: ");
	scanf("%d", &opcao);
	return opcao;
}

void inicializar (struct tDescritor *fil) { 
	(*fil).ini = (*fil).fim = NULL;	
}

// Listar não faz parte do comportamento da fila, mas estamos implementando como lista encadeada para ver se está funcionando
void listar(struct tDescritor fil) { 
	struct tNo *p = fil.ini;
	printf("Codigo - Descricao - Valor\n");
	while (p != NULL) {
		printf("%d - %s - %.2f\n", p->dado.codigo, p->dado.descricao, p->dado.valor);
		p = p->prox;				
	}
}

void enqueue (struct tDescritor *fil, struct tNo *novo) {
	struct tNo *q; 
	
	// fil é uma referência para o descritor
	
	if ((*fil).ini == NULL) { // vazio
	// se o início está apontando pra NULL, o fim também está
		(*fil).ini = (*fil).fim = novo; // atribuição em cascata
	}
	else { // não vazia
	// Tem sempre que entrar no fim
		(*fil).fim->prox = novo;
		(*fil).fim = novo;
	}
	novo->prox = NULL;
}

// pegar a ideia do consultar de fazer ele retornar um nó

struct tNo *dequeue (struct tDescritor *fil) {
	// se o retorno dele é um nó, é possível retornar null se a fila estiver vazia
	struct tNo *p = (*fil).ini;
	
	if ((*fil).ini != NULL) { // não vazia
	// poderia usar o *p na linha acima, mas fica mais legível colocando da forma que está
		(*fil).ini = (*fil).ini->prox;
		return p;
	}
}

void destruir (struct tDescritor *fil) {
	struct tNo *p = (*fil).ini, *q;
	
	while (p != NULL) {
		q = p; 
		p = p->prox; 	
		free(q);						
	}
	
	inicializar(fil); 
}
