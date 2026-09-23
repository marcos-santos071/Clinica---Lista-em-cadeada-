#ifndef FUNCOES_CLINICA_H
#define FUNCOES_CLINICA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//ira limpar a tela do usuario
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

// Valida se o nome contém apenas letras e espaços
int nomeValido(const char *nome) {
    if (strlen(nome) == 0) return 0;

    for (int i = 0; nome[i] != '\0'; i++) {
        if (!isalpha((unsigned char)nome[i]) && !isspace((unsigned char)nome[i])) {
            return 0; // Se contiver número ou símbolo, é inválido
        }
    }
    return 1;
}

// Valida se o texto é apenas composto por números
int ehNumeroInteiro(const char *str) {
    if (strlen(str) == 0) return 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit((unsigned char)str[i])) {
            return 0;
        }
    }
    return 1;
}

// Leitura segura da opção do menu
int lerOpcaoInteira() {
    char entrada[20];

    while (1) {
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = '\0';

        if (ehNumeroInteiro(entrada)) {
            return atoi(entrada);
        }

        printf("--> Entrada inválida! Digite apenas números inteiros: ");
    }
}

// Garante que o usuário digite EXATAMENTE 0 ou 1
int lerOpcaoBinaria() {
    int valor;
    while (1) {
        valor = lerOpcaoInteira();
        if (valor == 0 || valor == 1) {
            return valor;
        }
        printf("--> Opção inválida! Digite apenas 1 para SIM ou 0 para NÃO: ");
    }
}

// Função para inserir paciente mantendo os prioritários na frente
void inserirPaciente(No **inicio) {
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) {
        printf("\nErro de alocação de memória!\n");
        return;
    }

    do {
        printf("\nDigite o nome do paciente: ");
        fgets(novo->nome, sizeof(novo->nome), stdin);
        novo->nome[strcspn(novo->nome, "\n")] = '\0';

        if (!nomeValido(novo->nome)) {
            printf("--> Nome inválido! Não digite números ou caracteres especiais.\n");
        }
    } while (!nomeValido(novo->nome));

    printf("O paciente %s é prioritário?\n", novo->nome);
    printf("Digite 1 para SIM ou 0 para NÃO: ");

    novo->prioritario = lerOpcaoBinaria();
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
    }

    else {
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


    int pos = 1;
    for (No *p = *inicio; p != NULL; p = p->proximo) {
        p->posicao = pos++;
    }

    printf("\n--> Paciente atendido com sucesso e removido da fila!\n");
}

void buscaPaciente(No *inicio) {
    if (inicio == NULL) {
        printf("\nA lista está vazia! Não há pacientes para buscar.\n");
        return;
    }

    char nomeBuscado[32];
    printf("\nDigite o nome do paciente para saber se está na fila: ");
    fgets(nomeBuscado, sizeof(nomeBuscado), stdin);
    nomeBuscado[strcspn(nomeBuscado, "\n")] = '\0';

    for (No *atual = inicio; atual != NULL; atual = atual->proximo) {
        if (strcmp(atual->nome, nomeBuscado) == 0) {
            int pessoasNaFrente = atual->posicao - 1;

            printf("\n--> O paciente '%s' ESTÁ na lista! Posição: %d\n", atual->nome, atual->posicao);

            if (pessoasNaFrente == 0) {
                printf("Ele(a) é o próximo a ser atendido!\n");
            } else if (pessoasNaFrente == 1) {
                printf("Tem 1 pessoa para ser atendida na frente de %s.\n", nomeBuscado);
            } else {
                printf("Tem %d pessoas para serem atendidas na frente de %s.\n", pessoasNaFrente, nomeBuscado);
            }
            return;
        }
    }

    printf("\n--> O paciente '%s' NÃO está na lista.\n", nomeBuscado);
}

//cancela um paciente específico em qualquer posição da fila
void cancelarPaciente(No **inicio) {
    if (*inicio == NULL) {
        printf("\nA lista está vazia! Não há pacientes para cancelar.\n");
        return;
    }

    char nomeBuscado[32];
    printf("\nDigite o nome do paciente que deseja cancelar a consulta: ");
    fgets(nomeBuscado, sizeof(nomeBuscado), stdin);
    nomeBuscado[strcspn(nomeBuscado, "\n")] = '\0';

    No *atual = *inicio;
    No *anterior = NULL;

while (atual != NULL && strcmp(atual->nome, nomeBuscado) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }


    if (atual == NULL) {
        printf("\n--> O paciente '%s' NÃO foi encontrado na fila!\n", nomeBuscado);
        return;
    }


    if (anterior == NULL) {
        *inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
}

    printf("\n--> Agendamento do paciente '%s' foi CANCELADO e removido da fila com sucesso!\n", atual->nome);
    free(atual);

    int pos = 1;
    for (No *p = *inicio; p != NULL; p = p->proximo) {
        p->posicao = pos++;
    }
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
