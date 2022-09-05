// Sintese
//   objetivo "Árvore Binária de Busca"
//   autor "Edson F. da Fonseca & Turma de Estrutura de Dados 2021/1"
//   data "12/05/2021"
#include <stdio.h>
#include <stdlib.h>

//*** Declaracao de tipo de variavel **********************************************
struct tProduto {
	int codigo; // chave de ordenacao
	char descricao[30];
	float valor;
};

struct tNo {
	struct tNo *esq;
	struct tProduto dado;
	struct tNo *dir;
};

#include "edsonArvore.h"

//*** Prototipos ******************************************************************
int menu();
void inicializar (struct tNo **raiz);
void incluir(struct tNo **raiz, struct tNo *novo);
void caminharEmOrdem(struct tNo *raiz);
void caminharPreOrdem(struct tNo *raiz);
void caminharPosOrdem(struct tNo *raiz);
void desenhar (struct tNo *raiz);
struct tNo *buscar (struct tNo *raiz, int cod);
int excluir (struct tNo **raiz, int cod);
void destruir (struct tNo **raiz);
	
int main(void) {
	struct tNo *arvore; // descritor
	struct tNo *p, *q;
	int opcao, codigo;
	
	inicializar(&arvore);
	do {
		opcao = menu();
		switch (opcao) {
			case 1:
				printf("\n\n\nInclusao\n");
				/* Com o código abaixo, toda vez cria a árvore toda
				p = (struct tNo*) malloc(sizeof(struct tNo));
				printf("Digite o codigo...: ");
				scanf("%d", &(p->dado.codigo)); //scanf("%d", &((*p).dado.codigo));
				printf("Digite a descricao: ");
				fflush(stdin);
				gets(p->dado.descricao);
				printf("Digite o valor....: ");
				scanf("%f", &(p->dado.valor));				
				incluir(&arvore, p);*/
				
				// No código abaixo, toda vez que executar o incluir, cria uma árvore fixa
				p = (struct tNo*) malloc(sizeof(struct tNo));
				p->dado.codigo = 8;
				incluir(&arvore, p);
				p = (struct tNo*) malloc(sizeof(struct tNo));
				p->dado.codigo = 6;
				incluir(&arvore, p);
				p = (struct tNo*) malloc(sizeof(struct tNo));
				p->dado.codigo = 10;
				incluir(&arvore, p);
				p = (struct tNo*) malloc(sizeof(struct tNo));
				p->dado.codigo = 4;
				incluir(&arvore, p);
				p = (struct tNo*) malloc(sizeof(struct tNo));
				p->dado.codigo = 20;
				incluir(&arvore, p);
				p = (struct tNo*) malloc(sizeof(struct tNo));
				p->dado.codigo = 7;
				incluir(&arvore, p);
				p = (struct tNo*) malloc(sizeof(struct tNo));
				p->dado.codigo = 15;
				incluir(&arvore, p);
				p = (struct tNo*) malloc(sizeof(struct tNo));
				p->dado.codigo = 25;
				incluir(&arvore, p);
				
				break;
			case 2:
				printf("\n\n\nCaminhamento Em-ordem\n");
				caminharEmOrdem (arvore);
				// Arvore passa por valor, pois não precisa alterá-la para percorre-la.
				break;
			case 3:
				printf("\n\n\nCaminhamento Pre-ordem\n");
				caminharPreOrdem (arvore);
				break;
			case 4:
				printf("\n\n\nCaminhamento Pos-ordem\n");
				caminharPosOrdem (arvore);
				break;
			case 5:
				printf("\n\n\nBuscar\n");
				printf("Digite o codigo...: ");
				scanf("%d", &codigo);
				p = buscar(arvore, codigo);
				if (p == NULL)
					printf("\nCodigo nao encontrado!");
				else {
					printf("\nDescricao: %s\n", p->dado.descricao);
					printf("Valor....: R$ %.2f", p->dado.valor);
				}
				break;
			case 6:
				printf("\n\n\nExcluir\n");
				printf("Digite o codigo...: ");
				scanf("%d", &codigo);

				// Vai direto para a função excluir, pois esta já vai fazer o papel de consulta dentro dela
				if (!excluir(&arvore, codigo)) // Se não excluir...
					printf("Codigo nao encontrado!");
				break;
			case 7:
				printf("\n\n\nDesenhar - Representacao de parenteses aninhados\n");
				// É preciso caminhar pela árvore toda e mostrar todos os nós dela
				desenhar(arvore);
		}
	} while (opcao != 0);
	destruir(&arvore);
	return 0;
}

