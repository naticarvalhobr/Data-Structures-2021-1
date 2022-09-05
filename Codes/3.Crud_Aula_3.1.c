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
int menu();
void inicializar (struct tNo **lst);
void listar(struct tNo *lst);
void incluir(struct tNo **lst, struct tNo *novo);
struct tNo *consultar (struct tNo *lst, int cod);
void destruir (struct tNo **lst);

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
				scanf("%d", &(p->dado.codigo)); //scanf("%d", &((*p).dado.codigo));
				printf("Digite a descricao: ");
				fflush(stdin);
				gets(p->dado.descricao);
				printf("Digite o valor....: ");
				scanf("%f", &(p->dado.valor));				
				
				// Criar o n� fora do m�dulo inclus�o e depois incluir na lista
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
				
				p = consultar(lista, codigo); // retornar um n� inteiro, quando o encontrar
				
				if (p == NULL) {
					printf("Codigo nao encontrado!");
				} else {
					printf("Descricao: %s\n", p->dado.descricao);
					printf("Valor: R$ %.2f", p->dado.valor);
				}
				break;
			case 4:
				printf("\n\n\n Alterar\n"); 
				// se quisesse alterar o codigo (o que � incomum), exclui o n� antigo que quer alterar, e insere o novo com os dados alterados
				printf("Digite o codigo do produto: ");
				scanf("%d", &codigo);
				
				p = consultar(lista, codigo); // retornar um n� inteiro, quando o encontrar
				
				if (p == NULL) {
					printf("Codigo nao encontrado!");
				} else {
					printf("Descricao: %s\n", p->dado.descricao);
					printf("Valor: R$ %.2f\n", p->dado.valor);
					
					// Nesse exemplo, n�o permitimos a altera��o do c�digo
					printf("Digite a descricao: ");
					fflush(stdin);
					gets(p->dado.descricao); // sobrescreve a antiga descri��o
					printf("Digite o valor....: ");
					scanf("%f", &(p->dado.valor)); // sobrescreve o antigo valor
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
	printf("0. Sair\n\n");
	printf("Digite sua opcao: ");
	scanf("%d", &opcao);
	return opcao;
}

void inicializar (struct tNo **lst) { // ponteiro sendo passado por refer�ncia
	(*lst) = NULL;	
}

void listar(struct tNo *lst) { // ponteiro sendo passado por valor
	struct tNo *p = lst;
	printf("Codigo - Descricao - Valor\n");
	while (p != NULL) {
		printf("%d - %s - %.2f\n", p->dado.codigo, p->dado.descricao, p->dado.valor);
		p = p->prox;				
	}
}

void incluir(struct tNo **lst, struct tNo *novo) {
	// um * para indicar que � ponteiro e o outro * para desreferenciar
	struct tNo *q;
	
	// p = elemento novo
	// lista = aponta para o primeiro elemento
	if (((*lst) == NULL) || (novo->dado.codigo < (*lst)->dado.codigo)) { // vazia ou in�cio
		// Se a lista est� vazia, lst aponta para NULL
		novo->prox = (*lst); // prox aponta para onde lista est� apontando (onde anteriormente era o primeiro) 
		(*lst) = novo;
		// � preciso escrever as duas linhas acima nessa ordem
	}
	else { // fim, meio		
		q = (*lst);
		while ((q->prox != NULL) && (q->prox->dado.codigo < novo->dado.codigo)) { // coloca q no ultimo || ou no anterior ao n� onde o novo vai entrar
			// Enquanto n�o chegou no ultimo *e* o proximo elemento � menor que o novo elemento
			q = q->prox;
			// q->prox->dado.codigo : aponta para o proximo do q
			// q e p sempre apontam para n�s
		}
		//q->prox = novo; // q->prox no ultimo elemento vale NULL
		//novo->prox = NULL;
		novo->prox = q->prox;
		q->prox = novo;
	}
}						

struct tNo *consultar (struct tNo *lst, int cod) { // retorna um ponteiro capaz de apontar para um ponteiro do tipo tNo
	struct tNo *q = lst; // ponteiro auxiliar para percorrer a lista
	
	while ((q != NULL) && (q->dado.codigo < cod)) { // deve checar se primeiro � diferente de NULL porque, no ultimo elemento
	// da lista, q == NULL, e n�o teria como nem checar o codigo. Ou seja, j� daria erro na primeira parte.
		q = q->prox;
	// pode sair do while porque chegou em NULL, porque encontrou o cod ou porque o codigo inserido � maior que o cod
	}
	
	if ((q != NULL) && (cod == q->dado.codigo)) { // se encontrar o codigo procurado, retorne o n� para onde q est� apontando
			return q;
	}
	
	return NULL; // seria o mesmo que retornar q, porque nesse momento q=NULL. Mas em termos de processamento, fica
	// mais lento, porque tem que ir l� olhar o que q vale.
}

void destruir (struct tNo **lst) {
	struct tNo *p = (*lst), *q;
	
	// Libera a memoria ocupada pelos n�s da lista
	while (p != NULL) {
		q = p; // coloca o q em algum lugar que ele morre
		p = p->prox; // salva o p		
		free(q);						
	}
	
	inicializar(lst); // o ponteiro que aponta pra lista volta a apontar pra NULL, pra sinalizar que a lista est� vazia
	// n�o coloca o & porque, dentro da fun��o, lst j� � uma refer�ncia de ponteiro.
	// Se o lst fosse apenas um ponteiro, a� sim precisaria colocar o &, assim como na main.
}
