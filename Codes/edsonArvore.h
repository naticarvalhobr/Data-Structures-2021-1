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
		// Se raiz->esq == NULL, � porque raiz n�o tem um filho � esquerda.
		// Nunca compara um valor com outro, pois n�o precisa. Faz uso do conceito da pr�pria estrutura de dados.
	}
	menor(raiz->esq); 
}
// O menor elemento de uma �rvore ser� o elemento que est� mais � esquerda de todos.

// *** maior **********************************************************************
struct tNo *maior (struct tNo *raiz) {
	if ((raiz == NULL) || (raiz->dir == NULL)) {
		return raiz;
	}
	maior(raiz->dir); 
}
// O maior elemento de uma �rvore ser� o elemento que est� mais � direita de todos.

// *** altura **********************************************************************
int altura(struct tNo *raiz) {
	// Dist�ncia do n� em rela��o � folha mais distante
	int e, d;
	if (raiz == NULL) { // descobre se o n� � folha
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
// Profundidade: dist�ncia medida em n�vel do n� at� a raiz
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

// *** Verifica��o folha *************************************************************
int folha(struct tNo *no){
	int flag;
	if((no->dir != NULL) || (no->esq != NULL))
		flag = 1;
	else
		flag = 0;
	return flag;
}
