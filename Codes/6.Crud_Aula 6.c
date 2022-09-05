#include <stdio.h>
#include <stdlib.h>

//*** Declaracao de tipo de variavel **********************************************
struct tProduto {
	int codigo; // chave de ordenação
	char descricao[30];
	float valor;
};

struct tNo {
	struct tNo *ant;
	struct tProduto dado;
	struct tNo *prox;
};

struct tDescritor {
	struct tNo *ini; // ponteiro para uma struct tNo  
	int qtd; 
	struct tNo *fim;
};

//*** Prototipos ******************************************************************
int menu();
void inicializar (struct tDescritor *lst);
void incluir(struct tDescritor *lst, struct tNo *novo);
void listar(struct tDescritor lst);
struct tNo *consultar (struct tDescritor lst, int cod);
void excluir (struct tDescritor *lst, struct tNo *vitima);
void destruir (struct tDescritor *lst);
// vitima é o ponteiro que aponta para o nó que quer excluir

int main(void) {
	struct tDescritor lista; // descritor	
	// Antes, o descritor era simplesmente um ponteiro que apontava para o primeiro nó da lista
	
	struct tNo *p, *q; 
	int opcao, codigo;
	
	inicializar(&lista);
	
	do {
		opcao = menu();
		switch (opcao) {
			case 1:
				printf("\n\n\n Inclusao\n");
				p = malloc(sizeof(struct tNo));
				printf("Digite o codigo...: ");
				scanf("%d", &(p->dado.codigo)); 
				printf("Digite a descricao: ");
				fflush(stdin);
				gets(p->dado.descricao);
				printf("Digite o valor....: ");
				scanf("%f", &(p->dado.valor));				
				
				incluir(&lista, p);	
				// Passa o descritor todo por referência			
				break;
			case 2:
				printf("\n\n\n Listagem\n");
				listar(lista);
				break;
			case 3:
				printf("\n\n\n Consulta\n");
				printf("Digite o codigo do produto: ");
				scanf("%d", &codigo);
				
				p = consultar(lista, codigo); 
				
				if (p == NULL) {
					printf("Codigo nao encontrado!");
				} else {
					printf("Descricao: %s\n", p->dado.descricao);
					printf("Valor: R$ %.2f", p->dado.valor);
				}
				break;
			case 4:
				printf("\n\n\n Alterar\n"); 
				printf("Digite o codigo do produto: ");
				scanf("%d", &codigo);
				
				p = consultar(lista, codigo); 
				
				if (p == NULL) {
					printf("Codigo nao encontrado!");
				} else {
					printf("Descricao: %s\n", p->dado.descricao);
					printf("Valor: R$ %.2f\n", p->dado.valor);
					
					
					printf("Digite a descricao: ");
					fflush(stdin);
					gets(p->dado.descricao); 
					printf("Digite o valor....: ");
					scanf("%f", &(p->dado.valor));
					break;
				}
			case 5:
				printf("\n\n\n Excluir\n"); 
				printf("Digite o codigo do produto: ");
				scanf("%d", &codigo);
				
				p = consultar(lista, codigo); 
				
				if (p == NULL) {
					printf("Codigo nao encontrado!");
				} else {
					printf("Descricao: %s\n", p->dado.descricao);
					printf("Valor: R$ %.2f\n", p->dado.valor);
					
					excluir(&lista, p);
					// lista deve ser passada por referência pois precisa alterá-la dentro da função
				}
		}
	} while (opcao != 0);
	
	destruir (&lista);

	return 0;
}

// *** menu ***********************************************************************
int menu(void) {
	int opcao;
	printf("\n\n\n*** Menu ***\n");
	printf("1. Incluir produto\n");
	printf("2. Listar produtos\n");
	printf("3. Consultar produtos\n");
	printf("4. Alterar produtos\n");
	printf("5. Excluir produtos\n");
	printf("0. Sair\n\n");
	printf("Digite sua opcao: ");
	scanf("%d", &opcao);
	return opcao;
}

