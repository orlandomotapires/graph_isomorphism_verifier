#ifndef LISTASE_H
#define LISTASE_H
#include<stdio.h>
#include<stdlib.h>

typedef char tp_item;

typedef struct tp_no{
  struct tp_no *adj;
  struct tp_no *prox;
  tp_item info;
}tp_listase;

typedef struct{
  tp_listase *lista;
}graph;

tp_listase *inicializa_listase(){
  return NULL;
}

int listase_vazia(tp_listase *lista){
  if(lista==NULL) return 1;
  else return 0;
}

tp_listase *aloca_listase(){
  tp_listase *novo_no;
  novo_no = (tp_listase*) malloc(sizeof(tp_listase));
  return novo_no;
}

tp_listase *procura_elemento_lista_principal(tp_listase *lista, tp_item e){
  tp_listase *atu;
  atu = lista;
  while(atu->prox != NULL){
    if(atu->info == e){
      return atu;
    }
    atu=atu->prox;
  }

  return NULL;
}

tp_listase *procura_elemento_base(tp_listase *lista, int pos){
  tp_listase *atu;
  atu = lista;

  int c = 0;
  while(atu->prox != NULL){
    if(pos == c){
      return atu;
    }
    atu=atu->prox;
    c++;
  }

  return NULL;
}

int insere_listase_no_fim(tp_listase **l, tp_item e){
  tp_listase *novo_no, *atu;
  novo_no = aloca_listase();
  if(novo_no == NULL) return 0;
  
  novo_no->info = e;
  novo_no->adj = procura_elemento_lista_principal(l, e);
  novo_no->prox = NULL;

  if(listase_vazia(*l)){
    *l = novo_no;
  } else{
    atu = *l;
    while(atu->prox != NULL){
      atu = atu->prox;
    }
    atu->prox=novo_no;
  }

  return 1;
}

void imprime_listase(tp_listase *lista){
  tp_listase *atu;
  atu = lista;
  
  printf("%c -> ", atu->info);
  while(atu->prox != NULL){
    printf("%c", atu->info);
    atu = atu -> prox; 
  }
}

void imprime_listase_inteira(tp_listase *lista){
  tp_listase *atu;
  atu = lista;
  int c=0;
  
  while(atu->prox != NULL){  
    atu=atu->prox;
    c++;

    printf("\nIMPRIMINDO A LISTA DA LETRA %c\n", atu->info);
    if(atu->adj != NULL)
      printf("\nIMPRIMINDO A LISTA DA LETRA adj %c\n", atu->adj->info);
    imprime_listase(atu);

  }
}


#endif