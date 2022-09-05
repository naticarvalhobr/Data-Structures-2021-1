// Sintese
//   objetivo "�rvore Bin�ria de Busca Balanceada - AVL"
//   autor "Edson F. da Fonseca & Turma de Estrutura de Dados 2021/1"
//   data "19/05/2021"
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
void rotacaoSD(struct tNo **pai);
void rotacaoSE(struct tNo **pai);
void caminharEmOrdem(struct tNo *raiz);
void caminharPreOrdem(struct tNo *raiz);
void caminharPosOrdem(struct tNo *raiz);
void desenhar (struct tNo *raiz);
struct tNo *buscar (struct tNo *raiz, int cod);
int excluir (struct tNo **raiz, int cod);
void destruir (struct tNo **raiz);
int fb(struct tNo *raiz);
void balancearAVL(struct tNo **raiz);
	
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
				//Com o c�digo abaixo, toda vez cria a �rvore toda
				p = (struct tNo*) malloc(sizeof(struct tNo));
				printf("Digite o codigo...: ");
				scanf("%d", &(p->dado.codigo)); 
				/*printf("Digite a descricao: ");
				fflush(stdin);
				gets(p->dado.descricao);
				printf("Digite o valor....: ");
				scanf("%f", &(p->dado.valor)); */				
				incluir(&arvore, p); 
				break;
			case 2:
				printf("\n\n\nCaminhamento Em-ordem\n");
				caminharEmOrdem (arvore);
				// Arvore passa por valor, pois n�o precisa alter�-la para percorre-la.
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

				// Vai direto para a fun��o excluir, pois esta j� vai fazer o papel de consulta dentro dela
				if (!excluir(&arvore, codigo)) // Se n�o excluir...
					printf("Codigo nao encontrado!");
				break;
			case 7:
				printf("\n\n\nDesenhar - Representacao de parenteses aninhados\n");
				// � preciso caminhar pela �rvore toda e mostrar todos os n�s dela
				desenhar(arvore);
		}
	} while (opcao != 0);
	//destruir(&lista);
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
void inicializar(struct tNo **raiz) { // ponteiro sendo passado por refer�ncia
	(*raiz) = NULL;
}

// *** Caminhar Em-Ordem **********************************************************
void caminharEmOrdem (struct tNo *raiz) { 
	if (raiz == NULL) { // Se for verdadeiro, n�o tem como caminhar na �rvore pois ela est� vazia
		return; // Como � void, n�o tem um valor para retornar. O return s� sinaliza que a fun��o encerrou.
	}
	caminharEmOrdem (raiz->esq); // Anda o lado esquerdo todo da �rvore
	// Vai pra esquerda e, s� a�, verifica se � Null
	printf("%d ", raiz->dado.codigo); // Imprime o valor do n�
	caminharEmOrdem (raiz->dir); // Anda o lado direito todo da �rvore
}

// *** Caminhar Pre-Ordem *********************************************************
void caminharPreOrdem (struct tNo *raiz) { 
	if (raiz == NULL) { // Se for verdadeiro, n�o tem como caminhar na �rvore pois ela est� vazia
		return; // Como � void, n�o tem um valor para retornar. O return s� sinaliza que a fun��o encerrou.
	}
	printf("%d ", raiz->dado.codigo); // Imprime o valor do n�
	caminharPreOrdem (raiz->esq); // Anda o lado esquerdo todo da �rvore
	caminharPreOrdem (raiz->dir); // Anda o lado direito todo da �rvore
}

// *** Caminhar Pos-Ordem *********************************************************
void caminharPosOrdem (struct tNo *raiz) { 
	if (raiz == NULL) { // Se for verdadeiro, n�o tem como caminhar na �rvore pois ela est� vazia
		return; // Como � void, n�o tem um valor para retornar. O return s� sinaliza que a fun��o encerrou.
	}
	caminharPosOrdem (raiz->esq); // Anda o lado esquerdo todo da �rvore
	caminharPosOrdem (raiz->dir); // Anda o lado direito todo da �rvore
	printf("%d ", raiz->dado.codigo); // Imprime o valor do n�
}

