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
	struct elementoJ *lista, nodo;
    int qtd;
    
    nodo.valor0 = 2;
    nodo.prox = NULL;

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