void inicializar (struct tDescritor *lst) { 
	// Antes, o descritor era apenas um ponteiro com nome lista, passado por referência.
	// Agora, se trata de uma variável com nome lista, do tipo struct tDescritor.
	(*lst).ini = (*lst).fim = NULL;	
	(*lst).qtd = 0; 
}

void listar(struct tDescritor lst) {  
	// lst é uma cópia de lista por ter sido passado por valor
	struct tNo *p = lst.ini;
	printf("Codigo - Descricao - Valor\n");
	while (p != NULL) {
		printf("%d - %s - %.2f\n", p->dado.codigo, p->dado.descricao, p->dado.valor);
		p = p->prox;				
	}
}

void incluir(struct tDescritor *lst, struct tNo *novo) {
	struct tNo *q = (*lst).ini; // já nasce apontando para o mesmo lugar que a referência de lst.ini aponta
	
	if ((*lst).ini == NULL) { // Vazia
		novo->ant = novo->prox = NULL;
		(*lst).ini = (*lst).fim = novo;		
	} 
	else { 
		if (novo->dado.codigo < (*lst).ini->dado.codigo) { // Início	
			novo->ant = NULL;
			novo->prox = (*lst).ini;
			(*lst).ini->ant = novo;
			(*lst).ini = novo;
		}
		else {
			if (novo->dado.codigo > (*lst).fim->dado.codigo) { // Fim
				novo->prox = NULL;
				novo->ant = (*lst).fim; // aponta para o mesmo lugar que o fim do descritor está apontando
				(*lst).fim->prox = novo;
				(*lst).fim = novo;
			}
			else { // Meio
				while ((q->prox->dado.codigo < novo->dado.codigo)) { // coloca o ponteiro q no nó posterior à entrada			
				// O risco de chegar a NULL não existe, porque já sei que não é uma inclusão de fim	   	
					q = q->prox;				
				}
				novo->ant = q->ant;
				novo->prox = q;
				novo->ant->prox = novo; // também poderia partir do q: q->ant->prox
				novo->prox->ant = novo; // também poderia partir do q novamente: q->ant
			}
		}
	}
	(*lst).qtd++;
}						

struct tNo *consultar (struct tDescritor lst, int cod) { 
	struct tNo *q = lst.ini; // q aponta para o primeiro nó, onde lst.ini está apontando 
	
	// É preciso usar a pesquisa sequencial, a não ser que já tenha alguma informação prévia
	// de onde é mais provavel que o código a ser procurado esteja. Ex.: normalmente está mais
	// pro final.
	 
	while ((q != NULL) && (q->dado.codigo < cod)) { 
		q = q->prox;
	}
	
	if ((q != NULL) && (cod == q->dado.codigo)) { 
			// Testa se é diferente de NULL pois pode ser um valor que não está na lista por ser maior que o ultimo elemento da lista.
			return q;
	}
	
	return NULL; 
}

void destruir (struct tDescritor *lst) { // *lst é um parâmetro  passado por referência
	struct tNo *p = (*lst).ini, *q;		 // (*lst) - lugar para onde se refere (aponta)
	
	while (p != NULL) {
		q = p; 
		p = p->prox; 	
		free(q);						
	}
	
	inicializar(lst);
	// na chamada da main, é preciso colocar o & porque lista não é uma referência na função main.
	// aqui, lst já é um ponteiro; ele já se refere à lista.
}

void excluir (struct tDescritor *lst, struct tNo *vitima) {
	struct tNo *p = (*lst).ini;
	
	if (((*lst).ini == vitima) && ((*lst).fim == vitima)) { // Unico
		// A vítima é, ao mesmo tempo, o início e o fim
		(*lst).ini = (*lst).fim = NULL;		
	} 
	else { 
		if ((*lst).ini == vitima) { // Início	
			vitima->prox->ant = NULL;
			(*lst).ini = vitima->prox;
		}
		else {
			if ((*lst).fim == vitima) { // Fim
				vitima->ant->prox = NULL;
				(*lst).fim = vitima->ant;
			}
			else { // Meio
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
}
