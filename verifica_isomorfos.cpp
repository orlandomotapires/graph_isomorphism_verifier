#include <iostream>
#include <stdio.h>
#include <string.h>
#include "listaSE.h"

void le_arquivo_cria_grafo(Graph **graph_a, FILE *arq){
    int a, i = 1;
    char Linha[300];

    Graph *no_a_ser_inserido, *no_base;

    no_a_ser_inserido=inicializa_vertice();
    no_base=inicializa_vertice();
    
    while (!feof(arq)){
        if (fgets(Linha, 100, arq))
        if (i==1){
            for(a=0; a<=(strlen(Linha)); a++){
                if (Linha[a] != ' ') insere_lista_principal(graph_a, Linha[a]);   
            }
        }else{
            for(a=0; a<=(strlen(Linha)); a++){
                if(Linha[a]=='1'){
                    no_a_ser_inserido=busca_vertice(*graph_a, a+1);
                    no_base=busca_vertice(*graph_a, (i-1));
                    insere_no_fim(&no_a_ser_inserido->lista_principal, &no_base);
                }
            }
        }
        i++;
    }

}

bool grafos_tamanhos_iguais(Graph *graph_a, Graph *graph_b){
    return tam_lista_principal(graph_a) == tam_lista_principal(graph_b);
}

bool vertices_graus_iguais(Graph *graph_a, Graph *graph_b){
    int *graus_a, *graus_b;

    graus_a = pega_todos_graus(graph_a);
    graus_b = pega_todos_graus(graph_b);

    for(int i = 0; i < tam_lista_principal(graph_a); i++){
        if(graus_a[i] != graus_b[i]) return false;
    }

    return true;
}

bool relaciona_verticeA_verticeB(int i, int j){

}

bool brute_force(Graph *graph_a, Graph *graph_b){
    int *graus_a, *graus_b;

    graus_a = pega_todos_graus(graph_a);
    graus_b = pega_todos_graus(graph_b);

    for(int i = 0; i < tam_lista_principal(graph_a); i++){
        for(int j = i; j < tam_lista_principal(graph_a); j++){
            if(relaciona_verticeA_verticeB(i, j)){
                break;
            }
        }
        
    }
}

int verifica_isormorfismo(Graph *graph_a, Graph *graph_b){
    if(!grafos_tamanhos_iguais(graph_a, graph_b)) return 0;
    else if(!vertices_graus_iguais(graph_a, graph_b)) return 0;
    else if(!brute_force(graph_a, graph_b)) return 0;
    else return 1;
}

int main() {
    FILE *arq_a, *arq_b;
    Graph *graph_a, *graph_b;

    arq_a = fopen("adj_a.txt", "rt");
    arq_b = fopen("adj_b.txt", "rt");

    graph_a=inicializa_vertice();
    graph_b=inicializa_vertice();

    if (arq_a == NULL){
        printf("Problemas na abertura do arquivo\n");
        return 1;
    }
    
    le_arquivo_cria_grafo(&graph_a, arq_a);
    le_arquivo_cria_grafo(&graph_b, arq_b);

    fclose(arq_a);
    fclose(arq_b);

    if(verifica_isormorfismo(graph_a, graph_b)) printf("São isomorfos!\n");
    else printf("Não são isomorfos!\n");

  return 0;
}