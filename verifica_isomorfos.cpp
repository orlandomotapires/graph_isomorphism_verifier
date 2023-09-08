#include <iostream>
#include <stdio.h>
#include <string.h>
#include "listaSE.h"

void le_arquivo_cria_grafo(Graph **graph_a, FILE *arq, Graph *no_a_ser_inserido, Graph *no_base){
    int a, i = 1;
    char Linha[300];
    
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
                    insere_no_fim(&no_a_ser_inserido->lista, &no_base);
                }
            }
        }
        i++;
    }
}

int main() {
    FILE *arq_a, *arq_b;
    Graph *graph_a, *graph_b, *no_a_ser_inserido, *no_base;

    arq_a = fopen("adj_a.txt", "rt");
    arq_b = fopen("adj_b.txt", "rt");

    graph_a=inicializa_vertice();
    graph_b=inicializa_vertice();

    if (arq_a == NULL)
    {
        printf("Problemas na abertura do arquivo\n");
        return 1;
    }

    no_a_ser_inserido=inicializa_vertice();
    no_base=inicializa_vertice();
    
    le_arquivo_cria_grafo(&graph_a, arq_a, no_a_ser_inserido, no_base);
    le_arquivo_cria_grafo(&graph_b, arq_b, no_a_ser_inserido, no_base);


    printf("Grafo A: \n");
    imprime(graph_a);

    printf("Grafo B: \n");
    imprime(graph_b);

    fclose(arq_a);
    fclose(arq_b);

  return 0;
}