#ifndef LISTASE_H
#define LISTASE_H
#include<stdio.h>
#include<stdlib.h>

typedef int tp_item;

typedef struct tp_no{
  struct tp_no **adj;
  struct tp_no *prox;
}tp_listase;

typedef struct{
    tp_listase *lista;
    char info;
}graph;

tp_listase *inicializa_listase(){
  return NULL;
}

int listase_vazia(tp_listase *lista){
  if(lista==NULL) return 1;
  else return 0;
}

// tp_listase *aloca_listase(){
//   tp_listase *novo_no;
//   novo_no = (tp_listase*) malloc(sizeof(tp_listase));
//   return novo_no;
// }

// int insere_listase_no_fim(tp_listase **l, tp_item e){
//   tp_listase *novo_no, *atu;
//   novo_no = aloca_listase();
//   if(novo_no == NULL) return 0;
//   novo_no->adj = e;
//   novo_no->prox = NULL;

//   if(listase_vazia(*l)){
//     *l = novo_no;
//   } else{
//     atu = *l;
//     while(atu->prox != NULL){
//       atu = atu->prox;
//     }
//     atu->prox=novo_no;
//   }

// return 1;
// }

// void imprime_listase(tp_listase *lista, int i){
//   tp_listase *atu;
//   atu = lista;
//   int c=0;
//   while(c<i){
//     printf("%d ", atu->info);
//     atu=atu->prox;
//     c++;
//   }
// }

// int tamanho_listase(tp_listase *lista){
//   int cont = 0;
//   tp_listase *atu;
//   atu=lista;
//   while(atu!=NULL){
//     cont++;
//     atu=atu->prox;
//   }
//   return cont;
// }

// void desfaz_lista(tp_listase **lista){
//   tp_listase *atu;
//   atu = *lista;
//   while(atu!=NULL){
//     *lista = atu->prox;
//     free(atu);
//   }
// }


// int busca_listase(tp_listase *lista, tp_item e){
//   tp_listase *atu;
//   int c=0;
//   atu = lista;
//   while((atu!=NULL) && (atu->info!=e)){
//     atu = atu->prox; 
//     c++;
//   }
//   if(atu == NULL) return 0;
//   return c;
// }

#endif