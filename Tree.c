#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int code;
    struct node *left, *right;
} Node;

Node * createNode()
{
    // Creates node

    Node *new = (Node *) malloc(sizeof(Node));
    printf("Code: ");
    scanf("%d", &new->code);
    new->left = NULL;
    new->right = NULL;

    return new;
}

Node * insNode(Node *root, Node *new)
{
    // Inserts new node

    if (root == NULL) return new;
    else if (new->code < root->code) root->left = insNode(root->left, new);
    else root->right = insNode(root->right, new);
    return root;
}

void prntTree(Node *root)
{
    // Prints tree in order
    if (root == NULL) return;
    prntTree(root->left);
    printf("%d ", root->code);
    prntTree(root->right);
}

Node ** searchTree(Node **root, int targ)
{
    // Prints and returns address of the node that has code equal to targ

    while (root != NULL){
        if ((*root)->code == targ){
            printf("Product found. Code: %d\n", (*root)->code);
            return root;
        }
        if (targ < (*root)->code) root = &(*root)->left;
        else root = &(*root)->right;
    }
    printf("Product not found.\n");
    return NULL;
}

Node ** findClosest(Node **root)
{
    // Returns address of node with closest code to "root"

    Node **big, **small, **aux;

    aux = &(*root)->left;
    while (1){
        if ((*aux)->right == NULL){
            big = aux;
            break;
        }
        aux = &(*aux)->right;
    }

    aux = &(*root)->right;
    while (1){
        if ((*aux)->left == NULL){
            small = aux;
            break;
        }
        aux = &(*aux)->left;
    }

    printf("Root code: %d\nBig code: %d\nSmall code: %d\n", (*root)->code, (*big)->code, (*small)->code);

    if ((*root)->code - (*big)->code < (*small)->code - (*root)->code) return big;
    else return small;
}

void delNode(Node **root)
{   
    // Deletes node, addressing all the cases (leaf node, single child, two child nodes)

    Node **leaf, **nroot;
    int target;

    printf("Node to be removed: ");
    scanf("%d", &target);
    printf("\n");

    nroot = searchTree(root, target);

    if ((*nroot)->left == NULL && (*nroot)->right == NULL) *nroot = NULL;
    else if ((*nroot)->right == NULL) *nroot = (*nroot)->left;
    else if ((*nroot)->left == NULL) *nroot = (*nroot)->right;
    else {
        leaf = findClosest(nroot);
        (*nroot)->code = (*leaf)->code;
        if ((*leaf)->left != NULL) *leaf = (*leaf)->left;
        else if ((*leaf)->right != NULL) *leaf = (*leaf)->right;
        else{
            leaf = NULL;
            free(*leaf);
        }
        return;
    }
    if (*nroot == NULL) free(*nroot);
    return;
}

int main()
{
    Node *root = NULL;
    for (int i=0; i<10; i++){
        if (root == NULL) root = insNode(root, createNode());
        else insNode(root, createNode());
    }
    printf("\n");
    prntTree(root);
    printf("\n\n");
    delNode(&root);
    printf("\n");
    prntTree(root);
    return 0;
}