// Sintese
//   objetivo "Lista Simplesmente Encadeada"
//   autor "Nat?lia Carvalho Barros"
//   data "27/02/2021"
#include <stdio.h>
#include <stdlib.h>

// Declaracao de tipo de variavel
struct tProduto {
	int codigo;
	char descricao[30];
	float valor;
};

struct tNo {
	struct tProduto dado;
	struct tNo *prox;
};

// Prototipos das funcoes
int menu ();
void listar(struct tNo *lst);
void incluir (struct tNo **lst, struct tNo *novo);

int main(void) {
	struct tNo *lista=NULL, *p, *q; // vazia
	int opcao, opcao2, qtdProd = 0, codigo1, codigo2, flag = 0, flag1 = 0;
	char opcao1;
	
	do {
		opcao = menu ();
		switch (opcao) {
			case 1:
				printf("\n\n\n Inclusao\n"); // Incluir o n? com produto criado na lista
				p = malloc (sizeof(struct tNo)); // p passa a apontar para um novo elemento que vai entrar na lista
				printf("Digite o codigo...: ");
				scanf("%d", &(p->dado.codigo)); //scanf("%d", &((*p).dado.codigo));
				fflush(stdin);
				printf("Digite a descricao: ");
				gets(p->dado.descricao);
				printf("Digite o valor....: ");
				scanf("%f", &(p->dado.valor));
				fflush(stdin);
				
				// Criar o n? fora do m?dulo inclus?o e depois incluir na lista
				incluir(&lista, p);
				break;
			case 2:
				printf("\n\n\n Listagem\n");
				listar(lista);
				break;
			case 3:
				printf("\n\n\n Consulta\n");
				printf("Digite o codigo do produto: ");
				scanf("%d", &codigo1);
				fflush(stdin);
				p = lista;
				while (p != NULL) {
					if (codigo1 == p->dado.codigo) {
						printf("Produto %d\n", p->dado.codigo);
						printf("Descricao: %s\n", p->dado.descricao);
						printf("Valor: %.2f\n", p->dado.valor);
						flag = 1;
					} 
					p = p->prox;
				}
				if(flag == 0) {
					printf("Produto inexistente!\n");
				}
				break;
			case 4:
				printf("\n\n\n Alteracao\n");
				printf("Digite o codigo do produto que deseja alterar: ");
				scanf("%d", &codigo2);
				fflush(stdin);
				for (p = lista; p != NULL; p = p->prox) {
					if (codigo2 == p->dado.codigo) {
						flag1 = 1;
						printf("\nDados do produto\n Codigo: %d\n Descricao: %s\n Valor: %.2f", p->dado.codigo, p->dado.descricao, p->dado.valor);
						do {
							printf("\nConfirma? (S/N) ");
							scanf("%c", &opcao1); 
							fflush(stdin);
							if ((opcao1 != 'S') && (opcao1 != 'N')) {
								printf("Opcao invalida!");
							}
						} while ((opcao1 != 'S') && (opcao1 != 'N'));
						if (opcao1 == 'S') {
							printf("1. Descricao\n");
							printf("2. Valor\n");
							printf("Digite o nr do campo que deseja alterar: ");
							scanf("%d", &opcao2);
							fflush(stdin);
							switch (opcao2) {
								case 1:
									printf("Nova descricao: ");
									gets(p->dado.descricao);
									break;
								case 2: 
									printf("Novo valor: ");
									scanf("%f", &(p->dado.valor));
									fflush(stdin);
									break;
							}
						} 
					} 
				}
				if (flag1 == 0) {
					printf("Codigo inexistente.\n");
				}	
				break;
		}
	} while (opcao != 0);
	
	p = lista;
	while (p != NULL) {
		q = p; // coloca o q em algum lugar que ele morre
		p = p->prox; // salva o p
		free(q);
	}
		
	return 0;
}

int menu() {
	int opcao;
	
	printf("\n\n*** Menu ***\n");
	printf("1. Incluir produto\n");
	printf("2. Listar produtos\n");
	printf("3. Consultar produtos\n");
	printf("4. Alterar produtos\n");
	printf("0. Sair\n\n");
	printf("Digite sua opcao: ");
	scanf("%d", &opcao);
	
	return opcao;
}

void listar(struct tNo *lst) {	
	struct tNo *p = lst;
	printf("Codigo - Descricao - Valor\n");
	while (p != NULL) {
	printf("%d - %s - %.2f\n", p->dado.codigo, p->dado.descricao, p->dado.valor);
	p = p->prox;				
	}
}

void incluir (struct tNo **lst, struct tNo *novo) {
	// um * para indicar que ? ponteiro e o outro * para desreferenciar
	struct tNo *q;
	
	// p = elemento novo
	// lista = aponta para o primeiro elemento
	if ((*lst) == NULL) { // vazia
		novo->prox == NULL;
		(*lst) = novo;
	} else {
		if (novo->dado.codigo < (*lst)->dado.codigo) { // inicio
			novo->prox = (*lst); // prox aponta para onde lista est? apontando (onde anteriormente era o primeiro)
			(*lst) = novo;
			// ? preciso escrever as duas linhas acima nessa ordem
		} else {
			q = (*lst);
			while (q->prox != NULL) { // percorrer a lista at? o ultimo
				q = q->prox; // q passa a ser o ?ltimo
			}
			if (novo->dado.codigo > q->dado.codigo) { // fim
			// q e p sempre apontam para n?s
				q->prox = novo;
				novo->prox = NULL;
			} else {
				q = (*lst);
			while (q->prox->dado.codigo < novo->dado.codigo) {
				q = q->prox;
				// q->prox->dado.codigo : aponta para o proximo do q
			}
				novo->prox = q->prox;
				q->prox = novo;
			}
		}
	}	
}