// *** menu ***********************************************************************
int menu(void) {
	int opcao;
	printf("\n\n\n*** menu ***\n");
	printf("1. Incluir produto\n");
	printf("2. Caminhar em-ordem\n");
	printf("3. Caminhar pre-ordem\n");
	printf("4. Caminhar pos-ordem\n");
	printf("5. Buscar produto\n");
	printf("6. Excluir produto\n");
	printf("7. Desenhar a arvore\n"); 
	printf("0. Sair\n\n");
	printf("Digite sua opcao: ");
	scanf("%d", &opcao);
	return opcao;
}

// *** Inicializar ****************************************************************
void inicializar(struct tNo **raiz) { // ponteiro sendo passado por referência
	(*raiz) = NULL;
}

// *** Caminhar Em-Ordem *********************************************************************
void caminharEmOrdem (struct tNo *raiz) { 
	if (raiz == NULL) { // Se for verdadeiro, não tem como caminhar na árvore pois ela está vazia
		return; // Como é void, não tem um valor para retornar. O return só sinaliza que a função encerrou.
	}
	caminharEmOrdem (raiz->esq); // Anda o lado esquerdo todo da árvore
	// Vai pra esquerda e, só aí, verifica se é Null
	printf("%d ", raiz->dado.codigo); // Imprime o valor do nó
	caminharEmOrdem (raiz->dir); // Anda o lado direito todo da árvore
}

// *** Caminhar Pre-Ordem *********************************************************************
void caminharPreOrdem (struct tNo *raiz) { 
	if (raiz == NULL) { // Se for verdadeiro, não tem como caminhar na árvore pois ela está vazia
		return; // Como é void, não tem um valor para retornar. O return só sinaliza que a função encerrou.
	}
	printf("%d ", raiz->dado.codigo); // Imprime o valor do nó
	caminharPreOrdem (raiz->esq); // Anda o lado esquerdo todo da árvore
	caminharPreOrdem (raiz->dir); // Anda o lado direito todo da árvore
}

// *** Caminhar Pos-Ordem *********************************************************************
void caminharPosOrdem (struct tNo *raiz) { 
	if (raiz == NULL) { // Se for verdadeiro, não tem como caminhar na árvore pois ela está vazia
		return; // Como é void, não tem um valor para retornar. O return só sinaliza que a função encerrou.
	}
	caminharPosOrdem (raiz->esq); // Anda o lado esquerdo todo da árvore
	caminharPosOrdem (raiz->dir); // Anda o lado direito todo da árvore
	printf("%d ", raiz->dado.codigo); // Imprime o valor do nó
}

// *** Desenhar árvore usando parenteses aninhados *********************************************************************
// Mesma lógica do Pré Ordem
void desenhar (struct tNo *raiz) { 
	if (raiz == NULL) { // Se for verdadeiro, não tem como caminhar na árvore pois ela está vazia
		printf("()"); // Se quisesse representar os pontos em que não há nós
		return; 
	}
	printf("%d(", raiz->dado.codigo); // Imprime o valor do nó
	desenhar (raiz->esq); // Anda o lado esquerdo todo da árvore
	desenhar (raiz->dir); // Anda o lado direito todo da árvore
	printf(")"); // Imprime o parênteses fechando
}

// *** incluir ********************************************************************
void incluir(struct tNo **raiz, struct tNo *novo) {
	// novo é uma cópia do p (dia 05/05 11h03)
	
	/* Parte do código para acompanhar o andamento na função
	if ((*raiz) == NULL) {
		printf("\nBuscar - No: null");
	} 
	else {
		printf("\nBuscar - No: %d", (*raiz)->dado.codigo);	
	}*/
	
	
	if ((*raiz) == NULL) {
		novo->esq = novo->dir = NULL; // todo nó quando é incluído é uma folha (sem filhos). Depois, pode deixar de ser uma folha
		(*raiz) = novo;
	} else { // procura uma árvore vazia
		if (novo->dado.codigo < (*raiz)->dado.codigo) { // esquerda (menor)
			incluir(&((*raiz)->esq), novo); // & pois passa por referência
			// Chamo recursivamente a função
		} else { // direita (maior ou igual)
			incluir(&((*raiz)->dir), novo);
			// Ex.: a primeira instância chama o incluir, gerando a segunda instância
		}
	}
}

