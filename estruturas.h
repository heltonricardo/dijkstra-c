#pragma once

#define NOMETAM 40
#define false 0
#define true 1

typedef short bool;

typedef struct caminho {
   int cidade;
   double distancia;
   struct caminho *prox;
} CAMINHO;

typedef struct cidade {
   char nome[NOMETAM];
   double x, y;
   CAMINHO *cab;
} CIDADE;

typedef struct grafo {
   int nCidades;
   int nCaminhos;
   CIDADE *cid;
} GRAFO;

typedef struct vets {
   int tamanho;
   bool *abertas;
   int *antecessoras;
   double *distancias;
} VETS;
