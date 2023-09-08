#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
    struct Graph* verticeapontado;
    struct No* proxlista;
}No;

typedef struct Graph{
    char vertice;
    No* lista;
}Graph;

Graph *inicializa_vertice(){
	return NULL;
}

int lista_vertice_vazia(Graph *lista){
	if(lista==NULL) return 1;
	return 0;
}

int lista_no_vazia(No *lista){
	if(lista==NULL) return 1;
	return 0;
}

Graph *aloca_vertice(){
	Graph *novo_vertice;
	novo_vertice=(Graph*) malloc(sizeof(Graph));
	return novo_vertice;
}

No *aloca_no(){//usado
  No *novo_no;
	novo_no=(No*) malloc(sizeof(No));
	return novo_no;
}

int insere_lista_principal(Graph **l, char e){
	Graph *novo_no, *atu;
	novo_no=aloca_vertice();
	novo_no->lista=aloca_no();

	novo_no->vertice=e;

	if(novo_no==NULL || novo_no->lista==NULL) return 0;
  
	if(lista_vertice_vazia(*l)){
		*l=novo_no;
	} else{
		atu=*l;
		while(atu->lista->verticeapontado!=NULL){
			atu=atu->lista->verticeapontado;
		}
		atu->lista->verticeapontado=novo_no;
	}
	return 1;
}

Graph *busca_vertice(Graph *lista, int i){
	Graph *atu;
	atu=lista;

	int c = 1;
	while((atu!=NULL)&&(i!=c)){
		atu=atu->lista->verticeapontado; c++;
	}
	if (atu==NULL) return NULL;
	return atu;
}

int grau_do_vertice(No *lista, int i){
	No *atu;
	atu=lista;

	int tam = 0;
	while((atu!=NULL)){
		atu=atu->proxlista;
		tam++;
	}
	return tam;
}

int insere_no_fim(No **l, Graph **e){
	No *novo_no, *atu;
	novo_no=aloca_no();
	if(novo_no==NULL) return 0;
	novo_no->verticeapontado=*e;
	novo_no->proxlista=NULL;
	if(lista_no_vazia(*l)){
		*l=novo_no;
	} else{
		atu=*l;
		while(atu->proxlista!=NULL){
			atu=atu->proxlista;
		}
		atu->proxlista=novo_no;
	}
	return 1;
}

void imprimeno(No *lista){
	No *atu;
	atu=lista;
	while(atu!=NULL){
		if(atu->proxlista==NULL){
			printf(" %c\n", atu->verticeapontado->vertice);
			atu=atu->proxlista;
		} else{
			printf(" %c ->", atu->verticeapontado->vertice);
			atu=atu->proxlista;
		}
	}
}

void imprime(Graph *listacompleta){
	Graph *atu;
	No *aux;
	atu=listacompleta;
	while(atu->lista->verticeapontado!=NULL){
		printf("%c ->", atu->vertice);
		imprimeno(atu->lista->proxlista);
		atu=atu->lista->verticeapontado;
    }
}