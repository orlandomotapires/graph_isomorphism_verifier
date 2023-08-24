#include <stdio.h>
#include <string.h>
#include "listaSE.h"

const int MAX = 1e2 + 10;

graph g; 

int main(){

    char linhas[MAX][MAX];
    int vis[MAX];  

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

    for(int i = 0; i < strlen(linhas); i++){
        for(int j = 0; j < strlen(linhas[i]); j++){
            printf("%c ", linhas[i][j]);
        }

        printf("\n");
    }

    return 0;

}