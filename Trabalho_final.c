#include <stdio.h>
#include <stdlib.h>

typedef struct product {
    int code, qt_stock;
    char name[30];
    float price;
    struct product *next, *prev;
} Product;

typedef struct {
    Product *head, *tail;
} LProduct;

typedef struct cart {
    int codeprod;
    int qt_buy;
    struct cart *next, *prev;
} Cart;

typedef struct {
    Cart *head, *tail;
} LCart;

void insItem(LProduct *l)
{
    Product *new, *aux;
    new = (Product *) malloc(sizeof(Product));
    while(1){
    printf("Code: ");
    scanf("%d", &new->code);
    if (new->code > 0) break;
    else printf("Code must be greater than 0.\n");
    }
    printf("Name: ");
    scanf("%s", new->name);
    printf("Price: ");
    scanf("%f", &new->price);
    printf("Number in stock: ");
    scanf("%d", &new->qt_stock);
    printf("\n");
    if (l->head == NULL){
        l->head = new;
        l->tail = new;
        return;
    }
    if (new->code == l->head->code || new->code == l->tail->code){
        printf("Item with code %d already exists.\n", new->code);
        return;
    }
    if (new->code < l->head->code){
        new->next = l->head;
        l->head = new;
        return;
    }
    else if (new->code > l->tail->code){
        l->tail->next = new;
        new->prev = l->tail;
        l->tail = new;
        return;
    }
    else {
        for (aux = l->head; aux != NULL; aux = aux->next){
            if (new->code == aux->code){
                printf("Item with code %d already exists.\n", new->code);
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
}

void prntList(Product *h)
{
    Product *aux;
    if (h == NULL) printf("List is empty.\n");
    for (aux = h; aux != NULL; aux = aux->next)
        printf("Item code: %d, Name: %s, Price: %.2f, Qnt. in stock: %d;\n", aux->code, aux->name, aux->price, aux->qt_stock);
    printf("\n");
    return;
}

Product * searchItem(Product *h)
{
    int targ;
    Product *aux;
    printf("Item code: ");
    scanf("%d", &targ);
    printf("\n");
    for (aux = h; aux != NULL; aux = aux->next)
        if (aux->code == targ){
            return aux;
        }
    printf("Item not found.\n\n");
    aux = NULL;
    return aux;
}

void delItem(LProduct *l)
{
    if (l->head == NULL){
        printf("List is empty!\n\n");
        return;
    }
    Product *aux;
    int target;
    printf("Item code: ");
    scanf("%d", &target);
    printf("\n");
    for (aux = l->head; aux != NULL; aux = aux->next){
        if (aux->code == target){
            if (aux == l->head){
                l->head = aux->next;
                if (l->head != NULL) l->head->prev=NULL;
            } else if (aux == l->tail){
                l->tail = l->tail->prev;
                if (l->tail != NULL) l->tail->next = NULL;
            } else{
                aux->next->prev = aux->prev;
                aux->prev->next = aux->next;
            }
            free(aux);
            return;
        }
    }
    printf("Item not found.\n");
    return;
}

int isCartEmpty(Cart *c)
{
    if (c == NULL) return 1;
    else return 0;
}

void purchaseTotal(Cart *c, Product *l)
{
    Product *aux = l;
    Cart *c_aux = c;
    float total = 0;
    for (aux = l; aux != NULL; aux = aux->next){
        for (c_aux = c; c_aux != NULL; c_aux = c_aux->next){
            if (c_aux->codeprod == aux->code) total += (aux->price * c_aux->qt_buy);
        }
    }
    printf("\n");
    for (int i = 0; i < 51; i++) printf("=");
    printf("\n");
    printf("Total: %.2f\n", total);
    printf("\n");
    return;
}

void prntCart(Cart *c, Product *l)
{
    if (isCartEmpty(c)){
        printf("Cart is empty.\n");
        return;
    }
    Cart *aux;
    Product *laux;
    for (aux = c; aux != NULL; aux = aux->next){
        for(laux = l; laux != NULL; laux = laux->next){
            if (aux->codeprod == laux->code){
                printf("Code: %d, Name: %s, Price: %.2f, Qnt. in stock: %d, Bought: %d;\n",
                aux->codeprod, laux->name, laux->price, laux->qt_stock, aux->qt_buy);
            }
        }
    }
    if (!isCartEmpty(c)) purchaseTotal(c, l);
    return;
}

void addToCart(LCart *c, LProduct *l)
{
    Cart *aux, *new;
    Product *getItem = searchItem(l->head);
    if (getItem == NULL) return;
    if (getItem->qt_stock == 0){
        printf("Item out of stock.\n\n");
        return;
    }
    new = (Cart *) malloc(sizeof(Cart));
    new->codeprod = getItem->code;
    int qnt;
    printf("Quantity: ");
    scanf("%d", &qnt);
    printf("\n");
    if (qnt <= getItem->qt_stock) new->qt_buy = qnt;
    else{
    printf("Quantity exceeds item stock.\n\n");
    return;
    }
    for (aux = c->head; aux != NULL; aux = aux->next){
        if (aux->codeprod == new->codeprod){
            if ((aux->qt_buy + qnt) <= getItem->qt_stock) aux->qt_buy += qnt;
            else printf("Quantity exceeds item stock.\n\n");
            return;
        }
    }
    if (c->head == NULL){
        c->head = new;
        c->tail = new;
        prntCart(c->head, l->head);
        return;
    }
    if (new->codeprod < c->head->codeprod){
        c->head->prev = new;
        new->prev = NULL;
        new->next = c->head;
        c->head = new;
        prntCart(c->head, l->head);
        return;
    } else if (new->codeprod > c->tail->codeprod){
        c->tail->next = new;
        new->prev = c->tail;
        new->next = NULL;
        c->tail = new;
        prntCart(c->head, l->head);
        return;
    }
    for (aux = c->head; aux != NULL; aux = aux->next){
        if (new->codeprod < aux->codeprod && new->codeprod > aux->prev->codeprod){
            new->prev = aux->prev;
            new->next = aux;
            aux->prev->next = new;
            aux->prev = new;
            prntCart(c->head, l->head);
            return;
        }
    }
    return;
}

void delCartItem(LCart *c, int target)
{
    Cart *aux;
    if (target == c->head->codeprod){
        aux = c->head;
        c->head = c->head->next;
        if (c->head != NULL) c->head->prev = NULL;
    } else if (target == c->tail->codeprod){
        aux = c->tail;
        c->tail = c->tail->prev;
        if (c->tail != NULL) c->tail->next = NULL;
    } else{
        for (aux = c->head; aux != NULL; aux = aux->next){
            if (aux->codeprod == target){
                aux->prev->next = aux->next;
                aux->next->prev = aux->prev;
                break;
            }
        }
    }
    free(aux);
    return;
}

void rmCartItem(LCart *c, LProduct *l)
{
    if (isCartEmpty(c->head)){
        printf("Cart is empty.\n");
        return;
    }
    int target, qnt;
    printf("Item code: ");
    scanf("%d", &target);
    printf("\n");
    printf("Quantity: ");
    scanf("%d", &qnt);
    printf("\n");
    Cart *aux;
    for (aux = c->head; aux != NULL; aux = aux->next){
        if (aux->codeprod == target){
            if (qnt > aux->qt_buy){
                printf("Quantity exceeds number of bought items.\n");
                return;
            }
            aux->qt_buy -= qnt;
            if (aux->qt_buy == 0) delCartItem(c, target);
            prntCart(c->head, l->head);
            return;
        }
    }
    printf("Item not found.\n\n");
    return;
}

void checkout(LCart *c, LProduct *l)
{
    prntCart(c->head, l->head);
    Cart *aux;
    Product *laux;
    for (aux = c->head; aux != NULL; aux = aux->next){
        for(laux = l->head; laux != NULL; laux = laux->next){
            if (aux->codeprod == laux->code) laux->qt_stock -= aux->qt_buy;
        }
    }
    while (1){
        if (c->head != NULL) delCartItem(c, c->head->codeprod);
        else break;
    }
    return;
}

void freeMem(Product *l, Cart *c)
{
    if (l != NULL){
        Product *aux, *prev = l;
        for (aux = (l)->next; aux != NULL; aux = aux->next){
            free(prev);
            prev = aux;
        }
        free(aux);
    }
    if (c != NULL){
        Cart *c_aux, *c_prev = c;
        for (c_aux = (c)->next; c_aux != NULL; c_aux = c_aux->next){
            free(c_prev);
            c_prev = c_aux;
        }
        free(c_aux);
    }
    return;
}

void cartMenu(LProduct *l, LCart *c)
{
    int opt = 0;
    while (1){
        printf("1. Buy item\n2. Remove items\n3. List items\n4. Checkout\n=> ");
        scanf("%d", &opt);
        printf("\n");
        switch (opt){
            case 1:
                addToCart(c, l);
                break;
            case 2:
                rmCartItem(c, l);
                break;
            case 3:
                prntCart(c->head, l->head);
                break;
            case 4:
                checkout(c, l);
                return;
                break;
            default:
                printf("Invalid input.\n");
                break;
        }
    } 
}

void mainMenu(LProduct *l, LCart *c)
{
    int opt = 0;
    Product *item;
    while (1){
        printf("1. Add item\n2. List items\n3. Search for item\n4. Delete items\n5. Buy\n6. Exit\n=> ");
        scanf("%d", &opt);
        printf("\n");
        switch (opt){
            case 1:
                insItem(l);
                break;
            case 2:
                prntList(l->head);
                break;
            case 3:
                item = searchItem(l->head);
                if (item != NULL) printf("Code: %d, Name: %s, Price: %f, Qnt. in stock: %d;\n", item->code, item->name, item->price, item->qt_stock);
                printf("\n");
                break;
            case 4:
                delItem(l);
                break;
            case 5:
                cartMenu(l, c);
                break;
            case 6:
                freeMem(l->head, c->head);
                return;
            default:
                printf("Invalid input.\n");
                break;
        }
    }
    return;
}

int main()
{
    LProduct list = {NULL, NULL};
    LCart cart = {NULL, NULL};
    mainMenu(&list, &cart);
    return 0;
}