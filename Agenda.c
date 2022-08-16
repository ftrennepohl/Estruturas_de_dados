#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT 10

typedef struct {
	int day;
	int month;
	int year;
} Date;

struct MREC {
    char name[30];
    Date  birth; 
    char email[40];
    char phone[15];
    struct MREC *left;
    struct MREC *right;
}; 

typedef struct MREC Contact;

// Funções auxiliares


int getHeight(Contact *root){
    if (root == NULL)
        return 0;
    if (getHeight(root->left) > getHeight(root->right)) return 1 + getHeight(root->left);
    return 1 + getHeight(root->right);
}

int getBalance(Contact *root){
    if (root == NULL)
        return 0;
    return getHeight(root->left) - getHeight(root->right);
}

Contact *RRrotation(Contact *root) {
  Contact *newRoot = root->left, *aux = newRoot->right;

  newRoot->right = root;
  root->left = aux;

  return newRoot;
}

Contact *LLrotation(Contact *root) {
  Contact *newRoot = root->right, *aux = newRoot->left;

  newRoot->left = root;
  root->right = aux;

  return newRoot;
}

Contact *newContact(){
    Contact *new = malloc(sizeof(Contact));
    printf("Nome: ");
    scanf("%s", new->name);
    printf("Nascimento: (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &new->birth.day, &new->birth.month, &new->birth.year);
    printf("Email: ");
    scanf("%s", new->email);
    printf("Telefone: ");
    scanf("%s", new->phone);
    new->left = NULL;
    new->right = NULL;
    return new;
}

char *getTarget(){
    char *targetName = malloc(30 * sizeof(char));
    printf("Nome do contato: ");
    scanf("%s", targetName);
    printf("\n");
    return targetName;
}

//

Contact *insContact(Contact *root, Contact *new){
    if (root == NULL) return new;
    if (strcmp(new->name, root->name) < 0) root->left = insContact(root->left, new);
    else if (strcmp(new->name, root->name) > 0) root->right = insContact(root->right, new);
    else return root;

    int balance = getBalance(root);

    // Lado esquerdo tem altura maior e nova chave < chave raiz->esquerda (Caso LL)
    if(balance > 1 && strcmp(new->name, root->left->name) < 0) return RRrotation(root);

    // Lado direito tem altura maior e nova chave > chave raiz->direita (Caso RR)
    if(balance < -1 && strcmp(new->name, root->right->name) > 0) return LLrotation(root);

    // Lado esquerdo tem altura maior e nova chave > chave raiz->esquerda (Caso LR)
    if(balance > 1 && strcmp(new->name, root->left->name) > 0){
        root->left = LLrotation(root->left);
        return RRrotation(root);
    }
    // Lado direito tem altura maior e nova chave < chave raiz->direita (Caso RL)
    if(balance < -1 && strcmp(new->name, root->right->name) < 0){
        root->right = RRrotation(root->right);
        return LLrotation(root);
    }
    return root;
}

Contact *minContact(Contact *root) {
  Contact *aux = root;
  while (aux->left != NULL) aux = aux->left;

  return aux;
}

Contact *delContact(Contact *root, char *targetName){
    if (root == NULL) return root;
    if (strcmp(targetName, root->name) < 0) root->left = delContact(root->left, &(*targetName));
    else if (strcmp(targetName, root->name) > 0) root->right = delContact(root->right, &(*targetName));
    else{
        Contact *aux;
        if((root->left == NULL) || (root->right == NULL)){
            if (root->left != NULL) aux = root->left; else aux = root->right;
            if(aux == NULL){ // Sem filhos, exclui o nó
                root = NULL;
                aux = root;
            }
            else *root = *aux; // Ao menos um filho, troca com o filho e exclui o nó
            free(aux);
        }else{ // Dois filhos, substitui o nó atual pelo menor nó da subarvore direita e exclui este
            aux = minContact(root->right);
            strcpy(root->name, aux->name);
            strcpy(root->email, aux->email);
            strcpy(root->phone, aux->phone);
            root->birth.day = aux->birth.day;
            root->birth.month = aux->birth.month;
            root->birth.year = aux->birth.year;
            root->right = delContact(root->right, aux->name);
        }
    }

    if (root == NULL) return root;

    int balance = getBalance(root);

    // Caso LL: profundidade >= 2 para a esquerda
    if (balance > 1 && getBalance(root->left) >= 0) return RRrotation(root);

    // Caso RR: profundidade >= 2 para a direita
    if (balance < -1 && getBalance(root->right) <= 0) return LLrotation(root);

    // Caso LR: fator de balanceamento positivo, raiz->esquerda->direita
    if (balance > 1 && getBalance(root->left) < 0){
        root->left = LLrotation(root->left);
        return RRrotation(root);
    }

    // Caso RL: fator de balanceamento negativo, raiz->direita->esquerda
    if (balance < -1 && getBalance(root->right) > 0){
        root->right = RRrotation(root->right);
        return LLrotation(root);
    }

    return root;
}

void upContact(Contact *root, char *name){
    if(root == NULL){
        printf("Contato não encontrado.\n");
        return;
    }
    if(strcmp(name, root->name) < 0) upContact(root->left, name);
    else if(strcmp(name, root->name) > 0) upContact(root->right, name);
    else{
        printf("Nome: ");
        scanf("%s", root->name);
        printf("Data de nascimento: ");
        scanf("%d/%d/%d", &root->birth.day, &root->birth.month, &root->birth.year);
        printf("Email: ");
        scanf("%s", root->email);
        printf("Telefone: ");
        scanf("%s", root->phone);
        return;
    }
}

void queryContact(Contact *root, char *name){
    if(root == NULL){
        printf("Contato não encontrado.\n");
        return;
    }
    if(strcmp(name, root->name) < 0) queryContact(root->left, name);
    else if(strcmp(name, root->name) > 0) queryContact(root->right, name);
    else{
        printf("Nome: %s\nData de nascimento: %d/%d/%d\nEmail: %s\nTelefone: %s\n",
        root->name, root->birth.day, root->birth.month, root->birth.year,
        root->email, root->email);
        return;
    }

}

void listContacts(Contact *root){
    if (root == NULL) return;
    listContacts(root->left);
    printf("Nome: %s\nData de nascimento: %d/%d/%d\nEmail: %s\nTelefone: %s\n\n",
        root->name, root->birth.day, root->birth.month, root->birth.year,
        root->email, root->phone);
    listContacts(root->right);
}

int menu(){
    int op = 0;
    printf("\n");
    for(int i = 0; i< 40; i++) printf("=");
    printf("\n");
    printf(" %2d - Inserir cliente\n", 1);
    printf(" %2d - Deletar cliente\n", 2);
    printf(" %2d - Atualizar dados de cliente\n", 3);
    printf(" %2d - Buscar cliente\n", 4);
    printf(" %2d - Mostrar agenda completa\n", 5);
    printf(" %2d - Salvar e sair\n", EXIT);
    for(int i = 0; i< 40; i++) printf("=");
    printf("\n\n: ");
    scanf("%d",&op);
    printf("\n");
    return op;
}


void saveData(Contact *root, FILE *f){
    if (root == NULL) return;
    saveData(root->left, f);
    fprintf(f, "%s %d/%d/%d %s %s\n", root->name, root->birth.day, root->birth.month,
    root->birth.year, root->email, root->email);
    saveData(root->right, f);
}

Contact *loadData(FILE *f){
    Contact *root;
    while(1){
        if (feof(f)) return root;
        Contact *new = malloc(sizeof(Contact));
        fscanf(f, "%s  %d/%d/%d  %s %s\n", new->name, &new->birth.day, &new->birth.month, &new->birth.year, new->email, new->phone);
        root = insContact(root, new);
    }
}

int main(){
    int op = 0;
    Contact *root = NULL;

    if(fopen("data.txt", "r") != NULL){
        FILE *data = fopen("data.txt", "r");
        root = loadData(data);
    }

    while (op != EXIT){
        op = menu();
        switch(op){
            case 1 : {
                root = insContact(root, newContact());
                break;
            }
            case 2 : {
                char *target = getTarget();
                root = delContact(root, target);
                free(target);
                break;
            }
            case 3 : {
                char *target = getTarget();
                upContact(root, target);
                free(target);
                break;
            }
            case 4 : {
                char *target = getTarget();
                queryContact(root, target);
                free(target);
                break;
            }
            case 5 : {
                if(root == NULL) printf("Agenda vazia.");
                listContacts(root);
                break;
            }
            case 10: {
                FILE *data = NULL;
                data = fopen("data.txt", "w");
                saveData(root, data);
                printf("Saindo...\n");
                break;
            }
            default : {
                printf("Opção inválida.\n");
                break;
            }
        }
    }
    return 0;
}