#include <stdio.h>
#include <stdlib.h>

typedef struct product {
    int code, qt_stock;
    char name[30];
    float price;
    struct product *next, *prev;
} Product;

typedef struct node{
    Product *prod;
    struct node *left, *right;
} Node;

Node * createNode()
{
    Product *data = (Product *) malloc(sizeof(Product));
        while(1){
        printf("Code: ");
        scanf("%d", &data->code);
        if (data->code > 0) break;
        else printf("Code must be greater than 0.\n");
    }
    /*printf("Name: ");
    scanf("%s", data->name);
    printf("Price: ");
    scanf("%f", &data->price);
    printf("Number in stock: ");
    scanf("%d", &data->qt_stock);
    printf("\n");*/
    //
    Node *new = (Node *) malloc(sizeof(Node));
    new->prod = data;
    new->left = NULL;
    new->right = NULL;

    return new;
}

Node * insNode(Node *root, Node *new)
{
    if (root == NULL) return new;
    else if (new->prod->code < root->prod->code) root->left = insNode(root->left, new);
    else root->right = insNode(root->right, new);
    return root;
}

void prntTree(Node *root)
{
    if (root == NULL){
        printf("\n"); 
        return;
    }
    prntTree(root->left);
    printf("%d", root->prod->code);
    prntTree(root->right);
}

void delNode(Node *root, int targ)
{   
    // Search node
    int found = 0;
    Node *aux = root;
    while (aux != NULL){
        if (aux->prod->code == targ){
            root = aux;
            found = 1;
            break;
        }
        if (targ < root->prod->code) aux = aux->left;
        else aux = aux->right;
    }
    if (!found){
        printf("Not found");
        return;
    }
    //
    // Get closest element
    Node *big, *small;

    aux = root->left;
    while (1){
        if (aux->right == NULL){
            big = aux;
            break;
        }
        aux = aux->right;
    }

    aux = root->right;
    while (1){
        if (aux->left == NULL){
            small = aux;
            break;
        }
        aux = aux->left;
    }
    //
    // Deletion
    if (root->left == NULL && root->right == NULL) root = NULL;
    else if (root->left != NULL) root = root->left;
    else if (root->right != NULL) root = root->right;
    else {
        if (root->prod->code - big->prod->code < small->prod->code - root->prod->code){
            root = big;
            big = NULL;
        }
        else{
            root = small;
            small = NULL;
        }
    }
    return;
}

int main()
{
    Node *root = NULL;
    for (int i=0; i<10; i++){
        if (root == NULL) root = insNode(root, createNode());
        else insNode(root, createNode());
    }
    delNode(root, 27);
    prntTree(root);
    return 0;
}