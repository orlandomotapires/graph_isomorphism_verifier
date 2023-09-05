#include <iostream>
#include <stdio.h>
#include <string.h>
#include "listaSE.h"

int main() {
  FILE *arq;
  char Linha[300];
  char *result;
  int i = 1, a;
  Graph *v, *no_a_ser_inserido, *no_base;

  arq = fopen("adj.txt", "rt");
  v=inicializa_vertice();


  if (arq == NULL)
  {
      printf("Problemas na CRIACAO do arquivo\n");
      return 1;
  }

  no_a_ser_inserido=inicializa_vertice();
  no_base=inicializa_vertice();

  while (!feof(arq)){	// Lê uma linha (inclusive com o '\n')
      if (fgets(Linha, 100, arq))  // Se foi possível ler
      if (i==1){
        for(a=0; a<=(strlen(Linha)); a++){ //for pra criar a lista de vertices
          if (Linha[a] != ' ') insere_lista_principal(&v, Linha[a]);   
        }
      }else{
        for(a=0; a<=(strlen(Linha)); a++){
            if(Linha[a]=='1'){
              no_a_ser_inserido=busca_vertice(v, a+1);
              no_base=busca_vertice(v, (i-1));
              insere_no_fim(&no_a_ser_inserido->lista, &no_base);
            }
        }
    }
        i++;
  }

  imprime(v);
  fclose(arq);

  return 0;
}