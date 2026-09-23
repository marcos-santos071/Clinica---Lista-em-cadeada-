#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "funções_clinica.h"

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
        printf("3 - Buscar nome na fila\n");
        printf("4 - Cancelar paciente da fila\n"); // <-- Nova Opção!
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");

        opcao = lerOpcaoInteira();

        switch (opcao) {
            case 1:
                inserirPaciente(&lista);
                break;
            case 2:
                atenderPaciente(&lista);
                break;
            case 3:
                buscaPaciente(lista);
                break;
            case 4:
                cancelarPaciente(&lista); // <-- Chamada da função
                break;
            case 0:
                printf("\nEncerrando e liberando memória...\n");
                liberar_lista(&lista);
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                break;
        }

        if (opcao != 0) {
            printf("\nPressione [ENTER] para voltar ao menu...");
            getchar();
        }

    } while (opcao != 0);

    return 0;
}
