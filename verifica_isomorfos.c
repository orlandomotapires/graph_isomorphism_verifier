#include <stdio.h>
#include <string.h>
#include "listaSE.h"

const int MAX = 1e2 + 10;

graph *g; 

int main(){

    char linhas[MAX][MAX];
    int vis[MAX];  

    g = aloca_listase();

    FILE *arq;
    arq = fopen("adj.txt", "rt");

    if(arq == NULL){
        printf("Arquivo nao foi aberto!");
        return 0;
    }

    // Retirando informacoes do arquivo txt
    char linha[MAX];
    int it = 0;
    while(!feof(arq)){
        if(fgets(linha, 50, arq)) strcpy(linhas[it++], linha);
    }

    for(int i = 0; i < strlen(linhas[0]); i++){
        insere_listase_no_fim(&g, linhas[0][i]);
    }  

    for(int i = 1; i < strlen(linhas); i++){
        for(int j = 0; j < strlen(linhas[i]); j++){
            if(linhas[i][j] == '1'){              
                tp_listase *no_base_correto = procura_elemento_base(g, i);
                //printf("No_base_correto->info: %c", no_base_correto->info);
                //printf("\n");

                insere_listase_no_fim(no_base_correto, linhas[0][j]);  
    
            }
        }
    }

    imprime_listase_inteira(g);

//   ABCD
// A 1111
// B 1011
// C 1101
// D 1111

    return 0;

}