#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para um contato 
struct Contato {
    char nome[50];
    int celular;  
    struct Contato* left; 
    struct Contato* right;  
};

// Protótipos das funções
struct Contato* inserir(struct Contato* raiz, struct Contato* novo);
struct Contato* buscar(struct Contato* raiz, const char* nome);
struct Contato* remover(struct Contato* raiz, const char* nome);
void listar(struct Contato* raiz); 
void menu();
struct Contato* encontrarMinimo(struct Contato* raiz);

// Função auxiliar pedida na Pág. 2 
int compararNomes(char* nome1, char* nome2) {
    return strcmp(nome1, nome2);
}

int main() {
    struct Contato* raiz = NULL;
    int opcao;

    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                // Adicionar contato
                struct Contato* novo = (struct Contato*)malloc(sizeof(struct Contato));
                if (novo == NULL) {
                    printf("Erro de alocação.\n");
                    break;
                }

                printf("Nome: ");
                scanf(" %[^\n]", novo->nome);

                printf("Celular: ");
                scanf("%d", &novo->celular); 

                novo->left = NULL;
                novo->right = NULL;

                raiz = inserir(raiz, novo);
                printf("Contato adicionado!\n");
                break;
            }
            case 2: {
                // Buscar contato
                char nome[50];
                printf("Digite o nome para buscar: ");
                scanf(" %[^\n]", nome);

                struct Contato* encontrado = buscar(raiz, nome);

                if (encontrado) {
                    
                    printf("Contato encontrado: %s, Celular: %d\n", encontrado->nome, encontrado->celular);
                } else {
                    printf("Contato não encontrado.\n"); 
                }
                break;
            }
            case 3: {
                // Remover contato
                char nome[50];
                printf("Nome para remover: ");
                scanf(" %[^\n]", nome);

                raiz = remover(raiz, nome);
                break;
            }
            case 4: {
                // Imprimir contatos
                printf("\n=== LISTA DE CONTATOS ===\n");
                listar(raiz); 
                break;
            }
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}

// Implementação das funções

void menu() {

    printf("\nMenu:\n");
    printf("1. Adicionar contato\n");
    printf("2. Buscar contato\n");
    printf("3. Remover contato\n");
    printf("4. Listar contatos\n"); 
    printf("5. Sair\n");
    printf("Opção: ");
}

struct Contato* inserir(struct Contato* raiz, struct Contato* novo) 
{
    if (raiz == NULL) 
        return novo;
        
    // Se novo < raiz, vai p esquerda
    if (compararNomes(novo->nome, raiz->nome) < 0) 
    {
        raiz->left = inserir(raiz->left, novo);
    }
    
    // Se novo > raiz, vai para direita 
    else if (compararNomes(novo->nome, raiz->nome) > 0) 
    {
        raiz->right = inserir(raiz->right, novo);
    }
    else {
        printf("Esse contato já foi adicionado.\n");
    }
    
    return raiz;
}

struct Contato* buscar(struct Contato* raiz, const char* nome) {
    
    if (raiz == NULL || compararNomes((char*)raiz->nome, (char*)nome) == 0) 
    {
        return raiz;
    }

    if (compararNomes((char*)nome, (char*)raiz->nome) < 0) 
    {
        return buscar(raiz->left, nome);
    }
    return buscar(raiz->right, nome);
}

struct Contato* encontrarMinimo(struct Contato* raiz) {
    struct Contato* atual = raiz;
    while (atual && atual->left != NULL) {
        atual = atual->left;
    }
    return atual;
}

struct Contato* remover(struct Contato* raiz, const char* nome) {
    if (raiz == NULL) {
        printf("Contato não encontrado.\n");
        return raiz;
    }

    if (compararNomes((char*)nome, (char*)raiz->nome) < 0) {
        raiz->left = remover(raiz->left, nome);
    }
    else if (compararNomes((char*)nome, (char*)raiz->nome) > 0) {
        raiz->right = remover(raiz->right, nome);
    }
    else {
        // Nó encontrado
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

        struct Contato* temp = encontrarMinimo(raiz->right);
        strcpy(raiz->nome, temp->nome);
        strcpy(raiz->celular, temp->celular); 
        raiz->right = remover(raiz->right, temp->nome);
    }
    return raiz;
}

void ImprimirArvoreDeContatos(struct Contato* raiz) {
    if (raiz != NULL) {
        ImprimirArvoreDeContatos(raiz->left);
 
        printf(" === LISTA DE CONTATOS === ");
        printf("Nome: %s | Celular: %s\n", raiz->nome, raiz->celular);
        ImprimirArvoreDeContatos(raiz->right);
    }
}