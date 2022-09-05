#include <stdio.h>
#include <stdlib.h>

//*** Declaracao de tipo de variavel **********************************************
struct tProduto {
	int codigo; // chave de ordena��o
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
				// Passa o descritor todo por refer�ncia			
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

void inicializar (struct tDescritor *lst) { 
	// Antes, o descritor era apenas um ponteiro com nome lista, passado por refer�ncia.
	// Agora, se trata de uma vari�vel com nome lista, do tipo struct tDescritor.
	(*lst).ini = (*lst).fim = NULL;	
	(*lst).qtd = 0; 
}

void listar(struct tDescritor lst) {  
	// lst � uma c�pia de lista por ter sido passado por valor
	struct tNo *p = lst.ini;
	printf("Codigo - Descricao - Valor\n");
	while (p != NULL) {
		printf("%d - %s - %.2f\n", p->dado.codigo, p->dado.descricao, p->dado.valor);
		p = p->prox;				
	}
}

void incluir(struct tDescritor *lst, struct tNo *novo) {
	struct tNo *q = (*lst).ini; // j� nasce apontando para o mesmo lugar que a refer�ncia de lst.ini aponta
	
	if ((*lst).ini == NULL) { // Vazia
		novo->ant = novo->prox = NULL;
		(*lst).ini = (*lst).fim = novo;		
	} 
	else { 
		if (novo->dado.codigo < (*lst).ini->dado.codigo) { // In�cio	
			novo->ant = NULL;
			novo->prox = (*lst).ini;
			(*lst).ini->ant = novo;
			(*lst).ini = novo;
		}
		else {
			if (novo->dado.codigo > (*lst).fim->dado.codigo) { // Fim
				novo->prox = NULL;
				novo->ant = (*lst).fim; // aponta para o mesmo lugar que o fim do descritor est� apontando
				(*lst).fim->prox = novo;
				(*lst).fim = novo;
			}
			else { // Meio
				while ((q->prox->dado.codigo < novo->dado.codigo)) { // coloca o ponteiro q no n� posterior � entrada			
				// O risco de chegar a NULL n�o existe, porque j� sei que n�o � uma inclus�o de fim	   	
					q = q->prox;				
				}
				novo->ant = q->ant;
				novo->prox = q;
				novo->ant->prox = novo; // tamb�m poderia partir do q: q->ant->prox
				novo->prox->ant = novo; // tamb�m poderia partir do q novamente: q->ant
			}
		}
	}
	(*lst).qtd++;
}						

struct tNo *consultar (struct tDescritor lst, int cod) { 
	struct tNo *q = lst.ini; // q aponta para o primeiro n�, onde lst.ini est� apontando 
	
	// � preciso usar a pesquisa sequencial, a n�o ser que j� tenha alguma informa��o pr�via
	// de onde � mais provavel que o c�digo a ser procurado esteja. Ex.: normalmente est� mais
	// pro final.
	 
	while ((q != NULL) && (q->dado.codigo < cod)) { 
		q = q->prox;
	}
	
	if ((q != NULL) && (cod == q->dado.codigo)) { 
			// Testa se � diferente de NULL pois pode ser um valor que n�o est� na lista por ser maior que o ultimo elemento da lista.
			return q;
	}
	
	return NULL; 
}

void destruir (struct tDescritor *lst) { // *lst � um par�metro  passado por refer�ncia
	struct tNo *p = (*lst).ini, *q;		 // (*lst) - lugar para onde se refere (aponta)
	
	while (p != NULL) {
		q = p; 
		p = p->prox; 	
		free(q);						
	}
	
	inicializar(lst);
	// na chamada da main, � preciso colocar o & porque lista n�o � uma refer�ncia na fun��o main.
	// aqui, lst j� � um ponteiro; ele j� se refere � lista.
}

void excluir (struct tDescritor *lst, struct tNo *vitima) {
	struct tNo *p = (*lst).ini;
	
	if (((*lst).ini == vitima) && ((*lst).fim == vitima)) { // Unico
		// A v�tima �, ao mesmo tempo, o in�cio e o fim
		(*lst).ini = (*lst).fim = NULL;		
	} 
	else { 
		if ((*lst).ini == vitima) { // In�cio	
			vitima->prox->ant = NULL;
			(*lst).ini = vitima->prox;
		}
		else {
			if ((*lst).fim == vitima) { // Fim
				vitima->ant->prox = NULL;
				(*lst).fim = vitima->ant;
			}
			else { // Meio
				// N�o precisa de um ponteiro auxiliar pois, por ser lista duplamente encadeada
				// j� sabe qual � o anterior e o pr�ximo dele.
				vitima->prox->ant = vitima->ant;
				// O ponteiro ant do pr�ximo n� depois da v�tima passa a apontar para o n� anterior da v�tima.
				vitima->ant->prox = vitima->prox;
				// O ponteiro prox do n� anterior � v�tima passa a apontar para o pr�ximo n� depois da v�tima.
			}
		}
	}
	(*lst).qtd--;
	free(vitima);
}
