#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct product {
    int code, qt_stock;
    char name[30];
    float price;
    struct product *next, *prev;
} Product;

typedef struct {
    Product *head, *tail;
} LProduct;

typedef struct {
    int codeprod;
    int qt_buy;
    Product *next, *prev;
} Cart;


int notEmpty(Product *h)
{
    if (h != NULL) return 1;
    else return 0;
}

/*void initList(LProduct *l)
{
    l->head = NULL;
    l->tail = NULL;
}*/

void insProduct(Product *h, Product *t)
{
    Product *aux, *new;
    new = (Product *) malloc(sizeof(Product));
    printf("Código: \n");
    scanf("%d", &new->code);
    printf("Nome: \n");
    scanf("%s", new->name);
    printf("Preço: \n");
    scanf("%f", &new->price);
    printf("Quantidade em estoque: \n");
    scanf("%d", &new->qt_stock);
    // Product insertion
    if (h == NULL){ 
        h = new;
        t = new;
        return;
    }
    if (new->code == h->code || new->code == t->code){
        printf("Product with code %d already exists!\n", new->code);
        return;
    }
    if (new->code < h->code){
        new->next = h;
        h = new;
        return;
    }
    else if (new->code > t->code){
        t->next = new;
        new->prev = t;
        t = new;
        return;
    }
    else {
        for (aux = h; aux != NULL; aux = aux->next){
            if (new->code == aux->code){
                printf("Product with code %d already exists!\n", new->code);
                break;
            }
            if (new->code < aux->code && new->code > aux->prev->code){
                aux->prev->next = new;
                new->prev = aux->prev;
                aux->prev = new;
                new->next = aux;
            }
        }
        return;
    }
    new->next = h;
    new->next->prev = new;
    h = new;
    return;
}

/*void delList(LProduct *l){
    if (!notEmpty(f)){
        printf("Lista Vazia!\n");
        return;
    }
    LProduct *aux;
    char targ[10];
    scanf("%s", targ);
    for (aux = f; aux != NULL; aux = aux->next){
        if (strcmp(aux->matricula, targ) == 0){
            if (aux == f){
                f = aux->next;
                if (notEmpty(f)) (f)->prev=NULL;
                else t = NULL;
            } else if (aux == t){
                t = aux->prev;
                (t)->next = NULL;
            } else{
                aux->next->prev = aux->prev;
                aux->prev->next = aux->next;
            }
            free(aux);
            return;
        }
    }
    return;
}*/

void prntList(Product *h)
{
    Product *aux;
    if (h == NULL) printf("Lista Vazia!\n");
    for (aux = h; aux != NULL; aux = aux->next)
        printf("%d %s", aux->code, aux->name);
    return;
}

/*void revprntList(LProduct *t){
    if (t == NULL){
        printf("Lista Vazia!\n");
        return;
    }
    for (; t != NULL; t = t->prev)
        printf("%s, %s, %d/%d/%d, %.2f\n", t->matricula, t->nome, t->nascimento.dia, t->nascimento.mes, 
        t->nascimento.ano, t->media);
    return;
}

void freeMem(LProduct *l){
    h = l->head;
    LProduct *aux, *prev = h;
    for (aux = (h)->next; aux != NULL; aux = aux->next){
		free(prev);
		printf("*");
        prev = aux;
    }
    free(aux);
    printf("*");
    return;
}*/

int main()
{
    LProduct *list;
    list->head = NULL;
    list->tail = NULL;
    insProduct(list->head, list->tail);
    prntList(list->head);
    /*int opt=1;
    while (opt != 0){ //Opção 0: Sair do programa
        scanf("%d", &opt);
        switch (opt){
            case 1: //Opção 1: Incluir elemento na lista
                insList(&head, &tail);
                break;
            case 2: //Opção 2: Excluir elemento da lista
                delList(&head, &tail);
                break;
            case 3: //Opção 3: Listar todos os elementos da lista na ordem de inclusão
                prntList(head);
                break;
            case 4: //Opção 4: Listar todos os elementos da lista na ordem inversa a inclusão
                revprntList(tail);
                break;
            case 5: //Opção 5: Apresentar quantos elementos existem na lista
                lenList(head);
                break;
            default:
                break;
        }
    }
    */
    return 0;
}
