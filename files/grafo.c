/// ATIVIDADE ..: TRABALHO PRÁTICO EDDA3 2020-1
/// DATA .......: 04-10-2020
/// AUTOR ......: HELTON RICARDO SANTOS DA COSTA
/// CURSO ......: ANÁLISE E DESENVOLVIMENTO DE SISTEMAS
/// TURMA ......: III SEMESTRE
/// PROFESSOR ..: MARQUES MOREIRA DE SOUSA

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "estruturas.h"
#include "dijkstra.h"
#include "limpaTela.h"

void titulo(void) {
   limparTela();
   printf("\n :: PROGRAMA CAMINHO MINIMO EM GRAFO COM DIJKSTRA ::");
   printf("\n :: HELTON RICARDO - IFSP-CJO TADS III - 2020 ::");
   printf("\n\n\n");
}

GRAFO *criarGrafo(GRAFO **grafo, int q) {
   *grafo = (GRAFO *) malloc(sizeof(GRAFO));
   if (*grafo) {
      (*grafo)->nCidades = q;
      (*grafo)->nCaminhos = 0;
      (*grafo)->cid = (CIDADE *) malloc(q * sizeof(CIDADE));
      for (int i = 0; i < q; ++i)
         (*grafo)->cid[i].cab = NULL;
   }
   return *grafo; // retorna 0 caso alocação dê errado
}

void lerCidades(GRAFO *grafo) {
   if (!grafo) return;
   titulo();
   for (int i = 0; i < grafo->nCidades; ++i) {
      printf(" Nome da cidade %2d: ", i + 1);
      scanf(" %[^\n]", grafo->cid[i].nome);
      printf(" Coordenadas [x y]: ");
      scanf("%lf %lf", &grafo->cid[i].x, &grafo->cid[i].y);
      grafo->cid[i].cab = NULL;
      printf("\n");
   }
}

double haCaminhoDireto(CAMINHO *atual, int cidade) {
   if (atual) {
      if (atual->cidade == cidade)
         return atual->distancia;
      return haCaminhoDireto(atual->prox, cidade);
   } else return 0;
}

bool criarCaminho(GRAFO *grafo, int ci, int cf) {
   if (!grafo) return 0;
   if (ci < 0 || grafo->nCidades <= ci) return false;
   if (cf < 0 || grafo->nCidades <= cf) return false;
   CAMINHO *novo = (CAMINHO*) malloc(sizeof(CAMINHO));
   if (!novo) return false;
   CIDADE *c1 = &grafo->cid[ci];
   CIDADE *c2 = &grafo->cid[cf];
   novo->cidade = cf;
   novo->distancia = sqrt(pow(c1->x - c2->x, 2) + pow(c1->y - c2->y, 2));
   novo->prox = grafo->cid[ci].cab;
   grafo->cid[ci].cab = novo;
   grafo->nCaminhos++;
   return true;
}

int gerarCaminhos(GRAFO *grafo, int porcentagem) {
   srand(time(0));
   int maxCaminhos = grafo->nCidades * (grafo->nCidades - 1);
   int quantidade = maxCaminhos * porcentagem / 100;
   int ci, cf;
   while (grafo->nCaminhos < quantidade) {
      ci = rand() % grafo->nCidades;
      cf = rand() % grafo->nCidades;
      if (ci != cf && !haCaminhoDireto(grafo->cid[ci].cab, cf))
         criarCaminho(grafo, ci, cf);
   }
   return quantidade;
}

void pausa(void) {
   char e;
   printf("\n\n Pressione <Enter> para continuar... ");
   while (getchar() != '\n');
   scanf("%c", &e);
}

void imprimir(GRAFO *grafo) {
   titulo();
   printf(" Numero de cidades ...: %d\n", grafo->nCidades);
   printf(" Numero de caminhos ..: %d\n", grafo->nCaminhos);
   printf("\n Legenda:\n\n");
   for (int i = 0; i < grafo->nCidades; ++i)
      printf(" c%02d: %s\n", i + 1, grafo->cid[i].nome);
   printf("\n");
   for (int i = 0; i < grafo->nCidades; ++i) {
      printf(" c%02d:", i + 1);
      CAMINHO *atual = grafo->cid[i].cab;
      while (atual) {
         printf(" c%02d(%10.6lf)", atual->cidade + 1, atual->distancia);
         atual = atual->prox;
      }
      printf("\n");
   }
   pausa();
}

void limparCaminhos(CAMINHO *caminho) {
   if (caminho) {
      limparCaminhos(caminho->prox);
      free(caminho);
   }
}

void limparGrafo(GRAFO *grafo) {
   for (int i = 0; i < grafo->nCidades; ++i)
      limparCaminhos(grafo->cid[i].cab);
   free(grafo->cid);
   free(grafo);
}

int indiceCidade(GRAFO *grafo, char *nome) {
   for (int i = 0; i < grafo->nCidades; ++i)
      if (!strcmp(grafo->cid[i].nome, nome))
         return i;
   return -1;
}

void caminhosAleatorios(GRAFO *grafo) {
   int q;
   titulo();
   if (grafo) {
      do {
         printf(" Porcentagem de caminhos para gerar [1, 100]: ");
         scanf("%d", &q);
      } while (q < 1 || 100 < q);
      q = gerarCaminhos(grafo, q);
      printf("\n %d Caminhos aleatorios gerados com sucesso!", q);
      pausa();
   }
}

void inicio(GRAFO **grafo) {
   int q;
   titulo();
   do {
      printf(" Quantidade de cidades [10, 50]: ");
      scanf("%d", &q);
   } while (q < 10 || 50 < q);
   printf("\n");
   criarGrafo(grafo, q);
   lerCidades(*grafo);
   caminhosAleatorios(*grafo);
}

void interacao(GRAFO **grafo) {
   char nome[NOMETAM];
   int cid1, cid2;
   bool erro;
   CAMINHO *caminho;
   titulo();
   printf(" Encontrar menor caminho entre cidades\n");
   printf(" (Entre 'sair', sem aspas, para voltar)\n\n");
   do {
      printf(" Cidade origem ...: ");
      scanf(" %[^\n]", nome);
      if (strcmp(nome, "sair") == 0) return;
      cid1 = indiceCidade(*grafo, nome);
      if (cid1 == -1) {
         erro = true;
         printf(" ERRO: Cidade nao encontrada!\n");
      }
      else erro = false;
   } while (erro);
   printf("\n");
   do {
      printf(" Cidade destino ..: ");
      scanf(" %[^\n]", nome);
      if (strcmp(nome, "sair") == 0) return;
      cid2 = indiceCidade(*grafo, nome);
      if (cid2 == -1) {
         erro = true;
         printf(" ERRO: Cidade nao encontrada!\n");
      }
      else erro = false;
   } while (erro);
   dijkstra(*grafo, cid1, cid2);
   pausa();
}

int main(void) {
   GRAFO *grafo;
   int continua;
   inicio(&grafo);
   do {
      titulo();
      printf(" Selecione uma opcao:");
      printf("\n\n [1] - Exibir lista de adjacencia");
      printf("\n\n [2] - Calcular caminho minimo entre cidades");
      printf("\n\n [0] - Encerrar");
      printf("\n\n > ");
      scanf("%d", &continua);
      switch(continua) {
         case 1: imprimir(grafo);  break;
         case 2: interacao(&grafo); break;
      }
   } while (continua);
   limparGrafo(grafo);
   return 0;
}
