#include <stdio.h>
#include <stdlib.h>
#include "funções_clinica.h"
#include <ctype.h>

int main() {
    No *lista = NULL;
    int opcao = 0;

    do {
        limpar_tela();

        printf("=======================\n");
        printf("------- CLÍNICA -------\n");
        printf("=======================\n");

        imprimir_lista(lista);

        printf("\n1 - Adicionar paciente\n");
        printf("2 - Atender próximo paciente (Remover do início)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (opcao) {
            case 1:
                inserirPaciente(&lista);
                break;

            case 2:
                atenderPaciente(&lista);
                break;

            case 0:
                printf("\nEncerrando e liberando memória...\n");
                liberar_lista(&lista);
                break;

            default:
                printf("\nOpção inválida!\n");
                break;
        }

        if (opcao != 0) {
            printf("\nPressione [ENTER] para voltar ao menu...");
            getchar();
        }

    } while (opcao != 0);

    return 0;
}
