#ifndef FUNCOES_CLINICA_H
#define FUNCOES_CLINICA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void limpar_tela() {
    #ifdef _WIN32
        system("cls");  // Comando para Windows
    #else
        system("clear"); // Comando para Linux e macOS
    #endif
}

// Estrutura do Nó única
typedef struct No {
    int posicao;
    char nome[32];
    int prioritario;
    struct No *proximo;
} No;

// Função para inserir paciente no final da lista
void inserirPaciente(No **inicio) {
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) {
        printf("\nErro de alocação de memória!\n");
        return;
    }

    printf("\nDigite o nome do paciente: ");
    fgets(novo->nome, sizeof(novo->nome), stdin);
    novo->nome[strcspn(novo->nome, "\n")] = '\0';

    printf("O paciente %s é prioritário?\n", novo->nome);
    printf("Digite 1 para SIM ou 0 para NÃO: ");
    scanf("%d", &novo->prioritario);


    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    novo->proximo = NULL;


    if (*inicio == NULL) {
        novo->posicao = 1;
        *inicio = novo;
        printf("\n--> Paciente '%s' adicionado na posição 1!\n", novo->nome);
        return;
    }


    if (novo->prioritario == 1) {

        if ((*inicio)->prioritario == 0) {
            novo->proximo = *inicio;
            *inicio = novo;
        } else {

            No *atual = *inicio;
            while (atual->proximo != NULL && atual->proximo->prioritario == 1) {
                atual = atual->proximo;
            }

            novo->proximo = atual->proximo;
            atual->proximo = novo;
        }
    }else {
        No *atual = *inicio;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }

    int pos = 1;
    for (No *p = *inicio; p != NULL; p = p->proximo) {
        p->posicao = pos++;
    }

    printf("\n--> Paciente '%s' adicionado com sucesso!\n", novo->nome);
}

// Imprime todos os pacientes da lista
void imprimir_lista(No *inicio) {
    printf("\n==============================");
    printf("\n--- Lista de Espera Atual ---");
    printf("\n==============================\n");

    if (inicio == NULL) {
        printf("\nA lista de espera está vazia.\n\n");
        return;
    }

    for (No *atual = inicio; atual != NULL; atual = atual->proximo) {
        if (atual->prioritario == 1) {
            printf("Posição: %d | Nome: %s | [PRIORITÁRIO]\n", atual->posicao, atual->nome);
        } else {
            printf("Posição: %d | Nome: %s\n", atual->posicao, atual->nome);
        }
    }
}

// Libera a memória de todos os nós
void liberar_lista(No **inicio) {
    No *proximo_no;

    for (No *atual = *inicio; atual != NULL; atual = proximo_no) {
        proximo_no = atual->proximo;
        free(atual);
    }
    *inicio = NULL;
}

#endif // FUNCOES_CLINICA_H
