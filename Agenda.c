#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct date {
    int d, m, y;
} Date;

typedef struct contact{
    char name[30];
    Date bdate;
    char email[40];
    char phone[15];
    struct contact *next, *prev;
} Contact;

typedef struct node{
    Contact info;
    struct node *left, *right;
    int height;
} Node;

Node * newNode()
{
    Contact data;
    printf("Name: ");
    scanf("%s", data.name);
    // printf("\n");
    // printf("Birth date (dd/mm/yyyy): ");
    // scanf("%d %d %d", &data.bdate.d, &data.bdate.m, &data.bdate.y);
    // printf("\n");
    // printf("Email: ");
    // scanf("%s", data.email);
    // printf("\n");
    // printf("Phone: ");
    // scanf("%s", data.phone);
    // printf("\n");
    //
    Node *new = malloc(sizeof(Node));
    new->info = data;
    new->left = NULL;
    new->right = NULL;
    new->height = 1;
    return new;
}

void prntTree(Node *root)
{
    if (root == NULL){
        printf("\n"); 
        return;
    }
    prntTree(root->left);
    printf("%s", root->info.name);
    prntTree(root->right);
}

int getHeight(Node *root){
    if(N == NULL) return 0;
    return(root->height);
}

Node * insNode(Node *root, Node *new)
{
    if (root == NULL) return new;
    if (strcmp(new->info.name, root->info.name) < 0) root->left = insNode(root->left, new);
    else if root->right = insNode(root->right, new);
    else return root;
}

int maxHeight(int h1, int h2){
    if(h1>h2) return h1;
    return h2;
}

int heightL(Node *root){
    if (root == NULL) return 0;
    return 1+heightL(root->left);
}

int heightR(Node *root){
    if(root==NULL) return 0;
    return 1+heightR(root->right);
}

int getHeight(Node *root){
    if(root==NULL) return 0;
    return maxHeight(heightL(root->left), heightR(root->right));
}

int balance(Node *root){
    if(root==NULL) return 0;
    return getHeight(root->left - root->right);
}

Node * rotationRight(Node *root){
    Node *aux = root->left->right;
    root->left->right = root;
    root->left = aux;

    root->height = getHeight(root);
    root->left->height getHeight(root->left);

    return root->left;
}

Node * rotationLeft(Node *root){
    Node *aux = root->right->left;
    root->right->left = root;
    root->right = aux;

    root->height = getHeight(root);
    root->left->height getHeight(root->left);

    return root->right;
}

Node * insertNode(Node *root){
    if(root == NULL) return 
}

/*
void delNode(Node *root, int targ)
{   
    // Search node
    int found = 0;
    Node *aux = root;
    while (aux != NULL){
        if (aux->info->code == targ){
            root = aux;
            found = 1;
            break;
        }
        if (targ < root->info->code) aux = aux->left;
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
        if (root->info->code - big->info->code < small->info->code - root->info->code){
            root = big;
            big = NULL;
        }
        else{
            root = small;
            small = NULL;
        }
    }
    return;
} */

int main()
{
    Node *root = NULL;
    for (int i=0; i<3; i++){
        if (root == NULL) root = insNode(root, newNode());
        else insNode(root, newNode());
    }
    prntTree(root);
    balanceFactor(root->left);
    balanceFactor(root->right);
    return 0;
}