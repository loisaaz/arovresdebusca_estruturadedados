#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para um contato
struct Contato {
    char nome[50];
    char celular[15];
    struct Contato* left;
    struct Contato* right;
};

// Função para criar um novo nó
struct Contato* criarNo(char* nome, char* celular) {
    struct Contato* novo = (struct Contato*)malloc(sizeof(struct Contato));
    strcpy(novo->nome, nome);
    strcpy(novo->celular, celular);
    novo->left = NULL;
    novo->right = NULL;
    return novo;
}

// Função para inserir um contato
struct Contato* inserir(struct Contato* raiz, struct Contato* novo) {
    if (raiz == NULL) {
        return novo;
    }
    if (strcmp(novo->nome, raiz->nome) < 0) {
        struct Contato* inserido = inserir(raiz->left, novo);
        if (inserido != NULL) raiz->left = inserido;
    } 
    else if (strcmp(novo->nome, raiz->nome) > 0) {
        struct Contato* inserido = inserir(raiz->right, novo);
        if (inserido != NULL) raiz->right = inserido;
    } 
    else {
        free(novo); // libera memória do nó duplicado
        return NULL;
    }
    return raiz;
}

// Buscar um contato pelo nome
struct Contato* buscar(struct Contato* raiz, const char* nome) {
    if (raiz == NULL || strcmp(raiz->nome, nome) == 0) {
        return raiz;
    }
    if (strcmp(nome, raiz->nome) < 0) {
        return buscar(raiz->left, nome);
    } 
    else {
        return buscar(raiz->right, nome);
    }
}

// Encontrar o menor valor (usado na remoção)
struct Contato* encontrarMin(struct Contato* raiz) {
    struct Contato* atual = raiz;
    while (atual && atual->left != NULL) {
        atual = atual->left;
    }
    return atual;
}

// Remover um contato
struct Contato* remover(struct Contato* raiz, const char* nome) {
    if (raiz == NULL) {
        printf("Contato não encontrado.\n");
        return raiz;
    }
    if (strcmp(nome, raiz->nome) < 0) {
        raiz->left = remover(raiz->left, nome);
    } 
    else if (strcmp(nome, raiz->nome) > 0) {
        raiz->right = remover(raiz->right, nome);
    } 
    else {
        //caso 1 -> folha ou no com 1 filho
        if (raiz->left == NULL) {
            struct Contato* temp = raiz->right;
            free(raiz);
            return temp;
            
        } 
        else if (raiz->right == NULL) {
            struct Contato* temp = raiz->left;
            free(raiz);
            return temp;
        }
        
        //caso 2 -> no com 2 filhos
        struct Contato* temp = encontrarMin(raiz->right);
        strcpy(raiz->nome, temp->nome);
        strcpy(raiz->celular, temp->celular);
        raiz->right = remover(raiz->right, temp->nome);
    }
    return raiz;
}

// Listar os contatos em ordem alfabética
void listar(struct Contato* raiz) {
    if (raiz != NULL) {
        listar(raiz->left);
        printf("%s | Celular: %s\n", raiz->nome, raiz->celular);
        listar(raiz->right);
    }
}

// Cadastrar um novo contato
struct Contato* cadastrarContato(struct Contato* raiz) {
    char nome[50];
    char celular[15];
    printf("Nome: ");
    scanf(" %[^\n]", nome);
    
    if (buscar(raiz, nome) != NULL) {
        printf("Contato duplicado. Nao foi inserido.\n");
        return raiz;
    }
    printf("Celular: ");
    scanf(" %[^\n]", celular);

    struct Contato* novo = criarNo(nome, celular);
    raiz = inserir(raiz, novo);

    printf("Contato inserido com sucesso!\n");
    return raiz;
}

// Buscar e exibir um contato
void buscarExibirContato(struct Contato* raiz) {
    char nome[50];
    printf("Digite o Nome para buscar: ");
    scanf(" %[^\n]", nome);
    struct Contato* encontrado = buscar(raiz, nome);
    if (encontrado) {
        printf("%s | Celular: %s\n", encontrado->nome, encontrado->celular);
    } else {
        printf("Contato não encontrado.\n");
    }
}

// Remover um contato via interface
struct Contato* removerContato(struct Contato* raiz) {
    char nome[50];
    printf("Digite o nome do contato: ");
    scanf(" %[^\n]", nome);
    return remover(raiz, nome);
}

// Menu principal
void menu() {
    printf("\nMenu\n");
    printf("1. Adicionar contato\n");
    printf("2. Buscar contato\n");
    printf("3. Remover contato\n");
    printf("4. Listar contatos\n");
    printf("5. Sair\n");
    printf("Opção: ");
}

void liberarArvore(struct Contato* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->left);
        liberarArvore(raiz->right);
        free(raiz);
    }
}

int main() {
    struct Contato* raiz = NULL;
    int opcao;
    do {
        menu();
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                raiz = cadastrarContato(raiz);
                break;
            case 2:
                buscarExibirContato(raiz);
                break;
            case 3:
                raiz = removerContato(raiz);
                break;
            case 4:
                printf("\n=== LISTA DE CONTATOS ===\n");
                listar(raiz);
                break;
            case 5:
                printf("Saindo...\n");
                liberarArvore(raiz);
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 5);
    return 0;
}
