// Sintese
// Objetivo "Arvore"
// autor "Edson F. da Fonseca

// *** grau ***********************************************************************
int grau(struct tNo *raiz) {
	if ((raiz->esq == NULL) && (raiz->dir == NULL)) {
		return 0;
	}
	if ((raiz->esq != NULL) && (raiz->dir != NULL)) {
		return 2;
	}
	return 1;
}

// *** menor **********************************************************************
struct tNo *menor (struct tNo *raiz) {
	if ((raiz == NULL) || (raiz->esq == NULL)) {
		return raiz;
		// Se raiz->esq == NULL, é porque raiz não tem um filho à esquerda.
		// Nunca compara um valor com outro, pois não precisa. Faz uso do conceito da própria estrutura de dados.
	}
	menor(raiz->esq); 
}
// O menor elemento de uma árvore será o elemento que está mais à esquerda de todos.

// *** maior **********************************************************************
struct tNo *maior (struct tNo *raiz) {
	if ((raiz == NULL) || (raiz->dir == NULL)) {
		return raiz;
	}
	maior(raiz->dir); 
}
// O maior elemento de uma árvore será o elemento que está mais à direita de todos.

// *** altura **********************************************************************
int altura(struct tNo *raiz) {
	// Distância do nó em relação à folha mais distante
	int e, d;
	if (raiz == NULL) { // descobre se o nó é folha
		return -1;
	}	
	e = altura(raiz->esq);
	d = altura(raiz->dir);
	if (e > d) {
		return e+1;
	}
	return d+1;
}

// *** Profundidade *****************************************************************
// Profundidade: distância medida em nível do nó até a raiz
void nivel(struct tNo *raiz, struct tNo *no, int *n){
	if(raiz->esq == NULL)
		return ;
	if(raiz->dir == NULL)
		return ;	
	if(raiz->esq != no)
		nivel(raiz->esq, no, n);
	else if(raiz->dir != no)
			nivel(raiz->dir, no, n);
	*n = *n + 1;
}

// *** Verificação folha *************************************************************
int folha(struct tNo *no){
	int flag;
	if((no->dir != NULL) || (no->esq != NULL))
		flag = 1;
	else
		flag = 0;
	return flag;
}
