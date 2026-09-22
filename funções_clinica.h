#ifndef FUNCOES_CLINICA_H
#define FUNCOES_CLINICA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void limpar_tela() {
    #ifdef _WIN32
        system("cls");  // Comando para Windows
    #else
        system("clear"); // Comando para Linux e macOS
    #endif
}

// Estrutura do Nó
typedef struct No {
    int posicao;
    char nome[32];
    int prioritario;
    struct No *proximo;
} No;

int nomeValido(const char *nome){
  if(strlen(nome)== 0) return 0;

  for(int i = 0; nome[i] != '\0'; i++){
    if(!isalpha((unsigned char)nome[i])&& !isspace((unsigned char)nome[i])){
        return 0;
    }
  }
  return 1;
}



// Função para inserir paciente mantendo os prioritários na frente
void inserirPaciente(No **inicio) {
    // DECLARAÇÃO E ALOCAÇÃO DE MEMÓRIA DO NÓ
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) {
        printf("\nErro de alocação de memória!\n");
        return;
    }

    do{

    printf("\nDigite o nome do paciente: ");
    fgets(novo->nome, sizeof(novo->nome), stdin);
    novo->nome[strcspn(novo->nome, "\n")] = '\0';

    if(!nomeValido(novo->nome)){
        printf("--> Nome invávlido! Não digite numeros ou caracteres especias.\n");
      }
    }while(!nomeValido(novo->nome));

    printf("O paciente %s é prioritário?\n", novo->nome);
    printf("Digite 1 para SIM ou 0 para NÃO: ");
    scanf("%d", &novo->prioritario);

    // Limpa o buffer do teclado
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    novo->proximo = NULL;

    // Caso 1: Lista vazia
    if (*inicio == NULL) {
        novo->posicao = 1;
        *inicio = novo;
        printf("\n--> Paciente '%s' adicionado na posição 1!\n", novo->nome);
        return;
    }

    // Caso 2: Paciente prioritário
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
    }
    // Caso 3: Paciente comum
    else {
        No *atual = *inicio;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }

    // Recalcula as posições da fila
    int pos = 1;
    for (No *p = *inicio; p != NULL; p = p->proximo) {
        p->posicao = pos++;
    }

    printf("\n--> Paciente '%s' adicionado com sucesso!\n", novo->nome);
}

// Remove o primeiro paciente da lista
void atenderPaciente(No **inicio) {
    if (*inicio == NULL) {
        printf("\nNão há pacientes na fila de espera!\n");
        return;
    }

    No *temp = *inicio;

    printf("\n============================\n");
    printf("--> Chamado para atendimento: %s\n", temp->nome);
    printf("==============================\n");

    *inicio = (*inicio)->proximo;
    free(temp);

    // Recalcula as posições numéricas
    int pos = 1;
    for (No *p = *inicio; p != NULL; p = p->proximo) {
        p->posicao = pos++;
    }

    printf("\n--> Paciente atendido com sucesso e removido da fila!\n");
}

// Imprime a lista
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

// Libera toda a memória
void liberar_lista(No **inicio) {
    No *proximo_no;

    for (No *atual = *inicio; atual != NULL; atual = proximo_no) {
        proximo_no = atual->proximo;
        free(atual);
    }
    *inicio = NULL;
}

#endif // FUNCOES_CLINICA_H
