#include <stdio.h>
#include <string.h>
#include "listaSE.h"
#include "pilha.h"

#define qnt_letras 4

int matriz_adj_a[50][50];
int matriz_adj_b[50][50];

void le_arquivo_cria_grafo(Graph **graph, FILE *arq, int g_num){
    int a, i = 0;
    char Linha[300];

    Graph *no_a_ser_inserido, *no_base;

    no_a_ser_inserido=inicializa_vertice();
    no_base=inicializa_vertice();
    
    if (fgets(Linha, 100, arq))
        for(a=0; a<=(strlen(Linha)); a++){
            if (Linha[a] != ' ') insere_lista_principal(graph, Linha[a]);   
        }

    while (!feof(arq)){
        if (fgets(Linha, 100, arq))
            for(a=0; a<=(strlen(Linha)); a++){
                if(Linha[a]=='1'){
                    no_a_ser_inserido=busca_vertice(*graph, a+1);
                    no_base=busca_vertice(*graph, (i+1));
                    insere_no_fim(&no_a_ser_inserido->lista_principal, &no_base);
                }

                if(Linha[a] == '1' || Linha[a] == '0'){
                    if(g_num){
                        matriz_adj_b[i][a] = Linha[a];
                    }else{
                        matriz_adj_a[i][a] = Linha[a];
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

void imprime_matriz(int matriz[50][50]){
    for(int i =0; i < qnt_letras; i++){
        for(int j=0; j < qnt_letras; j++){
            printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }
}

bool diagonal_principal_igual(){
    int qnt_1_a = 0, qnt_1_b = 0;

    for(int i = 0; i < qnt_letras; i++) {
        
        if(matriz_adj_a[i][i] == '1') qnt_1_a++;
        if(matriz_adj_b[i][i] == '1') qnt_1_b++;
    }

    if(qnt_1_a != qnt_1_b)return 0;
    
    return 1;
}

bool linha_coluna_iguais(int matriz_adj_atu[50][50]){
    for(int i = 0; i < qnt_letras; i++){
        for(int lin = i; lin < qnt_letras; lin++){
            for(int col = i; col < qnt_letras; col++){
                if(matriz_adj_atu[lin][col] != matriz_adj_atu[col][lin]) return 0;
            }
        }
    }
    return 1;
}

bool ambos_digrafos_ou_ambos_grafos_normais(){
    if(linha_coluna_iguais(matriz_adj_a) == linha_coluna_iguais(matriz_adj_b)) return 1;
    return 0;
}

bool tem_ciclos(Graph *graph){

    struct Pilha nodos_restantes;
    int nodos_visitados[500], capacidade = 50;

    memset(nodos_visitados, -1, sizeof(int));

    criarpilha (&nodos_restantes, capacidade);
    empilhar(&nodos_restantes, 'A');

    while(!estavazia(&nodos_restantes)){
        int no_atu = desempilhar(&nodos_restantes);
        nodos_visitados[no_atu] = 1;

        Graph *aux;
        aux = inicializa_vertice();
        aux = busca_vertice(graph, no_atu - 64);

        No *vizinhos = aux->lista_principal;
        vizinhos = vizinhos->lista_adj;

        while(vizinhos->lista_adj != NULL){
            vizinhos = vizinhos->lista_adj;

            char letra_atu = vizinhos->letra_apontada->letra;

            if(nodos_visitados[letra_atu] == 1){
                //printf("Achei um ciclo! %c\n", letra_atu);
                return true;
            }
            empilhar(&nodos_restantes, letra_atu);
        }
    }

    //printf("Não achei um ciclo!\n");
    return false;
}

/*
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

*/

int verifica_isormorfismo(Graph *graph_a, Graph *graph_b){
    if(!diagonal_principal_igual()){
        printf("Caiu na: diagonal_principal_igual() \n");
        return 0;
    }
    else if(!grafos_tamanhos_iguais(graph_a, graph_b)){
        printf("Caiu na: grafos_tamanhos_iguais() \n");
        return 0;
    }
    else if(!vertices_graus_iguais(graph_a, graph_b)) {
        printf("Caiu na: vertices_graus_iguais() \n");
        return 0;
    }
    else if(tem_ciclos(graph_a) != tem_ciclos(graph_b)) {
        printf("Caiu na: tem_ciclos() \n");
        return 0;
    }
    else if(!ambos_digrafos_ou_ambos_grafos_normais()) {
        printf("Caiu na: ambos_digrafos_ou_ambos_grafos_normais() \n");
        return 0;
    }
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

    le_arquivo_cria_grafo(&graph_a, arq_a, 0);
    le_arquivo_cria_grafo(&graph_b, arq_b, 1);

    fclose(arq_a);
    fclose(arq_b);

    if(verifica_isormorfismo(graph_a, graph_b)) printf("São isomorfos!\n");
    else printf("Não são isomorfos!\n");

  return 0;
}