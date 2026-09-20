#ifndef funções_clinica_h
#define funções_clinica_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//ira guardar a posicao de cada cliente da lista e ira guardar o nome de cada individuo =
typedef struct No{
  int posicao;
  char nome[32];
  struct No *proximo;
} No;

No* criarNo(int posicao) {​
No *novo = (No*) malloc(sizeof(No));​
​
if (novo == NULL) {​
printf("Erro: sem memoria disponivel.\n");​
return;​
}​
​
novo->posicao = posicao;​
novo->proximo = NULL;​
return novo;​
}​




#endif //funções_clinica_h