// *** Desenhar �rvore usando parenteses aninhados ********************************
// Mesma l�gica do Pr� Ordem
void desenhar (struct tNo *raiz) { 
	if (raiz == NULL) { // Se for verdadeiro, n�o tem como caminhar na �rvore pois ela est� vazia
		//printf("()"); // Se quisesse representar os pontos em que n�o h� n�s
		return; 
	}
	printf("%d(", raiz->dado.codigo); // Imprime o valor do n�
	desenhar (raiz->esq); // Anda o lado esquerdo todo da �rvore
	desenhar (raiz->dir); // Anda o lado direito todo da �rvore
	printf(")"); // Imprime o par�nteses fechando
}

// *** incluir ********************************************************************
void incluir(struct tNo **raiz, struct tNo *novo) {
	// novo � uma c�pia do p (dia 05/05 11h03)
		
	if ((*raiz) == NULL) {
		novo->esq = novo->dir = NULL; // todo n� quando � inclu�do � uma folha (sem filhos). Depois, pode deixar de ser uma folha
		(*raiz) = novo;
	} else { // procura uma �rvore vazia
		if (novo->dado.codigo < (*raiz)->dado.codigo) { // esquerda (menor)
			incluir(&((*raiz)->esq), novo); // & pois passa por refer�ncia
			// Chamo recursivamente a fun��o
		} else { // direita (maior ou igual)
			incluir(&((*raiz)->dir), novo);
			// Ex.: a primeira inst�ncia chama o incluir, gerando a segunda inst�ncia
		}
	}
	/* No momento em que foi incluir um n� na �rvore, percorreu-a toda de forma recursiva. Isso significa que tem uma inst�ncia
	apontando para raiz, e uma inst�ncia apontando para n� do caminho que percorreu at� incluir aquele n� em particular. 
	No momento em que termina de executar cada inst�ncia da fun��o, em cada n� do caminho, verificaremos se nele a �rvore ficou
	desbalanceada (olhando o FB dele). */
	balancearAVL(raiz);
}

// *** Fator de Balanceamento *************************************************
int fb(struct tNo *raiz) { // passa raiz por valor
	return altura(raiz->dir) - altura(raiz->esq);
	// Altura: dist�ncia em n�veis do n� passado como par�metro at� a folha mais distante dele
}


// *** Rota��o Simples Direita *************************************************
void rotacaoSD(struct tNo **pai) {
	struct tNo *filho = (*pai)->esq; // guarda dentro de um n� em particular o filho
	
	(*pai)->esq = filho->dir;
	filho->dir = (*pai);
	(*pai) = filho; 
	/* Lembre que, em nenhum tipo de rota��o, nunca ningu�m vai apontar para NULL aqui dentro, apenas troca para onde ponteiros 
	j� existentes apontam. Isso porque h� situa��es em que isso n�o pode ocorrer. */	
}

// *** Rota��o Simples Esquerda *************************************************
void rotacaoSE(struct tNo **pai) {
	struct tNo *filho = (*pai)->dir;
	
	(*pai)->dir = filho->esq;
	filho->esq = (*pai);
	(*pai) = filho; 
}

// *** Buscar ******************************************************************
struct tNo *buscar(struct tNo *raiz, int cod) {
	
	if ((raiz == NULL) || (raiz->dado.codigo == cod)) { // se chegar em NULL, o n� que est� procurando n�o existe
		return raiz; // se encontrou o que procurava, raiz aponta para ele. Ent�o, retorna ele.
	} 
	if (cod < raiz->dado.codigo) { // esquerda
		return buscar(raiz->esq, cod); 
	} 
	// direita
	return buscar(raiz->dir, cod);
	
	/* Quando achar o valor que est� procurando, retorna ele para a inst�ncia anterior. Esta pega
	o retorno e retorna para a outra inst�ncia. Esse processo continua at� que a �ltima inst�ncia
	retorna um ponteiro para o main.
	
	O buscar' passou como primeiro par�metro para o buscar'' o caminho para o pr�ximo n�. Depois, buscar'' 
	retorna para a fun��o que a chamou, buscar', um ponteiro para o n� encontrado, nesse caso.
	*/
}

