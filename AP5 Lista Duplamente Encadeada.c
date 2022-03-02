#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data{
    int dia, mes, ano;
};
typedef struct data Data;

struct aluno{
    char matricula[10], nome[40];
    Data nascimento;
    float media;
    struct aluno *prev;
    struct aluno *next;
};
typedef struct aluno Aluno;

void insList(Aluno **f, Aluno **t){
    Aluno *aux, *new;
    char targ[10];
    new = (Aluno *) malloc(sizeof(Aluno));
    scanf("%s", targ);
    scanf("%s", new->matricula);
    scanf("%s", new->nome);
    scanf("%d/%d/%d", &new->nascimento.dia, &new->nascimento.mes, &new->nascimento.ano);
    scanf("%f", &new->media);
    if (*f == NULL){ 
        *f = new;
        *t = new;
        return;
    }
    for (aux = (*f)->next; aux != NULL; aux = aux->next){
        if (strcmp(aux->matricula, targ) == 0){
            new->next = aux;
            new->prev = aux->prev;
            new->prev->next = new;
            aux->prev = new;
            return;
        }
    }
    new->next = *f;
    new->next->prev = new;
    *f = new;
    return;
}

void delList(Aluno **f, Aluno **t){
    if (*f == NULL){
        printf("Lista Vazia!\n");
        return;
    }
    Aluno *aux;
    char targ[10];
    scanf("%s", targ);
    for (aux = *f; aux != NULL; aux = aux->next){
        if (strcmp(aux->matricula, targ) == 0){
            if (aux == *f){
                *f = aux->next;
                (*f)->prev=NULL;
            } else if (aux == *t){
                *t = aux->prev;
                (*t)->next = NULL;
            } else{
            aux->next->prev = aux->prev;
            aux->prev->next = aux->next;
            }
            free(aux);
            return;
        }
    }
    return;
}

void prntList(Aluno *f){
    Aluno *aux;
    if (f == NULL) printf("Lista Vazia!\n");
    for (aux = f; aux != NULL; aux = aux->next)
        printf("%s, %s, %d/%d/%d, %.2f\n", aux->matricula, aux->nome, aux->nascimento.dia, aux->nascimento.mes, 
        aux->nascimento.ano, aux->media);
    return;
}

void revprntList(Aluno *t){
    void revprnt(Aluno *t){
        Aluno *aux;
        for (aux = t; aux != NULL; aux = aux->prev)
            printf("%s, %s, %d/%d/%d, %.2f\n", aux->matricula, aux->nome, aux->nascimento.dia, aux->nascimento.mes, 
            aux->nascimento.ano, aux->media);
    }
    if (t == NULL){
        printf("Lista Vazia!\n");
        return;
    }
    revprnt(t);
    return;
}

void lenList(Aluno *f){
    int num = 0;
    for (; f != NULL; f = f->next) num++;
    printf("%d\n", num);
    return;
}

void freeMem(Aluno **f){
    Aluno *aux, *prev;
    for (aux = *f; aux != NULL; aux = aux->next){
		if (aux->next != NULL){
			free(prev);
			printf("*");
		} else{
			free(aux);
			printf("*");
			return;
		}
        prev = aux;
    }
}

int main(){
    Aluno *head=NULL, *tail=NULL;
    int opt=1;
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
    freeMem(&head);
    return 0;
}
