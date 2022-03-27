#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char addr[60];
    struct node *next;
};
typedef struct node Node;

struct stack {
    Node *top;
};
typedef struct stack Stack;

void initStack(Stack *s){
    s->top = NULL;
    return;
}

void insNode(Stack *s, char *v){
    Node *aux;
    aux = malloc(sizeof(Node));
    strcpy(aux->addr, v);
    aux->next = s->top;
    s->top = aux;
    return;
}

void rmNode(Stack *s){
    if (s->top == NULL){
        printf("Vazio\n");
        return;
    }
    Node *aux = s->top;
    printf("%s\n", s->top->addr);
    s->top = s->top->next;
    free(aux);
    return;
}

void freeStack(Stack *s){
    if (s->top == NULL){
        printf("!");
        return;
    }
    Node *aux;
    while (s->top != NULL){
        aux = s->top;
        s->top = s->top->next;
        printf("@");
        free(aux);
    }
    printf("\n");
    return;
}

void input(Stack *s){
    char v[60];
    while (1){
        scanf("%s", v);
        if (strcmp(v, "B") == 0){
            rmNode(s);
        } else if (strcmp(v, "E") == 0) {
            freeStack(s);
            return;
        } else {
            insNode(s, v);
        }
    }
}

int main(){
    Stack s;
    initStack(&s);
    input(&s);
    return 0;
}