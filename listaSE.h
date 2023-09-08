#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
    struct Graph* letra_apontada;
    struct No* lista_adj;
}No;

typedef struct Graph{
    char letra;
    No* lista_principal;
}Graph;

Graph *inicializa_vertice(){
	return NULL;
}

int grafo_vazio(Graph *lista){
	if(lista==NULL) return 1;
	return 0;
}

int lista_no_vazia(No *lista){
	if(lista==NULL) return 1;
	return 0;
}

Graph *aloca_grafo(){
	Graph *novo_vertice;
	novo_vertice=(Graph*) malloc(sizeof(Graph));
	return novo_vertice;
}

No *aloca_no(){
  No *novo_no;
	novo_no=(No*) malloc(sizeof(No));
	return novo_no;
}

int insere_lista_principal(Graph **l, char e){
	Graph *novo_no, *atu;
	novo_no=aloca_grafo();
	novo_no->lista_principal=aloca_no();

	novo_no->letra=e;

	if(novo_no==NULL || novo_no->lista_principal==NULL) return 0;
  
	if(grafo_vazio(*l)){
		*l=novo_no;
	} else{
		atu=*l;
		while(atu->lista_principal->letra_apontada!=NULL){
			atu=atu->lista_principal->letra_apontada;
		}
		atu->lista_principal->letra_apontada=novo_no;
	}
	return 1;
}

Graph *busca_vertice(Graph *lista, int i){
	Graph *atu;
	atu=lista;

	int c = 1;
	while((atu!=NULL)&&(i!=c)){
		atu=atu->lista_principal->letra_apontada; c++;
	}
	if (atu==NULL) return NULL;
	return atu;
}

int grau_do_vertice(No *lista){
	No *atu;
	atu=lista;

	int tam = 0;
	while((atu!=NULL)){
		atu=atu->lista_adj;
		tam++;
	}
	return tam;
}

int tam_lista_principal(Graph *listacompleta){
	Graph *atu;
	atu=listacompleta;
	
	int tam = 0;
	while(atu->lista_principal->letra_apontada!=NULL){
		atu=atu->lista_principal->letra_apontada;
		tam++;
    }

	return tam;
}

int *pega_todos_graus(Graph *listacompleta){
	int *graus;

	graus = (int *) malloc(tam_lista_principal(listacompleta) * sizeof(int));

	Graph *atu;
	atu=listacompleta;
	
	int i = 0;
	while(atu->lista_principal->lista_adj!=NULL){
		int grau = grau_do_vertice(atu->lista_principal->lista_adj);
		graus[i] = grau;
		atu=atu->lista_principal->letra_apontada;
		i++;
    }

	return graus;
}

int insere_no_fim(No **l, Graph **e){
	No *novo_no, *atu;
	novo_no=aloca_no();
	if(novo_no==NULL) return 0;
	novo_no->letra_apontada=*e;
	novo_no->lista_adj=NULL;
	if(lista_no_vazia(*l)){
		*l=novo_no;
	} else{
		atu=*l;
		while(atu->lista_adj!=NULL){
			atu=atu->lista_adj;
		}
		atu->lista_adj=novo_no;
	}
	return 1;
}

void imprime_no(No *lista){
	No *atu;
	atu=lista;
	while(atu!=NULL){
		if(atu->lista_adj==NULL){
			printf(" %c\n", atu->letra_apontada->letra);
			atu=atu->lista_adj;
		} else{
			printf(" %c ->", atu->letra_apontada->letra);
			atu=atu->lista_adj;
		}
	}
}

void imprime_grafo_completo(Graph *listacompleta){
	Graph *atu;
	No *aux;
	atu=listacompleta;
	while(atu->lista_principal->letra_apontada!=NULL){
		if(atu->letra != ' ')
		printf("%c ->", atu->letra);
		imprime_no(atu->lista_principal->lista_adj);
		atu=atu->lista_principal->letra_apontada;
    }
}

