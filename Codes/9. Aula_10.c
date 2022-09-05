// Sintese
//   objetivo "Lista Simplesmente Encadeada"
//   autor "Edson F. da Fonseca & Turma de Estrutura de Dados 2021/1"
//   data "17/03/2021"
#include <stdio.h>
#include <stdlib.h>

#define M 10
#define VAZIO 0
#define OCUPADO 1 
#define DELETADO -1 

//*** Declaracao de tipo de variavel **********************************************
struct tProduto {
	int codigo; // chave de ordenacao
	char descricao[30];
	float valor;
};

struct tPosicao {
	int estado; // vazio, ocupado, deletado
	struct tProduto dado;
};

//*** Prototipos ******************************************************************
int menu();
int hash (int chave, int i);
void inicializar (struct tPosicao tabela[]);
void incluir(struct tPosicao tabela[], struct tProduto prod);
void listar(struct tPosicao tabela[]);
//struct tNo *consultar (struct tNo *lst, int cod);
//void destruir (struct tNo **lst);
//void excluir (struct tNo **lst, struct tNo *vitima);
	
int main(void) {
	
	struct tPosicao tabelaHash[M]; // Tabela Hash
	struct tProduto produto;
	int opcao, codigo;
	
	inicializar(tabelaHash);
	do {
		opcao = menu();
		switch (opcao) {
			case 1:
				printf("\n\n\nInclusao\n");
				printf("Digite o codigo...: ");
				scanf("%d", &produto.codigo); 
				
				printf("Digite a descricao: ");
				fflush(stdin);
				gets(produto.descricao);
				
				printf("Digite o valor....: ");
				scanf("%f", &produto.valor);				
				
				if (!incluir(tabelaHash, produto)) {
					printf("\nColisao!!\n\n");
				}
				break;
			case 2:
				printf("\n\n\nListagem\n");
				listar(tabelaHash);
				break;
			case 3:
				printf("\n\n\nConsultar\n");
				printf("Digite o codigo...: ");
				scanf("%d", &codigo);
				// Pesquisar um produto com este codigo
				/*
				p = consultar(lista, codigo); // retornar um n� inteiro, quando o encontrar
				if (p == NULL) {
					printf("Codigo nao encontrado!");
				} else {
					printf("Descricao: %s\n", p->dado.descricao);
					printf("Valor....: R$ %.2f", p->dado.valor);
				}
				break;*/
			case 4:
				printf("\n\n\nAlterar\n");
				printf("Digite o codigo...: ");
				scanf("%d", &codigo);
				/*p = consultar(lista, codigo);
				if (p == NULL) {
					printf("Codigo nao encontrado!");
				} else {
					printf("Descricao: %s\n", p->dado.descricao);
					printf("Valor....: R$ %.2f\n", p->dado.valor);	
					printf("Digite a descricao: ");
					fflush(stdin);
					gets(p->dado.descricao); // sobrescreve a antiga descri��o
					printf("Digite o valor....: ");
					scanf("%f", &(p->dado.valor)); // sobrescreve o antigo valor
					
					// Consultar pelo codigo e, caso encontre, permitir alterar apenas a descri��o e o valor.
					// N�o o codigo, pois � chave!	
					// se quisesse alterar o codigo (o que � incomum), exclui o n� antigo que quer alterar, 
					// e insere o novo com os dados alterados						
				}*/
				break;
			case 5:
				printf("\n\n\nExcluir\n");
				printf("Digite o codigo...: ");
				scanf("%d", &codigo);
				/*p = consultar(lista, codigo);
				if (p == NULL) {
					printf("Codigo nao encontrado!");
				} else {
					printf("Descricao: %s\n", p->dado.descricao);
					printf("Valor....: R$ %.2f\n", p->dado.valor);	
					excluir(&lista, p);
					// lista deve ser passada por refer�ncia pois precisa alter�-la dentro da fun��o				
				}*/
				// Consultar pelo codigo e, caso encontre, excluir o no da lista.
		}
	} while (opcao != 0);

	return 0;
}

// *** menu ***********************************************************************
int menu(void) {
	int opcao;
	printf("\n\n\n*** menu ***\n");
	printf("1. Incluir/espalhar\n");
	printf("2. Listar produtos\n");
	printf("3. Consultar produto\n");
	printf("4. Alterar produto\n");
	printf("5. Excluir produto\n");
	printf("0. Sair\n\n");
	printf("Digite sua opcao: ");
	scanf("%d", &opcao);
	return opcao;
}