// *** Excluir *****************************************************************
int excluir (struct tNo **raiz, int cod) {
	// Usa a mesma l�gica do incluir e buscar
	struct tNo *p = (*raiz); // ponteiro auxiliar p aponta para o mesmo lugar que raiz
	int retorno;
	
	if ((*raiz) == NULL) { // n�o encontrou o n� que queria
		return 0;  
		// tem a possibilidade de n�o achar porque a fun��o excluir tamb�m faz o papel de consulta
	} 
	if ((*raiz)->dado.codigo == cod) { // Testa se o n� onde est� � o que deseja excluir
		if (((*raiz)->esq == NULL) && ((*raiz)->dir == NULL)) { // folha
			(*raiz) = NULL;
			free(p);
			return 1; // retorna 1 porque excluiu com sucesso			
		}
		if ((*raiz)->esq == NULL) { // Um filho � direita
			(*raiz) = (*raiz)->dir; // o ponteiro que apontava para o que ser� exclu�do, passa a apontar para o filho da direita dele
			free(p);
			// Ou seja, o filho entra no lugar do que foi exclu�do
			return 1;
		}
		if ((*raiz)->dir == NULL) { // Um filho � esquerda
			(*raiz) = (*raiz)->esq; // o ponteiro que apontava para o que ser� exclu�do, passa a apontar para o filho da esquerda dele
			free(p);
			return 1;
		}
		// S� sobra a possibilidade de ter dois filhos  	
		p = maior((*raiz)->esq); // p aponta para o maior que est� � esquerda. Passa como par�metro o filho da esquerda do n� que quero excluir
		// Fun��o "maior": passa como par�metro pra ela um n� e vai retornar um ponteiro que aponta para o maior n� a partir do lugar que passou como refer�ncia.
		(*raiz)->dado = p->dado; // Copia os dados do n� maior (p) para o n� que quer excluir (raiz). Depois disso, os dados de p estar�o dobrados.    
		excluir(&((*raiz)->esq), p->dado.codigo); 
		return 1; 
	}
	if (cod < (*raiz)->dado.codigo) { // esquerda
		retorno = excluir(&((*raiz)->esq), cod); 
		balancearAVL(raiz);
		return retorno;
	} 
	// direita
	retorno = excluir(&((*raiz)->dir), cod);
	balancearAVL(raiz);
	return retorno;
}

// *** Destruir ***************************************************************
// Destruir tem a mesma l�gica do caminhamento em P�s Ordem.
void destruir(struct tNo **raiz) { 
	if ((*raiz) == NULL) { 
		return; 
	}
	destruir (&((*raiz)->esq)); // Anda o lado esquerdo todo da �rvore
	destruir (&((*raiz)->dir)); // Anda o lado direito todo da �rvore
	// & pois est� passando por refer�ncia
	free(*raiz); 
}

// *** Realiza o balanceamento, se necess�rio *********************************
void balancearAVL(struct tNo **raiz) {
	int fator = fb(*raiz);
	
	if ((fator == 2) || (fator == -2)) { // A �rvore est� desbalanceada nesse n� em particular.
		// A partir de agora, detecta que tipo de rota��o ir� fazer.
		if ((fator == -2) && (fb((*raiz)->esq) == -1)) { // Simples direita
			rotacaoSD(&*raiz); // ou rotacaoSD(raiz); por raiz j� ser uma refer�ncia dentro da fun��o
		}
		if ((fator == 2) && (fb((*raiz)->dir) == 1)) { // Simples esquerda
			rotacaoSE(&*raiz);
		} 
		if ((fator == -2) && (fb((*raiz)->esq) == 1)) { // Dupla direita
			rotacaoSE(&((*raiz)->esq)); // A primeira rota��o � com o filho � esquerda do raiz
			rotacaoSD(&*raiz); // depois faz a rota��o no pai, ou raiz 
		}
		if ((fator == 2) && (fb((*raiz)->dir) == -1)) { // Dupla esquerda
			rotacaoSD(&((*raiz)->dir)); // A primeira rota��o � com o filho � direita do raiz
			rotacaoSE(&*raiz);
		}
	}
}
