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
void excluir(struct tNo **lst, struct tNo *vitima);
void excluir2 (struct tNo **lst, struct tNo *vitima);
	
int main(void) {
	struct tNo *p, *q, *lista;
	int opcao, codigo, qtd = 0;
	
	inicializar(&lista);
	do {
		opcao = menu();
		switch (opcao) {
			case 1:
				printf("\n\n\nInclusao\n");
				p = (struct tNo*) malloc(sizeof(struct tNo)); // p passa a apontar para um novo elemento que vai entrar na lista
				printf("Digite o codigo...: ");
				scanf("%d", &(p->dado.codigo)); //scanf("%d", &((*p).dado.codigo));
				printf("Digite a descricao: ");
				fflush(stdin);
				gets(p->dado.descricao);
				printf("Digite o valor....: ");
				scanf("%f", &(p->dado.valor));	
							
				incluir(&lista, p); // Incluir o n� com produto criado na lista			
				// p = elemento novo
				// lista = aponta para o primeiro elemento
				break;
			case 2:
				printf("\n\n\nListagem\n");
				listar(lista); // Listar (mostrar na tela) todos os produtos
				break;
			case 3:
				printf("\n\n\nConsultar\n");
				printf("Digite o codigo...: ");
				scanf("%d", &codigo);
				// Pesquisar um produto com este codigo

				p = consultar(lista, codigo); // retornar um n� inteiro, quando o encontrar
				if (p == NULL) {
					printf("Codigo nao encontrado!");
				} else {
					printf("Descricao: %s\n", p->dado.descricao);
					printf("Valor....: R$ %.2f", p->dado.valor);
				}
				break;
			case 4:
				printf("\n\n\nAlterar\n");
				printf("Digite o codigo...: ");
				scanf("%d", &codigo);
				p = consultar(lista, codigo);
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
				}
				break;
			case 5:
				printf("\n\n\nExcluir\n");
				printf("Digite o codigo...: ");
				scanf("%d", &codigo);
				p = consultar(lista, codigo);
				if (p == NULL) {
					printf("Codigo nao encontrado!");
				} else {
					printf("Descricao: %s\n", p->dado.descricao);
					printf("Valor....: R$ %.2f\n", p->dado.valor);	
					excluir(&lista, p);
					// lista deve ser passada por refer�ncia pois precisa alter�-la dentro da fun��o				
				}
				// Consultar pelo codigo e, caso encontre, excluir o no da lista.
				break;
			case 6:
				printf("\n\n\nExcluir varios\n");
				p = lista;
				while (p != NULL) {
					if (p->dado.codigo % 2 == 0) {
						excluir2(&lista, p);
					}
				}
		}
	} while (opcao != 0);
	destruir(&lista);
	return 0;
}

// *** menu ***********************************************************************
int menu(void) {
	int opcao;
	printf("\n\n\n*** menu ***\n");
	printf("1. Incluir produto\n");
	printf("2. Listar produtos\n");
	printf("3. Consultar produto\n");
	printf("4. Alterar produto\n");
	printf("5. Excluir produto\n");
	printf("6. Exclusão de vários\n");
	printf("0. Sair\n\n");
	printf("Digite sua opcao: ");
	scanf("%d", &opcao);
	return opcao;
}

// *** Inicializar ****************************************************************
void inicializar(struct tNo **lst) { // ponteiro sendo passado por refer�ncia
	(*lst) = NULL;
}

// *** listar *********************************************************************
void listar(struct tNo *lst) { // ponteiro sendo passado por valor
	struct tNo *p = lst;
	printf("Codigo - Descricao - Valor\n");
	while (p != NULL) {
		printf("%d - %s - %.2f\n", p->dado.codigo, p->dado.descricao, p->dado.valor);
		p = p->prox;				
	}
}

// *** incluir ********************************************************************
void incluir(struct tNo **lst, struct tNo *novo) {
	// um * para indicar que � ponteiro e o outro * para desreferenciar
	struct tNo *q;
	if (((*lst) == NULL) || (novo->dado.codigo < (*lst)->dado.codigo)) { // vazia & inicio
		// Se a lista est� vazia, lst aponta para NULL
		novo->prox = (*lst); // prox aponta para onde lista est� apontando 
		(*lst) = novo;
		// � preciso escrever as duas linhas acima nessa ordem
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
}

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

void excluir2(struct tNo **lst, struct tNo *vitima)
{
	struct tNo *p = (*lst);

	while (p != NULL) {
		if ((*lst) == vitima) 
			(*lst) = vitima->prox;
		else { // meio OU fim
			while (p->prox != vitima) { // coloca p no n� anterior a vitima
				p = p->prox; // p aponta para onde p->prox atualmente est� apontando
			}
			p->prox = vitima->prox;	
		}
		printf("O codigo de valor %d foi excluído.", vitima->dado.codigo);
		free(vitima);
	}

}

// *** Excluir varios *************************************************************
/*void excluir2 (struct tNo **lst, struct tNo *vitima)
{
    // Store head node
    struct tNo *temp = (*lst), *prev;
 
    // If head node itself holds the key or multiple
    // occurrences of key
    while ((*lst) != NULL && *lst->dado == *vitima)
    {
        *lst = temp->prox; // Changed head
        free(temp); // free old head
        temp = (*lst); // Change Temp
    }
 
    // Delete occurrences other than head
    while (temp != NULL)
    {
        // Search for the key to be deleted, keep track of
        // the previous node as we need to change
        // 'prev->next'
        while (temp != NULL && lst->dado != *vitima)
        {
            prev = temp;
            temp = temp->prox;
        }
 
        // If key was not present in linked list
        if (temp == NULL)
            return;
 
        // Unlink the node from linked list
        prev->prox = temp->prox;
 
        free(temp); // Free memory
 
        // Update Temp for next iteration of outer loop
        temp = prev->prox;
    }
}*/

// *** Destruir *******************************************************************
// Libera a memoria ocupada pelos nos da lista
void destruir(struct tNo **lst) {
	struct tNo *p=(*lst), *q;
	while (p != NULL) {
		q = p; // coloca o q em algum lugar que ele morre
		p = p->prox; // salva o p		
		free(q);						
	}
	inicializar(lst);
}
