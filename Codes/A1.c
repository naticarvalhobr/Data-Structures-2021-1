/*
Síntese: Atividade Avaliativa
Autor: Natália Carvalho
Data: 28/04
*/
#include <stdio.h>
#include <stdlib.h>

struct elementoJ {
  float valor0;
  struct elementoJ *prox;
};

int main () {
	struct elementoJ *lista = NULL, nodo, q;
    int qtd;

    nodo.valor0 = 2;
    nodo.prox = NULL;

    if (((*lst) == NULL) || (novo->dado.codigo < (*lst)->dado.codigo)) { // vazia & inicio
		novo->prox = (*lst); // prox aponta para onde lista esta apontando 
		(*lst) = novo;
	}
	else { // fim, meio
		q = (*lst);
		while ((q->prox != NULL) && (q->prox->dado.codigo < novo->dado.codigo)) { // coloca q no ultimo || no anterior ao n� onde o novo vai entrar
			// Enquanto n�o chegou no ultimo *e* o proximo elemento � menor que o novo elemento
			q = q->prox;
		}
		//q->prox = novo; // q->prox no ultimo elemento vale NULL
		//novo->prox = NULL;
		novo->prox = q->prox;
		q->prox = novo;
		// q e p sempre apontam para n�s
	}

    qtd = iguais (lista, nodo);
    printf("\nQtd: %d\n", qtd);

}

// Escreva uma função em C que receba 
// como parâmetro a lista e um nó e retorne a quantidade de elemento(s) com valores iguais ao daquele nó.

int iguais (struct elementoJ *lst, struct elementoJ no){ 
  struct elementoJ *q = lst;
  int qtd=0;

  while (q != NULL) {
    if (q->valor0 == no.valor0) {
      qtd++;  
    }
    q = q->prox;
  }
  return qtd;
}