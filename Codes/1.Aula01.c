// Sintese
//   objetivo "LSE - Lista Simplesmente Encadeada"
//   autor "Edson F. da Fonseca"
//   data "24/02/2020"
#include <stdio.h>
#include <stdlib.h>

//*** Declaracoes de tipos *****************************************************
struct tProduto {
	int codigo; // chave de ordenacao
	char descricao[30];
	float valor;
};

struct tNo {
	struct tProduto dado;
	struct tNo *prox;
};

//*** Prototipos de funcoes ****************************************************
int menu(void);
void incluir(struct tNo **, struct tNo *);
void listar(struct tNo *);

//*** Bloco Principal **********************************************************
int main(void) {
	struct tNo *lista=NULL, *p;
	int opcao, codigo;
	do {
        opcao = menu();
        switch (opcao) {
               case 1: 
                    printf("\n\n*** Inclusao ***\n\n");
                    p = malloc(sizeof(struct tNo)); // Criar um no
                    printf("Digite o codigo...: ");
                    scanf("%d", &(p->dado.codigo));
                    printf("Digite a descricao: ");
                    fflush(stdin);
                    gets(p->dado.descricao);
                    incluir(&lista, p); // Incluir o no com produto criado na lista
	                break;
               case 2: 
                    printf("\n\n*** Consulta ***\n\n");
                    printf("Digite o codigo: ");
                    scanf("%d", &codigo);
                    // Pesquisar um produto com este codigo
	                break;
               case 3: 
                    printf("\n\n*** Listagem ***\n\n");
                    listar(lista); // Listar (mostrar na tela) todos os produtos
	                break;
               case 4: 
                    printf("\n\n*** Alteracao ***\n\n");
                    // Consultar pelo codigo e, caso encontre, permitir
					// alterar apenas a descricao.
					// Nao a codigo, pois � chave!
	                break;
               case 5: 
                    printf("\n\n*** Exclusao ***\n\n");
                    // Consultar pelo codigo e, caso encontre, excluir o no da lista.
	                break;
        }
    } while (opcao != 0);
	return 0;
}

//*** Menu *********************************************************************
int menu(void) {
    int op;
    printf("\n\n*** MENU ***\n\n");
    printf("1. Inclusao\n");
    printf("2. Consulta\n");
    printf("3. Listagem\n");
    printf("4. Alteracao\n");
    printf("5. Exclusao\n");
    printf("0. Sair\n\n");
    printf("Escolha sua opcao: ");
    scanf("%d", &op);
    return op;
}

//*** Inclusao *****************************************************************
void incluir(struct tNo **lst, struct tNo *novo) {
	struct tNo *p = (*lst), *q;
	if ((*lst) == NULL) { // Lista vazia
		novo->prox = NULL;
		(*lst) = novo;
	}
	else { // inicio, fim ou meio
		if (novo->dado.codigo < (*lst)->dado.codigo) { // inicio
			novo->prox = (*lst);
			(*lst) = novo;
		}
		else { // fim ou meio
			while (p->prox != NULL)
				p = p->prox;
			if (novo->dado.codigo > p->dado.codigo) { // fim
				p->prox = novo;
				novo->prox = NULL;
			}
			else { // meio
				p = (*lst);
				while (p->dado.codigo < novo->dado.codigo) {
					q = p;
					p = p->prox;
				}
				q->prox = novo;
				novo->prox = p;
			}
		}
	}
}

//*** Listagem *****************************************************************
void listar(struct tNo *lst) {
	struct tNo *p = lst;
	while (p != NULL) {
		printf("%d - %s\n", p->dado.codigo, p->dado.descricao);
		p = p->prox;
	}
}

//*** FIM **********************************************************************
