//
// Exercicio Lista 1 -  Estruturas de Dados - Fabricio Trennepohl
//
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
    struct aluno *next;
};
typedef struct aluno Aluno;

void insList(Aluno **f){
    Aluno *aux, *new;
    new = (Aluno *) malloc(sizeof(Aluno));
    scanf("%s", new->matricula);
    scanf("%s", new->nome);
    scanf("%d/%d/%d", &new->nascimento.dia, &new->nascimento.mes, &new->nascimento.ano);
    scanf("%f", &new->media);
    if (*f == NULL){ 
        *f = new;
        return;
    }
    for (aux = *f; aux != NULL; aux = aux->next){
        if (aux->next == NULL){
            aux->next = new;
            return;
        }
    }
    return;
}

void delList(Aluno **f){
    if (*f == NULL){
        printf("Lista Vazia!\n");
        return;
    }
    Aluno *aux, *prev = *f;
    char v[10];
    scanf("%s", v);
    for (aux = *f; aux != NULL; aux = aux->next){
        if (strcmp(aux->matricula, v) == 0){
            if (aux == *f){
                *f = aux->next;
                free(aux);
                return;
            }
            prev->next = aux->next;
            free(aux);
            return;
        }
        prev = aux;
    }
    return;
}

void prntList(Aluno *f){
    Aluno *aux;
    if (f == NULL){
        printf("Lista Vazia!\n");
    }
    for (aux = f; aux != NULL; aux = aux->next){
        printf("%s, %s, %d/%d/%d, %.2f\n", aux->matricula, aux->nome, aux->nascimento.dia, aux->nascimento.mes, 
        aux->nascimento.ano, aux->media);
    }
    return;
}

void revprntList(Aluno *f){
    void revprnt(Aluno *f){
        if (f == NULL) return;
        revprnt(f->next);
        printf("%s, %s, %d/%d/%d, %.2f\n", f->matricula, f->nome, f->nascimento.dia, f->nascimento.mes, 
        f->nascimento.ano, f->media);
    }
    if (f == NULL){
        printf("Lista Vazia!\n");
        return;
    } else {
        revprnt(f);
        return;
    }
}

void lenList(Aluno *f){
    int num = 0;
    for (; f != NULL; f = f->next){
        num++;
    }
    printf("%d\n", num);
    return;
}

void freeMem(Aluno *f){
    Aluno *aux, *prev;
    int i, count = 0;
    for (aux = f; aux != NULL; aux = aux->next){
        if (aux != f) free(prev);
        prev = aux;
        count++;
    }
    for (i = 0; i < count; i++) printf("-");
}

int main(){
    Aluno *head=NULL;
    int opt;
    while (opt != 0){ //Opção 0: Sair do programa
        scanf("%d", &opt);
        switch (opt){
            case 1: //Opção 1: Incluir elemento na lista
                insList(&head);
                break;
            case 2: //Opção 2: Excluir elemento da lista
                delList(&head);
                break;
            case 3: //Opção 3: Listar todos os elementos da lista na ordem de inclusão
                prntList(head);
                break;
            case 4: //Opção 4: Listar todos os elementos da lista na ordem inversa a inclusão
                revprntList(head);
                break;
            case 5: //Opção 5: Apresentar quantos elementos existem na lista
                lenList(head);
                break;
            default:
                break;
        }
    }
    freeMem(head);
    return 0;
}
