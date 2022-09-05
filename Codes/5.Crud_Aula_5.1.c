#include <stdio.h>
#include <stdlib.h>

//*** Declaracao de tipo de variavel **********************************************
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
	struct tNo *ini; // ponteiro para uma struct tNo  
	int qtd; 
	struct tNo *fim;
};

//*** Prototipos ******************************************************************
int menu();
void inicializar (struct tNo **lst);
void listar(struct tNo *lst);
void incluir(struct tNo **lst, struct tNo *novo);
struct tNo *consultar (struct tNo *lst, int cod);
void destruir (struct tNo **lst);
void excluir (struct tNo **lst, struct tNo *vitima);
// vitima � o ponteiro que aponta para o n� que quer excluir

int main(void) {
	struct tDescritor lista; // descritor	
	// Antes, o descritor era simplesmente um ponteiro que apontava para o primeiro n� da lista
	
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
					// lista deve ser passada por refer�ncia pois precisa alter�-la dentro da fun��o
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

void inicializar (struct tNo **lst) { 
	(*lst) = NULL;	
}

void listar(struct tNo *lst) { 
	struct tNo *p = lst;
	printf("Codigo - Descricao - Valor\n");
	while (p != NULL) {
		printf("%d - %s - %.2f\n", p->dado.codigo, p->dado.descricao, p->dado.valor);
		p = p->prox;				
	}
}

void incluir(struct tNo **lst, struct tNo *novo) {
	struct tNo *q;
	
	if (((*lst) == NULL) || (novo->dado.codigo < (*lst)->dado.codigo)) { 
		novo->prox = (*lst);  
		(*lst) = novo;
	}
	else { 
		q = (*lst);
		while ((q->prox != NULL) && (q->prox->dado.codigo < novo->dado.codigo)) { // coloca q no ultimo || ou no anterior ao n� onde o novo vai entrar
			q = q->prox;
		}
		novo->prox = q->prox;
		q->prox = novo;
	} 
}						

struct tNo *consultar (struct tNo *lst, int cod) { 
	struct tNo *q = lst; 
	
	while ((q != NULL) && (q->dado.codigo < cod)) { 
		q = q->prox;
	}
	
	if ((q != NULL) && (cod == q->dado.codigo)) { 
			// Testa se � diferente de NULL pois pode ser um valor que n�o est� na lista por ser maior que o ultimo elemento da lista.
			return q;
	}
	
	return NULL; 
}

void destruir (struct tNo **lst) {
	struct tNo *p = (*lst), *q;
	
	while (p != NULL) {
		q = p; 
		p = p->prox; 	
		free(q);						
	}
	
	inicializar(lst); 
}

void excluir (struct tNo **lst, struct tNo *vitima) {
// vitima � uma c�pia do p da main - passado por valor
// Independente do lugar pra onde vitima esteja apontando, a fun��o excluir deve excluir esse n� e manter a lista correta
	struct tNo *p = (*lst); // j� nasce apontando para o in�cio da lista
	
// Depois que executa a fun��o de um elemento em uma lista com apenas ele, ela fica vazia
// Exclus�o de �nico e In�cio: altera o valor da lista, ou seja, para onde ela est� apontando
// Se � elemento �nico, ele tamb�m � o primeiro. 
	if ((*lst == vitima)) { // Unico OU in�cio
		// Testa se o lugar pra onde a refer�ncia de lst aponta � o mesmo que vitima aponta
		(*lst) = vitima->prox;
		// Pode chegar no proximo por lst ou por vitima  
	} else { // Meio OU fim
		// Colocar um ponteiro apontando para o primeiro da lista e avan�ar um por um at� chegar no n� anterior � v�tima
		while (p->prox != vitima) { // coloca p no n� anterior a v�tima
			p = p->prox; // p aponta para onde p->prox atualmente est� apontando
		}
		p->prox = vitima->prox;  
	}
	free(vitima);
	// Libera a �rea de dados que foi alocada, que est� sendo apontada pelo ponteiro v�tima
}