// *** Buscar ******************************************************************
struct tNo *buscar(struct tNo *raiz, int cod) {
	
	/* Parte do código para acompanhar o andamento na função
	if (raiz == NULL) {
		printf("\nBuscar - No: null");
	} 
	else {
		printf("\nBuscar - No: %d", raiz->dado.codigo);	
	}*/
	
	
	if ((raiz == NULL) || (raiz->dado.codigo == cod)) { // se chegar em NULL, o nó que está procurando não existe
		return raiz; // se encontrou o que procurava, raiz aponta para ele. Então, retorna ele.
	} 
	if (cod < raiz->dado.codigo) { // esquerda
		return buscar(raiz->esq, cod); 
	} 
	// direita
	return buscar(raiz->dir, cod);
	
	/* Quando achar o valor que está procurando, retorna ele para a instância anterior. Esta pega
	o retorno e retorna para a outra instância. Esse processo continua até que a última instância
	retorna um ponteiro para o main.
	
	O buscar' passou como primeiro parâmetro para o buscar'' o caminho para o próximo nó. Depois, buscar'' 
	retorna para a função que a chamou, buscar', um ponteiro para o nó encontrado, nesse caso.
	*/
}

// *** Excluir ********************************************************************
int excluir (struct tNo **raiz, int cod) {
	// Usa a mesma lógica do incluir e buscar
	struct tNo *p = (*raiz); // ponteiro auxiliar p aponta para o mesmo lugar que raiz
	if ((*raiz) == NULL) { // não encontrou o nó que queria
		return 0;  
		// tem a possibilidade de não achar porque a função excluir também faz o papel de consulta
	} 
	if ((*raiz)->dado.codigo == cod) { // Testa se o nó onde está é o que deseja excluir
		if (((*raiz)->esq == NULL) && ((*raiz)->dir == NULL)) { // folha
			(*raiz) = NULL;
			free(p);
			return 1; // retorna 1 porque excluiu com sucesso			
		}
		if ((*raiz)->esq == NULL) { // Um filho à direita
			(*raiz) = (*raiz)->dir; // o ponteiro que apontava para o que será excluído, passa a apontar para o filho da direita dele
			free(p);
			// Ou seja, o filho entra no lugar do que foi excluído
			return 1;
		}
		if ((*raiz)->dir == NULL) { // Um filho à esquerda
			(*raiz) = (*raiz)->esq; // o ponteiro que apontava para o que será excluído, passa a apontar para o filho da esquerda dele
			free(p);
			return 1;
		}
		// Só sobra a possibilidade de ter dois filhos
		/* Não vai excluir esse nó que tem dois filhos, mas sim substituir o valor dele pelo nó com valor
		imediatamente anterior a ele ou imediatamente posterior a ele.
		Então, efetivamente exclui o nó que terá seu valor copiado, o qual nunca poderá ter dois filhos. 
		Pegando o elemento imediatamente anterior a ele, será o mais à direita da esquerda do que está sendo substituido.
		Pegando o elemento imediatamente depois dele, será o mais à esquerda da direita do que está sendo substituído. Tanto faz se é esse método ou o da linha acima.
		*/   	
		p = maior((*raiz)->esq); // p aponta para o maior que está à esquerda. Passa como parâmetro o filho da esquerda do nó que quero excluir
		// Função "maior": passa como parâmetro pra ela um nó e vai retornar um ponteiro que aponta para o maior nó a partir do lugar que passou como referência.
		(*raiz)->dado = p->dado; // Copia os dados do nó maior (p) para o nó que quer excluir (raiz). Depois disso, os dados de p estarão dobrados.    
		excluir(&((*raiz)->esq), p->dado.codigo); 
		return 1; 
	}
	if (cod < (*raiz)->dado.codigo) { // esquerda
		return excluir(&((*raiz)->esq), cod); 
	} 
	// direita
	return excluir(&((*raiz)->dir), cod);
}

// *** Destruir *******************************************************************
// Destruir tem a mesma lógica do caminhamento em Pós Ordem.
void destruir(struct tNo **raiz) { 
	if ((*raiz) == NULL) { 
		return; 
	}
	destruir (&((*raiz)->esq)); // Anda o lado esquerdo todo da árvore
	destruir (&((*raiz)->dir)); // Anda o lado direito todo da árvore
	// & pois está passando por referência
	free(*raiz); 
}
