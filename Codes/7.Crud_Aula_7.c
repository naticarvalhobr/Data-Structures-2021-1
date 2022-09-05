// Lista Circular Simplesmente Encadeada com Cabe�a e Descritor (somente com 1 ponteiro)
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

//*** Prototipos ******************************************************************
int menu();
void inicializar (struct tNo **lst);
void listar(struct tNo *lst);
void incluir(struct tNo *lst, struct tNo *novo);
struct tNo *consultar (struct tNo *lst, int cod);
void excluir (struct tNo *lst, struct tNo *vitima);
// vitima � o ponteiro que aponta para o n� que quer excluir
void destruir (struct tNo *lst);

int main(void) {
	struct tNo *p, *q, *lista; 
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
				
				incluir(lista, p);				
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
					
					excluir(lista, p);
					// lista deve ser passada por refer�ncia pois precisa alter�-la dentro da fun��o
				}
		}
	} while (opcao != 0);
	
	destruir (lista);

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

void inicializar (struct tNo **cabeca) { 
	// struct tNo *cabeca = malloc (sizeof (struct tNo)); // criou uma vari�vel local que � ponteiro e aponta para 
	// uma �rea de mem�ria que foi criada agora.
	// struct tNo *cabeca = (struct tNo*) malloc (sizeof (struct tNo)); // ficaria assim se pedisse um cast
	// Para criar um n�, a �nica maneira de aloc�-lo na mem�ria � usando malloc.
	(*cabeca) = malloc (sizeof(struct tNo)); // "Lista" criou o n� e j� passou a apontar pra ele	
	
	(*cabeca)->prox = (*cabeca);
	//(*cabeca) = cabeca; // A refer�ncia de cabeca, ou seja "Lista", vai apontar para o mesmo lugar que "cabeca" aponta
}

void listar(struct tNo *cabeca) { // Nesse caso, cabeca � uma c�pia de "lista", ou seja, um ponteiro que aponta para a cabe�a
	struct tNo *p = cabeca->prox;
	
	printf("Codigo - Descricao - Valor\n");
	
	while (p != cabeca) {
		printf("%d - %s - %.2f\n", p->dado.codigo, p->dado.descricao, p->dado.valor);
		p = p->prox;				
	}
}

void incluir(struct tNo *cabeca, struct tNo *novo) { 
	struct tNo *p = cabeca; // coloca "p" na cabe�a. No caso da primeira inclus�o ap�s a cabe�a, p aponta para si mesma.
	
	while ((p->prox != cabeca) && (p->prox->dado.codigo < novo->dado.codigo)) { // coloca "p" no anterior � entrada
		p = p->prox;
	}
	
	novo->prox = p->prox;
	p->prox = novo;
}				 		

struct tNo *consultar (struct tNo *cabeca, int cod) { 
	struct tNo *p = cabeca->prox; 
	// Cabe�a est� sendo usada como Sentinela. N�o precisa criar um n� a mais.
	// Antes de mais nada, � preciso setar o Sentinela com o valor que deseja.
	cabeca->dado.codigo = cod + 1; // colocando no Sentinela o valor buscado + 1
	// N�o tem problema que fique esse valor dentro do "cabeca". � lixo.
	
	while (p->dado.codigo < cod) { 
		p = p->prox;
	}
	
	if (cod == p->dado.codigo) { // s� para no n� caso seja o cod buscado
			// Testa se � diferente de cabe�a pois, se isso for F, p j� vai ter voltado pra cabe�a
			return p;
	}
	
	return NULL; // se n�o achar o n�, retorna NULL
}

void excluir (struct tNo *cabeca, struct tNo *vitima) {
	struct tNo *p = cabeca; 
	// Nunca vai excluir a cabe�a, mas sim um n�. Por isso, pode ser passada por valor.
	// Toda exclus�o � de meio.
	
	while (p->prox != vitima) { // coloca p no n� anterior � v�tima
		p = p->prox; 
	}
	p->prox = vitima->prox;  
	
	free(vitima);
}

void destruir (struct tNo *cabeca) { // Apaga tudo, inclusive a cabe�a
	struct tNo *p = cabeca->prox, *q;
	// Aqui dentro, entende a cabe�a como um n� qualquer e apaga ele tamb�m
	cabeca->prox = NULL; // transforma a circular em linear. Cabe�a passa a apontar 
	// para NULL. O n� anterior a ele passa a ser o pen�ltimo da lista.
	
	while (p != NULL) {
		q = p; 
		p = p->prox; 	
		free(q);						
	}
	
	// N�o tem mais como colocar para inicializar a lista aqui novamente, igual fazia antes
}