// *** Fun��o de Hash ****************************************************************
int hash (int chave, int i) {
	return (chave + i) % M; // n�o � obrigado a somar, mas precisa usar i de alguma forma
	// mod de 10 - faz ele sempre retornar um valor entre 0 e 9
	// resto da divis�o pelo tamanho da tabela (normalmente � M)
}

// *** Inicializar ****************************************************************
void inicializar (struct tPosicao tabela[]) {
	int i;
	
	for (i=0; i < M; i++) {
		tabela[i].estado = VAZIO;
	} 
}

// *** listar *********************************************************************
void listar(struct tPosicao tabela[]) {
	int i;
	
	printf("POS - ESTADO - Codigo - Descricao - Valor\n");
	for (i=0; i < M; i++) {
		switch (tabela[i].estado) {
			case VAZIO: printf("%3d - VAZIO\n", i); break;
			case OCUPADO: printf("%3d - OCUPADO - %d - %s - %.2f\n", i, tabela[i].dado.codigo, tabela[i].dado.descricao, tabela[i].dado.valor); break;
			case DELETADO: printf("%3d - DELETADO", i);
		}
	}
}

// *** incluir ********************************************************************
int incluir(struct tPosicao tabela[], struct tProduto prod) {
	int posicao, i=0;

	// Endere�amento Linear
	do {
		posicao = hash (prod.codigo, i); // fator linear = 0
		i++;		
	} while ((i < M) && (tabela[posicao].estado == OCUPADO)); // n�o pode ser vazio, nem deletado
	// do while porque precisa procurar a posi��o pelo menos 1x

	if (i < M) { 
		tabela[posicao].dado = prod; // ocupou a posi��o
		tabela[posicao].estado = OCUPADO; // muda o estado para ocupado
		return 1;
	}
	return 0;		
}

/*
// *** Consultar ******************************************************************
struct tNo *consultar(struct tNo *lst, int cod) { // retorna um ponteiro capaz de apontar para um ponteiro do tipo tNo
	struct tNo *q=lst; // ponteiro auxiliar para percorrer a lista
		
	while ((q != NULL) && (q->dado.codigo < cod)) { // deve checar se primeiro � diferente de NULL porque, no ultimo elemento
	// da lista, q == NULL, e n�o teria como nem checar o codigo. Ou seja, j� daria erro na primeira parte.
		q = q->prox;
		// pode sair do while porque chegou em NULL, porque encontrou o cod ou porque o codigo inserido � maior que o cod
	}
	if ((q != NULL) && (q->dado.codigo == cod)) { // se encontrar o codigo procurado, retorne o n� para onde q est� apontando
		// Testa se � diferente de NULL pois pode ser um valor que n�o est� na lista por ser maior que o ultimo elemento da lista.
		return q;
	}
	
	return NULL; // seria o mesmo que retornar q, porque nesse momento q=NULL. Mas em termos de processamento, fica
	// mais lento, porque tem que ir l� olhar o que q vale.
}

// *** Excluir ********************************************************************
void excluir(struct tNo **lst, struct tNo *vitima) {
	// vitima � uma c�pia do p da main - passado por valor
// Independente do lugar pra onde vitima esteja apontando, a fun��o excluir deve excluir esse n� e manter a lista correta
	struct tNo *p = (*lst); // j� nasce apontando para o in�cio da lista
	
	// Depois que executa a fun��o de um elemento em uma lista com apenas ele, ela fica vazia
	// Exclus�o de �nico e In�cio: altera o valor da lista, ou seja, para onde ela est� apontando
	// Se � elemento �nico, ele tamb�m � o primeiro.
	if ((*lst) == vitima) // unico OU inicio
		// Testa se o lugar pra onde a refer�ncia de lst aponta � o mesmo que vitima aponta
		(*lst) = vitima->prox;
		// Pode chegar no proximo por lst ou por vitima  
	else { // meio OU fim
		// Colocar um ponteiro apontando para o primeiro da lista e avan�ar um por um at� chegar no n� anterior � v�tima
		while (p->prox != vitima) { // coloca p no n� anterior a vitima
			p = p->prox; // p aponta para onde p->prox atualmente est� apontando
		}
		p->prox = vitima->prox;	
	}
	free(vitima);
	// Libera a �rea de dados que foi alocada, que est� sendo apontada pelo ponteiro v�tima
}

// *** Destruir *******************************************************************
void destruir(struct tNo **lst) {
	struct tNo *p=(*lst), *q;
	while (p != NULL) {
		q = p;
		p = p->prox;		
		free(q);						
	}
	inicializar(lst);
}*/

