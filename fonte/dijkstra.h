#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "estruturas.h"

VETS *alocar(GRAFO *grafo) {
   VETS *vets = (VETS *) malloc(sizeof(VETS));
   if (vets) {
      vets->tamanho = grafo->nCidades;
      vets->abertas = (bool *) malloc(vets->tamanho * sizeof(bool));
      vets->antecessoras = (int *) malloc(vets->tamanho * sizeof(int));
      vets->distancias = (double *) malloc(vets->tamanho * sizeof(double));
      if (vets->abertas && vets->antecessoras && vets->distancias)
         for (int i = 0; i < vets->tamanho; ++i) {
            vets->abertas[i] = true;
            vets->antecessoras[i] = -1;
            vets->distancias[i] = DBL_MAX;
         }
   }
   return vets;
}

int selecionarCidade(VETS *vets) {
   int i;
   for (i = 0; i < vets->tamanho; ++i)
      if (vets->abertas[i])
         break;
   if (i == vets->tamanho) return -1;
   int menor = i;
   for (i = menor; i < vets->tamanho; ++i)
      if (vets->abertas[i] && vets->distancias[i] < vets->distancias[menor])
         menor = i;
   return menor;
}

bool relaxar(VETS *vets, int origem, CAMINHO *destino) {
   double soma = vets->distancias[origem] + destino->distancia;
   if (soma < vets->distancias[destino->cidade]) {
      vets->antecessoras[destino->cidade] = origem;
      vets->distancias[destino->cidade] = soma;
   }
}

void desalocar(VETS *vets) {
   if (vets) {
      if (vets->abertas)
         free(vets->abertas);
      if (vets->antecessoras)
         free(vets->antecessoras);
      if (vets->distancias)
         free(vets->distancias);
      free(vets);
   }
}

void rota(GRAFO *grafo, VETS *vets, int cid) {
   if (cid != -1) {
      rota(grafo, vets, vets->antecessoras[cid]);
      printf(" - %s\n", grafo->cid[cid].nome);
   }
}

void dijkstra(GRAFO *grafo, int ci, int cf) {
   int atual;
   CAMINHO *tmp;
   VETS *vets = alocar(grafo);
   vets->distancias[ci] = 0;
   while (vets->abertas[cf]) {
      atual = selecionarCidade(vets);
      if (atual == -1) break;
      vets->abertas[atual] = false;
      if (atual == cf) break;
      tmp = grafo->cid[atual].cab;
      while (tmp) {
         relaxar(vets, atual, tmp);
         tmp = tmp->prox;
      }
   }
   if (vets->distancias[cf] != DBL_MAX) {
      printf("\n Caminho a ser percorrido:\n");
      rota(grafo, vets, cf);
      printf("\n Distancia total (caminho minimo): %.6lf\n", vets->distancias[cf]);
   }
   else printf("\n Nao ha caminho possivel entre as cidades informadas!\n");
   desalocar(vets);
}
